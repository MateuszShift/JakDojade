#pragma once
#include <iostream>



class FieldArea{ //klasa dla tablicy obiektow mapy
//
public:
char type;
char* name;
int coordX;
int coordY;
//jeszcze lista

FieldArea(){
    this->type = '.';
    this->name = NULL;
    this->coordX = 0;
    this->coordY = 0;
}
~FieldArea(){}
};