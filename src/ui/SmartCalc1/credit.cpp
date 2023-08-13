#include "credit.h"

#include "ui_credit.h"

credit::credit(QWidget* parent) : QDialog(parent), ui(new Ui::credit) {
  ui->setupUi(this);

  setWindowTitle("Credit calculator");
  setFixedSize(width(), height());
}

credit::~credit() { delete ui; }

void credit::on_calc_credit_clicked() {
  QLabel* overPayLabel = ui->overPay;
  overPayLabel->setStyleSheet(
      "color: #475679;"
      "font-size: 28px;");
  QLabel* totalPayLabel = ui->totalPay;
  totalPayLabel->setStyleSheet(
      "color: #475679;"
      "font-size: 28px;");

  QLabel* labelMonth = ui->monthPayment;
  QLabel* paymentName = ui->monPaymentsName;
  QString amountStr = ui->creditAmount->toPlainText();
  bool amOk = false;
  double amountValue = amountStr.toDouble(&amOk);

  if (amountValue >= 10000000 && amountValue <= 100000000) {
    overPayLabel->setStyleSheet(
        "color: #475679;"
        "font-size: 26px;");
    totalPayLabel->setStyleSheet(
        "color: #475679;"
        "font-size: 26px;");
  } else if (amountValue >= 100000000 && amountValue <= 1000000000) {
    overPayLabel->setStyleSheet(
        "color: #475679;"
        "font-size: 24px;");
    totalPayLabel->setStyleSheet(
        "color: #475679;"
        "font-size: 24px;");
  } else if (amountValue >= 1000000000 && amountValue <= 10000000000) {
    overPayLabel->setStyleSheet(
        "color: #475679;"
        "font-size: 22px;");
    totalPayLabel->setStyleSheet(
        "color: #475679;"
        "font-size: 22px;");
  } else if (amountValue >= 10000000000 && amountValue <= 100000000000) {
    overPayLabel->setStyleSheet(
        "color: #475679;"
        "font-size: 20px;");
    totalPayLabel->setStyleSheet(
        "color: #475679;"
        "font-size: 20px;");
  } else if (amountValue >= 100000000000 && amountValue <= 1000000000000) {
    overPayLabel->setStyleSheet(
        "color: #475679;"
        "font-size: 18px;");
    totalPayLabel->setStyleSheet(
        "color: #475679;"
        "font-size: 18px;");
  } else if (amountValue >= 1000000000000 && amountValue <= 9999999999999) {
    overPayLabel->setStyleSheet(
        "color: #475679;"
        "font-size: 16px;");
    totalPayLabel->setStyleSheet(
        "color: #475679;"
        "font-size: 16px;");
  } else if (amountValue >= 10000000000000)
    QMessageBox::information(this, "ERROR", "Enter a credit amount less");

  QString termStr = ui->creditTerm->toPlainText();
  bool termOk = false;
  int termValue = termStr.toInt(&termOk);
  QString termPer = ui->termPer->currentText();
  int term_period = 0;
  termPer == "Year" ? term_period = 12 : term_period = 1;
  QString rateStr = ui->rate->toPlainText();
  bool rateOk = false;
  double rateValue = rateStr.toDouble(&rateOk);

  if (amOk && termOk && rateOk && amountValue > 0 && termValue > 0 &&
      rateValue >= 0) {
    QString typePayment = ui->creditType->currentText();
    if (typePayment == "Annuities") {
      labelMonth->setStyleSheet(
          "padding-top: 1px;"
          "color: #475679;"
          "font-size: 28px;");
      paymentName->setStyleSheet(
          "color: #5f697f;"
          "text-align: center;"
          "font-size: 13px;");
      double monthPaymentsAnn = calc_month_payments_ann(amountValue, termValue,
                                                        term_period, rateValue);
      double termMonth = calc_term_month(termValue, term_period);
      double totalPayment = calc_total_payment(monthPaymentsAnn, termMonth);
      double overPay = calc_over_payment(totalPayment, amountValue);

      QString totalPaymentStr = QString::number(totalPayment, 'f', 2);
      QString totalOverPayStr = QString::number(overPay, 'f', 2);

      ui->totalPay->setText(totalPaymentStr + " \u20BD");
      ui->overPay->setText(totalOverPayStr + " \u20BD");
      paymentName->setText("Monthly payments:");

      if (monthPaymentsAnn >= 10000000 && monthPaymentsAnn <= 100000000) {
        labelMonth->setStyleSheet(
            "padding-top: 1px;"
            "color: #475679;"
            "font-size: 26px;");
      } else if (monthPaymentsAnn >= 100000000 &&
                 monthPaymentsAnn <= 1000000000) {
        labelMonth->setStyleSheet(
            "padding-top: 1px;"
            "color: #475679;"
            "font-size: 24px;");
      } else if (monthPaymentsAnn >= 1000000000 &&
                 monthPaymentsAnn <= 10000000000) {
        labelMonth->setStyleSheet(
            "padding-top: 1px;"
            "color: #475679;"
            "font-size: 22px;");
      } else if (monthPaymentsAnn >= 10000000000 &&
                 monthPaymentsAnn <= 100000000000) {
        labelMonth->setStyleSheet(
            "padding-top: 1px;"
            "color: #475679;"
            "font-size: 20px;");
      }

      QString monthPaymentsStr = QString::number(monthPaymentsAnn, 'f', 2);
      ui->monthPayment->setText(monthPaymentsStr + " \u20BD");

    } else if (typePayment == "Differentiated") {
      labelMonth->setStyleSheet(
          "padding-top: 1px;"
          "color: #475679;"
          "font-size: 20px;");
      paymentName->setStyleSheet(
          "color: #5f697f;"
          "text-align: center;"
          "font-size: 12px;");
      paymentName->setText("First and last monthly payments:");
      double first_pay = 0, last_pay = 0, total_pay = 0;
      calc_month_payments_diff(amountValue, termValue, term_period, rateValue,
                               &first_pay, &last_pay, &total_pay);
      QString firstPayStr = QString::number(first_pay, 'f', 2);
      QString lastPayStr = QString::number(last_pay, 'f', 2);
      QString totalPayStr = QString::number(total_pay, 'f', 2);
      ui->monthPayment->setText(firstPayStr + " \u20BD" + '\n' + lastPayStr +
                                " \u20BD");
      ui->totalPay->setText(totalPayStr + " \u20BD");
      double overPay = calc_over_payment(total_pay, amountValue);
      QString totalOverPayStr = QString::number(overPay, 'f', 2);
      ui->overPay->setText(totalOverPayStr + " \u20BD");
    }
  } else {
    ui->monthPayment->setText("ERROR");
    ui->overPay->setText("ERROR");
    ui->totalPay->setText("ERROR");
    if (!amOk || amountValue <= 0)
      QMessageBox::information(this, "ERROR",
                               "Enter a credit amount correctly");
    if (!termOk || termValue <= 0)
      QMessageBox::information(this, "ERROR", "Enter a credit term correctly");
    if (!rateOk || rateValue < 0)
      QMessageBox::information(this, "ERROR",
                               "Enter a yearly interest rate correctly");
  }
}
