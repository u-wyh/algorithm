#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXM = 1e5+5;

int n,m;
struct node{
    int pos,val;
}nums[MAXM];

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
    return a.pos<b.pos;
}

int compute(int l,int r){
    int res=0,ans=0;
    if(nums[l].pos==1){
        for(int i=l;i<=r;i++){
            ans^=nums[i].val;
            res+=ans;
        }
    }
    else{
        for(int i=30;i>=0;i--){
            int cnt[2],tot[2];
            cnt[0]=tot[0]=0;
            cnt[1]=tot[1]=1;
            for(int j=0;j<=1;j++){
                for(int k=l;k<=r;k++){
                    tot[j]^=(nums[k].val>>i)&1;
                    cnt[j]+=tot[j];
                }
            }
            res+=(1<<i)*min(cnt[0],cnt[1]);
        }
    }
    return res;
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        nums[i].pos=read();
        nums[i].val=read();
    }
    sort(nums+1,nums+m+1,cmp);
    int now=1;
    int ans=0;
    while(now<=m){
        int lst=now;
        while(now<=m&&nums[now].pos==nums[now+1].pos-1){
            now++;
        }
        ans+=compute(lst,now);
        now++;
    }
    cout<<ans<<endl;
    return 0;
}
