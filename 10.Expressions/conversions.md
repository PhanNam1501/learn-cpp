# 10.5.2 Chuyển đổi kiểu (Conversions)

Các kiểu dữ liệu cơ bản (fundamental types) có thể chuyển đổi ngầm định (implicit conversion) lẫn nhau theo nhiều cách khác nhau.

**Tác giả nhận xét:** C++ cho phép quá nhiều kiểu chuyển đổi, đôi khi nguy hiểm.

## Ví dụ

```cpp
void f(double d) {
    char c = d;  // chú ý: chuyển từ double → char
}
```

Chuyển từ double sang char có thể làm mất dữ liệu (narrowing conversion).

Khi viết code, nên tránh các hành vi undefined và các conversion âm thầm làm mất thông tin.

May mắn là nhiều compiler sẽ cảnh báo các chuyển đổi nghi vấn.

Cú pháp `{}` initializer sẽ ngăn narrowing:

```cpp
void f(double d) {
    char c {d};  // error: narrowing conversion
}
```

Nếu không thể tránh narrowing, có thể dùng run-time checked conversion như `narrow_cast<>()`.

## 10.5.2.1 Integral Conversions (chuyển số nguyên)

Một số nguyên có thể được chuyển sang kiểu nguyên khác.

Một giá trị enum có thể được chuyển sang kiểu nguyên tương ứng.

### Chuyển sang kiểu unsigned:

- Giá trị sẽ giữ các bit thấp đủ để vừa trong kiểu đích
- Các bit cao bị bỏ đi nếu cần
- Nói cách khác: kết quả là số nguyên không dấu modulo 2^n (n = số bit kiểu unsigned)

**Ví dụ:**

```cpp
unsigned char uc = 1023;  
// binary: 1111111111 → uc = 11111111 = 255
```

### Chuyển sang kiểu signed:

- Nếu giá trị có thể biểu diễn trong kiểu đích → giữ nguyên
- Nếu không → implementation-defined (có thể khác nhau giữa compiler)

**Ví dụ:**

```cpp
signed char sc = 1023; 
// có thể là 127 hoặc -1 tùy compiler
```

`bool` hoặc `enum` cũng có thể chuyển ngầm định sang giá trị nguyên.

## 10.5.2.2 Floating-Point Conversions (chuyển số thực)

Một số thực có thể chuyển sang số thực khác (float → double, double → long double...).

- Nếu giá trị gốc được biểu diễn chính xác → giữ nguyên
- Nếu nằm giữa hai giá trị kiểu đích → lấy một trong hai giá trị gần nhất
- Nếu không thể → undefined behavior

**Ví dụ:**

```cpp
float f = FLT_MAX;       // lớn nhất float
double d = f;            // OK: d = f

double d2 = DBL_MAX;     // lớn nhất double
float f2 = d2;           // undefined nếu d2 > FLT_MAX

long double ld = d2;     // OK
long double ld2 = std::numeric_limits<long double>::max();
double d3 = ld2;         // undefined nếu sizeof(long double) > sizeof(double)
```

`FLT_MAX`, `DBL_MAX` được định nghĩa trong `<climits>` hoặc `<limits>`.

## 10.5.2.3 Pointer and Reference Conversions (con trỏ và reference)

- Con trỏ đến bất kỳ kiểu object nào → ngầm định chuyển sang `void*`
- Con trỏ (hoặc reference) đến lớp kế thừa → ngầm định chuyển sang con trỏ (reference) lớp cơ sở nếu accessible & unambiguous

**Lưu ý:** con trỏ hàm hoặc con trỏ member không thể chuyển sang `void*`

- `0` constant expression → ngầm định chuyển thành null pointer
- Tương tự, `0` có thể chuyển thành pointer-to-member type

**Ví dụ:**

```cpp
int* p = (1+2)*(2*(1-1));  // OK nhưng kỳ lạ
```

Nên dùng `nullptr` thay vì `0`

Chuyển `T → const T**` và `T& → const T&` cũng được phép.

## 10.5.2.4 Pointer-to-Member Conversions

Con trỏ hoặc reference tới member → chuyển đổi như §20.6.3 (cũng là ngầm định)

## 10.5.2.5 Boolean Conversions

Con trỏ, số nguyên, số thực → ngầm định chuyển sang `bool`

- `0` → `false`, khác `0` → `true`

**Ví dụ:**

```cpp
void f(int* p, int i) {
    bool is_not_zero = p;  // true nếu p != nullptr
    bool b2 = i;            // true nếu i != 0
}
```

Chuyển pointer → bool rất tiện trong điều kiện if, nhưng có thể gây nhầm lẫn khi truyền vào hàm:

```cpp
void fi(int);
void fb(bool);

int* p;  
fi(p);  // lỗi: không có conversion từ int* → int
fb(p);  // OK: pointer → bool conversion
```

## 10.5.2.6 Floating-Integral Conversions (số thực ↔ số nguyên)

### Floating → Integer:

Phần thập phân bị loại bỏ (truncated)

```cpp
int i = int(1.6);  // i = 1
```

Nếu giá trị không thể biểu diễn → undefined

```cpp
char b = 2000.7;  // undefined vì char 8-bit không chứa 2000
```

### Integer → Floating:

- Chính xác nếu phần cứng cho phép
- Có thể mất độ chính xác nếu integer quá lớn

```cpp
int i = float(1234567890);  
// nếu int và float đều 32-bit, i = 1234567936
```

## Kết luận

Nên tránh các conversion có khả năng mất dữ liệu.

Compiler có thể cảnh báo một số conversion nguy hiểm như: floating → int, long int → char.

Nếu cần, có thể dùng checked conversion:

```cpp
char checked_cast(int i) {
    char c = i;
    if (i != c) throw std::runtime_error{"int-to-char check failed"};
    return c;
}

void my_code(int i) {
    char c = checked_cast(i);
}
```

Dùng `numeric_limits` hoặc cú pháp `{}` initializer để tránh truncate và đảm bảo portable.

