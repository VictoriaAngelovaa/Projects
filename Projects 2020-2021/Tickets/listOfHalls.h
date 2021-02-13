#ifndef _LISTOFHALLS_HH
#define _LISTOFHALLS_HH

#include"hall.h"
#include<vector>
#include<string>

class ListOfHalls {
    std::vector<Hall*> halls;

    void copy (std::vector<Hall*> _halls);
    void destroy ();

    public:
    ListOfHalls () = default;
    ListOfHalls (std::vector<Hall*> _halls);
    ListOfHalls (const ListOfHalls& other);
    ListOfHalls& operator = (const ListOfHalls& other);
    ~ListOfHalls ();

    ///This method creates halls based on the information in the file, i.e. how many rows are in each hall and how many seats are on each row.
    bool loadHalls (const std::string& fileName);
    ///This method adds events based on the information in the file, i.e. names and dates of the events and the halls in which they are going to be performed.
    void loadEvents (const std::string& fileName);

    ///Returns the index of a hall from the std::vector<Hall*> halls based on a given hall number.
    const int findIndexByNumber (const int& _number) const;
    ///Checks in which hall the given event is going to be performed and returns the index of the hall from std::vector<Hall*> halls.
    const int hallIndexByEvent (const std::string& _date, const std::string& _name) const;
    ///This method adds a new event to a hall.
    void addEventInHall (const std::string& _date, const std::string& _name, const int& _hallNumber);
    ///Reserves a seat _seat on row _row for the event _name on date _date.
    void bookTicket (const std::string& _date, const std::string& _name, const int& _row, const int& _seat);
    ///Canceles a reservation for a seat _seat on row _row for the event _name on date _date.
    void unbookTicket (const std::string& _date, const std::string& _name, const int& _row, const int& _seat);
    ///Buys a ticket for a seat _seat on row _row for the event with name _name on date _date.
    void buyTicket (const std::string& _date, const std::string& _name, const int& _row, const int& _seat);

    ///Prints all of the supported commands.
    void printHelp () const;
    ///Shows all free seats for a given event.
    void freeseats (const std::string& _date, const std::string& _name) const;
    ///Shows all booked seats for a given event/date/name or all of the booked seats in each hall for every event if the date and name are not specified.
    void bookings (const std::vector<std::string>& info) const;
    ///This method gives information about a seat based on a given code - the number of the seat and the row that it is on.
    void check (const std::string& _code) const;
    ///Shows all of the the number of bought tickets for each event in a hall in a given period of time or in all of the halls if the hall number is not specified.
    void report (const std::vector<std::string>& info) const;
    void printAllEvents () const;
    ///Saves the information about each event in a file.
    void serialize (std::ofstream& file) const;

    ///It is used to clear all events when the command close is called.
    void clearEvents ();

    void run ();
};

#endif
