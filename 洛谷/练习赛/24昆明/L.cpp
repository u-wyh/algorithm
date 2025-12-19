#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int n,m;
int a[MAXN];
int b[MAXN];
int attack;
int boom;
int lt,rt;

bool compute1(){
    int pre=boom;
    while(rt<=m){
        if(b[rt]<=boom){
            boom++;
            rt++;
        }
        else{
            break;
        }
    }
    return boom!=pre;
}

bool compute2(){
    int pre=boom;
    while(lt<=n){
        if(a[lt]<=boom){
            boom++;
            lt++;
        }
        else{
            break;
        }
    }
    return boom!=pre;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m;
        attack=0,boom=0;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        for(int i=1;i<=m;i++){
            cin>>b[i];
        }
        lt=1,rt=1;
        sort(a+1,a+n+1);
        sort(b+1,b+m+1);
        if(a[1]==1){
            attack++;
            boom++;
            lt=2;
        }
        for(int i=1;i<=n;i++){
            if(a[i]>1){
                a[i]--;
                attack++;
            }
        }
        while(true){
            // 开始爆炸环节
            int flag1=compute1();
            int flag2=compute2();
            cout<<flag1<<' '<<flag2<<endl;
            while(flag1||flag2){
                flag1=compute1();
                flag2=compute2();
                cout<<flag1<<' '<<flag2<<endl;
            }
            // 引爆b的爆炸环节
            int need=b[rt]-boom;
            if(need>attack){
                break;
            }
            else{
                rt++;
                boom++;
                attack-=need;
            }
            if(rt==m+1){
                break;
            }
        }
        if(rt==m+1){
            cout<<"Yes"<<endl;
        }
        else{
            cout<<"No"<<endl;
        }
    }
    return 0;
}
/*
5 3
3 4 5 6 7
1 5 7
*/