// https://www.luogu.com.cn/problem/P10507
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;

int n;
int pos[MAXN];
int dis[MAXN];

int main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>pos[i];
        }
        sort(pos+1,pos+n+1);
        int pre=0;
        for(int i=1;i<=n;i++){
            dis[i]=pos[i]-pre-1;
            pre=pos[i];
        }
        int eor=0;
        for(int i=n;i>=1;i-=2){
            eor^=dis[i];
        }
        if(eor){
            cout<<"Georgia will win"<<endl;
        }
        else{
            cout<<"Bob will win"<<endl;
        }
    }
    return 0;
}