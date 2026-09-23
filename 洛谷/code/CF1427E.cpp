// https://www.luogu.com.cn/problem/CF1427E
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;

int len;
int op[MAXN][3];

int x,y,d,px,py;

int val[64];

void exgcd(int a,int b){
    if(b==0){
        d=a;
        x=1;
        y=0;
    }
    else{
        exgcd(b,a%b);
        px=x;
        py=y;
        x=py;
        y=px-py*(a/b);
    }
}

signed main()
{
    int a;
    cin>>a;

    int k=-1;
    int t=a;
    while(t){
        k++;
        t>>=1;
    }

    int z=a;
    while(k){
        ++len;
        op[len][0]=z;
        op[len][1]=z;
        op[len][2]=1;
        z<<=1;
        k--;
    }
    int b=a^z;
    ++len;
    op[len][0]=z;
    op[len][1]=a;
    op[len][2]=2;

    exgcd(a,b);
    int dx=b;
    int dy=a;
    if(x<=0){
        int delta=(dx-x)/dx;
        x+=delta*dx;
        y-=delta*dy;
    }
    else{
        int delta=(x-1)/dx;
        y+=delta*dy;
        x-=delta*dx;
    }

    y=-y;
    if(y&1){
        y+=dy;
        x+=dx;
    }

    val[0]=a;
    for(int i=1;(1ll<<i)<=x;i++){
        val[i]=val[i-1]*2;
        ++len;
        op[len][0]=val[i-1];
        op[len][1]=val[i-1];
        op[len][2]=1;
        if((x>>i)&1){
            ++len;
            op[len][0]=a;
            op[len][1]=val[i];
            op[len][2]=1;
            a+=val[i];
        }
    }

    val[0]=b;
    bool flag=true;
    for(int i=1;(1ll<<i)<=y;i++){
        val[i]=val[i-1]*2;
        ++len;
        op[len][0]=val[i-1];
        op[len][1]=val[i-1];
        op[len][2]=1;
        if(((y>>i)&1)){
            if(flag){
                b=val[i];
                flag=false;
                continue;
            }
            ++len;
            op[len][0]=b;
            op[len][1]=val[i];
            op[len][2]=1;
            b+=val[i];
        }
    }

    ++len;
    op[len][0]=a;
    op[len][1]=b;
    op[len][2]=2;

    cout<<len<<endl;
    for(int i=1;i<=len;i++){
        char c=(op[i][2]==1)?'+':'^';
        cout<<op[i][0]<<' '<<c<<' '<<op[i][1]<<endl;
    }
    return 0;
}