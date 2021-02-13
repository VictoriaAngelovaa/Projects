#ifndef _LINE_HH
#define _LINE_HH_

#include "Figure.h"
#include <iostream>

class Line : public Figure {
    double x1;
    double x2;
    double y1;
    double y2;
    void copy(const std::string& _fill, const double& _x1, const double& _x2, const double& _y1, const double& _y2);
    public:
    Line* clone () override;
    Line ();
    Line (const std::string& _fill, const double& _x1, const double& _x2, const double& _y1, const double& _y2);
    Line (const Line& other);
    Line& operator = (const Line& other);
    ~Line () = default;
    void print () override;
    bool create (const std::vector<std::string>& info) override;
    void serialize (std::ostream& out) override;
    void deserialize (std::istream& in) override;
    ///Translates the line.
    void translate (const double& v, const double& h) override;
    ///Checks if the line is located within a given rectangle and prints it. 
    bool withinRect (const double& _x, const double& _y, const double& _width, const double& _height) override;
    ///Checks if the line is located within a given circle and prints it. 
    bool withinCircle (const double& _cx, const double& _cy, const double& _r) override;
};

#endif