#include <iostream>
int main()
{
  double x = 0.5649;
  for(int i = 0; i < 100; i++) {
    std::cout << i << "\t" << x << std::endl;
    x = (int(x*x*1e6) % 10000)/1.0e4;
  }
}
