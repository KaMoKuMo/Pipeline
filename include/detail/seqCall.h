#ifndef __SEQUENTIEL_CALL_H
#define __SEQUENTIEL_CALL_H

#include <optional>

namespace pipeline {

template <typename Arg, typename Call> auto seqCall(Arg arg, Call call) {
  static_assert(is_filter<Call>::value || is_transformation<Call>::value ||
                    is_ptr_filter<Call>::value,
                "The Functors, named f, must either be wrapped by a "
                "pipeline::makeFilter(f), pipeline::makePtrFilter(f), or by a "
                "pipeline::makeTransformation(f) Call");
  if constexpr (is_filter<Call>::value) {
    if (call(arg)) {
      return std::optional<decltype(arg)>(arg);
    } else {
      return std::optional<decltype(arg)>{};
    }
  } else if constexpr (is_transformation<Call>::value){
    return std::optional<decltype(call(arg))>(call(arg));
  } else if constexpr (is_ptr_filter<Call>::value) {
		if(call(arg))
		{
			return std::optional<decltype(call(arg))>(call(arg));
		}
		else
		{
			return std::optional<decltype(call(arg))>{};
		}
	}
}

template <typename Arg, typename Call, typename... Calls>
auto seqCall(Arg arg, Call call, Calls... calls) {
  static_assert(is_filter<Call>::value || is_transformation<Call>::value ||
                    is_ptr_filter<Call>::value,
                "The Functors, named f, must either be wrapped by a "
                "pipeline::makeFilter(f), pipeline::makePtrFilter(f), or by a "
                "pipeline::makeTransformation(f) Call");
  if constexpr (is_filter<Call>::value) {
    if (call(arg)) {
      return seqCall(arg, calls...);
    } else {
      return decltype(seqCall(arg, calls...)){};
    }
  } else if constexpr (is_transformation<Call>::value){
    return seqCall(call(arg), calls...);
  } else if constexpr (is_ptr_filter<Call>::value) {
		if(call(arg))
		{
			return seqCall(call(arg), calls... );
		}
		else
		{
			return decltype(seqCall(call(arg), calls...)){};
		}
	}
}

} // namespace pipeline

#endif
