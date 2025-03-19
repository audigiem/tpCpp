//
// Created by matteo on 19/03/25.
//

#include "../include/univers.h"

int main() {
    Univers univers2D(2, 10, 1);

    univers2D.showUnivers();


    univers2D.fillUnivers(10);
    univers2D.showUnivers();
    return 0;
}