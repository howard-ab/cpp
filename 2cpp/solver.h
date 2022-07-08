#ifndef FORMAL_SOLVER_H
#define FORMAL_SOLVER_H

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <exception>

class IncorrectRegexp: public std::exception {
  const char* what() const noexcept override {
    return "Incorrect regexp";
  }
};

class Solver {
 public:
  Solver() = default;
  Solver(const Solver&) = delete;
  Solver(const Solver&&) = delete;
  Solver operator=(const Solver&) = delete;
  Solver operator=(const Solver&&) = delete;
  Solver(const std::string& regexp) : regexp_(regexp) {}
  size_t FindTheShortestWord(size_t max_number, char letter);

 private:
  const size_t INF = static_cast<size_t>(1e9);
  const std::string alphabet_ = "abc";
  typedef std::vector<size_t> State;
  std::stack<State> states_;
  std::string regexp_;
  char letter_to_find_;
  size_t amount_of_letters_;

  State AddLetter(char symbol);
  State Disjoint();
  State Merge(const State& one, const State& two);
  State Concatenate();
  State Append(const State& one, const State& two);
  State Closure();
  State CreateAnswerState();
};

#endif