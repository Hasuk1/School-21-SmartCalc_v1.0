#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QDialog>
#include <QMessageBox>

extern "C" {
#include "../../modules/modules.h"
}

namespace Ui {
class deposit;
}

class deposit : public QDialog {
  Q_OBJECT

 public:
  explicit deposit(QWidget *parent = nullptr);
  ~deposit();

 private slots:
  void on_calcDeposit_clicked();

 private:
  Ui::deposit *ui;
};

#endif  // DEPOSIT_H
