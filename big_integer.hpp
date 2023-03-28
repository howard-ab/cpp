#pragma once
#include <iostream>
#include <string>
#include <vector>

class BigInt {
 public:
  BigInt();
  BigInt(const std::string&);
  BigInt(int64_t);
  BigInt(const BigInt& other);
  BigInt& operator*=(const BigInt&);
  BigInt& operator+=(const BigInt&);
  BigInt& operator-=(const BigInt&);
  BigInt& operator/=(const BigInt&);
  BigInt& operator%=(const BigInt&);
  BigInt& operator=(const BigInt& other);
  BigInt& operator=(int);
  friend bool operator<(const BigInt&, const BigInt&);
  friend bool operator>(const BigInt&, const BigInt&);
  friend bool operator==(const BigInt&, const BigInt&);
  friend bool operator!=(const BigInt&, const BigInt&);
  friend bool operator>=(const BigInt&, const BigInt&);
  friend bool operator<=(const BigInt&, const BigInt&);
  BigInt& operator++();
  BigInt operator++(int);
  BigInt& operator--();
  BigInt operator--(int);
  BigInt operator-() const;
  void Eraser();
  friend std::ostream& operator<<(std::ostream&, const BigInt&);
  friend std::istream& operator>>(std::istream&, BigInt&);
  friend BigInt operator%(const BigInt&, const BigInt&);
  friend BigInt operator*(const BigInt&, const BigInt&);
  friend BigInt operator/(const BigInt&, const BigInt&);
  void Swap(BigInt&);
  void Helper(const BigInt&);

 private:
  std::vector<int> nums_;
  bool sign_ = false;
  bool Sing() const;
  size_t Length() const;
  std::vector<int> Getter() const;
  static void DivFor(BigInt&, BigInt&, BigInt&, BigInt&, BigInt);
  void ForPlus(size_t&, int&, int&, const BigInt&);
  static const int kBase = 1000000000;
  static const int kDivider = 10;
};

BigInt operator+(const BigInt&, const BigInt&);
BigInt operator-(const BigInt&, const BigInt&);