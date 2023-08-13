#include "deposit.h"

#include "ui_deposit.h"

deposit::deposit(QWidget *parent) : QDialog(parent), ui(new Ui::deposit) {
  ui->setupUi(this);

  setWindowTitle("Deposit calculator");
  setFixedSize(width(), height());
}

deposit::~deposit() { delete ui; }

void deposit::on_calcDeposit_clicked() {
  bool amOk = false, termOk = false, interestOk = false, taxOk = false,
       replOk = false, withdOk = false;
  QString depAmountStr = ui->depAmount->toPlainText();
  QString depTermStr = ui->depTerm->toPlainText();
  QString depTermPerStr = ui->depTermPer->currentText();
  QString depInterestStr = ui->depIntrst->toPlainText();
  QString depTaxStr = ui->depTax->toPlainText();
  QString depFrqncStr = ui->depFrqPay->currentText();
  QRadioButton *depCapital = ui->depCapital;
  bool depCapitalization = depCapital->isChecked();
  QString depReplStr = ui->depMonReplsmnt->toPlainText();
  QString depWtdhrwStr = ui->depMonWithdraw->toPlainText();

  double depAmountVal = depAmountStr.toDouble(&amOk);
  int depTermVal = depTermStr.toInt(&termOk);
  int depTermPerVal = 0;
  depTermPerStr == "Year" ? depTermPerVal = 12 : depTermPerVal = 1;
  double depInterestVal = depInterestStr.toDouble(&interestOk);
  double depTaxVal = depTaxStr.toDouble(&taxOk);
  int depFrqncVal = 0;
  depFrqncStr == "Once a year" ? depFrqncVal = 12 : depFrqncVal = 1;
  double depReplVal = depReplStr.toDouble(&replOk);
  double depWtdhrwVal = depWtdhrwStr.toDouble(&withdOk);
  if (amOk && termOk && interestOk && taxOk && replOk && withdOk &&
      depAmountVal > 0 && depTermVal > 0 && depInterestVal > 0 &&
      depTaxVal >= 0 && depReplVal >= 0 && depWtdhrwVal >= 0) {
    double totalInterest =
        calc_total(depAmountVal, depTermVal, depTermPerVal, depInterestVal,
                   depFrqncVal, depCapitalization, depReplVal, depWtdhrwVal);
    double totalTax = calc_tax_amount(totalInterest, depTaxVal);
    double endBalance =
        calc_total_deposit(totalInterest, depAmountVal, totalTax, depTermVal,
                           depTermPerVal, depReplVal, depWtdhrwVal);
    QString totalInterestStr = QString::number(totalInterest, 'f', 2);
    QString totalTaxStr = QString::number(totalTax, 'f', 2);
    QString endBalanceStr = QString::number(endBalance, 'f', 2);
    if (totalInterestStr.length() > 11 || totalTaxStr.length() > 11 ||
        endBalanceStr.length() > 11) {
      ui->totalInterest->setStyleSheet(
          "color: #475679;"
          "font-size: 15px;"
          "background-color: rgba(0, 0, 0, 0.00);");
      ui->totalTax->setStyleSheet(
          "color: #475679;"
          "font-size: 15px;"
          "background-color: rgba(0, 0, 0, 0.00);");
      ui->endBalance->setStyleSheet(
          "color: #475679;"
          "font-size: 15px;"
          "background-color: rgba(0, 0, 0, 0.00);");
    } else {
      ui->totalInterest->setStyleSheet(
          "color: #475679;"
          "font-size: 28px;"
          "background-color: rgba(0, 0, 0, 0.00);");
      ui->totalTax->setStyleSheet(
          "color: #475679;"
          "font-size: 28px;"
          "background-color: rgba(0, 0, 0, 0.00);");
      ui->endBalance->setStyleSheet(
          "color: #475679;"
          "font-size: 28px;"
          "background-color: rgba(0, 0, 0, 0.00);");
    }
    ui->totalInterest->setText(totalInterestStr + " \u20BD");
    ui->totalTax->setText(totalTaxStr + " \u20BD");
    ui->endBalance->setText(endBalanceStr + " \u20BD");
  } else {
    ui->totalInterest->setText("ERROR");
    ui->totalTax->setText("ERROR");
    ui->endBalance->setText("ERROR");
    QMessageBox::information(this, "ERROR", "Enter a deposit info correctly");
  }
}
