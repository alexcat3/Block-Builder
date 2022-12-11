//
// Created by alexc on 12/6/2022.
//

#ifndef GLFW_TEST_BLOCKSELECTOR_H
#define GLFW_TEST_BLOCKSELECTOR_H

#include <memory>
#include "Rect2D.h"
#include "Block.h"

class BlockSelector {
    bool menuEnabled = false;
    const int menuNumCols;
    const int menuNumRows;
    const float menuColWidth;
    const float menuRowHeight;
    Rect2D menuBackgroundRect;
    int menuCursorCol, menuCursorRow;
    std::vector<Rect2D> blockChoiceRects;
    Texture menuCursorTexture;


    const int hotbarNumElements = menuNumCols;
    const float hotbarElementWidth = menuColWidth;
    const float hotbarHeight = menuRowHeight;
    Rect2D hotbarBackgroundRect;
    int hotbarSelectionCol=0;
    std::vector<std::unique_ptr<Block>> hotbarBlocks;
    std::vector<Rect2D> hotbarBlockRects;
    Texture hotbarCursorTexture;

public:
    BlockSelector();
    void draw();
    void processKbdInput(int key, int action);
    std::unique_ptr<Block> getSelectedBlock(glm::vec3 coords);
};


#endif //GLFW_TEST_BLOCKSELECTOR_H
