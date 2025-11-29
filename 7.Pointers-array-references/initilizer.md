# C++ Initializers và Memory Management Guide

## Mục lục
1. [Initializers trong C++](#initializers-trong-c)
2. [Reference vs Value](#reference-vs-value)
3. [Missing Initializers](#missing-initializers)
4. [Initializer Lists](#initializer-lists)
5. [new và Dynamic Memory](#new-và-dynamic-memory)
6. [Stack vs Heap](#stack-vs-heap)
7. [Con trỏ: *p, p, &p](#con-trỏ-p-p-p)

---

## Initializers trong C++

### Initializer List (Danh sách khởi tạo)

Dùng trong constructor để khởi tạo các thành viên của class:

```cpp
class MyClass {
    int x;
    int y;
public:
    // Initializer list
    MyClass(int a, int b) : x(a), y(b) {
        // Constructor body
    }
};
```

### Variable Initialization (Khởi tạo biến)

```cpp
int x = 10;        // Copy initialization
int y{20};         // Brace initialization (C++11)
int z(30);         // Direct initialization
```

### Uniform Initialization (C++11)

```cpp
int arr[]{1, 2, 3, 4};
std::vector<int> vec{1, 2, 3};
MyClass obj{10, 20};
```

---

## Reference vs Value

### Với dấu `&` (Reference)

```cpp
class Test {
    int &t;  // t là một reference (tham chiếu)
public:
    Test(int &t) : t(t) {}  // Nhận reference làm tham số
    int getT() { return t; }
};
```

**Đặc điểm:**
- `t` là một **reference**, không phải bản sao
- `t` trỏ đến biến gốc bên ngoài
- Khi biến gốc thay đổi, `t` cũng thay đổi
- Không chiếm thêm bộ nhớ (chỉ là alias)

**Ví dụ:**
```cpp
int x = 10;
Test obj(x);  // obj.t tham chiếu đến x
x = 20;       // obj.getT() sẽ trả về 20
```

### Không có dấu `&` (Value/Copy)

```cpp
class Test {
    int t;  // t là một biến giá trị
public:
    Test(int t) : t(t) {}  // Nhận giá trị (copy)
    int getT() { return t; }
};
```

**Đặc điểm:**
- `t` là một **bản sao** (copy) của giá trị
- `t` độc lập với biến gốc
- Khi biến gốc thay đổi, `t` không đổi
- Chiếm bộ nhớ riêng

**Ví dụ:**
```cpp
int x = 10;
Test obj(x);  // obj.t là bản sao của x
x = 20;       // obj.getT() vẫn trả về 10
```

### So sánh

| Đặc điểm | `int &t` (Reference) | `int t` (Value) |
|----------|---------------------|-----------------|
| Bản chất | Tham chiếu đến biến gốc | Bản sao độc lập |
| Bộ nhớ | Không chiếm thêm | Chiếm bộ nhớ riêng |
| Thay đổi | Phản ánh thay đổi của biến gốc | Không bị ảnh hưởng |
| Khởi tạo | Bắt buộc trong initializer list | Có thể khởi tạo sau |

---

## Missing Initializers

### Quy tắc khởi tạo mặc định

#### 1. Static objects (global, namespace, static local, static member)
- Tự động khởi tạo = `{}` (zero-initialized)

```cpp
int a;        // a = 0 (như int a{})
double d;     // d = 0.0 (như double d{})
```

#### 2. Local variables và dynamic objects (heap)
- **Built-in types**: Không được khởi tạo (giá trị không xác định)
- **User-defined types**: Dùng default constructor

```cpp
void f() {
    int x;                    // ❌ Giá trị không xác định!
    char buf[1024];           // ❌ buf[i] không xác định!
    int* p {new int};         // ❌ *p không xác định!
    char* q {new char[1024]}; // ❌ q[i] không xác định!
    
    string s;                 // ✅ s == "" (default constructor)
    vector<char> v;           // ✅ v == {} (default constructor)
    string* ps {new string};  // ✅ *ps == "" (default constructor)
}
```

### Giải pháp: Luôn dùng `{}` để khởi tạo

```cpp
void ff() {
    int x {};                    // ✅ x = 0
    char buf[1024]{};            // ✅ buf[i] = 0 cho mọi i
    int* p {new int{10}};        // ✅ *p = 10
    char* q {new char[1024]{}};  // ✅ q[i] = 0 cho mọi i
}
```

---

## Initializer Lists

### Khởi tạo nhiều giá trị

Dùng `{}` để khởi tạo với nhiều giá trị:

```cpp
int a[] = {1, 2};                    // Array
struct S { int x; string s; };
S s = {1, "Helios"};                 // Struct
complex<double> z = {0, pi};         // Constructor
vector<double> v = {0.0, 1.1, 2.2};  // List constructor
```

Dấu `=` là tùy chọn:
```cpp
int a[] {1, 2};  // Tương đương với int a[] = {1, 2};
```

### Function-style initialization

```cpp
complex<double> z(0, pi);      // Constructor
vector<double> v(10, 3.3);     // 10 phần tử, mỗi phần tử = 3.3
```

### Lưu ý quan trọng

Dấu `()` rỗng có nghĩa là **function declaration**, không phải initialization:

```cpp
complex<double> z1(1, 2);      // ✅ Initialization
complex<double> f1();          // ❌ Function declaration (không phải init!)
complex<double> z2 {1, 2};     // ✅ Initialization
complex<double> f2 {};         // ✅ Default initialization
```

### Với auto

Khi dùng `auto`, `{}` được suy luận thành `std::initializer_list<T>`:

```cpp
auto x1 {1, 2, 3, 4};     // x1 là initializer_list<int>
auto x2 {1.0, 2.25, 3.5}; // x2 là initializer_list<double>
auto x3 {1.0, 2};         // ❌ Lỗi: không thể suy luận type
```

---

## new và Dynamic Memory

### `new` là gì?

`new` là toán tử cấp phát bộ nhớ động (dynamic memory allocation) trên **heap**.

### Cú pháp cơ bản

```cpp
// Cấp phát 1 biến
int* p = new int;        // Cấp phát 1 int, giá trị không xác định
int* p = new int(10);    // Cấp phát 1 int, khởi tạo = 10
int* p = new int{10};    // Cấp phát 1 int, khởi tạo = 10 (C++11)

// Cấp phát mảng
int* arr = new int[10];        // Cấp phát mảng 10 int, không khởi tạo
int* arr = new int[10]{};      // Cấp phát mảng 10 int, tất cả = 0
int* arr = new int[10]{1,2,3}; // Cấp phát mảng, khởi tạo 3 phần tử đầu
```

### Ví dụ

```cpp
int* p {new int{10}};
//      ^^^        ^
//      |          |
//      |          └─ Khởi tạo giá trị = 10
//      └──────────── Cấp phát 1 int trên heap

char* q {new char[1024]{}};
//       ^^^            ^^
//       |              |
//       |              └─ Khởi tạo tất cả = 0
//       └──────────────── Cấp phát mảng 1024 char trên heap
```

### Quy tắc quan trọng

1. **Mỗi `new` phải có `delete` tương ứng:**
   ```cpp
   int* p = new int;    // new
   delete p;            // delete
   
   int* arr = new int[10];  // new[]
   delete[] arr;            // delete[] (không phải delete!)
   ```

2. **Memory leak nếu quên `delete`:**
   ```cpp
   void bad_function() {
       int* p = new int{10};
       // Quên delete p; → Memory leak!
   }
   ```

3. **Dangling pointer sau khi `delete`:**
   ```cpp
   int* p = new int{10};
   delete p;
   *p = 20;  // ❌ NGUY HIỂM! p đã bị giải phóng
   ```

### Modern C++ (C++11+)

Nên dùng smart pointers thay vì `new`/`delete` thủ công:

```cpp
#include <memory>

// Thay vì:
int* p = new int{10};
delete p;

// Nên dùng:
unique_ptr<int> p = make_unique<int>(10);
// Tự động giải phóng khi ra khỏi scope
```

---

## Stack vs Heap

### STACK (Ngăn xếp)

**Đặc điểm:**
- Tự động quản lý bởi compiler
- Tốc độ rất nhanh
- Kích thước nhỏ (thường vài MB)
- LIFO (Last In First Out)
- Tự động giải phóng khi ra khỏi scope
- Địa chỉ liên tục, tăng/giảm theo thứ tự

**Ví dụ:**
```cpp
void function() {
    int x = 10;        // Trên stack
    char c = 'A';      // Trên stack
    int arr[100];      // Trên stack
    // Tất cả tự động giải phóng khi function kết thúc
}
```

### HEAP (Đống)

**Đặc điểm:**
- Phải quản lý thủ công (new/delete)
- Tốc độ chậm hơn stack
- Kích thước lớn (phụ thuộc RAM)
- Không có thứ tự cụ thể
- Phải tự giải phóng bằng delete
- Địa chỉ ngẫu nhiên, phân mảnh

**Ví dụ:**
```cpp
void function() {
    int* p = new int{10};      // Trên heap
    char* arr = new char[1000]; // Trên heap
    // Phải tự giải phóng!
    delete p;
    delete[] arr;
}
```

### So sánh

| Đặc điểm | STACK | HEAP |
|----------|-------|------|
| **Tốc độ** | Rất nhanh | Chậm hơn |
| **Kích thước** | Nhỏ (vài MB) | Lớn (phụ thuộc RAM) |
| **Quản lý** | Tự động | Thủ công (new/delete) |
| **Địa chỉ** | Liên tục, gần nhau | Ngẫu nhiên, phân mảnh |
| **Thứ tự** | LIFO (ngăn xếp) | Không có thứ tự |
| **Giải phóng** | Tự động khi ra scope | Phải dùng delete |
| **Dùng cho** | Biến local, tham số | Dữ liệu lớn, động |

### Sơ đồ bộ nhớ

```
BỘ NHỚ CHƯƠNG TRÌNH
┌─────────────────────────────────────────┐
│                                         │
│  STACK (Ngăn xếp)                       │
│  ┌─────────────────┐                   │
│  │ main()          │                   │
│  │   stack_var     │ ← 0x7fff5fbff60c  │
│  │   stack_arr     │ ← 0x7fff5fbff5f0  │
│  │   heap_var ptr  │ ← 0x7fff5fbff600  │
│  │   heap_arr ptr  │ ← 0x7fff5fbff5f8  │
│  └─────────────────┘                   │
│         │                               │
│         │ Con trỏ trỏ đến              │
│         ↓                               │
│  HEAP (Đống)                            │
│  ┌─────────────────┐                   │
│  │   [free]        │                   │
│  ├─────────────────┤                   │
│  │   heap_var = 20 │ ← 0x7ff8a5c00010  │
│  ├─────────────────┤                   │
│  │   [free]        │                   │
│  ├─────────────────┤                   │
│  │   heap_arr[5]   │ ← 0x7ff8a5c00020  │
│  ├─────────────────┤                   │
│  │   [free]        │                   │
│  └─────────────────┘                   │
│                                         │
└─────────────────────────────────────────┘
```

### Khi nào dùng Stack vs Heap?

**Dùng STACK khi:**
- Biến local, tham số hàm
- Kích thước nhỏ, biết trước
- Thời gian sống ngắn (trong scope)
- Ví dụ: `int x = 10;`, `char arr[100];`

**Dùng HEAP khi:**
- Kích thước lớn hoặc không biết trước
- Cần tồn tại sau khi ra khỏi scope
- Cấu trúc dữ liệu động
- Ví dụ: `new int[1000000]`, `new MyClass()`

---

## Con trỏ: *p, p, &p

### 3 khái niệm quan trọng

```cpp
int* p {new int{10}};

// 1. *p  → Giá trị mà p trỏ đến (dereference)
// 2. p   → Địa chỉ mà p lưu (địa chỉ của biến trên heap)
// 3. &p  → Địa chỉ của biến con trỏ p (địa chỉ của p trên stack)
```

### Ví dụ minh họa

```cpp
#include <iostream>
using namespace std;

int main() {
    int* p {new int{10}};
    
    cout << "*p = " << *p << endl;    // Giá trị: 10
    cout << "p = " << p << endl;      // Địa chỉ trên heap: 0x7ff8a5c00010
    cout << "&p = " << &p << endl;    // Địa chỉ trên stack: 0x7fff5fbff618
    
    delete p;
    return 0;
}
```

### Sơ đồ bộ nhớ

```
Stack (Local variables)          Heap (Dynamic memory)
┌─────────────────┐              ┌─────────────────┐
│  p              │              │                 │
│  ┌───────────┐  │              │                 │
│  │ 07x7ff8... │──┼─────────────>│  10             │
│  └───────────┘  │              │                 │
│  ↑              │              │                 │
│  &p             │              │                 │
│  (0x7fff5f...)  │              │                 │
└─────────────────┘              └─────────────────┘
     ↑                                ↑
     |                                |
   &p = địa chỉ của p              p = địa chỉ của vùng nhớ
                                   *p = giá trị 10
```

### Bảng tóm tắt

| Biểu thức | Ý nghĩa | Ví dụ giá trị | Vị trí bộ nhớ |
|-----------|---------|---------------|---------------|
| `*p` | Giá trị mà p trỏ đến | `10` | Heap (giá trị) |
| `p` | Địa chỉ mà p lưu | `0x7ff8a5c00010` | Heap (địa chỉ) |
| `&p` | Địa chỉ của biến p | `0x7fff5fbff618` | Stack (địa chỉ) |

### Lưu ý quan trọng

1. `p` và `&p` là 2 địa chỉ khác nhau:
   - `p`: địa chỉ trên heap (nơi lưu dữ liệu)
   - `&p`: địa chỉ trên stack (nơi lưu con trỏ)

2. Khi in `p` trực tiếp, cout sẽ in địa chỉ (dạng hex):
   ```cpp
   cout << p;  // In địa chỉ, không phải giá trị
   ```

3. Để in giá trị, phải dùng `*p`:
   ```cpp
   cout << *p;  // In giá trị 10
   ```

### Tại sao không thể bỏ dấu `*`?

```cpp
int* p {new int{10}};
//  ↑
//  Con trỏ đến int

// new int{10} trả về int* (con trỏ), không phải int
// Phải khai báo int* để khớp kiểu
```

**Nếu bỏ `*`:**
```cpp
int p {new int{10}};  // ❌ LỖI!
// error: cannot convert 'int*' to 'int' in initialization
```

**Lý do:**
- `new int{10}` trả về `int*` (con trỏ)
- `p` là `int` (số nguyên)
- Không thể gán con trỏ vào biến int

---

## Tóm tắt

### Initializers
- Luôn khởi tạo biến, trừ khi cần tối ưu buffer lớn
- Static objects tự động = 0; local/dynamic built-in types không được khởi tạo
- Dùng `{}` để khởi tạo an toàn
- `()` rỗng là function declaration, dùng `{}` cho default initialization

### Reference vs Value
- Reference (`&`): Tham chiếu đến biến gốc, không chiếm thêm bộ nhớ
- Value: Bản sao độc lập, chiếm bộ nhớ riêng

### Memory Management
- **Stack**: Tự động, nhanh, nhỏ, cho biến local
- **Heap**: Thủ công, chậm hơn, lớn, cho dữ liệu động
- **Con trỏ** (`p`) được lưu trên **stack**, nhưng nó **trỏ đến** dữ liệu trên **heap**

### Con trỏ
- `*p`: Giá trị mà p trỏ đến
- `p`: Địa chỉ trên heap (nơi lưu dữ liệu)
- `&p`: Địa chỉ trên stack (nơi lưu con trỏ)

---

## Tài liệu tham khảo

- The C++ Programming Language (Bjarne Stroustrup)
- C++ Core Guidelines
- cppreference.com
