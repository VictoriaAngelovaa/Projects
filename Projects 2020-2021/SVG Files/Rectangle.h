#ifndef _RECTANGLE_HH
#define _RECTANGLE_HH_

#include "Figure.h"
#include <iostream>

class Rectangle : public Figure {
    double x;
    double y;
    double width;
    double height;
    void copy(const std::string& _fill, const double& _x, const double& _y, const double& _width, const double& _height);
    public:
    Rectangle* clone () override;
    Rectangle ();
    Rectangle (const std::string& _fill, const double& _x, const double& _y, const double& _width, const double& _height);
    Rectangle (const Rectangle& other);
    Rectangle& operator = (const Rectangle& other);
    ~Rectangle () = default;
    void print () override;
    bool create (const std::vector<std::string>& info) override;
    void serialize (std::ostream& out) override;
    void deserialize (std::istream& in) override;
    ///Translates the rectangle.
    void translate (const double& v, const double& h) override;
    ///Checks if the rectangle is located within a given rectangle and prints it. 
    bool withinRect (const double& _x, const double& _y, const double& _width, const double& _height) override;
    ///Checks if the rectangle is located within a given circle and prints it. 
    bool withinCircle (const double& _cx, const double& _cy, const double& _r) override;
};

#endif