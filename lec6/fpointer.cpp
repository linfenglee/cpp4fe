// Example program
#include <iostream>
#include <string>


int foo(int a, int b) {return a + b;}

int foo2(int a, int b) {return a - b;}


int main()
{
  // function name stores the address of the function
  std::cout << "foo = " << foo << std::endl;
  std::cout << "foo = " << (void *) foo << std::endl;

  // assigning the address of the function foo to fp
  int (*fp)(int, int) = foo2;
  std::cout << "fp = " << fp << std::endl;
  // call function foo(5, 9) through fp.
  std::cout << (*fp)(5, 9) << std::endl;
  return 0;
}
