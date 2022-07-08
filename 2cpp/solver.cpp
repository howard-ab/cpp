#include "solver.h"


size_t Solver::FindTheShortestWord(const size_t max_number, const char letter) {
  letter_to_find_ = letter;
  amount_of_letters_ = max_number;
  State final = CreateAnswerState();

  return (final[amount_of_letters_] == INF ? -1 : final[amount_of_letters_]);
}

Solver::State Solver::CreateAnswerState() {
  for (const auto symbol : regexp_) {
    if (alphabet_.find(symbol) != std::string::npos) {
      states_.push(AddLetter(symbol));
    } else if (symbol == '+') {
      states_.push(Disjoint());
    } else if (symbol == '.') {
      states_.push(Concatenate());
    } else if (symbol == '*') {
      states_.push(Closure());
    }
  }
  if (states_.size() != 1) {
    throw IncorrectRegexp();
  }
  return states_.top();
}

Solver::State Solver::AddLetter(char symbol) {
  State result(amount_of_letters_ + 1, INF);
  if (symbol == letter_to_find_) {
    result[1] = 1;
  } else {
    result[0] = 1;
  }
  return result;
}

Solver::State Solver::Append(const State& one, const State& two) {
  State result(amount_of_letters_ + 1, INF);
  for (size_t index = 0; index <= amount_of_letters_; ++index) {
    for (size_t i = 0; i <= index; ++i) {
      result[index] = std::min(result[index], one[i] + two[index - i]);
    }
  }
  return result;
}

Solver::State Solver::Concatenate() {
  if (states_.size() < 2) {
    throw IncorrectRegexp();
  }
  State state_one = states_.top();
  states_.pop();
  State state_two = states_.top();
  states_.pop();
  return Append(state_one, state_two);
}

Solver::State Solver::Merge(const State& one, const State& two) {
  State result(amount_of_letters_ + 1, INF);
  for (size_t i = 0; i <= amount_of_letters_; ++i) {
    result[i] = std::min(one[i], two[i]);
  }
  return result;
}

Solver::State Solver::Disjoint() {
  if (states_.size() < 2) {
    throw IncorrectRegexp();
  }
  State state_one = states_.top();
  states_.pop();
  State state_two = states_.top();
  states_.pop();
  return Merge(state_one, state_two);
}

Solver::State Solver::Closure() {
  if (states_.empty()) {
    throw IncorrectRegexp();
  }
  std::stack<State> closure_states;
  const State curr_state = states_.top();
  states_.pop();
  closure_states.push(curr_state);
  for (size_t iteration = 1; iteration < amount_of_letters_; ++iteration) {
    State other = closure_states.top();
    closure_states.push(Append(curr_state, other));
  }
  for (size_t iteration = 1; iteration < amount_of_letters_; ++iteration) {
    State one = closure_states.top();
    closure_states.pop();
    State two = closure_states.top();
    closure_states.pop();
    closure_states.push(Merge(one, two));
  }
  State result = closure_states.top();
  result[0] = 0;
  return result;
}