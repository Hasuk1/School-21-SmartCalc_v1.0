#include "deposit.h"

#include "mainwindow.h"
#include "ui_deposit.h"

deposit::deposit(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::deposit),
      deposit_amount_validator(0, 100000000, 7, this),
      term_validator(1, 60, 0, this),
      rate_validator(0.1, 1000, 2, this),
      operations_validator(0, 100000000, 7, this) {
  ui->setupUi(this);
  // set validators
  QLocale locale(QLocale::English);
  deposit_amount_validator.setNotation(QDoubleValidator::StandardNotation);
  term_validator.setNotation(QDoubleValidator::StandardNotation);
  rate_validator.setNotation(QDoubleValidator::StandardNotation);
  operations_validator.setNotation(QDoubleValidator::StandardNotation);
  deposit_amount_validator.setLocale(locale);
  term_validator.setLocale(locale);
  rate_validator.setLocale(locale);
  operations_validator.setLocale(locale);
  ui->deposit_amount_val->setValidator(&deposit_amount_validator);
  ui->term_val->setValidator(&term_validator);
  ui->interest_rate_val->setValidator(&rate_validator);
  ui->tax_rate_val->setValidator(&rate_validator);
  ui->replenish_val->setValidator(&operations_validator);
  ui->withdraw_val->setValidator(&operations_validator);
}

deposit::~deposit() { delete ui; }

void deposit::on_calc_btn_clicked() {
  if (ui->deposit_amount_val->text().isEmpty() ||
      ui->term_val->text().isEmpty() || ui->term_val->text().isEmpty() ||
      ui->interest_rate_val->text().isEmpty() ||
      (!ui->months->isChecked() && !ui->years->isChecked()) ||
      (!ui->monthly_btn->isChecked() && !ui->yearly_btn->isChecked())) {
    // warning
    QMessageBox::warning(this, "not all filled",
                         "Please fill in all fields to enter");
  } else {
    // logic for OK
    long double deposit_amount = ui->deposit_amount_val->text().toDouble();
    double term = ui->term_val->text().toDouble();
    if (ui->years->isChecked()) {
      term = convert_years_to_months(term);
    }
    long double interest_rate = ui->interest_rate_val->text().toDouble();
    long double tax_rate = ui->tax_rate_val->text().toDouble();
    int mode = ui->monthly_btn->isChecked() ? MONTHLY : YEARLY;
    bool is_capitalization = ui->is_capital->isChecked();
    long double monthly_replenishment = ui->replenish_val->text().toDouble();
    long double monthly_withdrawal = ui->withdraw_val->text().toDouble();
    long double total_earned = get_total_earned(
        &deposit_amount, term, interest_rate, mode, is_capitalization,
        monthly_replenishment, monthly_withdrawal);
    long double tax_amount = get_tax_amount(total_earned, tax_rate);
    long double total_amount =
        get_total_amount(deposit_amount, total_earned, tax_amount);
    QString tot_e = QString::number(total_earned, 'g', 7);
    QString tax_a = QString::number(tax_amount, 'g', 7);
    QString tot_a = QString::number(total_amount, 'g', 7);
    ui->earned_val->setText(tot_e);
    ui->taxed_val->setText(tax_a);
    ui->total_val->setText(tot_a);
  }
}
