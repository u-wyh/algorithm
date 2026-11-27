// https://onlinejudge.org/external/7/756.pdf
// 题意：多组数据，每组给体力、情绪、智力的峰值日
// p、e、i，以及当前日 d。四项全为 -1 时结束。
// 三个周期依次为 23、28、33 天。
// 输出：每组按 Case k 格式输出 d 之后，
// 距三个峰值下次同一天出现还有多少天。
// 数据范围：0 <= p, e, i, d <= 365。
// 答案至多 21252。
// 算法标签：中国剩余定理、扩展欧几里得
#include<bits/stdc++.h>
using namespace std;

int a[4];
int b[4]={0,23,28,33};
int st;
int d, x, y, px, py;

void exgcd(int a, int b) {
    if (b == 0) {
        d = a;
        x = 1;
        y = 0;
    } else {
        exgcd(b, a % b);
        px = x;
        py = y;
        x = py;
        y = px - py * (a / b);
    }
}

int crt(){
    int lcm=1;
    for(int i=1;i<=3;i++){
        lcm*=b[i];
    }
    int ai, ci, ans = 0;
    for (int i = 1; i <= 3; i++) {
        // ai = lcm / m[i]
        ai = lcm / b[i];
        // ai逆元，在%m[i]意义下的逆元
        exgcd(ai, b[i]);
        // ci = (ri * ai * ai逆元) % lcm
        ci =( a[i]*((ai*x)%lcm))%lcm;
        ans = (ans + ci) % lcm;
    }
    ans=(ans+lcm)%lcm;
    if(ans<=st){
        ans+=((st-ans)/lcm+1)*lcm;
    }
    return ans-st;
}

int main()
{
    int cas=0;
    while(cin>>a[1]>>a[2]>>a[3]>>st){
        if(a[1]==-1){
            break;
        }
        cout<<"Case "<<++cas
            <<": the next triple peak occurs in "
            <<crt()<<" days."<<endl;
    }
    return 0;
}