#include<iostream>

using namespace std;

class vehicle
{
    public:
    virtual void message(){cout<<"Vehicle\n";}//设置为虚函数
    /*
    virtual void run()=0; 
    // 纯虚函数，在基类中只定义存在，留给派生类实现功能,除了在基类中毫无作用外与虚函数用法一样
    //使用虚函数的类为抽象类，抽象类不可用于生成对象
    */
    virtual ~vehicle() // 虚析构函数，基类设置为虚后，所有派生类析构函数都变为虚函数
    {
        cout<<"vehicle delete\n";
    }
    private:
    int wheels;
};

class car : public vehicle
{
    public:
    void message(){cout<<"Car\n";}
    void run()
    {
        cout<<"start\n";
    }
    ~car(){cout<<"Car delete\n";}
};


int main()
{
    vehicle * ptr;
    ptr = new vehicle();
    ptr->message();
    ptr = new car();
    ptr->message(); // 基类中使用虚函数后，基类指针 指向继承类后可以调用继承类中与基类同名的不同函数
    delete ptr; // 使用了虚析构函数，故用 delete 删除对象后先执行派生类的析构函数；
                // 若不使用虚析构函数，则 delete 后由于静态关联，只执行基类的析构函数
    return 0;
}
