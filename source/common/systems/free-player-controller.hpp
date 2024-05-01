#pragma once

#include "../ecs/world.hpp"
#include "../components/camera.hpp"
#include "../components/free-player-controller.hpp"

#include "../application.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <iostream>

namespace our
{

    // The free camera controller system is responsible for moving every entity which contains a FreeCameraControllerComponent.
    // This system is added as a slightly complex example for how use the ECS framework to implement logic.
    // For more information, see "common/components/free-camera-controller.hpp"
    class FreePLayerControllerSystem
    {
        Application *app;           // The application in which the state runs
        bool mouse_locked = false;  // Is the mouse locked
        float jumpStrength = 10.0f; // Strength of the jump impulse
        bool isOnGround = true;     // This should be updated based on collision detection with the ground
        bool isRightKeyPressed = false;
        bool isLeftKeyPressed = false;

    public:
        // When a state enters, it should call this function and give it the pointer to the application
        void enter(Application *app)
        {
            this->app = app;
        }

        // This should be called every frame to update all entities containing a FreeCameraControllerComponent
        void update(World *world, float deltaTime)
        {
            // First of all, we search for an entity containing both a CameraComponent and a FreeCameraControllerComponent
            // As soon as we find one, we break
            CameraComponent *camera = nullptr;
            FreePlayerControllerComponent *controller = nullptr;
            for (auto entity : world->getEntities())
            {
                camera = entity->getComponent<CameraComponent>();
                controller = entity->getComponent<FreePlayerControllerComponent>();
                if (controller)
                    break;
            }
            if (!(controller))
                return;
            // Get the entity that we found via getOwner of camera (we could use controller->getOwner())
            Entity *entity = controller->getOwner();

            // We get a reference to the entity's position and rotation
            glm::vec3 &position = entity->localTransform.position;
            glm::vec3 &rotation = entity->localTransform.rotation;

            // We prevent the pitch from exceeding a certain angle from the XZ plane to prevent gimbal locks
            if (rotation.x < -glm::half_pi<float>() * 0.99f)
                rotation.x = -glm::half_pi<float>() * 0.99f;
            if (rotation.x > glm::half_pi<float>() * 0.99f)
                rotation.x = glm::half_pi<float>() * 0.99f;
            // This is not necessary, but whenever the rotation goes outside the 0 to 2*PI range, we wrap it back inside.
            // This could prevent floating point error if the player rotates in single direction for an extremely long time.
            rotation.y = glm::wrapAngle(rotation.y);

            // We get the camera model matrix (relative to its parent) to compute the front, up and right directions
            glm::mat4 matrix = entity->localTransform.toMat4();

            glm::vec3 front = glm::vec3(matrix * glm::vec4(0, 0, -1, 0)),
                      up = glm::vec3(matrix * glm::vec4(0, 1, 0, 0)),
                      right = glm::vec3(matrix * glm::vec4(1, 0, 0, 0));

            glm::vec3 current_sensitivity = controller->positionSensitivity;

            position -= front * (deltaTime * current_sensitivity.z);
            if (app->getKeyboard().isPressed(GLFW_KEY_SPACE) && !controller->isJumping)
            {
                controller->isJumping = true;                             // The player starts jumping
                controller->currentVelocity.y = controller->jumpVelocity; // Apply vertical jump velocity
            }

            // Apply gravity and update position if jumping
            if (controller->isJumping)
            {
                position += controller->currentVelocity * deltaTime;              // Update position based on current velocity
                controller->currentVelocity.y -= controller->gravity * deltaTime; // Apply gravity to vertical velocity

                // Check if player has landed
                if (position.y <= 0.8)
                {
                    position.y = 0.8;                  // Reset to ground level
                    controller->isJumping = false;     // Stop jumping
                    controller->currentVelocity.y = 0; // Reset vertical velocity
                    controller->currentVelocity.x = 0; // Reset horizontal velocity
                }
            }
            // If the LEFT SHIFT key is pressed, we multiply the position sensitivity by the speed up factor
            if (app->getKeyboard().isPressed(GLFW_KEY_LEFT_SHIFT))
                current_sensitivity *= controller->speedupFactor;

            // this is for checking for the key press of left and right, but making the key press registered only once
            if (app->getKeyboard().isPressed(GLFW_KEY_RIGHT))
            {
                if (!isRightKeyPressed)
                {
                    if (position.x >= 0.9)
                    {
                        position.x=1;
                    }
                    else
                    position -= right * glm::vec3(20, 20, 20);
                    isRightKeyPressed = true;
                }
            }
            else
            {
                isRightKeyPressed = false;
            }

            // Check for left key press
            if (app->getKeyboard().isPressed(GLFW_KEY_LEFT) )
            {
                if (!isLeftKeyPressed)
                {
                    if (position.x <= -1)
                    {
                        position.x=-1;
                    }
                    else
                    position += right * glm::vec3(20, 20, 20);
                    isLeftKeyPressed = true;
                }
            }
            else
            {
                isLeftKeyPressed = false;
            }
        }
        // When the state exits, it should call this function to ensure the mouse is unlocked
        void
        exit()
        {
            if (mouse_locked)
            {
                mouse_locked = false;
                app->getMouse().unlockMouse(app->getWindow());
            }
        }
    };
}
