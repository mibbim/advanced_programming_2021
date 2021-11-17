#include <iostream>
//#include <>
#include "instrumented.hpp"
#include <memory>  //std::allocator
#include <utility
// #include <vector>

template <typename T, typename Allocator = std::allocator<T>>
class vector {
  // we use raw poiters bc we want to use std::allocator and it's easier
  T* data{nullptr};
  std::size_t _size{0};
  std::size_t _capacity{0};
  Allocator allocator;

  void check_capacity() {  // #############
    if (_size < _capacity)
      return;
    // _size == _capacity
    reserve(2 * _size);
  }

  template <typename X>
  void _push_back(X&& x) {
    if (_size == 0)
      reserve(8);
    else
      check_capacity();  // don't do today what we can do tomorrow
    data[_size] = std::forward<X>(x);
    ++_size;
  }

  void clean_data() {
    for (std::size_t i{0}; i < _size; ++i) {  // destry elements
      traits_alloc::destroy(allocator, data + i);
    }

    traits_alloc::deallocate(allocator, data, _capacity);
  }

  void move_data_to(T* tmp) {
    // std vector copies, we move which is better

    // std::copy(data, data + _size, tmp);

    // for (std::size_t i{0}; i < _size; ++i)
    //   tmp[i] = std::move(data[i]);

    // std::uninitialized_move(data, data + _size, tmp);  // dince c++17
    for (std::size_t i{0}; i < _size; ++i)
      // construct the object at the passed address
      // new (tmp + i) T{std::move(data[i])};

      traits_alloc::construct(allocator, tmp + i, std::move(data[i]));

    // delete[] data;
    clean_data();

    data = tmp;
  }

 public:
  // typetrait tecniques
  // type that provides unified interface for allocating destroy
  using traits_alloc = std::allocator_traits<Allocator>;

  vector() = default;
  ~vector() {
    if (data)
      clean_data();
  };

  vector(Allocator a) : allocator{std::move(a)} {}

  void push_back(const T& x) { _push_back(x); }
  void push_back(T&& x) { _push_back(std::move(x)); }

  /* */
  void reserve(std::size_t n) {  // public bc may useful in api for user
    // auto tmp = new T[n];         // it may invoje default ctors
    auto tmp = traits_alloc::allocate(allocator, n);  // allocate raw memory
    move_data_to(tmp);
    _capacity = n;
  }

  // emplace back can have whatever number of arguments
  template <typename... Types>
  void emplace_back(Types&&... args) {  // forrwarding refence
    check_capacity();
    traits_alloc::construct(allocator, data + _size,
                            T{std::forward<Types>(args)...});
  }

  auto capacity() { return _capacity; };
  auto size() { return _size; };
};

int main() {
  vector<int> v;
  for (auto i = 0; i < 33; ++i) {
    v.push_back(i);
    std::cout << v.capacity() << ", " << v.size() << std::endl;
  }

  std::pair<int, double> p;
  p.first = 7;
  p.second = 9.9;

  vector<std::pair<int, int>> vp;                // vector of pairs
  vp.push_back(std::make_pair<int, int>(3, 4));  // can pass 1 argument
  vp.push_back(std::pair<int, int>(3, 4));       // can pass 1 argument
  vp.push_back({3, 4});                          // can pass 1 argument

  vp.emplace_back(3, 4);  // this is the difference between emplace and push.
  // the performance is basically the same
  using value_type = instrumented<int>;
  {
    vector<value_type> v2;
    value_type::initialize(1);
    for (auto i = 0; i < 9; ++i) {
      v2.push_back(i);
      std::cout << v.capacity() << ", " << v.size() << std::endl;
    }
  }
  value_type::print_summary(;)
}