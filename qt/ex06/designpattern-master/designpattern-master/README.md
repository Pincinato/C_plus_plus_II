Producer Consumer Pattern
=========================
This repo contains a basic example of a producer-consumer pattern

## Exercises ##

Exercise 06: Observer Pattern
------------------------------
 * Implement the observer pattern to reduce coupling and increase code reuse. In particular, remove compile time dependencies by:
 1. decoupling module Control from Module VCamera, i.e. VCamera should compile without the knowledge of module Control
 2. decoupling module Widget from Module Control, i.e. Control should compile without the knowledge of module Widget
 * Therefore, you have to implement an abstract interface IVCamera for VCamera and IControl for Control
    
    