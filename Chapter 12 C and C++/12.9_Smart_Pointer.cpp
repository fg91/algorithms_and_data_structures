// "Copyright 2019 <Fabio M. Graetz>"
#include <iostream>
#include <vector>

template<typename T>
class SmartPointer {
 private:
  T * rawptr{nullptr};
  unsigned int * count{nullptr};

 public:
  SmartPointer() {
    std::cerr << "No parameter constructor" << std::endl;
    count = new unsigned int(1);
  }

  explicit SmartPointer(T * ptr) {
    std::cerr << "Constructor" << std::endl;
    rawptr = ptr;
    count = new unsigned int(1);
  }

  SmartPointer(const SmartPointer<T> & other) {
    std::cerr << "Copy constructor" << std::endl;
    rawptr = other.rawptr;
    count  = other.count;
    ++(*count);
  }

  SmartPointer<T> &operator=(const SmartPointer<T> &other) {
    std::cerr << "Copy assignment operator" << std::endl;
    if (this == &other) return *this;

    if (*count > 0) {
      remove();
    }

    rawptr = other.rawptr;
    count  = other.count;
    ++(*count);
    return *this;
  }

  ~SmartPointer() {
    remove();
  }

  T &operator*() {
    return *rawptr;
  }

  unsigned int getCount() const {
    return *count;
  }

 protected:
  void remove() {
    --(*count);
    if (*count == 0) {
      std::cerr << "Object destroyed" << std::endl;
      delete rawptr;
      delete count;
      rawptr = nullptr;
      count  = nullptr;
    } 
  }
};

int main() {
  SmartPointer<std::vector<int>> smptr;
  SmartPointer<std::vector<int>> smptr1(new std::vector<int>{1, 2});

  {
    std::vector<int> *v = new std::vector<int>{1, 2, 3};
    SmartPointer<std::vector<int>> smptr2(v);
    smptr1 = smptr2;  // the object smptr1 originally pointed to is destroyed here
    std::cout << "Value: " << (*smptr2)[1] << " " << (*smptr1)[1] << std::endl;
    std::cout << "Count: " << smptr2.getCount() << " " << smptr1.getCount() << std::endl;

    // smptr2 goes out of scope here but smptr1 is still in scope until end of main
    // so object they point to is not destroyed yet.
  }
  std::cout << "End" << std::endl;
  return 0;
}
