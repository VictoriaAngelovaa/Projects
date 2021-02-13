#pragma once

#include "Figure.h"
#include <fstream>
#include <vector>

///Class containing all of the figures from a given SVG file.

class SVGFiles {
    std::vector<Figure*> figures;
    void copy (std::vector<Figure*> otherFigures);
    void destroy ();
    public:
    SVGFiles () = default;
    SVGFiles (std::vector<Figure*> otherFigures);
    SVGFiles (const SVGFiles& other);
    SVGFiles& operator = (const SVGFiles& other);
    ~SVGFiles ();
    void printHelp () const;
    void loadFigures (const std::string& fileName);
    void print () const;
    void serialize (std::ofstream& outFile);
    void createFigure (const std::vector<std::string>& info);
    void erase (const std::vector<std::string>& info);
    ///Translates all figures or a specific figure. 
    void translate (const std::vector<std::string>& info);
    ///Shows all figures located within a given circle/rectangle. 
    void within (const std::vector<std::string>& info);
    void svgRun ();
};

//g++ Figure.cpp Circle.cpp Rectangle.cpp Line.cpp Ellipse.cpp Factory.cpp svgFiles.cpp main.cpp -o svg.exe