#include <iostream>
#include <string>
using namespace std;

class Animal {
public:
    // 类的成员变量的内置类型 不会默认初始化。会得到一个不确定的值
    int age;
    string name;

    Animal() = default;
    Animal(int age, string name)
        : age(age)
        , name(name)
    {
        cout << "use animal construct" << endl;
    }

    // 只有定义为虚函数 ，才能被重写
    virtual void tostring()
    {
        cout << "use animal" << endl;
    }

    void test()
    {
        cout << "ani.." << endl;
    }
};

class Dog : public Animal {
public:
    string move;
    int age;

    Dog() = default;
    Dog(int age, string name, string move)
        : Animal(age, name)
        , move(move)
        , age(age)
    {
    }

    void tostring() override
    {
        cout << "use dog ..." << endl;
    }
    void test()
    {
        cout << "do..." << endl;
    }
};

// 只有全局变量 内置类型会有默认初始值
int number;

int main(int argc, char* argv[])
{
    Dog dd(5, "gg", "run");
    Animal a;
    cout << a.age << " 1" << a.name << "2" << endl;

    dd.test();

    // 子类调用父类的方法
    dd.Animal::test();

    a.test();
    // Dog dd;

    // dd.age = 19;
    cout << dd.age << endl;

    // cout << dd.Animal::age << endl;

    Animal& an = dd;

    an.test();

    

    // cout<<dd.age<<" 1 "<<dd.name<<" 2 "<<dd.move<<endl;

    // an.tostring();

    // cout << an.age << " " << an.name << endl;
    // cout << an.age << " " << an.name << endl;

    return 0;
}