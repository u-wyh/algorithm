// https://www.luogu.com.cn/problem/P4392
// 题意：给定长度为 n 的序列 a，若长度为 m 的连续子段极差（最大值减最小值）不超过 c 则视为静音
// 按出现顺序输出所有静音子段的起始下标（若无输出 NONE）。
// 数据范围：1 <= n <= 10^6，1 <= m <= 10^4，0 <= c <= 10^4，0 <= a_i <= 10^6。
#include<bits/stdc++.h>
// 算法标签：单调队列、滑动窗口
using namespace std;

int n,m,c;
int maxqueue[10005],minqueue[10005],arr[1000005];
int maxhead=0,maxtail=0,minhead=0,mintail=0;
bool p=false;

int main()
{
    cin>>n>>m>>c;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    for(int i=1;i<=n;i++){
        while(maxhead<maxtail&&i-maxqueue[maxhead]>=m){
            maxhead++;
        }
        while(minhead<mintail&&i-minqueue[minhead]>=m){
            minhead++;
        }
        while(maxhead<maxtail&&arr[maxqueue[maxtail-1]]<=arr[i]){
            maxtail--;
        }
        maxqueue[maxtail++]=i;
        while(minhead<mintail&&arr[minqueue[mintail-1]]>=arr[i]){
            mintail--;
        }
        minqueue[mintail++]=i;
        if(i>=m){
            if(arr[maxqueue[maxhead]]-arr[minqueue[minhead]]<=c){
                cout<<i-m+1<<endl;
                p=true;
            }
        }
    }
    if(!p)
        cout<<"NONE";
    return 0;
}
