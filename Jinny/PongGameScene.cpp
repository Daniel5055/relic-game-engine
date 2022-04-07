#include "PongGameScene.h"

#include "PongPaddleInputComponent.h"
#include "PongPaddlePhysicsComponent.h"
#include "SolidColourGraphicsComponent.h"
#include "LoggingComponent.h"
#include "StaticRigidBodyPhysicsComponent.h"
#include "PongBallPhysicsComponent.h"

void relic::pong::PongGameScene::doInitialisation()
{
    auto& paddle_1 = createObject("Paddle 1");
    const framework::Shape paddle_1_bounds = { 50, 190, 20, 100 };
    paddle_1.addComponent(new PongPaddlePhysicsComponent(paddle_1_bounds, 'w', 's'));
    paddle_1.addComponent(new PongPaddleInputComponent('w', 's'));
    paddle_1.addComponent(new SolidColourGraphicsComponent(paddle_1_bounds, {200, 200, 100, 255}));
    paddle_1.addComponent(new LoggingComponent());

    auto& paddle_2 = createObject("Paddle 1");
    const framework::Shape paddle_2_bounds = { 570, 190, 20, 100 };
    paddle_2.addComponent(new PongPaddlePhysicsComponent(paddle_2_bounds, 'k', 'j'));
    paddle_2.addComponent(new PongPaddleInputComponent('k', 'j'));
    paddle_2.addComponent(new SolidColourGraphicsComponent(paddle_2_bounds, {200, 0, 100, 255}));
    paddle_2.addComponent(new LoggingComponent());

    auto& wall_1 = createObject("Wall1");
    const framework::Shape wall_1_bounds = { 630, 0, 10, 480 };
    wall_1.addComponent(new SolidColourGraphicsComponent(wall_1_bounds, {0, 0, 0, 255}));
    wall_1.addComponent(new StaticRigidBodyPhysicsComponent(wall_1_bounds));

    auto& wall_2 = createObject("Wall2");
    const framework::Shape wall_2_bounds = { 10, 470, 620, 10 };
    wall_2.addComponent(new SolidColourGraphicsComponent(wall_2_bounds, {0, 0, 0, 255}));
    wall_2.addComponent(new StaticRigidBodyPhysicsComponent(wall_2_bounds));

    auto& wall_3 = createObject("Wall3");
    const framework::Shape wall_3_bounds = { 0, 0, 10, 480 };
    wall_3.addComponent(new SolidColourGraphicsComponent(wall_3_bounds, {0, 0, 0, 255}));
    wall_3.addComponent(new StaticRigidBodyPhysicsComponent(wall_3_bounds));

    auto& wall_4 = createObject("Wall4");
    const framework::Shape wall_4_bounds = { 10, 0, 620, 10 };
    wall_4.addComponent(new SolidColourGraphicsComponent(wall_4_bounds, {0, 0, 0, 255}));
    wall_4.addComponent(new StaticRigidBodyPhysicsComponent(wall_4_bounds));

    auto& ball = createObject("Ball");
    const framework::Shape ball_bounds = { 200, 210, 20, 20 };
    ball.addComponent(new SolidColourGraphicsComponent(ball_bounds, { 0, 0, 0, 255 }));
    ball.addComponent(new PongBallPhysicsComponent(ball_bounds, wall_3.getId(), wall_1.getId()));
}
