Game Engine
===========

This was a project I started working on in 2020. I had wanted to create a decent game engine. The project was named Jinny and the source code can be found in the Jinny directory. I originally developed this engine for about 3 months using some notable design patterns I had picked up from https://gameprogrammingpatterns.com/. Unfortunately, I eventually stopped working on it after accidentally breaking the program and not keeping it version controlled. Now I have decided to revive this project due to the considerable progress I had already made. With 8000 lines of code in the project when I rediscovered it, I decided it was worthwhile to continue this development, however I will need to refine some of the code as my coding practices have improved since I first programmed the project.

Development
===========

When I first worked on the project, I had no idea what git was and so I never had any version control. Not suprisingly, I eventually made some changes to the program that did not work and I could not reverse it easily. Looking at the code now, luckily the design meant that most of the broken code was isolated to the physics engine so I still recovered the whole underlying structure.

I will briefly explain the structure now. The game engine consists of different systems that communicate with eachother via a dettached messaging bus system. There exists a physics, graphics, input, and core system so far. These systems also utilise tools I developed in a namespace called framework. This was essentially a wrapper namespace for SDL2 code or physics-related calculation code. For the game objects, I decided to use the component pattern, where each game object is essentially defined by a collection of components. These components are either physics, graphics, input, core, or misc and all inherit from a single component class. So for example some text displayed on the screen would be a game object with the TextGraphicsComponenet, while a player contains components like the ImageGraphicComponent, PlayerInputComponent, PlayerPhysicsComponent.

To communicate between each other, components use a simple internal messaging system within the object yet I currently this is weakly implemented and I find that I coupled the components too closely to the game object so I will improve that as I move on.

Game states are called scenes and are where game objects are intially defined.

The physics engine I designed at the time is rather overly complicated (I think) yet it included friction, the coefficient of restitution, and dampening. Notably it only worked for 2d rectangular orthoganl objects. I am currently rewriting the collision engine with better coding practises and a simpler design, almost identical to this prototype I developed in Java a few months back, https://github.com/Daniel5055/physics-engine. A flowchart of the original collision system is available in the readme of that repository.

I believe the concludes everything I have to say so far. I also realised I did actually keep the changes I made on the physics engine in a text file in the repo which details the developments I made. I understand that some of the complexity I added to this physics engine was meant to make it quicker (over optimisation in my opinion), so I will look back on that log at a later date to see if I could reimplement some of these concepts. The new physics engine I am building is in the branch new_physics of this repository.
