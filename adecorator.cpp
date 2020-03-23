#include "adecorator.h"

ADecorator::ADecorator()
{

}

MoonDecorator::MoonDecorator(long double t0, long double t1, long double SamplingIncrement,
                           TModel &decorator,TVector & X0)
{
    EMS=new ModelEMS(t0,t1,SamplingIncrement);

    Model=&decorator;

    this->t0=t0;
    this->t1=t1*EMS->T;
    this->SamplingIncrement=SamplingIncrement*EMS->T;

    this->GlobalT=t0;

    this->X0=X0;

    Run();
}

void MoonDecorator::Run()
{
    //считаем для Луны
    TIntegrator * integrator=new TDormandPrince();
    integrator->setPrecision(1e-18);
    integrator->Run(EMS);
    delete integrator;

    for(int i=0;i<EMS->getResult().GetRowCount();i++)
    {
        TVector arg(9);
        for(int j=0;j<9;j++)
            arg[j]=EMS->getResult()(i,j+1);
        vec_dX_EMS.push_back(std::move(arg));
    }

}

TVector MoonDecorator::getRight( const TVector& X, long double t )
{
    TVector Y(6);
    TVector dX_EMS(9);
   if (t<GlobalT+SamplingIncrement){
       dX_EMS=vec_dX_EMS.at(GlobalIndex);
   } else {
       if(EMS->getResult().GetRowHigh()>GlobalIndex)
       {
           GlobalT+=SamplingIncrement;
           GlobalIndex++;
       }
   }
   for(int i=0;i<3;i++)
       Y[i]=X[i+3];


   TVector dx_Sattelite=Model->getRight(X,t);
   TVector RMoon(3);

   TVector EM(3);
   //EM=(dX_EMS.Concat(0,2)-dX_EMS.Concat(3,5))*EMS->a;
   for(int i=0;i<3;i++)
       EM[i]=dX_EMS[i]-dX_EMS[i+3];

   EM=EM*(EMS->a);
   RMoon=EM;
   for(int i=0;i<3;i++)
       RMoon[i]-=X[i];

   auto u=EMS->mu[0]*EMS->G;

   auto RMoonlength=pow(RMoon.length(),3);
//   auto EMlength=pow(EM.length()/EMS->a,3)*pow(EMS->a,3);

   Y[3]=dx_Sattelite[3]+u/RMoonlength*RMoon[0];
   Y[4]=dx_Sattelite[4]+u/RMoonlength*RMoon[1];
   Y[5]=dx_Sattelite[5]+u/RMoonlength*RMoon[2];

   return Y;
}


SunDecorator::SunDecorator(long double t0, long double t1, long double SamplingIncrement,
                           TModel &decorator,TVector & X0)
{
    EMS=new ModelEMS(t0,t1,SamplingIncrement);
    Model=&decorator;
    this->t0=t0;
    this->t1=t1*EMS->T;
    this->SamplingIncrement=SamplingIncrement*EMS->T;
    this->GlobalT=t0;
    this->X0=X0;
    Run();
}

void SunDecorator::Run()
{
    //считаем как бы для луны
    TIntegrator * integrator=new TDormandPrince();
    //считаем как бы для солнца
    integrator->setPrecision(1e-18);
    integrator->Run(EMS);
    delete integrator;

    for(int i=0;i<EMS->getResult().GetRowCount();i++)
    {
        TVector arg(9);
        for(int j=0;j<9;j++)
            arg[j]=EMS->getResult()(i,j+1);
        vec_dX_EMS.push_back(std::move(arg));
    }

}

 TVector SunDecorator::getRight(const TVector &X, long double t)
 {
        TVector Y(6);
        TVector dX=Model->getRight(X,t);
        TVector dX_EMS(9);
        TVector RSun(3);

       if (t<GlobalT+SamplingIncrement){
           dX_EMS=vec_dX_EMS.at(GlobalIndex);
       } else {
           if(EMS->getResult().GetRowHigh()>GlobalIndex)
           {
               GlobalT+=SamplingIncrement;
               GlobalIndex++;
           }
       }

        for(int i=0;i<3;i++)
            Y[i]=X[i+3];

        //ошибка в логике (нужно было брать X[0],X[1],X[2]
        for(int i=0;i<3;i++)
        RSun[i]=(dX_EMS[i+6]-dX_EMS[i+3]);
        RSun=RSun*(EMS->a);
        for(int i=0;i<3;i++)
            RSun[i]-=X[i];

        auto RSunlength=pow(RSun.length(),3);
        auto u=EMS->mu[2]*EMS->G;

        Y[3]=dX[3]+u/RSunlength*RSun[0];
        Y[4]=dX[4]+u/RSunlength*RSun[1];
        Y[5]=dX[5]+u/RSunlength*RSun[2];
        return Y;

 }
