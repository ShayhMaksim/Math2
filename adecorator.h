#ifndef ADECORATOR_H
#define ADECORATOR_H
#include "model.h"
#include "modelems.h"
#include "Sattelite.h"
#include "normalgpz.h"
#include <thread>
class ADecorator:public TModel
{
protected:
    long double GlobalT;
    int GlobalIndex=0;
public:
    TModel * Model;
    ADecorator();
    virtual void Run()=0;
};

class MoonDecorator:public ADecorator
{
public:
    MoonDecorator(long double t0, long double t1, long double SamplingIncrement,
                  TModel &decorator,TVector & X0);
    virtual TVector getRight( const TVector& X, long double t ) override;
    void Run() override;
    ModelEMS * EMS;
    std::vector<TVector> vec_dX_EMS;
};

class SunDecorator:public ADecorator
{
public:
    SunDecorator(long double t0, long double t1, long double SamplingIncrement,
                 TModel &decorator,TVector & X0);
    virtual TVector getRight( const TVector& X, long double t ) override;
    void Run() override;
    ModelEMS * EMS;
    std::vector<TVector> vec_dX_EMS;
};


#endif // ADECORATOR_H
