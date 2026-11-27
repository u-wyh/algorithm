// https://www.luogu.com.cn/problem/P3615
// 题意：输入时间限制 N、串段数 M，
// 以及 M 组字符串 S_i 与重复次数 K_i，
// 按顺序拼接成长度为 2N 的男女生（M/F）排队序列。
// 有 1 个女生专用厕位和 1 个男女共用厕位，每人如厕耗时 1 分钟：
// 共用厕位空时队头可进（但女厕也空时女生优先进女厕）
// 仅女厕空时队列最靠前的女生可提前越队去女厕。
// 允许重排原队列使所有人能在 N 分钟内如厕完，
// 每个人的不满度等于其在原队列后退的步数，输出最大不满度的最小值；
// 若无论如何无法完成则输出 -1。
// 数据范围：1 <= N, K_i <= 10^18，
// 1 <= M <= 100000，sum |S_i| <= 200000。
// 算法标签：贪心、后缀和
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int n,m;
string s[MAXN];
int times[MAXN];

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>s[i]>>times[i];
    }
    int all=0;
    int ans=1;
    for(int i=m;i>=1;i--){
        int len=s[i].length();
        int t=times[i];

        int now=0;
        int maxx=0;
        for(int j=len-1;j>=0;j--){
            if(s[i][j]=='F'){
                now--;
            }
            else{
                now++;
            }
            maxx=max(maxx,now);
        }

        if(now>0){
            ans=max(ans,all+(t-1)*now+maxx);
        }
        else{
            ans=max(ans,maxx+all);
        }
        all+=t*now;
    }
    if(all>0){
        cout<<-1<<endl;
    }
    else{
        cout<<(ans-1)<<endl;
    }
    return 0;
}