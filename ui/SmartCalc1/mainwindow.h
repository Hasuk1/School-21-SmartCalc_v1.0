#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
extern"C"{
#include "../../modules/modules.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void digits_num();

    void on_PushButton_dot_clicked();

    void on_PushButton_div_clicked();

    void on_PushButton_mult_clicked();

    void on_PushButton_minus_clicked();

    void on_PushButton_plus_clicked();

    void on_PushButton_bracket1_clicked();

    void on_PushButton_bracket2_clicked();

    void on_PushButton_del_clicked();

    void on_PushButton_all_del_clicked();

    void on_PushButton_cos_clicked();

    void on_PushButton_tan_clicked();

    void on_PushButton_sin_clicked();

    void on_PushButton_atan_clicked();

    void on_PushButton_asin_clicked();

    void on_PushButton_acos_clicked();

    void on_PushButton_log_clicked();

    void on_PushButton_ln_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
