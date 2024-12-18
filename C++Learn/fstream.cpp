#include<iostream>
#include<fstream>

using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)
int main()
{
    ofstream outfile;
    outfile.open("data.out");
    rep(i,1,100) outfile<<i<<' ';
    outfile.close();
    return 0;
}