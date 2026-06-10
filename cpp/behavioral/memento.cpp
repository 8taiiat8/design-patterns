// Memento — capture an object's internal state in a snapshot object so it
// can be restored later, without exposing the object's internals.
//
// Use for undo, checkpoints, and transactional rollback. The originator
// creates/restores mementos; the caretaker stores them but never looks
// inside.
//
// Build: g++ -std=c++17 memento.cpp -o memento

#include <iostream>
#include <string>
#include <vector>

// Originator: the object whose state we want to snapshot.
class TextEditor {
public:
    // Memento: opaque to everyone except the originator.
    class Snapshot {
        friend class TextEditor;
        explicit Snapshot(std::string text) : text_(std::move(text)) {}
        std::string text_;
    };

    void type(const std::string& words) {
        text_ += words;
    }

    Snapshot save() const { return Snapshot(text_); }
    void restore(const Snapshot& snapshot) { text_ = snapshot.text_; }

    void show() const { std::cout << "editor: \"" << text_ << "\"\n"; }

private:
    std::string text_;
};

// Caretaker: manages history without knowing what's inside a Snapshot.
class History {
public:
    void push(TextEditor::Snapshot snapshot) { stack_.push_back(std::move(snapshot)); }

    bool undo(TextEditor& editor) {
        if (stack_.empty()) return false;
        editor.restore(stack_.back());
        stack_.pop_back();
        return true;
    }

private:
    std::vector<TextEditor::Snapshot> stack_;
};

int main() {
    TextEditor editor;
    History history;

    editor.type("Hello");
    history.push(editor.save());

    editor.type(", world");
    history.push(editor.save());

    editor.type("!!! oops, typo");
    editor.show();

    history.undo(editor);  // back to "Hello, world"
    editor.show();

    history.undo(editor);  // back to "Hello"
    editor.show();
    return 0;
}
