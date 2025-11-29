#include <iostream>
using namespace std;

int main() {
    int a[5] = {10, 20, 30, 40, 50};

    for (int j = 0; j < 5; ++j) {
        cout << "a[" << j << "] = " << a[j] << endl;
        cout << "*(&a[0] + " << j << ") = " << *(&a[0] + j) << endl;
        cout << "*(a + " << j << ") = " << *(a + j) << endl;
        cout << "*(" << j << " + a) = " << *(j + a) << endl;
        cout << j << "[a] = " << j[a] << endl;
        cout << "----------------------\n";

    }

    cout << 4[a] << "\n";

    return 0;
}
