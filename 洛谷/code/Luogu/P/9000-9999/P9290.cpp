#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;

int n,ans;
int arr[MAXN],st[MAXN];
int L[MAXN],R[MAXN],l,r;
//左边第一个严格大于自己的数字下标
//右边第一个严格小于自己的数字下标

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

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
    }
    int cur;
    for(int i=1;i<=n;i++){
        while(r>0&&arr[st[r-1]]>arr[i]){
            cur=st[--r];
            R[cur]=i;
        }
        st[r++]=i;
    }
    while(r>0){
        cur=st[--r];
        R[cur]=n+1;
    }
    for(int i=n;i>=1;i--){
        while(l>0&&arr[st[l-1]]<arr[i]){
            cur=st[--l];
            L[cur]=i;
        }
        st[l++]=i;
    }
    while(l>0){
        cur=st[--l];
        L[cur]=0;
    }
    l=1,r=1;
    while(l<=n){
        r=l;
        for(r=R[l]-1;r>=l;r--){
            if(L[r]<=l){
                break;
            }
        }
        l=r+1;
        ans++;
    }
    cout<<ans<<endl;
    return 0;
}
