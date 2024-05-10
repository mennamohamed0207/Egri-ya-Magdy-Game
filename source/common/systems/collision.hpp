#pragma once
#include "../ecs/world.hpp"
#include "../components/movement.hpp"
#include "../components/mesh-renderer.hpp"
#include "../application.hpp"
#include "repeat-controller.hpp"
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
        void setPlayerHight(float hight)
        {
            glm::vec3 &position = player->localTransform.position;
            position.y = hight;
        }

        char getlane(glm::vec3 position)
        {
            if (position.x >= -0.1 && position.x <= 0.1)
                return 'm';
            else if (position.x < -0.8)
                return 'l';
            else if (position.x > 0.8)
                return 'r';
            return 'm';
        }
        char getlevel(glm::vec3 position)
        {
            // set the level of the player
            if (position.y >= 1.5)
                return 't';
            else
                return 'f';
            return 'f';
        }
        bool checkCollision(Entity *objectComponent, Entity *playerComponent)
        {
            glm::vec3 playerPosition = playerComponent->localTransform.position;
            glm::vec3 objectPosition = objectComponent->localTransform.position;

            // std::cout << getlane(playerPosition) << " " << getlane(objectPosition) << std::endl;
            if (getlane(playerPosition) != getlane(objectPosition))
                return false;
            if (getlevel(playerPosition) != getlevel(objectPosition))
                return false;
            FreePlayerControllerComponent *player = playerComponent->getComponent<FreePlayerControllerComponent>();
            if (player && player->level == 't')
            {
                RepeatControllerComponent *obj = objectComponent->getComponent<RepeatControllerComponent>();
                if (obj && obj->repeatedObject == "train")
                    return false;
            }

            glm::vec3 frontFace = objectPosition + objectComponent->size / 2;
            glm::vec3 backFace = objectPosition - objectComponent->size / 2;

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
                if (entity->hidden==false && entity->name != "magdy" && checkCollision(entity, player))
                {
                    // std::cout << "collision happened" << std::endl;
                    if (entity->name == "coin")
                    {
                        entity->hidden = true;
                        return 1;
                    }
                    else if (entity->name == "train")
                    {

                        if (player->getComponent<FreePlayerControllerComponent>()->isJumping == true)
                        {
                            // std::cout<<"jumping"<<std::endl;
                            player->getComponent<FreePlayerControllerComponent>()->isJumping = false;
                            player->getComponent<FreePlayerControllerComponent>()->currentVelocity.y = 0;
                            player->getComponent<FreePlayerControllerComponent>()->currentVelocity.x = 0;
                            setPlayerHight(1.5);
                            return 0;
                        }
                        entity->hidden = true;
                        return -1;
                    }
                    else if (entity->name == "star"){
                        entity->hidden = true;
                        return 2;
                    }else if (entity->name == "heart"){
                        entity->hidden = true;
                        return 3;
                    }
                }
            }
            return 0;
        }
        void UpdatePlayerHight(World *world)
        {
            if(player->getComponent<FreePlayerControllerComponent>()->isJumping == true) return;
            // std::cout << "UpdatePlayerHight" << std::endl;
            bool isFalling = true;
            for (const auto &entity : world->getEntities())
            {
                if (entity->name == "train" && !entity->hidden)
                {
                    glm::vec3 playerPosition = player->localTransform.position;
                    glm::vec3 objectPosition = entity->localTransform.position;

                    // std::cout << getlane(playerPosition) << " " << getlane(objectPosition) << std::endl;
                    if (getlane(playerPosition) != getlane(objectPosition))
                        continue;

                    glm::vec3 frontFace = objectPosition + entity->size / 2;
                    glm::vec3 backFace = objectPosition - entity->size / 2;

                    if (playerPosition.z <= frontFace.z && playerPosition.z >= backFace.z)
                    {
                        // std::cout << "is falling = false" << std::endl;
                        // setPlayerHight(1);
                        isFalling = false;
                    }
                }
            }
            if (isFalling)
                setPlayerHight(1);
        }
    };

}