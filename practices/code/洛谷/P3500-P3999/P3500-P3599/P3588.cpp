// https://www.luogu.com.cn/problem/P3588
// 题意：输入序列长度 n、已知元素数 s、区间信息数 m，
// 接下来 s 组 (p_i, d_i)（p_i 递增）
// 表示 a_{p_i} = d_i；
// 再输入 m 条信息，
// 每条给出 l_i, r_i, k_i 及 k_i 个位置
// x_1..x_{k_i}
// 表示 [l_i, r_i] 内这 k_i
// 个位置的值均严格大于区间内其余位置的值。
// 构造一个各项均在 [1, 10^9] 内的正整数序列 a。
// 若无解输出 NIE；否则第一行输出 TAK，第二行输出 n 个正整数。
// 数据范围：1 <= s <= n <= 10^5，
// 1 <= m <= 2*10^5，1 <= l_i < r_i <= n
// 1 <= k_i <= r_i - l_i，
// sum(k_i) <= 3*10^5，1 <= a_i <= 10^9。
// 难度评分：2500（洛谷分级换算）
// 算法标签：线段树优化建图、拓扑排序
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 30*MAXN;
const int INF = 1e9;

int n,s,m;
int nodecnt;
int in[MAXM];

int val[MAXM];
bool ok[MAXM];

int tmp[MAXN];

int root;
int ls[MAXM];
int rs[MAXM];

int head[MAXM];
int nxt[MAXM<<2];
int to[MAXM<<2];
int weight[MAXM<<2];
int cnt=1;

struct point{
    int pos,val;
};
point nums[MAXN];

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

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    in[v]++;
    head[u]=cnt++;
}

int build(int l,int r){
    if(l==r){
        return l;
    }
    else{
        int now=++nodecnt;
        int mid=(l+r)>>1;
        ls[now]=build(l,mid);
        rs[now]=build(mid+1,r);
        addedge(now,ls[now],0);
        addedge(now,rs[now],0);
        return now;
    }
}

bool cmp(point a,point b){
    return a.val<b.val;
}

int merge(int a,int b){
    if(a==0||b==0){
        return a+b;
    }
    int now=++nodecnt;
    addedge(now,a,0);
    addedge(now,b,0);
    return now;
}

int query(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl>jobr){
        return jobv;
    }
    if(jobl<=l&&r<=jobr){
        return merge(jobv,i);
    }
    else{
        int mid=(l+r)>>1;
        if(jobl<=mid&&jobr>mid){
            return merge(query(jobl,jobr,jobv,l,mid,ls[i]),query(jobl,jobr,jobv,mid+1,r,rs[i]));
        }
        else if(jobl<=mid){
            return query(jobl,jobr,jobv,l,mid,ls[i]);
        }
        else{
            return query(jobl,jobr,jobv,mid+1,r,rs[i]);
        }
    }
}

int main()
{
    n=read(),s=read(),m=read();
    nodecnt=n;
    root=build(1,n);
    for(int i=1;i<=s;i++){
        nums[i].pos=read(),nums[i].val=read();
        val[nums[i].pos]=nums[i].val;
        ok[nums[i].pos]=true;
    }
    sort(nums+1,nums+s+1,cmp);
    int st=0;
    int now=0;
    for(int i=2;i<=s;i++){
        while(st+1<i&&nums[st+1].val<nums[i].val){
            st++;
            now=merge(now,nums[st].pos);
        }
        if(now){
            addedge(nums[i].pos,now,1);
        }
    }
    while(m--){
        int now=0;
        int l,r,k;
        l=read(),r=read(),k=read();
        for(int i=1;i<=k;i++){
            tmp[i]=read();
        }
        int lt=l;
        for(int i=1;i<=k;i++){
            now=query(lt,tmp[i]-1,now,1,n,root);
            lt=tmp[i]+1;
        }
        if(lt<=r){
            now=query(lt,r,now,1,n,root);
        }
        for(int i=1;i<=k;i++){
            addedge(tmp[i],now,1);
        }
    }

    bool flag=false;
    queue<int>q;
    for(int i=1;i<=nodecnt;i++){
        if(!ok[i]){
            val[i]=INF;
        }
        if(in[i]==0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            in[v]--;
            int w=val[u]-weight[i];
            if(ok[v]){
                if(val[v]>w){
                    flag=true;
                    break;
                }
            }
            else{
                val[v]=min(val[v],w);
            }
            if(in[v]==0){
                q.push(v);
            }
        }
        if(flag){
            break;
        }
    }
    for(int i=1;i<=nodecnt;i++){
        if(in[i]){
            flag=true;
            break;
        }
        if(val[i]<=0){
            flag=true;
            break;
        }
    }
    if(flag){
        printf("NIE\n");
    }
    else{
        printf("TAK\n");
        for(int i=1;i<=n;i++){
            printf("%d ",val[i]);
        }
    }
    return 0;
}