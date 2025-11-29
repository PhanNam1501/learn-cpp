#include <iostream>

int main() {
    // Unnamed enum (enum vô danh)
    enum { arrow_up = 1, arrow_down, arrow_sideways };

    // Sử dụng hằng số trực tiếp
    int move = arrow_up;
    std::cout << "Move code: " << move << std::endl;

    move = arrow_down;
    std::cout << "Move code: " << move << std::endl;

    move = arrow_sideways;
    std::cout << "Move code: " << move << std::endl;

    // Thử dùng trong điều kiện
    int input = 2;
    if (input == arrow_down) {
        std::cout << "Input corresponds to arrow_down\n";
    }

    return 0;
}
