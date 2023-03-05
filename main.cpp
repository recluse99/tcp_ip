//
// Created by root on 23-3-2.
//
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

template<class T>
void my_print(T &list) {

    for (auto &a: list) {
        cout << a << " " << endl;
    }

    cout<<"end ...."<<endl;

}

void test01() {

    vector<int> ve;
    ve.push_back(2);
    ve.push_back(5);
    ve.push_back(7);

    my_print<vector<int>>(ve);


    unordered_set<int> un_set;

    un_set.insert(5);

    my_print<unordered_set<int>>(un_set);


    cout << "run ... test01()" << endl;
}

int main() {

    cout << "hello,world" << endl;

    test01();

    return 0;
}