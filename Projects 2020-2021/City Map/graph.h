#ifndef _GRAPH_HH
#define _GRAPH_HH

#include <iostream>
#include <fstream>
#include <functional>
#include <map>
#include <set>
#include <stack>
#include <exception>
#include <vector>
#include <string>


/// Implementation of a weighted directed graph
template <class VertexType = std::string, class WeightType = int>
class Graph { 
    using EdgeType = std::pair<VertexType, VertexType>;
    using NeighboursType = std::set<VertexType>;

    /// a container that stores all vertices of the graph; due to the fact that all vertices are unique (i.e. there cannot be more than one occurence of each vertex in the graph) the container is a set.
    std::set<VertexType> vertices; 
    /// a container that stores the neighbours of each vertex; each vertex has its own set of neighbours.
    std::map<VertexType, NeighboursType> neighs; 
    /// a container that stores the weights of all edges (an edge connects two vertices in a graph).
    std::map<EdgeType, WeightType> weights; 
    /// a container that shows if a given vertex is closed i.e. cannot be reached from any other vertex (cannot be discovered); all vertices are open at the beginning.
    std::map<VertexType, bool> closed; 

    /// this method is used to remove the edge (the connection) from v1 (start vertex) to v2 (end vertex).
    void removeEdge(const VertexType &v1, const VertexType &v2); 

    public:
    /// adds a vertex to the graph.
    void addVertex(const VertexType &v); 
    /// adds an edge between the two given vertices and sets its weight.
    void addEdge(const VertexType &v1, const VertexType &v2, const WeightType &weight); 

    /// checks if there is such vertex in the graph.
    bool hasVetrex(const VertexType &v) const; 
    /// checks if there is such edge (if the two given vertices are connected) in the graph.
    bool hasEdge(const VertexType &v1, const VertexType &v2) const; 

    /// returns the weight of the edge between the two given vertices.
    WeightType getEdge(const VertexType &v1, const VertexType &v2) const; 

    /// shows all adjacent vertices to (all vertices that can be reached directly from) the given vertex.
    void printNeighboursTo(const VertexType &vertex) const; 

    /// opens a vertex so that it can be discovered (reached).
    void open(const VertexType &v); 
    /// closes a vertex so that it cannot be discovered (reached).
    void close(const VertexType &v); 
    /// shows all closed vertices.
    void printClosed() const; 

    /// a dead end is a vertex from which no exit is possible (no other vertex cannot be reached from it); this method shows all of the dead ends in the graph.
    void deadEnds() const; 

    /// calculates the number of vertices to which the given vertex is adjacent.
    int inDegree(const VertexType &v) const; 
    /// calculates the number of vertices that are adjacent to the given vertex.
    int outDegree(const VertexType &v) const; 
    /// checks if each vertex of the graph has the same in and out degree.
    bool sameDegree() const; 

    /// depth-first search - an algorithm for traversing a graph.
    void DFSHelp(const VertexType &vertex, std::map<VertexType, bool> &visited); 

    /// creates a transposed (reversed) graph - the direction of each edge is reversed.
    Graph transposeGraph(); 
    /// checks if the graph is strongly connected; a graph is said to be strongly connected if every vertex (with nonzero degree) is reachable from every other vertex (with nonzero degree).
    /// the method is based on Kosaraju's algorithm.
    bool isStronglyConnected(const VertexType &vertex); 
    /// prints the Eulerian path from the given vertex; the method is based on Hierholzer's algorithm.                                                    
    void printEulerianPathHelp(const VertexType &vertex); 
    /// checks if there is an Eulerian path from the given vertex; the Eulerian path is a trail in a graph that visits every edge exactly once (allowing for revisiting vertices).
    bool EulerianPath(const VertexType &vertex); 

    /// checks if the given vertex is a mother vertex; a mother vertex in a graph is a vertex v such that all other vertices in the graph can be reached by a path from v.
    bool motherVertex(VertexType vertex); 

    /// helper method for printing a path
    void printPath(const std::map<VertexType, VertexType> &prev, const VertexType &v) const; 
    /// checks if there is a path between the given vertices (if the second vertex can be reached by a path from the first); the method is based on dfs.
    bool foundPathFromToIter(const VertexType &from, const VertexType &to); 
    /// checks if there is a cycle from the given vertex; a directed circuit is a non-empty directed trail in which the first vertex is equal to the last vertex.
    bool isCyclicIter(const VertexType &from); 

    /// finds all paths (with the corresponding distanceс) between the two given vertices; the method is based on dfs.
    void allPathsHelp(const VertexType &from, const VertexType &to, std::map<VertexType, bool> &visited,
                      std::vector<VertexType> &path, std::vector<std::pair<std::vector<VertexType>, WeightType>> &allPaths); 
    ///shows the three (if possible) shortest paths between the two given verices; 
    void shortest(const VertexType &from, const VertexType &to); 

    /// prints each vertex and its neoghbours.
    void printGraph() const; 
    /// visualizes the graph.
    void drawGraph(std::ostream &out); 
};

#include "graph.cpp"

#endif

