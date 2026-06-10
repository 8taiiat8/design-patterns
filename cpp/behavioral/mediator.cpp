// Mediator — define an object that encapsulates how a set of objects
// interact, so they don't reference each other directly.
//
// Use when many objects communicate in complex ways (chat rooms, UI forms,
// air traffic control); the mediator turns many-to-many links into
// one-to-many.
//
// Build: g++ -std=c++17 mediator.cpp -o mediator

#include <iostream>
#include <string>
#include <vector>

class User;

// Mediator interface
class ChatRoom {
public:
    virtual ~ChatRoom() = default;
    virtual void broadcast(const std::string& from, const std::string& message) = 0;
    virtual void join(User* user) = 0;
};

// Colleague: only knows the mediator, not the other users.
class User {
public:
    User(std::string name, ChatRoom& room) : name_(std::move(name)), room_(room) {
        room_.join(this);
    }

    const std::string& name() const { return name_; }

    void send(const std::string& message) {
        std::cout << name_ << " sends: " << message << "\n";
        room_.broadcast(name_, message);
    }

    void receive(const std::string& from, const std::string& message) {
        std::cout << "  " << name_ << " receives from " << from << ": " << message << "\n";
    }

private:
    std::string name_;
    ChatRoom& room_;
};

// Concrete mediator: routes messages between registered users.
class SimpleChatRoom : public ChatRoom {
public:
    void join(User* user) override { users_.push_back(user); }

    void broadcast(const std::string& from, const std::string& message) override {
        for (User* user : users_) {
            if (user->name() != from) user->receive(from, message);
        }
    }

private:
    std::vector<User*> users_;
};

int main() {
    SimpleChatRoom room;
    User alice("Alice", room);
    User bob("Bob", room);
    User carol("Carol", room);

    alice.send("hi everyone!");
    bob.send("hey Alice");
    return 0;
}
