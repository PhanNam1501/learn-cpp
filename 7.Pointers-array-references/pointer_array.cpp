#include<iostream>
using namespace std;

int main()
{
    int v[] = { 1, 2, 3, 4 };
    int* p1 = v;      //pointer to initial element
    int* p2 = &v[0];  //pointer to initial element
    int* p3 = v + 4;  //pointer to one-beyond-last element
    int* p4 = v - 1;  //before the beginning, undefined: don't do it
    int* p5 = v + 7;  //beyond the end, undefined: don't do it
}