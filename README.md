## Final Project: Block Builder
### By Sean Cunneen

### Installation:
The libraries necessary to compile and run this program on a 64-bit Windows machine are
present in this repository. One can simply open the repository in CLion and press
the run button. If you have a mac or linux machine, I suggest that you use Virtual Votey
to run the program.

### About Block Builder:
Block Builder is a very basic Minecraft clone. It allows you to build structures 
using 4 types of blocks. Instead of placing blocks using the mouse, you use a cursor
block which you can move around the world, overlapping other blocks and placing blocks
at its location.
### Controls:
* Camera
  * The mouse rotates the camera
  * The W A S D keys move the camera forward, left, right, and back
  * The space and left shift keys move the camera up and down
* Hotbar
  * The hotbar holds 8 types of blocks. At the beginning of the game it is empty.
  * To select a spot in the hotbar, use the number keys 1-8
* Menu
  * The menu allows you to put blocks in the hotbar
  * To enter or exit the menu, press E
  * The selected block in the menu is highlighted in blue. To change which block is selected, use the arrow keys
  * To put the selected block in the selected spot in the hotbar, press ENTER
* Placing/Removing Blocks
  * You choose a location at which to place or remove a block by looking at it with the camera.
  * The blue cursor block appears to show you where a block will be placed or removed
  * To place the type of block that is selected in the hotbar, left click
  * To remove a block from behind the cursor block, right click
* Exiting
  * To leave the game, press ESCAPE. Your work will automatically be saved.
  
###Changes (Since submitted as M4OEP)
* The program now saves the world to a file so you can pick up where you left off
* You rotate the camera and place blocks using the mouse instead of using the keyboard
* Instead of using some official Minecraft textures, it uses some textures from the open source PixelPerfectionCE texture pack
* There is an on-screen menu to select blocks
* There are more types of blocks
* It supports transparent blocks (glass + several colors of stained glass)
* It supports blocks with different images on different faces-- sandstone, crafting table, and furnace

### Concepts Used
* 3D graphics using OpenGL-- from module 4
* Inheritance and composition from module 2
  * I.E. the ScreenObject class contains instances of Texture and VertexArray (Composition). The Block class extends ScreenObject and CubeIdenticalFace and Cube4Face extend Block (Inheritance).

### Citations
  I relied heavily on the [Learn OpenGL Tutorial](https://learnopengl.com). Much of the code that directly manipulates graphics
  was copied from this tutorial, however, the class structure and main logic of the program are original. 
  
The program uses the [GLFW graphics library](https://www.glfw.org/), the [GLAD driver library](https://glad.dav1d.de/), and the [stb_image library](https://github.com/nothings/stb). It uses textures from the [PixelPerfectionCE
texture pack](https://github.com/Athemis/PixelPerfectionCE)

### Grade
#### Design
The program uses concepts from two different models, accepts user input (mouse/keyboard controls) and validates it (it will not let you place a block beyond the boundary of the world)
and has visual elements (the entire game), Therefore it satisfies  the requirements  
ALl requirements are included in ways that make sense. The documentation is fairly robust-- the README clearly explains the controls and header files are commented
40/40

#### Execution
The program uses concepts from two different models, accepts user input (mouse/keyboard controls) and validates it (it
will not let you place a block beyond the boundary of the world) has visual elements (the entire game),
tests most but perhaps not all appropriate non-trivial class methods (many methods could not be tested because they only
affect what is outputted to the screen, but I might have missed one or two methods that could be tested),
and has all required sections in the README. Therefore it satisfies most the requirements, but perhaps not completely 
the testing one. The program has no known bugs, and the documentation is pretty good.
40/50

#### Usability
The controls are simple and are explained in the README file. It is interactive, validates inputs (it does not let you
place a block beyond the boundary of the world) and the output is clear. As a clone of a very successful computer game
the concept is pretty interesting. 
25/25

#### Complexity
While the program itself is pretty complex, it was built on code from my last Open Ended Project and I'm not sure I added
quite enough new stuff.
40/50

#### Effort
The fully 3D graphics of the program do give a "WOW" factor, however I only spent a week on the additions to the
program for the final project.
10/25

#### TOTAL:
155/200