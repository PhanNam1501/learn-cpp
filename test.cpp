 #include <limits>
 #include <iostream>
 using namespace std;
 // §40.2
 int main()
 {
    struct A { int x; };
    struct B { double y; };

    A a{10};
    B* b = reinterpret_cast<B*>(&a);
    cout << b->y;   // UB — đọc sai kiểu

 }