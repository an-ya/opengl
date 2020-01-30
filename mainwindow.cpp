#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "windows.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    ui->openGLWidget->setFocusPolicy(Qt::StrongFocus);

    QRegExp rx("^[1-2]\\d|[1-9]|[1-2]\\d\\.\\d{1,4}|[1-9]\\.\\d{1,4}|30$"); //1到30的浮点数匹配
    QRegExpValidator *pReg = new QRegExpValidator(rx, this);
    ui->lineEdit->setValidator(pReg);

    ui->lineEdit->setText(QString("%1").arg(ui->openGLWidget->getT()));
    ui->slider->setValue((int)(ui->openGLWidget->getT() * 10000.0f));

    connect(ui->pushButton, SIGNAL(clicked(bool)), ui->openGLWidget, SLOT(render()));
    connect(ui->lineEdit, SIGNAL(textEdited(const QString &)), this, SLOT(setSliderValue(const QString &)));
    connect(ui->slider, SIGNAL(sliderMoved(int)), this, SLOT(setInputValue(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setInputValue(int value)
{
    // 放大倍数10000
    float v = (float)value / 10000.0f;
    ui->openGLWidget->setT(v);
    ui->lineEdit->setText(QString("%1").arg(v));
}

void MainWindow::setSliderValue(const QString &text)
{
    if (text.compare("") == 0) {
        ui->slider->setValue(10000);
        ui->openGLWidget->setT(1.0f);
    } else {
        ui->slider->setValue((int)(text.toFloat() * 10000.0f));
        ui->openGLWidget->setT(text.toFloat());
    }
}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    ui->openGLWidget->setKeyPressText(ev->text());
    switch (ev->key())
    {
    case Qt::Key_W:
        ui->btnW->setChecked(true);
        break;
    case Qt::Key_A:
        ui->btnA->setChecked(true);
        break;
    case Qt::Key_S:
        ui->btnS->setChecked(true);
        break;
    case Qt::Key_D:
        ui->btnD->setChecked(true);
        break;
    case Qt::Key_Left:
        ui->btnLeft->setChecked(true);
        break;
    case Qt::Key_Up:
        ui->btnUp->setChecked(true);
        break;
    case Qt::Key_Right:
        ui->btnRight->setChecked(true);
        break;
    case Qt::Key_Down:
        ui->btnDown->setChecked(true);
        break;
    default:
        break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *ev)
{
    ui->openGLWidget->setKeyPressText("");
    switch (ev->key())
    {
    case Qt::Key_W:
        ui->btnW->setChecked(false);
        break;
    case Qt::Key_A:
        ui->btnA->setChecked(false);
        break;
    case Qt::Key_S:
        ui->btnS->setChecked(false);
        break;
    case Qt::Key_D:
        ui->btnD->setChecked(false);
        break;
    case Qt::Key_Left:
        ui->btnLeft->setChecked(false);
        break;
    case Qt::Key_Up:
        ui->btnUp->setChecked(false);
        break;
    case Qt::Key_Right:
        ui->btnRight->setChecked(false);
        break;
    case Qt::Key_Down:
        ui->btnDown->setChecked(false);
    default:
        break;
    }
}


void MainWindow::on_btnA_pressed()
{
    keybd_event(0x41, 0, 0, 0);
}

void MainWindow::on_btnA_released()
{
    keybd_event(0x41, 0, KEYEVENTF_KEYUP, 0);
}

void MainWindow::on_btnD_pressed()
{
    keybd_event(0x44, 0, 0, 0);
}

void MainWindow::on_btnD_released()
{
    keybd_event(0x44, 0, KEYEVENTF_KEYUP, 0);
}

void MainWindow::on_btnS_pressed()
{
    keybd_event(0x53, 0, 0, 0);
}

void MainWindow::on_btnS_released()
{
    keybd_event(0x53, 0, KEYEVENTF_KEYUP, 0);
}

void MainWindow::on_btnW_pressed()
{
    keybd_event(0x57, 0, 0, 0);
}

void MainWindow::on_btnW_released()
{
    keybd_event(0x57, 0, KEYEVENTF_KEYUP, 0);
}
