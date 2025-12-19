// https://www.luogu.com.cn/problem/P4036
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int BASE = 499;
const int MOD = 1e9+7;
const int MAXN = 100001;

int n,m;
char s[MAXN];

int head = 0;
int cnt = 0;
char key[MAXN];
int ls[MAXN];
int rs[MAXN];
int sz[MAXN];
int h[MAXN];
double priority[MAXN];

int p[MAXN];

//没有词频压缩  所以出现次数就是1
void up(int i) {
    sz[i] = sz[ls[i]] + sz[rs[i]] + 1;
    h[i]=(h[ls[i]]*p[sz[rs[i]]+1]%MOD+(key[i]-'a'+1)*p[sz[rs[i]]]%MOD+h[rs[i]])%MOD;
}

//根据值分裂树
//这里当前来到了i节点  <=num的目前到达的节点是l  >num的目前到达的节点是r
//分裂过程中左右树的头结点其实并不重要  重要的是当前来到的节点
void split(int l, int r, int i, int num) {
    if (i == 0) {
        rs[l] = ls[r] = 0;
    } else {
        int lsz=sz[ls[i]];
        if(lsz+1<=num){
            rs[l]=i;
            split(i,r,rs[i],num-lsz-1);
        }
        else{
            ls[r]=i;
            split(l,i,ls[i],num);
        }
        up(i);
    }
}

int merge(int l, int r) {
    if (l == 0 || r == 0) {
        return l + r;
    }
    if (priority[l] >= priority[r]) {
        rs[l] = merge(rs[l], r);
        up(l);
        return l;
    } else {
        ls[r] = merge(l, ls[r]);
        up(r);
        return r;
    }
}

int create(char c){
    cnt++;
    key[cnt]=c;
    sz[cnt]=1;
    priority[cnt] = (double)rand() / RAND_MAX;
    h[cnt]=c-'a'+1;
    return cnt;
}

void insert(int pos,char c){
    int node=create(c);
    if(head==0){
        head=node;
        return ;
    }
    if(pos==0){
        head=merge(node,head);
    }
    else{
        split(0,0,head,pos);
        head=merge(merge(rs[0],node),ls[0]);
    }
}

int gethash(int l,int r){
    split(0,0,head,r);
    int lm=rs[0];
    int rt=ls[0];
    split(0,0,lm,l-1);
    int lt=rs[0];
    int m=ls[0];
    int ans=h[m];
    head=merge(merge(lt,m),rt);
    return ans;
}

int query(int x,int y){
    int len=sz[head];
    int l=0,r=min(len-y+1,len-x+1),ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        int h1=gethash(x,x+mid-1);
        int h2=gethash(y,y+mid-1);
        if(h1==h2){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    return ans;
}

void update(int num,char c){
    split(0,0,head,num);
    int lm=rs[0];
    int rt=ls[0];
    split(0,0,lm,num-1);
    int lt=rs[0];
    int m=ls[0];
    key[m]=c;
    h[m]=c-'a'+1;
    head=merge(merge(lt,m),rt);
}

signed main() 
{
    p[0]=1;
    for(int i=1;i<MAXN;i++){
        p[i]=p[i-1]*BASE;
        p[i]%=MOD;
    }
    scanf("%s",s+1);
    n=strlen(s+1);
    for(int i=0;i<n;i++){
        insert(i,s[i+1]);
    }
    cin>>m;
    while(m--){
        char op,c;
        int x,y;
        cin>>op>>x;
        if(op=='Q'){
            cin>>y;
            cout<<query(x,y)<<endl;
        }
        else if(op=='R'){
            cin>>c;
            update(x,c);
        }
        else{
            cin>>c;
            insert(x,c);
        }
    }
    return 0;
}