#include<iostream>

using namespace std;

int al,bl,len,a[507],b[507],c[507];




int main()
{
    //freopen("data.in","r",stdin);
    string A,B;
    cin>>A>>B;
    al = A.length(), bl = B.length();
    len = max(al,bl);
    for(int i=0;i<al;++i) a[al-i-1] = A[i]-'0';
    for(int i=0;i<bl;++i) b[bl-i-1] = B[i]-'0';
    for(int i=0;i<len;++i) 
    {
        c[i] += a[i]+b[i];
        if(c[i]>9) c[i]%=10,c[i+1]++;
    }
    if(c[len]) len++;
    for(int i=len-1;~i;i--)cout<<c[i];



    return 0;
}