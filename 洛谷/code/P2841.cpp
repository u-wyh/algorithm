#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;

int n;
bool vis[MAXN];
int pre[MAXN];
int val[MAXN];
queue<int>q;

string divide(string num, int divisor) {
    if (divisor == 1) {
        return num;
    }
    string res = "";
    long long rem = 0;
    for (int i = 0; i < num.size(); i++) {
        rem = rem * 10 + (num[i] - '0');
        if (res.size() > 0 || rem >= divisor) {
            res += (rem / divisor) + '0';
        }
        rem %= divisor;
    }
    if (res.empty()) {
        return "0";
    }
    return res;
}

int main()
{
    cin>>n;
    if(n==1){
        cout<<"1 1"<<endl;
        return 0;
    }
    pre[1]=-1;
    vis[1]=1;
    val[1]=1;
    q.push(1);
    int res=0;
    while(!q.empty()){
        int r=q.front();
        q.pop();

        int r0=(r*10)%n;
        if(!vis[r0]){
            vis[r0]=1;
            val[r0]=0;
            pre[r0]=r;
            if(r0==0){
                break;
            }
            q.push(r0);
        }

        int r1=(r*10+1)%n;
        if(!vis[r1]){
            vis[r1]=1;
            val[r1]=1;
            pre[r1]=r;
            if(r1==0){
                break;
            }
            q.push(r1);
        }

    }
    string s="";
    while(res!=-1){
        s+=('0'+val[res]);
        res=pre[res];
    }
    reverse(s.begin(),s.end());
    string b=divide(s,n);
    cout<<b<<' '<<s<<endl;
    return 0;
}