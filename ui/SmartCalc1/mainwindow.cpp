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
        if ((currentText.isEmpty() || currentText == "-") && button->text() != "+") {
            ui->Labe_out->setText(currentText + button->text());
        } else {
            if (currentText.startsWith("+")) {
                currentText.remove(0, 1);
            }

            if (currentText.endsWith(")")) {
                ui->Labe_out->setText(currentText + "×" + button->text());
            } else {
                ui->Labe_out->setText(currentText + button->text());
            }
        }
    }

    if (ui->Labe_out->text().length() > 14) {
        double value = ui->Labe_out->text().toDouble();
        QString formattedText = QString::number(value, 'E', 6);
        ui->Labe_out->setText(formattedText);
    }
}

void MainWindow::on_PushButton_dot_clicked()
{
    if (!(ui->Labe_out->text().contains('.'))) {
        ui->Labe_out->setText(ui->Labe_out->text() + ".");
    }
}

void MainWindow::on_PushButton_div_clicked()
{
    QString currentText = ui->Labe_out->text();
    QChar prevChar = currentText.length() > 1 ? currentText[currentText.length() - 2] : QChar(' ');
    if (!currentText.isEmpty())
    {
        QChar lastChar = currentText.back();
        if ((lastChar == '+' || lastChar == '-' || lastChar == QChar(0xD7)) && prevChar != '(')
        {
            currentText.chop(1);
            currentText += QChar(0xF7);
            ui->Labe_out->setText(currentText);
        }
        else if (std::isdigit(lastChar.toLatin1()) || lastChar == ')')
        {
            currentText += QChar(0xF7);
            ui->Labe_out->setText(currentText);
        }
    }
}

void MainWindow::on_PushButton_mult_clicked()
{
    QString currentText = ui->Labe_out->text();
    QChar prevChar = currentText.length() > 1 ? currentText[currentText.length() - 2] : QChar(' ');
    if (!currentText.isEmpty())
    {
        QChar lastChar = currentText.back();
        if ((lastChar == '+' || lastChar == '-' || lastChar == QChar(0xF7)) && prevChar != '(')
        {
            currentText.chop(1);
            currentText += QChar(0xD7);
            ui->Labe_out->setText(currentText);
        }
        else if (std::isdigit(lastChar.toLatin1()) || lastChar == ')')
        {
            currentText += QChar(0xD7);
            ui->Labe_out->setText(currentText);
        }
    }
}


void MainWindow::on_PushButton_minus_clicked()
{
    std::string text = ui->Labe_out->text().toStdString();
    QString currentText = ui->Labe_out->text();
    QChar lastChar = currentText.back();
    QChar prevChar = currentText.length() > 1 ? currentText[currentText.length() - 2] : QChar(' ');
        if (currentText.isEmpty()) {
            ui->Labe_out->setText("-");
        } else if (lastChar == '0' || (currentText.length() == 1 && currentText[0] == '+')) {
            ui->Labe_out->setText("-");
        } else if (lastChar == QChar(0xD7) || lastChar == QChar(0xF7)) {
            ui->Labe_out->setText(ui->Labe_out->text() + "(-");
        } else if (lastChar == '+' || prevChar == '(') {
            currentText.chop(1);
            currentText += '-';
            ui->Labe_out->setText(currentText);
        } else if (lastChar == '(' || lastChar == ' ' || lastChar == '.') {
            ui->Labe_out->setText(currentText + "-");
        } else if (std::isdigit(text.back()) || lastChar == ')') {
            ui->Labe_out->setText(ui->Labe_out->text() + "-");
        }
}


void MainWindow::on_PushButton_plus_clicked()
{
    std::string text = ui->Labe_out->text().toStdString();
    QString currentText = ui->Labe_out->text();
    QChar lastChar = currentText.back();
    QChar prevChar = currentText.length() > 1 ? currentText[currentText.length() - 2] : QChar(' ');
        if (currentText.isEmpty()) {
            ui->Labe_out->setText("+");
        } else if (lastChar == '0' || (currentText.length() == 1 && currentText[0] == '-')) {
            ui->Labe_out->setText("+");
        } else if (std::isdigit(text.back()) || lastChar == ')') {
            ui->Labe_out->setText(ui->Labe_out->text() + "-");
        } else if (lastChar == '-' || lastChar == QChar(0xD7) || lastChar == QChar(0xF7) || prevChar == '(') {
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


void MainWindow::on_PushButton_bracket1_clicked()
{
    QString currentText = ui->Labe_out->text();

    if (currentText.isEmpty() || currentText.endsWith('0') || currentText.endsWith('+') || currentText.endsWith('-')
        || currentText.endsWith(QChar(0xD7)) || currentText.endsWith(QChar(0xF7)))
    {
        if (currentText.endsWith('0'))
            currentText.chop(1);

        ui->Labe_out->setText(currentText + '(');
    }
    else if (!(currentText.endsWith('(')))
    {
        ui->Labe_out->setText(currentText + "×(");
    }
}

void MainWindow::on_PushButton_bracket2_clicked()
{
    QString currentText = ui->Labe_out->text();
    int openBracketsCount = currentText.count('(');
    int closeBracketsCount = currentText.count(')');

    if (openBracketsCount > closeBracketsCount && !currentText.endsWith('('))
    {
        if (currentText.endsWith('0'))
            currentText.chop(1);

        ui->Labe_out->setText(currentText + ')');
    }
}


void MainWindow::on_PushButton_del_clicked()
{
    QString currentText = ui->Labe_out->text();
    if (!currentText.isEmpty()) {
        currentText.chop(1);
        ui->Labe_out->setText(currentText);
    } else {
        ui->Labe_out->setText("0");
    }
}


void MainWindow::on_PushButton_all_del_clicked()
{
    ui->Labe_out->clear();
    ui->Labe_out->setText("0");
}


void MainWindow::on_PushButton_cos_clicked()
{
    QString currentText = ui->Labe_out->text();
    if (currentText.endsWith('0'))
        currentText.chop(1);
    ui->Labe_out->setText(currentText + "cos(");
}


void MainWindow::on_PushButton_tan_clicked()
{
    QString currentText = ui->Labe_out->text();
    if (currentText.endsWith('0'))
        currentText.chop(1);
    ui->Labe_out->setText(currentText + "tan(");
}


void MainWindow::on_PushButton_sin_clicked()
{
    QString currentText = ui->Labe_out->text();
    if (currentText.endsWith('0'))
        currentText.chop(1);
    ui->Labe_out->setText(currentText + "sin(");
}


void MainWindow::on_PushButton_atan_clicked()
{
    QString currentText = ui->Labe_out->text();
    if (currentText.endsWith('0'))
        currentText.chop(1);
    ui->Labe_out->setText(currentText + "atan(");
}


void MainWindow::on_PushButton_asin_clicked()
{
    QString currentText = ui->Labe_out->text();
    if (currentText.endsWith('0'))
        currentText.chop(1);
    ui->Labe_out->setText(currentText + "asin(");
}


void MainWindow::on_PushButton_acos_clicked()
{
    QString currentText = ui->Labe_out->text();
    if (currentText.endsWith('0'))
        currentText.chop(1);
    ui->Labe_out->setText(currentText + "acos(");
}


void MainWindow::on_PushButton_log_clicked()
{
    QString currentText = ui->Labe_out->text();
    if (currentText.endsWith('0'))
        currentText.chop(1);
    ui->Labe_out->setText(currentText + "log(");
}


void MainWindow::on_PushButton_ln_clicked()
{
    QString currentText = ui->Labe_out->text();
    if (currentText.endsWith('0'))
        currentText.chop(1);
    ui->Labe_out->setText(currentText + "ln(");
}

