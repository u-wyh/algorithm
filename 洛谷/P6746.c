#include<stdio.h>

int min(int a,int b){
    return a<b?a:b;
}

int main()
{
    int a,b,c,d;
    scanf("%d %d %d %d",&a,&b,&c,&d);
    if(a==0&&b==0){
        printf("0\n");
    }else if(a*b==0){
        printf("%d\n",d);
    }else if(a==b){
        printf("%d\n",min(c,2*d));
    }else{
        printf("%d\n",min(c+d,2*d));
    }
    return 0;
}
