#include<bits/stdc++.h>
using namespace std;
const int MAXN = 20005;

int cnt;
int visit[MAXN];
int prime[10005];

bool ok[MAXN];
int step[MAXN];
bool appear[MAXN];

void euler() {
    for (int i = 2; i <= 20000; i++) {
        if (!visit[i]) {
            prime[cnt++] = i;
        }
        for (int j = 0; j < cnt && i * prime[j] <= 20000; j++) {
            //每一次从最小的质数开始
            visit[i * prime[j]] = 1; // 标记为合数
            if (i % prime[j] == 0) {
                break; // 每个合数只被其最小的质因数筛去一次
            }
        }
    }
}

void build(){
    step[0]=step[1]=0;
    for(int i=2;i<=20000;i++){
        memset(appear,false,sizeof(appear));
        bool flag=false;
        for(int j=1;j<=cnt;j++){
            if(prime[j]>i){
                break;
            }
            if(!ok[i-prime[j]]){
                flag=true;
                appear[step[i-prime[j]]]=true;
            }
        }
        ok[i]=flag;
        for(int i=0;i<=20000;i++){

        }
    }
}

int main()
{
    euler();
    build();
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        if(ok[n]){
            cout<<step[n]<<endl;
        }
        else{
            cout<<-1<<endl;
        }
    }
    return 0;
}