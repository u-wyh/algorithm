// https://www.luogu.com.cn/problem/P5854
// 题意：给定 1~n 的排列 p，构建以编号为二叉搜索树关键字、以 p_i 为小根堆关键字的笛卡尔树。
// 输入 n 及排列 p；输出两数分别为 xor_{i=1}^n i*(l_i+1) 和 xor_{i=1}^n i*(r_i+1)。
// 数据范围：1 <= n <= 10^7。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e7+5;

int n;
int val[MAXN];

int ls[MAXN];
int rs[MAXN];
int sta[MAXN];

void compute(){
    int top=0;
    for(int i=1;i<=n;i++){
        int pos=top;

        while(pos>0&&val[sta[pos]]>=val[i]){
            pos--;
        }

        if(pos){
            rs[sta[pos]]=i;
        }

        if(top!=pos){
            ls[i]=sta[pos+1];
        }

        sta[++pos]=i;
        top=pos;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    compute();
    long long ansl=0,ansr=0;
    for(int i=1;i<=n;i++){
        ansl=ansl^(1ll*(ls[i]+1)*i);
        ansr=ansr^(1ll*(rs[i]+1)*i);
    }
    cout<<ansl<<' '<<ansr<<endl;
    return 0;
}