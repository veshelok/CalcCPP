#include "../Headers/controller.h"

bool s21::Controller::ToChecking(std::string const &str) {
  return M_->Checking(str);
}

double s21::Controller::ToCalculation(std::string const &str) {
  M_->Calculation(str);
  return M_->GetData();
}

void s21::Controller::ClearAll() { M_->ClearAll(); }
