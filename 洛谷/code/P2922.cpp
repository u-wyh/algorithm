// https://www.luogu.com.cn/problem/P2922
// 题意：输入截获信息条数 M、暗号条数 N，M 条截获二进制串的前 b_i 位，以及 N 条暗号二进制串的前 c_j 位。
// 对每条暗号 j，统计有多少条截获信息 i 与之匹配，即两者在前 min(b_i, c_j) 位上完全相同（具有相同前缀）。
// 依次计算每条暗号的匹配信息数量。
// 输出共 N 行，第 i 行一个整数表示第 i 个暗号可以匹配的消息数。
// 数据范围：对于 100% 的数据，1 <= M, N <= 50000，1 <= b_i, c_j <= 10000
// 且总位数 sum(b_i) + sum(c_j) <= 5*10^5。
#include<bits/stdc++.h>
// 算法标签：字典树
using namespace std;
struct cow{
    int nex[2],sum,end;
}t[500001];
int a[10001];
inline int read()
{
    int data=0,w=1; char ch=0;
    while(ch!='-' && (ch<'0' || ch>'9')) ch=getchar();
    if(ch=='-') w=-1,ch=getchar();
    while(ch>='0' && ch<='9') data=data*10+ch-'0',ch=getchar();
    return data*w;
}
int main()
{
    ios::sync_with_stdio(false);
    int n,m,js=1;
    memset(t,0,sizeof(t));
    m=read();n=read();
    for (int i=1;i<=m;i++)
    {
        int len;
        len=read();
        for (int j=1;j<=len;j++) a[j]=read();
        int now=1;
        for (int j=1;j<=len;j++)
        {
            if (t[now].nex[a[j]]!=0) now=t[now].nex[a[j]];
            else
            {
                js++;
                t[now].nex[a[j]]=js;
                t[js].nex[1]=t[js].nex[0]=0;
                now=js;
            }
            t[now].sum++;
        }
        t[now].end++;
    }
    for (int i=1;i<=n;i++)
    {
        int len;
        len=read();
        for (int j=1;j<=len;j++) a[j]=read();
        int now=1,ans=0;
        bool flag=true;
        for (int j=1;j<=len;j++)
        {
            if (t[now].nex[a[j]]!=0) now=t[now].nex[a[j]];
            else
            {
                flag=false;
                break;
            }
            ans+=t[now].end;
        }
        if (!flag) cout<<ans<<endl;
        else cout<<ans+t[now].sum-t[now].end<<endl;
    }
    return 0;
}
