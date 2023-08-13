#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  setWindowTitle("SmartCalc");
  setFixedSize(width(), height());

  ui->Labe_out->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  ui->Labe_out->setTextInteractionFlags(Qt::TextSelectableByMouse);

  connect(ui->PushButton_0, SIGNAL(clicked()), this, SLOT(digits_num()));
  connect(ui->PushButton_1, SIGNAL(clicked()), this, SLOT(digits_num()));
  connect(ui->PushButton_2, SIGNAL(clicked()), this, SLOT(digits_num()));
  connect(ui->PushButton_3, SIGNAL(clicked()), this, SLOT(digits_num()));
  connect(ui->PushButton_4, SIGNAL(clicked()), this, SLOT(digits_num()));
  connect(ui->PushButton_5, SIGNAL(clicked()), this, SLOT(digits_num()));
  connect(ui->PushButton_6, SIGNAL(clicked()), this, SLOT(digits_num()));
  connect(ui->PushButton_7, SIGNAL(clicked()), this, SLOT(digits_num()));
  connect(ui->PushButton_8, SIGNAL(clicked()), this, SLOT(digits_num()));
  connect(ui->PushButton_9, SIGNAL(clicked()), this, SLOT(digits_num()));

  connect(ui->PushButton_cos, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->PushButton_tan, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->PushButton_sin, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->PushButton_atan, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->PushButton_asin, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->PushButton_acos, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->PushButton_log, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->PushButton_ln, SIGNAL(clicked()), this, SLOT(function()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_num() {
  QPushButton* button = static_cast<QPushButton*>(sender());
  QString currentText = ui->Labe_out->text();
  if (currentText == "ERROR") currentText = '0';
  if (currentText == "0" && button->text() != "0") {
    ui->Labe_out->setText(button->text());
  } else {
    if ((currentText.isEmpty() || currentText == "-") &&
        button->text() != "+") {
      ui->Labe_out->setText(currentText + button->text());
    } else {
      if (currentText.startsWith("+")) {
        currentText.remove(0, 1);
      }

      if (currentText.endsWith(')') || currentText.endsWith('x')) {
        ui->Labe_out->setText(currentText + "*" + button->text());
      } else {
        ui->Labe_out->setText(currentText + button->text());
      }
    }
  }

  if (ui->Labe_out->text().length() > 63) {
    double value = ui->Labe_out->text().toDouble();
    QString formattedText = QString::number(value, 'E', 6);
    ui->Labe_out->setText(formattedText);
  }
}

void MainWindow::function() {
  QPushButton* button = static_cast<QPushButton*>(sender());
  QString currentText = ui->Labe_out->text();
  QChar lastChar = currentText.back();
  if (currentText.endsWith('0') && currentText.length() == 1)
    currentText.chop(1);
  if ((lastChar.isDigit() && currentText.length() > 1) || lastChar == 'x') {
    ui->Labe_out->setText(currentText + '*' + button->text() + "(");
  } else
    ui->Labe_out->setText(currentText + button->text() + "(");
}

void MainWindow::on_PushButton_dot_clicked() {
  QString currentText = ui->Labe_out->text();
  int len = currentText.length();
  if (len == 0 || is_operator(currentText[len - 1].toLatin1()) ||
      currentText.back() == '(') {
    ui->Labe_out->setText(currentText + "0.");
  } else {
    int lastNumberStart = -1;
    for (int i = len - 1; i >= 0; i--) {
      QChar ch = currentText[i];
      if (ch.isDigit() || ch == '.') {
        lastNumberStart = i;
      } else {
        break;
      }
    }

    if (lastNumberStart >= 0) {
      QString lastNumber = currentText.mid(lastNumberStart);
      if (!lastNumber.contains('.')) {
        ui->Labe_out->setText(currentText + ".");
      }
    }
  }
}
void MainWindow::on_PushButton_div_clicked() {
  QString currentText = ui->Labe_out->text();
  QChar prevChar = currentText.length() > 1
                       ? currentText[currentText.length() - 2]
                       : QChar(' ');
  if (!currentText.isEmpty()) {
    QChar lastChar = currentText.back();
    if ((lastChar == '+' || lastChar == '-' || lastChar == '*' ||
         lastChar == '^' || lastChar == '%') &&
        prevChar != '(' && currentText.length() > 1) {
      currentText.chop(1);
      currentText += '/';
      ui->Labe_out->setText(currentText);
    } else if (std::isdigit(lastChar.toLatin1()) || lastChar == ')' ||
               lastChar == 'x') {
      currentText += '/';
      ui->Labe_out->setText(currentText);
    }
  }
}

void MainWindow::on_PushButton_mult_clicked() {
  QString currentText = ui->Labe_out->text();
  QChar prevChar = currentText.length() > 1
                       ? currentText[currentText.length() - 2]
                       : QChar(' ');
  if (!currentText.isEmpty()) {
    QChar lastChar = currentText.back();
    if ((lastChar == '+' || lastChar == '-' || lastChar == '/' ||
         lastChar == '^' || lastChar == '%') &&
        prevChar != '(' && currentText.length() > 1) {
      currentText.chop(1);
      currentText += '*';
      ui->Labe_out->setText(currentText);
    } else if (std::isdigit(lastChar.toLatin1()) || lastChar == ')' ||
               lastChar == 'x') {
      currentText += '*';
      ui->Labe_out->setText(currentText);
    }
  }
}

void MainWindow::on_PushButton_exp_clicked() {
  QString currentText = ui->Labe_out->text();
  QChar prevChar = currentText.length() > 1
                       ? currentText[currentText.length() - 2]
                       : QChar(' ');
  if (!currentText.isEmpty()) {
    QChar lastChar = currentText.back();
    if ((lastChar == '+' || lastChar == '-' || lastChar == '*' ||
         lastChar == '/') &&
        prevChar != '(' && currentText.length() > 1) {
      currentText.chop(1);
      currentText += '^';
      ui->Labe_out->setText(currentText);
    } else if (std::isdigit(lastChar.toLatin1()) || lastChar == ')' ||
               lastChar == 'x') {
      currentText += '^';
      ui->Labe_out->setText(currentText);
    }
  }
}

void MainWindow::on_PushButton_minus_clicked() {
  std::string text = ui->Labe_out->text().toStdString();
  QString currentText = ui->Labe_out->text();
  QChar lastChar = currentText.back();
  if (currentText.isEmpty()) {
    ui->Labe_out->setText("-");
  } else if ((lastChar == '0' && currentText.length() == 1) ||
             (currentText.length() == 1 && currentText[0] == '+')) {
    ui->Labe_out->setText("-");
  } else if (lastChar == '*' || lastChar == '/' || lastChar == '^' ||
             lastChar == '%') {
    ui->Labe_out->setText(ui->Labe_out->text() + "(-");
  } else if (lastChar == '+') {
    currentText.chop(1);
    currentText += '-';
    ui->Labe_out->setText(currentText);
  } else if (lastChar == '(' || lastChar == ' ' || lastChar == '.') {
    ui->Labe_out->setText(currentText + "-");
  } else if (std::isdigit(text.back()) || lastChar == ')' || lastChar == 'x') {
    ui->Labe_out->setText(ui->Labe_out->text() + "-");
  }
}

void MainWindow::on_PushButton_plus_clicked() {
  std::string text = ui->Labe_out->text().toStdString();
  QString currentText = ui->Labe_out->text();
  QChar lastChar = currentText.back();
  QChar prevChar = currentText.length() > 1
                       ? currentText[currentText.length() - 2]
                       : QChar(' ');
  if (currentText.isEmpty()) {
    ui->Labe_out->setText("+");
  } else if ((lastChar == '0' && currentText.length() == 1) ||
             (currentText.length() == 1 && currentText[0] == '-')) {
    ui->Labe_out->setText("+");
  } else if (std::isdigit(text.back()) || lastChar == ')' || lastChar == 'x') {
    ui->Labe_out->setText(ui->Labe_out->text() + "+");
  } else if (lastChar == '-' || lastChar == '*' || lastChar == '/' ||
             prevChar == '(' || lastChar == '^' || lastChar == '%') {
    if (prevChar == '(' && lastChar == '-') {
      currentText.chop(1);
      ui->Labe_out->setText(currentText);
    } else {
      currentText.chop(1);
      currentText += '+';
      ui->Labe_out->setText(currentText);
    }
  }
}

void MainWindow::on_pushButton_mod_clicked() {
  QString currentText = ui->Labe_out->text();
  QChar prevChar = currentText.length() > 1
                       ? currentText[currentText.length() - 2]
                       : QChar(' ');
  if (!currentText.isEmpty()) {
    QChar lastChar = currentText.back();
    if ((lastChar == '+' || lastChar == '-' || lastChar == '*' ||
         lastChar == '/' || lastChar == '^') &&
        prevChar != '(') {
      currentText.chop(1);
      currentText += '^';
      ui->Labe_out->setText(currentText);
    } else if (std::isdigit(lastChar.toLatin1()) || lastChar == ')' ||
               lastChar == 'x') {
      currentText += '%';
      ui->Labe_out->setText(currentText);
    }
  }
}

void MainWindow::on_PushButton_bracket1_clicked() {
  QString currentText = ui->Labe_out->text();

  if (currentText.isEmpty() || currentText.endsWith('0') ||
      currentText.endsWith('+') || currentText.endsWith('-') ||
      currentText.endsWith('*') || currentText.endsWith('/') ||
      currentText.endsWith('^')) {
    if (currentText.endsWith('0') && currentText.length() == 1)
      currentText.chop(1);

    ui->Labe_out->setText(currentText + '(');
  } else if (!(currentText.endsWith('('))) {
    ui->Labe_out->setText(currentText + "*(");
  }
}

void MainWindow::on_PushButton_bracket2_clicked() {
  QString currentText = ui->Labe_out->text();
  int openBracketsCount = currentText.count('(');
  int closeBracketsCount = currentText.count(')');

  if (openBracketsCount > closeBracketsCount && !currentText.endsWith('(')) {
    if (currentText.endsWith('0') && currentText.length() == 1)
      currentText.chop(1);
    if (currentText.back().isDigit()) ui->Labe_out->setText(currentText + ')');
  }
}

void MainWindow::on_PushButton_del_clicked() {
  QString currentText = ui->Labe_out->text();
  if (!currentText.isEmpty()) {
    currentText.chop(1);
    ui->Labe_out->setText(currentText);
  } else {
    ui->Labe_out->setText("0");
  }
}

void MainWindow::on_PushButton_all_del_clicked() {
  ui->Labe_out->clear();
  ui->xValue->clear();
  ui->Labe_out->setText("0");
}

void MainWindow::on_PushButton_percent_clicked() {
  QString currentText = ui->Labe_out->text();
  static QRegularExpression regex(R"([-+]?\d*\.?\d+(?:[eE][-+]?\d+)?)");
  QRegularExpressionMatchIterator matchIterator =
      regex.globalMatch(currentText);

  QString lastNumber;
  int lastNumberStart = -1;
  int lastNumberEnd = -1;

  while (matchIterator.hasNext()) {
    QRegularExpressionMatch match = matchIterator.next();
    lastNumber = match.captured();
    lastNumberStart = match.capturedStart();
    lastNumberEnd = match.capturedEnd();
  }

  if (!lastNumber.isEmpty() && lastNumberStart >= 0 && lastNumberEnd >= 0) {
    double number = lastNumber.toDouble();
    double result = number * 0.01;
    QString resultString = QString::number(result);

    currentText.remove(lastNumberStart, lastNumberEnd - lastNumberStart);
    currentText.insert(lastNumberStart, resultString);

    ui->Labe_out->setText(currentText);
  }
}

void MainWindow::on_PushButton_equals_clicked() {
  QPushButton* buttonEquals = ui->PushButton_equals;
  QString currentText = ui->Labe_out->text();
  int countOpenBracket = currentText.count('('),
      countClosedBracket = currentText.count(')');
  while (countClosedBracket < countOpenBracket) {
    currentText += ')';
    countClosedBracket++;
  }
  QByteArray currentTextUtf8 = currentText.toUtf8();
  char* currentTextCStr = currentTextUtf8.data();
  char postfix[MAX_SIZE];
  int exit_status = infix_to_postfix(currentTextCStr, postfix);
  QString strValue = ui->xValue->toPlainText();
  bool ok;
  double x = strValue.toDouble(&ok);
  int countX = currentText.count('x');
  if (buttonEquals->text() == '=') {
    if (exit_status == OK && ((countX == 0 && !ok) || (countX > 0 && ok))) {
      char result[MAX_SIZE] = {0};
      evaluate_postfix(postfix, x, result);
      QString resultString = QString::fromUtf8(result);
      ui->Labe_out->setText(resultString);
    } else if (exit_status == OK && countX > 0 && !ok) {
      QMessageBox::information(this, "ERROR", "Enter a value for x correctly");
    } else {
      ui->Labe_out->setText("ERROR");
    }
  } else if (buttonEquals->text() == "PLOT") {
    QString resultString = QString::fromUtf8(postfix);
    emit plot(resultString, strValue);
  }
}

void MainWindow::on_PushButton_graph_clicked() {
  QPushButton* buttonGraph = ui->PushButton_graph;
  QPushButton* buttonEquals = ui->PushButton_equals;
  if (buttonGraph->property("isPressed").toBool()) {
    if (GraphWindow && GraphWindow->isVisible()) {
      GraphWindow->close();
    }
    buttonGraph->setStyleSheet(
        "  border-radius: 9px;"
        "  background-color: #a9b8c2;"
        "  color: #ffffff;"
        "  border: 2px outset #9cacb6;");

    buttonEquals->setText("=");
    buttonEquals->setStyleSheet(
        "QPushButton {"
        "  border-radius: 10px;"
        "  background-color: #C1E80C;"
        "  color: white;"
        "  border: 2px outset #add00a;"
        "  font-size: 30px;"
        "}"
        "QPushButton:pressed {"
        "  background-color: #add00a;"
        "  border: 2px outset #9ab909;"
        "  font-size: 29px;"
        "}");
  } else {
    buttonGraph->setStyleSheet(
        "QPushButton#PushButton_graph {"
        "  border-radius: 9px;"
        "  background-color: #87959f;"
        "  color: #ffffff;"
        "  border: 2px outset #79868f;"
        "}");
    buttonEquals->setText("PLOT");
    buttonEquals->setStyleSheet(
        "QPushButton {"
        "  border-radius: 10px;"
        "  background-color: #8c8cd3;"
        "  color: #ffffff;"
        "  border: 2px outset #7c7cbc;"
        "  font-size: 20px;"
        "  font-weight: bold;"
        "}"
        "QPushButton:pressed {"
        "  background-color: #7c7cbc;"
        "  border: 2px outset #6d6da4;"
        "  font-size: 19px;"
        "}");
    GraphWindow = new graph(this);
    int mainWinWidth = this->width();
    int mainWinX = this->x();
    int mainWinY = this->y();
    int modalX = mainWinX + mainWinWidth;
    int modalY = mainWinY + 28;
    GraphWindow->setGeometry(modalX, modalY, 400, 570);
    if (!GraphWindow->isVisible()) GraphWindow->show();
    connect(this, &MainWindow::plot, GraphWindow, &graph::plot);
  }

  buttonGraph->setProperty("isPressed",
                           !buttonGraph->property("isPressed").toBool());
}

void MainWindow::on_PushButton_cred_clicked() {
  QPushButton* buttonCred = ui->PushButton_cred;
  QPushButton* buttonDep = ui->PushButton_dep;
  if (buttonCred->property("isPressed").toBool()) {
    if (CreditWindow && CreditWindow->isVisible()) CreditWindow->close();
    buttonCred->setStyleSheet(
        "  border-radius: 7px;"
        "  background-color: #a9b8c2;"
        "  color: #ffffff;"
        "  border: 2px outset #9cacb6;");
  } else {
    if (DepositWindow && DepositWindow->isVisible()) {
      DepositWindow->close();
      buttonDep->setProperty("isPressed",
                             !buttonDep->property("isPressed").toBool());
      buttonDep->setStyleSheet(
          "  border-radius: 7px;"
          "  background-color: #a9b8c2;"
          "  color: #ffffff;"
          "  border: 2px outset #9cacb6;");
    }

    buttonCred->setStyleSheet(
        "  border-radius: 7px;"
        "  background-color: #92a1ab;"
        "  color: #ffffff;"
        "  border: 2px outset #87959f;");
    CreditWindow = new credit(this);
    int mainWinX = this->x();
    int mainWinY = this->y();
    int modalX = mainWinX - 450;
    int modalY = mainWinY + 100;
    CreditWindow->setGeometry(modalX, modalY, 450, 285);
    if (!CreditWindow->isVisible()) CreditWindow->show();
  }
  buttonCred->setProperty("isPressed",
                          !buttonCred->property("isPressed").toBool());
}

void MainWindow::on_PushButton_dep_clicked() {
  QPushButton* buttonDep = ui->PushButton_dep;
  QPushButton* buttonCred = ui->PushButton_cred;
  if (buttonDep->property("isPressed").toBool()) {
    if (DepositWindow && DepositWindow->isVisible()) DepositWindow->close();
    buttonDep->setStyleSheet(
        "  border-radius: 7px;"
        "  background-color: #a9b8c2;"
        "  color: #ffffff;"
        "  border: 2px outset #9cacb6;");
  } else {
    if (CreditWindow && CreditWindow->isVisible()) {
      CreditWindow->close();
      buttonCred->setProperty("isPressed",
                              !buttonCred->property("isPressed").toBool());
      buttonCred->setStyleSheet(
          "  border-radius: 7px;"
          "  background-color: #a9b8c2;"
          "  color: #ffffff;"
          "  border: 2px outset #9cacb6;");
    }

    buttonDep->setStyleSheet(
        "  border-radius: 7px;"
        "  background-color: #92a1ab;"
        "  color: #ffffff;"
        "  border: 2px outset #87959f;");
    DepositWindow = new deposit(this);
    int mainWinX = this->x();
    int mainWinY = this->y();
    int modalX = mainWinX - 450;
    int modalY = mainWinY + 100;
    DepositWindow->setGeometry(modalX, modalY, 450, 280);
    if (!DepositWindow->isVisible()) DepositWindow->show();
  }
  buttonDep->setProperty("isPressed",
                         !buttonDep->property("isPressed").toBool());
}

void MainWindow::on_PushButton_x_clicked() {
  QString currentText = ui->Labe_out->text();
  QChar lastChar = currentText.back();
  if (lastChar == '0' && currentText.length() == 1) {
    ui->Labe_out->setText("x");
  } else if (!currentText.isEmpty() && lastChar != 'x') {
    if (lastChar.isDigit() || lastChar == ')') {
      ui->Labe_out->setText(currentText + "*x");
    } else
      ui->Labe_out->setText(currentText + 'x');
  }
}

void MainWindow::on_PushButton_sqrt_clicked() {
  QString currentText = ui->Labe_out->text();
  QChar lastChar = currentText.back();
  if (currentText.endsWith('0') && currentText.length() == 1)
    currentText.chop(1);
  if ((lastChar.isDigit() && currentText.length() > 1) || lastChar == 'x') {
    ui->Labe_out->setText(currentText + '*' + "sqrt" + "(");
  } else
    ui->Labe_out->setText(currentText + "sqrt" + "(");
}
