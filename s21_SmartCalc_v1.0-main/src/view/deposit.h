#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QDialog>
#include <QDoubleValidator>
#include <QMessageBox>

namespace Ui {
class deposit;
}

class deposit : public QDialog {
  Q_OBJECT

 public:
  explicit deposit(QWidget *parent = nullptr);
  ~deposit();

 private slots:
  void on_calc_btn_clicked();

 private:
  Ui::deposit *ui;
  QDoubleValidator deposit_amount_validator;
  QDoubleValidator term_validator;
  QDoubleValidator rate_validator;
  QDoubleValidator operations_validator;
};

#endif  // DEPOSIT_H
