#include <iostream>
#include <vector>
using namespace std;

template<class Iter, class Value>
Iter myFind(Iter first, Iter last, Value val)
{
    while (first != last && *first != val)
        ++first; //next iterator
    return first;
}

//v.begin() -> iterator

int main()
{
    vector<int> v = {1, 3, 5, 7, 9};

    auto it = myFind(v.begin(), v.end(), 5);

    //cout << it << "\n"; //error

    if (it != v.end())
        cout << "Found: " << *it << "\n";
    else
        cout << "Not found\n";

    auto it2 = myFind(v.begin(), v.end(), 100);

    if (it2 != v.end())
        cout << "Found: " << *it2 << "\n";
    else
        cout << "Not found 100\n";

    return 0;
}
