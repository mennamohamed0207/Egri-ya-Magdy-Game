#include "light.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"

namespace our
{
    void LightComponent::deserialize(const nlohmann::json &data)
    {
        // Check if the JSON data is an object
        if (!data.is_object())
            return;

        // TODO:Read the data of light form the json file 
    }
}