#include <iostream>

// 虚基类
class Base {
public:
    Base() { std::cout << "Base constructor called.\n"; }
    virtual ~Base() { std::cout << "Base destructor called.\n"; }
    void show() { std::cout << "Base show\n"; }
};

// 中间类
class Derived1 : virtual public Base {//virtual 保证菱形继承结构中祖父的实例不会被重复继承
public:
    Derived1() { std::cout << "Derived1 constructor called.\n"; }
    ~Derived1() { std::cout << "Derived1 destructor called.\n"; }
    void show() { std::cout << "Derived1 show\n"; }
};

class Derived2 : virtual public Base {
public:
    Derived2() { std::cout << "Derived2 constructor called.\n"; }
    ~Derived2() { std::cout << "Derived2 destructor called.\n"; }
    void show() { std::cout << "Derived2 show\n"; }
};

// 最终派生类
class MostDerived : public Derived1, public Derived2 {
public:
    MostDerived() { std::cout << "MostDerived constructor called.\n"; }
    ~MostDerived() { std::cout << "MostDerived destructor called.\n"; }
    void show() {
        Base::show();
        Derived1::show();
        Derived2::show();
    }
};

namespace virtue_constructor
{
    class Base {
    public:
        Base(int x) {
            // 构造函数的实现
        }
    };

    class Derived1 : virtual public Base {
    public:
        Derived1(int x) : Base(x) {
            // 调用虚基类的构造函数
        }
    };

    class Derived2 : virtual public Base {
    public:
        Derived2(int x) : Base(x) {
            // 调用虚基类的构造函数
        }
    };

    class MostDerived : public Derived1, public Derived2 {
    public:
    //放在初始化列表的部分在构造函数之前执行
        MostDerived(int x) : Base(x), Derived2(x), Derived1(x) { // 基类的构造函数通过子类的初始化列表调用
            // 调用虚基类的构造函数
        }
    };
    /*
    间接基类也要写虚基类的构造函数，但实际上只在最终类里使用一次
    */
}

int main() {
    MostDerived obj;
    obj.show();
    return 0;
}