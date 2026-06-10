// Template Method — define the skeleton of an algorithm in a base class
// and let subclasses override specific steps without changing the
// algorithm's structure.
//
// Use when several classes share the same overall workflow but differ in
// some steps (data importers, report generators, test fixtures).
//
// Build: g++ -std=c++17 template_method.cpp -o template_method

#include <iostream>
#include <string>

// The base class owns the algorithm's skeleton.
class DataImporter {
public:
    virtual ~DataImporter() = default;

    // The template method: fixed order, non-virtual on purpose.
    void run() {
        open();
        parse();
        validate();  // optional hook with a default
        save();
        close();
    }

protected:
    // Steps subclasses must provide.
    virtual void open() = 0;
    virtual void parse() = 0;

    // Hook: has a sensible default, override only if needed.
    virtual void validate() { std::cout << "  (default validation: none)\n"; }

private:
    // Steps that are identical for everyone stay private and fixed.
    void save() { std::cout << "  saving records to database\n"; }
    void close() { std::cout << "  closing source\n"; }
};

class CsvImporter : public DataImporter {
protected:
    void open() override { std::cout << "  opening data.csv\n"; }
    void parse() override { std::cout << "  parsing comma-separated rows\n"; }
};

class JsonImporter : public DataImporter {
protected:
    void open() override { std::cout << "  opening data.json\n"; }
    void parse() override { std::cout << "  parsing JSON objects\n"; }
    void validate() override { std::cout << "  validating against JSON schema\n"; }
};

int main() {
    std::cout << "CSV import:\n";
    CsvImporter{}.run();

    std::cout << "JSON import:\n";
    JsonImporter{}.run();
    return 0;
}
