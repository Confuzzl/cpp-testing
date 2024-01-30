// #include <iostream>
//
//// struct A {
////   // private:
////   virtual void foo() { std::cout << "A\n"; }
//// };
////
//// struct B : A {
////   void foo() override { std::cout << "B\n"; }
//// };
////
//// template <typename T>
//// concept HasFoo = requires(T t) { t.foo(); };
////
//// template <typename T> struct FooHolder {
////   void callFoo(T t) { t.foo(); }
//// };
////
//// template <HasFoo T> struct ConceptFooHolder : FooHolder<T> {};
////
//// int main() {
////   A a{};
////   B b{};
////   ConceptFooHolder<A> i{};
////   i.callFoo(a);
////   ConceptFooHolder<B> j{};
////   j.callFoo(b);
////   FooHolder<A> k{};
////   k.callFoo(a);
////   FooHolder<B> l{};
////   l.callFoo(b);
////   FooHolder<int> m{};
////   m.callFoo(1);
//// }
//
//// struct A {
////   int m;
////   A(int &&m) : m{m} {}
////   ~A() { std::cout << "dtor\n"; }
//// };
////
//// void foo(A &&n) { std::cout << n.m << "\n"; }
////
//// #include <format>
////// #include <Psapi.h>
//// #include <Windows.h>
////
//// int main() {
////   MEMORYSTATUSEX memInfo;
////   memInfo.dwLength = sizeof(MEMORYSTATUSEX);
////   GlobalMemoryStatusEx(&memInfo);
////   DWORDLONG totalVirtualMem;
////   DWORDLONG virtualMemUsed;
////   DWORDLONG totalPhysicalMem;
////   DWORDLONG physicalMemUsed;
////
////   totalVirtualMem = memInfo.ullTotalPageFile;
////   virtualMemUsed = totalVirtualMem - memInfo.ullAvailPageFile;
////   totalPhysicalMem = memInfo.ullTotalPhys;
////   physicalMemUsed = totalPhysicalMem - memInfo.ullAvailPhys;
////   std::cout << std::format("{}/{} {:.2f}% \n", virtualMemUsed,
////   totalVirtualMem,
////                            100.0 * virtualMemUsed / totalVirtualMem);
////   std::cout << std::format("{}/{} {:.2f}% \n", physicalMemUsed,
////                            totalPhysicalMem,
////                            100.0 * physicalMemUsed / totalPhysicalMem);
////
////   int i = 0;
////
////   totalVirtualMem = memInfo.ullTotalPageFile;
////   virtualMemUsed = totalVirtualMem - memInfo.ullAvailPageFile;
////   totalPhysicalMem = memInfo.ullTotalPhys;
////   physicalMemUsed = totalPhysicalMem - memInfo.ullAvailPhys;
////   std::cout << std::format("{}/{} {:.2f}% \n", virtualMemUsed,
////   totalVirtualMem,
////                            100.0 * virtualMemUsed / totalVirtualMem);
////   std::cout << std::format("{}/{} {:.2f}% \n", physicalMemUsed,
////                            totalPhysicalMem,
////                            100.0 * physicalMemUsed / totalPhysicalMem);
//// }
//
// #include <format>
// #include <initializer_list>
// #include <memory>
// #include <vector>
//
// struct A {
//  static int count;
//  int id;
//
//  A() : id{count++} { std::cout << std::format("ctor {}\n", id); }
//  A(const A &a) : id{count++} {
//    std::cout << std::format("copy ctor {}\n", id);
//  }
//  A(A &&a) noexcept : id{count++} {
//    std::cout << std::format("move ctor {}\n", id);
//  }
//  ~A() { std::cout << std::format("dtor {}\n", id); }
//};
// int A::count = 0;
//
// struct B {
//  std::shared_ptr<A> m;
//  std::vector<std::shared_ptr<A>> vectorPtrA;
//
//  // B(const std::vector<std::shared_ptr<A>> &a) : vectorPtrA{a} {
//  //   std::cout << "const vec ref\n";
//  //   print();
//  // }
//
//  B() {}
//
//  B(std::vector<std::shared_ptr<A>> &&a) : vectorPtrA{std::move(a)} {
//    std::cout << "vec rvalue ref\n";
//    print();
//  }
//
//  // B(A &&a) : m{std::make_unique<A>(a)} { print1(m); }
//
//  void setM(std::shared_ptr<A> &&p) {
//    m = std::move(p);
//    print1(m);
//  }
//
//  void setM2(std::shared_ptr<A> &p) {
//    m = p;
//    print1(m);
//  }
//
//  void addA(std::shared_ptr<A> &&a) {
//    print1(a);
//    vectorPtrA.emplace_back(a);
//  }
//
//  void print() {
//    for (const auto &p : vectorPtrA)
//      print1(p);
//  }
//
//  void print1(const std::shared_ptr<A> &p) {
//    std::cout << std::format("{} count: {}\n", (*p).id, p.use_count());
//  }
//};
//
// struct C {
//  C() { std::cout << "ctor\n"; }
//  C(const C &c) { std::cout << "copy ctor\n"; }
//  C(C &&c) { std::cout << "move ctor\n"; }
//
//  C &operator=(C &c) { std::cout << "copy assignment\n"; }
//  C &operator=(C &&c) noexcept { std::cout << "move assignment\n"; }
//};
//
// struct A1 {};
// struct B1 : A1 {};
// struct C1 {
//  std::unique_ptr<A1> m;
//};
//
// int main() {
//  C1 c1{std::make_unique<A1>()};
//  C1 c2{std::make_unique<B1>()};
//}