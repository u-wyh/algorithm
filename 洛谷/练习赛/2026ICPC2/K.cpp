#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e3+5;
const int MAXM = 5e5+5;

int n,m;
int val[MAXN];
int query[MAXM];
int ans[MAXM];

map<int,bool>exist;
map<int,int>result;

int cnt[MAXN];

void compute(int k){
    int limit=min(5000,n);
    for(int i=0;i<=limit;i++){
        cnt[i]=0;
    }
    for(int i=1;i<=n;i++){
        int v=val[i];
        if(0<=v&&v<=limit){
            cnt[v]++;
        }
        else if((k-limit)<=v&&v<=k){
            cnt[k-v]++;
        }
    }
    int ans=0;
    for(int i=0;i<=limit+1;i++){
        if(cnt[i]){
            cnt[i]--;
        }
        else if(k-i>=0&&(k-i)<=limit){
            if(cnt[k-i]){
                cnt[k-i]--;
            }
            else{
                ans=i;
                break;
            }
        }
        else{
            ans=i;
            break;
        }
    }
    result[k]=ans;
}

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    cin>>m;

    exist.clear();
    result.clear();
    for(int i=1;i<=m;i++){
        cin>>query[i];
        exist[query[i]]=true;
    }

    sort(val+1,val+n+1);
    int initans=0;
    for(int i=1;i<=n;i++){
        if(val[i]!=initans){
            continue;
        }
        else{
            initans++;
        }
    }
    for(int i=1;i<=m;i++){
        ans[i]=initans;
    }

    for(int i=1;i<=n;i++){
        if(val[i]!=val[i-1]){
            if(exist[val[i]+initans]){
                compute(val[i]+initans);
            }
        }
    }

    for(int i=1;i<=m;i++){
        int x=result[query[i]];
        if(x){
            ans[i]=x;
        }
    }

    int res=0;
    for(int i=1;i<=m;i++){
        res^=ans[i];
    }
    cout<<res<<endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int T;
    cin>>T;
    val[0]=-1;
    while(T--){
        solve();
    }
    return 0;
}
/*
2
3
0 1 3
3
1
2
5
9
0 0 1 1 2 3 3 4 5
7
4
5
6
7
8
9
10
*/