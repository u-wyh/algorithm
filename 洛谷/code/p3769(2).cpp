#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e6+5;
const int BASE = 31;

int n;
string s;
long long p[MAXN];
long long h[MAXN];
int ans;

void build(const string& str) {
    p[0] = 1;
    for (int j = 1; j < MAXN; ++j) {
        p[j] = p[j - 1] * BASE;
    }
    h[0] = str[0] - 'A' + 1;
    for (int j = 1; j < str.length()+1; ++j) {
        h[j] = h[j - 1] * BASE + str[j] - 'A' + 1;
    }
}

// 范围是s[l,r]，左闭右闭
long long getHash(int l, int r) {
    long long ans = h[r];
    if (l > 0) {
        ans -= h[l - 1] * p[r - l+1];
    }
    return ans;
}

long long rehash(int l,int r,int pos){ //在[l, r]中删去pos重新hash
	return getHash(l,pos-1)*p[r-pos]+getHash(pos+1,r);
}

int main()
{
    cin>>n>>s;
    build(s);
    if(n%2==0){
        cout<<"NOT POSSIBLE"<<endl;
        return 0;
    }
    long long val1=getHash(0,n/2-1);
    long long val2=getHash(n/2+1,n-1);
    //cout<<val1<<' '<<val2<<endl;
    string str1,str2;
    for(int i=0;i<n;i++){
        if(i<=n/2){
            long long val=rehash(0,n/2,i);
            if(val==val2){
                //cout<<666<<' '<<i<<endl;
                ans=1;
                str1=s.substr(n/2+1,n/2);
            }
        }
        else{
            long long val=rehash(n/2,n-1,i);
            if(val==val1){
                //cout<<777<<' '<<i<<endl;
                if(ans>=1){
                    ans=2;
                }
                str2=s.substr(0,n/2);
            }
        }
    }
    if(ans>=2&&str1!=str2){
        cout<<"NOT UNIQUE"<<endl;
        return 0;
    }
    if(ans==0){
        cout<<"NOT POSSIBLE"<<endl;
        return 0;
    }
    cout<<str1<<endl;
    return 0;
}
