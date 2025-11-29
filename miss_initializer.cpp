#include <iostream>
using namespace std;

int main() {
    // Cấp phát 1 int
    int* p {new int{10}};
    cout << "*p = " << *p << endl;  // Output: *p = 10
    // 1. *p  → Giá trị mà p trỏ đến (dereference)
    // 2. p   → Địa chỉ mà p lưu (địa chỉ của biến trên heap)
    // 3. &p  → Địa chỉ của biến con trỏ p (địa chỉ của p trên stack)
    
    // Cấp phát mảng char
    char* q {new char[1024]{}};
    cout << "q[0] = " << (int)q[0] << endl;  // Output: q[0] = 0
    cout << "q[100] = " << (int)q[100] << endl;  // Output: q[100] = 0
    
    // Thay đổi giá trị
    *p = 20;
    q[0] = 'A';
    q[1] = 'B';
    
    cout << "*p = " << *p << endl;  // Output: *p = 20
    cout << "q[0] = " << q[0] << endl;  // Output: q[0] = A
    
    // QUAN TRỌNG: Phải giải phóng bộ nhớ!
    delete p;      // Giải phóng 1 biến
    delete[] q;    // Giải phóng mảng (phải dùng delete[])
    
    return 0;
}