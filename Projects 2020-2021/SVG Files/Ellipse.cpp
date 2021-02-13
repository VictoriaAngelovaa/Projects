#include "Ellipse.h"
#include <iostream>
#include <string>
#include <vector>

double intoNumber(const std::string &word, int ind);
double getNumber(const std::string &word);
std::string getFill(const std::string &word);
void splitIntoWords(const std::string &info, std::vector<std::string> &words, const int &start);
bool isNumber(const std::string &word);

void Ellipse::copy(const std::string &_fill, const double &_cx, const double &_cy, const double &_rx, const double &_ry) {
    type = "ellipse";
    fill = _fill;
    cx = _cx;
    cy = _cy;
    rx = _rx;
    ry = _ry;
}
Ellipse *Ellipse::clone() {
    return new Ellipse(*this);
}

Ellipse::Ellipse() : cx{0}, cy{0}, rx{0}, ry{0} {
    type = "ellipse";
    fill = "";
}

Ellipse::Ellipse(const std::string &_fill, const double &_cx, const double &_cy, const double &_rx,
                 const double &_ry) : cx{_cx}, cy{_cy}, rx{_rx} {
    type = "ellipse";
    fill = _fill;
}

Ellipse::Ellipse(const Ellipse &other) {
    copy(other.fill, other.cx, other.cy, other.rx, other.ry);
}

Ellipse &Ellipse::operator=(const Ellipse &other) {
    if (this != &other) {
        copy(other.fill, other.cx, other.cy, other.rx, other.ry);
    }
    return *this;
}

void Ellipse::print() {
    std::cout << type << " " << cx << " " << cy << " " << rx << " " << ry << " " << fill << std::endl;
}

bool Ellipse::create(const std::vector<std::string> &info) {
    if (info.size() != 6 || !isNumber(info[1]) || !isNumber(info[2]) ||
        !isNumber(info[3]) || !isNumber(info[4]) || isNumber(info[5])) {
        std::cout << "Invalid info.\n";
        return false;
    }
    type = "ellipse";
    cx = intoNumber(info[1], -1);
    cy = intoNumber(info[2], -1);
    rx = intoNumber(info[3], -1);
    ry = intoNumber(info[4], -1);
    fill = info[5];

    std::cout << "You have successfully created an ellipse.\n";
    return true;
}

void Ellipse::serialize(std::ostream &out) {
    out << "<ellipse cx=\"" << cx << "\" cy=\"" << cy << "\" rx=\"" << rx << "\" ry=\"" << ry << "\" fill=\"" << fill << "\"/>\n";
}

void Ellipse::deserialize(std::istream &in) {
    std::string info;
    getline(in, info);

    std::vector<std::string> words;
    splitIntoWords(info, words, 1);

    type = "ellipse";
    cx = getNumber(words[0]);
    cy = getNumber(words[1]);
    rx = getNumber(words[2]);
    ry = getNumber(words[3]);
    fill = getFill(words[4]);
}

void Ellipse::translate(const double &v, const double &h) {
    cx += h;
    cy += v;
}

bool Ellipse::withinRect(const double &_x, const double &_y, const double &_width, const double &_height) {
    return cx >= _x && cx <= (_x + _width) && cy >= _y && cy <= (_y + _height) &&
           (cx + rx) <= (_x + _width) && (cx - rx) >= _x && (cy + ry) <= (_y + _height) && (cy - ry) >= _y;
}

bool Ellipse::withinCircle(const double &_cx, const double &_cy, const double &_r) {
    double centerDis = sqrt((cx - _cx) * (cx - _cx) + (cy - _cy) * (cy - _cy));
    return (centerDis + rx) <= _r && (centerDis + ry) <= _r;
}