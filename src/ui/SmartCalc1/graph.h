#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>
#include <QVector>

extern "C" {
#include "../../modules/modules.h"
}

namespace Ui {
class graph;
}

class graph : public QDialog {
  Q_OBJECT

 public:
  explicit graph(QWidget *parent = nullptr);
  ~graph();

 private:
  Ui::graph *ui;
  double xBegin, xEnd, yBegin, yEnd, h = 0.1, X, Y;
  int N;
  QVector<double> x, y;

 public slots:
  void plot(QString postfix, QString strValue);
};

#endif  // GRAPH_H
