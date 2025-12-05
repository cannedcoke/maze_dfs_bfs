#include <deque>
#include <utility>
#include <iostream>

using namespace std;

int main(){

    deque<pair<int,int>> q;
    
    q.push_back({5,7});
    q.push_back({10,3});

    pair<int,int> p = q.front();

    cout << p.first << " " << p.second << endl;

    q.pop_front();

    p = q.front();

    cout << p.first << " " << p.second << endl;

}