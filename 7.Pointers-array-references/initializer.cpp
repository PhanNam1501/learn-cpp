#include <iostream>
using namespace std;

// Case 1: With & (Reference)
class TestWithReference {
    int &t;  // t is a reference
public:
    TestWithReference(int &t) : t(t) {}  // Takes reference as parameter
    int getT() { return t; }
    void setT(int value) { t = value; }  // Modifies the original variable
};

// Case 2: Without & (Value/Copy)
class TestWithValue {
    int t;  // t is a value variable
public:
    TestWithValue(int t) : t(t) {}  // Takes value (copy)
    int getT() { return t; }
    void setT(int value) { t = value; }  // Only modifies the copy
};

int main() {
    cout << "=== TEST 1: With & (Reference) ===" << endl;
    int x1 = 10;
    cout << "Initial value of x1: " << x1 << endl;
    
    TestWithReference obj1(x1);  // obj1.t references x1
    cout << "obj1.getT() after initialization: " << obj1.getT() << endl;
    
    // Modify original variable
    x1 = 20;
    cout << "After changing x1 = 20:" << endl;
    cout << "  x1 = " << x1 << endl;
    cout << "  obj1.getT() = " << obj1.getT() << " (also changed!)" << endl;
    
    // Modify from within object
    obj1.setT(30);
    cout << "After obj1.setT(30):" << endl;
    cout << "  x1 = " << x1 << " (also changed!)" << endl;
    cout << "  obj1.getT() = " << obj1.getT() << endl;
    
    cout << "\n=== TEST 2: Without & (Value/Copy) ===" << endl;
    int x2 = 10;
    cout << "Initial value of x2: " << x2 << endl;
    
    TestWithValue obj2(x2);  // obj2.t is a copy of x2
    cout << "obj2.getT() after initialization: " << obj2.getT() << endl;
    
    // Modify original variable
    x2 = 20;
    cout << "After changing x2 = 20:" << endl;
    cout << "  x2 = " << x2 << endl;
    cout << "  obj2.getT() = " << obj2.getT() << " (NOT changed!)" << endl;
    
    // Modify from within object
    obj2.setT(30);
    cout << "After obj2.setT(30):" << endl;
    cout << "  x2 = " << x2 << " (NOT changed!)" << endl;
    cout << "  obj2.getT() = " << obj2.getT() << endl;
    
    cout << "\n=== CONCLUSION ===" << endl;
    cout << "Reference (&): Changes in object affect original variable" << endl;
    cout << "Value: Changes in object do NOT affect original variable" << endl;
    
    return 0;
}