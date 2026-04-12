#include<bits/stdc++.h>
using namespace std;

bool vis[10];
int cnt;

bool query(int x,int n){
    vis[x%10]=true;
    vis[(x/10)%10]=true;
    vis[(x/100)%10]=true;
    vis[(x/1000)%10]=true;
    for(int i=0;i<10;i++){
        if(vis[i]){
            cnt++;
            vis[i]=false;
        }
    }
    return cnt==n;
}

int main()
{
    int x,y;
    cin>>x>>y;
    for(int i=0;i<=2000;i++){
        cnt=0;
        if(query(x+i,y)){
            cout<<i<<' ';
            cout<<(x+i)/1000<<((x+i)/100)%10<<((x+i)/10)%10<<(x+i)%10;
            break;
        }
    }
    return 0;
}