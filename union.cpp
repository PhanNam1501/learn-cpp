#include <iostream>
using namespace std;

// ===== BEFORE: struct KHÔNG dùng union (lãng phí bộ nhớ) =====
enum Type { str, num };

struct Entry {
    char* name;
    Type t;
    char* s;   // nếu t == str
    int i;     // nếu t == num
};

// ===== AFTER: dùng union để tiết kiệm bộ nhớ =====
union Value {
    char* s;
    int i;
};

struct Entry2 {
    char* name;
    Type t;
    Value v;
};

int main() {
    cout << "===== SIZE COMPARISON =====\n";
    cout << "sizeof(Entry)  = " << sizeof(Entry)  << " bytes\n";
    cout << "sizeof(Entry2) = " << sizeof(Entry2) << " bytes\n";

    // ===== USE BEFORE: Không dùng union =====
    Entry e1;
    e1.name = (char*)"hello";
    e1.t = str;
    e1.s = (char*)"world";

    cout << "\n===== BEFORE: Without union =====\n";
    if (e1.t == str)
        cout << e1.name << " " << e1.s << "\n";

    // ===== USE AFTER: Dùng union =====
    Entry2 e2;
    e2.name = (char*)"foo";
    e2.t = num;
    e2.v.i = 12345;

    cout << "\n===== AFTER: Using union =====\n";
    if (e2.t == num)
        cout << e2.name << " " << e2.v.i << "\n";

    // Thay đổi sang kiểu string
    e2.t = str;
    e2.v.s = (char*)"bar";

    cout << "switched type: " << e2.name << " " << e2.v.s << "\n";
    cout << static_cast<void*>(e2.v.s);  // in địa chỉ


    return 0;
}
