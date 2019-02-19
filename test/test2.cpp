#include "../include/copy_if.h"
#include "../include/transformation_with_filter.h"
#include <algorithm>
#include <iostream>
#include <optional>
#include <vector>

bool isBigger10(double x) { return x > 10; }

template <typename T> void print(std::vector<T> const &v) {
  for (auto w : v) {
    std::cout << w << '\t';
  }
  std::cout << '\n';
}

int main() {
  auto f = [](double x) { return x < 3.0; };
  auto f2 = [](double x) { return x * x; };

  auto onlyLessThan3 = pipeline::makeFilter(f);
  auto onlyBiggerThan10 = pipeline::makeFilter(isBigger10);
  auto squaring = pipeline::makeTransformation(f2);

  std::vector<double> v = {1., 2.2, 3.3, 4.4, 10.1, 24.5, 0, -3.234};

  std::vector<double> v2;
  pipeline::transform_with_filter(v.begin(), v.end(), std::back_inserter(v2),
                                  onlyLessThan3, squaring, squaring,
                                  onlyBiggerThan10);
  print(v2);

  std::vector<double> v3;
  pipeline::copy_if(v.begin(), v.end(), std::back_inserter(v3),
                    pipeline::makeFilter([](auto x) { return x > 2; }),
                    pipeline::makeFilter([](auto y) { return y < 10; }));

/* The following will not compile, since the lambda wasn't wrapped. The error
 * message is thought to be complete. (Notify if you think differently)

  pipeline::copy_if(v.begin(), v.end(), std::back_inserter(v3),
                    [](auto x) { return x > 2; });

										*/
  print(v3);

  return 1;
}
