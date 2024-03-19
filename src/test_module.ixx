export module test_module;

export template <typename T> struct tem;

export template <> struct tem<int> {
  void foo();
};