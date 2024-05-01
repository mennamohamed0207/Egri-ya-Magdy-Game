#include "world.hpp"
#include "../components/free-train-controller.hpp"
#include <vector>
#include <iostream>
namespace our
{

    // This will deserialize a json array of entities and add the new entities to the current world
    // If parent pointer is not null, the new entities will be have their parent set to that given pointer
    // If any of the entities has children, this function will be called recursively for these children
    std::vector<nlohmann::json> trains;
    void World::deserialize(const nlohmann::json &data, Entity *parent)
    {
        if (!data.is_array())
            return;

        for (const auto &entityData : data)
        {
            // TODO: (Req 8) Create an entity, make its parent "parent" and call its deserialize with "entityData".
            Entity *entity = this->add();
            entity->parent = parent;
            entity->deserialize(entityData);

            if (entityData.contains("type") && entityData["type"] == "Free Train Controller")
            {
                trains.push_back(entityData);
            }
            if (entityData.contains("children"))
            {
                // TODO: (Req 8) Recursively call this world's "deserialize" using the children data
                //  and the current entity as the parent
                deserialize(entityData["children"], entity);
            }
        }
        // This part is for repeating the obstacles
        std::vector<nlohmann::json> repeatedTrains;
        for (auto &train : trains)
        {
            if (train.contains("position"))
            {
                auto positionArray = train["position"];
                glm::vec3 position(positionArray[0].get<float>(), positionArray[1].get<float>(), positionArray[2].get<float>());
                int repeatCount = 1; // rand() % 100 + 1;
                for (int i = 0; i < repeatCount; i++)
                {
                    // float randX = position.x + rand() % 101 - 55;
                    // float randY = position.y + rand() % 6;
                    // float randZ = position.z + rand() % 81 - 40;
                    float randX = position.x ;
                    float randY = position.y;
                    float randZ = position.z +4;

                    train["position"] = {randX, randY, randZ};

                    // if (obstacle.contains("children"))
                    // {
                    //     deserialize(obstacle["children"], entity);
                    // }

                    repeatedTrains.push_back(train);
                }
            }
        }

        for (const auto &train : repeatedTrains)
        {
            Entity *entity = add();
            entity->parent = parent;
            entity->deserialize(train);
        }
    }

}