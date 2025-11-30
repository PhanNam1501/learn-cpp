#include<iostream>
using namespace std;


int max(int a, int b)
{
    return (a > b) ? a : b;
}

enum E1 { a, b };
enum class E2 { a, b };

void f(E1 x, E2 y)
{
    if (x) {
        cout << "x\n"; 
    }
    //if (y) //error: no conversion to bool
    if (y == E2::a)
    {
        cout << "y\n";
    }
}

int main()
{
    f(E1::b, E2::a);
}