# Constexpr và Reference trong C++

## 📌 1. Tại sao constexpr "không thích" reference?

`constexpr` nghĩa là mọi thứ phải được xác định hoàn toàn tại compile-time.

Reference bình thường (`T&`) lại là địa chỉ của một biến, mà địa chỉ thì:

- thay đổi theo runtime
- không phải là "giá trị thuần"
- compiler không đảm bảo được ở compile-time

👉 **Vì thế:** non-const reference không thể dùng trong constexpr.

## 📌 2. Nhưng tại sao const reference lại dùng được?

Vì `const T&` có thể bind vào một temporary constant expression, mà temporary thì compiler được phép tối ưu và coi như một giá trị cố định.

### Ví dụ:

```cpp
constexpr complex<float> z1{1, 2};
constexpr double re = z1.real();
constexpr double im = z1.imag();
constexpr complex<double> z2{re, im};
constexpr complex<double> z3{z1}; // dùng const reference
```

Trong constructor:

```cpp
constexpr complex(const complex<float>&);
```

Reference chỉ dùng để đọc giá trị của `z1` — mà `z1` là constexpr, tức hoàn toàn cố định tại compile time.

Compiler thấy reference trỏ vào 1 giá trị bất biến, nên nó bỏ qua reference và xử lý như kiểu:

```cpp
constexpr complex<double> z3 { (double)z1.real(), (double)z1.imag() };
```

**Không hề có address, không có pointer thật sự.**  
Compiler copy bằng giá trị → đáp ứng đúng yêu cầu của constexpr.

## 📌 3. Các hàm nào không được là constexpr?

Các hàm thay đổi state/giá trị thì không thể là constexpr, ví dụ:

```cpp
void real(double);
void imag(double);
complex<double>& operator=(double);
complex<double>& operator+=(double);
```

Vì constexpr bắt buộc phải:

- không có side-effects
- không mutate object

## 📌 4. Các hàm nào được là constexpr?

Các hàm chỉ đọc giá trị, ví dụ:

```cpp
constexpr double real();
constexpr double imag();
```

Nếu object là constexpr, các hàm này có thể chạy ngay tại compile time.

## 📌 5. Ý nghĩa chính của đoạn này

`constexpr` cho phép lập trình hàm đầy đủ tại compile-time, không chỉ integer như template-metaprogramming truyền thống.

Reference chỉ được phép trong constexpr khi:

- reference là `const T&`
- reference bind tới một constant expression
- compiler dùng giá trị, không dùng địa chỉ.

## 📌 6. Giải thích bằng ví dụ ngắn gọn

### ❌ Không được:

```cpp
constexpr int& bad() {
    static int x = 5;
    return x;            // constexpr không được chứa reference đến object mutable
}
```

### ✔ Được:

```cpp
constexpr int f(const int& x) {
    return x * 2;        // chỉ đọc giá trị, OK
}

constexpr int y = f(5);  // chạy tại compile time
```

