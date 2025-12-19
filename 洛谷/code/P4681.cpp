#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXP = 1e4+5;
const int MAXH = 100;

int n,m,mod;
int val[MAXN];

int degree[MAXP];
// 判断某个数字是不是在循环中了
bool cycle[MAXP];

// 是否所有节点都已经在循环中了
bool cyc[MAXN<<2];
// 如果在循环节中  循环节长度是多少
int len[MAXN<<2];
// 如果在循环节中  目前是在循环节的哪一位上
int now[MAXN<<2];
// 如果在循环节中  这个循环节是什么
int tree[MAXN<<2][MAXH];
// 如果在这个循环节中  那么此时节点的懒信息是什么
int tag[MAXN<<2];

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

inline int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}

void up(int i){
    cyc[i]=(cyc[i<<1]&&cyc[i<<1|1]);
    if(cyc[i]){
        now[i]=1;
        len[i]=(len[i<<1]*len[i<<1|1])/gcd(len[i<<1],len[i<<1|1]);
        for(int p=1;p<=len[i];p++){
            tree[i][p]=tree[i<<1][(p-2+now[i<<1])%len[i<<1]+1]+tree[i<<1|1][(p-2+now[i<<1|1])%len[i<<1|1]+1];
        }
    }
}

void build(int l,int r,int i){
    if(l==r){
        if(cycle[val[l]]){
            cyc[i]=true;
            now[i]=1;
            tree[i][1]=val[l];
            for(int p=2;p<MAXH;p++){
                int val=(tree[i][p-1]*tree[i][p-1])%mod;
                if(val!=tree[i][1]){
                    tree[i][p]=val;
                }
                else{
                    len[i]=p-1;
                    break;
                }
            }
        }
        else{
            cyc[i]=false;
        }
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void lazy(int i,int t){
    now[i]=(now[i]+t-1)%len[i]+1;
    tag[i]=(tag[i]+t)%len[i];
}

void down(int i){
    if(tag[i]){
        lazy(i<<1,tag[i]);
        lazy(i<<1|1,tag[i]);
        tag[i]=0;
    }
}

void update(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        if(cyc[i]){
            lazy(i,1);
        }
        else{
            if(l==r){
                val[l]=(val[l]*val[l])%mod;
                if(cycle[val[l]]){
                    cyc[i]=1;
                    now[i]=1;
                    tree[i][1]=val[l];
                    for(int p=2;p<MAXH;p++){
                        int val=(tree[i][p-1]*tree[i][p-1])%mod;
                        if(val!=tree[i][1]){
                            tree[i][p]=val;
                        }
                        else{
                            len[i]=p-1;
                            break;
                        }
                    }
                }
            }
            else{
                int mid=(l+r)>>1;
                update(jobl,jobr,l,mid,i<<1);
                update(jobl,jobr,mid+1,r,i<<1|1);
                up(i);
            }
        }
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            update(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            update(jobl,jobr,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        if(cyc[i]){
            return tree[i][now[i]];
        }
        else{
            if(l==r){
                return val[l];
            }
            else{
                int mid=(l+r)>>1;
                int ans=0;
                ans+=query(jobl,jobr,l,mid,i<<1);
                ans+=query(jobl,jobr,mid+1,r,i<<1|1);
                return ans;
            }
        }
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        int ans=0;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,i<<1|1);
        }
        return ans;
    }
}

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%mod;
        }
        a=(a*a)%mod;
        b>>=1;
    }
    cout<<' '<<ans<<endl;
    return ans;
}

int main()
{
    // mod=233;
    // cout<<(power(135,4)+power(76,32)+power(183,32)+power(134,32)+power(118,8))<<endl;

    n=read(),m=read(),mod=read();

    // 哪些数字已经在循环节中了
    for(int i=0;i<mod;i++){
        cycle[i]=true;//全部初始化为在循环节中
        degree[(i*i)%mod]++;
    }
    queue<int>q;
    for(int i=0;i<mod;i++){
        if(!degree[i]){
            q.push(i);
        }
    }
    while(!q.empty()){
        int x=q.front();
        q.pop();
        cycle[x]=false;
        if(--degree[(x*x)%mod]==0){
            q.push((x*x)%mod);
        }
    }

    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    build(1,n,1);
    for(int i=1;i<=m;i++){
        int op,l,r;
        op=read(),l=read(),r=read();
        if(op==1){
            update(l,r,1,n,1);
        }
        else{
            printf("%d\n",query(l,r,1,n,1));
        }
    }
    return 0;
}
/*
5 10 233
135 76 183 134 118
1 2 5
1 4 4
2 2 4
2 2 3
1 2 5
1 1 3
1 1 5
1 2 4
2 1 5
1 4 4
*/