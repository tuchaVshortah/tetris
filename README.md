Read it carefully.

Known bugs:

    Sometimes blocks may disappear from the screen

WARNING!
This software is in alpha state. NOT production ready in any way. 

ATTENTION!
Bad quality C++ code has been detected. Probably shoud've been written in the OOP style.

Prototype of the Tetris game fully written in C++


https://user-images.githubusercontent.com/71591558/142195671-18f01e50-2e0a-413d-8d5e-be76d784eaab.mp4


https://user-images.githubusercontent.com/71591558/142198992-6faa6fe8-f290-4d4c-bc74-7c2136b368e3.mp4


To compile this game you will need:

    1. (optional -> in Manjaro you can download it with pacman) SFML library from https://www.sfml-dev.org/download/sfml/2.5.1/
    
    2. make

After installing dependencies:

    1. open Terminal/CMD/Powershell
    
    2. edit Makefile if necessary
    
    3. run "make" command in root of the project
    
    4. it will produce a binary file name "tetris"

Now you are able to "play" tetris -> launch "tetris".

Hotkeys:
    1 - singleplayer mode
   
    2 - multiplayer mode on keyboard (left player - WASD, right player - arrows)
   
    3 - multiplayer mode through TCP socket connection (either of players use WASD)
   
    C - client mode
   
    S - server mode
   
    ESC - move to the previous screen or close the game
   
    Backspace - delete characters
   
    W - rotate to the right
   
    A - move to the left
   
    S - fall down faster
   
    D - move to the right
   
   Arrows - do the same thing as WASD
   
Rules:

        1. You lose 1 point for each new block
        
        2. You receive 10 points for each line

Goal:

        Your goal is to receive as many points as you can
  
P.S. When entering ip address of the server don't forget to add dots in correct places: 127.0.0.1 -> correct, 1270.0.1. -> incorrect, DO NOT DO THAT

P.P.S DO NOT forget that maximum value for the port is 65535
