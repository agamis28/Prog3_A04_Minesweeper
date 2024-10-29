#include "box.h"

    // Box Constructor 
    // Initalizing variable memebers
    Box::Box(float boxSize, BoxType boxType , int numberOfAdjacentMines)
        : boxSize{ boxSize }, boxType{ boxType }, numberOfAdjacentMines{ numberOfAdjacentMines }, flagged{ false }, revealed{ false }{
        if (numberOfAdjacentMines == 0) {
            boxType = Empty;
        }
    }

    void Box::display() {

    }
