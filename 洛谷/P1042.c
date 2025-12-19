#include<stdio.h>

int f[2]={11,21};
int a[25*2500+10],n=0;

int max(int a,int b){
    return a>b?a:b;
}

int main()
{
    char s;
    while(1){
        scanf("%c",&s);
        if(s=='E')
            break;
        else if(s=='W'){
            a[n++]=1;
        }else if(s=='L'){
            a[n++]=0;
        }
    }
    for(int k=0;k<2;k++){
        int w=0,l=0;
        for(int i=0;i<n;i++){
            w+=a[i];
            l+=1-a[i];
            if(max(w,l)>=f[k]&&abs(w-l)>=2){
                printf("%d:%d\n",w,l);
                w=0,l=0;
            }
        }
        printf("%d:%d\n",w,l);
        printf("\n");
    }
    return 0;
}
