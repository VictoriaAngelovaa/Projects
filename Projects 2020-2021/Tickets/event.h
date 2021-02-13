#ifndef _EVENT_HH
#define _EVENT_HH

#include"ticket.h"
#include<string>
#include<vector>


class Event {
    std::string name;
    std::string date;
    std::vector<Ticket*> tickets;

    void copy (const std::string& _name, const std::string& _date, std::vector<Ticket*> _tickets);
    void destroy();
    
    public:
    Event () = default;
    Event (const std::string& _name, const std::string& _date, std::vector<Ticket*> _tickets);
    Event (const Event& other);
    Event (const std::string& _date, const std::string& _name);
    Event& operator = (const Event& other);
    ~Event ();
    Event* clone ();

    const std::string getName () const;
    const std::string getDate () const;

    ///This setter is used when a new event is added. It creates all of the tickets for the event, which at first are all vacant/free.
    void setTickets (std::vector<Ticket*> _tickets);

    ///Returns the index of a ticket from the std::vector<Ticket*> tickets.
    const int ticketIndex (const int& _row, const int& _seat) const;
    ///Bool function that checks if a seat is vacant.
    bool seatIsFree (const int& _row, const int& _seat) const;
    ///Bool function that checks if a given code is valid. It returns false if there is not a bought ticket with this unique code.
    bool foundCode (const std::string& _code) const;
    ///This method reserves a seat and sets the type of the ticket to booked.
    void bookTicket (const int& _row, const int& _seat);
    ///This method cancels a reservation for a ticket and sets the type of the ticket to free.
    void unbookTicket (const int& _row, const int& _seat);
    ///This method sets the type of a ticket to bought and creates an unique code for the ticket.
    void buyTicket (int _hall, int _event, int _row, int _seat);
    ///This method is used to count how many tickets are booked or bought.
    int countTickets (const std::string& _type) const;

    ///This method gives information about a seat - the number of the seat and the row that it is on.
    void infoByCode (const std::string& _code) const;
    void printEvent () const;
    void serialize (std::ofstream& file) const;
    void printTickets () const;
    void printFreeTickets () const;
    void printBookedTickets () const;
};

#endif
