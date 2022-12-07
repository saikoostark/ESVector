#include "ESVector.h"

int main() {
    ESVector<int> v{1,2,3,4,5,6,7,8,9};
    cout << v << endl;
    v.push_back(4);
    cout << v << endl;
    v.push_back(4);
    cout << v << endl;
    v.clear();
    cout << v << endl;
    ESVector<int> t=v;
cout<<boolalpha<<(v==t);


}
