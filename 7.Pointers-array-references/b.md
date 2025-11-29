# C++ Notes - Pointers, Arrays, and References

## Con trỏ (Pointers)

`x` là giá trị được lưu trong biến.

`&x` là địa chỉ bộ nhớ của biến x.

`*x` chỉ có ý nghĩa khi x là pointer!

```cpp
int x = 42;
int* ptr = &x;   // ptr lưu địa chỉ của x

cout << ptr;     // 0x7ffc1234 (địa chỉ)
cout << *ptr;    // 42 (giá trị tại địa chỉ đó - DEREFERENCE)

*ptr = 100;      // Thay đổi giá trị tại địa chỉ
cout << x;       // 100 (x đã thay đổi!)
```

**Giải thích:**

- `*ptr` = "lấy giá trị tại địa chỉ mà `ptr` trỏ đến"
- `*ptr = 100` = "thay đổi giá trị tại địa chỉ đó"

```
Memory:
┌────────────┬──────────────┐
│ ptr        │  x           │
│ 0x7ffc1234 │  100         │
└────────────┴──────────────┘
      │              ↑
      └──────────────┘
         ptr trỏ đến x
```

## Function Pointer

```cpp
int (*fp)(char*);
```

+ Đây là con trỏ tới một hàm (function pointer).
+ Hàm mà fp trỏ tới nhận tham số `char*`
+ Và trả về `int`
+ `fp` không phải là hàm.
+ `fp` chỉ là một biến dùng để lưu địa chỉ của một hàm.

```cpp
int* f(char*);
```

+ Đây là một hàm, không phải con trỏ.
+ Hàm `f` nhận tham số `char*`
+ Hàm `f` trả về `int*` (con trỏ tới int)

## Void Pointer

`void*` as "pointer to an object of unknown type."

`void*` là con trỏ không có kiểu (untyped pointer).

Nó chỉ lưu địa chỉ nhưng KHÔNG chứa thông tin về kiểu dữ liệu.

→ Do đó, máy không biết "địa chỉ này trỏ tới cái gì".

- Gán bất kỳ con trỏ object nào vào `void*`
- Gán `void*` sang `void**`
- Cast `void*` trở lại loại cụ thể: `int* pi2 = static_cast<int*>(pv);`

❌ Không được dereference:
❌ Không được increment:
❌ Không được chuyển ngầm định sang con trỏ kiểu khác

## reinterpret_cast

`reinterpret_cast` là một loại type casting trong C++ cho phép chuyển đổi giữa các kiểu con trỏ một cách "thô" (low-level), chỉ đơn giản là diễn giải lại bit pattern tại địa chỉ đó.

### Đặc điểm:

+ **Không thay đổi giá trị địa chỉ** - chỉ thay đổi cách diễn giải kiểu dữ liệu
+ **Rất nguy hiểm** - có thể dẫn đến undefined behavior nếu dùng sai
+ **Chỉ nên dùng khi thực sự cần thiết** - thường dùng cho low-level programming

### Cú pháp:

```cpp
reinterpret_cast<new_type>(expression)
```

### Ví dụ trong code của bạn:

```cpp
template<typename T>
int byte_diff(T* p, T* q)
{
    return reinterpret_cast<char*>(q) - reinterpret_cast<char*>(p);
}
```

**Giải thích:**

- `T*` có thể là `int*` (mỗi phần tử 4 bytes) hoặc `short*` (mỗi phần tử 2 bytes)
- Khi trừ hai con trỏ cùng kiểu: `q - p` cho kết quả là **số phần tử**, không phải số bytes
- Để tính **số bytes**, cần chuyển sang `char*` (mỗi phần tử 1 byte)
- `reinterpret_cast<char*>(p)` = "coi địa chỉ này như là con trỏ tới `char`"
- Khi trừ hai `char*`: kết quả là số bytes giữa hai địa chỉ

### Ví dụ cụ thể:

```cpp
int vi[10];
short vs[10];

// &vi[1] - &vi[0] = 1 (số phần tử, không phải bytes)
// byte_diff(&vi[0], &vi[1]) = 4 (số bytes, vì int = 4 bytes)

// &vs[1] - &vs[0] = 1 (số phần tử)
// byte_diff(&vs[0], &vs[1]) = 2 (số bytes, vì short = 2 bytes)
```

### So sánh với các cast khác:

| Cast Type | Mục đích | An toàn |
|-----------|----------|---------|
| `static_cast` | Chuyển đổi kiểu thông thường (int → double, base → derived) | Tương đối an toàn |
| `dynamic_cast` | Chuyển đổi trong inheritance hierarchy với kiểm tra runtime | An toàn (trả về nullptr nếu fail) |
| `const_cast` | Bỏ/tạo const/volatile | Nguy hiểm nếu dùng sai |
| `reinterpret_cast` | Diễn giải lại bit pattern | Rất nguy hiểm |

### Lưu ý quan trọng:

❌ **KHÔNG được dereference** kết quả của `reinterpret_cast` trừ khi bạn chắc chắn về kiểu dữ liệu

❌ **KHÔNG được dùng** để chuyển đổi giữa các kiểu không liên quan (trừ pointer types)

✅ **Nên dùng** khi cần tính toán địa chỉ ở mức byte (như trong ví dụ `byte_diff`)

✅ **Nên dùng** khi làm việc với low-level memory operations

## Arrays

For a type T, `T[size]` is the type "array of size elements of type T." The elements are indexed from 0 to size-1. For example:

```cpp
float v[3];      // an array of three floats: v[0], v[1], v[2]
char* a[32];     // an array of 32 pointers to char: a[0] .. a[31]
```

**Array indexing equivalence:**

```
a[j] == *(&a[0]+j) == *(a+j) == *(j+a) == j[a]
```

### Pointer Arithmetic với Arrays

```cpp
void f()
{
    int v1[10];
    int v2[10];
    
    int i1 = &v1[5] - &v1[3]; // i1 = 2 (số phần tử)
    int i2 = &v1[5] - &v2[3]; // result undefined (trừ con trỏ khác array)
    
    int* p1 = v2 + 2;  // p1 = &v2[2] (OK)
    int* p2 = v2 - 2;  // *p2 undefined (trỏ ra ngoài array)
}
```

**Lưu ý:**

+ Chỉ được trừ hai con trỏ **cùng một array**
+ Trừ con trỏ khác array → **undefined behavior**
+ Con trỏ ra ngoài array → **undefined behavior**

## Vector

`std::vector<T>` là mảng động trong C++:

+ Tự động thay đổi kích thước.
+ Quản lý bộ nhớ an toàn.
+ Hỗ trợ đầy đủ phương thức thao tác dữ liệu.
+ Không xảy ra lỗi vượt biên như array truyền thống (nhưng `v[i]` vẫn không kiểm tra, `v.at(i)` có kiểm tra).

### Khai báo vector:

```cpp
#include <vector>
using namespace std;

vector<int> v;           // vector rỗng
vector<int> v2(5);       // 5 phần tử, mỗi phần tử = 0
vector<int> v3(5, 10);   // 5 phần tử, mỗi phần tử = 10
vector<string> names;    // vector string
```

### Thao tác với vector:

```cpp
v.push_back(10);     // thêm vào cuối
v.emplace_back(20);  // tạo trực tiếp tại cuối (tối ưu hơn)

int x = v[0];      // không kiểm tra vượt biên
int y = v.at(1);   // có kiểm tra, an toàn hơn

v.front();
v.back();

v.pop_back();                  // xóa phần tử cuối
v.erase(v.begin() + 2);        // xóa phần tử thứ 3
v.erase(v.begin(), v.end());   // xóa toàn bộ
v.clear();                     // xóa toàn bộ

v.size();       // số phần tử hiện tại
v.capacity();   // dung lượng đã cấp phát
v.empty();      // kiểm tra rỗng
```

### Duyệt vector:

```cpp
for (int i = 0; i < v.size(); i++) {
    cout << v[i] << " ";
}

for (int x : v) {
    cout << x << " ";
}

for (auto it = v.begin(); it != v.end(); it++) {
    cout << *it << " ";
}
```

### Khởi tạo từ array:

```cpp
int a[] = {1, 2, 3, 4};
vector<int> v(a, a + 4);
```

## String Literals

String literal là một chuỗi ký tự cố định được đặt trong dấu ngoặc kép `"..."` trong code.

```cpp
"Hello, world"
"abc"
"123"
```

Đây là các string literal.

Chúng luôn được cấp phát tĩnh trong bộ nhớ (read-only data segment).

Tự động kết thúc bằng ký tự null (`'\0'`) để đánh dấu kết thúc chuỗi.

Kiểu của string literal là: `const char[n]`

```cpp
sizeof("Bohr"); // 5, gồm 4 ký tự + '\0'
const char* s = "Bohr";
```

- Immutable (không thay đổi được)
- An toàn để return từ hàm
- Có thể sử dụng escape characters
- Có thể nối các literal liền nhau: `char s[] = "Hello " "World"; // compiler sẽ nối thành "Hello World"`

## Const và Pointers

### `const char* pc` → pointer đến dữ liệu const

```cpp
const char* pc = s;
pc[3] = 'g';   // ❌ ERROR – dữ liệu const
pc = p;        // ✔ OK – đổi hướng pointer được
```

### `char* const cp` → pointer là const, nhưng dữ liệu thì không

```cpp
char* const cp = s;
cp[3] = 'a';   // ✔ OK – sửa dữ liệu
cp = p;        // ❌ ERROR – pointer const
```

### `const char* const cpc` → pointer const trỏ tới dữ liệu const

```cpp
const char* const cpc = s;
cpc[3] = 'a';  // ❌ lỗi – không được sửa dữ liệu
cpc = p;       // ❌ lỗi – pointer không đổi hướng được
```

## References

### 1. `T&` (lvalue reference thường) chỉ được bind vào lvalue

```cpp
double& dr = 1;   // ❌ Error
```

**Lý do:**

+ `double&` yêu cầu phải bind vào một object tồn tại trong bộ nhớ
+ Nhưng `1` là rvalue literal → không có địa chỉ rõ ràng, không có biến tồn tại để reference bám vào
+ Nên C++ không cho phép

### 2. `const T&` có thể bind vào rvalue (literal, temporary)

```cpp
const double& cdr = 1; // ✔ OK
```

Vì với `const T&`, C++ cho phép bind vào temporary theo cơ chế 3 bước:

```cpp
const double& cdr {1};
```

[1] Convert literal `1` → `double` (nếu cần): `double{1}`

[2] Tạo một temporary object: `double temp = double{1};`

[3] `cdr` bind vào temporary đó: `const double& cdr = temp;`
