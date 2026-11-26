// https://www.luogu.com.cn/problem/P8606
// 题意：输入一行 N 个递增整数表示站在台阶上的小和尚位置（台阶从 1 编号，最后一人位置即为总台阶数）。
// 两人轮流选一个小和尚向上走任意多级（不能越过或落在前面小和尚同一台阶，不能向下走），无法移动者负。
// 求先手必胜的第一步 A B（将 A 位置和尚移到 B），多解输出 A 最小者，无解输出 -1。
// 数据范围：N < 100，台阶总数 < 1000。
// https://www.luogu.com.cn/problem/P8606
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;

int n;
int val[MAXN];
int diff[MAXN];

int main()
{
    while(cin>>val[++n]);
    n--;

    sort(val+1,val+n+1);

    for(int i=2;i<=n;i++){
        diff[i-1]=val[i]-val[i-1]-1; 
    }

    int eor=0;
    for(int i=1;i<=n-1;i+=2){
        eor^=diff[i];
    }

    if(eor==0){
        cout<<-1<<endl;
        return 0;
    }

    for(int i=1;i<n;i++){
        int old=val[i];

        for(int j=old+1;j<val[i+1];j++){
            int d=j-old;
            int neor=eor;

            if((i-1)>=1&&(i-1)%2==1){
                neor^=diff[i-1];
                neor^=(diff[i-1]+d);
            }

            if(i%2==1){
                neor^=diff[i];
                neor^=(diff[i]-d);
            }

            if(neor==0){
                cout<<old<<" "<<j<<endl;
                return 0;
            }
        }
    }

    cout<<-1<<endl;
    return 0;
}