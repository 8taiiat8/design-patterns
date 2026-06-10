// ☕ Café Patterna — Chapter 18: The Chalkboard Specials
//
// STORY: Every morning you draft today's specials on the chalkboard.
// Before each risky idea ("durian latte"?) you photograph the board.
// When an idea flops, you restore the board from the last photo. The
// photos go in a drawer — whoever keeps them never reads the board off
// of them, they just hand them back.
//
// PATTERN: Memento — capture an object's internal state in a snapshot so
// it can be restored later, without exposing the object's internals.
// Originator = chalkboard, memento = photo, caretaker = the drawer.
//
// Build: g++ -std=c++17 memento.cpp -o memento

#include <iostream>
#include <string>
#include <vector>

// Originator: the object whose state we want to snapshot.
class Chalkboard {
public:
    // Memento: opaque to everyone except the originator.
    class Photo {
        friend class Chalkboard;
        explicit Photo(std::string text) : text_(std::move(text)) {}
        std::string text_;
    };

    void write(const std::string& chalk) { text_ += chalk; }

    Photo snap() const { return Photo(text_); }
    void restore(const Photo& photo) { text_ = photo.text_; }

    void show() const { std::cout << "chalkboard: \"" << text_ << "\"\n"; }

private:
    std::string text_;
};

// Caretaker: stores photos without knowing what's on them.
class PhotoDrawer {
public:
    void keep(Chalkboard::Photo photo) { stack_.push_back(std::move(photo)); }

    bool undo(Chalkboard& board) {
        if (stack_.empty()) return false;
        board.restore(stack_.back());
        stack_.pop_back();
        return true;
    }

private:
    std::vector<Chalkboard::Photo> stack_;
};

int main() {
    Chalkboard board;
    PhotoDrawer drawer;

    board.write("TODAY: flat white $3");
    drawer.keep(board.snap());

    board.write(" | pumpkin latte $4");
    drawer.keep(board.snap());

    board.write(" | durian latte $6");  // bold. too bold.
    board.show();

    drawer.undo(board);  // scrap the durian idea
    board.show();

    drawer.undo(board);  // back to just the flat white
    board.show();
    return 0;
}
