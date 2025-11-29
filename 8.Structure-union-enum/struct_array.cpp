#include <iostream>
using namespace std;

struct Array3 {
    int elem[3];

    int& operator[](size_t n) {
        return elem[n];
    }

    int* begin() noexcept {
        return elem;
    }

    const int* begin() const noexcept {
        return elem;
    }


};


template<typename T, size_t N> 
// Đây là một khuôn mẫu (template) cho phép cấu trúc array hoạt động với:
// + T: kiểu dữ liệu của các phần tử (int, double, string, struct,...)
// + N: số lượng phần tử (kích thước mảng), kiểu size_t
// --> Ví dụ : array<int, 5> sẽ là mảng gồm 5 phần tử kiểu int.

struct array {
    T elem[N]; 
    // Đây là mảng tĩnh có N phần tử kiểu T
    // Được lưu trực tiếp trong struct, không cấp phát động như vector

    T* begin() noexcept { return elem; }
    // begin() trả về con trỏ đến phần tử đầu tiên của mảng
    // bản thường: T* begin() → cho phép sửa giá trị

    const T* begin() const noexcept { return elem; }
    // bản const: const T* begin() const → dùng cho đối tượng const

    T* end() noexcept { return elem+N; }
    const T* end() const noexcept { return elem+N; }
    //Trả về con trỏ đến phần tử ngay sau phần cuối của mảng (giống chuẩn STL).
    //Dùng để duyệt bằng iterator, ví dụ trong for(auto& x: arr)

    constexpr size_t size() noexcept;
    // Hàm trả về kích thước của mảng (N).
    // constexpr: có thể đánh giá tại compile-time.
    // noexcept: đảm bảo không ném ngoại lệ.

    T& operator[](size_t n) { return elem[n]; }
    const T& operator[](size_t n) const { return elem[n]; }
    // const T& operator[](size_t n) const
    // Nạp toán tử [] để truy cập phần tử:
    // bản thường: trả về tham chiếu (cho phép chỉnh sửa)
    // bản const: trả về tham chiếu const (không cho phép chỉnh sửa)

    T* data() noexcept { return elem; }
    const T* data() const noexcept { return elem; }
    // Trả về con trỏ tới vùng nhớ chứa dữ liệu.
    // Dùng khi cần làm việc với API C hay memcpy,…
};


int main() {
    Array3 a{{1,2,3}};

    int x = a[1];            // OK
    int y = a.operator[](2); // Gọi operator[] trực tiếp => OK

    a[2] = 10;               // OK
    a.operator[](2)= 20;    // Gán qua operator[] trực tiếp => OK

    cout << x << endl;       // 2
    cout << y << endl;       // 3
    cout << a[2] << endl;    // 20

    int* t1 = a.begin();
    cout << *t1 << "\n";

    return 0;
}
