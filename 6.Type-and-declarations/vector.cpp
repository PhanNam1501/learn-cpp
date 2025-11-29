#include <iostream>
#include <vector>
using namespace std;

int main() 
{
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);

    int firstElement = vec[0];
    int secondElement = vec.at(1);

    cout << firstElement << "\n";
    cout << secondElement;
}
