# 10.5 Chuyển đổi kiểu ngầm định (Implicit Type Conversion)

Các kiểu số nguyên (integral) và số thực (floating-point) có thể pha trộn tự do trong các phép gán hoặc biểu thức.

Khi pha trộn, compiler sẽ cố gắng chuyển đổi giá trị mà không mất thông tin.

Tuy nhiên, một số chuyển đổi gây mất dữ liệu (gọi là **narrowing conversion**) vẫn xảy ra.

## Các loại chuyển đổi

### Chuyển đổi bảo toàn giá trị (value-preserving conversion):

Bạn có thể chuyển đổi giá trị sang kiểu khác, rồi chuyển lại về kiểu gốc, vẫn ra giá trị ban đầu.

### Chuyển đổi thu hẹp (narrowing conversion):

Nếu chuyển kiểu mà không thể bảo toàn giá trị, đó là narrowing conversion.

## Nội dung phần này

Phần này mô tả:

- quy tắc chuyển đổi
- các vấn đề phát sinh
- cách giải quyết

---

## 10.5.1 Promotions (Nâng cấp kiểu an toàn)

Các chuyển đổi ngầm định bảo toàn giá trị thường được gọi là **promotion**.

### Promotion trước khi thực hiện phép toán:

- **Integral promotion:** nâng các kiểu nguyên nhỏ lên `int`.
- **Floating-point promotion:** nâng `float` lên `double`.

> **Lưu ý:** Promotion không nâng đến `long` trừ khi toán hạng là `char16_t`, `char32_t`, `wchar_t` hoặc một enum đã lớn hơn `int`.

### Mục đích:

Đưa toán hạng về kích thước "tự nhiên" (natural size) cho CPU thực hiện các phép toán, theo truyền thống C.

---

## ✅ Chi tiết các integral promotions

### 1. `char`, `signed char`, `unsigned char`, `short int`, `unsigned short int` → `int`

- Nếu `int` có thể chứa tất cả giá trị của kiểu gốc → chuyển thành `int`
- Nếu không → chuyển thành `unsigned int`

### 2. `char16_t`, `char32_t`, `wchar_t`, plain enum → `int`/`unsigned int`/`long`/`unsigned long`/`unsigned long long`

Compiler chọn kiểu nhỏ nhất có thể chứa toàn bộ giá trị của kiểu gốc.

### 3. Bit-field

- Nếu `int` chứa được tất cả giá trị → promote thành `int`
- Nếu không, nếu `unsigned int` chứa được → promote thành `unsigned int`
- Nếu cả hai không được → không có promotion

### 4. `bool` → `int`

- `false` → `0`
- `true` → `1`

---

## 📝 Ghi chú quan trọng

Promotion được sử dụng như một phần của **"usual arithmetic conversions"** (§10.5.3) để chuẩn hóa các toán hạng trước khi thực hiện các phép toán số học.

