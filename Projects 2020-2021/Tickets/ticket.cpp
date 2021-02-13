#include"ticket.h"
#include<iostream>
#include<string>
#include<cmath>

std::string toString (int _num) {
    std::string code = "";
    while (_num != 0) {
        int dig = _num % 10;
        _num = _num / 10;
        char a = dig + '0';
        code.push_back(a);
    }
    return code;
}

std::string reverseString (std::string& str) {
    for (int i = 0; i < str.size() / 2; i++) {
        std::swap(str[i], str[str.size() - i - 1]);
    }
    return str;
}

void Ticket::copy (const std::string& _type, const int& _row, const int& _seat, const std::string& _uniqueNo) {
    type = _type;
    row = _row;
    seat = _seat;
    uniqueNo = _uniqueNo;
}

Ticket::Ticket (const std::string& _type, const int& _row, const int& _seat, const std::string& _uniqueNo) {
    copy(_type, _row, _seat, _uniqueNo);
}

Ticket::Ticket (const Ticket& other) {
    copy(other.type, other.row, other.seat, other.uniqueNo);
}

Ticket& Ticket::operator = (const Ticket& other) {
    if (this != &other) {
        copy(other.type, other.row, other.seat, other.uniqueNo);
    }
    return *this;
}

Ticket* Ticket::clone () {
    return new Ticket(*this);
}

const std::string Ticket::getType () const {
    return type;
}

const std::string Ticket::getUniqueNo () const {
    return uniqueNo;
}

const int Ticket::getRow () const {
    return row;
}

const int Ticket::getSeat () const {
    return seat;
}

void Ticket::setType (const std::string& _type) {
    type = _type;
}

bool Ticket::freeSeat () const {
   return type == "free";
}

void Ticket::createCode(int _hall, int _event, int _row, int _seat) {
    std::string code = "";

    std::string s = toString (_hall);
    code += reverseString(s);
    code.push_back('#');

    s = toString (_event);
    code += reverseString(s);
    code.push_back('#');

    s = toString (_row);
    code += reverseString(s);
    code.push_back('#');
    
    s = toString (_seat);
    code += reverseString(s);
    uniqueNo = code;
}

void Ticket::infoByCode (const std::string& _code) const {
    int _seat = 0;
    int _row = 0;
    int i = _code.size() - 1;
    int cnt = 0;
    while (_code[i] != '#') {
        _seat += (_code[i] - '0') * pow(10, cnt);
        cnt++;
        i--;
    }
    i--;
    cnt = 0;
    while (_code[i] != '#') {
        _row += (_code[i] - '0') * pow(10, cnt);
        cnt++;
        i--;
    }
    std::cout << "* Your seat is on row " << _row << " and the seat number is " << _seat << ". *\n";
}

void Ticket::printTicket () const {
    std::cout << "Type: " << type << " " << "Row: " << row << " Seat: " << seat << " Code: " << uniqueNo << std::endl;
}
