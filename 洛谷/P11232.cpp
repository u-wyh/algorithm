#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int n,m,len,V;
struct node{
    int l,r;
}nums[MAXN];
int d[MAXN],v[MAXN],a[MAXN];
int cnt=0;
int pos[MAXN];

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

int find(int i,int L){
    int l=L,r=m,ans=m+1;
    while(l<=r){
        int mid=(l+r)/2;
        if(v[i]+2ll*a[i]*(pos[mid]-d[i])>V){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int find1(int val){
    int l=1,r=m,ans=m+1;
    while(l<=r){
        int mid=(l+r)/2;
        if(pos[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int find2(int i,int L){
    int l=L,r=m,ans=-1;
    while(l<=r){
        int mid=(l+r)/2;
        if(v[i]+2ll*a[i]*(pos[mid]-d[i])>V){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    return ans;
}

bool cmp(node a,node b){
    return (a.r==b.r)?(a.l<b.l):(a.r<b.r);
}

signed main()
{
    int T;
    T=read();
    while(T--){
        n=read(),m=read(),len=read(),V=read();
        V*=V;
        cnt=0;
        for(int i=1;i<=n;i++){
            d[i]=read();v[i]=read();a[i]=read();
            v[i]*=v[i];
        }
        for(int i=1;i<=m;i++){
            pos[i]=read();
        }
        for(int i=1;i<=n;i++){
            if(a[i]>=0){
                if(v[i]+2ll*a[i]*(len-d[i])<=V){
                    continue;
                }
                else{
                    int L=find1(d[i]);
                    if(L==m+1){
                        continue;
                    }
                    nums[++cnt].r=m;
                    nums[cnt].l=find(i,L);
                    if(nums[cnt].l==m+1){
                        cnt--;
                    }
                }
            }
            else{
                if(v[i]<=V){
                    continue;
                }
                else{
                    int L=find1(d[i]);
                    if(L==m+1){
                        continue;
                    }
                    nums[++cnt].l=L;
                    nums[cnt].r=find2(i,nums[cnt].l);
                    if(nums[cnt].r==-1){
                        cnt--;
                    }
                }
            }
        }
        sort(nums+1,nums+cnt+1,cmp);
        int res=0;
        int lst=0;
        for(int i=1;i<=cnt;i++){
            if(nums[i].l<=lst){
                continue;
            }
            else{
                res++;
                lst=nums[i].r;
            }
        }
        cout<<cnt<<' '<<(m-res)<<endl;
    }
    return 0;
}