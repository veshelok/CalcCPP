#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"

namespace s21 {
class Controller {
public:
  explicit Controller(Model *m) : M_(m) {}
  ~Controller() {}

  void ClearAll();
  bool ToChecking(std::string const &str);
  double ToCalculation(std::string const &str);

private:
  Model *M_;
};

} // namespace s21

#endif // CONTROLLER_H
