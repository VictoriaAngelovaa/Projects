#ifndef _CITYMAP_HH
#define _CITYMAP_HH

#include "graph.h"
#include <string>
#include <fstream>
#include <vector>


template <class VertexType = std::string, class WeightType = int>
class CityMap {
    Graph<VertexType, WeightType> cityMap;
    VertexType currentJunction;

    public:
    /// creates the map by extracting the needed information - all junctions and streets - from the given file.
    bool createMap(const std::string &fileName, VertexType _currentJunction);

    void help() const;
    /// shows the current location i.e. the junction we are at.
    void location() const; 
    /// changes the current location.
    void change(const VertexType &newLocation);
    /// shows all adjacent junctions to the current junction.
    void neighbours() const;
    
    /// if there is a path from the current junction to the given one then the current junction is changed and set to the given one; otherwise the current location stays the same;
    /// it also shows the path between the two if there is one.
    void move(const VertexType &newLocation);
    /// finds the three (if possible) shortest paths between the current junction and the given one.
    void shortest(const VertexType &to);
    /// closes a junction so that it cannot be reached.
    void close(const VertexType &vertex);
    /// opens a junction so that it can be reached.
    void open(const VertexType &vertex);
    /// shows all of the closed junctions.
    void closed() const;
    /// shows all of the dead-end streets.
    void deadEnds() const;
    /// checks if there is a path from the current junction to all of the other junctions.
    void toAll();
    /// checks if it is possible to tour the city, starting from the current location, by passing through each street only once.
    void tour();
    /// checks if it is possible to tour a part of the city and go back to the start.
    void partialTour();
    /// visualizes the map
    void draw(const std::string &fileName);
    /// shows each junction, its neighbours and the distance between them.
    void printMap() const;

    void run();
};

#include "cityMap.cpp"

#endif
