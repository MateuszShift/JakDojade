#include "Coordinate.h"
#include "MapLink.h"
#include "MapPoint.h"

MapLink::MapLink(pMapPointNode point, int distance){
    this->point = point;
    this->distance = distance;
}

pMapPointNode MapLink::getPoint(){
    return this->point;
}

const char* MapLink::getName(){
    return this->point->data->getName();
}

const char MapLink::getType(){
    return this->point->data->getType();
}

const Coordinate MapLink::getCoordinate(){
    return this->point->data->getCoordinate();
}

bool MapLink::operator==(const Coordinate& coords){
    return this->point->data->getCoordinate() == coords;
}

bool MapLink::operator==(const char* nameOther){
    return strcmp(this->getName(), nameOther);
}
