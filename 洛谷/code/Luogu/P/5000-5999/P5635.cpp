#include<bits/stdc++.h>
using namespace std;

int t,mod,x,y;
short book[10005][10005];

int fun(int x,int y){
    if(book[x][y]==-1)
        return -1;
    if(book[x][y])
        return book[x][y];
    book[x][y]=-1;
    if(!x){
        book[x][y]=1;
        return 1;
    }
    if(!y){
        book[x][y]=2;
        return 2;
    }
    int num=(x+y)%mod;
    book[x][y]=fun(num,(num+y)%mod);
    return book[x][y];
}

int main()
{
    cin>>t>>mod;
    while(t--){
        cin>>x>>y;
        int ans=fun(x,y);
        if(ans==-1){
            cout<<"error"<<endl;
        }else
            cout<<book[x][y]<<endl;
    }
    return 0;
}
