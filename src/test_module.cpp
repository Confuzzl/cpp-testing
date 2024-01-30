module;

#define IMPL
#include <iostream>

module test_module;
void module_test() { std::cout << "module test\n"; }

void A::foo() { std::cout << "foo\n"; }

void B::bar() { std::cout << "bar\n"; }