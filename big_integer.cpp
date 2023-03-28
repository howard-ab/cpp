#include "big_integer.hpp"

#include <algorithm>
#include <iostream>
#include <string>

BigInt::BigInt() { this->sign_ = true; }

BigInt& BigInt::operator=(int other) {
  *this = BigInt(other);
  return *this;
}

BigInt::BigInt(const std::string& str) {
  if (str[0] == '-') {
    if (str.length() == 2 && str[1] == '0') {
      sign_ = true;
      nums_.push_back(0);
      return;
    }
    sign_ = false;
  } else {
    sign_ = true;
    nums_.push_back(str[0] - '0');
  }
  for (size_t i = 1; i < str.size(); ++i) {
    nums_.push_back(str[i] - '0');
  }
  std::reverse(nums_.begin(), nums_.end());
}

BigInt::BigInt(int64_t num) : BigInt(std::to_string(num)) {}

bool BigInt::Sing() const { return sign_; }

bool operator<(const BigInt& left, const BigInt& right) {
  bool asign = left.Sing();
  bool xsign = right.Sing();
  if (!asign && !xsign) {
    return -right < -left;
  }
  if (!asign) {
    return true;
  }
  if (!xsign) {
    return false;
  }
  size_t len1 = left.Length();
  size_t len2 = right.Length();
  if (len1 != len2) {
    return len1 < len2;
  }
  std::vector<int> anum = left.Getter();
  std::vector<int> xnum = right.Getter();
  for (int i = static_cast<int>(anum.size()) - 1; i >= 0; --i) {
    if (anum[i] != xnum[i]) {
      return anum[i] < xnum[i];
    }
  }
  return false;
}

size_t BigInt::Length() const { return nums_.size(); }

bool operator==(const BigInt& left, const BigInt& right) {
  return !(left < right) && !(left > right);
}

bool operator>(const BigInt& left, const BigInt& right) { return right < left; }

bool operator!=(const BigInt& first, const BigInt& right) {
  return !(first == right);
}

bool operator>=(const BigInt& num, const BigInt& sec) { return !(num < sec); }

std::istream& operator>>(std::istream& cin, BigInt& num) {
  std::string str;
  cin >> str;
  num = BigInt(str);
  return cin;
}

BigInt& BigInt::operator=(const BigInt& other) {
  if (this != &other) {
    sign_ = other.sign_;
    nums_ = other.nums_;
  }
  return *this;
}

std::ostream& operator<<(std::ostream& cout, const BigInt& num) {
  if (!num.sign_ && num != 0) {
    cout << '-';
  }
  for (int i = num.nums_.size() - 1; i >= 0; --i) {
    cout << num.nums_[i];
  }

  return cout;
}

BigInt operator+(const BigInt& first, const BigInt& second) {
  BigInt copy = first;
  copy += second;
  return copy;
}

BigInt& BigInt::operator++() {
  *this += BigInt(1);
  return *this;
}
void BigInt::ForPlus(size_t& ind, int& carry, int& res, const BigInt& num) {
  for (; ind < num.nums_.size(); ++ind) {
    res = (num.nums_[ind] + carry) % kDivider;
    if (carry + num.nums_[ind] >= kDivider) {
      carry = 1;
    } else {
      carry = 0;
    }
    nums_.push_back(res);
  }
}
BigInt& BigInt::operator+=(const BigInt& num) {
  int carry = 0;
  int res;
  size_t ind = 0;
  if (this->sign_ == num.sign_) {
    for (ind = 0; ind < nums_.size(); ++ind) {
      if (ind < num.nums_.size()) {
        res = (nums_[ind] + num.nums_[ind] + carry) % kDivider;
        carry = (nums_[ind] + num.nums_[ind] + carry) / kDivider;
      } else {
        res = (nums_[ind] + carry) % kDivider;
        if (carry + nums_[ind] >= kDivider) {
          carry = 1;
        } else {
          carry = 0;
        }
      }
      nums_[ind] = res;
    }
    ForPlus(ind, carry, res, num);
    nums_.push_back(carry);
    BigInt::Eraser();
  } else {
    BigInt::Helper(num);
  }
  if (nums_.size() == 1 && nums_[0] == 0 && !sign_) {
    sign_ = !sign_;
  }
  return *this;
}

BigInt::BigInt(const BigInt& other) {
  sign_ = other.sign_;
  nums_ = other.nums_;
}

void BigInt::Helper(const BigInt& num) {
  BigInt tmp = num;
  int res;
  int carry;
  size_t ind = 0;
  if ((!sign_ && -(*this) < tmp) || (*this < -tmp && sign_)) {
    BigInt::Swap(tmp);
  }
  carry = 0;
  for (; ind < tmp.nums_.size(); ++ind) {
    res = (nums_[ind] - tmp.nums_[ind] - carry);
    if ((nums_[ind] - tmp.nums_[ind] - carry) >= 0) {
      carry = 0;
    } else {
      carry = 1;
    }
    if (carry != 0) {
      res += kDivider;
    }
    nums_[ind] = res;
  }
  while (carry != 0) {
    res = nums_[ind] - carry;
    carry = res < 0 ? 1 : 0;
    res += (carry != 0 ? kDivider : 0);
    nums_[ind] = res;
    ++ind;
  }
  BigInt::Eraser();
}

void BigInt::Swap(BigInt& tmp) {
  std::swap(tmp.nums_, nums_);
  std::swap(tmp.sign_, sign_);
}

BigInt BigInt::operator++(int) {
  BigInt tmp = *this;
  *this += BigInt(1);
  return tmp;
}

BigInt BigInt::operator-() const {
  BigInt answer = *this;
  BigInt zero(0);
  if (answer != zero) {
    answer.sign_ = !answer.sign_;
  }
  return answer;
}

BigInt& BigInt::operator--() {
  *this -= BigInt(1);
  return *this;
}

BigInt BigInt::operator--(int) {
  BigInt tmp = *this;
  *this -= BigInt(1);
  return tmp;
}

BigInt& BigInt::operator-=(const BigInt& num) {
  *this = *this - num;
  return *this;
}

BigInt operator*(const BigInt& left, const BigInt& right) {
  BigInt answer;
  if (left == 0 || right == 0) {
    answer = BigInt(0);
    answer.sign_ = true;
    return answer;
  }
  answer.nums_.assign(left.nums_.size() + right.nums_.size(), 0);
  for (size_t i = 0; i < left.nums_.size(); i++) {
    for (size_t j = 0; j < right.nums_.size(); j++) {
      answer.nums_[i + j] += left.nums_[i] * right.nums_[j];
    }
  }
  int carry = 0;
  for (int& num : answer.nums_) {
    num += carry;
    carry = num / BigInt::kDivider;
    num %= BigInt::kDivider;
  }
  answer.Eraser();
  answer.sign_ = ((left.sign_ ^ right.sign_) == 0);
  return answer;
}

BigInt operator/(const BigInt& left, const BigInt& right) {
  BigInt ans = left;
  ans /= right;
  return ans;
}

BigInt operator%(const BigInt& left, const BigInt& right) {
  return left - ((left / right) * right);
}

void BigInt::Eraser() {
  if (nums_.empty()) {
    nums_.push_back(0);
    sign_ = true;
  } else {
    while (nums_.size() > 1 && nums_.back() == 0) {
      nums_.pop_back();
    }
    if (nums_.size() == 1 && nums_[0] == 0) {
      sign_ = true;
    }
  }
}

BigInt& BigInt::operator/=(const BigInt& other) {
  BigInt first = *this;
  BigInt second = other;
  BigInt ans;
  BigInt zero = 0;
  BigInt cur;
  if (ans.nums_.empty()) {
    ans.nums_.clear();
  }
  if (second < 0) {
    second = -second;
  }
  if (first < 0) {
    first = -first;
  }
  if (!zero.nums_.empty()) {
    zero.nums_.clear();
  }
  zero.sign_ = true;
  DivFor(first, second, zero, ans, cur);
  for (size_t j = 0; j < ans.nums_.size() / 2; ++j) {
    std::swap(ans.nums_[j], ans.nums_[ans.nums_.size() - j - 1]);
  }
  ans.sign_ = (sign_ == other.sign_);
  *this = ans;
  Eraser();
  return *this;
}

void BigInt::DivFor(BigInt& first, BigInt& second, BigInt& zero, BigInt& ans,
                    BigInt cur) {
  for (int i = static_cast<int>(first.nums_.size()) - 1; i >= 0; --i) {
    for (size_t j = 0; j < zero.nums_.size() / 2; ++j) {
      std::swap(zero.nums_[j], zero.nums_[zero.nums_.size() - j - 1]);
    }
    zero.nums_.push_back(first.nums_[i]);
    for (size_t j = 0; j < zero.nums_.size() / 2; ++j) {
      std::swap(zero.nums_[j], zero.nums_[zero.nums_.size() - j - 1]);
    }
    while (zero.nums_.size() > 1 && zero.nums_.back() == 0) {
      zero.nums_.pop_back();
    }
    if (zero >= second) {
      int left = 1;
      int right = kBase;
      while (right - left > 1) {
        int mid = (right + left) / 2;
        (cur = second) *= mid;
        if (cur <= zero) {
          left = mid;
        } else {
          right = mid;
        }
      }
      ans.nums_.push_back(left);
      zero -= ((cur = second) *= left);
    } else {
      ans.nums_.push_back(0);
    }
  }
}

BigInt& BigInt::operator%=(const BigInt& other) {
  *this = *this % other;
  return *this;
}

BigInt& BigInt::operator*=(const BigInt& num) {
  *this = *this * num;
  return *this;
}

BigInt operator-(const BigInt& first, const BigInt& second) {
  return first + (-second);
}

bool operator<=(const BigInt& num, const BigInt& sec) { return !(num > sec); }

std::vector<int> BigInt::Getter() const { return nums_; }