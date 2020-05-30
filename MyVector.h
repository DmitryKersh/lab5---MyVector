#ifndef LAB5___MYVECTOR_MYVECTOR_H
#define LAB5___MYVECTOR_MYVECTOR_H

#include <iostream>
#include <cstddef>
#include <string>
#include <cmath>

using std::cout;
using std::endl;

template <typename T>
class MyVector {
  T* Data;
  size_t length;
  size_t Capacity;

  void extend(float coefficient){
    reserve(size_t(ceil(Capacity * coefficient)));
  }

public:
  MyVector<T>(){
    length = 0;
    Capacity = 1;
    Data = new T[1];
  }

  MyVector<T>(const MyVector<T>& other){
    length = other.length;
    Capacity = other.Capacity;
    Data = new T[other.Capacity];
    for (size_t i = 0; i < length; i++){
      Data[i] = other.Data[i];
    }
  }

  explicit MyVector<T>(const size_t& size){
    length = size;
    Capacity = size;
    Data = new T[size];
  }

  MyVector<T>(const std::initializer_list<T>& init_list){
    length = init_list.size();
    Capacity = init_list.size();
    Data = new T[length];
    size_t i = 0;
    for (const T& item : init_list){
      Data[i] = item;
      i++;
    }
  }

  ~MyVector(){
    delete[] Data;
  }

  T& operator[](size_t index) const {
      return Data[index];
  }

  MyVector& operator= (const MyVector<T>& other){
    if (this != &other) {
      length = other.length;
      Capacity = other.Capacity;

      Data = new T[other.Capacity];

      for (size_t i = 0; i < length; i++) {
        Data[i] = other.Data[i];
      }
    }
    return *this;
  }

  T& at(size_t index) {
    if (index > Capacity){
      throw std::out_of_range("Tried to access " + std::to_string(index)
                              + "th element, but vector has capacity of "
                              + std::to_string(Capacity)
                              + " elements\n");
    }
    return Data[index];
  }
  T& at(size_t index) const {
    if (index > Capacity){
      throw std::out_of_range("Tried to access " + std::to_string(index)
                                                  + "th element, but vector has capacity of"
                                                  + std::to_string(Capacity)
                                                  + " elements\n");
    }
    return Data[index];
  }

  T& front() { return Data[0]; }
  T& front() const { return Data[0]; }

  T& back() { return Data[length - 1]; }
  T& back() const { return Data[length - 1]; }

  T* data() const { return Data; }

  bool empty() const { return length; }

  size_t size() const { return length; }

  void reserve(size_t new_cap){
    if (new_cap > Capacity){
      T* new_data = new T[new_cap];

      for (size_t i = 0; i < length; i++){
        new_data[i] = Data[i];
      }

      delete[] Data;

      Data = new_data;
      Capacity = new_cap;
    }
  }

  size_t capacity() const { return Capacity; }

  void clear() {
    delete[] Data;

    Data = new T[1];
    length = 0;
    Capacity = 1;
  }
  // inserts BEFORE pos
  void insert(size_t pos, const T& value){
    if (length == Capacity) extend(1.5);

    for (size_t i = length - 1; i >= pos; i--){
      Data[i + 1] = Data[i];
    }

    length++;
    at(pos) = value;
  }

  void erase(size_t pos){
    for (size_t i = pos; i < length - 1; i++){
      Data[i] = Data[i + 1];
    }
    length--;
  }

  void push_back(const T& value){
    if (length == Capacity)
      extend(1.5);
    Data[length] = value;
    length++;
  }

  void pop_back(){ if (length > 0) length--; }

  void resize(size_t new_size){
    T* new_data = new T[new_size];

    for (size_t i = 0; i < std::min(new_size, length); i++){
      new_data[i] = Data[i];
    }
    for (size_t i = std::min(new_size, length); i < new_size; i++){
      new_data[i] = T{};
    }
    length = new_size;
    Capacity = new_size;

    delete[] Data;
    Data = new_data;
  }

  void swap(MyVector<T>& other){
    std::swap(Data, other.Data);
    std::swap(Capacity, other.Capacity);
    std::swap(length, other.length);
  }


};

template<typename T>
std::ostream& operator<<(std::ostream& out, const MyVector<T>& vec){
  if (!vec.size()){
    out << "<empty>" << endl;
    return out;
  }
  for (int i = 0; i < vec.size() - 1; i++){
    //out << '[' << i << "] " << vec[i] << endl;
    out << vec[i] << ", ";
  }
  out << vec.back();
  out << endl;
  return out;
}

#endif // LAB5___MYVECTOR_MYVECTOR_H
