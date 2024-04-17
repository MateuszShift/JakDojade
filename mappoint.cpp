#include "main.h"
#include "FieldArea.h"
#include "MapGraph.h"
#include "MapPoint.h"

void MapPoint::addLink(pMapPointNode point, int distance){
    this->links->add(new MapLink(point,distance));
}

void MapPoint::updateLinks(MapGraph * mapGraph){
    listNode<MapLink>* mLink = this->links->head;

    while(mLink){
        MapLink * link = mLink->data;
        pMapPointNode childPoint = link->getPoint();

        if(!childPoint->data->used && (childPoint->data->distance > (this->distance + link->getDistance()))){
            childPoint->data->distance = this->distance + link->getDistance();
            childPoint->data->previous = this;

            mapGraph->sortPoint(childPoint);
        }

        mLink = mLink->next;
    }
}
