#include <bits/stdc++.h>
using namespace std;
#define lld long long 
#define pb push_back
int a,b;
int flag;
void dfs(vector<vector<int> >&v,int s,int vis[],vector<int> &vv)
{
	vis[s]=1;
	if(flag)return;
	vv.pb(s);
	if(s==b){
		flag=1; return;
	}
	if(flag)return;
	for(auto x: v[s])
	{
		if(!vis[x]&&flag==0)
		{
			dfs(v,x,vis,vv);
		}
	}
	if(flag==0)
	vv.pop_back();
}
lld min(lld a,lld b){return a<b?a:b;}
int main()
{
	int t; cin>>t;
	while(t--){
	flag=0;
	lld n,d; cin>>n>>d;
	vector<vector<int> > v(n+5);
	lld col[n+1],jmp[n+1];
	for(int i=2;i<=n;++i)
	{
		int x; cin>>x; v[i].pb(x);
		v[x].pb(i);
	}
	for(int i=1;i<=n;++i)cin>>col[i];
    for(int i=1;i<=n;++i)cin>>jmp[i];
    cin>>a>>b;
    int vis[n+1];
    memset(vis,0,sizeof(vis));
    vector<int> vv;
   // vv.push_back(a);
    dfs(v,a,vis,vv);
    lld dd=0;
    lld ans=999999999999999;
    for(auto x: vv)
    {
    	if(x==b){ans=min(ans,dd); break;}
    	if(col[x]==col[b])
    	{
    		ans=min(ans,dd+jmp[b]);
    	}
    	dd=dd+d;
    }
    cout<<ans<<endl;
}

	return 0;
}