#include <cmath>
#include <string>

const int x = 7;          // x là hằng, có thể dùng ở compile-time
const std::string s = "asdf";  // s là hằng nhưng không phải literal type
const int y = sqrt(x);    // y là hằng nhưng sqrt() không phải constexpr

constexpr int xx = x;     // ✅ OK, x là hằng số nguyên
constexpr std::string ss = s; // ❌ lỗi, string không phải literal type
constexpr int yy = y;     // ❌ lỗi, sqrt(x) không phải constexpr
