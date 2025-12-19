#include<bits/stdc++.h>
using namespace std;
const int MAXN = 31;

int n;
int arr[MAXN];
int cnt;
int val[MAXN];

void dfs(int u){
    if(2*u<=n){
        dfs(2*u);
    }
    if(2*u+1<=n){
        dfs(2*u+1);
    }
    val[u]=arr[++cnt];
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    dfs(1);
    for(int i=1;i<n;i++){
        cout<<val[i]<<' ';
    }
    cout<<val[n];
    return 0;
}