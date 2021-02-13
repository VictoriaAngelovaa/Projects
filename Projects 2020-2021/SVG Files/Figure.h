#ifndef _FIGURE_HH
#define _FIGURE_HH

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cmath>

///Abstract base class 

class Figure {
    protected:
    std::string type;
    std::string fill;
    public:
    virtual Figure* clone () = 0;
    virtual ~Figure () {}
    virtual void print () = 0;
    virtual bool create (const std::vector<std::string>& info) = 0;
    virtual void serialize (std::ostream& out) = 0;
    virtual void deserialize (std::istream& in) = 0;
    ///Translates a figure with a given serial number.
    virtual void translate (const double& v, const double& h) = 0; 
    ///Checks if a figure is located within a given rectangle and prints it. 
    virtual bool withinRect (const double& _x, const double& _y, const double& _width, const double& _height) = 0;
    ///Checks if a figure is located within a given circle and prints it. 
    virtual bool withinCircle (const double& _cx, const double& _cy, const double& _r) = 0;
};

#endif