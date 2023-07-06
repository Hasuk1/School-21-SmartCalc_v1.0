#ifndef CREDIT_H
#define CREDIT_H

#include <QDialog>
#include <QDoubleValidator>
#include <QMessageBox>

namespace Ui {
class credit;
}

class credit : public QDialog {
  Q_OBJECT

 public:
  explicit credit(QWidget *parent = nullptr);
  ~credit();

 private slots:
  void on_calc_btn_clicked();

 private:
  Ui::credit *ui;
  QDoubleValidator loan_amount_validator;
  QDoubleValidator term_validator;
  QDoubleValidator interest_rate_validator;
};

#endif  // CREDIT_H
