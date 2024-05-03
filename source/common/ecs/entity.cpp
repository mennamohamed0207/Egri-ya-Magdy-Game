#include "entity.hpp"
#include "../deserialize-utils.hpp"
#include "../components/component-deserializer.hpp"

#include <glm/gtx/euler_angles.hpp>

namespace our
{

    // This function returns the transformation matrix from the entity's local space to the world space
    // Remember that you can get the transformation matrix from this entity to its parent from "localTransform"
    // To get the local to world matrix, you need to combine this entities matrix with its parent's matrix and
    // its parent's parent's matrix and so on till you reach the root.
    glm::mat4 Entity::getLocalToWorldMatrix() const
    {
        // TODO: (Req 8) Write this function
        glm::mat4 result = localTransform.toMat4();
        const Entity *parent = this->parent;
        // to get the root of the tree
        while (parent != nullptr)
        {
            // to get the transformation matrix from this entity to its parent
            result = parent->localTransform.toMat4() * result;
            parent = parent->parent;
        }
        return result;
    }

    // Deserializes the entity data and components from a json object
    void Entity::deserialize(const nlohmann::json &data)
    {
        if (!data.is_object())
            return;
        name = data.value("name", name);
        glm::vec3 position = data.value("position", glm::vec3(0, 0, 0));
        if (position.x >= -0.5 && position.x <= 0.5)
            lane = 'm';
        else if(position.x < -0.5) lane='l';
        else if(position.x > 0.5) lane='r';
        localTransform.deserialize(data);
        if (data.contains("components"))
        {
            if (const auto &components = data["components"]; components.is_array())
            {
                for (auto &component : components)
                {
                    deserializeComponent(component, this);
                }
            }
        }
    }

}