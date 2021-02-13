#include "Line.h"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

double intoNumber(const std::string &word, int ind);
double getNumber(const std::string &word);
std::string getFill(const std::string &word);
void splitIntoWords(const std::string &info, std::vector<std::string> &words, const int &start);
bool isNumber(const std::string &word);

void Line::copy(const std::string &_fill, const double &_x1, const double &_x2, const double &_y1, const double &_y2) {
    type = "line";
    fill = _fill;
    x1 = _x1;
    x2 = _x2;
    y1 = _y1;
    y2 = _y2;
}
Line *Line::clone() {
    return new Line(*this);
}

Line::Line() : x1{0}, x2{0}, y1{0}, y2{0} {
    type = "line";
    fill = "";
}

Line::Line(const std::string &_fill, const double &_x1, const double &_x2, const double &_y1,
           const double &_y2) : x1{_x1}, x2{_x2}, y1{_y1}, y2{_y2} {
    type = "line";
    fill = _fill;
}

Line::Line(const Line &other) {
    copy(other.fill, other.x1, other.x2, other.y1, other.y2);
}

Line &Line::operator=(const Line &other) {
    if (this != &other) {
        copy(other.fill, other.x1, other.x2, other.y1, other.y2);
    }
    return *this;
}

void Line::print() {
    std::cout << type << " " << x1 << " " << x2 << " " << y1 << " " << y2 << " " << fill << std::endl;
}

bool Line::create(const std::vector<std::string> &info) {
    if (info.size() != 6 || !isNumber(info[1]) || !isNumber(info[2]) ||
        !isNumber(info[3]) || !isNumber(info[4]) || isNumber(info[5])) {
        std::cout << "Invalid info.\n";
        return false;
    }
    type = "line";
    x1 = intoNumber(info[1], -1);
    x2 = intoNumber(info[2], -1);
    y1 = intoNumber(info[3], -1);
    y2 = intoNumber(info[4], -1);
    fill = info[5];

    std::cout << "You have successfully created a line.\n";
    return true;
}

void Line::serialize(std::ostream &out) {
    out << "<line x1=\"" << x1 << "\" x2=\"" << x2 << "\" y1=\"" << y1 << "\" y2=\"" << y2 << "\" stroke=\"" << fill << "\"/>\n";
}

void Line::deserialize(std::istream &in) {
    std::string info;
    getline(in, info);

    std::vector<std::string> words;
    splitIntoWords(info, words, 1);

    type = "line";
    x1 = getNumber(words[0]);
    x2 = getNumber(words[1]);
    y1 = getNumber(words[2]);
    y2 = getNumber(words[3]);
    fill = getFill(words[4]);
}

void Line::translate(const double &v, const double &h) {
    x1 += h;
    x2 += h;
    y1 += v;
    y2 += v;
}

bool Line::withinRect(const double &_x, const double &_y, const double &_width, const double &_height) {
    return x1 >= _x && x1 <= (_x + _width) && y1 >= _y && y1 <= (_y + _height) &&
           x2 >= _x && x2 <= (_x + _width) && y2 >= _y && y2 <= (_y + _height);
}

bool Line::withinCircle(const double &_cx, const double &_cy, const double &_r) {
    double point1 = sqrt((x1 - _cx) * (x1 - _cx) + (y1 - _cy) * (y1 - _cy));
    double point2 = sqrt((x2 - _cx) * (x2 - _cx) + (y2 - _cy) * (y2 - _cy));
    return point1 <= _r && point2 <= _r;
}