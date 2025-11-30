#include<iostream>
using namespace std;

// KHÔNG NÊN làm:
int buffer[128];  
double amount = price * 6.24; // tỉ giá

// NÊN làm:
constexpr int BUFFER_SIZE = 128;
constexpr double DKK_TO_USD = 6.24;

int buffer[BUFFER_SIZE];
double amount = price * DKK_TO_USD;
