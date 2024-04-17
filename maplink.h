#pragma once
#include "main.h"
#include "Coordinate.h"
#include "dlList.h"

class MapPoint;

typedef listNode<MapPoint> *pMapPointNode;

class MapLink {
private:

pMapPointNode point;
int distance;

public:

MapLink(pMapPointNode point ,int distance);

const char* getName();

const char getType();

const Coordinate getCoordinate();

pMapPointNode getPoint();

const int getDistance(){
    return distance;
}

void setDistance(int distance){
    this->distance = distance;
}

bool operator==(const Coordinate& coords);

bool operator==(const char* nameOther);

bool operator>=(const MapLink &link)
{
    return this->distance >= link.distance;
}

bool operator<=(const MapLink &link)
{
    return this->distance <= link.distance;
}

friend std::ostream &operator<<(std::ostream &out, MapLink *conn)
  {
    if (conn)
    {
      out << "MapLink:"
          << conn->getName();
      out << "Distance:"
          << conn->getDistance();
    }
    return out;
  }

};
