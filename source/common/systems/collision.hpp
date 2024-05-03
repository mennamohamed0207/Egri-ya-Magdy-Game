#pragma once
#include "../ecs/world.hpp"
#include "../components/movement.hpp"
#include "../components/mesh-renderer.hpp"
#include "../application.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <iostream>
#include <string>

namespace our
{

    class CollisionSystem
    {
        // std::vector<Entity *> cars, batteries, planes, packages;
        Entity *player;

    public:
        void setPlayer(Entity *player)
        {
            this->player = player;
        }
        char getlane(glm::vec3 position){
            if (position.x >= -0.1 && position.x <= 0.1)
                return 'm';
            else if (position.x < -0.8)
                return 'l';
            else if (position.x > 0.8)
                return 'r';
            return 'm';
        }
        bool checkCollision(Entity *objectComponent, Entity *playerComponent){
            glm::vec3 playerPosition = playerComponent->localTransform.position;
            glm::vec3 objectPosition = objectComponent->localTransform.position;

            // std::cout << getlane(playerPosition) << " " << getlane(objectPosition) << std::endl;
            if (getlane(playerPosition) != getlane(objectPosition))
                return false;
            FreePlayerControllerComponent *player = playerComponent->getComponent<FreePlayerControllerComponent>();
            if (player && player->level == 't')
            {
                RepeatControllerComponent *obj = objectComponent->getComponent<RepeatControllerComponent>();
                if (obj && obj->repeatedObject == "train")
                    return false;
            }
            // glm::vec4 objectCenter = objectComponent->getLocalToWorldMatrix() * glm::vec4(objectComponent->localTransform.position, 1.0);
            // glm::vec4 objectFront = objectCenter + glm::vec4(objectComponent->localTransform.scale, 0.0);
            // glm::vec4 objectBack = objectCenter - glm::vec4(objectComponent->localTransform.scale, 0.0);

            // if (playerPosition.z <= front.z && playerPosition.z >= back.z)
            //     return true;
            // else
            //     return false;

            // glm::mat4 matrix = objectComponent->localTransform.toMat4();
            // glm::vec3 front = glm::vec3(matrix * glm::vec4(0, 0, 1, 0));
            // glm::vec3 back = glm::vec3(matrix * glm::vec4(0, 0, -1, 0));

            glm::vec3 frontFace =  objectPosition + objectComponent->size/2;
            glm::vec3 backFace  = objectPosition - objectComponent->size/2;

            if(objectComponent->name == "coin")
                std::cout << frontFace.z << " " << backFace.z << " " << playerPosition.z << std::endl;

            if (playerPosition.z <= frontFace.z && playerPosition.z >= backFace.z)
                return true;
            else
                return false;
        }

        int update(World *world, float deltaTime)
        {
            // iterate over all entities in the world and check for collisions with the player
            for (const auto &entity : world->getEntities())
            {
                // std::cout << entity->name << std::endl;
                if (entity->name != "magdy" && checkCollision(entity, player))
                {
                    std::cout << "collision happened" << std::endl;
                    if (entity->name == "coin")
                    {
                        entity->hidden = true;
                        return 1;
                    }
                    else if (entity->name == "train")
                    {
                        entity->hidden = true;
                        return -1;
                    }
                }
            }
            return 0;
        }
    };
}