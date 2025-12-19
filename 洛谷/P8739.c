#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 100000+5

int cmp(const void *a,const void *b){
    return (*(int *)b-*(int *)a);
}

int main()
{
    int k;
    scanf("%d",&k);
    getchar();
    char s[MAX];
    scanf("%s",s);
    int n=strlen(s);
    //printf("%c %c %c\n",s[0],s[n-2],s[n-1]);
    if(n<k||n%k!=0){
        printf("-1\n");
        return 0;
    }
    int cnt[26],ans=0;
    for(int i=0;i<n/k;i++){
        memset(cnt,0,sizeof(cnt));
        for(int j=0;j<k;j++){
            cnt[s[i+j*(n/k)]-'a']++;
        }
        qsort(cnt,26,sizeof(int),cmp);
        ans+=k-cnt[0];
    }
    printf("%d\n",ans);
    return 0;
}
