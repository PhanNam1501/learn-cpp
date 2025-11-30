# Literal Types trong C++

## 1. "Literal Type" là gì?

Trong C++:

👉 **Literal type** = một kiểu dữ liệu đủ đơn giản để có thể xuất hiện trong constant expression.

Nghĩa là:

+ Bạn có thể tạo object của nó tại compile-time bằng `constexpr`.

+ Các kiểu built-in như `int`, `double`, `char`, `bool`, `nullptr_t`, `enum` → đều là literal type.

+ Nhưng C++ cho phép cả user-defined types (struct/class) cũng có thể trở thành literal type, nếu chúng đủ đơn giản.

## 2. Khi nào một class/struct được xem là "literal type"?

### Các điều kiện cơ bản (C++11):

✔ **1. Có constexpr constructor**

Constructor phải:

+ có body rỗng (empty body `{}`),

+ mọi member phải được init trong initializer list bằng potentially constant expressions.

✔ **2. Các member phải là literal types**

+ Ví dụ `int`, `double`, `char`, hoặc một literal type khác.

✔ **3. Không được dùng tính năng phức tạp**

+ Ví dụ: `virtual`, destructor không `constexpr`, pointer lạ, allocation, I/O… đều không hợp lệ.

## 3. Ví dụ trong sách

Ta có:

```cpp
struct Point {
    int x, y, z;
    constexpr Point up(int d) { return {x, y, z + d}; }
    constexpr Point move(int dx, int dy) { return {x + dx, y + dy, z}; }
};
```

Đây là literal type vì:

+ Members: `int x, y, z` → literal types.

+ Các hàm member `constexpr` → không thay đổi state, chỉ trả về đối tượng mới.

## 4. Sử dụng literal type trong constant expression

```cpp
constexpr Point origo {0, 0};
constexpr int z = origo.x;
```

`origo` tạo tại compile-time → truy cập thành viên được.

## 5. constexpr array of literal types

```cpp
constexpr Point a[] = {
    origo,
    Point{1, 1},
    Point{2, 2},
    origo.move(3, 3)
};
```

✔ `Point` là literal type

✔ constructor `constexpr`

✔ function `move()` là `constexpr`

**==> Array `a` được tạo tại compile-time.**

Lấy phần tử:

```cpp
constexpr int x = a[1].x;  // x = 1
```

+ Compiler evaluate tại compile-time.

## 6. Khi nào không được constexpr?

```cpp
constexpr Point xy{0, sqrt(2)};
```

⚠ **ERROR:**

`sqrt(2)` không phải là `constexpr` function

→ `xy` không thể được evaluate tại compile-time.

## 7. constexpr member function mặc định là const

Điểm cực kỳ quan trọng:

+ Một member function mà bạn đánh dấu `constexpr` tự động được xem là `const`.

Nghĩa là nó không được phép thay đổi object hiện tại.

Do đó:

```cpp
constexpr Point move(int dx, int dy) const { ... }
```

Dòng `const` là thừa → compiler tự thêm.

## 8. constexpr function hoạt động với literal type

```cpp
constexpr int square(int x) {
    return x * x;
}

constexpr int radial_distance(Point p) {
    return isqrt(square(p.x) + square(p.y) + square(p.z));
}
```

`Point` là literal type → truyền vào `constexpr` function được.

## 9. Ví dụ compile-time hoàn chỉnh

```cpp
constexpr Point p1{10, 20, 30};
constexpr Point p2{p1.up(20)};
constexpr int dist = radial_distance(p2);
```

✔ `p1` compile-time

✔ `p2` compile-time

✔ `dist` compile-time

Compiler tính tất cả trước khi chương trình chạy.

## 10. Tóm tắt dễ nhớ

### Literal type

→ loại type mà compiler có thể tạo instance tại compile-time.

### Điều kiện chính

+ `constexpr` constructor (body rỗng)

+ members là literal type

+ không có behavior runtime phức tạp

+ các hàm `constexpr` tự là `const`

### Ứng dụng

+ Tạo object compile-time

+ `constexpr` arrays

+ params cho template

+ biểu thức math compile-time

---

## Zero-Cost Abstraction

Literal types là một ví dụ điển hình của **zero-cost abstraction** trong C++:

+ Bạn viết code high-level, dễ đọc với struct/class

+ Nhưng compiler tối ưu hóa hoàn toàn tại compile-time

+ Không có overhead runtime

+ Performance giống như viết raw code với các giá trị hard-coded

