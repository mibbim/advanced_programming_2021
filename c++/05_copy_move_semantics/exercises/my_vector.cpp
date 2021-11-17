#include <iostream>

template <typename T>
class vector {
  // we use raw poiters bc we want to use std::allocator and it's easier
  T* data{nullptr};
  std::size_t _size{0};
  std::size_t _capacity{0};

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

  void move_data_to(T* tmp) {
    // std vector copies, we move which is better
    // std::copy(data, data + _size, tmp);
    for (std::size_t i{0}; i < _size; ++i)
      tmp[i] = std::move(data[i]);
    delete[] data;
    data = tmp;
  }

 public:
  vector() = default;
  ~vector() {
    if (data)
      delete[] data;
  };

  auto capacity() { return _capacity; };
  auto size() { return _size; };

  void push_back(const T& x) { _push_back(x); }
  void push_back(T&& x) { _push_back(std::move(x)); }

  /* */
  void reserve(std::size_t n) {  // public bc may useful in api for user
    auto tmp = new T[n];         // it may invoje default ctors 
    move_data_to(tmp);
    _capacity = n;
  }
};

int main() {
  vector<int> v;
  for (auto i = 0; i < 33; ++i) {
    v.push_back(i);
    std::cout << v.capacity() << ", " << v.size() << std::endl;
  }
}