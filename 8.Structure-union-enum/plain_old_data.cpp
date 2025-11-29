#include <iostream>
#include <cstring>
#include <type_traits>
using namespace std;

template<typename T>
void mycopy(T* to, const T* from, int count) {
    if (is_pod<T>::value) {
        cout << "Using memcpy (POD)\n";
        memcpy(to, from, count * sizeof(T));
    } else {
        cout << "Using element-by-element copy (non-POD)\n";
        for (int i = 0; i < count; ++i)
            to[i] = from[i];
    }
}

// ------------------- KIỂU POD -------------------
struct PointPOD {
    int x, y;
};

// ------------------- KIỂU NON-POD -------------------
struct PointNonPOD {
    int x, y;
    PointNonPOD(int xx = 0, int yy = 0) : x(xx), y(yy) {}

    // Copy constructor TỰ ĐỊNH NGHĨA → không còn là POD
    PointNonPOD(const PointNonPOD& other) {
        cout << "Calling user-defined copy constructor\n";
        x = other.x;
        y = other.y;
    }
};

int main() {

    cout << "===== Copy POD (PointPOD) =====\n";
    PointPOD a[3] = {{1,2}, {3,4}, {5,6}};
    PointPOD b[3];

    mycopy(b, a, 3);

    for (auto& p : b)
        cout << "(" << p.x << "," << p.y << ")\n";


    cout << "\n===== Copy NON-POD (PointNonPOD) =====\n";
    PointNonPOD c[3] = {{7,8}, {9,10}, {11,12}};
    PointNonPOD d[3];

    mycopy(d, c, 3);

    for (auto& p : d)
        cout << "(" << p.x << "," << p.y << ")\n";

    return 0;
}
