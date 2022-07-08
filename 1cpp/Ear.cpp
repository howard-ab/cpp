include "ear.h"

bool EarlyAlgo::Situation::operator<(const Situation& another) const {
  if (rule_ == another.rule_) {
    if (point_ == another.point_) {
      return i_ < another.i_;
    }
    return point_ < another.point_;
  }
  return rule_ < another.rule_;
}

bool EarlyAlgo::Check(const std::string& s) {
  string_to_check_ = s;
  states_.clear();
  states_.resize(string_to_check_.size() + 1);
  states_[0].insert(Situation(grammar_.getRules()[0], 0, 0));

  size_t current_size;
  do {
    current_size = states_[0].size();
    Predict(0);
    Complete(0);
  } while (states_[0].size() != current_size);

  for (size_t i = 1; i <= string_to_check_.size(); ++i) {
    Scan(i - 1, string_to_check_[i - 1]);
    do {
      current_size = states_[i].size();
      Predict(i);
      Complete(i);
    } while (states_[i].size() != current_size);
  }
  Situation end(grammar_.getRules()[0], 1, 0);
  return states_[string_to_check_.size()].find(end) !=
         states_[string_to_check_.size()].end();
}

void EarlyAlgo::Predict(size_t j) {
  std::vector<Situation> new_situations;
  for (auto situation : states_[j]) {
    for (const auto& rule : grammar_.getRules()) {
      if (rule.first == situation.rule_.second[situation.point_]) {
        new_situations.emplace_back(rule, 0, j);
      }
    }
  }
  for (const auto& situation : new_situations) {
    states_[j].insert(situation);
  }
}

void EarlyAlgo::Scan(size_t j, char x) {
  for (auto situation : states_[j]) {
    if (situation.rule_.second[situation.point_] == x) {
      states_[j + 1].emplace(situation.rule_, situation.point_ + 1, situation.i_);
    }
  }
}

void EarlyAlgo::Complete(size_t j) {
  std::vector<Situation> new_situations;
  for (const auto& situation_a : states_[j]) {
    if (situation_a.point_ != situation_a.rule_.second.size()) continue;
    for (auto situation_b : states_[situation_a.i_]) {
      if (situation_b.rule_.second[situation_b.point_] == situation_a.rule_.first) {
        new_situations.emplace_back(situation_b.rule_, situation_b.point_ + 1, situation_b.i_);
      }
    }
  }
  for (const auto& situation : new_situations) {
    states_[j].insert(situation);
  }
}