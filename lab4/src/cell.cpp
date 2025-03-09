//
// Created by matteo on 09/03/25.
//

#ifndef CELL_H
#define CELL_H

class Cell {
private:
    int length;
public:
    Cell(int length) : length(length) {}

    int getLength() const { return length; }

    void setLength(int length) { this->length = length; }

};

#endif //CELL_H
