#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;
const int MAXH = 20;

int n,m,k;
int p;

int val[MAXN];
int pre[MAXN];
int f[MAXN];

int up[MAXH][MAXN];
int sum[MAXH][MAXN];

set<pair<long long,int>>st;

int MOD(int x){
    x%=k;
    if(x<0){
        x+=k;
    }
    return x;
}

void compute(int l,int r,int pos){
    auto it=st.lower_bound({l,-1});

    vector<pair<long long,int>>vec;
    while(it!=st.end()&&it->first<=r){
        vec.push_back(*it);
        it++;
    }
    for(auto p:vec){
        st.erase(p);
        f[p.second]=pos;
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    for(int i=1;i<=n;i++){
        if(i&1){
            pre[i]=pre[i-1]+val[i];
        }
        else{
            pre[i]=pre[i-1]-val[i];
        }
    }

    for(int i=1;i<=n+1;i++){
        f[i]=n+1;
    }

    for(int i=1;i<=n;i++){
        if(i&1){
            st.insert({MOD(pre[i-1]),i});
        }
        else{
            f[i]=i;
            int high=MOD(pre[i-1]);

            if(val[i]>=k-1){
                compute(0,k-1,i);
            }
            else{
                int low=MOD(high-val[i]);
                if(low<high){
                    compute(low,high,i);
                }
                else{
                    compute(low,k-1,i);
                    compute(0,high,i);
                }
            }
        }
    }

    for(int i=1;i<=n;i++){
        if(f[i]<=n){
            up[0][i]=f[i]+1;
            sum[0][i]=(pre[f[i]-1]-pre[i-1])/k;
        }
        else{
            up[0][i]=n+2;
        }
    }

    p=log2(n);
    for(int k=1;k<=p;k++){
        for(int i=1;i<=n;i++){
            int mid=up[k-1][i];
            if(mid<=n){
                up[k][i]=up[k-1][mid];
                sum[k][i]=sum[k-1][i]+sum[k-1][mid];
            }
            else{
                up[k][i]=n+2;
                sum[k][i]=sum[k-1][i];
            }
        }
    }

    for(int i=1;i<=m;i++){
        int l,r;
        cin>>l>>r;

        int ans=0;
        int cur=l;
        for(int k=p;k>=0;k--){
            if(cur<=n&&up[k][cur]<=r+1){
                ans+=sum[k][cur];
                cur=up[k][cur];
            }
        }
        if(cur<=r){
            ans+=(pre[r]-pre[cur-1])/k;
        }
        cout<<ans<<endl;
    }
    return 0;
}