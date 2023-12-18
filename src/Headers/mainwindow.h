#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "controller.h"
#include "credit.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(s21::Controller *Contr, QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_button_result_clicked();
  void digits_numbers();
  void operations();
  void on_button_ac_clicked();
  void on_button_graphic_clicked();
  void on_button_c_clicked();
  void on_button_credit_clicked();

private:
  Ui::MainWindow *ui;
  Credit *credit_window_;
  s21::Controller *Controller_;
  double x_begin_, x_end_, X_;
  double h_ = 0.01;
  QVector<double> for_x_, for_y_;

  void ForX(QString &str, QString &x);
};
#endif // MAINWINDOW_H
