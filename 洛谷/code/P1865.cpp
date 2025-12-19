#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int prime[MAXN / 2 + 1];
int visit[MAXN + 1];
int sum[MAXN];

// 欧拉筛统计0 ~ n范围内的质数个数
// 时间复杂度O(n)
void euler(int n) {
    int cnt = 0;

    for (int i = 2; i <= n; i++) {
        if (!visit[i]) {
            prime[cnt++] = i;
        }

        for (int j = 0; j < cnt && i * prime[j] <= n; j++) {
            visit[i * prime[j]] = 1; // 标记为合数
            if (i % prime[j] == 0) {
                break; // 每个合数只被其最小的质因数筛去一次
            }
        }
    }
}

int main() {
    int  m,n ;
    cin>>m>>n;
    euler(n);
    visit[1]=1;
    visit[0]=1;
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+1-visit[i];
        //printf("%3d",sum[i]);
    }
    //cout<<endl;
    for(int i=1,l,r;i<=m;i++){
        cin>>l>>r;
        if(l<=0||r>n){
            cout<<"Crossing the line"<<endl;
        }
        else{
            cout<<sum[r]-sum[l-1]<<endl;
        }
    }
    return 0;
}

