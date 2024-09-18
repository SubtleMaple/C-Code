#include<iostream>

using namespace std;

void ck(int x,int y,int z)
{
    bool vis[11] = {0};
    int a[3];
    a[0] = x*100+y*10+z;
    a[1] = 2*a[0], a[2] = a[0]*3;
    if(a[1]>999 || a[2]>999) return;
    for(int i=0;i<=2;i++)
    {
        int p = a[i];
        for(int j=1;j<=3;j++)
        {
            int tmp = p%10;
            if(tmp==0) return;
            if(vis[tmp]) return;
            vis[tmp] = 1;
            p /= 10;
        }
    }
    cout<<a[0]<<' '<<a[1]<<' '<<a[2]<<"\n";
}

int main()
{
    for(int i=1;i<=9;i++)
    {
        for(int j=1;j<=9;j++) if(j!=i)
        {
            for(int k=1;k<=9;k++) if(k!=i && k!=j)
            {
                ck(i,j,k);
            }
        }
    }


    return 0;
}