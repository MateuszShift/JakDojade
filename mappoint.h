#pragma once
#include "main.h"
#include "dlList.h"
#include "MapLink.h"
#include "Coordinate.h"

class MapGraph;

class MapPoint
{
private:
    char type;
    char *name;
    Coordinate coordinate;
    DoublyLinkedList<MapLink> *links;

public:
    int distance;
    MapPoint *previous;
    bool used;

    MapPoint(char *name, char type, int coordX, int coordY)
    {
        this->name = StrDup(name);
        this->type = type;
        this->coordinate.x = coordX;
        this->coordinate.y = coordY;
        this->links = new DoublyLinkedList<MapLink>();
        this->clean();
    }

    ~MapPoint()
    {
        free(name);
    }

    void clean()
    {
        this->distance = INT_MAX;
        this->used = false;
        this->previous = NULL;
    }

    char getType()
    {
        return type;
    }

    char *getName()
    {
        return name;
    }

    Coordinate getCoordinate()
    {
        return coordinate;
    }

    bool operator==(const Coordinate &coords)
    {
        return coordinate == coords;
    }

    bool operator==(const MapPoint &node)
    {
        return false;
    }

    bool operator==(const int node)
    {
        return false;
    }

    bool operator==(const char *node)
    {
        if (!name)
        {
            return false;
        }
        return strcmp(name, node) == 0;
    }

    bool operator>=(const MapPoint &node)
    {
        return this->distance >= node.distance;
    }

    bool operator<=(const MapPoint &node)
    {
        return this->distance <= node.distance;
    }

    void addLink(pMapPointNode point, int distance = 1);

    void updateLinks(MapGraph *mapGraph);

    friend std::ostream &operator<<(std::ostream &out, const MapPoint *point)
    {
        if (point)
        {
            out << "Point: " << point->type << " " << &(point->coordinate) << " Dist: " << point->distance;
            if(point->name)
            {
                out << " City: " << point->name;
            }
        }
        return out;
    }
};
