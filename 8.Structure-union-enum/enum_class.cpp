#include <iostream>

enum class Printer_flags {
    acknowledge = 1,
    paper_empty = 2,
    busy = 4,
    out_of_black = 8,
    out_of_color = 16,
};

constexpr Printer_flags operator|(Printer_flags a, Printer_flags b)
{
    return static_cast<Printer_flags>(
        static_cast<int>(a) | static_cast<int>(b));
}

constexpr Printer_flags operator&(Printer_flags a, Printer_flags b)
{
    return static_cast<Printer_flags>(
        static_cast<int>(a) & static_cast<int>(b));
}

constexpr bool any(Printer_flags f) {
    return static_cast<int>(f) != 0;
}

void try_to_print(Printer_flags x)
{
    if (any(x & Printer_flags::acknowledge)) {
        std::cout << "acknowledge\n";
    }
    else if (any(x & Printer_flags::busy)) {
        std::cout << "busy\n";
    }
    else if (any(x & (Printer_flags::out_of_black | Printer_flags::out_of_color))) {
        std::cout << "het muc\n";
    }

    std::cout << any(Printer_flags::out_of_black | Printer_flags::out_of_color) << "\n";
}

int main() {
    try_to_print(Printer_flags::busy);
    try_to_print(Printer_flags::out_of_black);
}
