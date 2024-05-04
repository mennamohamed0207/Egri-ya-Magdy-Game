#pragma once

#include "../ecs/world.hpp"
#include "../components/camera.hpp"
#include "../components/repeat-controller.hpp"
#include "../components/repeat-controller.hpp"

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
    class RepeatControllerSystem
    {
        Application *app;          // The application in which the state runs
        bool mouse_locked = false; // Is the mouse locked

    public:
        // When a state enters, it should call this function and give it the pointer to the application
        void enter(Application *app)
        {
            this->app = app;
        }

        // This should be called every frame to update all entities containing a FreeCameraControllerComponent
        void update(World *world)
        {
            // First of all, we search for an entity containing both a CameraComponent and a FreeCameraControllerComponent
            // As soon as we find one, we break
            CameraComponent *camera = nullptr;

            RepeatControllerComponent *controller = nullptr;
            for (auto entity : world->getEntities())
            {
                camera = entity->getComponent<CameraComponent>();
                if (camera)
                    break;
            }
            if (!camera)
                return;
            Entity *camEntity = camera->getOwner();
            glm::vec3 &cam_position = camEntity->localTransform.position;

            for (auto entity : world->getEntities())
            {
                controller = entity->getComponent<RepeatControllerComponent>();

                if (controller)
                {
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

                    if (controller->repeatedObject == "train")
                    {
                        // std::cout<<"z"<<std::endl;
                        position -= front * abs(static_cast<float>(cos(2 * glm::pi<float>() * controller->currentTime * controller->speedupFactor)))*controller->speedupFactor;
                        controller->currentTime += 0.001f;
                        // std::cout << position.z << " " << controller->currentTime << std::endl;
                        if (position.z > 4.0f)
                        {
                            position.z = -60.0f + cam_position.z;
                            controller->currentTime = 0.0f;
                            entity->hidden = false;
                            // std::cout << front.z << std::endl;
                        }
                    }
                    else if(controller->repeatedObject == "coin")
                    {
                        controller->speedupFactor=3;
                        // std::cout<<"z"<<std::endl;
                        position -= front * abs(static_cast<float>(cos(2 * glm::pi<float>() * controller->currentTime * controller->speedupFactor)))*controller->speedupFactor;
                        // controller->currentTime += 0.001f;
                        // std::cout << position.z << " " << controller->currentTime << std::endl;
                        if (position.z > 4.0f)
                        {
                            position.z = -60.0f + cam_position.z;
                            controller->currentTime = 0.0f;
                            entity->hidden = false;
                            // std::cout << front.z << std::endl;
                        }
                    }
                    else if (controller->repeatedObject == "floor")
                    {

                        // std::cout << position.z << " " << cam_position.z<< std::endl;
                        position.z = controller->initialpos+cam_position.z;

                    }
                }
            }
            if (!(controller))
                return;
            // Get the entity that we found via getOwner of camera (we could use controller->getOwner())
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
