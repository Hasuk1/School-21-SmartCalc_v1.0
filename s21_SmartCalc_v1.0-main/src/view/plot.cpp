#include "plot.h"

#include <QTextEdit>

#include "mainwindow.h"
#include "ui_plot.h"

Plot::Plot(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::Plot),
      m_doubleValidator(-999999, 999999, 7, this),
      step_doubleValidator(0.1, 20, 1, this) {
  ui->setupUi(this);
  is_set = false;
  // set validators
  QLocale locale(QLocale::English);
  m_doubleValidator.setNotation(QDoubleValidator::StandardNotation);
  step_doubleValidator.setNotation(QDoubleValidator::StandardNotation);
  m_doubleValidator.setLocale(locale);
  step_doubleValidator.setLocale(locale);
  ui->xmin_val->setValidator(&m_doubleValidator);
  ui->xmax_val->setValidator(&m_doubleValidator);
  ui->ymin_val->setValidator(&m_doubleValidator);
  ui->ymax_val->setValidator(&m_doubleValidator);
  ui->step_val->setValidator(&step_doubleValidator);
  // initialize fields
  x_min = ui->xmin_val->text().toDouble();
  x_max = ui->xmax_val->text().toDouble();
  y_min = ui->ymin_val->text().toDouble();
  y_max = ui->ymax_val->text().toDouble();
  h_step = ui->step_val->text().toDouble();
  X_temp = x_min;
  N = (x_max - x_min) / h_step + 2;
  // create qcustomplot and set Axis
  ui->plotRender->addGraph();
  ui->plotRender->graph(0)->setData(x_vector, y_vector);
  ui->plotRender->yAxis->setRange(y_min, y_max);
  ui->plotRender->xAxis->setRange(x_min, x_max);
  // make zoom
  ui->plotRender->setInteraction(QCP::iRangeZoom, true);
  ui->plotRender->setInteraction(QCP::iRangeDrag, true);
  ui->plotRender->replot();
}

Plot::~Plot() { delete ui; }

void Plot::plot_slot(const char *str) {
  strncpy(math_expression, str, MAX_LEN);
  is_set = true;
  ui->plotRender->clearGraphs();
  render_graph();
}

void Plot::render_graph() {
  N = (x_max - x_min) / h_step + 2;
  if (N > 1000000) {
    N = 1000000;
  }
  y_vector.clear();
  x_vector.clear();
  X_temp = x_min;
  // set pen for plot
  QPen my_pen;
  my_pen.setColor(QColor(49, 49, 49));
  my_pen.setWidthF(2);
  // add coords to plot
  for (int i = 0; i < N; i++) {
    long double x_calc = 0;
    api_calculate_str_with_x(math_expression,
                             (long double)(X_temp + i * h_step), &x_calc);
    if (x_calc > y_min && x_calc < y_max) {
      x_vector.push_back(x_min + i * h_step);
      y_vector.push_back((double)x_calc);
    }
  }
  ui->plotRender->addGraph();
  ui->plotRender->graph(0)->setData(x_vector, y_vector);
  ui->plotRender->graph(0)->setPen(my_pen);
  ui->plotRender->replot();
}

void Plot::on_xmin_val_editingFinished() {
  if (is_set &&
      ui->xmin_val->text().toDouble() < ui->xmax_val->text().toDouble()) {
    x_min = ui->xmin_val->text().toDouble();
    ui->plotRender->clearGraphs();
    render_graph();
  }
}

void Plot::on_xmax_val_editingFinished() {
  if (is_set &&
      ui->xmin_val->text().toDouble() < ui->xmax_val->text().toDouble()) {
    x_max = ui->xmax_val->text().toDouble();
    ui->plotRender->clearGraphs();
    render_graph();
  }
}

void Plot::on_ymin_val_editingFinished() {
  if (is_set &&
      ui->ymin_val->text().toDouble() < ui->ymax_val->text().toDouble()) {
    y_min = ui->ymin_val->text().toDouble();
    ui->plotRender->clearGraphs();
    render_graph();
  }
}

void Plot::on_ymax_val_editingFinished() {
  if (is_set &&
      ui->ymin_val->text().toDouble() < ui->ymax_val->text().toDouble()) {
    y_max = ui->ymax_val->text().toDouble();
    ui->plotRender->clearGraphs();
    render_graph();
  }
}

void Plot::on_step_val_editingFinished() {
  if (is_set) {
    h_step = ui->step_val->text().toDouble();
    ui->plotRender->clearGraphs();
    render_graph();
  }
}
