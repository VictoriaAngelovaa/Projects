#include "Factory.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Figure.h"
#include "Line.h"
#include "Rectangle.h"
#include <cassert>

Figure* FigureFactory::make(const std::string& type) {
    Figure *newFigure = nullptr;
    if (type == "<circle" || type == "circle") {
        newFigure = new Circle;
    }
    else if (type == "<rect" || type == "rectangle") {
        newFigure = new Rectangle;
    }
    else if (type == "<line" || type == "line") {
        newFigure = new Line;
    }
    else if (type == "<ellipse" || type == "ellipse") {
        newFigure = new Ellipse;
    }
    else {
        assert(false);
    }
    return newFigure;
}
