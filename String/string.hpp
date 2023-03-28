#pragma once

#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

class String {
 public:
  String();
  ~String();
  String(const String&);
  String(size_t, char);
  String(const char*);

  bool Empty() const;
  void Clear();
  void PushBack(char);
  void PopBack();
  void Resize(size_t);
  void Resize(size_t, char);
  void Swap(String&);
  void ShrinkToFit();
  static void Memcpy(char*, const char*, size_t);
  void Reserve(size_t);
  size_t Size() const;
  size_t Capacity() const;
  char& Front();
  char* Data();
  const char* Data() const;
  char& operator[](size_t);
  const char& operator[](size_t) const;
  const char& Front() const;
  const char& Back() const;
  char& Back();
  String& operator=(const String&);
  String& operator*=(size_t ans);
  String& operator+=(const String&);
  std::vector<String> Split(const String& delim = " ");
  String Join(const std::vector<String>&) const;
  bool operator>(const String&) const;
  bool operator<(const String&) const;
  bool operator>=(const String&) const;
  bool operator<=(const String&) const;
  bool operator!=(const String&) const;
  bool operator==(const String&) const;

 private:
  size_t size_;
  size_t capacity_;
  char* str_;
};

String operator+(const String& lhs, const String& rhs);
String operator*(const String& str, size_t num);
std::ostream& operator<<(std::ostream&, String str);
std::istream& operator>>(std::istream&, String& str);