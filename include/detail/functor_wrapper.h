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

template <typename T> struct PtrFilter : public BaseWrapper<T>{
	constexpr PtrFilter(T x) : BaseWrapper<T>(x) {}
};
template <typename T> struct is_ptr_filter{
	static constexpr bool value = false;
};
template <typename T> struct is_ptr_filter<PtrFilter<T>>{
	static constexpr bool value = true;
};

template <typename T> struct FilterX : public BaseWrapper<T> {
  constexpr FilterX(T x) : BaseWrapper<T>(x) {}
};
template <typename T> struct is_filter{
	static constexpr bool value = false;
};
template <typename T> struct is_filter<FilterX<T>>{
	static constexpr bool value = true;
};

template <typename T> struct TrafoX : public BaseWrapper<T> {
  constexpr TrafoX(T x) : BaseWrapper<T>(x) {}
};
template <typename T> struct is_transformation{
	static constexpr bool value = false;
};
template <typename T> struct is_transformation<TrafoX<T>>{
	static constexpr bool value = true;
};

} // namespace pipeline
#endif
