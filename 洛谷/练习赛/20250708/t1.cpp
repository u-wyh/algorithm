#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 3e5+5;
const int MAXM = 9e5+5;

int t,n,m;

struct node{
    int id,l,r;
}nums[MAXN];

int tree[MAXM];

int help[MAXM];
int cnt=0;

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
    return a.id<b.id;
}

int find(int val){
    int l=1,r=cnt,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(help[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int v){
    while(x<=cnt){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

int sum(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

signed main()
{
    int T;
    T=read();
    while(T--){
        t=read(),n=read(),m=read();
        for(int i=1;i<=m;i++){
            nums[i].id=read();
            nums[i].l=read(),nums[i].r=read();
            help[i*3-2]=nums[i].l,help[i*3-1]=nums[i].r,help[3*i]=nums[i].r+1;
        }
        sort(help+1,help+3*m+1);
        cnt=1;
        for(int i=2;i<=3*m;i++){
            if(help[i]!=help[i-1]){
                help[++cnt]=help[i];
            }
        }
        sort(nums+1,nums+m+1,cmp);
        int ans=0;
        for(int i=1;i<=cnt;i++){
            tree[i]=0;
        }
        for(int i=1;i<=m;i++){
            if(nums[i].id==0){
                int l=find(nums[i].l);
                int r=find(nums[i].r);
                for(int j=l;j<=r;j++){
                    add(j,help[j+1]-help[j]);
                    // cout<<' '<<j<<' '<<(help[j+1]-help[j])<<endl;
                }
            }
            else{
                int l=find(nums[i].l);
                int r=find(nums[i].r);
                ans+=sum(r)-sum(l-1);
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}