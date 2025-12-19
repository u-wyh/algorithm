#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;
const int MAXH = 20;
const int INF = 1e18;

int n;
int val[MAXN];
int lg2[MAXN];

int stmax[MAXN][MAXH];
int stmin[MAXN][MAXH];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int querymax(int l,int r){
    int p=lg2[r-l+1];
    return max(stmax[l][p],stmax[r-(1<<p)+1][p]);
}

int querymin(int l,int r){
    int p=lg2[r-l+1];
    return min(stmin[l][p],stmin[r-(1<<p)+1][p]);
}

signed main()
{
    n=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    lg2[0]=-1;
    for(int i=1;i<=n;i++){
        lg2[i]=lg2[i>>1]+1;
    }

    for(int i=1;i<=n;i++){
        stmax[i][0]=-INF;
        stmin[i][0]=INF;
    }

    for(int i=2;i<=n-1;i++){
        if(val[i-1]<=val[i]&&val[i]>=val[i+1]){
            stmax[i][0]=min(val[i-1]+val[i],val[i]+val[i+1]);
        }
        if(val[i-1]>=val[i]&&val[i]<=val[i+1]){
            stmin[i][0]=max(val[i-1]+val[i],val[i]+val[i+1]);
        }
    }
    for(int p=1;p<=lg2[n];p++){
        for(int i=1;i+(1<<(p-1))-1<=n;i++){
            stmin[i][p]=min(stmin[i][p-1],stmin[i+(1<<(p-1))][p-1]);
            stmax[i][p]=max(stmax[i][p-1],stmax[i+(1<<(p-1))][p-1]);
        }
    }
    int ans=0;
    for(int i=1;i<n;i++){
        int l=i+1,r=n,pos=i;
        while(l<=r){
            int mid=(l+r)>>1;
            if(mid-i<=1){
                pos=mid;
                l=mid+1;
            }
            else{
                int lt=querymax(i+1,mid-1);
                int rt=querymin(i+1,mid-1);
                if(lt<rt){
                    pos=mid;
                    l=mid+1;
                }
                else{
                    r=mid-1;
                }
            }
        }
        ans+=pos-i;
    }
    cout<<ans<<endl;
    return 0;
}