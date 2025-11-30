#include<iostream>
using namespace std;


void f(int i)
{
    switch (i) {
    case 2:
        cout << "2\n";
        break;
    //case 2.7: error: floating point uses for case
    //case 4-2: error: 2 used twice in case labels
    case 3:
        cout << "3\n";
        break;
    }
}

int main()
{
    f(2);
    f(3);
}