#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)

class people
{
    private:
    string nam;
    int ht,wt,age;

    public:
    people(string nam,int ht,int wt,int age):nam(nam),ht(ht),wt(wt),age(age){}
    void output()
    {
        cout<<nam<<": "<<ht<<' '<<wt<<' '<<age<<'\n';
    }
};

class student : public people // people 中可外部调用元素在 student 中作为 public 使用
{
    private:
    int cls,id;
    public:
    student(int cls,int id,string nam,int ht,int wt,int age):cls(cls),id(id),people(nam,ht,wt,age){}
    void output()
    {
        cout<<cls<<' '<<id<<'\n';
    }

};

int main()
{
    student swh(4,18,"swh",175,75,18);
    swh.people::output();//调用基类中的函数
    swh.output();
    return 0;
}