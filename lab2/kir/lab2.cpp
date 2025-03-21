#include "lab2.hpp"

template <typename T>
class Uniqe_pointer {
 private:
  T* unique_object;

 public:
  Uniqe_pointer(T* n_obj) { unique_object = n_obj; }
  Uniqe_pointer(const Uniqe_pointer& n) = delete;
  Uniqe_pointer& operator=(const Uniqe_pointer& n) = delete;
  Uniqe_pointer(Uniqe_pointer&& n) {
    unique_object = n.get();
    n.reset();
  }
  Uniqe_pointer& operator=(Uniqe_pointer&& n) {
    unique_object = n.get();
    n.reset();
  }
  ~Uniqe_pointer() {}
  T& operator*() const { return *unique_object; }
  T* operator->() const { return unique_object; }
  T* get() const { return unique_object; }
  void reset(T* p = nullptr) { unique_object = p; }
};

template <typename D>
class Shared_pointer {
 private:
  D* object;
  std::size_t* count;

 public:
  Shared_pointer(D* n_obj) {
    object = n_obj;
    count = new std::size_t;
    *count = 1;
  }
  Shared_pointer(const Shared_pointer& n) {
    object = n.object;
    count = n.count;
    *count += (std::size_t)1;
  }
  Shared_pointer& operator=(const Shared_pointer& n) {
    object = n.object;
    count = n.count;
    *count += (std::size_t)1;
  }
  Shared_pointer(Shared_pointer&& n) {
    object = n.object;
    count = n.count;
    n.object = nullptr;
    n.count = nullptr;
  }
  Shared_pointer& operator=(Shared_pointer&& n) {
    object = n.object;
    count = n.count;
    n.object = nullptr;
    n.count = nullptr;
  }
  ~Shared_pointer() {
    if (count != nullptr) {
      *count = *count - 1;
      if (*count == 0) {
        delete count;
      }
    }
  }
  D& operator*() { return *object; }
  D* operator->() { return object; }
  D* get() { return object; }
  void reset(D* p = nullptr) {
    object = p;
    count = new std::size_t;
    *count = 1;
  }
  std::size_t use_count() { return *count; }
};
