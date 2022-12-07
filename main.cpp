#include "ESVector.hpp"
#include<iostream>
#include<vector>
using namespace std;

int main(){


//vector<int> x = {4, 4 , 7 , 1 };

//auto g = x.begin() - 20;
//cout<< x.capacity()<<endl;
//x.insert(g , 5);
//cout<< x.capacity()<<endl;
//for(auto h : x)
//cout <<h << " ";
//cout<<endl;

#if 1
ESVector<int> x = {77 ,4 ,8};
cout<< x << endl;
x[1] = 22;
//cout<< *x.begin();
ESVector<int> y(2);
y = x ;
//y[4] = 3453;
//for(auto it = x.begin() ; it != x.end() ; it++)
//cout<< *it << " ";
//cout<< endl;

ESVector<int>::iterator ite = y.begin() + 6;

for(auto it = y.begin(); it != y.end() ; it++)
cout<< *it << " ";
cout<< endl;

cout<< y.size() << " " << y.capacity()<<endl;
y.insert(ite , 444);
cout<< y.size() << " " << y.capacity()<<endl;
for(auto it = y.begin(); it != y.end() ; it++)
cout<< *it << " ";
cout<< endl;
#endif
}