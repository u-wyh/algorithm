#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;

int pos[MAXN];

signed main() 
{
    int T;
    cin>>T;
    while(T--){
        string s;
        cin>>s;
        int n=s.size();
        int a=0,b=0;
        for(int i=0;i<n;i++){
            if(s[i]=='0'){
                a++;
            } 
            else{
                pos[b]=i;
                b++;
            }
        }

        if(a==0||b==0){
            cout<<0<<endl;
            continue;
        }
        if((a*b)%2!=0){
            cout<<-1<<endl;
            continue;
        }

        int need=(a*b)/2;
        int now=0;
        for (int i=0;i<b;i++) {
            now+=pos[i]-i;
        }

        if (now==need) {
            cout<<0<<endl;
            continue;
        }

        need=need-now;
        int cost=0;
        if (need>0) {
            int up=0;
            for (int i=0;i<b;i++) {
                up+=n-1-pos[i];
            }
            if (need<=up) {
                cost=need;
            } else {
                cost=need*2-up;
            }
        } else {
            need=-need;
            int down=0;
            for (int i=0;i<b;i++) {
                down+=pos[i];
            }
            if (need<=down) {
                cost=need;
            } else {
                cost=need*2-down;
            }
        }
        cout<<cost<<endl;
    }
    return 0;
}