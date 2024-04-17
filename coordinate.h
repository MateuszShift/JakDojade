#pragma once
#include <iostream>

class Coordinate{

public:

int x;
int y;

Coordinate(){}

Coordinate(int x, int y){
    this->x = x;
    this->y = y;
}

bool operator==(const Coordinate& coord){
    return x == coord.x && y == coord.y;
}

};