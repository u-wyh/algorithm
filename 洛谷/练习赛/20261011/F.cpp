#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;
const int MAXB = 505;

int n;
int val[MAXN];

int blen;
int bnum;
int bl[MAXB];
int br[MAXB];
int bi[MAXN];

int max1[MAXB];

int ans;
int l1[MAXN];
int l2[MAXN];
int r1[MAXN];
int r2[MAXN];

void calc(int x){
    int b=bi[x];
    int l=bl[b];
    int r=br[b];

    for(int i=x-1;i>=l;i--){
        if(val[i]>val[x]){
            if(l1[x]==0){
                l1[x]=i;
            }
            else if(l2[x]==0){
                l2[x]=i;
            }
        }
        if(l2[x]){
            break;
        }
    }
    for(int i=b-1;i>=1;i--){
        if(max1[i]>val[x]){
            int l=bl[i],r=br[i];
            for(int p=r;p>=l;p--){
                if(val[p]>val[x]){
                    if(l1[x]==0){
                        l1[x]=p;
                    }
                    else if(l2[x]==0){
                        l2[x]=p;
                        break;
                    }
                }
            }
        }
        if(l2[x]){
            break;
        }
    }

    r1[x]=r2[x]=n+1;
    for(int i=x+1;i<=r;i++){
        if(val[i]>val[x]){
            if(r1[x]==n+1){
                r1[x]=i;
            }
            else if(r2[x]==n+1){
                r2[x]=i;
            }
        }
        if(r2[x]!=n+1){
            break;
        }
    }
    for(int i=b+1;i<=bnum;i++){
        if(max1[i]>val[x]){
            int l=bl[i],r=br[i];
            for(int p=l;p<=r;p++){
                if(val[p]>val[x]){
                    if(r1[x]==n+1){
                        r1[x]=p;
                    }
                    else if(r2[x]==n+1){
                        r2[x]=p;
                        break;
                    }
                }
            }
        }
        if(r2[x]!=n+1){
            break;
        }
    }
}

void prepare(){
    val[0]=n+1,val[n+1]=n+1;

    blen=sqrt(n);
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(n,i*blen);
    }

    for(int b=1;b<=bnum;b++){
        int l=bl[b],r=br[b];
        for(int i=l;i<=r;i++){
            max1[b]=max(max1[b],val[i]);
        }
    }

    for(int i=1;i<=n;i++){
        calc(i);
    }
}

void compute(){
    for(int i=1;i<=n;i++){
        // cout<<i<<":   "<<l1[i]<<' '<<l2[i]<<' '<<r1[i]<<' '<<r2[i]<<endl;
        if(l1[i]!=0){
            ans+=(i-l1[i])*(l1[i]-l2[i])*(r1[i]-i);
        }
        if(r1[i]!=n+1){
            ans+=(r1[i]-i)*(i-l1[i])*(r2[i]-r1[i]);
        }
    }
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    prepare();
    compute();
    cout<<ans<<endl;
    return 0;
}