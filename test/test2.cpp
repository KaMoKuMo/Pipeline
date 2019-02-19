#include "../include/pipeline.h"
#include <algorithm>
#include <iostream>
#include <optional>
#include <vector>

bool isBigger10(double x) { return x > 10; }
bool isLess10(double x) { return x < 10; }

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
  auto squaringTrafo = pipeline::makeTransformation(f2);

  std::vector<double> v = {1., 2.2, 3.3, 4.4, 10.1, 24.5, 0, -3.234};

  std::vector<double> v2;
  pipeline::pipeline(v.begin(), v.end(), std::back_inserter(v2),
                     pipeline::makeFilter(f),
										 squaringTrafo,
										 pipeline::makeTransformation([](auto x){return x/2;}),
										 squaringTrafo,
                     pipeline::makeFilter(isBigger10));
  print(v2);

  std::vector<double> v3;
  pipeline::pipeline(v.begin(), v.end(), std::back_inserter(v3),
                     pipeline::makeFilter([](auto x) { return x > 2; }),
                     pipeline::makeFilter(isLess10));
  print(v3);

// The following is not good practice and therefore will not compile.

// pipeline::pipeline(v.begin(), v.end(), std::back_inserter(v3), f); //<- will not compile

// One would need to read the function body
// to understand the role it is playing in the pipeline.
// To encourage good practice either the makeFilter or makeTransformation
// wrappers are required. (type_traits for callable and checking the return
// valeu to be boolean might have been sufficient).


  return 1;
}
