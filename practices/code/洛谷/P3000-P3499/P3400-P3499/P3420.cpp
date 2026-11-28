// https://www.luogu.com.cn/problem/P3420
// 题意：输入存钱罐数量 N（编号 1..N），
// 接下来 N 行第 i 行给出第 i 个存钱罐对应的钥匙所在的存钱罐编号 x。
// 每个存钱罐要么用对应钥匙打开，要么直接砸开；
// 要打开全部 N 个存钱罐，求最少需要砸开几个。
// 输出一个整数，表示最少需要破坏的存钱罐数量。
// 数据范围：1 <= N <= 10^6，1 <= x <= N。
//P3420
// 难度评分：1300（洛谷分级换算）
// 算法标签：并查集
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000005;
int fa[MAXN];
int ans=0,n;

void build(){
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
}

int find(int i){
    if (i != fa[i]){
        fa[i] = find(fa[i]);
    }
    return fa[i];
}
void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
    }
    else
        ans++;
}

int main(){
	cin>>n;
	build();
	for(int i=1;i<=n;i++){
        int a;
        cin>>a;
        un(a,i);
	}
	cout<<ans;
	return 0;
}
