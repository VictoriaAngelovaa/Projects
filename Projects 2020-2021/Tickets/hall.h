#ifndef _HALL_HH
#define _HALL_HH

#include<string>
#include<vector>
#include"event.h"

class Hall {
    int hallNumber;
    int rowCount;
    std::vector<int> seatsPerRow;
    std::vector<Event*> eventsList;

    void copy (const int& _hallNumber, const int& _rowCount, 
               const std::vector<int>& _seatsPerRow, std::vector<Event*> _eventsList);
    void destroy ();

    public:
    Hall () = default;
    Hall (const int& _hallNumber, const int& _rowCount, 
          const std::vector<int>& _seatsPerRow, std::vector<Event*> _eventsList);
    Hall (const int& _hallNumber, const int& _rowCount, const std::vector<int>& _seatsPerRow);
    Hall (const Hall& otherHall);
    Hall& operator = (const Hall& otherHall);
    ~Hall ();
    Hall* clone ();

    int const getHallNumber () const; 
    int const getSeatsPerRow (const int& _row) const;

    ///This method adds a new event to the hall (to std::vector<Event*> eventsList).
    void addEvent (const std::string& _date, const std::string& _name);
    ///Returns the index of an event from the std::vector<Event*> eventsList.
    const int eventIndex (const std::string& _name, const std::string& _date) const;
    ///This method is used when a new event is added. It creates all of the tickets for the event, which at first are all vacant/free.
    void createTickets (const std::string& _date, const std::string& _name);
    ///Bool function that checks if there is such event in the hall.
    bool foundEvent (const std::string& _date, const std::string& _name) const;
    ///Bool function that checks if an event can be added on this date. It returns false if there already is another event on this date.
    bool freeDate (const std::string& _date) const;
    ///Bool function that checks if there is such seat in the hall.
    bool seatIsValid (const int& _row, const int& _seat) const;
    ///Bool function that checks if a given code is valid. It returns false if there is not a bought ticket with this unique code.
    bool foundCode (const std::string& _code) const;
    ///This method reserves a seat and sets the type of the ticket to booked.
    void bookTicketForEvent (const std::string& _date, const std::string& _name, const int& _row, const int& _seat);
    ///This method cancels a reservation for a ticket and sets the type of the ticket to free.
    void unbookTicketForEvent (const std::string& _date, const std::string& _name, const int& _row, const int& _seat);
    ///This method sets the type of a ticket to bought and creates an unique code for the ticket.
    void buyTicketForEvent (const std::string& _date, const std::string& _name, int _row, int _seat);
    
    ///This method gives information about a seat - the number of the seat and the row that it is on.
    void codeInfo (const std::string& _code) const;
    void printEvents () const;
    void serializeEvents (std::ofstream& file) const;
    void printFreeTicketsForEvent (const std::string& _date, const std::string& _name) const;
    void printBookedTickets () const;
    void printBookedTicketsForEvent (const std::string& _date, const std::string& _name) const;
    void printBookedTicketsForDate (const std::string& _date) const;
    void printBookedTicketsForName (const std::string& _name) const;
    ///Displays a reference to the bought tickets in a given period.
    void reportFromTo (const std::string& fromDate, const std::string& toDate) const;
    
    ///It is used to clear all events when the command close is called.
    void clearEvents ();
};

#endif
