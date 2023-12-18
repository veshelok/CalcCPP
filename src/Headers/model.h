#ifndef MODEL_H
#define MODEL_H

#include <cctype>
#include <cmath>
#include <map>
#include <string>
#include <vector>

namespace s21 {
class Model {
public:
  Model() : result_(0){};
  explicit Model(const std::string &str);

  bool Checking(std::string str);
  void Calculation(std::string str);
  double GetData() { return result_; }
  void ClearAll();

private:
  std::map<char, int> priority_ = {{'s', 1}, {'c', 1}, {'d', 1}, {'f', 1},
                                   {'t', 1}, {'g', 1}, {'l', 1}, {'j', 1},
                                   {'q', 1}, {'m', 3}, {'^', 2}, {'/', 3},
                                   {'*', 3}, {'+', 4}, {'-', 4}};
  std::vector<long double> numbers_;
  std::vector<char> operators_;
  std::string str;

  long double result_;

  bool BracketsCheck(std::string str);
  bool ForOper(std::string str, int i);
  bool NumberCheck(std::string str);
  bool OperatorCheck(std::string str);
  double ActForOne();
  double ActForTwo();
  int ForNumbers(std::string str, int i);
  void Process();
  void ReplaceOper(std::string &str);
  void ToResult();
};
} // namespace s21

#endif // MODEL_H
