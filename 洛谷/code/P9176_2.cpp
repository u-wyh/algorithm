// https://www.luogu.com.cn/problem/P9176
// 题意：体育课共 n 次事件，每次有 a_i 个身高为 v_i 的学生进入体育馆。
// 每次事件后所有学生按身高升序排列，输出站在正中间的学生的身高（若总人数为偶数，取中间两人中较矮的那个）。
// 数据范围：1 <= n <= 200000，1 <= v_i, a_i <= 10^9。
#include <bits/stdc++.h>
#define N 200001
#define int long long//十年 OI 一场空
using namespace std;
int n,sum;
int v[N],a[N],b[N],c[N];
//树状数组
void add(int x,int k){
    for (int i=x;i<=n;i+=i&(-i)){
        c[i]+=k;
    }
}
int qry(int x){
    int cnt=0;
    for (int i=x;i;i-=i&(-i)){
        cnt+=c[i];
    }
    return cnt;
}
int bin(){
    int l=1,r=n;
    while (l<=r){
        int mid=(l+r)>>1;
        if (qry(mid)>=(sum+1)/2){
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
    return l;
}
signed main(){
    cin>>n;
    for (int i=1;i<=n;i++){
        cin>>v[i]>>a[i];
        b[i]=v[i];
    }
    sort(b+1,b+n+1);
    for (int i=1;i<=n;i++){
        v[i]=lower_bound(b+1,b+n+1,v[i])-b;//离散化
        sum+=a[i];//更新当前人数
        add(v[i],a[i]);//维护前缀和
        cout<<b[bin()]<<endl;//注意二分的答案是离散化后的，需要还原
    }
    return 0;
}
