#include<stdio.h>
#include<string.h>

#define MAX 100000+5

int ans=0;
int size=0,len;
char str[MAX];

int main()
{
    scanf("%s",str);
    len=strlen(str);
    for(int i=0;i<len;i++){
        if(str[i]=='(')
            size++;
        else{
            if(size==0){
                ans++;
                size++;
            }
            else{
                size--;
            }
        }
    }
    printf("%d\n",ans+size/2);
    return 0;
}
