#include<iostream>
#include<cmath>

using namespace std;

const int N = 2100007;
const double pi = acos(-1);

struct complex{
	double r,i;
	complex(double r=0,double i=0):r(r),i(i){}
};
complex operator + (complex x,complex y){
	return complex(x.r+y.r,x.i+y.i);
}
complex operator - (complex x,complex y){
	return complex(x.r-y.r,x.i-y.i);
}
complex operator * (complex x,complex y){
	return complex(x.r*y.r-x.i*y.i,x.r*y.i+x.i*y.r);
}

complex a[N],b[N];

int len=1; 	
int lim=1;

// void FFT(int lim,complex *a,int type)
// {
// 	if(lim==1) return;
// 	complex a1[lim>>1],a2[lim>>1];
// 	for(int i=0;i<lim;i+=2)
// 		a1[i>>1] = a[i], a2[i>>1] = a[i+1];
	
// 	FFT(lim>>1,a1,type), FFT(lim>>1,a2,type);
	
// 	complex wn = complex(cos(2*pi/lim),type*sin(2*pi/lim));
// 	complex w = complex(1,0);
	
// 	for(int i=0; i < (lim>>1); ++i,w = w * wn)
// 	{
// 		complex tmp = w * a2[i];
// 		a[i] = a1[i] + tmp;
// 		a[i+lim/2] = a1[i] - tmp;
// 	}
// }

int rk[N];

void FFT(complex *a,int type)
{
	for(int i=0;i<lim;++i)
		if(i < rk[i]) swap(a[i],a[rk[i]]);
	for(int mid = 1; mid < lim; mid <<= 1)
	{
		complex wn = complex(cos(2*pi/mid),type*sin(2*pi/mid));
		for(int i=0;i<lim;i+=(mid<<1))
		{
			complex w = complex(1,0);
			for(int j=0;j<mid;++j,w = w * wn)
			{
				complex x = a[i+j], y = w * a[i+j+mid];
				a[i+j] = x + y;
				a[i+j+mid] = x - y;
				
			}
		}
	}
}



signed main()
{
	int n,m;
	cin>>n>>m;
	for(int i=0;i<=n;++i) cin>>a[i].r; //n+1 
	for(int i=0;i<=m;++i) cin>>b[i].r; // m+1
	 while(lim<=n+m) lim<<=1,len++;

	for(int i=0;i<lim;++i)
		rk[i] = (rk[i/2]>>1) | ((i&1)<<(len-1));


	///FFT(lim,a,1), FFT(lim,b,1);
	FFT(a,1), FFT(b,1);
	
	for(int i=0;i<lim;++i) a[i] = a[i]*b[i];
	
	//FFT(lim,a,-1);
	FFT(a,-1);
	
	for(int i=0;i<=n+m;++i) cout<<(int)(a[i].r/lim+0.5)<<' ';
	
	
	return 0;
 } 