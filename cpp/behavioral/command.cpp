// ☕ Café Patterna — Chapter 14: Tickets on the Rail
//
// STORY: The cashier doesn't shout orders into the kitchen — every order
// becomes a TICKET clipped to the rail. The kitchen executes tickets in
// its own time, and when a customer changes their mind, the last ticket
// is simply pulled off the rail (undo).
//
// PATTERN: Command — encapsulate a request as an object, letting you
// queue requests, log them, and support undo. Decouples the object that
// invokes an operation (cashier) from the one performing it (kitchen).
//
// Build: g++ -std=c++17 command.cpp -o command

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Receiver: the object that actually does the work.
class Kitchen {
public:
    void prepare(const std::string& item) { std::cout << "kitchen starts: " << item << "\n"; }
    void scrap(const std::string& item) { std::cout << "kitchen scraps: " << item << "\n"; }
};

// Command interface with undo support.
class OrderTicket {
public:
    virtual ~OrderTicket() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class DrinkTicket : public OrderTicket {
public:
    DrinkTicket(Kitchen& kitchen, std::string drink)
        : kitchen_(kitchen), drink_(std::move(drink)) {}
    void execute() override { kitchen_.prepare(drink_); }
    void undo() override { kitchen_.scrap(drink_); }

private:
    Kitchen& kitchen_;
    std::string drink_;
};

class PastryTicket : public OrderTicket {
public:
    PastryTicket(Kitchen& kitchen, std::string pastry)
        : kitchen_(kitchen), pastry_(std::move(pastry)) {}
    void execute() override { kitchen_.prepare(pastry_); }
    void undo() override { kitchen_.scrap(pastry_); }

private:
    Kitchen& kitchen_;
    std::string pastry_;
};

// Invoker: clips tickets to the rail and keeps a history for cancellation.
class TicketRail {
public:
    void place(std::unique_ptr<OrderTicket> ticket) {
        ticket->execute();
        history_.push_back(std::move(ticket));
    }

    void cancelLast() {
        if (history_.empty()) return;
        history_.back()->undo();
        history_.pop_back();
    }

private:
    std::vector<std::unique_ptr<OrderTicket>> history_;
};

int main() {
    Kitchen kitchen;
    TicketRail rail;

    rail.place(std::make_unique<DrinkTicket>(kitchen, "oat latte"));
    rail.place(std::make_unique<PastryTicket>(kitchen, "almond croissant"));

    std::cout << "-- customer changes their mind --\n";
    rail.cancelLast();
    return 0;
}
