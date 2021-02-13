#include"ticket.h"
#include"event.h"
#include<iostream>
#include<string>
#include<vector>
#include<fstream>


void Event::copy (const std::string& _name, const std::string& _date, std::vector<Ticket*> _tickets) {
    name = _name;
    date = _date;
    for (int i = 0; i < _tickets.size(); i++) {
        tickets.push_back(tickets[i]->clone());
    }
}

void Event::destroy () {
    for (auto t : tickets) {
        delete t;
    }
    tickets.clear();
}

Event::Event (const std::string& _name, const std::string& _date, std::vector<Ticket*> _tickets) {
    copy(_name, _date, _tickets);
}

Event::Event (const Event& other) {
    copy(other.name, other.date, other.tickets);
}

Event::Event (const std::string& _date, const std::string& _name) {
    name = _name;
    date = _date;
}

Event& Event::operator = (const Event& other) {
    if (this != &other) {
        destroy();
        copy(other.name, other.date, other.tickets);
    }
    return *this;
}

Event::~Event () {
    destroy();
}

Event* Event::clone () {
    return new Event(*this);
}

const std::string Event::getName () const {
    return name;
}

const std::string Event::getDate () const {
    return date;
}

void Event::setTickets (std::vector<Ticket*> _tickets) {
    for (int i = 0; i < _tickets.size(); i++) {
        tickets.push_back(_tickets[i]->clone());
    }
}

const int Event::ticketIndex (const int& _row, const int& _seat) const {
    for (int i = 0; i < tickets.size(); i++) {
        if(tickets[i]->getSeat() == _seat && tickets[i]->getRow() == _row) {
            return i;
        }
    }
    return -1;
}

bool Event::seatIsFree (const int& _row, const int& _seat) const {
    if (tickets[ticketIndex(_row, _seat)]->getType() == "free") {
        return true;
    }
    return false;
}

bool Event::foundCode (const std::string& _code) const {
    for (int i = 0; i < tickets.size(); i++) {
        if (_code == tickets[i]->getUniqueNo()) {
            return true;
        }
    }
    return false;
}

void Event::bookTicket (const int& _row, const int& _seat) {
    std::string _type = "booked";
    tickets[ticketIndex(_row, _seat)]->setType(_type);
}

void Event::unbookTicket (const int& _row, const int& _seat) {
    std::string _type = "free";
    tickets[ticketIndex(_row, _seat)]->setType(_type);
}

void Event::buyTicket (int _hall, int _event, int _row, int _seat) {
    std::string _type = "bought";
    tickets[ticketIndex(_row, _seat)]->setType(_type);
    tickets[ticketIndex(_row, _seat)]->createCode(_hall, _event, _row, _seat);
    std::cout << "* Ticket code: " << tickets[ticketIndex(_row, _seat)]->getUniqueNo() << " *" << std::endl;
}

int Event::countTickets (const std::string& _type) const {
    int cnt = 0;
    for (int i = 0; i < tickets.size(); i++) {
        if (tickets[i]->getType() == _type) {
            cnt++;
        }
    }
    return cnt;
}

void Event::infoByCode (const std::string& _code) const {
    for (int i = 0; i < tickets.size(); i++) {
        if (_code == tickets[i]->getUniqueNo()) {
            tickets[i]->infoByCode(_code);
        }
    }
}

void Event::printEvent () const {
    std::cout << "* Name: " << name << " Date: " << date << ". *" << std::endl;
}

void Event::serialize (std::ofstream& file) const {
    file << date << " " << name << " ";
}

void Event::printTickets () const {
    for (int i = 0; i < tickets.size(); i++) {
        tickets[i]->printTicket();
    }
}

void Event::printFreeTickets () const {
    for (int i = 0; i < tickets.size(); i++) {
        if (tickets[i]->getType() == "free") {
            tickets[i]->printTicket();
        }
    }
}

void Event::printBookedTickets () const {
    for (int i = 0; i < tickets.size(); i++) {
        if (tickets[i]->getType() == "booked") {
            std::cout << "* Event: " << name << " Date: " << date << " ";
            tickets[i]->printTicket();
        }
    }
}
