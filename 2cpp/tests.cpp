#include "solver.h"
#include <gtest/gtest.h>

TEST(FIRST_FROM_DOC, A_LETTER_CORRECT) {
  std::string regexp = "ab + c.aba. * .bac. + . + *";
  Solver solver(regexp);
  size_t answer = solver.FindTheShortestWord(7, 'a');
  EXPECT_EQ(answer, 11);
}

TEST(FIRST_FROM_DOC, A_LETTER_INCORRECT) {
  std::string regexp = "ab + c.aba. * .bac. + . + *";
  Solver solver(regexp);
  size_t answer = solver.FindTheShortestWord(5, 'a');
  EXPECT_NE(answer, 5);
}

TEST(FIRST_FROM_DOC, B_LETTER_CORRECT) {
  std::string regexp = "ab + c.aba. * .bac. + . + *";
  Solver solver(regexp);
  size_t answer = solver.FindTheShortestWord(2, 'b');
  EXPECT_EQ(answer, 4);
}

TEST(FIRST_FROM_DOC, B_LETTER_INCORRECT) {
  std::string regexp = "ab + c.aba. * .bac. + . + *";
  Solver solver(regexp);
  size_t answer = solver.FindTheShortestWord(2, 'b');
  EXPECT_TRUE(answer != 3);
}

TEST(FIRST_FROM_DOC, C_LETTER_CORRECT) {
  std::string regexp = "ab + c.aba. * .bac. + . + *";
  Solver solver(regexp);
  size_t answer = solver.FindTheShortestWord(2, 'c');
  EXPECT_EQ(answer, 4);
}

TEST(FIRST_FROM_DOC, C_LETTER_INCORRECT) {
  std::string regexp = "ab + c.aba. * .bac. + . + *";
  Solver solver(regexp);
  size_t answer = solver.FindTheShortestWord(3, 'c');
  EXPECT_TRUE(answer != 5);
}



TEST(SECOND_FROM_DOC, A_LETTER_CORRECT) {
  std::string regexp = "acb..bab.c. * .ab.ba. + . + *a.";
  Solver solver(regexp);
  size_t answer = solver.FindTheShortestWord(1, 'a');
  EXPECT_EQ(answer, 1);
}

TEST(SECOND_FROM_DOC, A_LETTER_INCORRECT) {
  std::string regexp = "acb..bab.c. * .ab.ba. + . + *a.";
  Solver solver(regexp);
  size_t answer = solver.FindTheShortestWord(5, 'a');
  EXPECT_NE(answer, 6);
}

TEST(SECOND_FROM_DOC, B_LETTER_CORRECT) {
  std::string regexp = "acb..bab.c. * .ab.ba. + . + *a.";
  Solver solver(regexp);
  size_t answer = solver.FindTheShortestWord(3, 'b');
  EXPECT_EQ(answer, 7);
}

TEST(SECOND_FROM_DOC, B_LETTER_INCORRECT) {
  std::string regexp = "acb..bab.c. * .ab.ba. + . + *a.";
  Solver solver(regexp);
  size_t answer = solver.FindTheShortestWord(2, 'b');
  EXPECT_TRUE(answer != 2);
}

TEST(SECOND_FROM_DOC, C_LETTER_CORRECT) {
  std::string regexp = "acb..bab.c. * .ab.ba. + . + *a.";
  Solver solver(regexp);
  size_t answer = solver.FindTheShortestWord(0, 'c');
  EXPECT_EQ(answer, 1);
}

TEST(SECOND_FROM_DOC, C_LETTER_INCORRECT) {
  std::string regexp = "acb..bab.c. * .ab.ba. + . + *a.";
  Solver solver(regexp);
  size_t answer = solver.FindTheShortestWord(0, 'c');
  EXPECT_TRUE(answer != 0);
}


TEST(EXCEPTIONS, INCORRECT_CONCATENATION_NO_OPERAND) {
  std::string regexp = "acb...";
  Solver solver(regexp);
  ASSERT_ANY_THROW(solver.FindTheShortestWord(1, 'a'));
}

TEST(EXCEPTIONS, INCORRECT_CONCATENATION_EMPTY_STACK) {
  std::string regexp = ".acb..";
  Solver solver(regexp);
  ASSERT_ANY_THROW(solver.FindTheShortestWord(1, 'a'));
}

TEST(EXCEPTIONS, INCORRECT_DISJUNCTION_NO_OPERAND) {
  std::string regexp = "acb+++";
  Solver solver(regexp);
  ASSERT_ANY_THROW(solver.FindTheShortestWord(1, 'a'));
}

TEST(EXCEPTIONS, INCORRECT_DISJUNCTION_EMPTY_STACK) {
  std::string regexp = "+cb+";
  Solver solver(regexp);
  ASSERT_ANY_THROW(solver.FindTheShortestWord(1, 'a'));
}

TEST(EXCEPTIONS, INCORRECT_CLOSURE_NO_OPERAND) {
  std::string regexp = "*";
  Solver solver(regexp);
  ASSERT_ANY_THROW(solver.FindTheShortestWord(1, 'a'));
}

TEST(EXCEPTIONS, MORE_OPERANDS_THAN_NECESSARY) {
  std::string regexp = "aaaaaa...";
  Solver solver(regexp);
  ASSERT_ANY_THROW(solver.FindTheShortestWord(1, 'a'));
}

TEST(EXCEPTIONS, ONLY_OPERANDS) {
  std::string regexp = "aaaaaa";
  Solver solver(regexp);
  ASSERT_ANY_THROW(solver.FindTheShortestWord(1, 'a'));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}