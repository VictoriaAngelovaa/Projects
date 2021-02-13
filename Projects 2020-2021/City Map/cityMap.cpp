#ifndef _CITYMAP_CPP
#define _CITYMAP_CPP

#include "cityMap.h"

void printMessage(const int &num) {
    if (num == 0) {
        std::cout << "**************************************************************************************" << std::endl;
        std::cout << "*     Before you start, please open the file containing the needed information.      *" << std::endl;
        std::cout << "*      <> use the following command - openMap <file> <current location>              *" << std::endl;
        std::cout << "**************************************************************************************" << std::endl;
    } 
    else if (num == 1) {
        std::cout << std::endl;
        std::cout << "**************************************************************************************" << std::endl;
        std::cout << "*                         What would you like to do next:                            *" << std::endl;
        std::cout << "**************************************************************************************" << std::endl;
        std::cout << std::endl;
    }
}

void splitIntoWords(const std::string &info, std::vector<std::string> &words) {
    std::string word;
    for (int i = 0; i < info.size(); i++) {
        if (info[i] == ' ') {
            i++;
            words.push_back(word);
            word.clear();
        }
        word.push_back(info[i]);
    }
    words.push_back(word);
}

template <class VertexType, class WeightType>
bool CityMap<VertexType, WeightType>::createMap(const std::string &fileName, VertexType _currentJunction) {
    std::ifstream file(fileName.c_str(), std::ios::in);
    if (!file) {
        std::cout << "* There is no such file. In order to create the map you have to give a valid filename. *\n";
        return false;
    }

    while (!file.eof()) {
        std::vector<std::string> mapInfo;
        std::string line;

        getline(file, line);
        splitIntoWords(line, mapInfo);

        cityMap.addVertex(mapInfo[0]);

        for (int i = 1; i < mapInfo.size() - 1; i += 2) {
            cityMap.addVertex(mapInfo[i]);
            cityMap.addEdge(mapInfo[0], mapInfo[i], std::stoi(mapInfo[i + 1]));
        }
    }
    file.close();

    while (!cityMap.hasVetrex(_currentJunction)) {
        std::cout << "* The location you have provided is not on the map. Please chose another one: *\n";
        std::cin >> _currentJunction;
    }

    currentJunction = _currentJunction;

    std::cout << "* You have successfully provided the needed information. *\n";
    return true;
}

template <class VertexType, class WeightType>
void CityMap<VertexType, WeightType>::help() const {
    std::cout << "\n* The following commands are supported: *\n";
    std::cout << "    <> help - prints this information\n";
    std::cout << "    <> exit - exits\n";
    std::cout << "    <> location - shows the current location\n";
    std::cout << "    <> change @ - changes the current location and sets it to @\n";
    std::cout << "    <> neighbours - shows all adjacent junctions to the current junction\n";
    std::cout << "    <> move @ - if there is a path from the current juncion to @ then changes the current location, sets it to @\n";
    std::cout << "                and prints the actual path; otherwise the current location stays the same\n";
    std::cout << "    <> shortest @ - shows the shortest paths from the currento location to @\n";
    std::cout << "    <> close @ - closes the junction @\n";
    std::cout << "    <> open @ - opens the junction @\n";
    std::cout << "    <> closed - shows all closed junctions\n";
    std::cout << "    <> deadEnds - shows all dead end streets\n";
    std::cout << "    <> toAll - checks if there is a path from the current junction to all of the other junctions\n";
    std::cout << "    <> tour - checks if it is possible to tour the city, starting from the current location,\n              by passing through each street only once\n";
    std::cout << "    <> partialTour - checks if it is possible to tour a part of the city and go back to the start\n";
    std::cout << "    <> draw @.dot - draws the graph in the file @.dot\n";
    std::cout << "    <> printMap - shows each junction, its neighbours and the distance between them\n";
}

template <class VertexType, class WeightType>
void CityMap<VertexType, WeightType>::location() const {
    std::cout << "* Current location: " << currentJunction << " *\n";
}

template <class VertexType, class WeightType>
void CityMap<VertexType, WeightType>::change(const VertexType &newLocation) {
    if (!cityMap.hasVetrex(newLocation)) {
        std::cout << "* No such junction. *\n";
        return;
    }

    currentJunction = newLocation;
    std::cout << "* The current location was successfully set to " << newLocation << " *\n";
}

template <class VertexType, class WeightType>
void CityMap<VertexType, WeightType>::neighbours() const {
    try {
        cityMap.printNeighboursTo(currentJunction);
    } 
    catch (const std::invalid_argument &ia) {
        std::cerr << ia.what();
    }
}

template <class VertexType, class WeightType>
void CityMap<VertexType, WeightType>::move(const VertexType &newLocation) {
    try {
        if (cityMap.foundPathFromToIter(currentJunction, newLocation)) {
            currentJunction = newLocation;
        }
    } 
    catch (const std::invalid_argument &ia) {
        std::cerr << ia.what();
    }
}

template <class VertexType, class WeightType>
void CityMap<VertexType, WeightType>::shortest(const VertexType &to) {
    try {
        cityMap.shortest(currentJunction, to);
    } 
    catch (const std::invalid_argument &ia) {
        std::cerr << ia.what();
    }
}

template <class VertexType, class WeightType>
void CityMap<VertexType, WeightType>::close(const VertexType &vertex) {
    try {
        cityMap.close(vertex);
    } 
    catch (const std::invalid_argument &ia) {
        std::cerr << ia.what();
    }
}

template <class VertexType, class WeightType>
void CityMap<VertexType, WeightType>::open(const VertexType &vertex) {
    try {
        cityMap.open(vertex);
    } 
    catch (const std::invalid_argument &ia) {
        std::cerr << ia.what();
    }
}

template <class VertexType, class WeightType>
void CityMap<VertexType, WeightType>::closed() const {
    cityMap.printClosed();
}

template <class VertexType, class WeightType>
void CityMap<VertexType, WeightType>::deadEnds() const {
    cityMap.deadEnds();
}

template <class VertexType, class WeightType>
void CityMap<VertexType, WeightType>::toAll() {
    try {
        cityMap.motherVertex(currentJunction);
    } 
    catch (const std::invalid_argument &ia) {
        std::cerr << ia.what();
    }
}

template <class VertexType, class WeightType>
void CityMap<VertexType, WeightType>::tour() {
    try {
        cityMap.EulerianPath(currentJunction);
    } 
    catch (const std::invalid_argument &ia) {
        std::cerr << ia.what();
    }
}

template <class VertexType, class WeightType>
void CityMap<VertexType, WeightType>::partialTour() {
    try {
        cityMap.isCyclicIter(currentJunction);
    } 
    catch (const std::invalid_argument &ia) {
        std::cerr << ia.what();
    }
}

template <class VertexType, class WeightType>
void CityMap<VertexType, WeightType>::draw(const std::string &fileName) {
    std::ofstream dot(fileName.c_str());
    cityMap.drawGraph(dot);
    std::cout << "* The graph was successfully drawn. To see open " << fileName << ". *\n";
}

template <class VertexType, class WeightType>
void CityMap<VertexType, WeightType>::printMap() const {
    cityMap.printGraph();
}

template <class VertexType, class WeightType>
void CityMap<VertexType, WeightType>::run() {
    printMessage(0);

    std::string command;
    std::cin >> command;

    std::string fileName;
    std::string currentJunction;
    std::cin >> fileName >> currentJunction;

    if (command == "openMap") {
        if (!createMap(fileName, currentJunction)) {
            return;
        }
    } 
    else {
        std::cout << "* You did not provide the needed info. Try again. *\n";
        return;
    }

    char elem = getchar();

    std::string choice;
    bool mapIsOpen = true;
    while (mapIsOpen) {
        printMessage(1);

        std::vector<std::string> _choice;
        getline(std::cin, choice);
        splitIntoWords(choice, _choice);

        if (_choice[0] == "help" && _choice.size() == 1) {
            help();
        }
         else if (_choice[0] == "location" && _choice.size() == 1) {
            location();
        } 
        else if (_choice[0] == "change" && _choice.size() == 2) {
            change(_choice[1]);
        } 
        else if (_choice[0] == "neighbours" && _choice.size() == 1) {
            neighbours();
        } 
        else if (_choice[0] == "move" && _choice.size() == 2) {
            move(_choice[1]);
        } 
        else if (_choice[0] == "shortest" && _choice.size() == 2) {
            shortest(_choice[1]);
        } 
        else if (_choice[0] == "close" && _choice.size() == 2) {
            close(_choice[1]);
        } 
        else if (_choice[0] == "open" && _choice.size() == 2) {
            open(_choice[1]);
        } 
        else if (_choice[0] == "closed" && _choice.size() == 1) {
            closed();
        } 
        else if (_choice[0] == "deadEnds" && _choice.size() == 1) {
            deadEnds();
        } 
        else if (_choice[0] == "toAll" && _choice.size() == 1) {
            toAll();
        } 
        else if (_choice[0] == "tour" && _choice.size() == 1) {
            tour();
        } 
        else if (_choice[0] == "partialTour" && _choice.size() == 1) {
            partialTour();
        } 
        else if (_choice[0] == "draw" && _choice.size() == 2) {
            draw(_choice[1]);
        } 
        else if (_choice[0] == "printMap" && _choice.size() == 1) {
            printMap();
        } 
        else if (_choice[0] == "exit" && _choice.size() == 1) {
            std::cout << "* Exiting... *" << std::endl;
            mapIsOpen = false;
        } 
        else {
            std::cout << "* Invalid command. Please, try again. *" << std::endl;
        }
    }
}

#endif
