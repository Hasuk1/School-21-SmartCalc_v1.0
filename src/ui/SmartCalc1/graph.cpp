#include "graph.h"

#include "ui_graph.h"

graph::graph(QWidget* parent) : QDialog(parent), ui(new Ui::graph) {
  ui->setupUi(this);

  setWindowTitle("Function graph");
  setFixedSize(width(), height());

  ui->widget->xAxis->setRange(-20, 20);
  ui->widget->yAxis->setRange(-20, 20);
}

graph::~graph() { delete ui; }

void graph::plot(QString postfix, QString strValue) {
  x.clear();
  y.clear();
  ui->widget->clearGraphs();

  QString strXminValue = ui->xMin->toPlainText();
  QString strXmaxValue = ui->xMax->toPlainText();
  QString strYminValue = ui->yMin->toPlainText();
  QString strYmaxValue = ui->yMax->toPlainText();
  bool okXmin = false, okXmax = false, okYmin = false, okYmax = false;

  xBegin = strXminValue.toDouble(&okXmin);
  xEnd = strXmaxValue.toDouble(&okXmax);
  yBegin = strYminValue.toDouble(&okYmin);
  yEnd = strYmaxValue.toDouble(&okYmax);

  if (okXmin && okXmax && okYmin && okYmax) {
    if (xBegin >= -1000000 && xBegin <= 1000000 && yBegin >= -1000000 &&
        yEnd <= 1000000) {
      QByteArray currentTextUtf8 = postfix.toUtf8();
      char* currentTextCStr = currentTextUtf8.data();

      char result[MAX_SIZE];

      bool ok;
      double xVal = strValue.toDouble(&ok);

      if (ok) {
        evaluate_postfix(currentTextCStr, xVal, result);
        Y = std::strtod(result, nullptr);
        if (Y >= yBegin && Y <= yEnd) {
          x.push_back(xVal);
          y.push_back(Y);
        }
      } else {
        for (X = xBegin; X <= xEnd; X += h) {
          evaluate_postfix(currentTextCStr, X, result);
          Y = std::strtod(result, nullptr);
          if (Y >= yBegin && Y <= yEnd) {
            x.push_back(X);
            y.push_back(Y);
          }
        }
      }
      ui->widget->addGraph();
      QCPGraph* graph = ui->widget->graph(0);
      QPen pen = graph->pen();
      pen.setWidth(2);
      pen.setColor(QColor::fromRgb(71, 86, 121));
      graph->setPen(pen);
      ui->widget->graph(0)->addData(x, y);
      ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                                  QCP::iSelectPlottables);
      ui->widget->rescaleAxes();
      ui->widget->replot();
    } else
      QMessageBox::information(
          this, "ERROR",
          "Set domain & codomain in the range from -1000000 to 1000000");
  } else
    QMessageBox::information(this, "ERROR", "Set domain & codomain correctly");
}
