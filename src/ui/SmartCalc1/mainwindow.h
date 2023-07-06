#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void delete_char();
    void delete_text();

    void on_PushButton_dot_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
