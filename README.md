Chess
==========

This is a repository for [CSE-20212] project **Chess**.

![alt text][logo]

[logo]: https://bytebucket.org/ktrinh1/chess/raw/c8eb2cac4c00bde455854f7f60607b80b741195b/pic.png?token=3f213f6eff6fd0cac3afa0c8d7eba2798d22f39a

**Members**:

* **Name**: Brian Byrne
* **NetID**: bbyrne5

* **Name**: David Mellitt
* **NetID**: dmellitt

* **Name**: Troy Prince
* **NetID**: tprince

* **Name**: Kevin Trinh
* **NetID**: ktrinh1

Implementation
--------

This game will include:

* Full Implementation of Chess (almost complete)
* AI (beginning)
* Graphics Utilizing SDL2 (done)

*This is currently a WIP.*

Documentation
--------

**Libraries:**
You will need **lib-sdl2**, **lib-sdl2-dev**, and **lib-sdl2-image**.

**How to Install:**
Download the git repository and type "make" in your terminal (you must have the above libraries).

**User Manual:**
After compiling the program, execute the *chess* file created. You will be prompted to input options for your game. After entering the options, an SDL2 window will appear. Simply click on the piece you want to move once it's your turn and click on one of the highlighted tiles that appear (indicating that you are able to move there). To exit the game, click on the terminal window and type Ctrl-C.

**Known bugs:**
- Screen dimming during the AI play
- Hard AI makes weird moves sometimes