#include "StartScene.h"

#include "ImageGraphicsComponent.h"
#include "TextGraphicsComponent.h"
#include "MouseInputComponent.h"
#include "ButtonAnimationComponent.h"
#include "SceneChangeCoreComponent.h"
#include "LoggingComponent.h"
#include "PlayerInputComponent.h"
#include "PlayerPhysicsComponent.h"
#include "DynamicRigidBodyPhysicsComponent.h"

#include "StaticRigidBodyPhysicsComponent.h"

void relic::StartScene::doInitialisation()
{
    // Asset loading (second number refers to asset type, 0 = texture
    loadAssets({
        {"Black", {".\\Assets\\Black.png", 0}},
        {"Red", {".\\Assets\\Red.png", 0}},
        {"Fancy Font", {".\\Assets\\Fonts\\Astloch-bold.ttf", 60}},
        {"Hi", {"C:\\Users\\dbrat\\Documents\\Coding\\C++\\Games\\Jinny\\Jinny\\Assets\\Hi.png", 0}}
        });

    //GameObject button = new GameObject("Button", { 100, 300, 0, 0 }, new TextGraphicsComponent(""))

    // Text
    //addHUDObject(new GameObject("Text", { 100, 300, 0, 0 }, new TextGraphicsComponent("Hello World!", "Fancy", { 0x00, 0x00, 0x00, 0xFF }, ".\\Assets\\Fonts\\Astloch-bold.ttf", 60)));

    auto& player = m_object_manager->createObject("Player");
    const framework::Shape player_bounds = { 10, 10, 20, 20 };
    player.addComponent(new ImageGraphicsComponent(player_bounds, "Red"));
    player.addComponent(new PlayerInputComponent());
    player.addComponent(new PlayerPhysicsComponent(10, 5, 5, player_bounds));
    player.addComponent(new LoggingComponent());


    auto& wall_1 = m_object_manager->createObject("Wall1");
    const framework::Shape wall_1_bounds = { 630, 0, 10, 480 };
    wall_1.addComponent(new ImageGraphicsComponent(wall_1_bounds, "Black"));
    wall_1.addComponent(new StaticRigidBodyPhysicsComponent(wall_1_bounds));

    auto& wall_2 = m_object_manager->createObject("Wall2");
    const framework::Shape wall_2_bounds = { 10, 470, 620, 10 };
    wall_2.addComponent(new ImageGraphicsComponent(wall_2_bounds, "Black"));
    wall_2.addComponent(new StaticRigidBodyPhysicsComponent(wall_2_bounds, framework::Material::brick));

    auto& wall_3 = m_object_manager->createObject("Wall3");
    const framework::Shape wall_3_bounds = { 0, 0, 10, 480 };
    wall_3.addComponent(new ImageGraphicsComponent(wall_3_bounds, "Black"));
    wall_3.addComponent(new StaticRigidBodyPhysicsComponent(wall_3_bounds));

    auto& wall_4 = m_object_manager->createObject("Wall4");
    const framework::Shape wall_4_bounds = { 10, 0, 620, 10 };
    wall_4.addComponent(new ImageGraphicsComponent(wall_4_bounds, "Black"));
    wall_4.addComponent(new StaticRigidBodyPhysicsComponent(wall_4_bounds));

    auto& dynamic = m_object_manager->createObject("Dynamic");
    const framework::Shape dynamic_bounds = { 300, 200, 20, 20 };
    dynamic.addComponent(new ImageGraphicsComponent(dynamic_bounds, "Black"));
    dynamic.addComponent(new DynamicRigidBodyPhysicsComponent(10, 10, 10, dynamic_bounds, framework::Material::wood, {130, 100}));

    createCamera({ 0, 0, 640, 480 });
}
