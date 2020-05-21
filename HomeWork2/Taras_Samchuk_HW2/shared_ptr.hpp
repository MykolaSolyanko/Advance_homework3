
// #include <iostream>

template <typename T>
struct Deleter {
 public:
  typedef T* pointer;
  void operator()(pointer t) const {
    std::cout << "()-----------------\n";
    delete t;
  }
};

template <typename T, typename F = Deleter<T>>
class SharedPtr;

template <typename T, typename F>
class SharedPtr {
 public:
  typedef T* pointer;

  SharedPtr() = default;  //?
  SharedPtr(const SharedPtr& ptr){
      _ptr=ptr._ptr;
      _count=ptr._count;
      _count++;
      /* ++ */
      //   _ptr= ptr
  };  //?
  SharedPtr& operator=(const SharedPtr&){/* ++ */};
  SharedPtr(pointer ptr) { /* ++ */
    // _ptr = ptr->_ptr;
    // _count=ptr._count;
    // _count++;
  };
  SharedPtr& operator=(pointer ptr){
      /*code*/  //+
  };

  SharedPtr(SharedPtr&& ptr){/* ++ */};

  // Replaces the managed object with an object pointed to by ptr
  void reset() {
    pointer tmp = _ptr;
    _ptr = nullptr;
    return tmp;
  };
  // Replaces the managed object with an object
  // pointed to by ptr
  void reset(pointer ptr) {
    free();
    _ptr = ptr;
  };
  // Replaces the managed object with an object pointed to by ptr
  void reset(pointer ptr, Deleter<T> del){};
  // Returns the stored pointer.
  T* get() { return _ptr; };
  // Returns the number of different shared_ptr instances
  // managing the current object
  long use_count() { return *_count; };

  // like get() != nullptr
  explicit operator bool() { return (_ptr != nullptr) ? true : false; };
  pointer operator->() { return &(this->operator*()); };
  T& operator*() { return *_ptr; };
  // if Unique_ptr store array
  T& operator[](long index);

 private:
  pointer _ptr{nullptr};
  long* _count{nullptr};
  void free(){
      if(_count){
          /*code*/
      };
      /* F(_ptr); */};
};

// template <typename T, typename F>
// T& SharedPtr<T, F> operator[](long index) = delete;
// T& SharedPtr<T,F>

// template <typename T, typename F>
// T& SharedPtr<T*, F> operator[](long index) {
//   return &(_ptr + index);
// };
