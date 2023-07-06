#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("SmartCalc");
    setFixedSize(width(), height());

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
    connect(ui->PushButton_del, SIGNAL(clicked()), this, SLOT(delete_char()));
    connect(ui->PushButton_all_del, SIGNAL(clicked()), this, SLOT(delete_text()));
    connect(ui->PushButton_dot, SIGNAL(clicked()), this, SLOT(on_PushButton_dot_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits_num()
{
    QPushButton* button = static_cast<QPushButton*>(sender());
    QString currentText = ui->Labe_out->text();

    if (currentText == "0" && button->text() != "0") {
        ui->Labe_out->setText(button->text());
    } else {
        ui->Labe_out->setText(currentText + button->text());
    }

    if (ui->Labe_out->text().length() > 14) {
        double value = ui->Labe_out->text().toDouble();
        QString formattedText = QString::number(value, 'E', 6);
        ui->Labe_out->setText(formattedText);
    }
}

void MainWindow::delete_char()
{
    QString currentText = ui->Labe_out->text();
    if (!currentText.isEmpty()) {
        currentText.chop(1);
        ui->Labe_out->setText(currentText);
    } else {
        ui->Labe_out->setText("0");
    }
}

void MainWindow::delete_text()
{
    ui->Labe_out->clear();
    ui->Labe_out->setText("0");
}

void MainWindow::on_PushButton_dot_clicked()
{
    if (!(ui->Labe_out->text().contains('.'))) {
        ui->Labe_out->setText(ui->Labe_out->text() + ".");
    }
}
