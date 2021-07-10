# Requirements

## Introduction

To design a 2-Dimensional aerial shooter game where protagonist plane shoots enemy Jets through user control.

## Research

### Game Genre

- Picking a game genre early is very important as it lays down the foundation to further improve and innovate.
  <img src="/3_Implementation/Images/game_genre1.png" alt="drawing" width="400"/>

- Top down shooter game belongs to both action and shooting category.

### Game Mechanics

- Gameplay connects players' actions with the purpose of the game and its main challenges.
- Gameplay will define what the player can or cannot do in the game, as well as conditions that allow the player to progress through the game.
- Game mechanics are constructs of rules that make up the gameplay of a game.
- game mechanics can be split into two main categories: core mechanics and sub-mechanics.
- Core mechanics are the most important mechanics in game. Shooting is one of the Core mechanics of this game.
- Sub-mechanics can be taken away without breaking the game. Various types of enemy planes can be regarded as sub-mechanics.

### Level Design

- A level is the venue where a player interacts with the gameplay elements.
- It can also be called as a map or stage.
- Game level with good flow control can direct a player toward the goal of the level and prevent idling or moments of unintentional confusion from occurring in game.
- Player must fight enemy planes till certain time limit and he fights the final boss.
- Certain powerups are also provided to get the user's attention.

### Choosing a visual style

- Before enagaging in design of the characters and environment, we need to set a visual guideline in order to ensure a consistent design throughout the game.
- When we place the characters together with the environment, they should fit with the background, and they should not have too distinctive art style and quality from each other as if the characters and environment were taken from different games.
- visual style can be split between two categories: realistic and stylized. This game belongs to stylized visual.

### The characters concept

- The characters concept usually refers to the concept arts, which display the design of the game characters.
- Here protagonist character is selected as fighter plane. Enemy Characters are designed to be fighter jets.\
   Protagonist Plane <img src="/3_Implementation/Images/Fly.png" alt="Protagonist Plane" width="150"/> \
  Enemy Plane <img src="/3_Implementation/Images/enemy1.png" alt="Enemy Plane" width="150"/>

### The environment concept

- This game has forest background and it scrolls infinitely which gives an appearance of movement of environment.\
  <img src="/3_Implementation/Images/Game_Background_142.png" alt="Protagonist Plane" width="800"/> \

## Cost and Features

• This project features a 2D shooter game which gives lot of fun to user.

• It also has various levels and sceneries to play which gets the attention of the user.

• It quickly builds the game executable file and offers a great FPS approximately 60 frames per second.

## Defining MY System

• This sytem(or game) takes user inputs through keyboard and provides the corresponding game experience to the user.

## SWOT ANALYSIS

   <img src="/3_Implementation/Images/SWOT_Analysis.png" alt="SWOT Analysis" width="800"/>

# 4W&#39;s and 1&#39;H

## Who:

• Intended for people who loves to play 2D aerial shooter games like old classics.

## What:

• It gives lot of fun to play as it has appropriate music, sound and background image assets.

## When:

• When the user gets bored and thinks of playing games.

## Where:

• Users can use this application on their desktop or laptop terminal.

# Detail requirements

## High Level Requirements

| ID   | Description                                                             | Status (Implemented/Future) |
| ---- | ----------------------------------------------------------------------- | --------------------------- |
| HA01 | Creating a responsive window                                            | Implemented                 |
| HA02 | Getting User Input from keyboard                                        | Implemented                 |
| HA03 | Selection of appropriate game assets                                    | Implemented                 |
| HA04 | Movement of player plane corressponding to user input                   | Implemented                 |
| HA05 | Enemy fighter jets creation and spawning the window at appropriate time | Implemented                 |
| HA06 | Animation of plane destruction and background image scrolling           | Implemented                 |

## Low level Requirements

| ID   | Description                                                                                                                      | HLR  | Status (Implemented/Future) |
| ---- | -------------------------------------------------------------------------------------------------------------------------------- | ---- | --------------------------- |
| LA01 | Importing all required SDL libraries and testing them                                                                            | HA01 | Implemented                 |
| LA02 | Creating a game renderer and game window which accepts user inputs through keyboard                                              | HA01 | Implemented                 |
| LA03 | Getting user input from keyboard and verifying through SDL scancodes                                                             | HA02 | Implemented                 |
| LA04 | Creating game background in adobe photoshop and player, enemy planes & their bullets                                             | HA03 | Implemented                 |
| LA05 | Laoding the player plane texture & changing its position coordinates according to user inputs                                    | HA04 | Implemented                 |
| LA06 | Loading player plane bullet's texture and implementing linked list for all the bullets                                           | HA04 | Implemented                 |
| LA07 | Loading enemy plane texture and their bullets. Create linked list for enemy planes for managing their position and firing bullet | HA05 | Implemented                 |
| LA08 | Animation of explosion when a bullet touches the plane                                                                           | HA06 | Implemented                 |
| LA09 | Importing sound & music and turning them on at appropriate game instants                                                         | HA06 | Implemented                 |
| LA10 | Background Image scrolling                                                                                                       | HA06 | Implemented                 |
| LA11 | Background dust particles animation by creating array of 500 dots which are spread randomly on game window                       | HA06 | Implemented                 |
| LA12 | Resetting the whole game when user plane gets destroyed due to enemy's bullet                                                    | HA01 | Implemented                 |
| LA13 | Implementation of enemy bullet trajectory towards user palne by calculating the slope                                            | HA05 | Implemented                 |
