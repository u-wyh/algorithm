#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int n,q;
int need[MAXN];//这种食物所需要的时间
int ok[MAXN];//这种食物已经好了的数量
int tree[MAXN<<2];

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

void build(int l,int r,int i){
    tree[i]=0;
    if(l==r){
        return ;
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
    }
}

void add(int pos,int val,int l,int r,int i){
    tree[i]+=val;
    if(l==r){
        return ;
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            add(pos,val,l,mid,i<<1);
        }
        else{
            add(pos,val,mid+1,r,i<<1|1);
        }
    }
}

int query(int l,int r,int i){
    if(tree[i]==0){
        return 0;
    }
    if(l==r){
        return l;
    }
    int mid=(l+r)>>1;
    if(tree[i<<1]){
        return query(l,mid,i<<1);
    }
    else{
        return query(mid+1,r,i<<1|1);
    }
}

int sum(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int ans=0;
        int mid=(l+r)>>1;
        if(jobl<=mid){
            ans+=sum(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            ans+=sum(jobl,jobr,mid+1,r,i<<1|1);
        }
        return ans;
    }
}

signed main()
{
    int T=read();
    while(T--){
        n=read();
        build(1,n,1);
        for(int i=1;i<=n;i++){
            need[i]=read();
            ok[i]=0;
        }
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>heap;
        vector<queue<int>>vec(n+1);
        q=read();
        while(q--){
            int t,op;
            t=read(),op=read();

            while(!heap.empty()){
                pair<int,int>u=heap.top();
                if(u.first>t){
                    break;
                }
                heap.pop();
                int id=u.second,tt=u.first;
                if(!vec[id].empty()&&vec[id].front()==tt){
                    vec[id].pop();
                    add(id,1,1,n,1);
                    ok[id]++;
                    if(!vec[id].empty()){
                        heap.push({vec[id].front(),id});
                    }
                }
            }

            if(op==0){
                int id=read();
                int tt=t+need[id];
                vec[id].push(tt);
                if(vec[id].size()==1){
                    heap.push({tt,id});
                }
            }
            else if(op==1){
                int id=query(1,n,1);
                if(id==0){
                    printf("Yazid is angry.\n");
                }
                else{
                    printf("%lld\n",id);
                    add(id,-1,1,n,1);
                    ok[id]--;
                }
            }
            else if(op==2){
                int id=read();
                if(ok[id]){
                    printf("Succeeded!\n");
                    add(id,-1,1,n,1);
                    ok[id]--;
                }
                else if(vec[id].empty()){
                    printf("YJQQQAQ is angry.\n");
                }
                else{
                    printf("%lld\n", vec[id].front() - t);
                }
            }
            else{
                int l,r;
                l=read(),r=read();
                printf("%lld\n",sum(l,r,1,n,1));
            }
        }
    }
    return 0;
}