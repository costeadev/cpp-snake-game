# Description
This is a snake game I did in C++. 
It uses `<termios.h>` for unbuffered/non-canonical stdin reading to provide "real time" WASD movement without having to press ENTER as in buffered stdin. And will probably just work in UNIX terminals.
The UI is just bare CLI, each frame is printed on top of the previous using cursor return.

# How to play
Use WASD to move the snake, eat the fruit which spawns, and well, it's the snake game lol.

# How to win
You just don't

# How to lose
You can lose multiple ways, colliding with your own body or with a wall.
