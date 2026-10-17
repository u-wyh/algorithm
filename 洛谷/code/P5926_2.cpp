// https://www.luogu.com.cn/problem/P5926
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXB = 405;
const int INF = 1e9;

int n,m;
int val[MAXN];

int blen,bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

int cnt[MAXB];
int numsval[MAXB][MAXB];
int mn[MAXB];

// f[i][j]：第 i 块到第 j 块的最小非零差值
int f[MAXB][MAXB];

// g[k][p]：位置 p 与一侧连续完整块的最小非零差值
int g[MAXB][MAXN];

struct node{
    int pos,val;
};
node nums[MAXN];

bool cmp(const node &a,const node &b){
    return a.val<b.val;
}

// 计算第 s 块的每个元素与第 t 块的贡献
// pre 是已经计算好的相邻状态
void calc(int s,int t,int pre){
    int p=1;

    for(int j=bl[s];j<=br[s];j++){
        int x=nums[j].val;

        // 在第 t 块中寻找 x 的前驱和后继
        while(p<=cnt[t]&&numsval[t][p]<x){
            p++;
        }

        int d=INF;

        // 严格小于 x 的前驱
        if(p>1){
            d=min(d,x-numsval[t][p-1]);
        }

        // 严格大于 x 的后继
        if(p<=cnt[t]){
            int q=p+(numsval[t][p]==x);

            if(q<=cnt[t]){
                d=min(d,numsval[t][q]-x);
            }
        }

        int id=nums[j].pos;

        // 合并之前的完整块贡献
        g[t][id]=min(g[pre][id],d);
    }
}

void prepare(){
    blen=sqrt(n);
    bnum=(n+blen-1)/blen;

    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
        nums[i]={i,val[i]};
    }

    // 分块并排序
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(n,i*blen);

        sort(nums+bl[i],nums+br[i]+1,cmp);

        mn[i]=INF;

        // 对每一块去重，同时计算块内最小差值
        for(int j=bl[i];j<=br[i];j++){
            int x=nums[j].val;

            if(cnt[i]&&numsval[i][cnt[i]]==x){
                continue;
            }

            if(cnt[i]){
                mn[i]=min(mn[i],x-numsval[i][cnt[i]]);
            }

            numsval[i][++cnt[i]]=x;
        }
    }

    // 第一部分：预处理 g
    for(int s=1;s<=bnum;s++){

        // 不包含任何其他完整块
        for(int j=bl[s];j<=br[s];j++){
            g[s][nums[j].pos]=INF;
        }

        // 向右扩展完整块
        for(int t=s+1;t<=bnum;t++){
            calc(s,t,t-1);
        }

        // 向左扩展完整块
        for(int t=s-1;t>=1;t--){
            calc(s,t,t+1);
        }
    }

    // 第二部分：预处理完整块之间的答案 f
    for(int i=1;i<=bnum;i++){
        f[i][i]=mn[i];

        for(int j=i+1;j<=bnum;j++){

            // 已有完整块的答案 + 新块内部的答案
            f[i][j]=min(f[i][j-1],mn[j]);

            // 新块与前面所有完整块之间的贡献
            for(int k=bl[j];k<=br[j];k++){
                int id=nums[k].pos;
                f[i][j]=min(f[i][j],g[i][id]);
            }
        }
    }
}

int solve(int l,int r){
    int lb=bi[l],rb=bi[r];

    int ans=INF;
    int last=-1;

    // 情况一：左右端点在同一个块
    if(lb==rb){
        for(int i=bl[lb];i<=br[lb];i++){
            int id=nums[i].pos;

            if(l<=id&&id<=r){
                int x=nums[i].val;

                if(last!=-1&&last!=x){
                    ans=min(ans,x-last);
                }

                last=x;
            }
        }

        return ans;
    }

    // 情况二：左右端点在不同块
    int x=bl[lb],y=bl[rb];

    // 是否存在中间完整块
    bool full=(lb+1<rb);

    // 完整块内部的答案
    if(full){
        ans=f[lb+1][rb-1];
    }

    // 归并左右两个散块
    while(x<=br[lb]||y<=br[rb]){

        // 过滤不属于询问区间的元素
        while(x<=br[lb]&&nums[x].pos<l){
            x++;
        }

        while(y<=br[rb]&&nums[y].pos>r){
            y++;
        }

        if(x>br[lb]&&y>br[rb]){
            break;
        }

        int cur;

        if(x<=br[lb]&&(y>br[rb]||nums[x].val<=nums[y].val)){
            cur=nums[x].val;

            // 左散块与中间完整块的贡献
            if(full){
                ans=min(ans,g[rb-1][nums[x].pos]);
            }

            x++;
        }
        else{
            cur=nums[y].val;

            // 右散块与中间完整块的贡献
            if(full){
                ans=min(ans,g[lb+1][nums[y].pos]);
            }

            y++;
        }

        // 两个散块之间，以及散块内部的贡献
        if(last!=-1&&last!=cur){
            ans=min(ans,cur-last);
        }

        last=cur;
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>m;

    for(int i=1;i<=n;i++){
        cin>>val[i];
    }

    prepare();

    for(int i=1;i<=m;i++){
        int l,r;
        cin>>l>>r;

        cout<<solve(l,r)<<'\n';
    }

    return 0;
}