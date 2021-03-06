#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#define LIM 100
using namespace std;
struct TRIE{
	int pre;
	int next[50];
	bool end;
};
int n,m,p;
int has[500],num;
vector<TRIE> trie;
int f[51][110][LIM];
void trie_insert(int cur[],int len)
{
	int x=1,i=0;
	while(i<len && !trie[x].end) //
	{
		if(trie[x].next[cur[i]])
			x=trie[x].next[cur[i]];
		else {
			int last=trie.size();
			trie.push_back(TRIE());
			memset(&trie[last],0,sizeof(TRIE));
			trie[x].next[cur[i]]=last;
			x=last;
		}
		i++;
	}
	trie[x].end=true;
}
void process(char str[])
{
	for(int i=0;;++i)
		if(str[i]=='\n' || str[i]=='\r') {
			str[i]='\0';
			break;
		}
}
void input()
{
	char str[100];
	int arr[120];
	scanf("%d%d%d\n",&n,&m,&p);
	scanf("%s",str);	
	//fgets(str,60,stdin);	
	//process(str);
	memset(has,255,sizeof(has));
	num=0;	
	for(int i=0;str[i];i++)
		if(has[str[i]+128]==-1) has[str[i]+128]=num++;	
	//construct trie
	trie.resize(2);
	memset(&trie[1],0,sizeof(TRIE));
	for(int i=0;i<p;++i)	
	{
		//fgets(str,60,stdin);
		//process(str);
		scanf("%s",str);
		for(int j=0;str[j];++j)	arr[j]=has[str[j]+128];
		trie_insert(arr,strlen(str));
	}
}
int find_pre(int x,int chi)
{
	while(x!=1){
		if(trie[x].next[chi]) break;
		x=trie[x].pre;
	}
	if(trie[x].next[chi]) x=trie[x].next[chi];
	return x;
}
void trie_pre_cal()
{
	queue<int> que;
	trie[1].pre=1;
	for(int i=0;i<n;++i)	
		if(trie[1].next[i])
			{
				trie[trie[1].next[i]].pre=1;
				que.push(trie[1].next[i]);
			}
	while(!que.empty())
	{
		int x=que.front(); que.pop();
		if(trie[x].end) continue; ///
		for(int i=0;i<n;++i)
			if(trie[x].next[i]){
				int pre_id=find_pre(trie[x].pre,i);
				trie[trie[x].next[i]].pre=pre_id;
				que.push(trie[x].next[i]);
				if(trie[pre_id].end) 
					trie[trie[x].next[i]].end=true; 
			}
	}
}
void add(int a[],int b[])
{
	int w=a[0];
	if(b[0]>w) w=b[0];
	int add=0;
	for(int i=1;i<=w;++i)	
	{
		a[i]=a[i]+b[i]+add;
		add=a[i]/10;
		a[i]%=10;
	}
	while(add){
		a[++w]=add%10;
		add/=10;
	}
	if(w>a[0]) a[0]=w;
}
void solve()
{
	vector<pair<int,int> > e;
	queue<int> que;
	que.push(1);
	while(!que.empty())
	{
		int x=que.front(); que.pop();
		for(int i=0;i<n;++i)
			if(trie[x].next[i]){
				if(trie[trie[x].next[i]].end) continue;
				que.push(trie[x].next[i]);
				e.push_back(make_pair(x,trie[x].next[i]));
				//printf("%d %d %d\n",x,trie[x].next[i],i);
			}else{
				int pre_id=find_pre(trie[x].pre,i);
				if(trie[pre_id].end) continue;
				e.push_back(make_pair(x,pre_id));
				//printf("%d %d %d\n",x,pre_id,i);
			}
	}
	memset(f,0,sizeof(f));	
	f[0][1][0]=1;
	f[0][1][1]=1;
	for(int step=1;step<=m;++step)
	{
		for(int i=0;i<e.size();++i)
			add(f[step][e[i].second],f[step-1][e[i].first]);
	}
	int ans[LIM];
	memset(ans,0,sizeof(ans));
	for(int i=1;i<trie.size();++i)
		add(ans,f[m][i]);
	if(ans[0]==0) printf("0\n");
	else{
		for(int i=ans[0];i>=1;--i) printf("%d",ans[i]);
		printf("\n");
	}
}
int main()
{
	freopen("u1158.in","r",stdin);
	input();
	trie_pre_cal();	
	solve();
	return 0;
}
