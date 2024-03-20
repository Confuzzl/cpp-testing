#include <algorithm>
#include <array>
#include <concepts>
#include <format>
#include <functional>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <ranges>
#include <string>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <vector>

std::random_device rd;
std::mt19937 mt{rd()};
template <typename T = int> T random_int(const T a, const T b) {
  return std::uniform_int_distribution<T>{a, b}(mt);
}

void println(const std::string &str = "") { std::cout << str << "\n"; }
template <typename... Args>
void println(std::format_string<Args...> str, Args &&...args) {
  println(std::format(str, std::forward<Args>(args)...));
}
template <typename T> void println(const T &o) { println("{}", o); }

// template <typename T> struct info_type {
//   static constexpr bool copy_con = std::is_copy_constructible<T>::value;
//   static constexpr bool copy_ass = std::is_copy_assignable<T>::value;
//   static constexpr bool move_con = std::is_move_constructible<T>::value;
//   static constexpr bool move_ass = std::is_move_assignable<T>::value;
// };
// template <typename T> struct std::formatter<info_type<T>> {
//   constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin();
//   }
//
//   auto format(const info_type<T> &info, std::format_context &ctx) const {
//     return std::format_to(ctx.out(), "cc: {} ca: {} mc: {} ma: {}",
//                           info_type<T>::copy_con, info_type<T>::copy_ass,
//                           info_type<T>::move_con, info_type<T>::move_ass);
//   }
// };
template <typename T> struct std::formatter<std::vector<T>> {
  constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

  auto format(const std::vector<T> &vector, std::format_context &ctx) const {
    // std::string out = "";
    // for (int i = 0; i < vector.size() - 1; i++)
    //   out += std::format("\t{},\n", vector[i]);
    // out += std::format("\t{}", vector[vector.size() - 1]);
    // return std::format_to(ctx.out(), "[\n{}\n]", out);
    std::string out = "";
    for (const T &e : vector | std::ranges::views::take(vector.size() - 1))
      out += std::format("{}, ", e);
    out += std::format("{}", vector[vector.size() - 1]);
    return std::format_to(ctx.out(), "[{}]", out);
  }
};

// struct collider {
//   virtual void foo() const = 0;
// };
// struct poly : collider {
//   int a = 0;
//   poly(const float x, const float y, const unsigned n, const float r) {}
//   void foo() const override {}
// };
// struct circle : collider {
//   int b = 1;
//   circle(const float x, const float y, const float r) {}
//   void foo() const override {}
// };
//
// struct base_object {
//   float mass;
//   base_object(const float mass) : mass{mass} {}
//
//   virtual void draw() const = 0;
// };
// std::vector<std::unique_ptr<base_object>> objs{};
//
// template <typename colltype> struct object;
// template <> struct object<poly> : base_object, poly {
//   object(const float x, const float y, const unsigned n, const float r,
//          const float mass)
//       : base_object(mass), poly(x, y, n, r) {}
//
//   void draw() const override { println("poly"); }
//
//   static object<poly> &New(const float x, const float y, const unsigned n,
//                            const float r, const float mass) {
//     auto &a =
//         objs.emplace_back(std::make_unique<object<poly>>(x, y, n, r, mass));
//     return static_cast<object<poly> &>(*a);
//   }
// };
// template <> struct object<circle> : base_object, circle {
//   object(const float x, const float y, const float r, const float mass)
//       : base_object(mass), circle(x, y, r) {}
//
//   void draw() const override { println("circle"); }
//
//   static object<circle> &New(const float x, const float y, const float r,
//                              const float mass) {
//     auto &a =
//         objs.emplace_back(std::make_unique<object<circle>>(x, y, r, mass));
//     return static_cast<object<circle> &>(*a);
//   }
// };
//
// struct p {
//   std::vector<int> data{1, 4, 9, 194, 129};
//   int offset;
//
//   using view_t =
//       std::ranges::transform_view<std::ranges::ref_view<std::vector<int>>,
//                                   std::function<int(int)>>;
//   view_t transformit;
//
// private:
//   view_t datat() {
//     println("refreshing it");
//     const int offset = this->offset;
//     return data | std::views::transform(std::function<int(int)>{
//                       [offset](const int n) { return n + offset; }});
//   }
//
// public:
//   view_t it() const { return transformit; }
//
//   void setOffset(const int o) {
//     offset = o;
//     transformit = datat();
//   }
//   p(const int o) : offset{0}, transformit{datat()} { setOffset(o); }
// };

import test_module;

int main() {
  std::vector<int> v{};
  for (int i = 0; i < 10; i++)
    v.emplace_back(random_int(-10, 10));

  println(v);
  // auto range = std::views::counted(v.begin() + 4, 5);
  auto range = std::ranges::subrange(v.begin(), v.begin() + 3);
  println(std::vector<int>(range.begin(), range.end()));

  // const double cutoff =
  //     std::reduce(v.begin(), v.end()) / static_cast<double>(v.size());

  // println(v);
  // println("cutoff: {}", cutoff);

  // auto part = std::partition(v.begin(), v.end(),
  //                            [cutoff](int i) { return i < cutoff; });
  // std::vector<int> left(v.begin(), part);
  // println("left: {}", left);
  // std::vector<int> right(part, v.end());
  // println("right: {}", right);
}