#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLogValueAxis>
#include <QLineSeries>
#include <QValueAxis>
#include <QChart>
#include <QChartView>
#include <thread>
#include "sundial.h"
#include "Sattelite.h"
#include "modelems.h"
#include "normalgpz.h"
#include "adecorator.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


using namespace QtCharts;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_MainWindow_iconSizeChanged(const QSize &iconSize);

private:
    double theta=M_PI_4, i=M_PI_4, w=M_PI_4, a=20000000,  e=0.1, O=M_PI_4;
    Ui::MainWindow *ui;
    ModelEMS * E_S;
    Sattelite * E_M;
    TModel * Decorator_moon;
    TModel * Decorator_sun;
    TModel * Decorator_all;
    void setSeries(QLineSeries *series,TMatrix Result,int first,int second,int j,int k,double mas);
    void setDialog(long double theta,long double i,long double w,long double a,long double e,long double O);
};

#endif // MAINWINDOW_H
