#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
char s[MAXN];
char t[MAXN];

int len1,len2;
int s1[MAXN];
int t1[MAXN];
int cnt1,cnt2;
int b1[MAXN];
int b2[MAXN];
int suma[MAXN];
int sumc[MAXN];

int main()
{
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d %s %s",&n,s+1,t+1);
        len1=0,len2=0;
        cnt1=0,cnt2=0;
        for(int i=1;i<=n;i++){
            if(s[i]=='b'){
                b1[++cnt1]=len1;
            }
            else{
                s1[++len1]=s[i]-'a'+1;
            }
        }
        for(int i=1;i<=n;i++){
            if(t[i]=='b'){
                b2[++cnt2]=len2;
            }
            else{
                t1[++len2]=t[i]-'a'+1;
            }
        }

        if(len1!=len2){
            cout<<"NO"<<endl;
            continue;
        }
        bool flag=false;
        for(int i=1;i<=len1;i++){
            if(s1[i]!=t1[i]){
                flag=true;
                break;
            }
        }
        if(flag){
            // cout<<777<<endl;
            cout<<"NO"<<endl;
            continue;
        }

        for(int i=1;i<=len1;i++){
            if(s1[i]==1){
                suma[i]=suma[i-1]+1;
                sumc[i]=sumc[i-1];
            }
            else{
                suma[i]=suma[i-1];
                sumc[i]=sumc[i-1]+1;
            }
        }

        for(int i=1;i<=cnt1;i++){
            if(b1[i]<b2[i]){
                if((b2[i]-b1[i])!=(sumc[b2[i]]-sumc[b1[i]])){
                    flag=true;
                    break;
                }
            }
            else if(b1[i]>b2[i]){
                if((b1[i]-b2[i])!=(suma[b1[i]]-suma[b2[i]])){
                    flag=true;
                    break;
                }
            }
        }
        if(flag){
            cout<<"NO"<<endl;
        }
        else{
            cout<<"YES"<<endl;
        }
    }
    return 0;
}