#ifndef _TICKET_HH
#define _TICKET_HH

#include<string>

class Ticket { 
    std::string type;
    int row;
    int seat;
    std::string uniqueNo;

    void copy (const std::string& _type, const int& _row, const int& _seat, const std::string& _uniqueNo);

    public:
    Ticket () = default;
    Ticket (const std::string& _label, const int& _row, const int& _seat, const std::string& _uniqueNo);
    Ticket (const Ticket& other);
    Ticket& operator = (const Ticket& other);
    ~Ticket () = default;
    Ticket* clone ();

    const std::string getType () const;
    const std::string getUniqueNo () const;
    const int getRow () const;
    const int getSeat () const;

    void setType (const std::string& _type);

    ///Bool function that checks if a seat is vacant.
    bool freeSeat () const;
    ///Method used for creating an unique code when a ticket is bought.
    void createCode (int _hall, int _event, int _row, int _seat);
    ///This method gives information about a seat - the number of the seat and the row that it is on.
    void infoByCode (const std::string& _code) const;
    void printTicket () const ; 
};

#endif
