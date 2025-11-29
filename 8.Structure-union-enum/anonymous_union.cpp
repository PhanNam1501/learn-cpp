#include <iostream>
#include <string>
#include <stdexcept>

class Entry2 {
private:
    enum class Tag { number, text };
    Tag type;  // type tag (discriminant)

    // Anonymous union
    union {
        int i;
        std::string s;  // string có constructor/destructor
    };

public:
    // Constructor cho int
    Entry2(int n) : type(Tag::number), i(n) {}

    // Constructor cho string
    Entry2(const std::string& str) : type(Tag::text), s(str) {}

    // Copy constructor
    Entry2(const Entry2& e) : type(e.type) {
        if (type == Tag::number) i = e.i;
        else new(&s) std::string(e.s); // placement new cho string
    }

    // Destructor
    ~Entry2() {
        if (type == Tag::text) this->s.std::string::~string(); // explicit destroy nếu string active
    }

    // Assignment operator
    Entry2& operator=(const Entry2& e) {
        if (this == &e) return *this;

        if (type == Tag::text) this->s.std::string::~string(); // destroy old string

        type = e.type;
        if (type == Tag::number) i = e.i;
        else new(&s) std::string(e.s); // placement new

        return *this;
    }

    // Accessors
    int number() const {
        if (type != Tag::number) throw std::runtime_error("Not a number");
        return i;
    }

    std::string text() const {
        if (type != Tag::text) throw std::runtime_error("Not text");
        return s;
    }

    // Mutators
    void set_number(int n) {
        if (type == Tag::text) this->s.std::string::~string(); // destroy old string
        i = n;
        type = Tag::number;
    }

    void set_text(const std::string& str) {
        if (type == Tag::text) s = str;          // assign to existing string
        else new(&s) std::string(str);          // placement new
        type = Tag::text;
    }
};

int main() {
    Entry2 e1(42);              // int
    Entry2 e2("Hello World");   // string

    std::cout << "Number: " << e1.number() << "\n";
    std::cout << "Text: " << e2.text() << "\n";

    // Gán giá trị mới
    e1.set_text("Now a string!");
    std::cout << "e1 as text: " << e1.text() << "\n";

    e2.set_number(100);
    std::cout << "e2 as number: " << e2.number() << "\n";

    return 0;
}
