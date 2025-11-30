# 10.5.3 Các Chuyển Đổi Số Học Thông Thường (Usual Arithmetic Conversions)

Các chuyển đổi số học thông thường được áp dụng cho các toán hạng của toán tử nhị phân (binary operator), nhằm đưa chúng về một kiểu chung. Kiểu này cũng sẽ là kiểu của kết quả.

## 1️⃣ Quy tắc cho số thực (floating types)

- Nếu một trong hai toán hạng là `long double`, toán hạng còn lại sẽ được convert sang `long double`.
- Nếu không, nếu một toán hạng là `double`, toán hạng còn lại convert sang `double`.
- Nếu không, nếu một toán hạng là `float`, toán hạng còn lại convert sang `float`.
- Nếu cả hai không phải số thực → chuyển sang các integral promotions (§10.5.1).

**Ví dụ:**

```cpp
float f = 1.5f;
double d = 2.5;
auto r = f + d;  // f → double, kết quả là double

long double ld = 3.5;
r = ld + d;      // d → long double, kết quả là long double
```

## 2️⃣ Quy tắc cho số nguyên (integer types)

Nếu không phải số thực, C++ áp dụng quy tắc chi tiết sau:

- Nếu một toán hạng là `unsigned long long`, toán hạng còn lại convert sang `unsigned long long`.

- Nếu một toán hạng là `long long int` và toán hạng kia là `unsigned long int`:
  - Nếu `long long int` có thể biểu diễn toàn bộ giá trị của `unsigned long int` → convert `unsigned long int` sang `long long int`
  - Nếu không → convert cả hai sang `unsigned long long int`

- Nếu một toán hạng là `long int` và toán hạng kia là `unsigned int`:
  - Nếu `long int` biểu diễn được toàn bộ giá trị của `unsigned int` → convert `unsigned int` sang `long int`
  - Nếu không → convert cả hai sang `unsigned long int`

- Nếu một toán hạng là `long` → convert toán hạng kia sang `long`

- Nếu một toán hạng là `unsigned` → convert toán hạng kia sang `unsigned`

- Nếu không áp dụng được gì → cả hai là `int`

## Ý nghĩa thực tế

Các quy tắc này giúp compiler chuẩn hóa kiểu toán hạng trước khi thực hiện các phép toán số học.

Tuy nhiên, nếu mix giữa signed và unsigned integer, kết quả có thể implementation-defined, tức là khác nhau tùy compiler.

→ **Đây là lý do không nên trộn signed và unsigned.**

## Ví dụ minh họa

```cpp
int a = 10;
unsigned int b = 20;

auto r = a + b;  // a → unsigned int, kết quả là unsigned int

long x = 1000;
unsigned int y = 500;

auto r2 = x + y; // y → long, kết quả là long nếu long đủ lớn
```

Trường hợp mix signed/unsigned nhỏ → có thể hiểu, nhưng mix kiểu lớn và unsigned → có thể gây bất ngờ.

