#include<bits/stdc++.h>
using namespace std;
const int MAXN = 50010;

int n,q,h[MAXN],log_2[MAXN],rmax[MAXN][18],rmin[MAXN][18];

void init(){
    for(int i=1;i<=n;i++)
        rmax[i][0]=rmin[i][0]=h[i];
    for(int j=1;(1<<j)<=n;j++){
        for(int i=1;i<=n-(1<<j)+1;i++){
            rmax[i][j]=max(rmax[i][j-1],rmax[i+(1<<j-1)][j-1]);
            rmin[i][j]=min(rmin[i][j-1],rmin[i+(1<<j-1)][j-1]);
        }
    }
}

int query_max(int A,int B){
    int x=log_2[B-A+1];
    return max(rmax[A][x],rmax[B-(1<<x)+1][x]);
}

int query_min(int A,int B){
    int x=log_2[B-A+1];
    return min(rmin[A][x],rmin[B-(1<<x)+1][x]);
}

int main()
{
    cin>>n>>q;
    for(int i=1;i<=n;i++)
        cin>>h[i];
    for(int i=2;i<=n;i++)
        log_2[i]=log_2[i>>1]+1;
    init();
    while(q--){
        int A,B;
        cin>>A>>B;
        cout<<query_max(A,B)-query_min(A,B)<<endl;
    }
    return 0;
}
