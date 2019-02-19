#ifndef __COPY_IF__H
#define __COPY_IF__H

#include "transformation_with_filter.h"

namespace pipeline {

template <typename InputIterator, typename OutputIterator, typename... Fs>
auto copy_if(InputIterator f, InputIterator l, OutputIterator o, Fs... fs) {
  return transform_with_filter(f, l, o, fs...);
}

} // namespace pipeline

#endif
