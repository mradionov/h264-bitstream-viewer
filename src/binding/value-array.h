#ifndef VALUE_ARRAY_H
#define VALUE_ARRAY_H

#include <array>

#include <emscripten/bind.h>

template <typename T, size_t N>
class ArrayElementInitializer {
public:
  static void init(emscripten::value_array<T>& arr) {
    ArrayElementInitializer<T, N - 1>::init(arr);
    arr.element(emscripten::index<N - 1>());
  }
};

template <typename T>
class ArrayElementInitializer<T, 0> {
public:
  static void init(emscripten::value_array<T>& arr) {}
};

// Use it to bind value_array and all of it's elements. Out of the box,
// you have to call `.element(emscripten::index<i>())` for each index you have,
// which is not nice when you have a lot of elements. The templates above
// recursively initialize all N array elements.
//
// Inspired by:
// http://nnarain.github.io/2019/01/19/GameboyCore-in-the-Web!.html
// https://github.com/nnarain/nnarain.github.io/issues/75
//
// Usage:
//
// initValueArray<int, 10>("my_array_int_10");
//
template <typename Element, size_t N>
void initValueArray(const char *name) {
  using Arr = std::array<Element, N>;

  emscripten::value_array<Arr> arr(name);
  ArrayElementInitializer<Arr, N>::init(arr);
}

// This is a workaround for Emscripten value_array - not sure how to bind
// 2d-arrays. Expected the following syntax to work but it does not:
//
// emscripten::value_array<std::array< std::array<int, 4>, 2>>("array_int_2_4");
//
// Thus instead of binding 2d-arrays, I am using a custom getter+setter on
// a 2d-array member of a struct. Member must be a 2d-array with dimensions NxM.
// Getter will convert 2d-array into a 1d-array and return it as a result.
// 1d-array still has to have a binding of the resulting size.
//
// Usage:
//
// struct Some {
//   int foo[2][4];
// };
//
// // 2 * 4 = 8 - size of resulting 1d array
//
// emscripten::value_object<Some>("Some")
//  .field("foo",
//    &readArray2d<int, 2, 4, int[2][4], Some, &Some::foo>,
//    &writeArray2d<int, 2, 4, Some>
//  );
//
// initValueArray<int, 8>("my_array_int_8");
//

template<
  typename T,
  size_t N,
  size_t M,
  typename Member,
  typename Object,
  Member Object::*member
>
std::array<T, N*M> readArray2d(const Object& obj) {
  std::array<T, N*M> arr1d;

  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      arr1d[i * M + j] = (obj.*member)[i][j];
    }
  }

  return arr1d;
}

template<typename T, size_t N, size_t M, typename Object>
void writeArray2d(Object& obj, std::array<T, N*M>) {}

#endif
