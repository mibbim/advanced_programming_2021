struct Foo {
  Foo();
  Foo(const Foo&);             // const Foo& is  l-value reference
  Foo(Foo&&);                  // Foo && is a r-value referece
  Foo& operator=(const Foo&);  // copy assigment
  Foo& operator=(Foo&&);       // move assignemet
};

// r and l value refence are built in tyoe
// std::move() it's a cast a from l to r value reference

// shallow copy:
/*
Copy by value all the members of the object.
It creates a second object with the pointers pointing
to the same memory locations of the first.
The compiler by default implements this.
 */

// deep copy:
/*
Copy element by element.
The compiler has no idea on how to implement a deep copy
 */

// Smart pointers:

/* functions:
T * .get
void .reset(T *)
T* release() // release the ownership and return a raw pointer

 */

// Then when we have pointers the copy semantics should be implemneted by the
// developer

template <typename T>
void swap(T& x, T& y) {
  auto tmp = x;  // copy ctor
  x = y;         // copy assignment
  y = tmp;       // copy assignment
}

/*
move is a real swap: the original resources are stolen
after a move the state of the object is valid (dtor can be invoked)
but it's value is undefined
*/

sizeof(v);  // pointer of vector + size of size_t
area_of(v)  // sizeof(v) + memory in the heap
areaof(v)>>sizeof(v)

// With unique pointer we can use the default move 