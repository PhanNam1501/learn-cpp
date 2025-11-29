#include <iostream>

enum class Warning {
    green,
    yellow,
    orange,
    red
};

int main() {
    std::cout << "green  = " << static_cast<int>(Warning::green)  << "\n";
    std::cout << "yellow = " << static_cast<int>(Warning::yellow) << "\n";
    std::cout << "orange = " << static_cast<int>(Warning::orange) << "\n";
    std::cout << "red    = " << static_cast<int>(Warning::red)    << "\n";
}
