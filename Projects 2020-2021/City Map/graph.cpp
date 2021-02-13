#ifndef _GRAPH_CPP
#define _GRAPH_CPP

#include "graph.h"

template <class VertexType, class WeightType>
void Graph<VertexType, WeightType>::removeEdge(const VertexType &v1, const VertexType &v2) {
    weights.erase(std::make_pair(v1, v2));
    neighs[v1].erase(v2);
}

template <class VertexType, class WeightType>
void Graph<VertexType, WeightType>::addVertex(const VertexType &v) {
    vertices.insert(v);
    closed.insert(std::make_pair(v, false));
    neighs[v];
}

template <class VertexType, class WeightType>
void Graph<VertexType, WeightType>::addEdge(const VertexType &v1, const VertexType &v2, const WeightType &weight) {
    vertices.insert(v1);
    vertices.insert(v2);
    neighs[v1].insert(v2);
    weights[std::make_pair(v1, v2)] = weight;
}

template <class VertexType, class WeightType>
bool Graph<VertexType, WeightType>::hasVetrex(const VertexType &v) const {
    return vertices.count(v) == 1;
}

template <class VertexType, class WeightType>
bool Graph<VertexType, WeightType>::hasEdge(const VertexType &v1, const VertexType &v2) const {
    return vertices.count(v1) && neighs.at(v1).count(v2) == 1;
}

template <class VertexType, class WeightType>
WeightType Graph<VertexType, WeightType>::getEdge(const VertexType &v1, const VertexType &v2) const {
    if (!hasEdge(v1, v2)) {
        throw std::invalid_argument("* No edge present. *\n");
    }

    return weights.at(std::make_pair(v1, v2));
}

template <class VertexType, class WeightType>
void Graph<VertexType, WeightType>::printNeighboursTo(const VertexType &vertex) const {
    if (!hasVetrex(vertex)) {
        throw std::invalid_argument("* No such junction. *\n");
    }

    std::cout << "* The neighbours of " << vertex << " are: *\n";
    for (auto n : neighs.at(vertex)) {
        std::cout << " <> " << n << "\n";
    }
}

template <class VertexType, class WeightType>
void Graph<VertexType, WeightType>::open(const VertexType &v) {
    if (!hasVetrex(v)) {
        throw std::invalid_argument("* No such junction. *\n");
    }

    closed[v] = false;
    std::cout << "* " << v << " was successfully opened. *\n";
}

template <class VertexType, class WeightType>
void Graph<VertexType, WeightType>::close(const VertexType &v) {
    if (!hasVetrex(v)) {
        throw std::invalid_argument("* No such junction. *\n");
    }

    closed[v] = true;
    std::cout << "* " << v << " was successfully closed. *\n";
}

template <class VertexType, class WeightType>
void Graph<VertexType, WeightType>::printClosed() const {
    bool thereIsClosed = false;
    
    std::cout << "* The closed junctions are: *\n";
    for (auto v : closed) {
        if (closed.at(v.first)) {
            thereIsClosed = true;
            std::cout << " <> " << v.first << "\n";
        }
    }

    if (!thereIsClosed) {
        std::cout << " <> There are no closed junctions. \n";
    }
}

template <class VertexType, class WeightType>
void Graph<VertexType, WeightType>::deadEnds() const {
    std::cout << "* The dead end streets are: *\n";
    for (auto v : vertices) {
        if (outDegree(v) == 0 && inDegree(v) > 0) {
            for (auto n : vertices) {
                if (hasEdge(n, v)) {
                    std::cout << " <> " << n << " -> " << v << std::endl;
                }
            }
        }
    }
}

template <class VertexType, class WeightType>
int Graph<VertexType, WeightType>::inDegree(const VertexType &v) const {
    int inDegree = 0;
    for (const auto &in : vertices) {
        if (hasEdge(in, v)) {
            inDegree++;
        }
    }
    return inDegree;
}

template <class VertexType, class WeightType>
int Graph<VertexType, WeightType>::outDegree(const VertexType &v) const {
    return neighs.at(v).size();
}

template <class VertexType, class WeightType>
bool Graph<VertexType, WeightType>::sameDegree() const {
    for (auto v : vertices) {
        if (outDegree(v) != inDegree(v)) {
            return false;
        }
    }

    return true;
}

template <class VertexType, class WeightType>
void Graph<VertexType, WeightType>::DFSHelp(const VertexType &vertex, std::map<VertexType, bool> &visited) {
    std::stack<VertexType> traversal;
    traversal.push(vertex);

    while (!traversal.empty()) {
        VertexType current = traversal.top();
        traversal.pop();

        if (!visited[current] && !closed.at(current)) {
            visited[current] = true;
            
            for (auto n : neighs.at(current)) {
                if (!visited.at(n) && !closed.at(n)) {
                    traversal.push(n);
                }
            }
        }
    }
}

template <class VertexType, class WeightType>
Graph<VertexType, WeightType> Graph<VertexType, WeightType>::transposeGraph() {
    Graph<VertexType, WeightType> temp;
    for (auto v : vertices) {
        if (inDegree(v) == 0) {
            temp.addVertex(v);
        }
        for (auto n : neighs.at(v)) {
            temp.addVertex(n);
            try {
                temp.addEdge(n, v, getEdge(v, n));
            } 
            catch (const std::invalid_argument &ia) {
                std::cerr << ia.what();
            }
        }
    }
    return temp;
}

template <class VertexType, class WeightType>
bool Graph<VertexType, WeightType>::isStronglyConnected(const VertexType &vertex) {
    if (inDegree(vertex) == 0 && outDegree(vertex) == 0) {
        return false;
    }

    std::map<VertexType, bool> visited;

    for (auto v : vertices) {
        visited.insert(std::make_pair(v, false));
    }

    DFSHelp(vertex, visited);

    for (auto v : vertices) {
        if (outDegree(v) > 0 && !visited.at(v)) {
            return false;
        }
    }

    Graph transposed = transposeGraph();
    transposed.closed = closed;

    for (auto v : vertices) {
        visited[v] = false;
    }

    transposed.DFSHelp(vertex, visited);

    for (auto v : transposed.vertices) {
        if (transposed.outDegree(v) > 0 && !visited.at(v)) {
            return false;
        }
    }

    return true;
}

template <class VertexType, class WeightType>
void Graph<VertexType, WeightType>::printEulerianPathHelp(const VertexType &vertex) {
    Graph<VertexType, WeightType> temp = *this;

    std::stack<VertexType> currentPath;
    currentPath.push(vertex);

    std::vector<VertexType> circuit;

    VertexType currentVertex = vertex;

    while (!currentPath.empty()) {
        if (temp.outDegree(currentVertex)) {
            currentPath.push(currentVertex);

            VertexType nextVertex = *--temp.neighs[currentVertex].end();

            if (closed.at(nextVertex)) {
                std::cout << "* You cannot make a full Eulerian circuit starting from " << vertex << ". *\n";
                return;
            }

            temp.removeEdge(currentVertex, nextVertex);

            currentVertex = nextVertex;
        } 
        else {
            circuit.push_back(currentVertex);

            currentVertex = currentPath.top();
            currentPath.pop();
        }
    }

    std::cout << "* You can make a full Eulerian circuit starting from " << vertex << " by following this route: *\n <> ";
    for (int i = circuit.size() - 1; i > 0; i--) {
        std::cout << circuit[i] << " -> ";
    }
    std::cout << circuit[0] << std::endl;
}

template <class VertexType, class WeightType>
bool Graph<VertexType, WeightType>::EulerianPath(const VertexType &vertex) {
    if (!hasVetrex(vertex)) {
        throw std::invalid_argument("* No such vertex. *\n");
    }

    if (!isStronglyConnected(vertex) || !sameDegree() || closed.at(vertex)) {
        std::cout << "* You cannot make a full Eulerian circuit starting from " << vertex << ". *\n";
        return false;
    }

    printEulerianPathHelp(vertex);
    return true;
}

template <class VertexType, class WeightType>
bool Graph<VertexType, WeightType>::motherVertex(VertexType vertex) {
    if (!hasVetrex(vertex)) {
        throw std::invalid_argument("* No such junction. *\n");
    }

    if ((outDegree(vertex) == 0 && vertices.size() > 1) || closed.at(vertex)) {
        std::cout << "* There is not a path from " << vertex << " to all of the other junctions. *\n";
        return false;
    }

    std::map<VertexType, bool> visited;

    for (auto v : vertices) {
        visited.insert(std::make_pair(v, false));
    }

    DFSHelp(vertex, visited);

    for (auto v : vertices) {
        if (!visited.at(v)) {
            std::cout << "* There is not a path from " << vertex << " to all of the other junctions. *\n";
            return false;
        }
    }

    std::cout << "* There is a path from " << vertex << " to all of the other junctions. *\n";
    return true;
}

template <class VertexType, class WeightType>
void Graph<VertexType, WeightType>::printPath(const std::map<VertexType, VertexType> &prev, const VertexType &v) const {
    if (vertices.count(prev.at(v)) == 0) {
        std::cout << v;
        return;
    }

    printPath(prev, prev.at(v));
    std::cout << " -> " << v ;
}

template <class VertexType, class WeightType>
bool Graph<VertexType, WeightType>::foundPathFromToIter(const VertexType &from, const VertexType &to) {
    if (!hasVetrex(from) || !hasVetrex(to)) {
        throw std::invalid_argument("* No such vertex/vertices. *\n");
    }

    if (closed.at(from) || closed.at(to)) {
        std::cout << "* There is no path from " << from << " to " << to << ". *\n";
        return false;
    }

    std::stack<VertexType> traversal;
    traversal.push(from);

    std::map<VertexType, bool> visited;
    for (auto v : vertices) {
        visited.insert(std::make_pair(v, false));
    }
    visited[from] = true;

    std::map<VertexType, VertexType> prev;
    for (auto v : vertices) {
        prev.insert(std::make_pair(v, ""));
    }

    while (!traversal.empty()) {
        VertexType u = traversal.top();
        traversal.pop();

        if (u == to) {
            std::cout << "* The path from " << from << " to " << to << " is: *\n";
            std::cout << " <> ";
            printPath(prev, to);
            std::cout << std::endl;
            return true;
        }

        for (auto n : neighs.at(u)) {
            if (!visited.at(n) && !closed.at(n)) {
                traversal.push(n);
                visited[n] = true;
                prev[n] = u;
            }
        }
    }

    std::cout << "* There is no path from " << from << " to " << to << ". *\n";
    return false;
}

template <class VertexType, class WeightType>
bool Graph<VertexType, WeightType>::isCyclicIter(const VertexType &from) {
    if (!hasVetrex(from)) {
        throw std::invalid_argument("* No such vertex. *\n");
    }

    if (closed.at(from)) {
        std::cout << "* You cannot tour a part of the city and go back to where you started. *\n";
        return false;
    }

    std::stack<VertexType> traversal;
    traversal.push(from);

    std::map<VertexType, bool> visited;
    for (auto v : vertices) {
        visited.insert(std::make_pair(v, false));
    }
    visited[from] = true;

    std::map<VertexType, VertexType> prev;
    for (auto v : vertices) {
        prev.insert(std::make_pair(v, ""));
    }

    while (!traversal.empty()) {
        VertexType u = traversal.top();
        traversal.pop();

        for (auto n : neighs.at(u)) {
            if (!visited.at(n) && !closed.at(n)) {
                traversal.push(n);
                visited[n] = true;
                if (u != from) {
                    prev[n] = u;
                }
            } 
            else if (visited.at(n) && n == from && !closed.at(n)) {
                prev[from] = u;
                std::cout << "* You can tour a part of the city and go back to where you started by following this route: *\n";
                std::cout << " <> " << from << " -> ";
                printPath(prev, from);
                std::cout << std::endl;
                return true;
            }
        }
    }

    std::cout << "* You cannot tour a part of the city and go back to where you started. *\n";
    return false;
}

template <class VertexType, class WeightType>
void Graph<VertexType, WeightType>::allPathsHelp(const VertexType &from, const VertexType &to, std::map<VertexType, bool> &visited,
                                                 std::vector<VertexType> &path, std::vector<std::pair<std::vector<VertexType>, WeightType>> &allPaths) {
    visited[from] = true;

    path.push_back(from);

    if (from == to) {
        WeightType dist = 0;
        for (int i = 0; i < path.size() - 1; i++) {
            try {
                dist += getEdge(path[i], path[i + 1]);
            } 
            catch (const std::invalid_argument &ia) {
                std::cerr << ia.what();
            }
        }
        allPaths.push_back(std::make_pair(path, dist));
    } 
    else {
        for (auto n : neighs.at(from)) {
            if (!visited.at(n) && !closed.at(n)) {
                allPathsHelp(n, to, visited, path, allPaths);
            }
        }
    }

    path.pop_back();
    visited[from] = false;
}

template <class VertexType, class WeightType>
void Graph<VertexType, WeightType>::shortest(const VertexType &from, const VertexType &to) {
    if (!hasVetrex(from) || !hasVetrex(to)) {
        throw std::invalid_argument("* No such vertex/vertices. *");
    }

    if (closed.at(from) || closed.at(to)) {
        std::cout << "* There is no path from " << from << " to " << to << ". *\n";
        return;
    }

    std::map<VertexType, bool> visited;
    for (auto v : vertices) {
        visited.insert(std::make_pair(v, false));
    }

    std::vector<VertexType> path;

    std::vector<std::pair<std::vector<VertexType>, WeightType>> allPaths;

    allPathsHelp(from, to, visited, path, allPaths);

    if (allPaths.size() == 0) {
        std::cout << "* There is no path from " << from << " to " << to << ". *\n";
        return;
    }

    for (int i = 0; i < allPaths.size() - 1; i++) {
        for (int j = 0; j < allPaths.size() - i - 1; j++) {
            if (allPaths[j].second > allPaths[j + 1].second) {
                std::swap(allPaths[j], allPaths[j + 1]);
            }
        }
    }

    std::cout << "* The shortest paths are: *\n";

    int n = allPaths.size();
    if (n >= 3) {
        n = 3;
    }

    for (int i = 0; i < n; i++) {
        std::cout << " <> ";
        for (int j = 0; j < allPaths[i].first.size() - 1; j++) {
            std::cout << allPaths[i].first[j] << " -> ";
        }
        std::cout << allPaths[i].first[allPaths[i].first.size() - 1]<<"; Distance: " << allPaths[i].second << "\n";
    }
}

template <class VertexType, class WeightType>
void Graph<VertexType, WeightType>::printGraph() const {
    for (const auto &n : neighs) {
        std::cout << n.first << ": ";
        for (const auto &v : n.second) {
            std::cout << v << " ";
            try {
                std::cout << getEdge(n.first, v) << "; ";
            } 
            catch (const std::invalid_argument &ia) {
                std::cerr << ia.what();
            }
        }
        std::cout << std::endl;
    }
}

template <class VertexType, class WeightType>
void Graph<VertexType, WeightType>::drawGraph(std::ostream &out) {
    out << "digraph G{\n";
    for (const auto &v : vertices) {
        if (closed.at(v)) {
            out << v << "[color=\"red\"];\n";
        } 
        else {
            out << v << ";\n";
        }
    }
    for (const auto &n : neighs) {
        for (const auto &v : n.second) {
            out << n.first << "->" << v << "[label=\"" << getEdge(n.first, v) << "\"];\n";
        }
    }
    out << "}\n";
}

#endif
