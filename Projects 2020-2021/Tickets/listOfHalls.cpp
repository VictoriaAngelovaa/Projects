#include"hall.h"
#include"ListOfHalls.h"
#include"event.h"
#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<vector>

void printMessage (const int& num) {
    if (num == 0) {
        std::cout << "**************************************************************************************" << std::endl;
        std::cout << "*     Before you start, please open the file containing the needed information.   *" << std::endl;
        std::cout << "**************************************************************************************" << std::endl;
    }
    else if (num == 1) {
        std::cout << std::endl;
        std::cout << "**************************************************************************************" << std::endl;
        std::cout << "*                         What would you like to do next:                            *" << std::endl;
        std::cout << "**************************************************************************************" << std::endl;
        std::cout << std::endl;
    }
}

bool checkIfDate (const std::string& _date) {
    if (_date.size() != 10 || _date[4] != '-' || _date[7]!='-' || _date[5] > '1' || 
        (_date[5] == '1' && _date[6] > '2') || (_date[5] == '0' && _date[6] == '0') || 
        _date[8] > '3' || (_date[8] == '3' && _date[9] > '1')) {
        return false;
    }
    for (int i = 0; i < _date.size(); i++) {
        if (i == 4 || i == 7) {
            i++;
        }
        if (_date[i]>'9' || _date[i]<'0') {
            return false;
        }
    }
    return true;
}

void splitIntoWords (const std::string& info, std::vector<std::string>& words) {
    std::string word;
    for (int i = 0; i < info.size(); i++) {
        if (info[i] == ' ') {
            i++;
            words.push_back(word);
            word.clear();
        }
        word.push_back(info[i]);
    }
    words.push_back(word);
}

int toInt (const std::string& _word) {
    int _num = 0;
    int cnt = _word.size() - 1;
    int index = 0;
    while (index < _word.size() && cnt >= 0) {
        _num += (_word[index] - '0') * pow(10, cnt);
        index++;
        cnt--;
    }
    return _num;
}

void ListOfHalls::copy (std::vector<Hall*> _halls) {
    for (int i = 0; i < _halls.size(); i++) {
        halls.push_back(_halls[i]->clone());
    }
}

void ListOfHalls::destroy () {
    for (Hall* h : halls) {
        delete h;
    }
    halls.clear();
}

ListOfHalls::ListOfHalls (std::vector<Hall*> _halls) {
    copy(_halls);
}

ListOfHalls::ListOfHalls (const ListOfHalls& other) {
    copy(other.halls);
}

ListOfHalls& ListOfHalls::operator = (const ListOfHalls& other) {
    if (this != &other) {
        destroy();
        copy(other.halls);
    }
    return *this;
}

ListOfHalls::~ListOfHalls () {
    destroy();
}

void ListOfHalls::printHelp () const {
    std::cout << "\n* The following commands are supported: *\n";
    std::cout << "    <> open <file> - opens <file>\n";
    std::cout << "    <> close - closes the currently opened file\n";
    std::cout << "    <> save - saves the currently opened file\n";
    std::cout << "    <> saveas <file> - saves the currently opened file in <file>\n";
    std::cout << "    <> help - prints this information\n";
    std::cout << "    <> exit - exits\n";
    std::cout << "    <> addevent <date> <name> <hall> - adds a new event\n";
    std::cout << "    <> freeseats <date> <name> - displays a reference to the vacant seats for an event\n";
    std::cout << "    <> book <row> <seat> <date> <name> - books a ticket for the event\n";
    std::cout << "    <> unbook <row> <seat> <date> <name> - cancels a reservation\n";
    std::cout << "    <> buy <row> <seat> <date> <name> - buys a ticket for an event\n";
    std::cout << "    <> bookings [<date>] [<name>] - displays a reference to the booked tickets\n";
    std::cout << "       > <date> and/or <name> can be skipped\n";
    std::cout << "    <> check <code> - checks for a valid ticket and gives information for the seat\n";
    std::cout << "    <> report <from> <to> [<hall>] - displays a reference to the bought tickets\n";
    std::cout << "       > <hall> can be skipped\n";
    std::cout << "    <> printEvents\n";
}

bool ListOfHalls::loadHalls (const std::string& fileName) {
    std::ifstream file(fileName.c_str(), std::ios::in);
    if (!file) {
        std::cout << "* There is no such file. In order to create some halls you have to give a valid filename. *\n";
        return false;
    }
    int _num, _rows;
    std::vector<int> _seats;
    while (!file.eof()) {
        file>>_num;
        file>>_rows;
        for (int j = 0; j < _rows; j++) {
            int s;
            file >> s;
            _seats.push_back(s);
        }
        _seats.clear();
        halls.push_back(new Hall(_num, _rows, _seats));
    }
    file.close();
    std::cout << "* You have successfully provided the needed information. *\n";
    return true;
}

void ListOfHalls::loadEvents (const std::string& fileName) {
    std::ifstream file(fileName.c_str(), std::ios::in);
    if (file.good()) {
        std::string _date;
        std::string _name;
        int _number;
        while (!file.eof()) {
            file>>_date;
            file>>_name;
            file>>_number;
            addEventInHall(_date, _name, _number);
        }
    }
    file.close();
}

const int ListOfHalls::findIndexByNumber (const int& _number) const {
    for (int i = 0; i < halls.size(); i++) {
        if (halls[i]->getHallNumber() == _number) {
            return i;
        }
    }
    return -1;
}

const int ListOfHalls::hallIndexByEvent (const std::string& _date, const std::string& _name) const {
    for (int i = 0; i < halls.size(); i++) {
        if (halls[i]->foundEvent(_date, _name) == true) {
            return i;
        }
    }
    return -1;
}

void ListOfHalls::addEventInHall (const std::string& _date, const std::string& _name, const int& _hallNumber) {
    if (checkIfDate(_date) == false) {
        std::cout << "* Invalid date. *";
        return;
    }
    if (findIndexByNumber(_hallNumber) >= 0) {
        halls[findIndexByNumber(_hallNumber)]->addEvent(_date, _name);
    }
    else {
        std::cout << "* There is no hall with that number. *\n";
        return;
    }
}

void ListOfHalls::freeseats (const std::string& _date, const std::string& _name) const {
    if (hallIndexByEvent(_date, _name) == -1) {
        std::cout << "* There is no such event. *\n";
        return;
    }
    halls[hallIndexByEvent(_date, _name)]->printFreeTicketsForEvent(_date, _name);
}

void ListOfHalls::bookTicket (const std::string& _date, const std::string& _name, const int& _row, const int& _seat) {
    if (hallIndexByEvent(_date, _name) == -1) {
        std::cout << "* There is no such event. *\n";
        return;
    }
    halls[hallIndexByEvent(_date, _name)]->bookTicketForEvent(_date, _name, _row, _seat);
}

void ListOfHalls::unbookTicket (const std::string& _date, const std::string& _name, const int& _row, const int& _seat) {
    if (hallIndexByEvent(_date, _name) == -1) {
        std::cout << "* There is no such event. *\n";
        return;
    }
    halls[hallIndexByEvent(_date, _name)]->unbookTicketForEvent(_date, _name, _row, _seat);
}

void ListOfHalls::buyTicket (const std::string& _date, const std::string& _name, const int& _row, const int& _seat) {
    if (hallIndexByEvent(_date, _name) == -1) {
        std::cout << "* There is no such event. *\n";
        return;
    }
    halls[hallIndexByEvent(_date, _name)]->buyTicketForEvent(_date, _name, _row, _seat);
}

void ListOfHalls::bookings (const std::vector<std::string>& info) const {
    if (info.size() == 1) {
        for(int i = 0; i < halls.size(); i++) {
            halls[i]->printBookedTickets();
        }
        return;
    }
    if (info.size() == 3) {
        if (hallIndexByEvent(info[1], info[2]) == -1) {
            std::cout<<"* There is no such event. *\n";
            return;
        }
        halls[hallIndexByEvent(info[1], info[2])]->printBookedTicketsForEvent(info[1], info[2]);
    }
    else {
        if (info.size() == 2) {
            if (checkIfDate(info[1])) {
                for (int i = 0; i < halls.size(); i++) {
                    halls[i]->printBookedTicketsForDate(info[1]);
                }
            }
            else {
                for (int i = 0; i < halls.size(); i++) {
                    halls[i]->printBookedTicketsForName(info[1]);
                }
            }
        }
    }
}

void ListOfHalls::check (const std::string& _code) const {
    if (_code == "0") {
        std::cout<<"* Invalid code. *\n";
        return;
    }
    bool found = false;
    for (int i = 0; i < halls.size(); i++) {
        if (halls[i]->foundCode(_code)) {
            found = true;
            halls[i]->codeInfo(_code);
            return;
        }
    }
    if (!found) {
        std::cout << "* Invalid code. *\n";
    }
}

void ListOfHalls::report (const std::vector<std::string>& info) const {
    if (!checkIfDate(info[1]) || !checkIfDate(info[2])) {
        std::cout<<"* Invalid date. *\n";
        return;
    }
    if (info.size() == 3) {
        for (int i = 0; i < halls.size(); i++) {
            halls[i]->reportFromTo(info[1], info[2]);
        }
    }
    else {
        if (findIndexByNumber(toInt(info[3])) == -1) {
            std::cout << "* There is no such hall. *\n";
            return;
        }
        halls[findIndexByNumber(toInt(info[3]))]->reportFromTo(info[1], info[2]);
    }
}

void ListOfHalls::printAllEvents () const {
    for (int i = 0; i < halls.size(); i++) {
        halls[i]->printEvents();
    }
}

void ListOfHalls::serialize (std::ofstream& file) const {
    for (int i = 0; i < halls.size(); i++) {
        halls[i]->serializeEvents(file);
    }
}

void ListOfHalls::clearEvents () {
    for (int i = 0; i < halls.size(); i++ ) {
        halls[i]->clearEvents();
    }
}

void ListOfHalls::run () {
    std::vector<std::string> commands;
    std::vector<std::string> fileNames; 

    printMessage(0);

    std::string command;
    std::cin>>command;
    commands.push_back(command);

    std::string fileName;
    std::cin>>fileName;
    char elem = getchar();

    if (command == "open") {
        if (!loadHalls(fileName.c_str())) 
            return;
    }
    else {
        std::cout << "* You did not provide the needed info. Try again. *\n";
        return;
    }

    std::string choice;
    bool isOpen = true;
    while (isOpen) {
        printMessage(1);

        std::vector<std::string> _choice;
        getline(std::cin, choice);
        splitIntoWords(choice, _choice);

        commands.push_back(_choice[0]);

        if (commands[commands.size() - 2] == "close" ) { 
            while (_choice[0] != "open" && _choice[0] != "exit")  {
                if (choice == "help") {
                    printHelp();
                    std::cout<<"\n";
                }
                else {
                    std::cout << "* Invalid command. Valid commands after closing a file: help, exit, open a new file. *\n";
                }
                getline(std::cin, choice);
                _choice.clear();
                splitIntoWords(choice, _choice);
            }
            commands.push_back(choice);
        }
        if (_choice[0] == "open") {
            if (fileNames.size() != 0) {
                std::cout << "There is already an open file. Please, close it before opening another one.\n";
            }
            else {
                fileNames.push_back(_choice[1]);
                loadEvents(_choice[1]);
                std::cout << "You have successfully opened " << _choice[1] << ".\n";
            }
        }
        else if (_choice[0] == "help") {
            printHelp();
        }
        else if (_choice[0] == "printEvents") {
            printAllEvents();
        }
        else if (_choice[0] == "addevent") {
            addEventInHall(_choice[1], _choice[2], toInt(_choice[3]));
        }
        else if (_choice[0] == "freeseats") {
            freeseats(_choice[1], _choice[2]);
        }
        else if (_choice[0] == "book") {
            bookTicket(_choice[3], _choice[4], toInt(_choice[1]), toInt(_choice[2]));
        }
        else if (_choice[0] == "unbook") {
            unbookTicket(_choice[3], _choice[4], toInt(_choice[1]), toInt(_choice[2]));
        }
        else if (_choice[0] == "buy") {
            buyTicket(_choice[3], _choice[4], toInt(_choice[1]), toInt(_choice[2]));
        }
        else if (_choice[0] == "bookings") {
            bookings(_choice);
        }
        else if (_choice[0] == "check") {
            check(_choice[1]);
        }
        else if (_choice[0] == "report") {
            report(_choice);
        }
        else if (_choice[0] == "save") {
            if (fileNames.size() == 0) {
                std::cout << "* No files to be saved. *\n";
            }
            else {
                std::ofstream file(fileNames[fileNames.size() - 1].c_str(), std::ios::out | std::ios::trunc);
                serialize(file);
                file.close();
                std::cout << "* You have successfully saved " << fileNames[fileNames.size() - 1] << ". *\n";
            }
        }
        else if (_choice[0] == "saveas") {
            std::ofstream newFile(_choice[1].c_str(), std::ios::out);
            serialize(newFile);
            newFile.close();
            std::cout << "* You have successfully saved another " << _choice[1] << ". *\n";
        }
        else if (_choice[0] == "close") {
            if (fileNames.size() == 0) {
                std::cout << "* No files to be closed. *\n";
                commands.pop_back();
            }
            else {
                clearEvents();
                std::cout << "* You have successfully closed " << fileNames[fileNames.size() - 1] << ". *\n";
                fileNames.pop_back();
            }
        }
        else if (_choice[0] == "exit") {
            std::cout << "* Exiting... *" << std::endl;
            isOpen = false;
        }
        else {
            std::cout << "* Invalid command. Please, try again. *" << std::endl;
        }
    } 
}
