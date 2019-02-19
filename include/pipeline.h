#ifndef __PIPELINE__H
#define __PIPELINE__H

#include "detail/functor_wrapper.h"
#include "detail/seqCall.h"

namespace pipeline{

template<typename T>
auto
makeFilter(T x)
{
	return FilterX<T>(x);
}

template<typename T>
auto
makeTransformation(T x)
{
	return TrafoX<T>(x);
}

template<typename T>
auto
makeTrafoThroughPtr(T x)
{
	return PtrFilter<T>(x);
}

template <typename InputIterator, typename OutputIterator, typename... Fs>
auto pipeline(InputIterator f, InputIterator l, OutputIterator o,
                           Fs... fs)
{
	while(f != l)
	{
		auto optVal = seqCall(*f, fs ...);
		if(optVal.has_value())
		{
			*o = optVal.value();
			++o;
		}
		++f;
	}
	return o;
}

}
#endif
