#include<bits/stdc++.h>
using namespace std;

int n,maxlen,minlen=100,a[55],b[70],s=0,c=1;
//a数组统计的实际上是词频  b数组统计的实际上是可以选择的木棍长度

void dfs(int len,int deep,int x,int pos){
    //参数说明：len每一根木棍的目标长度 deep已经完成了几根木棍(切割后的木棍) len目前这根木棍已有的长度 pos从哪里开始寻找木棍
    if(deep==n){
        //如果说n根木棍都已经被加上了  说明这个长度是可以的
        cout<<len;
        exit(0);
        //因为递归层数太多 所以直接结束程序
    }
    if(x==len){
        //如果说x==len 说明复原了一根之前的木棍
        //那么x=0 继续从最大的木棍长度开始找
        x=0;
        pos=maxlen;
    }
    for(int i=pos;i>=minlen;i--){
        if(!a[i]){
            //如果说这样长度的木棍已经没有了 那么继续下一个长度
            continue;
        }
        a[i]--;
        //使用这样长度的木棍  并且数量减去1
        dfs(len,deep+1,x+i,min(len-(x+i),i));
        //继续搜索  目前的长度是之前的x加上i  切割后的木棍完成数量加1
        //我们继续从大到小搜索有哪些木棍可以使用
        //首先  这个值必须小于len-(x+i)  要不然也是没有任何效果的
        //其次  如果说len-(x+i)超过了可以使用的最大长度  那么就选目前的最大长度
        a[i]++;
        //复原
        if(x==0||x+i==len)
            break;
        //x==0  说明这个长度的根本不行
        //x+i==len  说明这根切割前的木棍已经完成  不用向下寻找更短的木棍了
    }
    return ;
}

int main()
{
    cin>>n;
    for(int i=1,x;i<=n;i++){
        cin>>x;
        maxlen=max(maxlen,x);
        //统计最大值
        minlen=min(minlen,x);
        //统计最小值
        a[x]++;
        //统计词频
        s+=x;
        //计算总和
    }
    for(int i=maxlen;i<=s/2;i++){
        if(s%i==0){
            b[c++]=i;
        }
    }
//    for(int i=1;i<c;i++)
//        cout<<b[i]<<' ';
    for(int i=1;i<c;i++){
        dfs(b[i],0,0,maxlen);
        //检查每一个可以的长度是否符合题目要求
        //从小到大检测  如果可以  直接输出并结束程序
        //否则就说明只有总长度是可以的
    }
    cout<<s;
    return 0;
}
