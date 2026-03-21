#include<bits/stdc++.h>
using namespace std;
const int MAXN = 11000000+5;

int n;
char s[MAXN];
char ss[MAXN<<1];
int p[MAXN<<1];

void manacherss(){
    n=2*strlen(s+1)+1;
    ss[0]='#';
    for(int i=1;i<=n/2;i++){
        ss[2*i-1]=s[i];
        ss[2*i]='#';
    }
}

int manacher(){
    manacherss();
    int ans=0;
    for(int i=0,r=0,c=0;i<=n;i++){
        int len=(r>i)?min(r-i,p[2*c-i]):1;
        while(i+len<=n&&i-len>=0&&ss[i+len]==ss[i-len]){
            ++len;
        }

        if(i+len>r){
            r=i+len;
            c=i;
        }
        p[i]=len;
        ans=max(ans,len-1);
    }
    return ans;
}

int main()
{
    scanf("%s",s+1);
    cout<<manacher();
    return 0;
}