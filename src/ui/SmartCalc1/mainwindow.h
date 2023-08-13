#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QIcon>
#include <QMainWindow>
#include <QMessageBox>
#include <QRegularExpression>

#include "credit.h"
#include "deposit.h"
#include "graph.h"

extern "C" {
#include "../../modules/modules.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void moveEvent(QMoveEvent *event) override {
    QWidget::moveEvent(event);
    if (GraphWindow || CreditWindow || DepositWindow) {
      QPoint mainPos = pos();
      if (GraphWindow) GraphWindow->move(mainPos.x() + 290, mainPos.y());
      if (CreditWindow) CreditWindow->move(mainPos.x() - 450, mainPos.y() + 72);
      if (DepositWindow)
        DepositWindow->move(mainPos.x() - 450, mainPos.y() + 72);
    }
  }

 private slots:
  void digits_num();
  void function();
  void on_PushButton_dot_clicked();
  void on_PushButton_div_clicked();
  void on_PushButton_mult_clicked();
  void on_PushButton_minus_clicked();
  void on_PushButton_plus_clicked();
  void on_PushButton_bracket1_clicked();
  void on_PushButton_bracket2_clicked();
  void on_PushButton_del_clicked();
  void on_PushButton_all_del_clicked();
  void on_PushButton_exp_clicked();
  void on_pushButton_mod_clicked();
  void on_PushButton_percent_clicked();
  void on_PushButton_equals_clicked();
  void on_PushButton_graph_clicked();
  void on_PushButton_cred_clicked();
  void on_PushButton_dep_clicked();
  void on_PushButton_x_clicked();
  void on_PushButton_sqrt_clicked();

 private:
  Ui::MainWindow *ui;
  graph *GraphWindow;
  credit *CreditWindow;
  deposit *DepositWindow;

 signals:
  void plot(QString, QString);
};

#endif  // MAINWINDOW_H
