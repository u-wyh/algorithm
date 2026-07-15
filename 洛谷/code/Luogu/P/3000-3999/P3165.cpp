#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
struct node{
    int h,sub;
};
node nums[MAXN];
int arr[MAXN];

int head;
int cnt;
int val[MAXN];
int key[MAXN];
int ls[MAXN];
int rs[MAXN];
int sz[MAXN];
double priority[MAXN];
bool rev[MAXN];
int ans[MAXN];

bool cmp(node a,node b){
    return (a.h==b.h)?(a.sub<b.sub):(a.h<b.h);
}

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

void up(int i){
    sz[i]=sz[ls[i]]+sz[rs[i]]+1;
    val[i]=min(key[i],min(val[ls[i]],val[rs[i]]));
}

void down(int i){
    if(rev[i]){
        swap(ls[i],rs[i]);
        rev[ls[i]]^=1;
        rev[rs[i]]^=1;
        rev[i]=false;
    }
}

int getrank(int x){
    int u=head;
    int ans=0;
    while(u){
        down(u);
        if(val[ls[u]]==x){
            u=ls[u];
        }
        else if(val[rs[u]]==x){
            ans+=sz[ls[u]]+1;
            u=rs[u];
        }
        else{
            break;
        }
    }
    ans+=sz[ls[u]]+1;
    return ans;
}

int merge(int l, int r) {
    if (l == 0 || r == 0) {
        return l + r;
    }
    if (priority[l] >= priority[r]) {
        down(l);//下发懒信息
        rs[l] = merge(rs[l], r);
        up(l);
        return l;
    } else {
        down(r);
        ls[r] = merge(l, ls[r]);
        up(r);
        return r;
    }
}

void split(int l, int r, int i, int rank) {
    if (i == 0) {
        rs[l] = ls[r] = 0;
    } else {
        down(i);
        if (sz[ls[i]] + 1 <= rank) {
            rs[l] = i;
            split(i, r, rs[i], rank - sz[ls[i]] - 1);
        } else {
            ls[r] = i;
            split(l, i, ls[i], rank);
        }
        up(i);
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i].h=read();
        nums[i].sub=i;
    }
    sort(nums+1,nums+n+1,cmp);
    val[0]=INT_MAX;
    for(int i=1;i<=n;i++){
        arr[nums[i].sub]=i;
    }
    for(int i=1;i<=n;i++){
        ++cnt;
        key[cnt]=arr[i];
        val[cnt]=arr[i];
        sz[cnt]=1;
        priority[cnt]=(double)rand()/RAND_MAX;
        head=merge(head,cnt);
    }
    for(int i=1;i<=n;i++){
        int rk=getrank(i);
        split(0,0,head,rk);
        int lm=rs[0];
        int r=ls[0];
        split(0,0,lm,rk-1);
        rev[rs[0]]^=1;
        head=merge(rs[0],r);
        printf("%d ",rk+i-1);
    }
    return 0;
}