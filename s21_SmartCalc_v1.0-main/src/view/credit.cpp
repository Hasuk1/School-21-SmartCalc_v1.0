#include "credit.h"

#include "mainwindow.h"
#include "ui_credit.h"

credit::credit(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::credit),
      loan_amount_validator(0, 100000000, 7, this),
      term_validator(1, 60, 0, this),
      interest_rate_validator(0.1, 1000, 2, this) {
  ui->setupUi(this);
  // set validators
  QLocale locale(QLocale::English);
  loan_amount_validator.setNotation(QDoubleValidator::StandardNotation);
  term_validator.setNotation(QDoubleValidator::StandardNotation);
  interest_rate_validator.setNotation(QDoubleValidator::StandardNotation);
  loan_amount_validator.setLocale(locale);
  term_validator.setLocale(locale);
  interest_rate_validator.setLocale(locale);
  ui->amount_val->setValidator(&loan_amount_validator);
  ui->term_val->setValidator(&term_validator);
  ui->interest_rate->setValidator(&interest_rate_validator);
}

credit::~credit() { delete ui; }

void credit::on_calc_btn_clicked() {
  if (ui->amount_val->text().isEmpty() || ui->term_val->text().isEmpty() ||
      ui->interest_rate->text().isEmpty() ||
      (!ui->months->isChecked() && !ui->years->isChecked()) ||
      (!ui->annuity->isChecked() && !ui->diff->isChecked())) {
    // error window
    QMessageBox::warning(this, "Not all filled",
                         "Please fill in all fields to enter");
  } else {
    long double loan_amount = ui->amount_val->text().toDouble();
    double term = ui->term_val->text().toDouble();
    if (ui->years->isChecked()) {
      term = convert_years_to_months(term);
    }
    long double interest_rate = ui->interest_rate->text().toDouble();
    if (ui->annuity->isChecked()) {
      long double monthly_payment =
          get_monthly_payment_annuity(loan_amount, interest_rate, term);
      long double total_payment =
          get_total_payment_annuity(monthly_payment, term);
      long double overpayment =
          get_overpayment_on_credit(loan_amount, total_payment);
      QString mp = QString::number(monthly_payment, 'g', 7);
      QString tp = QString::number(total_payment, 'g', 7);
      QString ovp = QString::number(overpayment, 'g', 7);
      ui->monthly_payment_val->setText(mp);
      ui->overpayment_val->setText(ovp);
      ui->total_payment_val->setText(tp);
    } else {
      long double total_payment =
          get_total_payment_diff(loan_amount, term, interest_rate);
      long double monthly_payment =
          get_monthly_payment_diff(total_payment, term);
      long double overpayment =
          get_overpayment_on_credit(loan_amount, total_payment);
      QString mp = QString::number(monthly_payment, 'g', 7);
      QString tp = QString::number(total_payment, 'g', 7);
      QString ovp = QString::number(overpayment, 'g', 7);
      ui->monthly_payment_val->setText(mp + " avg");
      ui->overpayment_val->setText(ovp);
      ui->total_payment_val->setText(tp);
    }
  }
}
