#include<iostream>
#include<cmath>
using namespace std;

const double pi = cos(-1);
const int N = 1e6+7;

struct complex{
	double r,i;
	complex(double r=0,double i=0): r(r),i(i){}
	complex operator+(complex others){
		return complex(r+others.r,i+others.i);
	}
	complex operator-(complex others){
		return complex(r-others.r,i-others.i);
	}
	complex operator*(complex others){
		return complex(r*others.r-i*others.i,r*others.i+i*others.r);
	}
	friend complex operator*(complex x,double y){
		return complex(y*x.r,y*x.i);
	}
	friend complex operator*(double y,complex x){
		return complex(y*x.r,y*x.i);
	}
};

void FFT(int lim,complex *a,int type)
{
	if(lim == 1) return;
	complex a1[lim>>1],a2[lim>>1];
	for(int i=0;i<lim;i+=2)
		a1[i>>1] = a[i], a2[i>>1] = a[i+1];
	FFT(lim>>1,a1,type);
	FFT(lim>>1,a2,type);
	complex Wn = complex(cos(2*pi/lim),type*sin(2*pi/lim)),w = complex(1,0);
	for(int i = 0; i < (lim >> 1); ++i,w = w * Wn)
	{
		a[i] = a1[i] + w*a2[i];
		a[i+(lim>>1)] = a1[i] - w*a2[i];
	}
}

complex a[N],b[N];
int n,m;

int main()
{
	cin>>n>>m;
	for(int i=0;i<n;++i) cin>>a[i].r;
	for(int i=0;i<m;++i) cin>>b[i].r;
	int lim=1; while(lim <= (n+m)) lim <<= 1;
	FFT(lim,a,1);
	FFT(lim,b,1);
	for(int i=0;i<lim;++i) a[i] = a[i]*b[i];
	FFT(lim,a,-1);
	
}