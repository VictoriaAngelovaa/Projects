#include "Rectangle.h"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

double intoNumber(const std::string &word, int ind);
double getNumber(const std::string &word);
std::string getFill(const std::string &word);
void splitIntoWords(const std::string &info, std::vector<std::string> &words, const int &start);
bool isNumber(const std::string &word);

void Rectangle::copy(const std::string &_fill, const double &_x, const double &_y, const double &_width, const double &_height) {
    type = "rect";
    fill = _fill;
    x = _x;
    y = _y;
    width = _width;
    height = _height;
}

Rectangle *Rectangle::clone() {
    return new Rectangle(*this);
}

Rectangle::Rectangle() : x{0}, y{0}, width{0}, height{0} {
    type = "rect";
    fill = "";
}

Rectangle::Rectangle(const std::string &_fill, const double &_x, const double &_y, const double &_width,
                     const double &_height) : x{_x}, y{_y}, width{_width} {
    type = "rect";
    fill = _fill;
}

Rectangle::Rectangle(const Rectangle &other) {
    copy(other.fill, other.x, other.y, other.width, other.height);
}

Rectangle &Rectangle::operator=(const Rectangle &other) {
    if (this != &other) {
        copy(other.fill, other.x, other.y, other.width, other.height);
    }
    return *this;
}

void Rectangle::print() {
    std::cout << type << "angle " << x << " " << y << " " << width << " " << height << " " << fill << std::endl;
}

bool Rectangle::create(const std::vector<std::string> &info) {
    if (info.size() != 6 || !isNumber(info[1]) || !isNumber(info[2]) ||
        !isNumber(info[3]) || !isNumber(info[4]) || isNumber(info[5])) {
        std::cout << "Invalid info.\n";
        return true;
    }
    type = "rect";
    x = intoNumber(info[1], -1);
    y = intoNumber(info[2], -1);
    width = intoNumber(info[3], -1);
    height = intoNumber(info[4], -1);
    fill = info[5];

    std::cout << "You have successfully created a rectangle.\n";
    return true;
}

void Rectangle::serialize(std::ostream &out) {
    out << "<rect x=\"" << x << "\" y=\"" << y << "\" width=\"" << width << "\" height=\"" << height << "\" fill=\"" << fill << "\"/>\n";
}

void Rectangle::deserialize(std::istream &in) {
    std::string info;
    getline(in, info);

    std::vector<std::string> words;
    splitIntoWords(info, words, 1);

    type = "rect";
    x = getNumber(words[0]);
    y = getNumber(words[1]);
    width = getNumber(words[2]);
    height = getNumber(words[3]);
    fill = getFill(words[4]);
}

void Rectangle::translate(const double &v, const double &h) {
    x += h;
    y += v;
}

bool Rectangle::withinRect(const double &_x, const double &_y, const double &_width, const double &_height) {
    return x >= _x && x <= (_x + _width) && y >= _y && y <= (_y + _height) &&
           (x + width) >= _x && (x + width) <= (_x + _width) && (y + height) >= _y && (y + height) <= (_y + _height);
}

bool Rectangle::withinCircle(const double &_cx, const double &_cy, const double &_r) {
    double point1 = sqrt((x - _cx) * (x - _cx) + (y - _cy) * (y - _cy));
    double point2 = sqrt(((x + width) - _cx) * ((x + width) - _cx) + (y - _cy) * (y - _cy));
    double point3 = sqrt((x - _cx) * (x - _cx) + ((y + height) - _cy) * ((y + height) - _cy));
    double point4 = sqrt(((x + width) - _cx) * ((x + width) - _cx) + ((y + height) - _cy) * ((y + height) - _cy));
    return point1 <= _r && point2 <= _r && point3 <= _r && point4 <= _r;
}