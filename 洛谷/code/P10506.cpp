#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;

int n;
int sg[MAXN];
bool appear[MAXN];

void build(){
    sg[1]=0;
    for (int i = 2; i <= 1000; i++) {
        int k=0;
        memset(appear, false, sizeof(appear)); // 重置 appear 数组
        for (int j = 1; j <= i/2; j++) {
            if(i%j==0){
                k^=sg[j];
            }
        }
        for (int j = 1; j <= i/2; j++) {
            if(i%j==0){
                appear[k^sg[j]]=1;
            }
        }
        for (int s = 0; s < MAXN; s++) {
            if (!appear[s]) {
                sg[i] = s; // 找到最小的未出现的 SG 值
                break;
            }
        }
        //cout<<i<<": "<<sg[i]<<endl;
    }
}

int main()
{
    build();
    while(cin>>n){
        int ans=0;
        for(int i=1;i<=n;i++){
            int u;
            cin>>u;
            ans^=sg[u];
        }
        if(ans){
            cout<<"freda"<<endl;
        }
        else{
            cout<<"rainbow"<<endl;
        }
    }
    return 0;
}
