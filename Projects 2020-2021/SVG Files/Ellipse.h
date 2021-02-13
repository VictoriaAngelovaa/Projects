#ifndef _ELLIPSE_HH
#define _ELLIPSE_HH_

#include "Figure.h"
#include <iostream>

class Ellipse : public Figure {
    double cx;
    double cy;
    double rx;
    double ry;
    void copy(const std::string& _fill, const double& _cx, const double& _cy, const double& _rx, const double& _ry);
    public:
    Ellipse* clone () override;
    Ellipse ();
    Ellipse (const std::string& _fill, const double& _cx, const double& _cy, const double& _rx, const double& _ry);
    Ellipse (const Ellipse& other);
    Ellipse& operator = (const Ellipse& other);
    ~Ellipse () = default;
    void print () override;
    bool create (const std::vector<std::string>& info) override;
    void serialize (std::ostream& out) override;
    void deserialize (std::istream& in) override;
    ///Translates the ellipse.
    void translate (const double& v, const double& h) override;
    ///Checks if the ellipse is located within a given rectangle and prints it.
    bool withinRect (const double& _x, const double& _y, const double& _width, const double& _height) override;
    ///Checks if the ellipse is located within a given circle and prints it. 
    bool withinCircle (const double& _cx, const double& _cy, const double& _r) override;
};

#endif