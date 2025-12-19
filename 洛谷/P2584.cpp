#include<bits/stdc++.h>
using namespace std;
const int MAXN = 250005;
const int BASE = 1e6;

int n,all;

int head;
int cnt;
long long key[MAXN];
string name[MAXN];
int ls[MAXN];
int rs[MAXN];
int sz[MAXN];
double pritority[MAXN];
map<string,long long>vis;

string str;
long long val;

void up(int i){
    sz[i]=sz[ls[i]]+sz[rs[i]]+1;
}

void inorder(int u){
    if(u!=0){
        inorder(ls[u]);
        cout<<name[u]<<' ';
        inorder(rs[u]);
    }
}

void split(int l,int r,int i,int rk){
    if(i==0){
        rs[l]=ls[r]=0;
    }
    else{
        if (sz[ls[i]] + 1 <= rk) {
            rs[l] = i;
            split(i, r, rs[i], rk - sz[ls[i]] - 1);
        } else {
            ls[r] = i;
            split(l, i, ls[i], rk);
        }
        up(i);
    }
}

int merge(int l,int r){
    if (l == 0 || r == 0) {
        // 遇到了空树  直接结束
        return l + r;
    }
    if (pritority[l] >= pritority[r]) {
        rs[l] = merge(rs[l], r);
        up(l);
        return l;
    } else {
        ls[r] = merge(l, ls[r]);
        up(r);
        return r;
    }
}

void remove(int rk){
    split(0,0,head,rk);
    int lm=rs[0];
    int r=ls[0];
    split(0,0,lm,rk-1);
    int l=rs[0];
    head=merge(l,r);
}

void add(int rk){
    split(0,0,head,rk-1);
    ++cnt;
    key[cnt]=val;
    name[cnt]=str;
    sz[cnt]=1;
    pritority[cnt]=(double)rand()/RAND_MAX;
    head=merge(merge(rs[0],cnt),ls[0]);
}

// 返回大于val的个数+1
int getrank(long long val){
    int u=head;
    int ans=0;
    while(key[u]!=val&&u!=0){
        if(key[u]>val){
            ans+=sz[ls[u]]+1;
            u=rs[u];
        }
        else{
            u=ls[u];
        }
    }
    if(u!=0){
        ans+=sz[ls[u]];
    }
    return ans+1;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    srand(time(0));
    cin>>n;
    for(int i=1;i<=n;i++){
        char op;
        cin>>op;
        if(op=='?'){
            cin>>str;
            if(str[0]>='0'&&str[0]<='9'){
                val=0;
                for(int j=0;j<(int)str.length();j++){
                    val=val*10+str[j]-'0';
                }
                int l=val,r=min(all,(int)val+9);
                split(0,0,head,r);
                int lm=rs[0];
                int rt=ls[0];
                split(0,0,lm,l-1);
                inorder(ls[0]);
                cout<<endl;
                head=merge(merge(rs[0],ls[0]),rt);
            }
            else{
                long long score=vis[str];
                int rk=getrank(score);
                cout<<rk<<endl;
            }
        }
        else{
            cin>>str>>val;
            val=val*BASE+(n-i+1);
            long long tmp=vis[str];
            if(tmp!=0){
                int rk=getrank(tmp);
                remove(rk);
                all--;
            }
            int rk=getrank(val);
            vis[str]=val;
            add(rk);
            all++;
        }
    }
    return 0;
}