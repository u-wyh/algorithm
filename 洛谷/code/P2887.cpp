// https://www.luogu.com.cn/problem/P2887
// 题意：输入奶牛数 C、防晒霜种类数 L，每头牛可接受的阳光强度范围 [minSPF[i], maxSPF[i]]
// 以及每种防晒霜的固定强度 SPF[i] 和瓶数 cover[i]。
// 每头牛最多涂一瓶防晒霜，涂后接收到的阳光强度稳定为 SPF[i]，须落在该牛的区间内才能满足该牛。
// 合理分配防晒霜，最大化能够满足的奶牛数量。
// 输出一个整数，表示最多能满足日光浴的奶牛数目。
// 数据范围：对于 100% 的数据，1 <= C, L <= 2500，1 <= minSPF[i] <= maxSPF[i] <= 1000
// 1 <= SPF[i] <= 1000，1 <= cover[i] <= 2500。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2505;

struct node{
    int l,r;
}nums[MAXN];
int n,m;
struct point{
    int val,num;
}arr[MAXN];

bool cmp(node a,node b){
    return a.r<b.r;
}

bool cmp1(point a,point b){
    return a.val<b.val;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>nums[i].l>>nums[i].r;
    }
    sort(nums+1,nums+n+1,cmp);
    for(int i=1;i<=m;i++){
        cin>>arr[i].val>>arr[i].num;
    }
    sort(arr+1,arr+m+1,cmp1);
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(arr[j].num>0&&arr[j].val<=nums[i].r&&arr[j].val>=nums[i].l){
                arr[j].num--;
                ans++;
                break;
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
