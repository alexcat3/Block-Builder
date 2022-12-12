## Block Builder
### By Sean Cunneen

### Installation:
The libraries necessary to compile and run this program on a Windows machine are
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

### Future Work
  * Add ability to save creations
  * Add more different block textures to the game
  * Add support for transparent blocks
  * Make camera movement relative to the direction the camera faces, instead of in orthoganal directions
  * Use mouse to rotate the camera and place blocks
  * Add on-screen menus to select blocks
  * Add support for blocks with different textures on different faces
  * Add support for non-block-shaped objects like stairs
  * Add lighting and shadows to the world
  * Add objects that produce light
### Citations
  I relied heavily on the [Learn OpenGL Tutorial](https://learnopengl.com). Much of the code that directly manipulates graphics
  was copied from this tutorial, however, the class structure and main logic of the program are original. 
  
The program uses the GLFW graphics library, the GLAD driver library, and the stb_image library. It uses textures from the original
Minecraft game.

### Grade
#### Main Program
The main program uses many concepts from Module 4-- 3D graphics