#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1e3+5;
const int MAXM = 1e5+5;
const int MAXL = 105;
const int BASE = 499;
const int MOD = 998244353;

int n,len,m;
char str[MAXN][MAXL];

int cnt;
unordered_map<int,int>mp;
int p[MAXL];

int all[2*MAXM+MAXN];
int group[MAXN];
int val[MAXN];
int ans[MAXN];

void prepare(){
    p[0]=1;
    for(int i=1;i<=len;i++){
        p[i]=(p[i-1]*BASE)%MOD;
    }

    for(int i=1;i<=n;i++){
        int v=0;
        for(int j=1;j<=len;j++){
            v=((str[i][j]-'a'+1)*p[j]+v)%MOD;
        }
        int id=mp[v];
        if(id==0){
            mp[v]=++cnt;
            id=cnt;
        }
        group[i]=id;
        all[id]++;
        val[i]=v;
    }

    for(int i=1;i<=n;i++){
        ans[i]=all[group[i]];
    }
}

signed main()
{
    cin>>n>>len>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=len;j++){
            cin>>str[i][j];
        }
    }
    prepare();

    for(int i=1;i<=m;i++){
        int p1,p2,w1,w2;
        cin>>p1>>w1>>p2>>w2;

        int old1=group[p1];
        int old2=group[p2];

        int val1,val2;
        if(p1!=p2){
            val1=(val[p1]-(((str[p1][w1]-'a'+1)*p[w1])%MOD)+(((str[p2][w2]-'a'+1)*p[w1])%MOD))%MOD;
            val2=(val[p2]+(((str[p1][w1]-'a'+1)*p[w2])%MOD)-(((str[p2][w2]-'a'+1)*p[w2])%MOD))%MOD;
        }
        else{
            val1=val2=(val[p1]-(((str[p1][w1]-'a'+1)*p[w1])%MOD)+(((str[p2][w2]-'a'+1)*p[w1])%MOD)+(((str[p1][w1]-'a'+1)*p[w2])%MOD)-(((str[p2][w2]-'a'+1)*p[w2])%MOD))%MOD;
        }

        val1=(val1%MOD+MOD)%MOD;
        val2=(val2%MOD+MOD)%MOD;

        int new1=(mp[val1]==0)?(mp[val1]=++cnt):mp[val1];
        int new2=(mp[val2]==0)?(mp[val2]=++cnt):mp[val2];

        swap(str[p1][w1],str[p2][w2]);

        val[p1]=val1,val[p2]=val2;

        if(p1!=p2){
            all[old1]--,all[old2]--;
            all[new1]++,all[new2]++;
        }
        else{
            all[old1]--;
            all[new1]++;
        }

        group[p1]=new1,group[p2]=new2;

        for(int i=1;i<=n;i++){
            ans[i]=max(ans[i],all[group[i]]);
        }
    }

    for(int i=1;i<=n;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}