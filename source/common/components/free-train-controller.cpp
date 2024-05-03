#include "free-train-controller.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"

namespace our {
    // Reads sensitivities & speedupFactor from the given json object
    void FreeTrainControllerComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
        speedupFactor = data.value("speedupFactor", speedupFactor);
    }
}