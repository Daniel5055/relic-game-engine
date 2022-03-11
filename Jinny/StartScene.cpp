#include "StartScene.h"

#include "ImageGraphicsComponent.h"
#include "TextGraphicsComponent.h"
#include "MouseInputComponent.h"
#include "ButtonAnimationComponent.h"
#include "EventChangeCoreComponent.h"
#include "LoggingComponent.h"
#include "CameraCoreComponent.h"
#include "PlayerInputComponent.h"
#include "PlayerPhysicsComponent.h"
#include "DynamicRigidBodyPhysicsComponent.h"

#include "StaticRigidBodyPhysicsComponent.h"

void Jinny::StartScene::initialize()
{
	// Asset loading
	loadAssets({
		{"Black", {".\\Assets\\Black.png", 0}},
		{"Red", {".\\Assets\\Red.png", 0}},
		{"Fancy Font", {".\\Assets\\Fonts\\Astloch-bold.ttf", 60}}
		});

	CoreComponent* core = new EventChangeCoreComponent(ObjectInput(ObjectInputType::LEFT_MOUSE_UP), nullptr);

	//AnimationComponent* animation = new ButtonAnimationComponent(graphics, 100, 150);
	LoggingComponent* logging = new LoggingComponent();


	//button->addComponent(animation);
	//button->addComponent(logging);

	//addStaticObject(button);

	// Text
	//addStaticObject(new GameObject("Text", { 100, 300, 0, 0 }, new TextGraphicsComponent("Thors Sexploration!", "Fancy", { 0x00, 0x00, 0x00, 0xFF }, ".\\Assets\\Fonts\\Astloch-bold.ttf", 60)));

	GameObject* o = new GameObject("Player", { 300, 20, 20, 20 }, new ImageGraphicsComponent("Red"), new PlayerInputComponent(), new PlayerPhysicsComponent(10, 2, 10), nullptr);
	
	o->addComponent(logging);

	addWorldObject(new GameObject("Static1", { 630, 0, 100, 500 }, new ImageGraphicsComponent("Black"), nullptr, new StaticRigidBodyPhysicsComponent()));
	addWorldObject(new GameObject("Static2", { -90, 0, 100, 500 }, new ImageGraphicsComponent("Black"), nullptr, new StaticRigidBodyPhysicsComponent()));
	addWorldObject(new GameObject("Static2", { 0, -90, 800, 100 }, new ImageGraphicsComponent("Black"), nullptr, new StaticRigidBodyPhysicsComponent()));
	addWorldObject(new GameObject("Static2", { 0, 470, 800, 100}, new ImageGraphicsComponent("Black"), nullptr, new StaticRigidBodyPhysicsComponent()));

	addWorldObject(new GameObject("Static2", { 200, 200, 100, 100 }, new ImageGraphicsComponent("Black"), nullptr, new StaticRigidBodyPhysicsComponent()));

	addWorldObject(new GameObject("Dy2", { 100, 100, 50, 50 }, new ImageGraphicsComponent("Red"), nullptr, new DynamicRigidBodyPhysicsComponent(10, 10, 10, Framework::Material::METAL)));
	//addWorldObject(new GameObject("Dy3", { 400, 400, 20, 20 }, new ImageGraphicsComponent("Black"), nullptr, new DynamicRigidBodyPhysicsComponent(5, 10, 10, Framework::Material::NULLIUM, { -400, -400})));
	//addWorldObject(new GameObject("Dy4", { 610, 450, 20, 20 }, new ImageGraphicsComponent("Red"), nullptr, new DynamicRigidBodyPhysicsComponent(5, 10, 10)));
	//addWorldObject(new GameObject("Dy5", { 500, 200, 20, 20 }, new ImageGraphicsComponent("Black"), nullptr, new DynamicRigidBodyPhysicsComponent(5, 10, 10, Framework::Material::NULLIUM, { 0, 500 })));
	//addWorldObject(new GameObject("Dy6", { 500, 300, 20, 20 }, new ImageGraphicsComponent("Red"), nullptr, new DynamicRigidBodyPhysicsComponent(5, 10, 10, { 300, 0 })));
	//addWorldObject(new GameObject("Dy7", { 500, 400, 20, 20 }, new ImageGraphicsComponent("Black"), nullptr, new DynamicRigidBodyPhysicsComponent(5, 10, 10, { 100, 100 })));

	//addStaticObject(new GameObject("Static2", { 299, 49, 100, 150 }, new ImageGraphicsComponent("Hi"), nullptr, new StaticRigidBodyPhysicsComponent()));

	addWorldObject(o);

	createCamera({ 0, 0, 640, 480 });
}