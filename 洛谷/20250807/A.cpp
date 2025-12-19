#include<bits/stdc++.h>
using namespace std;
#define int __int128

int n;
int s[100];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

void write(int x)
{
    if(x<0)
        putchar('-'),x=-x;
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return;
}

signed main()
{
    int T=read();
    while(T--){
        int n=read();
        if(n<0){
            n*=-1;
            int len=0;
            while(n){
                s[++len]=n%10;
                n/=10;
            }
            int pos=0;
            for(int i=len;i>=1;i--){
                if(s[i]>=2){
                    pos=i;
                    break;
                }
            }
            for(int i=len;i>pos;i--){
                n=n*10+s[i];
            }
            n=n*10+1;
            for(int i=pos;i>=1;i--){
                n=n*10+s[i];
            }
            n*=-1;
            write(n);
        }
        else if(n==0){
            n=10;
            write(n);
        }
        else{
            int len=0;
            while(n){
                s[++len]=n%10;
                n/=10;
            }
            int pos=0;
            for(int i=len;i>=1;i--){
                if(s[i]==0){
                    pos=i;
                    break;
                }
            }
            for(int i=len;i>pos;i--){
                n=n*10+s[i];
            }
            n=n*10+1;
            for(int i=pos;i>=1;i--){
                n=n*10+s[i];
            }
            write(n);
        }
        cout<<endl;
    }
    return 0;
}