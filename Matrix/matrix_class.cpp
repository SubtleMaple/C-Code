#include<iostream>
#include<vector>
#include<cassert>
#include<cmath>

using namespace std;

const double eps = 1e-8;

class Matrix
{
public:
	int n,m;
	vector<vector<double>> data;

	Matrix(int _m,int _n) {
		m = _m;
		n = _n;
		data.resize(m);
		for(int i = 0; i < m; ++i) data[i].resize(n,0);
	}

	Matrix() {
		m = n = 0;
	}

	void print()
	{
		for(int i = 0; i < m; ++i)
		{
			for(int j=0; j < n; ++j)
			{
				cout<<(abs(data[i][j]) < eps ? 0 : data[i][j])<<" \n"[j==n-1];
			}
		}
	}

	vector<double>& operator[](int i) {
	    return data[i];
	}

	const vector<double>& operator[](int i) const {
	    return data[i];
	}

	friend Matrix operator*(const Matrix& A,const Matrix& B) {
		assert(A.n == B.m);
		Matrix res(A.m,B.n);
		for(int i = 0; i < A.m; ++i) {
			for(int k = 0; k < A.n; ++k) {
				for(int j = 0; j < B.n; ++j)
				{
					res[i][j] += A[i][k] * B[k][j];
				}
			}
		}
		return res;
	}

	friend Matrix operator*(const Matrix& A, double k)
	{
		Matrix res = A;
		for(int i = 0; i < A.m; ++i) for(int j = 0; j < A.n; ++j) res[i][j] *= k;
		return res;
	}

	friend Matrix operator*(double k,const Matrix& A)
	{
		Matrix res = A;
		for(int i = 0; i < A.m; ++i) for(int j = 0; j < A.n; ++j) res[i][j] *= k;
		return res;
	}

	friend Matrix operator+(const Matrix& A,const Matrix& B) {
		assert(A.m == B.m && A.n == B.n);
		Matrix res(A.m,A.n);
		for(int i=0;i<A.m;++i) for(int j=0;j<A.n;++j) res[i][j] = A[i][j] + B[i][j];
		return res;
	}
	friend Matrix operator-(const Matrix& A,const Matrix& B) {
		assert(A.m == B.m && A.n == B.n);
		Matrix res(A.m,A.n);
		for(int i=0;i<A.m;++i) for(int j=0;j<A.n;++j) res[i][j] = A[i][j] - B[i][j];
		return res;
	}

	friend vector<double> operator*(const Matrix& A,vector<double> vec)
	{
		assert(A.n == vec.size());
		vector<double> res(A.n,0);
		for(int i = 0; i < A.m; ++i)
			for(int k = 0; k < A.n; ++k)
				res[k] += A[i][k] * vec[k];
		return res;
	}
	// 交换两行
	void row_swap(int i,int j)
	{
		if (i < 0 || i >= m || j < 0 || j >= m) {
	        cerr << "swap index out of range!\n";
	        return;
	    }
		data[i].swap(data[j]);
	}
	// 交换两列
	void col_swap(int i,int j)
	{
		if (i < 0 || i >= n || j < 0 || j >= n) {
	        cerr << "swap index out of range!\n";
	        return;
	    }
	    for(int k = 0; k < m; ++k) swap(data[k][i],data[k][j]);
	}
	// 求转置
	Matrix Trans()
	{
		Matrix res(n,m);
		for(int i = 0; i < m; ++i) for(int j = 0; j < n; ++j) res[j][i] = data[i][j];
		return res;
	}
	// 取出第k行
	Matrix get_k_row(int k)
	{
		Matrix res(1,n);
		for(int i = 0; i < n; ++i) res[0][i] = data[k][i];
		return res;
	}
	// 取出第k列
	Matrix get_k_col(int k)
	{
		Matrix res(m,1);
		for(int i = 0; i < m; ++i) res[i][0] = data[i][k];
		return res;
	}

	// 某行乘k
	void k_row(double k,int i)
	{
		for(auto &x : data[i]) x *= k;
	}
	// 某列乘k
	void k_col(double k,int i)
	{
		for(int j = 0; j < m; ++j) data[j][i] *= k;
	}
	// x行加上k倍的y行
	void plus_k_row(int x,double k,int y)
	{
		for(int i = 0; i < n; ++i)
			data[x][i] += k * data[y][i];
	}
	// x列加上k倍的y列
	void plus_k_col(int x,double k,int y)
	{
		for(int i = 0; i < m; ++i)
			data[i][x] += k * data[i][y];
	}

	Matrix Inv()
	{
		assert(m == n);

		Matrix tmp = *this;

		Matrix res(m,n);for(int i = 0; i < m; ++i) res[i][i] = 1;

		for(int i = 0; i < m; ++i)
		{
			// 主元交换至当前行
			if(abs(tmp[i][i]) < eps) 
			{
				for(int j=i+1;j<m;++j) if(abs(tmp[j][i])>eps){
					res.row_swap(i,j); tmp.row_swap(i,j); break;
				}
				if(abs(tmp[i][i]) < eps){
					cerr<<"Row: "<<i<<" Can't be Inv!\n"; 
					tmp.print();
					exit(0);
				}
			}
			double div = tmp[i][i];
			res.k_row(1/div,i), tmp.k_row(1/div,i);
			for(int j = 0; j < m; ++j) if(j != i)
			{
				res.plus_k_row(j,-tmp[j][i],i);
				tmp.plus_k_row(j,-tmp[j][i],i);
			}
		}	
		return res;			
	}

	double Det()
	{
		Matrix tmp = *this;
		assert(tmp.m == tmp.n);
		double res = 1;
		for(int i = 0; i < m; ++i)
		{
			if(abs(tmp[i][i]) < eps) 
			{
				for(int j=i+1;j<m;++j) if(abs(tmp[j][i])>eps){
					res *= -1; tmp.row_swap(i,j); break;
				}
				if(abs(tmp[i][i]) < eps){
					// cerr<<"Row: "<<i<<" Can't be Inv!\n"; 
					// tmp.print();
					return 0;
				}
			}
			for(int j = i + 1; j < m; ++j)
			{
				tmp.plus_k_row(j,-tmp[j][i]/tmp[i][i],i);
			}
		}
		for(int i = 0; i < m; ++i) res *= tmp[i][i];
		return res;
	}
	// 幂方法求绝对值最大特征值
	double Max_Eigenvalue()
	{
		assert(m == n);
		Matrix A = *this;
		Matrix vec(m,1);
		for(int i = 0; i < m; ++i) vec[i][0] = 1.0;

		double eigenvalue = 0;
		for(int i = 0; i < 1000; ++i)
		{
			Matrix newvec = A * vec;
			double len = sqrt((newvec.Trans()*newvec)[0][0]);
			newvec.k_col(1/len,0);
			double neweigenvalue = (newvec.Trans() * A * newvec)[0][0];

			if(abs(neweigenvalue - eigenvalue) < eps) return eigenvalue;
			vec = newvec;
			eigenvalue = neweigenvalue;
		}
		return eigenvalue;
	}
	// 根据特征值性质，求出逆矩阵最大特征值，从而得出最小特征值
	double Min_Eigenvalue()
	{
		return 1.0/(this->Inv()).Max_Eigenvalue();
	}
	// 求QR分解的正交矩阵Q
	Matrix build_Q()
	{
		Matrix Q(m,n);
		for(int i = 0; i < n; ++i)
		{
			Matrix vec = this->get_k_col(i);
			for(int j = 0; j < i; ++j)
			{
				Matrix nwvec = Q.get_k_col(j);
				double tmp = ((nwvec.Trans() * vec)[0][0]) / ((nwvec.Trans() * nwvec)[0][0]);
				vec = vec - (tmp * nwvec);
			}
			double tmp = sqrt((vec.Trans() * vec)[0][0]);
			vec.k_col(1 / tmp,0);
			for(int k = 0; k < m; ++k) Q[k][i] = vec[k][0];
		}
		return Q;
	}
	// QR算法求解全部特征值
	Matrix QR_Algorithm()
	{
		assert(m == n);
		Matrix Lambda = *this;

		for(int i = 0; i < 1000; ++i)
		{
			Matrix Q = Lambda.build_Q();
			Matrix R = Q.Inv() * Lambda;
			Lambda = R * Q;
		}
		return Lambda;
	}

};

int main()
{
	int n,m; cin>>m>>n;
	Matrix tmp(m,n);
	for(int i = 0; i < m; ++i) for(int j = 0; j < n; ++j) cin>>tmp[i][j];
	tmp.print();
	cout<<tmp.Max_Eigenvalue()<<'\n';
	cout<<tmp.Min_Eigenvalue()<<'\n';
	tmp.QR_Algorithm().print();
	return 0;
}