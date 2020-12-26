#include <bits/stdc++.h>
using namespace std;
#define INF 1000000000
int main(){
	int n; cin>>n;
	vector<string> v(n);
	map<string,int> mp;
	int z=1;
	for(int i=0;i<n;++i){
		cin>>v[i];
		mp[v[i]]=z++;
	}
	int p; cin>>p;
	vector<string> domain(p);
	set<pair<int,string> >  vv[p];
	set<pair<string,int> >  vv2[p];
	map<string, int> mm;
	int pri[p];
	vector<set<pair<int,string> > > res(p);
	for(int j=0;j<p;++j){
		cin>>domain[j];
		int machines; cin>>machines;
		pri[j]=machines;
		for(int x=0;x<machines;++x){
			string s; cin>>s;
			vv[j].insert(make_pair(x,s));
			vv2[j].insert(make_pair(s,x));
			mm[s]=j;
		}
	}
	int q; cin>>q;
	string machine_up = "machine_up";
	string machine_down = "machine_down";
	vector<string> request[n+1];

	while(q--){
		string s; cin>>s;
		if(s.find(machine_down)!=string::npos || s.find(machine_up)!= string::npos){
			string ip="";
			for(int f=s.length()-1;f>=0;f--){
				if(s[f]=='=')break;
				ip=ip+s[f];
			}
			reverse(ip.begin(),ip.end());
			int bb=mm[ip];
			if(s.find(machine_up)!=string::npos){
				vv[bb].insert(make_pair(pri[bb]-1,ip));
				vv2[bb].insert(make_pair(ip,pri[bb]-1));
				pri[bb]++;
				continue;
			}
			auto it=lower_bound(vv2[bb].begin(),vv2[bb].end(),make_pair(ip,-1));
			pair<string,int> pp=*it;
			int zz=pp.second;
			vv[bb].erase(make_pair(zz,pp.first));
			vv2[bb].erase(make_pair(pp.first,zz));
			continue;
		}
		for(int j=0;j<p;++j){
			if(s.find(domain[j])!=string::npos){
				pair<int,string> pp=(*vv[j].begin());
				int sex=mp[pp.second];
				request[sex].push_back(s);
				vv[j].erase(pp);
				vv2[j].erase(make_pair(pp.second,pp.first));
				int priority=pri[j]+10000;
				vv[j].insert(make_pair(priority+10000,pp.second));
				vv2[j].insert(make_pair(pp.second,priority+10000));
				pri[j]++;
				continue;
			}
		}
	}
	for(int i=1;i<=n;++i){
		cout<<v[i-1]<<endl;
		for(int j=0;j<request[i].size();++j){
			cout<<request[i][j]<<endl;
		}
	}


}
