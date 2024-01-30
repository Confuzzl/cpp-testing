export module test_module:b;

export struct A;
export struct B {
  A *m;

  void bar();
};