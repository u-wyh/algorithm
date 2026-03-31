#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXB = 1e3+5;

int n,m;
int val[MAXN];
int sortv[MAXN];

int blen,bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

void prepare(){
    blen=sqrt(n);
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(n,i*blen);
    }
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }

    for(int i=1;i<=n;i++){
        sortv[i]=val[i];
    }
    for(int i=1;i<=bnum;i++){
        sort(sortv+bl[i],sortv+br[i]+1);
    }
}

int query(int i,int val){
    int l=bl[i],r=br[i],ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(sortv[mid]>=val){
            ans=br[i]-mid+1;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int compute(int l,int r,int v){
    int lb=bi[l];
    int rb=bi[r];
    int ans=0;
    if(lb==rb){
        for(int i=l;i<=r;i++){
            if(val[i]>=v){
                ans++;
            }
        }
    }
    else{
        for(int i=lb+1;i<rb;i++){
            ans+=query(i,v);
        }
        for(int i=l;i<=br[lb];i++){
            if(val[i]>=v){
                ans++;
            }
        }
        for(int i=bl[rb];i<=r;i++){
            if(val[i]>=v){
                ans++;
            }
        }
    }
    return ans;
}

void update(int pos,int v){
    int lb=bl[bi[pos]];
    int rb=br[bi[pos]];
    val[pos]=v;
    for(int i=lb;i<=rb;i++){
        sortv[i]=val[i];
    }
    sort(sortv+lb,sortv+rb+1);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    prepare();

    cin>>m;
    for(int i=1;i<=m;i++){
        int op,a,b,c;
        cin>>op>>a>>b;
        if(op==0){
            cin>>c;
            cout<<compute(a,b,c)<<endl;
        }
        else{
            update(a,b);
        }
    }
    return 0;
}