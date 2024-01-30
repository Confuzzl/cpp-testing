#include <algorithm>
#include <array>
#include <concepts>
#include <format>
#include <functional>
#include <iostream>
#include <numeric>
#include <ranges>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <vector>

// struct vec3 {
//   double x, y, z;
//
//   constexpr double operator[](const unsigned char n) const {
//     switch (n) {
//     case 0:
//       return x;
//     case 1:
//       return y;
//     case 2:
//       return z;
//     }
//     throw -1;
//   }
//
//   vec3 operator+(const vec3 &other) const {
//     return {x + other.x, y + other.y, z + other.z};
//   }
// };
//
// template <typename T>
// concept subscriptable = requires(T t) { t[0]; };
//
// template <template <typename> typename comparator, subscriptable T>
// bool hadamard_compare(T a, T b, unsigned int range) {
//   bool out = true;
//   const comparator<decltype(std::declval<T>().operator[](0))> compare{};
//   for (unsigned int i = 0; i < range; i++)
//     out &= compare(a[i], b[i]);
//   return out;
// }
//
// template <template <typename> typename lower,
//           template <typename> typename upper, subscriptable T>
// bool hadamard_in_range(T min, T n, T max, unsigned int range) {
//   return hadamard_compare<lower, T>(min, n, range) &&
//          hadamard_compare<upper, T>(n, max, range);
// }
//
// #include <chrono>
// import <random>;
//
// namespace random {
// std::random_device rd;
// std::mt19937 mt{rd()};
//
// double random(const double min, const double max) {
//   return std::uniform_real_distribution<double>{min, max}(mt);
// }
//
// int random(const int min, const int max) {
//   return std::uniform_int_distribution<>(min, max)(mt);
// }
// } // namespace random
//
// struct aabb {
//   enum struct State {
//     CLEAR,
//     INTERSECTING,
//     TOUCHING,
//   };
//
//   vec3 min, max;
//
//   State check1(const vec3 &point) const {
//     bool touching = false;
//     for (int i = 0; i < 3; i++) {
//       const auto lower = min[i] <=> point[i];
//       if (lower > 0)
//         return State::CLEAR;
//       if (lower == 0)
//         touching = true;
//
//       const auto upper = point[i] <=> max[i];
//       if (upper > 0)
//         return State::CLEAR;
//       if (upper == 0)
//         touching = true;
//     }
//     return touching ? State::TOUCHING : State::INTERSECTING;
//   }
//   State check2(const vec3 &point) const {
//     if (hadamard_in_range<std::less, std::less>(min, point, max, 3))
//       return State::INTERSECTING;
//     if (hadamard_in_range<std::less_equal, std::less_equal>(min, point, max,
//     3))
//       return State::TOUCHING;
//     return State::CLEAR;
//   }
//   State check3(const vec3 &point) const {
//     if ((min[0] < point[0] && point[0] < max[0]) &&
//         (min[1] < point[1] && point[1] < max[1]) &&
//         (min[2] < point[2] && point[2] < max[2]))
//       return State::INTERSECTING;
//     if ((min[0] <= point[0] && point[0] <= max[0]) &&
//         (min[1] <= point[1] && point[1] <= max[1]) &&
//         (min[2] <= point[2] && point[2] <= max[2]))
//       return State::TOUCHING;
//     return State::CLEAR;
//   }
//   State check4(const vec3 &point) const {
//     bool touching = false;
//     for (int i = 0; i < 3; i++) {
//       const double lower = min[i] - point[i];
//       if (lower > 0)
//         return State::CLEAR;
//       if (lower == 0)
//         touching = true;
//
//       const double upper = point[i] - max[i];
//       if (upper > 0)
//         return State::CLEAR;
//       if (upper == 0)
//         touching = true;
//     }
//     return touching ? State::TOUCHING : State::INTERSECTING;
//   }
//
//   State check1(const aabb &other) const {
//     bool touching = false;
//     for (int i = 0; i < 3; i++) {
//       const auto lower = min[i] <=> other.max[i];
//       if (lower > 0)
//         return State::CLEAR;
//       if (lower == 0)
//         touching = true;
//
//       const auto upper = max[i] <=> other.min[i];
//       if (upper > 0)
//         return State::CLEAR;
//       if (upper == 0)
//         touching = true;
//     }
//     return touching ? State::TOUCHING : State::INTERSECTING;
//   }
//   State check2(const aabb &other) const {
//     if (hadamard_compare<std::less>(min, other.max, 3) &&
//         hadamard_compare<std::greater>(max, other.min, 3))
//       return State::INTERSECTING;
//     if (hadamard_compare<std::less_equal>(min, other.max, 3) &&
//         hadamard_compare<std::greater_equal>(max, other.min, 3))
//       return State::TOUCHING;
//     return State::CLEAR;
//   }
//   State check3(const aabb &other) const {
//     if ((min[0] < other.max[0] && max[0] > other.min[0]) &&
//         (min[1] < other.max[1] && max[1] > other.min[1]) &&
//         (min[2] < other.max[2] && max[2] > other.min[2]))
//       return State::INTERSECTING;
//     if ((min[0] <= other.max[0] && max[0] >= other.min[0]) &&
//         (min[1] <= other.max[1] && max[1] >= other.min[1]) &&
//         (min[2] <= other.max[2] && max[2] >= other.min[2]))
//       return State::TOUCHING;
//     return State::CLEAR;
//   }
//   State check4(const aabb &other) const {
//     bool touching = false;
//     for (int i = 0; i < 3; i++) {
//       const double lower = min[i] - other.max[i];
//       if (lower > 0)
//         return State::CLEAR;
//       if (lower == 0)
//         touching = true;
//
//       const double upper = max[i] - other.min[i];
//       if (upper > 0)
//         return State::CLEAR;
//       if (upper == 0)
//         touching = true;
//     }
//     return touching ? State::TOUCHING : State::INTERSECTING;
//   }
// };
//
// vec3 testvec(const int n) {
//   return {random::random(1, n) * 0.5, random::random(1, n) * 0.5,
//           random::random(1, n) * 0.5};
// }
//
// using pointfunc = aabb::State (aabb::*)(const vec3 &) const;
// using aabbfunc = aabb::State (aabb::*)(const aabb &) const;
//
// #define TEST_COUNT 1'000'000
//
// template <typename functype> long long test(functype func);
// template <> long long test<pointfunc>(pointfunc func) {
//   auto start = std::chrono::high_resolution_clock::now();
//   // unsigned int counts[3]{0, 0, 0};
//   for (int i = 0; i < TEST_COUNT; i++) {
//     const vec3 min = testvec(3), size = testvec(3);
//     const aabb box{min, min + size};
//     // counts[(int)((&box)->*func)(testvec(3))]++;
//   }
//
//   auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
//                 std::chrono::high_resolution_clock::now() - start)
//                 .count();
//   return ms;
// }
// template <> long long test<aabbfunc>(aabbfunc func) {
//   auto start = std::chrono::high_resolution_clock::now();
//   unsigned int counts[3]{0, 0, 0};
//   for (int i = 0; i < TEST_COUNT; i++) {
//     const vec3 min1 = testvec(5), size1 = testvec(5);
//     const aabb box1{min1, min1 + size1};
//     const vec3 min2 = testvec(5), size2 = testvec(5);
//     const aabb box2{min1, min1 + size1};
//   }
//
//   auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
//                 std::chrono::high_resolution_clock::now() - start)
//                 .count();
//   return ms;
// }
//
// template <typename functype> auto trials(const unsigned int t, functype func)
// {
//   long long time = 0;
//   for (unsigned int i = 0; i < t; i++) {
//     time += test(func);
//   }
//   std::cout << std::format("avg of {}: {:.2f}s\n", t, time / 1000.0);
// }
//
// void println(const std::string &str) { std::cout << str << "\n"; }
//
// template <typename... Args>
// void println(std::format_string<Args...> str, Args &&...args) {
//   std::cout << std::format("{}\n",
//                            std::format(str, std::forward<Args>(args)...));
// }
//
// template <typename... Args>
// void rprintln(std::string_view str, Args &&...args) {
//   std::cout << std::vformat(str, std::make_format_args(args...)) << "\n";
// }

void println(const std::string &str) { std::cout << str << "\n"; }
template <typename... Args>
void println(std::format_string<Args...> str, Args &&...args) {
  println(std::format(str, std::forward<Args>(args)...));
}
#include <map>

struct vec2 {
  double x = 0, y = 0;
};

template <> struct std::formatter<vec2> {
  constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }
  auto format(const vec2 &vec, std::format_context &ctx) const {
    return std::format_to(ctx.out(), "({:+.2f},{:+.2f})", vec.x, vec.y);
  }
};

struct object;
struct collider;
struct aabb;

struct aabb {
  const collider &parent;
  aabb(const collider &parent) : parent{parent} {}

  vec2 globalPos() const;

  void foo() const;
};
struct collider {
  const object &parent;
  // aabb _aabb;
  std::unique_ptr<aabb> box;
  collider(const object &parent)
      : parent{parent}, box{std::make_unique<aabb>(*this)} {}

  vec2 globalPos() const;

  void foo() const;
};
struct convex : collider {
  const std::vector<vec2> vertices{};

  convex(const object &parent) : collider(parent) {}

  static convex create(const object &parent) {}
};

struct object {
  static unsigned COUNT;
  static std::map<unsigned, std::unique_ptr<object>> objects;

  const unsigned id;
  vec2 pos{2, 3};
  // collider coll;
  std::unique_ptr<collider> coll;

  object(std::unique_ptr<collider> coll) : id{COUNT++}, coll{std::move(coll)} {}
  object(const object &) = delete;
  object(object &&) = delete;
  object &operator=(const object &) = delete;
  object &operator=(object &&) = delete;

  static object &create() {
    std::unique_ptr<object> out = std::make_unique<object>();
    const unsigned id = out->id;
    objects.emplace(out->id, std::move(out));
    return *objects.at(id);
  }

  void foo() const {
    println("{:x} {:x} {:x}", reinterpret_cast<size_t>(this),
            reinterpret_cast<size_t>(coll.get()),
            reinterpret_cast<size_t>(coll->box.get()));
  }
};
unsigned object::COUNT = 0;
std::map<unsigned, std::unique_ptr<object>> object::objects{};

// constexpr bool a = std::is_move_constructible<object>::value;
// constexpr bool b = std::is_copy_constructible<object>::value;
// constexpr bool c = std::is_move_assignable<object>::value;
// constexpr bool d = std::is_copy_assignable<object>::value;

void aabb::foo() const {
  println("{:x} {:x} {:x}", reinterpret_cast<size_t>(&parent.parent),
          reinterpret_cast<size_t>(&parent), reinterpret_cast<size_t>(this));
}
vec2 aabb::globalPos() const { return parent.globalPos(); }

void collider::foo() const {
  println("{:x} {:x} {:x}", reinterpret_cast<size_t>(&parent),
          reinterpret_cast<size_t>(this), reinterpret_cast<size_t>(&_aabb));
}
vec2 collider::globalPos() const { return parent.pos; }

int main() {
  object &o1 = object::create();
  // println("{}", o1.pos);
  //  o1.foo();
  //  o1.coll.foo();
  //  o1.coll._aabb.foo();
  collider &c = o1.coll;
  aabb &d = c._aabb;
}