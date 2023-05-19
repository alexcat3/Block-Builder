## BlockBuilder
### By Sean Cunneen


### About BlockBuilder:
BlockBuilder is a very basic Minecraft clone, which allows you to build basic structures with blocks.

###Running BlockBuilder
At present, BlockBuilder only supports 64 bit Windows machines. To run the program, simply
download the archive download-windows.zip, which contains the program and the auxilliary files
(textures and DLLs) that it needs to run, extract and open it, enter the program folder, and launch BlockBuilder.exe.


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
  
###Recent Changes
* The program now saves the world to a file so you can pick up where you left off
* You rotate the camera and place blocks using the mouse instead of using the keyboard
* Instead of using official Minecraft textures, it uses textures from the open source PixelPerfectionCE texture pack
* There is an on-screen menu to select blocks
* There are more types of blocks
* It supports transparent blocks (glass + several colors of stained glass)
* It supports blocks with different images on different faces-- sandstone, crafting table, and furnace


### Citations 
The program uses the [GLFW graphics library](https://www.glfw.org/), the [GLAD driver library](https://glad.dav1d.de/), and the [stb_image library](https://github.com/nothings/stb). It uses textures from the [PixelPerfectionCE
texture pack](https://github.com/Athemis/PixelPerfectionCE)
