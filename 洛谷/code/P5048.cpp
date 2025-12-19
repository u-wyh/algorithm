#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXB = 805;

int n,m;
int nums[MAXN];

struct node{
    int v,sub;
};

node arr[MAXN];
int id[MAXN];

int blen;
int bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

int mode[MAXB][MAXB];
int cnt[MAXN];

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

bool cmp(node a,node b){
    if(a.v!=b.v){
        return a.v<b.v;
    }
    return a.sub<b.sub;
}

void prepare(){
    blen=sqrt(n);
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(n,i*blen);
    }

    for(int i=1;i<=n;i++){
        arr[i].v=nums[i];
        arr[i].sub=i;
    }
    sort(arr+1,arr+n+1,cmp);
    for(int i=1;i<=n;i++){
        id[arr[i].sub]=i;
    }

    for(int i=1;i<=bnum;i++){
        for(int j=i;j<=bnum;j++){
            int most=mode[i][j-1];
            for(int k=bl[j];k<=br[j];k++){
                most=max(most,++cnt[nums[k]]);
            }
            mode[i][j]=most;
        }
        for(int j=bl[i];j<=n;j++){
            cnt[nums[j]]=0;
        }
    }
}

int query(int l,int r){
    int ans=0;
    if(bi[l]==bi[r]){
        for(int i=l;i<=r;i++){
            ans=max(ans,++cnt[nums[i]]);
        }
        for(int i=l;i<=r;i++){
            cnt[nums[i]]=0;
        }
    }
    else{
        ans=mode[bi[l]+1][bi[r]-1];
        for(int i=l;i<=br[bi[l]];i++){
            int sub=id[i];
            while(sub+ans<=n&&arr[sub+ans].v==nums[i]&&arr[sub+ans].sub<=r){
                ans++;
            }
        }
        for(int i=bl[bi[r]];i<=r;i++){
            int sub=id[i];
            while(sub-ans>0&&arr[sub-ans].v==nums[i]&&arr[sub-ans].sub>=l){
                ans++;
            }
        }
    }
    return ans;
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    prepare();
    int ans=0;
    for(int i=1;i<=m;i++){
        int l=read(),r=read();
        l^=ans;
        r^=ans;
        ans=query(l,r);
        printf("%d\n",ans);
    }
    return 0;
}