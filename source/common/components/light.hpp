#pragma once

#include "../ecs/component.hpp"

#include <glm/gtx/euler_angles.hpp>
#include <glm/glm.hpp>

namespace our
{

    class LightComponent : public Component
    {
    public:
        // TODO: Add more members if needed
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        glm::vec3 position;
        glm::vec3 direction;
        int lightType;
        /*
        #define DIRECTIONAL 0
        #define POINT       1
        #define SPOT        2*/

        // The ID of this component type is "Lighting"
        static std::string getID() { return "Lighting"; }

        // Reads light component data from the given JSON object
        void deserialize(const nlohmann::json &data) override;
    };

}