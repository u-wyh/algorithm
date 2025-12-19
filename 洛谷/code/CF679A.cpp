#include<bits/stdc++.h>
using namespace std;

int prime[]={2,  3,  4,  5,  7,  9,  11, 13, 17, 19, 23, 25, 29, 31, 37, 41, 43, 47, 49};
char s[4];

int main()
{
    int cnt=0;
    for(int i:prime){
        printf("%d\n",i);
        fflush(stdout);
        scanf("%s",s);
        if(s[0]=='y'){
            cnt++;
            if(cnt==2){
                printf("composite");
                return 0;
            }
        }
    }
    printf("prime");
    return 0;
}