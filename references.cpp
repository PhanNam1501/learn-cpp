#include<iostream>
using namespace std;

void f()
{
    int var = 1;
    int& r {var}; // r and var now refer to the same int
    cout << "r: " << r << "\n";
    int x = r; // x becomes 1
    r = 2;
}

void g()
{
    int var = 0;
    int& rr {var};
    ++rr;   //var is incremented to 1
    cout << "rr: " << rr << "\n";
    cout << "var: " << var << "\n";
    int* pp = &rr; // pp points to var
    cout << "pp :" << pp << "\n";
}

int main()
{
    g();
}