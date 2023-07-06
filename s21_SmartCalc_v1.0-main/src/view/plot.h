#ifndef PLOT_H
#define PLOT_H

#include <string.h>

#include <QDialog>
#include <QDoubleValidator>
#include <QVector>

namespace Ui {
class Plot;
}

class Plot : public QDialog {
  Q_OBJECT

 public:
  explicit Plot(QWidget *parent = nullptr);
  ~Plot();

 public slots:
  void plot_slot(const char *str);

 private:
  Ui::Plot *ui;
  // Plot
  double x_min, x_max, y_min, y_max;
  double h_step, X_temp;
  int N;
  QVector<double> x_vector, y_vector;
  char math_expression[255];
  void render_graph();
  bool is_set;
  QDoubleValidator m_doubleValidator;
  QDoubleValidator step_doubleValidator;

 private slots:
  void on_xmin_val_editingFinished();
  void on_xmax_val_editingFinished();
  void on_ymin_val_editingFinished();
  void on_ymax_val_editingFinished();
  void on_step_val_editingFinished();
};

#endif  // PLOT_H
