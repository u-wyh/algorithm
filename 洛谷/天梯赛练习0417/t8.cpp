#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m,k;
struct node{
    int a,b;
}nums[MAXN];
int cnt[300];

int main()
{
    cin>>n>>m>>k;
    int tmp=0;
    for(int i=1;i<=n;i++){
        int a,b;
        cin>>a>>b;
        if(a<175){
            tmp++;
            continue;
        }
        if(b<k){
            cnt[a]++;
        }
    }
    // cout<<tmp<<endl;
    for(int i=175;i<=290;i++){
        if(cnt[i]>m){
            tmp+=(cnt[i]-m);
        }
    }
    // cout<<tmp<<endl;
    cout<<(n-tmp)<<endl;
    return 0;
}