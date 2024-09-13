#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)

const double pi = 3.14159;

class Circle
{
    //访问权限
    public:
    //属性
    int r;
    //行为
    double Cal_c(){
        return 2*pi*r;
    }
};


int main()
{
    Circle c1;
    c1.r = 1;
    cout<<c1.Cal_c();
    return 0;
}