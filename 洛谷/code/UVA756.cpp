// https://www.luogu.com.cn/problem/UVA756
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