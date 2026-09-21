// https://www.luogu.com.cn/problem/P3480
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;

int n;
int val[MAXN];
int diff[MAXN];

int main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>val[i];
            diff[i]=val[i]-val[i-1];
        }
        int eor=0;
        for(int i=n;i>=1;i-=2){
            eor^=diff[i];
        }
        if(eor){
            cout<<"TAK"<<endl;
        }
        else{
            cout<<"NIE"<<endl;
        }
    }
    return 0;
}