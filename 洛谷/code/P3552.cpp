// https://www.luogu.com.cn/problem/P3552
// 题意：输入二进制位数 n 和禁用串个数 k，两个 n 位 01 串 x, y（均不在禁用串中），以及 k 个禁用的 n 位 01 串。
// 任意两个合法（非禁用）的 n 位 01 串若恰有一位不同则有直接道路相连，判断能否从 x 走到 y。
// 可行输出 TAK，否则输出 NIE。
// 数据范围：1 <= n <= 60，0 <= k <= 10^6，k <= 2^n - 1，n*k <= 5*10^6。
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 65;
const int MAXM = 1e6+5;

int n,m;
char s[MAXN];
int sorted[MAXM];
int st,en;

unordered_set<int>unset;

// bool find(int val){
//     int l=1,r=m,ans=m+1;
//     while(l<r){
//         int mid=(l+r)>>1;
//         if(sorted[mid]>=val){
//             ans=mid;
//             l=mid-1;
//         }
//         else{
//             r=mid-1;
//         }
//     }
//     if(sorted[ans]!=val){
//         return false;
//     }
//     else{
//         return true;
//     }
// }

bool bfs(int st,int en){
    unset.clear();
    for(int i=1;i<=m;i++){
        unset.insert(sorted[i]);
    }

    int cnt=1;
    int limit=n*m;

    cnt++;
    queue<int>q;
    q.push(st);
    unset.insert(st);
    while(!q.empty()){
        int u=q.front();
        q.pop();

        for(int i=0;i<n;i++){
            int v=u^(1ll<<i);
            if(unset.find(v)==unset.end()){
                unset.insert(v);
                q.push(v);
                cnt++;

                if(v==en){
                    return true;
                }
            }
        }
        if(cnt>limit){
            return true;
        }
    }
    return false;
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>s[i];
        st+=(s[i]-'0')*(1ll<<(n-i));
    }
    for(int i=1;i<=n;i++){
        cin>>s[i];
        en+=(s[i]-'0')*(1ll<<(n-i));
    }

    for(int i=1;i<=m;i++){
        int val=0;
        for(int j=1;j<=n;j++){
            cin>>s[j];
            val+=(s[j]-'0')*(1ll<<(n-j));
        }
        sorted[i]=val;
    }
    // sort(sorted+1,sorted+m+1);

    if(bfs(st,en)&&bfs(en,st)){
        cout<<"TAK"<<endl;
    }
    else{
        cout<<"NIE"<<endl;
    }
    return 0;
}