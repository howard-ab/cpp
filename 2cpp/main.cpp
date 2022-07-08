#include <iostream>
#include "solver.h"

int main() {
  std::string regexp = "acb..bab.c. * .ab.ba. + . + *a.";
  char letter_to_find = 'b';
  int letter_number = 3;
  Solver solver(regexp);
  try {
    size_t answer = solver.FindTheShortestWord(letter_number, letter_to_find);
    if (answer == -1) {
      std::cout << "INF";
    } else {
      std::cout << answer;
    }
  } catch(IncorrectRegexp& ex) {
    std::cout << "ERROR";
  }

  return 0;
}