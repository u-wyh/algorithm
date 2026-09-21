// https://www.luogu.com.cn/problem/P1290
#include<bits/stdc++.h>
using namespace std;

bool check(int a,int b){
    if(a<b){
        swap(a,b);
    }
    if(a%b==0){
        return true;
    }
    if(a>2*b){
        return true;
    }
    return !check(b,a-b);
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        int a,b;
        cin>>a>>b;
        if(check(a,b)){
            cout<<"Stan wins"<<endl;
        }
        else{
            cout<<"Ollie wins"<<endl;
        }
    }
    return 0;
}