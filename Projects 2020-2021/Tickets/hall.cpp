#include"hall.h"
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<vector>
#include"ticket.h"
#include"event.h"


void Hall::copy (const int& _hallNumber, const int& _rowCount, 
                 const std::vector<int>& _seatsPerRow, std::vector<Event*> _eventsList) {
    hallNumber = _hallNumber;
    rowCount = _rowCount;
    for (int i = 0; i < rowCount; i++) {
        seatsPerRow.push_back(_seatsPerRow[i]);
    }
    for (int i = 0; i < _eventsList.size(); i++) {
        eventsList.push_back(_eventsList[i]->clone());
    }
}

void Hall::destroy () {
    for (Event* e : eventsList) {
        delete e;
    }
    eventsList.clear();
}

Hall::Hall (const int& _hallNumber, const int& _rowCount, 
            const std::vector<int>& _seatsPerRow, std::vector<Event*> _eventsList) {
    copy(_hallNumber, _rowCount, _seatsPerRow, _eventsList);
}

Hall::Hall (const int& _hallNumber, const int& _rowCount, const std::vector<int>& _seatsPerRow) {
    hallNumber = _hallNumber;
    rowCount = _rowCount;
    for (int i = 0; i < rowCount; i++) {
        seatsPerRow.push_back(_seatsPerRow[i]);
    }
}

Hall::Hall (const Hall& other) {
    copy(other.hallNumber, other.rowCount, other.seatsPerRow, other.eventsList);
}

Hall& Hall::operator = (const Hall& other) {
    if (this != &other) {
        seatsPerRow.clear();
        destroy();
        copy(other.hallNumber, other.rowCount, other.seatsPerRow, other.eventsList);
    }
    return *this;
}

Hall::~Hall () {
    destroy();
}

Hall* Hall::clone () {
    return new Hall(*this);
}

int const Hall::getHallNumber () const {
    return hallNumber;
}

int const Hall::getSeatsPerRow (const int& _row) const {
    return seatsPerRow[_row - 1];
} 

void Hall::addEvent (const std::string& _date, const std::string& _name) {
    if (freeDate(_date) == false) {
        std::cout << "* There is an event on this date. Please chose another date. *\n";
    }
    else { 
        eventsList.push_back(new Event(_date, _name));
        createTickets(_date, _name);
        std::cout << "* The event is added successfully. *\n";
    }
}

const int Hall::eventIndex (const std::string& _date, const std::string& _name) const {
    for (int i = 0; i < eventsList.size(); i++) {
        if (eventsList[i]->getName() == _name && eventsList[i]->getDate() == _date) {
            return i;
        }
    }
    return -1;
}

void Hall::createTickets (const std::string& _date, const std::string& _name) {
    std::vector<Ticket*> newTickets;
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < seatsPerRow[i]; j++) {
            std::string t = "free";
            std::string c = "0";
            newTickets.push_back(new Ticket(t, i+1, j+1, c));
        }
    }
    eventsList[eventIndex(_date, _name)]->setTickets(newTickets);
    for (Ticket* t : newTickets) {
        delete t;
    }
    newTickets.clear();
}

bool Hall::foundEvent (const std::string& _date, const std::string& _name) const {
    return eventIndex(_date, _name) >= 0;
}

bool Hall::freeDate (const std::string& _date) const {
    for (int i = 0; i < eventsList.size(); i++) {
        if (eventsList[i]->getDate() == _date) {
            return false;
        }
    }
    return true;
}

bool Hall::seatIsValid (const int& _row, const int& _seat) const {
    return _row <= rowCount && _seat <= seatsPerRow[_row - 1] && _row > 0 && _seat > 0;
}

bool Hall::foundCode (const std::string& _code) const {
    for (int i = 0; i < eventsList.size(); i++) {
        if (eventsList[i]->foundCode(_code)) {
            return true;
        }
    }
    return false;
}

void Hall::bookTicketForEvent (const std::string& _date, const std::string& _name, const int& _row, const int& _seat) {
    if (seatIsValid(_row, _seat) == false) {
        std::cout << "* Invalid seat. *\n";
        return;
    }
    if (!eventsList[eventIndex(_date, _name)]->seatIsFree(_row, _seat)) {
        std::cout << "* The seat has already been reserved. Please, chose another seat. *\n";
        return;
    }
    eventsList[eventIndex(_date, _name)]->bookTicket(_row, _seat);
    std::cout << "* The reservation was successfully made. *\n";
}

void Hall::unbookTicketForEvent (const std::string& _date, const std::string& _name, const int& _row, const int& _seat) {
    if (seatIsValid(_row, _seat)==false) {
        std::cout << "* Invalid seat. *\n";
        return;
    }
    if (eventsList[eventIndex(_date, _name)]->seatIsFree(_row, _seat)) {
        std::cout << "* The reservation has already been canceled. *\n";
        return;
    }
    eventsList[eventIndex(_date, _name)]->unbookTicket(_row, _seat);
    std::cout << "* The reservation was successfully canceled. *\n";
}

void Hall::buyTicketForEvent (const std::string& _date, const std::string& _name, int _row, int _seat) {
    if (seatIsValid(_row, _seat)==false) {
        std::cout << "* Invalid seat. *\n";
        return;
    }
    if (!eventsList[eventIndex(_date, _name)]->seatIsFree(_row, _seat)) {
        std::cout << "* The seat has already been reserved. Please, chose another seat. *\n";
        return;
    }
    eventsList[eventIndex(_date, _name)]->buyTicket(hallNumber, eventIndex(_date, _name) + 1, _row, _seat);
    std::cout << "* You have successfully bought a ticket for the event. *\n";
}

void Hall::codeInfo (const std::string& _code) const {
    for (int i = 0; i < eventsList.size(); i++) {
        if (eventsList[i]->foundCode(_code)) {
            eventsList[i]->infoByCode(_code);
            return;
        }
    }
}

void Hall::printEvents () const {
    for (int i = 0; i < eventsList.size(); i++) {
        eventsList[i]->printEvent();
    }
}

void Hall::serializeEvents (std::ofstream& file) const {
    for (int i = 0; i < eventsList.size(); i++) {
        eventsList[i]->serialize(file);
        file << hallNumber << "\n";
    }
}

void Hall::printFreeTicketsForEvent (const std::string& _date, const std::string& _name) const {
    eventsList[eventIndex(_date, _name)]->printFreeTickets();
}

void Hall::printBookedTickets () const {
    for (int i = 0; i < eventsList.size(); i++) {
        eventsList[i]->printBookedTickets();
    }
}

void Hall::printBookedTicketsForEvent (const std::string& _date, const std::string& _name) const {
    if (eventIndex(_date, _name) == -1 || eventsList[eventIndex(_date, _name)]->countTickets("booked") == 0) {
        return;
    }
    else {
        eventsList[eventIndex(_date, _name)]->printBookedTickets();
    }
}

void Hall::printBookedTicketsForDate (const std::string& _date) const {
    for (int i = 0; i < eventsList.size(); i++) {
        if (eventsList[i]->getDate() == _date) {
            eventsList[i]->printBookedTickets();
        }
    }
}

void Hall::printBookedTicketsForName (const std::string& _name) const {
    for (int i = 0; i < eventsList.size(); i++) {
        if (eventsList[i]->getName() == _name) {
            eventsList[i]->printBookedTickets();
        }
    }
}

void Hall::reportFromTo (const std::string& fromDate, const std::string& toDate) const {
    for (int i = 0; i < eventsList.size(); i++) {
        if (strcmp(eventsList[i]->getDate().c_str(), fromDate.c_str()) >= 0 && 
           strcmp(eventsList[i]->getDate().c_str(), toDate.c_str()) <= 0) {
            std::cout << "* Name: " << eventsList[i]->getName() << " Date: " << eventsList[i]->getDate() << 
                         " Bought tickets: " << eventsList[i]->countTickets("bought") << " *" << std::endl;
        }
    }
}

void Hall::clearEvents () {
    destroy();
}
