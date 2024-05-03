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

        bool checkCollision(Entity *playerComponent, Entity *objectComponent)
        {
            if (playerComponent->lane != objectComponent->lane)
                return false;
            if (playerComponent->getComponent<FreePlayerControllerComponent>()->level == 't')
            {
                RepeatControllerComponent *obj = objectComponent->getComponent<RepeatControllerComponent>();
                if (obj && obj->repeatedObject == "train") return false;
            }

            glm::vec4 objectCenter = objectComponent->getLocalToWorldMatrix() * glm::vec4(objectComponent->localTransform.position, 1.0);
            glm::vec4 objectFront = objectCenter + glm::vec4(objectComponent->localTransform.scale, 0.0);
            glm::vec4 objectBack = objectCenter - glm::vec4(objectComponent->localTransform.scale, 0.0);
            glm::vec3 playerPosition = playerComponent->localTransform.position;

            if (playerPosition.z <= objectFront.z && playerPosition.z >= objectBack.z)
                return true;
            else
                return false;
        }

        int update(World *world, float deltaTime)
        {
            // iterate over all entities in the world and check for collisions with the player
            for (const auto &entity : world->getEntities())
            {
                if (checkCollision(entity, player) && entity->name != "magdy")
                {
                    std::cout << "collision happened" << std::endl;
                    if (entity->name == "coin")
                    {
                        world->markForRemoval(entity);
                        return 1;
                    }
                    else if (entity->name == "train")
                    {
                        world->markForRemoval(entity);
                        return -1;
                    }
                    else if ((entity->name == "package"))
                    {
                        world->markForRemoval(entity);
                        return 2;
                    }
                    return 1;
                }
            }

            return 0;
        }
    };
}