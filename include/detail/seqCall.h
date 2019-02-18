#ifndef __SEQUENTIEL_CALL_H
#define __SEQUENTIEL_CALL_H

#include <optional>

namespace pipeline {

template <typename Arg, typename Call> auto seqCall(Arg arg, Call call) {
  if constexpr (Call::is_filter) {
    if (call(arg)) {
      return std::optional<decltype(arg)>(arg);
    } else {
      return std::optional<decltype(arg)>{};
    }
  } else if constexpr (Call::is_trafo) {
    return std::optional<decltype(call(arg))>(call(arg));
  }
}

template <typename Arg, typename Call, typename... Calls>
auto seqCall(Arg arg, Call call, Calls... calls) {
  if constexpr (Call::is_filter) {
    if (call(arg)) {
      return seqCall(arg, calls...);
    } else {
      return decltype(seqCall(arg, calls...)){};
    }
  } else if constexpr (Call::is_trafo) {
    return seqCall(call(arg), calls...);
  }
}

} // namespace pipeline

#endif
