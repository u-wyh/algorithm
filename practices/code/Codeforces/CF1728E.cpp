// https://codeforces.com/problemset/problem/1728/E
// 题意：给 n 道菜用红、黑胡椒时各自的美味度，
// 以及 m 家店里两种胡椒每包各能调味的菜数 x_j、y_j。
// 每次只在一家店买整包，每道菜选一种胡椒，不留剩余。
// 输出：对每家店求最大总美味度，无可行方案输出 -1。
// 数据范围：1 <= n, m <= 3*10^5，
// 1 <= a_i, b_i <= 10^9，
// 1 <= x_j, y_j <= n。
// 难度评分：2300（CF 官方）
// 算法标签：扩展欧几里得、贪心、排序
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 3e5+5;
const int INF = 1e18;

int n,m;
struct node{
    int a,b,d;
};
node nums[MAXN];
int sum[MAXN];
int id;

int x,y,d,px,py;

void exgcd(int a,int b){
    if(b==0){
        d=a;
        x=1;
        y=0;
    }
    else{
        exgcd(b,a%b);
        px=x;
        py=y;
        x=py;
        y=px-py*(a/b);
    }
}

bool cmp(node &a,node &b){
    return a.d>b.d;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    while(cin>>n){
        for(int i=1;i<=n;i++){
            cin>>nums[i].a>>nums[i].b;
            nums[i].d=nums[i].b-nums[i].a;
        }
        int base=0;
        sort(nums+1,nums+n+1,cmp);
        for(int i=1;i<=n;i++){
            sum[i]=sum[i-1]+nums[i].d;
            base+=nums[i].a;
            if(id==0&&nums[i].d<0){
                id=i;
            }
        }
        cin>>m;
        for(int i=1;i<=m;i++){
            int a,b;
            cin>>a>>b;
            exgcd(a,b);
            if(n%d!=0){
                cout<<-1<<endl;
            }
            else{
                int dx=b/d;
                int dy=a/d;
                x=n/d*x;
                y=n/d*y;
                if(x<0){
                    int delta=(dx-x-1)/dx;
                    x+=delta*dx;
                    y-=delta*dy;
                }
                else{
                    int delta=x/dx;
                    x-=delta*dx;
                    y+=delta*dy;
                }

                if(y<0){
                    cout<<-1<<endl;
                }
                else{
                    int ans=-INF;
                    int step=a/d*b;
                    int limit=b*y;

                    int target;
                    if(id!=0){
                        target=id-1;
                    }
                    else{
                        target=n;
                    }
                    if(target>=limit){
                        ans=max(ans,base+sum[limit]);
                    }
                    else{
                        int delta=(limit-target)/step;
                        int k=limit-delta*step;
                        ans=max(ans,base+sum[k]);

                        if(k-step>=0){
                            ans=max(ans,base+sum[k-step]);
                        }
                    }

                    cout<<ans<<endl;
                }
            }
        }
    }
    return 0;
}