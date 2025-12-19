#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int key[MAXN];
int ls[MAXN];
int rs[MAXN];

//中序遍历数组
int m;
int arr[MAXN];
int f[MAXN];
int help[MAXN];

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

void inorder(int i){
    if(ls[i]){
        inorder(ls[i]);
    }
    arr[++m]=key[i];
    if(rs[i]){
        inorder(rs[i]);
    }
    return ;
}

//找到help数组中第一个比这个元素大或相等的位置
int find(int x){
    int l=1,r=m,ans=-1;
    while(l<=r){
        int mid=(l+r)/2;
        if(help[mid]>=x){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        key[i]=read();
    }
    for(int i=2;i<=n;i++){
        int fa,op;
        fa=read(),op=read();
        if(op==0){
            ls[fa]=i;
        }
        else{
            rs[fa]=i;
        }
    }
    inorder(1);
    for(int i=1;i<=n;i++){
        arr[i]-=i;
    }
    m=0;
    for(int i=1;i<=n;i++){
        int sub=find(arr[i]);
        if(sub==-1){
            help[++m]=arr[i];
        }
        else{
            help[sub]=arr[i];
        }
    }
    cout<<(n-m)<<endl;
    return 0;
}
