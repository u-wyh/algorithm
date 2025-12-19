#include<stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    getchar();
    char s[8*n];
    scanf("%s",s);
    //printf("%c",s[1]);
    int cnt=0;
    for(int i=0;i<8*n;i++){
        if(s[i]=='1')
            cnt++;
    }
    if(cnt<3*n||cnt>6*n){
        printf("NIE\n");
        return 0;
    }
    int x[4]={0,0,0,0};
    x[3]=(cnt-3*n)/3;
    x[cnt%3]=1;
    x[0]=n-x[1]-x[2]-x[3];
    while(x[0]--)
        printf("a");
    while(x[1]--)
        printf("c");
    while(x[2]--)
        printf("g");
    while(x[3]--)
        printf("o");
    return 0;
}
