#include "cityMap.h"
#include <string>

int main () {
    CityMap<std::string, int> cityMap;
    cityMap.run();

    return 0;
}

// g++ main.cpp -o map.exe