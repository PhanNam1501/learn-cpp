#include<iostream>
using namespace std;

int main()
{
    int x=1, y=2;
    int j = x = y;              // x=y là lvalue, giá trị của x sau khi gán được trả về
    int* p = &++x;              // OK, ++x là lvalue
    int* q = &(x++);            // Lỗi, x++ là rvalue, không có địa chỉ
    int* p2 = &(x>y ? x : y);   // OK nếu cả x và y là lvalue cùng kiểu
    int& r = (x<y ? x : 1);     // Lỗi, 1 không phải lvalue
}