#ifndef __FUNCTOR_WRAPPER__H
#define __FUNCTOR_WRAPPER__H

#include <functional>

namespace pipeline {

template<typename T>
struct BaseWrapper {
  constexpr BaseWrapper(T x) : t_(x) {}

  template <typename... Us> constexpr auto operator()(Us &&... us) {
    return t_(std::forward<Us>(us)...);
  }

private:
  T t_;
};

template <typename T> struct FilterX : public BaseWrapper<T> {
  constexpr FilterX(T x) : BaseWrapper<T>(x) {}

  static constexpr bool is_trafo = false;
  static constexpr bool is_filter = true;
};

template <typename T> struct TrafoX : public BaseWrapper<T> {
  constexpr TrafoX(T x) : BaseWrapper<T>(x) {}

  static constexpr bool is_trafo = true;
  static constexpr bool is_filter = false;
};

} // namespace pipeline
#endif
