#include<bits/stdc++.h>
using namespace std;

int cnt[4];
int c[10];

void print(int op){
    if(op==0){
        printf("R\n");
    }
    else if(op==1){
        printf("G\n");
    }
    else{
        printf("B\n");
    }
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--){
        getchar();
        cnt[0]=0;
        cnt[1]=0;
        cnt[2]=0;
        for(int i=1;i<=8;i++){
            char op;
            scanf("%c",&op);
            if(op=='R'){
                cnt[0]++;
                c[i]=0;
            }
            else if(op=='G'){
                cnt[1]++;
                c[i]=1;
            }
            else{
                cnt[2]++;
                c[i]=2;
            }
        }
        if(c[1]!=c[5]){
            if(cnt[c[1]]>cnt[c[5]]){
                print(c[1]);
            }
            else if(cnt[c[5]]>cnt[c[1]]){
                print(c[5]);
            }
            else{
                printf("N\n");
            }
        }
        else{
            print(c[1]);
        }
    }
    return 0;
}