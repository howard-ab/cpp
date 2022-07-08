#ifndef EARLEY_GRAMMAR_H
#define EARLEY_GRAMMAR_H

#include <cstdio>
#include <iostream>
#include <vector>
#include <exception>
#include <string>

class IncorrectRule : public std::exception {
  const char* what() const noexcept override {
    return "Incorrect rule\n";
  }
};

class Grammar {
 public:
  using Rule = std::pair<char, std::string>;
  Grammar() = default;
  explicit Grammar(const std::vector<std::string>& rules);
  const std::vector<Rule>& getRules() const;
  friend std::istream& operator>>(std::istream& is, Grammar& grammar);

 private:
  Rule ParseEnteredRule(const std::string& rule);
  static bool IsRuleFormatCorrect(const std::string& rule);
  static bool IsLeftOperandCorrect(const char left_operand);
  std::vector<char> non_terminals_;
  std::vector<char> alphabet_;
  std::vector<Rule> rules_;
};

const Grammar::Rule bad_rule = {' ', " "};

#endif