#include "rpn.h"

#include "ui_rpn.h"

rpn::rpn(QWidget *parent) : QDialog(parent), ui(new Ui::rpn_window) {
  ui->setupUi(this);
}

rpn::~rpn() { delete ui; }

void rpn::rpn_slot(char *str) { ui->rpn_res->setText(str); }
