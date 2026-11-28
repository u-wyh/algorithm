// https://www.luogu.com.cn/problem/P3127
// 题意：输入干草捆数 N，以及每个干草捆的大小 S_j 和一维坐标 P_j。
// 奶牛朝同一方向连续移动距离 D 后，
// 能撞碎并永久消除路上遇到的大小严格小于 D 的干草捆。
// 若能撞破最左端或最右端草捆逃出，则算成功逃脱；
// 求区间内所有无法逃脱的实数起点总长度。
// 输出一个整数表示无法逃脱的起点位置总长度。
// 数据范围：1 <= N <= 10^5，
// 1 <= S_j, P_j <= 10^9，P_j 互不相同。
// 难度评分：1600（洛谷分级换算）
// 算法标签：双指针、模拟、排序
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

struct node{
    int v,pos;
}nums[MAXN];
int n;
int ans;
bool ok[MAXN];

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

bool cmp(node a,node b){
    return a.pos<b.pos;
}

bool compute(int x){
    int s=nums[x+1].pos-nums[x].pos;
    int l=x,r=x+1;
    while(l>=1&&r<=n){
        bool flag=false;
        if(s>nums[l].v){
            flag=true;
            l--;
            if(ok[l]){
                ok[x]=true;
                return true;
            }
            s+=(nums[l+1].pos-nums[l].pos);
        }
        if(s>nums[r].v){
            flag=true;
            r++;
            if(ok[r-1]){
                ok[x]=true;
                return true;
            }
            s+=(nums[r].pos-nums[r-1].pos);
        }
        if(!flag){
            return false;
        }
    }
    return true;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i].v=read(),nums[i].pos=read();
    }
    sort(nums+1,nums+n+1,cmp);
    ok[0]=true,ok[n]=true;
    for(int i=1;i<n;i++){
        if(!compute(i)){
            ans+=nums[i+1].pos-nums[i].pos;
        }
    }
    cout<<ans<<endl;
    return 0;
}
