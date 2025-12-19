#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;
const int MAXB = 27;

int fa[MAXB];
char s1[MAXN];
char s2[MAXN];
char s3[MAXN];

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
    }
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        scanf("%s %s %s",s1+1,s2+1,s3+1);
        int len1=strlen(s1+1);
        int len2=strlen(s2+1);
        int len3=strlen(s3+1);
        if(len1==len2&&len2==len3){
            for(int i=1;i<=26;i++){
                fa[i]=i;
            }
            for(int i=1;i<=len1;i++){
                un(s1[i]-'a'+1,s2[i]-'a'+1);
            }
            bool flag=false;
            for(int i=1;i<=len1;i++){
                int fx=find(s3[i]-'a'+1);
                int fy=find(s1[i]-'a'+1);
                if(fx!=fy){
                    flag=true;
                    break;
                }
            }
            if(flag){
                cout<<"YES"<<endl;
            }
            else{
                cout<<"NO"<<endl;
            }
        }
        else{
            if(len1==len2){
                cout<<"YES"<<endl;
            }
            else{
                cout<<"NO"<<endl;
            }
        }
    }
    return 0;
}