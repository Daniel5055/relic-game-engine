#include "StartScene.h"

#include "ImageGraphicsComponent.h"
#include "TextGraphicsComponent.h"
#include "ButtonInputComponent.h"
#include "ButtonLogicComponent.h"
#include "ButtonAnimationComponent.h"
#include "SceneChangeCoreComponent.h"
#include "LoggingComponent.h"
#include "PlayerInputComponent.h"
#include "PlayerPhysicsComponent.h"
#include "RigidBodyPhysicsComponent.h"
#include "SolidColourGraphicsComponent.h"
#include "GameObject.h"

#include "StaticRigidBodyPhysicsComponent.h"

void relic::StartScene::doInitialisation()
{
    // Second number is font size, might separate asset loading into font and texture loading
    loadAssets({
        {"Black", {".\\Assets\\Black.png", 0}},
        {"Red", {".\\Assets\\Red.png", 0}},
        {"Penguin", {".\\Assets\\Global Textures\\PenguinSprite.png", 0}},
        {"Fancy Font", {".\\Assets\\Fonts\\Astloch-bold.ttf", 60}},
        {"Hi", {".\\Assets\\Hi.png", 0}},
        });

    //GameObject button = new GameObject("Button", { 100, 300, 0, 0 }, new TextGraphicsComponent(""))

    // Text
    //addHUDObject(new GameObject("Text", { 100, 300, 0, 0 }, new TextGraphicsComponent("Hello World!", "Fancy", { 0x00, 0x00, 0x00, 0xFF }, ".\\Assets\\Fonts\\Astloch-bold.ttf", 60)));

    GameObject& player = createObject("Player");
    const framework::Shape player_bounds = { 10, 10, 20, 20 };
    player.addComponent(new SolidColourGraphicsComponent(player_bounds, {255, 0, 0, 255}));
    player.addComponent(new PlayerInputComponent());
    player.addComponent(new PlayerPhysicsComponent(10, 5, 5, player_bounds));
    player.addComponent(new LoggingComponent());

    GameObject& wall_1 = createObject("Wall1");
    const framework::Shape wall_1_bounds = { 630, 0, 10, 480 };
    wall_1.addComponent(new ImageGraphicsComponent(wall_1_bounds, "Black"));
    wall_1.addComponent(new StaticRigidBodyPhysicsComponent(wall_1_bounds));

    GameObject& wall_2 = createObject("Wall2");
    const framework::Shape wall_2_bounds = { 10, 470, 620, 10 };
    wall_2.addComponent(new ImageGraphicsComponent(wall_2_bounds, "Black"));
    wall_2.addComponent(new StaticRigidBodyPhysicsComponent(wall_2_bounds, framework::Material::brick));

    GameObject& wall_3 = createObject("Wall3");
    const framework::Shape wall_3_bounds = { 0, 0, 10, 480 };
    wall_3.addComponent(new ImageGraphicsComponent(wall_3_bounds, "Black"));
    wall_3.addComponent(new StaticRigidBodyPhysicsComponent(wall_3_bounds));

    GameObject& wall_4 = createObject("Wall4");
    const framework::Shape wall_4_bounds = { 10, 0, 620, 10 };
    wall_4.addComponent(new ImageGraphicsComponent(wall_4_bounds, "Black"));
    wall_4.addComponent(new StaticRigidBodyPhysicsComponent(wall_4_bounds));

    //GameObject& dynamic = createObject("Dynamic");
    //const framework::Shape dynamic_bounds = { 300, 200, 20, 20 };
    //dynamic.addComponent(new ImageGraphicsComponent(dynamic_bounds, "Black"));
    //dynamic.addComponent(new RigidBodyPhysicsComponent(10, 0, dynamic_bounds, framework::Material::wood, 10, 10, {130, 100}));

    /*
    GameObject& penguin = createObject("Penguin");
    const framework::Shape bounds = { 50, 214, 256, 256 };
    penguin.addComponent(new ImageGraphicsComponent(bounds, "Penguin"));
    penguin.addComponent(new RigidBodyPhysicsComponent(10, 0, bounds, framework::Material::nullium, 0, 0, { 200, 0 }));
    */

    GameObject& button = createObject("Button");
    const framework::Shape button_bounds = { 200, 200, 100, 50 };

    button.addComponent(new ButtonInputComponent(button_bounds));
    button.addComponent(new ButtonLogicComponent());
    button.addComponent(new ImageGraphicsComponent(button_bounds, "Hi"));
    button.addComponent(new AnimationComponent(100, 150, true));

    createCamera({ 0, 0, 640, 480 });
}
