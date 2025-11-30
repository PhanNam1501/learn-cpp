#include<iostream>
using namespace std;


void print_backwards(char a[], int i)
{
    cout << '{';
    do {
        cout << a[--i];
    } while (i);
    cout << '}';
}