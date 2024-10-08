#include<iostream>
#include<string>
#include<vector>

using namespace std;

class student
{
	int score,ht,wt;
	string nam;
	public:	
	student(int a,int b,int c):score(a),ht(b),wt(c){}

	~student()
	{
		cout<<"Over and Over\n";
	}

	student & operator=(const student& s)
	{
		score = s.score;
		ht = s.ht;
		wt = s.wt;
		return *this;
	}
	void output()
	{
		cout<<score<<' '<<ht<<' '<<wt<<'\n';
	}
};

class complex
{
	double r,i;
	public: // 务必注意public，否则类外无法调用类的任何内容
	complex(double _r,double _i){r=_r,i=_i;}
	complex(){r=0,i=0;}
	~complex(){}
	complex operator+(complex x)
	{
		return complex(r+x.r,i+x.i);
	}
	complex operator-(complex x)
	{
		return complex(r-x.r,i-x.i);
	}
	complex operator*(complex x)
	{
		complex tmp;
		tmp.r = r*x.r -i*x.i;
		tmp.i = r*x.i+i*x.r;
		return tmp;
	}
	friend complex operator*(const int& c,const complex& x)
	{
		return complex(c*x.r,c*x.i);
	}
	friend complex operator*(const complex& x,const int& c)
	{
		return complex(c*x.r,c*x.i);
	}
	complex operator/(complex x)
	{
		complex tmp;
		tmp.r = (r*x.r+i*x.i)/(x.r*x.r+x.i*x.i);
		tmp.i = (i*x.r-r*x.i)/(x.r*x.r+x.i*x.i);
		return tmp;
	}
	void output()
	{
		cout<<r<<' '<<i<<'\n';
	}

	complex& operator=(const complex& x)
	{
		r=x.r,i=x.i;
		return *this;
	}

	complex& operator++() // 前++返回值是对原变量的引用，使用原变量本身
	{
		r++;
		return *this;
	}
	complex operator++(int) // 后++返回值是++前的值，故使用临时变量储存原值，++后返回原值，是值传递
	{
		complex tmp = *this;
		r++;
		return tmp;
	}

};


class matrix
{
	private:
	int n,m;

	public:
	vector<vector<int> > data;

	matrix(int _m,int _n):n(_n),m(_m),data(m,vector<int>(n,0)){}

	void input()
	{
		for(int i=0;i<m;++i) for(int j=0;j<n;++j) cin>>data[i][j];
	}

	void output()
	{
		for(int i=0;i<m;++i)
		{
			for(int j=0;j<n;++j)
			{
				cout<<data[i][j]<<' ';
			}
			cout<<'\n';
		}
	}

	matrix operator+(const matrix& b)
	{
		if(n!=b.n || m!=b.m)
		{
			throw invalid_argument("Matrix A and B must be in the same size");
		}
		matrix tmp(m,n);
		for(int i=0;i<m;++i) for(int j=0;j<n;++j) tmp.data[i][j] = data[i][j] + b.data[i][j];
		return tmp;
	}

	matrix operator*(const matrix& b)
	{
		if(n != b.m) {
			throw invalid_argument("Matrix A's columns must equal Matrix B's rows.");
		}
		matrix tmp(m,b.n);
		for(int i=0;i<m;++i)
		{
			for(int k=0;k<min(n,b.m);k++)
			{
				for(int j=0;j<b.n;++j)
				{
					tmp.data[i][j] += data[i][k]*b.data[k][j];
				}
			}
		}
		return tmp;
	}

	friend matrix operator*(const int& c,const matrix& b)
	{
		matrix tmp(b.m,b.n);
		for(int i=0;i<b.m;++i) for(int j=0;j<b.n;++j)
			tmp.data[i][j] = b.data[i][j]*c;
		return tmp;
	}


};

void workstu()
{
	cout<<"Stu:\n";
	student swh(1,2,3);
	student swf(8,9,10);
	swh.output();
	swf.output();
	(swh=swf).output();
}

void workcomplex()
{
	cout<<"complex:\n";
	complex a(1,2);
	complex b(3,4);
	(a*b).output();
	(a+b).output();
	(a-b).output();
	(b/a).output();
	(2*a).output();
	(a*100).output();
	a = b;
	a.output();
	(++a).output();
	(a++).output();
	a.output();
}

void workmatrix()
{
	matrix a(2,2),b(2,2);
	a.input(),b.input();
	a.output(),b.output();
	(a+b).output();
	(a*b).output();

}

int main()
{
	workmatrix();
	

	return 0;
}
