#ifndef EARLEY_EARLEYALGO_H
#define EARLEY_EARLEYALGO_H

#include "Grammar.h"
#include <utility>
#include <vector>
#include <iostream>
#include <set>

using Rule = Grammar::Rule;

class EarlyAlgo {
 public:
  explicit EarlyAlgo(Grammar g) : grammar_(std::move(g)) {}
  bool Check(const std::string& s);
 private:
  struct Situation {
    Rule rule_;
    size_t point_;
    size_t i_;

    Situation(Rule rule, size_t point, size_t i) : rule_(std::move(rule)), point_(point), i_(i) {};

    bool operator<(const Situation& another) const;
  };

  std::string string_to_check_;
  std::vector<std::set<Situation>> states_;
  Grammar grammar_;

  void Predict(size_t j);
  void Scan(size_t j, char x);
  void Complete(size_t j);
};


#endif