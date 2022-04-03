Plans as of the 3rd April 2022 for development
==============================================

- Introduce more easily accessible logging and error registering features

- Change the LazyMessageSender to send queued messages on a method call rather than on addReceiver method

- Perhaps make better use of the component incorporated event in component intialisation? (Currently using lazy message senders which work well)

- Find a better solution for scenes creating components rather than directly referencing object managaer

- Change the messages sent between classes to be more flexible and optimised

- Change the design of components needing other components, such that they are decoupled (Like the Animation Component)

- Added documentation to the remaining classes

- Clean up code in the remaining classes

- Look more into move semantics and optimising message storing

- Create Rigid body base class component

- Allow for the other main component types to receive messages from systems
