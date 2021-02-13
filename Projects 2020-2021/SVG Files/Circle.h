#ifndef _CIRCLE_HH
#define _CIRLCE_HH_

#include "Figure.h"
#include <iostream>

class Circle : public Figure {
    double cx;
    double cy;
    double r;
    void copy (const std::string& _fill, const double& _cx, const double& _cy, const double& _r);
    public:
    Circle* clone () override;
    Circle ();
    Circle (const std::string& _fill, const double& _cx, const double& _cy, const double& _r);
    Circle (const Circle& other);
    Circle& operator = (const Circle& other);
    ~Circle () = default;
    void print () override;
    bool create (const std::vector<std::string>& info) override;
    void serialize (std::ostream& out) override;
    void deserialize (std::istream& in) override;
    ///Translates the circle.
    void translate (const double& v, const double& h) override;
    ///Checks if the circle is located within a given rectangle and prints it.
    bool withinRect (const double& _x, const double& _y, const double& _width, const double& _height) override;
    ///Checks if the circle is located within a given circle and prints it. 
    bool withinCircle (const double& _cx, const double& _cy, const double& _r) override;
};

#endif