#pragma once

#include "../ecs/component.hpp"

#include <glm/gtx/euler_angles.hpp>
#include <glm/glm.hpp>

namespace our
{

    class LightComponent : public Component
    {
    public:
       
        // The ID of this component type is "Lighting"
        static std::string getID() { return "Lighting"; }

        // Reads light component data from the given JSON object
        void deserialize(const nlohmann::json &data) override;
    };

}