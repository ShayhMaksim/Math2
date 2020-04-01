#include "mainwindow.h"
#include <QApplication>
#include "adecorator.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    TVector X0=Sattelite::setInitialPosition(0,0,0,10000000,0,0);
//    ModelEMS * E_S=new ModelEMS(0,0.1,0.00001);
//    Sattelite * E_M=new Sattelite(0,E_S->T*0.003,0.00001*E_S->T,0,0,0,10000000,0,0);
//    MoonDecorator * Decorator_moon=new MoonDecorator(0,0.003,0.00001,*E_M,X0);
//    Decorator_moon->Run();

//    SunDecorator *Decorator_sun=new SunDecorator(0,0.003,0.00001,*Decorator_moon,X0);
//    Decorator_sun->Run();
//    TIntegrator * integrator=new TDormandPrince();
//    integrator->setPrecision(1e-18);
//    Decorator_sun->Run();
//    integrator->Run(Decorator_moon);
//    delete integrator;
//    Decorator_sun->getResult().toText("go");
    return a.exec();
}
