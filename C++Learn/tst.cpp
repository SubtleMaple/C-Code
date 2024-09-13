#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;++i)

void the_def_of_lambda()
{
    [捕获列表] (参数列表) -> 返回类型 {
        函数体
    };
    /*
    捕获列表（[]）：定义了 lambda 可以访问的外部变量，通常用于在 lambda 表达式中捕获作用域外的变量。

    参数列表（()）：类似于普通函数的参数列表，用来指定 lambda 的参数。

    返回类型（->）：用来指定 lambda 表达式的返回类型（可选）。如果省略，编译器会自动推导返回类型。

    函数体（{}）：实际的函数执行代码。
    */

}


void work1()
{
    int a = 0;
    //auto f = []() { return a * 9; };   // Error, 无法访问 'a'
    //auto f = [a]() { return a * 9; };  // OK, 'a' 被值「捕获」
    auto f = [&a]() { return a++; };   // OK, 'a' 被引用「捕获」
                                    // 注意：请保证 Lambda 被调用时 a 没有被销毁
    auto b = f();  // f 从捕获列表里获得 a 的值，无需通过参数传入 a

    cout<<b<<'\n';
}

void work2()
{
    auto lam = [](int a, int b) { return a + b; };
    std::cout << lam(1, 9) << " " << lam(2, 6) << std::endl;
}

void work3()
{
    int x[] = {5, 1, 7, 6, 1, 4, 2};
    std::sort(x, x + 7, [](int a, int b) { return (a > b); });
    for (auto i : x) std::cout << i << " ";
}

void work3()
{
    int x = 10;
    auto lam = [x](int a){return a+x;}; // [x]按值捕获，[&x]按引用捕获，[=]按值捕获所有外部变量
                                        // [&]按引用捕获所有外部变量
    int ans = lam(5);
}

void work4()
{
    int x = 5;
    int y = 10;

    auto lambda1 = [=]() {
        return x + y;  // 按值捕获，lambda 内的 x 和 y 是捕获时的副本
    };  

    auto lambda2 = [&]() {
        x = 20;  // 按引用捕获，lambda 内的 x 是外部的 x，修改会影响外部的 x
        return x + y;
    };

    int result1 = lambda1();  // result1 = 15
    int result2 = lambda2();  // result2 = 30，x 被修改为 20

}

/*可变（mutable）lambda 表达式
默认情况下，按值捕获的 lambda 表达式中的捕获变量是不可修改的。
如果想在 lambda 内修改按值捕获的变量，可以使用 mutable 关键字。*/

void work5()
{
    //在这个例子中，mutable 使得 lambda 内部可以修改 x
    //，但这仅影响 lambda 内部的副本，外部的 x 不受影响。
    int x = 10;

    auto lambda = [x]() mutable {
        x += 5;  // 允许修改按值捕  获的变量 x
        return x;
    };

    int result = lambda();  // result = 15，但外部的 x 不变，仍然是 10

}

void work5()
{
    //返回类型推导
    //如果 lambda 表达式的返回类型比较复杂或者需要显式指定返回类型，可以使用 -> 来指定返回类型。
    auto lambda = [](int a, int b) -> double {
        return static_cast<double>(a) / b;
    }; //static_cast<target-type >(expression )	Returns a value of type target-type.

    double result = lambda(10, 3);  // result = 3.33333

}

void work6()
{
    //泛型 lambda（C++14 引入）
    //C++14 引入了泛型 lambda，允许使用 auto 来声明参数类型，从而使 lambda 具备泛型功能。
    auto lam = [](auto a,auto b){
        return a+b;
    };
    int ans = lam(1,2);
    double ans2 = lam(1.1,2.3);
}

void work7()
{
    //Lambda 表达式的用途
    //Lambda 表达式在 C++ 中有多种用途，特别是在需要传递短小的函数对象的场景中非常有用，例如：
    //用于标准算法：可以用 lambda 表达式作为参数传递给 std::sort, std::for_each 等标准算法。
    vector<int> vec = {4,5,2,3,1};      
    sort(vec.begin(),vec.end(),[](int a,int b){return a>b;});
}


int main()
{
    

    

    

    return 0;
}