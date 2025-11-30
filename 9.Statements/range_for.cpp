#include<iostream>
#include <vector>
using namespace std;

int sum(vector<int>& v)
{
    int s = 0;
    for (int x: v) {
        s += x;
    }
    return s;
}

void fix(vector<int>& v)
{
    v[0] = 100;
    v.push_back(200);
}

void get(vector<int> v, int l)
{
    for (int i = 0; i < l; i++) {
        cout << v[i] << "\n";
    }
}

int main() 
{
    vector<int> v = {1, 2, 3};\
    cout << sum(v) << "\n";
    fix(v);
    get(v, 4);
    

}