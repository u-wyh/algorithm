#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,m;

int head;
int cnt;
int fa[MAXN];
int ls[MAXN];
int rs[MAXN];
int sz[MAXN];
char key[MAXN];
int sta[MAXN];
double priority[MAXN];
bool rev[MAXN];

bool del[MAXN];

void up(int i){
    // if(ls[i]) fa[ls[i]]=i;
    // if(rs[i]) fa[rs[i]]=i;
    sz[i]=sz[ls[i]]+sz[rs[i]]+1;
    sta[i]=(sta[ls[i]]|sta[rs[i]])|(1<<(key[i]-'a'));
}

int newnode(char c){
    ++cnt;
    sz[cnt]=1;
    key[cnt]=c;
    priority[cnt]=(double)rand()/RAND_MAX;
    sta[cnt]=(1<<(c-'a'));
    return cnt;
}

void down(int i) {
    if (rev[i]) {
        swap(ls[i], rs[i]);
        rev[ls[i]] ^= 1;
        rev[rs[i]] ^= 1;
        rev[i] = false;
    }
}

void split(int l, int r, int i, int rank) {
    if (i == 0) {
        rs[l] = ls[r] = 0;
    } else {
        down(i);
        if (sz[ls[i]] + 1 <= rank) {
            rs[l] = i;
            fa[i]=l;
            split(i, r, rs[i], rank - sz[ls[i]] - 1);
        } else {
            ls[r] = i;
            fa[i]=r;
            split(l, i, ls[i], rank);
        }
        up(i);
    }
}

int merge(int l,int r){
    if (l == 0 || r == 0) {
        return l + r;
    }
    if (priority[l] >= priority[r]) {
        down(l);//下发懒信息
        rs[l] = merge(rs[l], r);
        fa[rs[l]]=l;
        up(l);
        return l;
    } else {
        down(r);
        ls[r] = merge(l, ls[r]);
        fa[ls[r]]=r;
        up(r);
        return r;
    }
}

void work(int u){
    while(fa[u]!=0){
        down(u);
        u=fa[u];
    }
    down(u);
}

int find(int x){
    work(x);
    int ans=sz[ls[x]]+1;
    while(fa[x]){
        if(rs[fa[x]]==x){
            ans+=sz[ls[fa[x]]]+1;
        }
        x=fa[x];
    }
    return ans;
}

void getrank(int rk){
    int u=head;
    while(rk){
        down(u);
        if(sz[ls[u]]+1==rk){
            cout<<key[u]<<endl;
            return ;
        }
        else if(sz[ls[u]]+1<rk){
            rk-=sz[ls[u]]+1;
            u=rs[u];
        }
        else{
            u=ls[u];
        }
    }
}

int compute(int val){
    // cout<<"       "<<val<<endl;
    int ans=0;
    while(val){
        if(val&1){
            ans++;
        }
        val>>=1;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        char c;
        cin>>c;
        head=merge(head,newnode(c));
    }
    while(m--){
        char op;
        int x;
        cin>>op>>x;
        if(op=='I'){
            char c;
            cin>>c;
            split(0,0,head,x);
            int lm=rs[0];
            int r=ls[0];
            lm=merge(lm,newnode(c));
            head=merge(lm,r);
        }
        else if(op=='D'){
            split(0,0,head,x);
            int lm=rs[0];
            int r=ls[0];
            split(0,0,lm,x-1);
            del[ls[0]]=1;
            head=merge(rs[0],r);
        }
        else if(op=='R'){
            int y;
            cin>>y;
            split(0,0,head,y);
            int lm=rs[0];
            int r=ls[0];
            split(0,0,lm,x-1);
            rev[ls[0]]^=1;
            head=merge(merge(rs[0],ls[0]),r);
        }
        else if(op=='P'){
            if(del[x]){
                cout<<0<<endl;
                continue;
            }
            cout<<find(x)<<endl;
        }
        else if(op=='T'){
            getrank(x);
        }
        else{
            int y;
            cin>>y;
            split(0,0,head,y);
            int lm=rs[0];
            int r=ls[0];
            split(0,0,lm,x-1);
            cout<<compute(sta[ls[0]])<<endl;
            head=merge(merge(rs[0],ls[0]),r);
        }
    }
    return 0;
}