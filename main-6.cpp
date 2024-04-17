#include "main.h"
#include "FieldArea.h"
#include "MapGraph.h"
#include "dlList.h"

#define DEBUG       0

#define NAME_SIZE   32

using namespace std;

template class listNode<MapPoint>;
template class DoublyLinkedList<MapPoint>;
template class DoublyLinkedContainer<MapPoint>;

template class listNode<MapLink>;
template class DoublyLinkedList<MapLink>;
template class DoublyLinkedContainer<MapLink>;

MapGraph *mapGraph;


char *StrDup(const char *str)
{
    if (str)
    {
        int len = std::strlen(str);
        char *out = (char *)malloc(len + 2);
        memset(out, 0, len + 2);
        if (len)
        {
            memcpy(out, str, len);
        }
        return out;
    }
    return NULL;
}

FieldArea **createFieldArea(int x, int y)
{
    FieldArea **mapArea = new FieldArea *[x];

    for (int i = 0; i < x; i++)
    {
        mapArea[i] = new FieldArea[y];
    }

    return mapArea;
} // stworzona tablica dynamiczna struktur elementow

FieldArea **addCityName(FieldArea **areaTab, int x, int y, int tempJIndex, int iValue, int jValue, int tempIIndex)
{
    int tempJ = tempJIndex;
    while (tempJ > 0 && areaTab[tempJ - 1][tempIIndex].type != '.' && areaTab[tempJ - 1][tempIIndex].type != '#')
    {
        tempJ--;
    }
    int indexTemp = 0;
    char *cityName = new char[indexTemp];
    // while(tempJ<x && areaTab[tempJ][tempIIndex].type != '.'){
    while (tempJ < x && (areaTab[tempJ][tempIIndex].type != '.' && areaTab[tempJ][tempIIndex].type != '#'))
    {
        char *tempTab = new char[indexTemp];
        for (int i = 0; i < indexTemp; i++)
        {
            tempTab[i] = cityName[i];
        }
        tempTab[indexTemp] = areaTab[tempJ][tempIIndex].type;
        areaTab[tempJ][tempIIndex].type = '.';
        tempJ++;
        indexTemp++;
        delete[] cityName;
        cityName = tempTab;
    }
    areaTab[jValue][iValue].name = new char[indexTemp + 1];
    memcpy(areaTab[jValue][iValue].name, cityName, indexTemp);
    areaTab[jValue][iValue].name[indexTemp] = 0;
    areaTab[jValue][iValue].coordX = jValue;
    areaTab[jValue][iValue].coordY = iValue;
    delete[] cityName;
    return areaTab;
}

FieldArea **fillFieldArea(FieldArea **area, int x, int y)
{
#if 0
    char line[x * 2];
    cin.getline(line, x * 2);
    for (int i = 0; i < y; i++)
    {
        cin.getline(line, x * 2);
        for (int j = 0; j < x; j++)
        {
            area[j][i].type = line[j];
        }
    }
#else
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            cin >> area[j][i].type;
        }
    }
#endif

    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            if (area[j][i].type == '*')
            {
                if (j > 0 && (area[j - 1][i].type != '.' && area[j - 1][i].type != '#' && area[j - 1][i].type != '*'))
                { // 1
                    int tempJ = j - 1;
                    while (area[tempJ - 1][i].type != '.' && area[tempJ - 1][i].type != '#' && tempJ > 0)
                    {
                        tempJ--;
                    }
                    int indexTemp = 0;
                    char *cityName = new char[indexTemp];
                    while (area[tempJ][i].type != '*')
                    {
                        char *tempTab = new char[indexTemp + 1];
                        for (int i = 0; i < indexTemp; i++)
                        {
                            tempTab[i] = cityName[i];
                        }
                        tempTab[indexTemp] = area[tempJ][i].type;
                        area[tempJ][i].type = '.'; // to nie musi byc zmieniane ale moze
                        tempJ++;
                        indexTemp++;
                        delete[] cityName;
                        cityName = tempTab;
                    }
                    area[tempJ][i].name = new char[indexTemp + 1];
                    memcpy(area[tempJ][i].name, cityName, indexTemp);
                    area[tempJ][i].name[indexTemp] = 0;
                    area[tempJ][i].coordX = j;
                    area[tempJ][i].coordY = i;
                    delete[] cityName;
                }
                else if (j > 0 && i > 0 && (area[j - 1][i - 1].type != '.' && area[j - 1][i - 1].type != '#'))
                { // 2
                    addCityName(area, x, y, j - 1, i, j, i - 1);
                }
                else if (i > 0 && (area[j][i - 1].type != '#' && area[j][i - 1].type != '.'))
                { // 3
                    addCityName(area, x, y, j, i, j, i - 1);
                }
                else if (j < x - 1 && i > 0 && (area[j + 1][i - 1].type != '#' && area[j + 1][i - 1].type != '.'))
                { // 4
                    addCityName(area, x, y, j + 1, i, j, i - 1);
                }
                else if (j < x - 1 && (area[j + 1][i].type != '#' && area[j + 1][i].type != '.'))
                { // 5
                    int tempJ = j + 1;
                    int indexTemp = 0;
                    char *cityName = new char[indexTemp];
                    while (tempJ < x && area[tempJ][i].type != '.')
                    {
                        char *tempTab = new char[indexTemp];
                        for (int i = 0; i < indexTemp; i++)
                        {
                            tempTab[i] = cityName[i];
                        }
                        tempTab[indexTemp] = area[tempJ][i].type;
                        area[tempJ][i].type = '.'; // to nie musi byc zmieniane ale moze
                        tempJ++;
                        indexTemp++;
                        delete[] cityName;
                        cityName = tempTab;
                    }
                    area[j][i].name = new char[indexTemp + 1];
                    memcpy(area[j][i].name, cityName, indexTemp);
                    area[j][i].name[indexTemp] = 0;
                    area[j][i].coordX = j;
                    area[j][i].coordY = i;
                    delete[] cityName;
                }
                else if (j < x - 1 && i < y - 1 && (area[j + 1][i + 1].type != '#' && area[j + 1][i + 1].type != '.'))
                { // 6
                    addCityName(area, x, y, j + 1, i, j, i + 1);
                }
                else if (i < y - 1 && (area[j][i + 1].type != '#' && area[j][i + 1].type != '.'))
                { // 7
                    addCityName(area, x, y, j, i, j, i + 1);
                }
                else if (j > 0 && i < y - 1 && (area[j - 1][i + 1].type != '#' && area[j - 1][i + 1].type != '.'))
                { // 8
                    addCityName(area, x, y, j - 1, i, j, i + 1);
                }
            }
            else if (area[j][i].type == '#')
            {
                area[j][i].coordX = j;
                area[j][i].coordY = i;
            }
        }
    }
    return area;
}

void parseFlights()
{
    char startCity[NAME_SIZE];
    char endCity[NAME_SIZE];
    int dist;
    cin >> startCity >> endCity >> dist;

    mapGraph->addLink(startCity, endCity, dist);
}

void parseJourney()
{
    int mode;
    char startCity[NAME_SIZE];
    char endCity[NAME_SIZE];

    cin >> startCity >> endCity >> mode;

    if (mode == 0)
    {
        int dist = mapGraph->findRoad(startCity, endCity);
        cout << dist << endl;
    }
    if (mode == 1)
    {
        int dist = mapGraph->findRoad(startCity, endCity);
        cout << dist << " ";
        pMapPointNode pEnd = mapGraph->findPoint(endCity);
        MapPoint *end = pEnd ? pEnd->data : NULL;

        DoublyLinkedList<MapPoint> *cities = new DoublyLinkedList<MapPoint>();

        while (end)
        {
            if (end->getName())
            {
                cities->add(end);
            }
            if (end == end->previous)
            {
                break;
            }
            end = end->previous;
        }
        listNode<MapPoint> *node = cities->tail;

        while (node)
        {
            if (node != cities->tail && node != cities->head)
            {
                if ( strcmp(node->data->getName(), "WARSZAWA") != 0 )
                {
                    cout << node->data->getName() << " ";
                }
            }
            node = node->previous;
        }

        cout << endl;

        delete cities;
    }
}

int main()
{
#if defined(__APPLE__) && DEBUG
    size_t ts = tp;
#endif

    int x, y;
    cin >> x >> y;

    FieldArea **mapArea = createFieldArea(x, y);
    fillFieldArea(mapArea, x, y);

    mapGraph = new MapGraph(mapArea, x, y);

    int airLinks;
    cin >> airLinks;

    for (int i = 0; i < airLinks; i++)
    {
        parseFlights();
    }

    int journeys;
    cin >> journeys;

    for (int i = 0; i < journeys; i++)
    {
        parseJourney();
    }

    return 0;
}
