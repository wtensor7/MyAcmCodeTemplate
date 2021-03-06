
void pre_cal()
{
	memset(isPrime,1,sizeof(isPrime)); /*线性筛素数*/
	memset(u,0,sizeof(u)); /*顺便利用积性函数特点求mobius函数*/
	np=0;
	u[1]=1;	
	for(int i=2;i<maxl;i++)
	{
		if(isPrime[i]) {
			prime[np++]=i;
			u[i]=-1;
		}
		for(int j=0;j<np && i*prime[j]<maxl;j++)
		{
			isPrime[i*prime[j]]=false;			
			if(i%prime[j]!=0) u[i*prime[j]]=u[i]*u[prime[j]];
			else break; 
	/*p[j] | i 时prime[j]之后的素数就不是i的最小素因数，假设i=i'*p[j],那么对j'>j, i*p[j']=(i'*p[j])*p[j']=(i'*p[j'])*p[j]=i''*p[j], 其中i''>i,于是后面的i''会把这个i*p[j']的非素数都筛去，就没必要做重复工作了*/
		}		
	}
}

