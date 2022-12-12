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
* Camera movement
  * W and S keys move the camera in the X direction
  * A and D keys move the camera in the Z direction
  * Space and Left Shift keys move the camera in the Y direction
  * Q and E keys rotate the camera
* Cursor block movement
  * Arrow keys move the cursor block in the X and Z directions
  * Right Shift and Right Control keys move the cursor block in the Y direction
* Placing blocks
  * 1 key places a Cobblestone block at the cursor block's location
  * 2 key places a Granite block at the cursor block's location
  * 3 key places a Calcite block at the cursor block's location
  * 4 key places a Sandstone block at the cursor block's location
* Removing blocks
  * Backspace key removes the block from the cursor block's location
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