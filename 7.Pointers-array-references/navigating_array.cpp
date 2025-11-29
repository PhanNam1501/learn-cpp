#include<iostream>
using namespace std;

template<typename T>
int byte_diff(T* p, T* q)
{
    // cout<<reinterpret_cast<char*>(q)<<"\n";
    // cout<<reinterpret_cast<char*>(p)<<"\n";
    return reinterpret_cast<int*>(q) - reinterpret_cast<int*>(p);
}

void diff_test()
{
    int vi[10]; // *(vi + 1) 
    short vs[10]; // 2

    cout << vi << ' ' << &vi[1] << ' ' << &vi[1] - &vi[0] << ' ' << byte_diff(&vi[0],&vi[1]) << '\n';
    cout << vs << ' ' << &vs[1] << ' ' << &vs[1] - &vs[0] << ' ' << byte_diff(&vs[0],&vs[1]) << '\n';

}

void f()
{
    int v1[10];
    int v2[10];
    int i1 = &v1[5] - &v1[3]; //i1 = 2
    int i2 = &v1[5] - &v2[3]; //result undefined
    int*p1 = v2 + 2; //p1 = &v2[2]
    int*p2 = v2 - 2; //*p2 undefined

}

int main()
{
    diff_test();
}