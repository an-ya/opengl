#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include "glwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnA_pressed();
    void on_btnA_released();
    void on_btnD_pressed();
    void on_btnD_released();
    void on_btnS_pressed();
    void on_btnS_released();
    void on_btnW_pressed();
    void on_btnW_released();
    void setInputValue(int value);
    void setSliderValue(const QString &text);

private:
    Ui::MainWindow *ui;

    virtual void keyPressEvent(QKeyEvent *ev);
    virtual void keyReleaseEvent(QKeyEvent *ev);
};

#endif // MAINWINDOW_H
