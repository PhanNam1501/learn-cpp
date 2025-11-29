 #include <limits>
 #include <iostream>
 using namespace std;
 // §40.2
 int main()
 {
    int v[] = {1, 2, 3, 4};
    int* p1 = v; //v = &v[0]
   //  int* p2 = &v[0];
   //  int* p3 = v + 4;


    int* ap[15];
    ap[1] = p1;
    cout << &v << "\n";
    cout << ap[0] << "\n";
    cout << ap << "\n";
    cout << *(ap + 1);

 }