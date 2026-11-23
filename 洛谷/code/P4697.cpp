// https://www.luogu.com.cn/problem/P4697
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n;
double x[MAXN];
double r[MAXN];
double ans[MAXN];

int sta[MAXN];
int top;

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>x[i]>>r[i];
    }

    for(int i=1;i<=n;i++){
        ans[i]=r[i];
        while(top){
            int j=sta[top];
            ans[i]=min(ans[i],(x[i]-x[j])*(x[i]-x[j])/(4*ans[j]));
            if(ans[i]>ans[j]){
                top--;
            }
            else{
                break;
            }
        }
        sta[++top]=i;
    }

    cout<<fixed<<setprecision(4);
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}