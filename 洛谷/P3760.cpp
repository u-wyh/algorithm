#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 1e6+5;

int n;
int nums[MAXN];
int tree[MAXM][2];
int p;
int base;

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

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int v,int op){
    while(x<=p){
        tree[x][op]+=v;
        x+=lowbit(x);
    }
}

int query(int x,int op){
    int ans=0;
    while(x){
        ans=(ans+tree[x][op])%2;
        x-=lowbit(x);
    }
    return ans;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
        nums[i]+=nums[i-1];
    }
    int ans=0;
    int cnt0=1,cnt1=0;
    int cnt=0;
    for(int i=1;i<=n;i++){
        if(nums[i]&1){
            cnt=(cnt+cnt0)%2;
            cnt1++;
        }
        else{
            cnt=(cnt+cnt1)%2;
            cnt0++;
        }
    }
    ans+=cnt;
    for(int i=1;i<=19;i++){
        cnt=0;
        p=1<<i;
        base=p-1;
        for(int j=0;j<=p;j++){
            tree[j][0]=tree[j][1]=0;
        }
        add(1,1,0);
        for(int j=1;j<=n;j++){
            int v=nums[j]&base;
            if(nums[j]&(1<<i)){
                cnt=(cnt+query(v+1,0)+(2+query(p,1)-query(v+1,1)))%2;
                add(v+1,1,1);
            }
            else{
                cnt=(cnt+query(v+1,1)+(2+query(p,0)-query(v+1,0)))%2;
                add(v+1,1,0);
            }
        }
        cnt=(cnt+2)%2;
        ans+=cnt*p;
    }
    cout<<ans<<endl;
    return 0;
}