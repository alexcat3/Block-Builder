//
// Created by alexc on 12/6/2022.
//

#include "BlockSelector.h"
#include "Block.h"
#include "CubeIdenticalFace.h"
BlockSelector::BlockSelector():
    menuNumCols(8),
    menuNumRows(8),
    menuColWidth(2.0/(menuNumCols+2)),
    menuRowHeight(2.0/(menuNumRows+3)),
    hotbarSelectionCol(1),
    hotbarNumElements(menuNumCols),
    hotbarElementWidth(menuColWidth),

    menuBackgroundRect(-1 + menuColWidth, 1-menuRowHeight, -1 + menuColWidth*(1+8), 1 - menuRowHeight*(1+8), -.99, Texture("../textures/menu_background.png", {})),
    hotbarBackgroundRect(-1+hotbarElementWidth, -1+hotbarHeight, -1+hotbarElementWidth*(1+hotbarNumElements), -1, -.99, Texture("../textures/hotbar_background.png", {}))
    {
    menuCursorCol = 0;
    menuCursorRow = 0;

    //Fill blockChoiceRects with rectangles textured with the side faces of all blocks, in a grid pattern in the bounds of the menu
    for(int i=0; i<Block::blockTypes.size(); i+=8){
        for(int j=i; j+i < Block::blockTypes.size() && j<8; j++) {
            if (Block::blockTypes[i + j] != nullptr) {
                blockChoiceRects.push_back(
                        Rect2D(-.8f + .2 * j + .02, .8 - .2 * i - .02, -.8 + .2 * j + .18, .8 - .2 * i - .18,
                               -1, Block::blockTypes[i + j]->getFlatTexture()));
            }
        }
    }

    hotbarBlocks = std::vector<std::unique_ptr<Block>>(hotbarNumElements);
    for(int i=0; i<hotbarNumElements; i++){
        hotbarBlockRects.push_back(Rect2D(-1+hotbarElementWidth*(1+i+.2), -1+hotbarHeight*.8, -1+hotbarElementWidth*(2+i-.2), -1+hotbarHeight*.2,-1,
                                          Texture("../textures/hotbar_background.png", {})));
    }

}

void BlockSelector::processKbdInput(int key, int action) {
    if(key <= GLFW_KEY_1 && key >= GLFW_KEY_8 && action == GLFW_PRESS){
        hotbarSelectionCol = key - GLFW_KEY_0;
    }
    else if(key == GLFW_KEY_E && action == GLFW_PRESS){
        menuEnabled = !menuEnabled;
    }

    if(key == GLFW_KEY_RIGHT && menuCursorCol < menuNumCols) menuCursorCol++;
    if(key == GLFW_KEY_LEFT && menuCursorCol > 1) menuCursorCol--;
    if(key == GLFW_KEY_UP && menuCursorRow > 1) menuCursorRow--;
    if(key == GLFW_KEY_DOWN && menuCursorRow < menuNumRows) menuCursorRow++;
}

void BlockSelector::draw(){
    hotbarBackgroundRect.draw();
    for(Rect2D &r:hotbarBlockRects){
        r.draw();
    }

    if(menuEnabled) {
        Rect2D menuCursor(-1 + menuColWidth*(menuCursorRow), 1-menuRowHeight*(menuCursorCol-1),
                          -1 + menuColWidth*(menuCursorRow+1), 1-menuRowHeight*(menuCursorCol-2),
                          -.995, Texture("menu_cursor.png",{}));
        menuBackgroundRect.draw();
        for (Rect2D &r: blockChoiceRects) {
            r.draw();
        }
    }
}

std::unique_ptr<Block> BlockSelector::getSelectedBlock(glm::vec3 coords){
    if(1 <= hotbarSelectionCol && hotbarSelectionCol <=4)
    return Block::newBlock(hotbarSelectionCol,coords);
}
