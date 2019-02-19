#include "../include/pipeline.h"
#include <iostream>
#include <vector>

struct A {
  A(double a) : a_(a) {}
  double a_;
};

struct B {
  B(A* aPtr) : aPtr_(aPtr) {}
	B() = default;
  A* aPtr_ = nullptr;
};

struct C {
  C(B* bPtr) : bPtr_(bPtr) {}
	C() = default;

  B* bPtr_ = nullptr;
};

int main() {
  auto a = A(1.0);
  auto b = B(&a);
	auto c = C(&b);
	auto b2 = B();
	auto c2 = C(&b2);
	auto a3 = A(2.);
	auto b3 = B(&a3);
	auto c3 = C(&b3);
	auto c4 = C();

  std::vector<C*> inputData = {&c,
														   &c,
														   &c4,				//oops !
														   &c2, 			//oops ! 
														   &c3};

	std::vector<double> processableData;

	pipeline::pipeline(inputData.begin(),inputData.end()
										 , std::back_inserter(processableData)
										 , pipeline::makeTrafoThroughPtr([](auto* c){return c->bPtr_;})
									   , pipeline::makeTrafoThroughPtr([](auto* b){return b->aPtr_;})
  									 , pipeline::makeTrafoThroughPtr([](auto* a){return a->a_;}));
	for(auto data : processableData)
	{
		std::cout<<data<<'\t';
	}
	std::cout<<'\n';

  return 1;
}
