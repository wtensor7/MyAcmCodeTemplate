//Tykoy 2010 Awkward Lights
//二进制的高斯消元，利用bitset优化
#include<cstdio>
#include<cstring>
#include<bitset>
using namespace std;

bitset<630> f[626],tm;
int a[30][30];
int n,m,d,s;
int ab(int x) {return x<0?-x:x;  }
void input()
{
    s=n*m;
    for(int i=0;i<s;i++) f[i].reset();
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%d",&a[i][j]);
        //建立初始方程矩阵
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            int x=i*m+j;
            f[x][x]=1;
            if(a[i][j]) f[x][s]=1;
            for(int k=0;k<n;k++)
                for(int l=0;l<m;l++)
                {
                    int y=k*m+l;
                    if(ab(i-k)+ab(j-l)==d){
                        f[x][y]=1;
                    }
                }
         }
}
//f[i][j]为对应方程的系数
bool solve()
{
    int t=0,zhi;   
    for(int i=0;i<s && t<s;i++)
    {
        bool flag=false;
        for(int j=i;j<s;j++)
            if(f[j][t]){
                flag=true;
                if(j!=i) {
                    tm=f[i];  f[i]=f[j]; f[j]=tm;  //交换,使得f[i][t]为1。
                }
                break;                
            }
        if(!flag)  { i--;   t++;   continue;  } //找不到，继续下一列
        zhi=i;
        for(int j=i+1;j<s;j++)
            if(f[j][t])    f[j]^=f[i];  //消元,速度快不少
        t++;
    }
    for(int i=zhi+1;i<s;i++) if(f[i][s]) return false; //无解
    return true; //唯一解，或者无穷解
}
int main()
{
    while(scanf("%d%d%d",&m,&n,&d),n+m+d)
    {
        input();
        if(solve()) printf("1\n");
        else printf("0\n");
    }
    return 0;
}
