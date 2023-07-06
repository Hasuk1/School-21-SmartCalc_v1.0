#include "mainwindow.h"

#include <float.h>

#include <QDebug>
#include <QMessageBox>
#include <string>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      x_input_validator(-9999999999999999, 9999999999999999, 17, this),
      input_area_validator(QRegularExpression(
          "^[(sin|cos|ln|tan|log|mod|asin|atan|acos|sqrt|)0-9^/*-+xe.]{255}")) {
  ui->setupUi(this);
  // make custom window
  this->setWindowFlags(Qt::WindowType::FramelessWindowHint);
  // set validators
  QLocale locale(QLocale::English);
  x_input_validator.setNotation(QDoubleValidator::StandardNotation);
  x_input_validator.setLocale(locale);
  ui->lineedit_xinput->setValidator(&x_input_validator);
  ui->InputArea->setValidator(&input_area_validator);
  // connect slots and signals
  bind_slots();
  // hide x field
  x_input_display(false);
  // Make Buttons Checkable
  ui->pushButton_plot->setCheckable(true);
  ui->pushButton_deposit->setCheckable(true);
  ui->pushButton_credit->setCheckable(true);
  ui->pushButton_rpn->setCheckable(true);
  // Creating additional Windows
  plotWindow = new Plot(this);
  ui->fx->hide();
  depositWindow = new deposit(this);
  creditWindow = new credit(this);
  rpnWindow = new rpn(this);
  // connect them
  connect_windows();
  // Make them frameless
  plotWindow->setWindowFlag(Qt::WindowType::FramelessWindowHint);
  depositWindow->setWindowFlag(Qt::WindowType::FramelessWindowHint);
  creditWindow->setWindowFlag(Qt::WindowType::FramelessWindowHint);
  rpnWindow->setWindowFlag(Qt::WindowType::FramelessWindowHint);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::mousePressEvent(QMouseEvent *event) {
  cur_pos = event->globalPosition().toPoint();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
  new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
  move(x() + new_pos.x(), y() + new_pos.y());

  // Moving modal windows with main
  plotWindow->move(plotWindow->x() + new_pos.x(),
                   plotWindow->y() + new_pos.y());
  depositWindow->move(depositWindow->x() + new_pos.x(),
                      depositWindow->y() + new_pos.y());
  creditWindow->move(creditWindow->x() + new_pos.x(),
                     creditWindow->y() + new_pos.y());
  rpnWindow->move(rpnWindow->x() + new_pos.x(), rpnWindow->y() + new_pos.y());

  cur_pos = event->globalPosition().toPoint();
}

void MainWindow::open_windows() {
  // Move them to right place
  plotWindow->move(this->x() + 361, this->y() + 125);
  depositWindow->move(this->x() + 361, this->y() + 185);
  creditWindow->move(this->x() + 361, this->y() + 245);

  // logic for open modal windows
  QPushButton *pressedBtn = (QPushButton *)sender();
  if (pressedBtn->y() == 0) {
    if (pressedBtn->isChecked()) {
      plotWindow->show();
      ui->pushButton_eq->setText("plot");
      ui->fx->show();
      ui->pushButton_deposit->setChecked(false);
      ui->pushButton_credit->setChecked(false);
    } else {
      plotWindow->hide();
      ui->fx->hide();
      ui->pushButton_eq->setText("=");
    }
    depositWindow->hide();
    creditWindow->hide();
  } else if (pressedBtn->y() == 60) {
    if (pressedBtn->isChecked()) {
      depositWindow->show();
      ui->pushButton_plot->setChecked(false);
      ui->pushButton_credit->setChecked(false);
    } else {
      depositWindow->hide();
    }
    plotWindow->hide();
    ui->fx->hide();
    ui->pushButton_eq->setText("=");
    creditWindow->hide();
  } else if (pressedBtn->y() == 120) {
    if (pressedBtn->isChecked()) {
      creditWindow->show();
      ui->pushButton_deposit->setChecked(false);
      ui->pushButton_plot->setChecked(false);
    } else {
      creditWindow->hide();
    }
    depositWindow->hide();
    plotWindow->hide();
    ui->fx->hide();
    ui->pushButton_eq->setText("=");
  }
  x_input_handler();
}

void MainWindow::on_pushButton_rpn_clicked() {
  rpnWindow->move(this->x() + 30, this->y() + 611);
  if (ui->pushButton_rpn->isChecked()) {
    rpnWindow->show();
  } else {
    rpnWindow->hide();
  }
}

void MainWindow::on_pushButton_eq_clicked() {
  // Transform InputArea text to C str
  std::string str = ui->InputArea->text().toStdString();
  const char *cstr = str.c_str();
  bool is_error = false;

  if (ui->pushButton_eq->text() == "=") {
    // RPN sender
    char res_str[MAX_LEN * 2] = {'\0'};
    api_infix_to_postfix_notation(cstr, res_str);
    emit rpn_signal(res_str);
    if (ui->label_fxico->isVisible()) {
      if (check_is_x_set()) {
        // API to count with X
        long double res = 0;
        is_error = api_calculate_str_with_x(
            cstr, (long double)ui->lineedit_xinput->text().toDouble(), &res);
        if (!is_error) {
          QString result = QString::number(res, 'g', 7);
          ui->InputArea->setText(result);
        } else {
          ui->InputArea->setText("Error");
        }
      } else {
        // window with error that x doesnt set
        QMessageBox::warning(this, "X not defined",
                             "Please enter value ​​for X");
      }
    } else {
      // API to count without X
      long double res = 0;
      is_error = api_calculate_str(cstr, &res);
      if (!is_error) {
        QString result = QString::number(res, 'g', 7);
        ui->InputArea->setText(result);
      } else {
        ui->InputArea->setText("Error");
      }
    }
  } else if (ui->pushButton_eq->text() == "plot") {
    emit plot_signal(cstr);
  }
}

void MainWindow::input_btns_clicked() {
  QPushButton *pressed_btn = (QPushButton *)sender();
  QByteArray btn_text = pressed_btn->text().toLocal8Bit();
  const char *c_str = btn_text.data();

  if (ui->InputArea->text() == '0' && !strpbrk(c_str, "+-/*.^")) {
    ui->InputArea->setText("");
  }
  if (strpbrk(c_str, "0123456789x+-()^.")) {
    ui->InputArea->setText(ui->InputArea->text() + pressed_btn->text());
  } else if (strpbrk(c_str, "√")) {
    ui->InputArea->setText(ui->InputArea->text() + "sqrt(");
  } else {
    ui->InputArea->setText(ui->InputArea->text() + pressed_btn->text() + "(");
  }
}

void MainWindow::on_pushButton_mult_clicked() {
  ui->InputArea->setText(ui->InputArea->text() + "*");
}

void MainWindow::on_pushButton_div_clicked() {
  ui->InputArea->setText(ui->InputArea->text() + "/");
}

void MainWindow::bind_slots() {
  /* BIND SLOTS WITH SIGNALS */
  connect(ui->InputArea, SIGNAL(textChanged(QString)), this,
          SLOT(x_input_handler()));
  // |- navigation
  connect(ui->pushButton_close, SIGNAL(clicked()), this, SLOT(close()));
  connect(ui->pushButton_minimize, SIGNAL(clicked()), this,
          SLOT(minimization()));
  connect(ui->pushButton_plot, SIGNAL(clicked()), this, SLOT(open_windows()));
  connect(ui->pushButton_deposit, SIGNAL(clicked()), this,
          SLOT(open_windows()));
  connect(ui->pushButton_credit, SIGNAL(clicked()), this, SLOT(open_windows()));
  // |- input buttons
  // |-- numbers
  connect(ui->pushButton_one, SIGNAL(clicked()), this,
          SLOT(input_btns_clicked()));
  connect(ui->pushButton_two, SIGNAL(clicked()), this,
          SLOT(input_btns_clicked()));
  connect(ui->pushButton_three, SIGNAL(clicked()), this,
          SLOT(input_btns_clicked()));
  connect(ui->pushButton_four, SIGNAL(clicked()), this,
          SLOT(input_btns_clicked()));
  connect(ui->pushButton_five, SIGNAL(clicked()), this,
          SLOT(input_btns_clicked()));
  connect(ui->pushButton_six, SIGNAL(clicked()), this,
          SLOT(input_btns_clicked()));
  connect(ui->pushButton_seven, SIGNAL(clicked()), this,
          SLOT(input_btns_clicked()));
  connect(ui->pushButton_eight, SIGNAL(clicked()), this,
          SLOT(input_btns_clicked()));
  connect(ui->pushButton_nine, SIGNAL(clicked()), this,
          SLOT(input_btns_clicked()));
  connect(ui->pushButton_zero, SIGNAL(clicked()), this,
          SLOT(input_btns_clicked()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this,
          SLOT(input_btns_clicked()));
  // |-- operatos
  connect(ui->pushButton_dot, SIGNAL(clicked()), this,
          SLOT(input_btns_clicked()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(input_btns_clicked()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(input_btns_clicked()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this,
          SLOT(input_btns_clicked()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this,
          SLOT(input_btns_clicked()));
  connect(ui->pushButton_opbracket, SIGNAL(clicked()), this,
          SLOT(input_btns_clicked()));
  connect(ui->pushButton_clbracket, SIGNAL(clicked()), this,
          SLOT(input_btns_clicked()));
  // |-- functions
  connect(ui->pushButton_cos, SIGNAL(clicked()), this,
          SLOT(input_btns_clicked()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this,
          SLOT(input_btns_clicked()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this,
          SLOT(input_btns_clicked()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this,
          SLOT(input_btns_clicked()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this,
          SLOT(input_btns_clicked()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this,
          SLOT(input_btns_clicked()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this,
          SLOT(input_btns_clicked()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this,
          SLOT(input_btns_clicked()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this,
          SLOT(input_btns_clicked()));
}

void MainWindow::on_pushButton_del_clicked() {
  QString res = ui->InputArea->text();
  res.chop(1);
  ui->InputArea->setText(res);
  if (ui->InputArea->text() == "") {
    ui->InputArea->setText("0");
  }
}

void MainWindow::on_pushButton_clear_clicked() { ui->InputArea->setText("0"); }

void MainWindow::x_input_display(bool val) {
  if (val) {
    ui->label_fxico->setVisible(true);
    ui->lineedit_xinput->setVisible(true);
  } else {
    ui->label_fxico->setVisible(false);
    ui->lineedit_xinput->setVisible(false);
  }
}

void MainWindow::x_input_handler() {
  QByteArray btn_text = ui->InputArea->text().toLocal8Bit();
  const char *c_str = btn_text.data();
  if (strchr(c_str, 'x') && !ui->pushButton_plot->isChecked()) {
    x_input_display(true);
  } else {
    x_input_display(false);
  }
}

bool MainWindow::check_is_x_set() {
  return !ui->lineedit_xinput->text().isEmpty();
}

void MainWindow::connect_windows() {
  connect(this, &MainWindow::rpn_signal, rpnWindow, &rpn::rpn_slot);
  connect(this, &MainWindow::plot_signal, plotWindow, &Plot::plot_slot);
}

// Clear 0 if keyboard input start
void MainWindow::on_InputArea_textChanged(const QString &arg1) {
  if (arg1.length() == 2) {
    if (arg1[0] == '0') {
      if (arg1[1] != '+' && arg1[1] != '-' && arg1[1] != '/' &&
          arg1[1] != '*' && arg1[1] != '.' && arg1[1] != '^') {
        ui->InputArea->setText(arg1[1]);
      }
    }
  }
}

void MainWindow::minimization() {
  if (ui->pushButton_plot->isChecked() || ui->pushButton_deposit->isChecked() ||
      ui->pushButton_credit->isChecked() || ui->pushButton_rpn->isChecked()) {
    plotWindow->hide();
    ui->fx->hide();
    ui->pushButton_eq->setText("=");
    depositWindow->hide();
    creditWindow->hide();
    rpnWindow->hide();
    x_input_handler();
    ui->pushButton_plot->setChecked(false);
    ui->pushButton_credit->setChecked(false);
    ui->pushButton_deposit->setChecked(false);
    ui->pushButton_rpn->setChecked(false);
  }
  showMinimized();
}

void MainWindow::on_pushButton_minimize_2_clicked() { aboutWindow.show(); }
