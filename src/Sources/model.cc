#include "../Headers/model.h"

s21::Model::Model(const std::string &str) { Calculation(str); }

bool s21::Model::Checking(std::string str) {
  for (std::size_t i = 0; str.length() > i; ++i) {
    ReplaceOper(str);
  }
  return (!BracketsCheck(str) && !NumberCheck(str) && !OperatorCheck(str));
}

void s21::Model::ReplaceOper(std::string &str) {
  if (str.find("acos") != std::string::npos) {
    str.replace(str.find("acos"), 4, "f");
  } else if (str.find("asin") != std::string::npos) {
    str.replace(str.find("asin"), 4, "g");
  } else if (str.find("atan") != std::string::npos) {
    str.replace(str.find("atan"), 4, "d");
  } else if (str.find("sin") != std::string::npos) {
    str.replace(str.find("sin"), 3, "s");
  } else if (str.find("cos") != std::string::npos) {
    str.replace(str.find("cos"), 3, "c");
  } else if (str.find("tan") != std::string::npos) {
    str.replace(str.find("tan"), 3, "t");
  } else if (str.find("ln") != std::string::npos) {
    str.replace(str.find("ln"), 2, "l");
  } else if (str.find("log") != std::string::npos) {
    str.replace(str.find("log"), 3, "j");
  } else if (str.find("mod") != std::string::npos) {
    str.replace(str.find("mod"), 3, "m");
  } else if (str.find("sqrt") != std::string::npos) {
    str.replace(str.find("sqrt"), 4, "q");
  }
}

bool s21::Model::BracketsCheck(std::string str) {
  int count = 0;
  for (std::size_t i = 0; str.length() > i; ++i) {
    if (str[i] == '(') {
      if ((str[i + 1] != '*') && (str[i + 1] != '/')) {
        ++count;
        if (str[i + 1] == ')') {
          return true;
        }
      } else
        return true;
    }
    if (str[i] == ')') {
      --count;
    }
    if (count < 0) {
      return true;
    }
  }
  return count;
}

bool s21::Model::OperatorCheck(std::string str) {
  for (std::size_t i = 0; str.length() > i; ++i) {
    if ((i != 0) && (priority_[str[i]] == 1)) {
      if (ForOper(str, i - 1) || (str[i - 1] == '(')) {
        if ((str[i] == str[i - 1]) && (str[i] != '(')) {
          return true;
        }
        return false;
      } else {
        return true;
      }
    }
    if (ForOper(str, i) && ((i + 1) == str.length())) {
      return true;
    }
  }
  return false;
}

bool s21::Model::ForOper(std::string str, int i) {
  if ((str[i] == '-') || (str[i] == '+') || (str[i] == '/') ||
      (str[i] == '*') || (str[i] == '^')) {
    return true;
  }
  return false;
}

bool s21::Model::NumberCheck(std::string str) {
  int number = 0;
  int dot = 0;
  for (std::size_t i = 0; str.length() > i; ++i) {
    if (isdigit(str[i])) {
      number = 1;
    } else if ((str[i]) == '.') {
      if ((dot == 1) || (number == 0) || ((str.length()) - 1 == i)) {
        return true;
      }
      dot = 1;
    } else if ((str[i]) == 'e') {
      if ((i == 0) || (!std::isdigit(str[i - 1]))) {
        return true;
      }
      if (((i + 1) < str.length()) &&
          ((str[i + 1] != '-') && (str[i + 1] != '+') &&
           (!(isdigit(str[i + 2]))))) {
        return true;
      }
    } else {
      number = 0;
      dot = 0;
    }
  }
  return false;
}

void s21::Model::Calculation(std::string str) {
  for (std::size_t i = 0; str.length() > i; ++i) {
    ReplaceOper(str);
    if (((i == 0) || (str[i - 1] == '(')) &&
        ((str[i] == '+') || ((str[i] == '-')))) {
      numbers_.push_back(0);
      operators_.push_back(str[i]);
      ++i;
    }
    if (isdigit(str[i])) {
      i = ForNumbers(str, i);
    } else {
      if (operators_.empty()) {
        operators_.push_back(str[i]);
      } else {
        if ((operators_.back() != '(') && (str[i] != '(') && (str[i] != ')')) {
          while ((priority_[str[i]] >= priority_[operators_.back()]) &&
                 ((str[i] != '^') && (operators_.back() != '^')) &&
                 (!operators_.empty()) && (operators_.back() != '(')) {
            Process();
          }
        }
        operators_.push_back(str[i]);
        if (str[i] == ')') {
          operators_.pop_back();
          while (operators_.back() != '(') {
            Process();
          }
          operators_.pop_back();
        }
      }
    }
  }
  while (!operators_.empty()) {
    Process();
  }
  ToResult();
}

void s21::Model::Process() {
  if ((operators_.back() != '(') && (!operators_.empty())) {
    double res = 0;
    if ((priority_[operators_.back()] > 1) && (!numbers_.empty())) {
      res = ActForTwo();
    } else {
      res = ActForOne();
    }
    numbers_.push_back(res);
  }
}

double s21::Model::ActForOne() {
  double a = numbers_.back();
  numbers_.pop_back();
  char op = operators_.back();
  operators_.pop_back();
  if (op == 's') {
    return sin(a);
  }
  if (op == 'c') {
    return cos(a);
  }
  if (op == 't') {
    return tan(a);
  }
  if (op == 'f') {
    return acos(a);
  }
  if (op == 'd') {
    return atan(a);
  }
  if (op == 'g') {
    return asin(a);
  }
  if (op == 'q') {
    return sqrt(a);
  }
  if (op == 'l') {
    return log(a);
  }
  if (op == 'j') {
    return log10(a);
  }
  return 0;
}

double s21::Model::ActForTwo() {
  double b = numbers_.back();
  numbers_.pop_back();
  double a = numbers_.back();
  numbers_.pop_back();
  char op = operators_.back();
  operators_.pop_back();
  if (op == '-') {
    return a - b;
  }
  if (op == '+') {
    return a + b;
  }
  if (op == '/') {
    return a / b;
  }
  if (op == '*') {
    return a * b;
  }
  if (op == 'm') {
    return fmod(a, b);
  }
  if (op == '^') {
    return pow(a, b);
  }
  return 0;
}

int s21::Model::ForNumbers(std::string str, int i) {
  str.erase(0, i);
  int lngt = str.length();
  double res = std::stod(str);
  numbers_.push_back(res);
  int j = 0;
  while ((lngt > j) && ((isdigit(str[j])) || (str[j] == '.') ||
                        (str[j] == 'e') || (j > 0 && (str[j - 1] == 'e')))) {
    j++;
  }
  return i + j - 1;
}

void s21::Model::ToResult() {
  while (!numbers_.empty()) {
    result_ = numbers_.back();
    numbers_.pop_back();
  }
}

void s21::Model::ClearAll() {
  str.clear();
  result_ = 0;
}
