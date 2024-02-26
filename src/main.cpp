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

void println(const std::string &str = "") { std::cout << str << "\n"; }
template <typename... Args>
void println(std::format_string<Args...> str, Args &&...args) {
  println(std::format(str, std::forward<Args>(args)...));
}

template <typename T> struct info_type {
  static constexpr bool copy_con = std::is_copy_constructible<T>::value;
  static constexpr bool copy_ass = std::is_copy_assignable<T>::value;
  static constexpr bool move_con = std::is_move_constructible<T>::value;
  static constexpr bool move_ass = std::is_move_assignable<T>::value;
};
template <typename T> struct std::formatter<info_type<T>> {
  constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

  auto format(const info_type<T> &info, std::format_context &ctx) const {
    return std::format_to(ctx.out(), "cc: {} ca: {} mc: {} ma: {}",
                          info_type<T>::copy_con, info_type<T>::copy_ass,
                          info_type<T>::move_con, info_type<T>::move_ass);
  }
};
template <typename T> struct std::formatter<std::vector<T>> {
  constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

  auto format(const std::vector<T> &vector, std::format_context &ctx) const {
    std::string out = "";
    for (int i = 0; i < vector.size() - 1; i++)
      out += std::format("\t{},\n", vector[i]);
    out += std::format("\t{}", vector[vector.size() - 1]);
    return std::format_to(ctx.out(), "[\n{}\n]", out);
  }
};

struct collider {
  virtual void foo() const = 0;
};
struct poly : collider {
  int a = 0;
  poly(const float x, const float y, const unsigned n, const float r) {}
  void foo() const override {}
};
struct circle : collider {
  int b = 1;
  circle(const float x, const float y, const float r) {}
  void foo() const override {}
};

struct base_object {
  float mass;
  base_object(const float mass) : mass{mass} {}

  virtual void draw() const = 0;
};
std::vector<std::unique_ptr<base_object>> objs{};

template <typename colltype> struct object;
template <> struct object<poly> : base_object, poly {
  object(const float x, const float y, const unsigned n, const float r,
         const float mass)
      : base_object(mass), poly(x, y, n, r) {}

  void draw() const override { println("poly"); }

  static object<poly> &New(const float x, const float y, const unsigned n,
                           const float r, const float mass) {
    auto &a =
        objs.emplace_back(std::make_unique<object<poly>>(x, y, n, r, mass));
    return static_cast<object<poly> &>(*a);
  }
};
template <> struct object<circle> : base_object, circle {
  object(const float x, const float y, const float r, const float mass)
      : base_object(mass), circle(x, y, r) {}

  void draw() const override { println("circle"); }

  static object<circle> &New(const float x, const float y, const float r,
                             const float mass) {
    auto &a =
        objs.emplace_back(std::make_unique<object<circle>>(x, y, r, mass));
    return static_cast<object<circle> &>(*a);
  }
};

int main() {
  const auto &a = object<poly>::New(0.0f, 0.0f, 3, 1.0f, 1.0f);
  const auto &b = object<circle>::New(0.0f, 0.0f, 2.0f, 2.0f);

  // std::vector<base_object *> objs{&a, &b};
  for (const auto &obj : objs)
    obj->draw();
}