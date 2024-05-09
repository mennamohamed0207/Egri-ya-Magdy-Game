#pragma once

#include <application.hpp>

#include <ecs/world.hpp>
#include <systems/forward-renderer.hpp>
#include <systems/free-camera-controller.hpp>
#include <systems/free-player-controller.hpp>
#include <systems/repeat-controller.hpp>
#include <systems/movement.hpp>
#include <asset-loader.hpp>
#include<systems/collision.hpp>
#include <imgui.h>

// This state shows how to use the ECS framework and deserialization.
class Playstate: public our::State {

    our::World world;
    our::ForwardRenderer renderer;
    our::FreeCameraControllerSystem cameraController;
    our::FreePLayerControllerSystem playerController;
    our::RepeatControllerSystem repeatController;
    our::CollisionSystem collisionController;
    our::MovementSystem movementSystem;
    
    int score = 0;
    int hearts = 3;
    bool increaseSpeedEffect = false;
    double time = 0.0;

    void onInitialize() override {
        // First of all, we get the scene configuration from the app config
        auto& config = getApp()->getConfig()["scene"];
        // If we have assets in the scene config, we deserialize them
        if(config.contains("assets")){
            our::deserializeAllAssets(config["assets"]);
        }
        // If we have a world in the scene config, we use it to populate our world
        if(config.contains("world")){
            world.deserialize(config["world"]);
        }
        // We initialize the camera controller system since it needs a pointer to the app
        cameraController.enter(getApp());
        playerController.enter(getApp());
        playerController.setPlayer(world.getEntityByName("magdy"));
        playerController.setCamera(world.getEntityByName("camera"));

        repeatController.enter(getApp());
        // Then we initialize the renderer
        collisionController.setPlayer(world.getEntityByName("magdy"));
        auto size = getApp()->getFrameBufferSize();
        renderer.initialize(size, config["renderer"]);
    }

    void onImmediateGui() override
    {
        auto size = getApp()->getFrameBufferSize();

        ImVec2 ScorePos(15, 30);
        ImGui::SetNextWindowPos(ScorePos);
        ImGui::SetNextWindowSize({1000,1000});

        // Set the window background alpha to 0 (fully transparent)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));

        ImGui::Begin("Score", NULL,
                     ImGuiWindowFlags_NoTitleBar |
                         ImGuiWindowFlags_NoResize |
                         ImGuiWindowFlags_NoMove |
                         ImGuiWindowFlags_NoScrollbar |
                         ImGuiWindowFlags_NoSavedSettings |
                         ImGuiWindowFlags_NoInputs |
                         ImGuiWindowFlags_AlwaysAutoResize);

        // Set the text color to fully transparent
        ImVec4 transparentColor(1.0f, 0.0f, 1.0f, 1.0f);
        ImGui::TextColored(transparentColor, "SCORE: %d ", score);
        ImGui::SetWindowFontScale(4.0f);

        ImGui::End();

        ImGui::PopStyleVar(3);  // Pop the style variables
        ImGui::PopStyleColor(); // Pop the style color
    }

    void onDraw(double deltaTime) override {
        // Here, we just run a bunch of systems to control the world logic
        movementSystem.update(&world, (float)deltaTime);
        cameraController.update(&world, (float)deltaTime);
        playerController.update(&world, (float)deltaTime);
        int collider = collisionController.update(&world, (float)deltaTime);
        if(collider==1){
            score= score+10;
        }else if(collider==-1){
            hearts = hearts-1;
            if(hearts==0){
                world.getEntityByName("heart1")->hidden = true;
                world.getEntityByName("heart2")->hidden = true;
                world.getEntityByName("heart3")->hidden = true;
                getApp()->changeState("GameOver");
            }else
            if(hearts==1){
                world.getEntityByName("heart2")->hidden = true;
                world.getEntityByName("heart3")->hidden = true;

            }else if(hearts==2){
                world.getEntityByName("heart3")->hidden = true;
            }
        }else if(collider==2){
           increaseSpeedEffect = true;
           time = glfwGetTime();
        }

        
        collisionController.UpdatePlayerHight(&world);
        // get current time
        repeatController.update(&world);

        // ImGui::TextColored(ImVec4(1, 1, 0, 1), "Score: %d", 8);

        if(increaseSpeedEffect && glfwGetTime() - time > 2.0){
            increaseSpeedEffect = false;
            time = 0.0;
        }

        // And finally we use the renderer system to draw the scene
        renderer.render(&world, increaseSpeedEffect);

        // Get a reference to the keyboard object
        auto &keyboard = getApp()->getKeyboard();

        if(keyboard.justPressed(GLFW_KEY_ESCAPE) ){
            // If the escape  key is pressed in this frame, go to the play state
            getApp()->changeState("menu");
        }
    }

    void onDestroy() override {
        // Don't forget to destroy the renderer
        renderer.destroy();
        // On exit, we call exit for the camera controller system to make sure that the mouse is unlocked
        cameraController.exit();
        playerController.exit();
        repeatController.exit();
        // Clear the world
        world.clear();
        // and we delete all the loaded assets to free memory on the RAM and the VRAM
        our::clearAllAssets();
    }
};