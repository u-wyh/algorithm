#include<bits/stdc++.h>
using namespace std;
const int MAXN = 11000005;

int n;
char s[MAXN];
char ss[MAXN<<1];
int p[MAXN<<1];

void manacherss(){
    n=strlen(s+1)*2+1;
    for(int i=1,j=1;i<=n;i++){
        ss[i]=(i&1)?'#':s[j++];
    }
}

int manacher(){
    manacherss();
    int maxans=0;
    int r=1,c=1,len=0;
    for(int i=1;i<=n;i++){
        len=(r>i)?min(p[2*c-i],r-i):1;
        while(i+len<=n&&i-len>=1&&ss[i+len]==ss[i-len]){
            len++;
        }
        if(i+len>r){
            r=i+len;
            c=i;
        }
        maxans=max(maxans,len);
        p[i]=len;
    }
    return maxans-1;
}

int main()
{
    scanf("%s",s+1);
    cout<<manacher();
    return 0;
}