// Copyright 2021 Denis <denis.gorbachev2002@yandex.ru>

#ifndef INCLUDE_SHARED_PTR_HPP_
#define INCLUDE_SHARED_PTR_HPP_

#include <cstdio>
#include <atomic>
template <typename T>
class SharedPtr {
 public:
  SharedPtr();
  explicit SharedPtr(T* ptr);
  SharedPtr(const SharedPtr& r);
  SharedPtr(SharedPtr&& r);
  ~SharedPtr();
  auto operator=(const SharedPtr& r) -> SharedPtr&;
  auto operator=(SharedPtr&& r) -> SharedPtr&;

  // проверяет, указывает ли указатель на объект
  explicit operator bool() const;
  auto operator*() const -> T&;
  auto operator->() const -> T*;

  auto get() -> T*;
  void reset();
  void reset(T* ptr);
  void swap(SharedPtr& r);
  // возвращает количество объектов SharedPtr, которые ссылаются на тот же управляемый объект
  auto use_count() const -> size_t;

 private:
  std::atomic_uint *_count_ptr{};
  T *_ptr{};
};

#endif // INCLUDE_SHARED_PTR_HPP_
