#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;
const int MAXM = 3e5+5;

int n,m;
int tot;
int tmp[MAXN*4];

int arr[MAXN];
int val[MAXN];

int tree1[MAXN*3];
int tree2[MAXN*3];

struct node{
    int op,l,r,pos;
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

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
        tmp[++tot]=arr[i];
    }
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=m;i++){
        nums[i].op=read(),nums[i].l=read(),nums[i].r=read();
        if(nums[i].op==2){
            nums[i].x=read();
            tmp[++tot]=nums[i].r;
        }
        else{
            tmp[++tot]=nums[i].l;
            tmp[++tot]=nums[i].r;
        }
    }
    sort(tmp+1,tmp+tot+1);
    tot=unique(tmp+1,tmp+tot+1)-tmp-1;
    for(int i=1;i<=n;i++){
        arr[i]=lower_bound(tmp+1,tmp+tot+1,arr[i])-tmp;
        update(arr[i],val[i],tmp[arr[i]]);
    }
    for(int i=1;i<=m;i++){
        if(nums[i].op==2){
            nums[i].r=lower_bound(tmp+1,tmp+tot+1,nums[i].r)-tmp;
            
        }
    }
    return 0;
}