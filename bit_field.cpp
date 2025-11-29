#include <iostream>
using namespace std;

// Struct dùng bit-field
struct BitField {
    unsigned int a : 1;
    unsigned int b : 2;
    unsigned int c : 3;
    unsigned int d : 1;
    unsigned int e : 1;
};

// Struct dùng biến bình thường
struct Normal {
    bool a;
    char b;
    char c;
    bool d;
    bool e;
};

int main() {
    cout << "Size of BitField = " << sizeof(BitField) << " bytes\n";
    cout << "Size of Normal   = " << sizeof(Normal)   << " bytes\n";

    BitField bf{};
    bf.a = 1;
    bf.b = 3;
    bf.c = 5;
    bf.d = 1;
    bf.e = 0;

    cout << "\nBitField values:\n";
    cout << "a=" << bf.a << " b=" << bf.b << " c=" << bf.c
         << " d=" << bf.d << " e=" << bf.e << endl;

    return 0;
}
