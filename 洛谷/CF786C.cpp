#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,blen;
int nums[MAXN];
bool vis[MAXN];
int ans[MAXN];

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

void prepare(){
    blen=sqrt(n);
    for(int i=1;i<=n;i++){
        ans[i]=-1;
    }
}

int query(int limit){
    int kind=0,cnt=0,st=1;
    for(int i=1;i<=n;i++){
        if(!vis[nums[i]]){
            kind++;
            if(kind>limit){
                cnt++;
                for(int j=st;j<i;j++){
                    vis[nums[j]]=false;
                }
                st=i;
                kind=1;
            }
            vis[nums[i]]=true;
        }
    }
    if(kind>0){
        cnt++;
        for(int i=st;i<=n;i++){
            vis[nums[i]]=false;
        }
    }
    return cnt;
}

int jump(int l,int r,int len){
    int ans=l;
    while(l<=r){
        int mid=(l+r)>>1;
        int check=query(mid);
        if(check==len){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    return ans+1;
}

void compute(){
    for(int i=1;i<=blen;i++){
        ans[i]=query(i);
    }
    for(int i=blen+1;i<=n;i=jump(i,n,ans[i])){
        ans[i]=query(i);
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    prepare();
    compute();
    for(int i=1;i<=n;i++){
        if(ans[i]==-1){
            ans[i]=ans[i-1];
        }
        printf("%d ",ans[i]);
    }
    return 0;
}