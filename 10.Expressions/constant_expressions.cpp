#include<iostream>
using namespace std;

int x1 = 7;           // Biến thường, run-time
constexpr int x2 = 7; // Hằng compile-time

constexpr int x3 = x1; // ❌ lỗi, x1 không phải constant expression
constexpr int x4 = x2; // ✅ OK, x2 là hằng compile-time


void f() {
    constexpr int y3 = x1; // ❌ lỗi
    constexpr int y4 = x2; // ✅ OK
}