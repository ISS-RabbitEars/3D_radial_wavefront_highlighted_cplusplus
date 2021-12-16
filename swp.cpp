#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "ran3.h"
#include "vec.hpp"
using namespace std;

#define MBIG 1000000000
#define MSEED 161803398
#define MZ 0
#define FAC (1.0/MBIG)
#define PI 3.141592653589793238462643383

double s(vec&, double&, double&, double&, double&, double&);
double gamma(double, vec&);
vec rdt(double, vec&);
vec psi(vec&, double, vec*, int*, int, double, double, double, double, double, bool&);
bool rul(vec&, double, double, double);
int sum(int*,int);

int main()
{
    int N=100000;
    int Ne=1;
    int seed=-934121523;
    int tr,fps,nframes,ti[Ne],cf[N],Nred,Nblue,rcount,bcount;
    double xa,ya,za,sigma,k,omega,phi,lambda,nlambda,delt,d;
    vec rp[N],rpdt[N],rc[Ne];
    ofstream redfile,bluefile,rnfile,bnfile;
    bool red=false;

    /* initialize parameters */
    xa=1.;
    ya=1.;
    za=1.;
    tr=7;
    fps=30;
    nframes=fps*tr;
    
    sigma=0.1;
    nlambda=5;
    lambda=xa/nlambda;
    k=2*PI/lambda;
    omega=1;
    phi=PI/2;

    d=sqrt(xa*xa+ya*ya+za*za);
    delt=(d*k)/(omega*(nframes-1));
    /*------------------------*/
    
    ti[0]=0;
    rc[0]();
    
    /* initialize array of points */
    for(int i=0;i<N;i++)
	{
        rp[i](xa*(2.*ran3(&seed)-1.),ya*(2.*ran3(&seed)-1),za*(2.*ran3(&seed)-1));
        rpdt[i]();
        cf[i]=0;
	}
    
    
    string redpts="points/points_red_";
    string bluepts="points/points_blue_";
    string nredpts="points/Nred_";
    string nbluepts="points/Nblue_";
    for(int i=1;i<=nframes;i++)
    {
        string rpu,bpu,rnu,bnu,snum;
        stringstream ssnum;
        ssnum<<i;
        snum=ssnum.str();
        ssnum.str("");
        rpu=redpts+snum;
        bpu=bluepts+snum;
        rnu=nredpts+snum;
        bnu=nbluepts+snum;

        for(int j=0;j<N;j++)
        {
            rpdt[j]=psi(rp[j],Ne,rc,ti,i,delt,sigma,k,omega,phi,red);
            if(red) cf[j]=1;
            red=false;
        }
        
        Nred=sum(cf,N);
        Nblue=N-Nred;
                
        vec *rpts,*bpts;
        rpts= new vec[Nred];
        bpts= new vec[Nblue];
        rcount=0;
        bcount=0;
        for(int j=0;j<N;j++)
        {
            if(cf[j]==1)
            {
                rpts[rcount]=rpdt[j];
                rcount++;
                cf[j]=0;
            }
            else
            {
                bpts[bcount]=rpdt[j];
                bcount++;
            }
        }
        
        rnfile.open(rnu.c_str());
        rnfile<<Nred<<endl;
        rnfile.close();
 
        bnfile.open(bnu.c_str());
        bnfile<<Nblue<<endl;
        bnfile.close();
        
        redfile.open(rpu.c_str());
        for(int j=0;j<Nred;j++)
        {
            redfile<<rpts[j];
            if(j<Nred-1) redfile<<",";
            redfile<<endl;
        }
        redfile.close();
        
        bluefile.open(bpu.c_str());
        for(int j=0;j<Nblue;j++)
        {
            bluefile<<bpts[j];
            if(j<Nblue-1) bluefile<<",";
            bluefile<<endl;
        }
        bluefile.close();
        
        delete[] rpts;
        delete[] bpts;
    }
	
    
    
    return 0;
}




double s(vec& r, double& t, double& sigma, double& k, double& omega, double& phi)
{
    return(2.0*PI*sigma/k)*cos((k*r.norm())-(omega*t)+phi);
}

double gamma(double s, vec& r)
{
    return((s/r.norm())+1.);
}

vec rdt(double gamma, vec& r)
{
    return(gamma*r);
}

vec psi(vec& rp, double N, vec* rc, int* ti, int ii, double delt, double sigma, double k, double omega, double phi, bool &red)
{
    int Nc=0;
    double t;
    vec r,rsum;
    rsum();
    for(int i=0;i<N;i++)
    {
        r();
        r=rp-rc[i];
        t=(ii-ti[i])*delt;
        if (rul(r,t,k,omega)&&ii>=ti[i])
        {
            rsum+=(rdt(gamma(s(r,t,sigma,k,omega,phi),r),r)+rc[i]);
            Nc++;
        }
    }
    if(rsum.zero()) rsum=rp;
    else
    {
        rsum-=((Nc-1)*rp);
        red=true;
    }
    return(rsum);
}

bool rul(vec& r, double t, double k, double omega)
{
    double d,dd,delta;
    delta=0.5;
    d=(omega*t)/k;
    dd=(2*PI*delta)/k;
    return((r.norm()>=(d-dd))&&(r.norm()<=(d+dd)));
}

int sum(int *a, int n)
{
    int sum=0;
    for(int i=0;i<n;i++)
    {
        sum+=a[i];
    }
    return(sum);
}


/*--------------------------------------------------------------------------*/
float ran3(int *idum)
//int *idum;
{
	static int inext,inextp;
	static long ma[56];
	static int iff=0;
	long mj,mk;
	int i,ii,k;

	if (*idum < 0 || iff == 0) {
		iff=1;
		mj=MSEED-(*idum < 0 ? -*idum : *idum);
		mj %= MBIG;
		ma[55]=mj;
		mk=1;
		for (i=1;i<=54;i++) {
			ii=(21*i) % 55;
			ma[ii]=mk;
			mk=mj-mk;
			if (mk < MZ) mk += MBIG;
			mj=ma[ii];
		}
		for (k=1;k<=4;k++)
			for (i=1;i<=55;i++) {
				ma[i] -= ma[1+(i+30) % 55];
				if (ma[i] < MZ) ma[i] += MBIG;
			}
		inext=0;
		inextp=31;
		*idum=1;
	}
	if (++inext == 56) inext=1;
	if (++inextp == 56) inextp=1;
	mj=ma[inext]-ma[inextp];
	if (mj < MZ) mj += MBIG;
	ma[inext]=mj;
	return mj*FAC;
}

#undef PI
#undef MBIG
#undef MSEED
#undef MZ
#undef FAC

