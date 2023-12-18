#include "../Headers/credit.h"

#include "ui_credit.h"

Credit::Credit(QWidget *parent) : QDialog(parent), ui(new Ui::Credit) {
  ui->setupUi(this);
}

Credit::~Credit() { delete ui; }

void Credit::Annuity() {
  QString res_plat, obsh_v, pereplata;
  double per, srok, stavka, summa, o_v, K, i, A;
  int index = ui->combo_box_time->currentIndex();
  srok = (ui->spin_box_time->value());
  if (index == 1) {
    srok = srok * 12;
  }
  stavka = (ui->spin_box_prc->value());
  i = stavka / 12 / 100;
  summa = (ui->sum_button->value());
  if ((summa != 0) && (srok != 0) && (stavka != 0)) {
    K = i * (pow((1 + i), srok)) / (pow((1 + i), srok) - 1);
    A = K * summa;
    o_v = A * srok;
    per = o_v - summa;
    res_plat = QString::number(A, 'f', 2);
    obsh_v = QString::number(o_v, 'f', 2);
    pereplata = QString::number(per, 'f', 2);
    ui->line_edit_per_mon->setText(res_plat);
    ui->line_edit_total->setText(obsh_v);
    ui->line_edit_over->setText(pereplata);
  }
}

void Credit::Differentiated() {
  QString res_plat, obsh_v, pereplata;
  double srok, stavka, summa, o_v, b, Sn_0, p, plat_0;
  srok = (ui->spin_box_time->value());
  int index = ui->combo_box_time->currentIndex();
  if (index == 1) {
    srok = srok * 12;
  }
  stavka = (ui->spin_box_prc->value());
  summa = (ui->sum_button->value());
  if ((summa != 0) && (srok != 0) && (stavka != 0)) {
    b = summa / srok;
    Sn_0 = summa - (b * 0);
    p = Sn_0 * (stavka / 100) / 12;
    plat_0 = b + p;
    res_plat = QString::number(plat_0, 'f', 2);
    if (srok > 1) {
      double Sn_1 = summa - (b * (srok - 1));
      double p_1 = Sn_1 * (stavka / 100) / 12;
      double plat_1 = b + p_1;
      QString res_plat_1 = QString::number(plat_1, 'f', 2);
      res_plat += " ... " + res_plat_1;
    }
    ui->line_edit_per_mon->setText(res_plat);
    double plat_x = 0;
    for (int j = 0; j < srok; j++) {
      double Sn_x = summa - (b * (j));
      double p_x = Sn_x * (stavka / 100) / 12;
      plat_x = plat_x + b + p_x;
    }
    o_v = plat_x;
    obsh_v = QString::number(o_v, 'f', 2);
    ui->line_edit_total->setText(obsh_v);
    double per = o_v - summa;
    pereplata = QString::number(per, 'f', 2);
    ui->line_edit_over->setText(pereplata);
  }
}

void Credit::on_count_button_clicked() {
  if ((ui->radio_button_ann->isChecked())) {
    Annuity();
  }
  if ((ui->radio_button_diff->isChecked())) {
    Differentiated();
  }
}
