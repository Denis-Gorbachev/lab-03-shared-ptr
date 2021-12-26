// Copyright 2021 Denis <denis.gorbachev2002@yandex.ru>

#include <stdexcept>
#include <shared_ptr.hpp>

// конструктор по умолчанию
template <typename T>
SharedPtr<T>::SharedPtr()
    :_ptr(nullptr), _count_ptr(nullptr) {}

// конструктор
template <typename T>
SharedPtr<T>::SharedPtr(T *ptr)
    :_ptr(ptr), _count_ptr(new std::atomic<unsigned int>) {
  *_count_ptr = 1;
}

// конструктор копирования
template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T> &r)
    :_ptr(r._ptr), _count_ptr(r._count_ptr){
  ++*_count_ptr;
}

// конструктор перемещения
template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T> &&r)
    :_ptr(r._ptr), _count_ptr(r._count_ptr) {
  r._ptr = nullptr;
  r._count_ptr = nullptr;
}

// деструктор
template <typename T>
SharedPtr<T>::~SharedPtr<T>() {
  if (_count_ptr) {
    if (*_count_ptr == 1) {
      _count_ptr = nullptr;
      _ptr = nullptr;
    } else {
      --(*_count_ptr);
    }
  }
}

// перегрузка оператора перемещения
template <typename T>
auto SharedPtr<T>::operator=(SharedPtr<T> &&r) -> SharedPtr<T>& {
  _ptr = std::move(r._ptr);
  if (this->_count_ptr!= nullptr){
    --*_count_ptr;
  }
  _count_ptr = std::move(r._count_ptr);
  ++(*_count_ptr);
  return *this;
}

// getter указателя
template <typename T>
auto SharedPtr<T>::get() -> T * {
  return _ptr;
}

// перегрузка оператора копирования
template <typename T>
auto SharedPtr<T>::operator=(const SharedPtr &r) -> SharedPtr& {
  _ptr = r._ptr;
  if (_count_ptr != nullptr){
    --*_count_ptr;
  }
  _count_ptr = r._count_ptr;
  ++*_count_ptr;
  return *this;
}

// оператор проверяет, указывает ли указатель на объект
template <typename T>
SharedPtr<T>::operator bool() const {
  if (_ptr != nullptr)
    return true;
  return false;
}

// перегрузка оператора разыменования
template <typename T>
auto SharedPtr<T>::operator*() const -> T& {
  return *get();
}

// перегрузка оператора доступа к членам класса по указателю
template <typename T>
auto SharedPtr<T>::operator->() const -> T* {
  return get();
}

template <typename T>
void SharedPtr<T>::reset() {
  if (_count_ptr != nullptr){
    _ptr = nullptr;
    if (*_count_ptr != 1){
      --*_count_ptr;
    }
    else{
      delete _count_ptr;
    }
    _count_ptr = nullptr;
  }
}

template <typename T>
void SharedPtr<T>::reset(T *ptr) {
  if (_count_ptr != nullptr) {
    --(*_count_ptr);
  }
  _count_ptr = new std::atomic<uint>;
  *_count_ptr = 1;
    *_ptr = ptr;
}

template <typename T>
void SharedPtr<T>::swap(SharedPtr &r) {
  SharedPtr<T> tmp(r);
  r._ptr = _ptr;
  r._count_ptr = _count_ptr;
  this->_ptr = std::move(tmp._ptr);
  this->_count_ptr = std::move(tmp._count_ptr);
}

// возвращает количество объектов SharedPtr, которые ссылаются на тот же управляемый объект
template <typename T>
auto SharedPtr<T>::use_count() const -> size_t {
  return *_count_ptr;
}
