//
// Created by matteo on 19/03/25.
//

#include "../include/univers.h"

int main() {

    Univers univers1D(1, 10, 0.1);
    univers1D.showUnivers();


    univers1D.fillUnivers(1000);
    univers1D.showUnivers();

    return 0;
}