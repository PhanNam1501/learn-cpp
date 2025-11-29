 #include <limits>
 #include <iostream>
 #include <cstring>
 using namespace std;

 void f1()
 {
    int a2[20];            //20 ints on the stack
    int* p = new int[40];  //40 ints on the free store
 }

 void f()
{
    char p[] = "Zeno";   // p is an array of 5 char
    p[0] = 'R';          // OK
    cout << strlen(p) << "\n";
    cout << p << "\n";
}

const char* error_message(int i)
{
    return "range error";
}



 int main()
 {
    char i = 'a';
    char* t = &i;   // t là pointer trỏ tới i
    cout << static_cast<void*>(t) << "\n"; // in địa chỉ, ép kiểu để cout không in ký tự
    
    f();
    const char* c = error_message(0);
    cout << c << "\n";
    c = "nam";
    cout << c << "\n";

    const char* p = "Plato";
    cout << &p << "\n";

    const char a[] = "abcbcbc";
    cout << a << "\n";

    return 0;
 }

