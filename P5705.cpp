#include<iostream>

using namespace std;

int main()
{
    double x;
    cin >> x;
    int y = (int)(x*10);
    cout<< y%10;
    y/=10;
    cout<<'.';
    while(y)
    {
        cout<< y%10;
        y/=10;
    }

    return 0;
}