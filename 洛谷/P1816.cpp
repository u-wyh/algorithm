#include<bits/stdc++.h>
using namespace std;
const int MAXN = 350005;
const int LIMIT = 17;

int n,m;
int st[MAXN][LIMIT];
int Log2[MAXN],arr[MAXN];

void build(int n){
    Log2[0]=-1;
    for(int i=1;i<=n;i++){
        Log2[i]=Log2[i>>1]+1;
        st[i][0]=arr[i];
    }
    for(int p=1;p<=Log2[n];p++){
        for(int i=1;i<=n;i++){
            st[i][p]=min(st[i][p-1],st[i+(1<<(p-1))][p-1]);
        }
    }
}

int query(int l,int r){
    int p=Log2[r-l+1];
    return min(st[l][p],st[r-(1<<p)+1][p]);
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>arr[i];
    build(n);
    while(m--){
        int l,r;
        cin>>l>>r;
        cout<<query(l,r)<<' ';
    }
    return 0;
}
