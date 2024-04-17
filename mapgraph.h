#pragma once
#include "main.h"
#include "dlList.h"
#include "MapPoint.h"

class MapGraph
{ // lista w ktorej beda elementy z tablicy FieldArea

    int maxX;
    int maxY;
    int points;
    int cities;

    FieldArea **mapFieldArea;

    pMapPointNode *mapPointNodes;       // Tablica punktw mapy
    int *mapCityIndex;                  // Tablica indeksow nazw miast

    DoublyLinkedContainer<MapPoint> *mapPointsBuffer; // Graf dla mapy

    pMapPointNode getPointNode(const int x, const int y)
    {
        if ((x >= 0 && x < this->maxX) && (y >= 0 && y < this->maxY))
        {
            return this->mapPointNodes[x + (y * this->maxX)];
        }
        return NULL;
    }

    void addLinks()
    {
        for (int i = 0; i < (this->maxX * this->maxY); i++)
        {
            pMapPointNode mPoint = this->mapPointNodes[i];
            if (mPoint)
            {
                Coordinate coord = mPoint->data->getCoordinate();
                pMapPointNode newLink;
                newLink = this->findPoint(coord.x, coord.y - 1);
                if (newLink)
                {
                    mPoint->data->addLink(newLink);
                }
                newLink = this->findPoint(coord.x, coord.y + 1);
                if (newLink)
                {
                    mPoint->data->addLink(newLink);
                }
                newLink = this->findPoint(coord.x - 1, coord.y);
                if (newLink)
                {
                    mPoint->data->addLink(newLink);
                }
                newLink = this->findPoint(coord.x + 1, coord.y);
                if (newLink)
                {
                    mPoint->data->addLink(newLink);
                }
                mPoint = mPoint->next;
            }
        }
    }

public:
    MapGraph(FieldArea **area, int x, int y)
    {
        this->mapFieldArea = area;
        this->maxX = x;
        this->maxY = y;
        this->mapPointsBuffer = new DoublyLinkedContainer<MapPoint>();
        this->points = 0;
        this->mapPointNodes = new pMapPointNode[x * y];
        this->cities = 0;
        this->mapCityIndex = new int[x * y];

        this->build();
    }

    ~MapGraph()
    {
        delete this->mapPointsBuffer;
        for (int i = 0; i < (this->maxX * this->maxY); i++)
        {
            if (this->mapPointNodes[i])
            {
                delete this->mapPointNodes[i];
            }
        }
        delete this->mapPointNodes;
    }

    pMapPointNode newPointNode(char *name, char type, int coordX, int coordY)
    {
        MapPoint *point = new MapPoint(name, type, coordX, coordY);
        return new listNode<MapPoint>(point);
    }

    bool addLink(const char *startName, const char *endName, int distance)
    { // do lotnicznych
        pMapPointNode start = this->findPoint(startName);
        pMapPointNode end = this->findPoint(endName);

        if (start && end)
        {
            start->data->addLink(end, distance);
            return true;
        }
        return false;
    }

    void swpIndex(int i, int j)
    {
        int x = this->mapCityIndex[i];
        this->mapCityIndex[i] = this->mapCityIndex[j];
        this->mapCityIndex[j] = x;
    }

    int cmpIndex(int i, int j)
    {
        char *s1 = this->mapPointNodes[this->mapCityIndex[i]]->data->getName();
        char *s2 = this->mapPointNodes[this->mapCityIndex[j]]->data->getName();

        return strcmp(s1, s2);
    }

    int cmpIndex(int i, const char *name)
    {
        char *s1 = this->mapPointNodes[this->mapCityIndex[i]]->data->getName();

        return strcmp(s1, name);
    }

    // Sortowanie indexow nazw miast
    void sortIndex(int l, int r)
    {
        int i, j;

        i = l - 1;
        j = r;

        if (r <= l)
            return;

        for (;;)
        {
            while (this->cmpIndex(++i, r) < 0)
            {
            }

            while (this->cmpIndex(--j, r) >= 0)
            {
                if (j == l)
                    break;
            }

            if (i >= j)
                break;

            this->swpIndex(i, j);
        }

        this->swpIndex(i, r);

        this->sortIndex(l, i - 1);
        this->sortIndex(i + 1, r);
    }

    // Szukanie binarne indeksu nazwy miasta
    bool findIndex(int *i, int b, int e, const char *name)
    {
        int res;

        while (e >= b)
        {
            *i = (b + e) / 2;
            res = this->cmpIndex(*i, name);

            if (res == 0)
            {
                return true;
            }
            else
            {
                if (res < 0)
                {
                    b = (*i) + 1;
                }
                else
                {
                    e = (*i) - 1;
                };
            };
        }

        *i = b;

        return false;
    }

    void build()
    {
        for (int i = 0; i < this->maxY; i++)
        {
            for (int j = 0; j < this->maxX; j++)
            {
                FieldArea field = this->mapFieldArea[j][i];
                pMapPointNode pointNode = NULL;
                if (field.type != '.')
                {
                    pointNode = this->newPointNode(field.name, field.type, field.coordX, field.coordY);

                    if (field.type == '*')
                    {
                        this->mapCityIndex[this->cities] = j + (i * this->maxX);
                        this->cities++;
                    }
                    this->points++;
                }
                this->mapPointNodes[j + (i * this->maxX)] = pointNode;
            }
        }

        if (this->cities)
        {
            this->sortIndex(0, this->cities - 1);
        }

        this->addLinks();

        this->prepare();

        // std::cout << "Build: points " << this->points << " cities " << this->cities << std::endl;
    }

    void prepare()
    {
        this->mapPointsBuffer->clean();

        for (int i = 0; i < (this->maxX * this->maxY); i++)
        {
            pMapPointNode pointNode = this->mapPointNodes[i];
            if (pointNode)
            {
                this->mapPointsBuffer->put(pointNode);
                pointNode->data->clean();
            }
        }
    }

    pMapPointNode findPoint(const int x, const int y)
    {
        return this->getPointNode(x, y);
    }

    pMapPointNode findPoint(const char *conName)
    {
        if (conName && this->cities)
        {
            int i;
            if (this->findIndex(&i, 0, this->cities - 1, conName))
            {
                return this->mapPointNodes[this->mapCityIndex[i]];
            }
        }
        return NULL;
    }

    bool sortPoint(pMapPointNode pointNode)
    {
        if (pointNode)
        {
            this->mapPointsBuffer->putSorted(this->mapPointsBuffer->get(pointNode), true);
            return true;
        }
        return false;
    }

    pMapPointNode getPoint()
    {
        return this->mapPointsBuffer->head;
    }

    int findRoad(const char *startName, const char *endName)
    {
        // std::cout << "FindRoad: " << startName << " to " << endName << std::endl;

        this->prepare();

        pMapPointNode start = this->findPoint(startName);
        pMapPointNode end = this->findPoint(endName);
        int distance = INT_MAX;

        if (start && end)
        {
            pMapPointNode point;

            start->data->distance = 0;
            start->data->previous = start->data;

            this->sortPoint(start);

            while ((point = this->getPoint()) != NULL)
            {
                // std::cout << "Get: " << point << std::endl;

                point->data->used = true;
                this->mapPointsBuffer->get(point);

                if (point->data == end->data)
                {
                    // std::cout << "Road: Found" << std::endl;

                    distance = end->data->distance;
                    break;
                }

                point->data->updateLinks(this);
            }
        }

        return distance;
    }

    friend std::ostream &operator<<(std::ostream &out, const MapGraph *mainList)
    {
        out << "city name: " << mainList->mapPointsBuffer << "\n";
        return out;
    }
};
