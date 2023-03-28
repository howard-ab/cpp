#include "string.hpp"

#include <vector>

String::String() : size_(0), capacity_(0), str_(nullptr) {}
String::~String() { delete[] str_; }
String::String(const String& str) {
  size_ = str.size_;
  str_ = new char[size_ + 1];
  capacity_ = str.capacity_;
  for (size_t i = 0; i < size_; ++i) {
    str_[i] = str.str_[i];
  }
  str_[size_] = '\0';
}
String::String(const char* my_str) {
  size_t length = strlen(my_str);
  capacity_ = length;
  str_ = new char[capacity_ + 1];
  size_ = length;
  Memcpy(str_, my_str, size_);
  str_[size_] = '\0';
}

String::String(size_t size, char character) {
  size_ = size;
  capacity_ = size * 2;
  str_ = new char[capacity_];
  for (size_t i = 0; i < size; ++i) {
    str_[i] = character;
  }
}

void String::PopBack() {
  if (size_ != 0) {
    --size_;
    str_[size_] = '\0';
  }
}

void String::PushBack(char str_character) {
  ++size_;
  if (size_ - 1 == 0 && capacity_ == size_ - 1) {
    capacity_ = 1;
  } else if (size_ != 0 && capacity_ <= size_) {
    capacity_ *= 2;
  }

  char* tmp_str = new char[size_];
  for (size_t i = 0; i < size_ - 1; ++i) {
    tmp_str[i] = str_[i];
  }
  delete[] str_;
  str_ = new char[capacity_ + 1];
  for (size_t i = 0; i < size_ - 1; ++i) {
    str_[i] = tmp_str[i];
  }
  delete[] tmp_str;
  str_[size_ - 1] = str_character;
  str_[size_] = '\0';
}

void String::Resize(size_t new_size) {
  if (capacity_ < new_size) {
    capacity_ = new_size;
    char* tmp = new char[size_];
    Memcpy(tmp, str_, size_);
    delete[] str_;
    str_ = new char[capacity_];
    Memcpy(str_, tmp, size_);
    delete[] tmp;
  }
  size_ = new_size;
}
void String::Resize(size_t new_size, char character) {
  if (capacity_ < new_size) {
    capacity_ = new_size;
    char* tmp = new char[size_];
    Memcpy(tmp, str_, size_);
    delete[] str_;
    str_ = new char[capacity_];
    Memcpy(str_, tmp, size_);
    delete[] tmp;
  }
  for (size_t i = size_; i < new_size; ++i) {
    str_[i] = character;
  }
  size_ = new_size;
}
void String::ShrinkToFit() {
  if (capacity_ > size_) {
    capacity_ = size_;
    char* tmp = new char[size_];
    Memcpy(tmp, str_, size_);
    delete[] str_;
    str_ = new char[capacity_];
    Memcpy(str_, tmp, size_);
    delete[] tmp;
  }
}
char& String::operator[](size_t current) { return str_[current]; }
const char& String::operator[](size_t current) const { return str_[current]; }

char& String::Front() { return str_[0]; }

const char& String::Front() const { return str_[0]; }

char& String::Back() { return str_[size_ - 1]; }

const char& String::Back() const { return str_[size_ - 1]; }

char* String::Data() { return str_; }

size_t String::Size() const { return size_; }

bool String::Empty() const { return size_ == 0; }

size_t String::Capacity() const { return capacity_; }

void String::Clear() {
  if (str_ != nullptr) {
    str_[0] = '\0';
  }
  size_ = 0;
}

String& String::operator=(const String& str) {
  if (&str != this) {
    delete[] str_;
    size_ = str.size_;
    str_ = new char[size_ + 1];
    for (size_t i = 0; i < size_; ++i) {
      str_[i] = str.str_[i];
    }
    capacity_ = str.capacity_;
    str_[size_] = '\0';
  }
  return *this;
}
String& String::operator+=(const String& str) {
  if (capacity_ < str.size_ + size_) {
    capacity_ = str.size_ + size_;
    char* tmp = new char[size_];
    Memcpy(tmp, str_, size_);
    delete[] str_;
    str_ = new char[1 + capacity_];
    Memcpy(str_, tmp, size_);
    delete[] tmp;
  }
  for (size_t i = 0; i < str.size_; ++i) {
    str_[size_ + i] = str.str_[i];
  }
  size_ += str.size_;
  str_[size_] = '\0';
  return *this;
}

void String::Swap(String& str) {
  std::swap(size_, str.size_);
  std::swap(capacity_, str.capacity_);
  std::swap(str_, str.str_);
}
void String::Memcpy(char* src, const char* srg, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    src[i] = srg[i];
  }
}

bool String::operator>(const String& str2) const {
  size_t min = std::min(size_, str2.size_);
  for (size_t i = 0; i < min; ++i) {
    if (str_[i] <= str2.str_[i]) {
      continue;
    }
    return true;
  }
  return size_ > min;
}
void String::Reserve(size_t new_cap) {
  if (capacity_ < new_cap) {
    capacity_ = new_cap;
    char* tmp = new char[size_];
    Memcpy(tmp, str_, size_);
    delete[] str_;
    str_ = new char[capacity_ + 1];
    Memcpy(str_, tmp, size_);
    str_[size_] = '\0';
    delete[] tmp;
  }
}

std::vector<String> String::Split(const String& delim) {
  std::vector<String> res;
  String tmp;
  String block;
  if (this->Empty()) {
    res.push_back("");
    return res;
  }
  for (size_t i = 0; i < size_; ++i) {
    if (tmp.Size() < delim.size_ && str_[i] == delim[tmp.Size()]) {
      tmp.PushBack(str_[i]);
    } else {
      if (!tmp.Empty()) {
        block += tmp;
        tmp.Clear();
      }
      block.PushBack(str_[i]);
    }
    if (tmp.Size() == delim.size_) {
      tmp.Clear();
      res.push_back(block);
      block.Clear();
    }
  }
  if (!tmp.Empty()) {
    block += tmp;
  }
  res.push_back(block);
  return res;
}

String String::Join(const std::vector<String>& strings) const {
  String res = "";
  if (!strings.empty()) {
    res += strings[0];
  }
  for (size_t i = 1; i < strings.size(); i++) {
    res += *this;
    res += strings[i];
  }
  return res;
}

bool String::operator<(const String& str2) const {
  size_t min = std::min(size_, str2.size_);
  for (size_t i = 0; i < min; ++i) {
    if (str_[i] == str2.str_[i]) {
      continue;
    }
    return str_[i] < str2.str_[i];
  }
  return str2.size_ > min;
}
std::ostream& operator<<(std::ostream& cout, String str) {
  cout << str.Data();
  return cout;
}
std::istream& operator>>(std::istream& cout, String& str) {
  char input;
  while (cout.get(input) && input != '\n' && input != ' ' && input != '\0' &&
         input != '\t') {
    str.PushBack(input);
  }
  return cout;
}

String operator+(const String& lhs, const String& rhs) {
  String tmp = lhs;
  tmp += rhs;
  return tmp;
}

String operator*(const String& str, size_t num) {
  String tmp = "";
  uint64_t num_copy = num;
  if (num < 2) {
    return (num == 0) ? tmp : str;
  }
  num /= 2;
  tmp = str * num;
  tmp += tmp;

  return (num_copy % 2) != 0 ? tmp += str : tmp;
}
String& String::operator*=(size_t ans) {
  *this = *this * ans;
  return *this;
}

bool String::operator>=(const String& str) const { return !(*this < str); }

bool String::operator<=(const String& str) const { return !(*this > str); }

bool String::operator==(const String& str) const {
  if (str.size_ != size_) {
    return false;
  }
  for (size_t i = 0; i < size_; ++i) {
    if (str[i] == str_[i]) {
      continue;
    }
    return false;
  }
  return true;
}

bool String::operator!=(const String& str) const { return !(*this == str); }
