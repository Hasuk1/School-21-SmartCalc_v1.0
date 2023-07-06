#ifndef RPN_H
#define RPN_H

#include <QDialog>

namespace Ui {
class rpn_window;
}

class rpn : public QDialog {
  Q_OBJECT

 public:
  explicit rpn(QWidget *parent = nullptr);
  ~rpn();

 public slots:
  void rpn_slot(char *str);

 private:
  Ui::rpn_window *ui;
};

#endif  // RPN_H
