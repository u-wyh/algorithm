#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,now;
struct node{
    int l,r,id;
};
node nums[MAXN];
bool vis[MAXN];

int ans[MAXN];
int cnt;

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

bool cmpl(node a,node b){
    if(a.l==b.l){
        return a.r>b.r;
    }
    return a.l<b.l;
}

bool cmpr(node a,node b){
    return a.r>b.r;
}

int main()
{
    int T=read();
    while(T--){
        n=read(),now=read();
        for(int i=1;i<=n;i++){
            nums[i].l=read();
            nums[i].r=read();
            nums[i].id=i;
        }
        sort(nums+1,nums+n+1,cmpl);

        cnt=0;
        for(int i=1;i<=n;i++){
            vis[i]=false;
        }

        long long res=0;

        for(int i=1;i<=n;i++){
            if(nums[i].r>=now){
                if(nums[i].l<=now){
                    ans[++cnt]=nums[i].id;
                    vis[nums[i].id]=1;
                }
                else{
                    ans[++cnt]=nums[i].id;
                    vis[nums[i].id]=1;
                    res+=nums[i].l-now;
                }
                now=nums[i].r;
            }
        }
        sort(nums+1,nums+n+1,cmpr);

        for(int i=1;i<=n;i++){
            res+=nums[i].r-nums[i].l;
        }
        for(int i=1;i<=n;i++){
            if(!vis[nums[i].id]){
                ans[++cnt]=nums[i].id;
            }
        }

        cout<<res<<endl;
        for(int i=1;i<=n;i++){
            cout<<ans[i]<<' ';
        }
        cout<<endl;
    }
    return 0;
}