#ifndef _FACTORY_HH
#define _FACTORY_HH

#include "Figure.h"

class FigureFactory {
    public:
    ///Creates a figure.
    static Figure* make (const std::string& type);
};

#endif