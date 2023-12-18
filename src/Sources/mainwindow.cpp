#include "../Headers/mainwindow.h"

#include "../Headers/credit.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(s21::Controller *Contr, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), Controller_(Contr) {
  ui->setupUi(this);

  connect(ui->button_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->button_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->button_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->button_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->button_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->button_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->button_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->button_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->button_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->button_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->button_to, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->button_acos, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->button_asin, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->button_cos, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->button_sin, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->button_tan, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->button_atan, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->button_log, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->button_ln, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->button_so, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->button_sz, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->button_x, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->button_mod, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->button_sqrt, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->button_po, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->button_di, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->button_mu, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->button_pl, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->button_mi, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->button_e, SIGNAL(clicked()), this, SLOT(digits_numbers()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_button_result_clicked() {
  QString result;
  QString count_x = (ui->spinbox_x->text());
  QString expression = (ui->line_edit_input->text());
  ForX(expression, count_x);
  QByteArray tmp = expression.toLocal8Bit();
  char *new_str = tmp.data();
  if (!Controller_->ToChecking(new_str)) {
    ui->result->setText("ERROR. TRY AGAIN");
  } else {
    ui->result->setText(
        QString::number(Controller_->ToCalculation(new_str), 'f', 7));
  }
}

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  QString digit;
  digit = (ui->line_edit_input->text() + button->text());
  ui->line_edit_input->setText(digit);
}

void MainWindow::operations() {
  QPushButton *button = (QPushButton *)sender();
  QString letter;
  letter = (ui->line_edit_input->text() + button->text() + '(');
  ui->line_edit_input->setText(letter);
}

void MainWindow::on_button_ac_clicked() {
  ui->line_edit_input->clear();
  ui->result->clear();
  Controller_->ClearAll();
}

void MainWindow::on_button_graphic_clicked() {
  QString expression;
  x_begin_ = ui->spinbox_begin->value();
  x_end_ = ui->spinbox_end->value();
  ui->widget->xAxis->setRange(x_begin_, x_end_);
  ui->widget->yAxis->setRange(x_begin_, x_end_);
  for (X_ = x_begin_; X_ <= x_end_; X_ += h_) {
    if ((X_ > -0.01) && (X_ < 0.01)) {
      X_ = 0.0;
    }
    expression = (ui->line_edit_input->text());
    QString count_x = QString::number(X_);
    ForX(expression, count_x);
    QByteArray tmp = expression.toLocal8Bit();
    char *new_str = tmp.data();
    if (Controller_->ToChecking(new_str)) {
      for_x_.push_back(X_);
      for_y_.push_back(Controller_->ToCalculation(new_str));
    } else {
      ui->result->setText("ERROR!");
    }
  }
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(for_x_, for_y_);
  ui->widget->graph(0)->setLineStyle(QCPGraph::LineStyle::lsNone);
  ui->widget->graph(0)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
  ui->widget->replot();
  for_x_.clear();
  for_y_.clear();
  ui->widget->graph(0)->data()->clear();
}

void MainWindow::on_button_c_clicked() {
  QString str = ui->line_edit_input->text();
  str.chop(1);
  while (str.size() && str.back() != 'e' && str.back().isLetter()) {
    str.chop(1);
  }
  ui->line_edit_input->setText(str);
}

void MainWindow::on_button_credit_clicked() {
  credit_window_ = new Credit(this);
  credit_window_->show();
}

void MainWindow::ForX(QString &str, QString &x) {
  x.prepend("(");
  x.append(")");
  str.replace(QString("x"), x);
  str.replace(QString(","), ".");
}
