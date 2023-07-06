#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDoubleValidator>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPoint>
#include <QRegularExpressionValidator>
#include <QVector>
#include <cstring>

#include "about.h"
#include "credit.h"
#include "deposit.h"
#include "plot.h"
#include "rpn.h"

extern "C" {
#include "../smart_calc_controller.h"
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

 protected:
  void keyPressEvent(QKeyEvent *event) {
    if (event->key() == 16777220) {
      on_pushButton_eq_clicked();
    }
  }

 private slots:
  void open_windows();
  void on_pushButton_rpn_clicked();
  void on_pushButton_eq_clicked();
  void input_btns_clicked();
  void bind_slots();
  void on_pushButton_del_clicked();
  void on_pushButton_clear_clicked();
  void x_input_handler();
  void on_pushButton_mult_clicked();
  void on_pushButton_div_clicked();
  void on_InputArea_textChanged(const QString &arg1);
  void minimization();

  void on_pushButton_minimize_2_clicked();

 private:
  Ui::MainWindow *ui;
  void x_input_display(bool val);
  bool check_is_x_set();
  QDoubleValidator x_input_validator;
  QRegularExpressionValidator input_area_validator;
  void connect_windows();
  // Windows transition
  QPoint cur_pos;
  QPoint new_pos;
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  // Windows
  About aboutWindow;
  Plot *plotWindow;
  deposit *depositWindow;
  credit *creditWindow;
  rpn *rpnWindow;

 signals:
  void rpn_signal(char *);
  void plot_signal(const char *);
};
#endif  // MAINWINDOW_H
