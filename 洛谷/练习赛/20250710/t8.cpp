#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int nums[MAXN];

int st[MAXN];
int top;

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

bool check(int limit){
    top=0;
    for(int i=1;i<=n;i++){
        if(nums[i]<limit){
            st[++top]=0;
        }
        else{
            st[++top]=1;
        }

        if(top>=3&&st[top-1]==0&&st[top-2]==0){
            top-=3;
            st[++top]=0;
        }
    }
    int one=0;
    for(int i=1;i<=top;i++){
        if(st[i]==0){
            one--;
        }
        else{
            one++;
        }
    }
    return one>0;
}

int main()
{
    int T;
    T=read();
    while(T--){
        n=read();
        for(int i=1;i<=n;i++){
            nums[i]=read();
        }
        int l=1,r=1e9,ans=1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(check(mid)){
                ans=mid;
                l=mid+1;
            }
            else{
                r=mid-1;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}