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
    menuCursorTexture("../textures/menu_cursor.png",{}),
    hotbarSelectionCol(1),
    hotbarNumElements(menuNumCols),
    hotbarElementWidth(menuColWidth),
    hotbarBlocks(8),
    hotbarCursorTexture("../textures/hotbar_cursor.png",{}),

    menuBackgroundRect(-1 + menuColWidth, 1-menuRowHeight, -1 + menuColWidth*(1+8), 1 - menuRowHeight*(1+8), -.99, Texture("../textures/menu_background.png", {})),
    hotbarBackgroundRect(-1+hotbarElementWidth, -1+hotbarHeight, -1+hotbarElementWidth*(1+hotbarNumElements), -1, -.99, Texture("../textures/hotbar_background.png", {}))
    {
    menuCursorCol = 1;
    menuCursorRow = 1;


    //Fill blockChoiceRects with rectangles textured with the side faces of all blocks, in a grid pattern in the bounds of the menu
    for(int i=0; i<Block::blockTypes.size(); i+=8){
        for(int j=0; j+i < Block::blockTypes.size() && j<8; j++) {
            if (Block::blockTypes[i + j] != nullptr) {
                blockChoiceRects.push_back(
                        Rect2D(-1+menuColWidth*(1+j+.2), 1-menuRowHeight*(1+i/8+.2),
                               -1+menuColWidth*(1+j+.8), 1-menuRowHeight*(1+i/8+.8),
                               -1, Block::blockTypes[i + j]->getFlatTexture()));
            }
        }
    }

    hotbarBlocks = std::vector<std::unique_ptr<Block>>(hotbarNumElements);
    Texture hotbarBackground("../textures/hotbar_background.png", {});
    for(int i=0; i<hotbarNumElements; i++){
        hotbarBlockRects.push_back(Rect2D(-1+hotbarElementWidth*(1+i+.2), -1+hotbarHeight*.8, -1+hotbarElementWidth*(2+i-.2), -1+hotbarHeight*.2,-1,
                                          hotbarBackground));
    }

}

void BlockSelector::processKbdInput(int key, int action) {
    if(key >= GLFW_KEY_1 && key <= GLFW_KEY_8 && action == GLFW_PRESS){
        hotbarSelectionCol = key - GLFW_KEY_0;
    }
    else if(key == GLFW_KEY_E && action == GLFW_PRESS){
        menuEnabled = !menuEnabled;
    }

    if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS && menuCursorCol < menuNumCols) menuCursorCol++;
    if(key == GLFW_KEY_LEFT && action == GLFW_PRESS && menuCursorCol > 1) menuCursorCol--;
    if(key == GLFW_KEY_UP && action == GLFW_PRESS && menuCursorRow > 1) menuCursorRow--;
    if(key == GLFW_KEY_DOWN && action == GLFW_PRESS && menuCursorRow < menuNumRows) menuCursorRow++;

    if(menuEnabled && key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
        int blockId = (menuCursorCol-1)+8*(menuCursorRow-1);
        std::unique_ptr<Block> block = Block::newBlock(blockId, glm::vec3(0,0,0));
        if(block){
            std::cout<<"Exchanged block"<<std::endl;
            hotbarBlockRects[hotbarSelectionCol-1].setTexture(block->getFlatTexture());
            hotbarBlocks[hotbarSelectionCol-1] = std::move(block);
        }else{
            std::cout<<blockId<<" is Not a real block!"<<std::endl;
        }
    }
}


void BlockSelector::draw(){


    hotbarBackgroundRect.draw();
    for(Rect2D &r:hotbarBlockRects){
        r.draw();
    }
    Rect2D hotbarCursor(-1+hotbarElementWidth*hotbarSelectionCol, -1+hotbarHeight, -1+hotbarElementWidth*(hotbarSelectionCol+1),-1,
        -.995, hotbarCursorTexture);
    hotbarCursor.draw();

    if(menuEnabled) {
        Rect2D menuCursor(-1 + menuColWidth*(menuCursorCol), 1-menuRowHeight*(menuCursorRow),
                          -1 + menuColWidth*(menuCursorCol+1), 1-menuRowHeight*(menuCursorRow+1),
                          -.995, menuCursorTexture);
        menuBackgroundRect.draw();
        menuCursor.draw();
        for (Rect2D &r: blockChoiceRects) {
            r.draw();
        }
    }
}

std::unique_ptr<Block> BlockSelector::getSelectedBlock(glm::vec3 coords){
    if(hotbarBlocks[hotbarSelectionCol-1]) {
        return Block::newBlock(hotbarBlocks[hotbarSelectionCol - 1]->getId(), coords);
    }
    return nullptr;
}
