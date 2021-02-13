#include "Circle.h"
#include "Rectangle.h"
#include <cmath>
#include <string>
#include <vector>

double getNumber(const std::string &word);
std::string getFill(const std::string &word);
void splitIntoWords(const std::string &info, std::vector<std::string> &words, const int &start);
double intoNumber(const std::string &word, int ind);
bool isNumber(const std::string &word);

void Circle::copy(const std::string &_fill, const double &_cx, const double &_cy, const double &_r) {
    type = "circle";
    fill = _fill;
    cx = _cx;
    cy = _cy;
    r = _r;
}
Circle *Circle::clone() {
    return new Circle(*this);
}

Circle::Circle() : cx{0.0}, cy{0.0}, r{0.0} {
    type = "circle";
    fill = "";
}

Circle::Circle(const std::string &_fill, const double &_cx, const double &_cy, const double &_r) : cx{_cx}, cy{_cy}, r{_r} {
    type = "circle";
    fill = _fill;
}

Circle::Circle(const Circle &other) {
    copy(other.fill, other.cx, other.cy, other.r);
}

Circle &Circle::operator=(const Circle &other) {
    if (this != &other) {
        copy(other.fill, other.cx, other.cy, other.r);
    }
    return *this;
}

void Circle::print() {
    std::cout << type << " " << cx << " " << cy << " " << r << " " << fill << std::endl;
}

bool Circle::create(const std::vector<std::string> &info) {
    if (info.size() != 5 || !isNumber(info[1]) || !isNumber(info[2]) || !isNumber(info[3]) || isNumber(info[4])) {
        std::cout << "Invalid info.\n";
        return false;
    }
    type = "circle";
    cx = intoNumber(info[1], -1);
    cy = intoNumber(info[2], -1);
    r = intoNumber(info[3], -1);
    fill = info[4];

    std::cout << "You have successfully created a circle.\n";
    return true;
}

void Circle::serialize(std::ostream &out) {
    out << "<circle cx=\"" << cx << "\" cy=\"" << cy << "\" r=\"" << r << "\" fill=\"" << fill << "\"/>\n";
}

void Circle::deserialize(std::istream &in) {
    std::string info;
    getline(in, info);

    std::vector<std::string> words;
    splitIntoWords(info, words, 1);

    type = "circle";
    cx = getNumber(words[0]);
    cy = getNumber(words[1]);
    r = getNumber(words[2]);
    fill = getFill(words[3]);
}

void Circle::translate(const double &v, const double &h) {
    cx += h;
    cy += v;
}

bool Circle::withinRect(const double &_x, const double &_y, const double &_width, const double &_height) {
    Rectangle rect("", _x, _y, _width, _height);
    if (rect.withinCircle(cx, cy, r)) {
        return false;
    }
    return cx >= _x && cx <= (_x + _width) && cy >= _y && cy <= (_y + _height) &&
           (cx + r) <= (_x + _width) && (cx - r) >= _x && (cy + r) <= (_y + _height) && (cy - r) >= _y;
}

bool Circle::withinCircle(const double &_cx, const double &_cy, const double &_r) {
    double centerDis = sqrt((cx - _cx) * (cx - _cx) + (cy - _cy) * (cy - _cy));
    return (centerDis + r) <= _r;
}