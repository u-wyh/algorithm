// https://www.luogu.com.cn/problem/P3253
// 题意：输入两堆物品个数 N_1, N_2，以及第一堆、第二堆分别从顶到底各物品的互异优先级。
// 每次只能把某堆顶部的物品移动到另一堆顶部，若某堆顶部物品是当前所有未删物品中优先级最高的，可直接将其删除且不计入步数。
// 输出删除全部物品所需的最少移动步数。
// 数据范围：1 <= N_1 + N_2 <= 100000，优先级 <= 10^7。
#include<bits/stdc++.h>
// 算法标签：树状数组、贪心、排序
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int n,m;
int tree[MAXN];
int arr[MAXN];
int temp[MAXN];
map<int,int>M;
int ans=0;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}


int lowbit(int i) {
	return i & -i;
}

void add(int i, int v) {
    while (i <= n+m) {
        tree[i] += v;
        i += lowbit(i);
    }
}

// 1~i范围的累加和
int sum(int i) {
    int ans = 0;
    while (i > 0) {
        ans += tree[i];
        i -= lowbit(i);
    }
    return ans;
}

bool cmp(int a,int b){
    return a>b;
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        arr[n-i+1]=read();
        temp[n-i+1]=arr[n-i+1];
        M[arr[n-i+1]]=n-i+1;
    }
    for(int j=n+1;j<=n+m;j++){
        arr[j]=read();
        temp[j]=arr[j];
        M[arr[j]]=j;
    }
    for(int i=1;i<=(n+m);i++){
        add(i,1);
    }
    sort(temp+1,temp+n+m+1,cmp);
//    for(int i=1;i<=(n+m);i++){
//        cout<<temp[i]<<' '<<M[temp[i]]<<endl;
//    }
//    cout<<endl;
    int l=n;
    for(int i=1;i<=(n+m);i++){
        int pos=M[temp[i]];
        //cout<<' '<<pos<<' ';
        if(pos<=l){
            ans+=sum(l)-sum(pos);
            add(pos,-1);
            l=pos;
        }
        else{
            ans+=sum(pos-1)-sum(l);
            add(pos,-1);
            l=pos-1;
        }
        //cout<<ans<<' '<<endl;
    }
    cout<<ans<<endl;
    return 0;
}
