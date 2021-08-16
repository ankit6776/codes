#include <bits/stdc++.h>
using namespace std;
#define N 10000
string factorialSumDigit(long n){
    set<string> ss;
    int fact[11];
    fact[0]=1;
    string num =to_string(n);
    string pp = num;
    for(int i=1;i<=9;++i)fact[i]=i*fact[i-1];
    ss.insert(num);
    while(1){
        string res="";
        long long ans = 0;
        for(int i=0;i<pp.length();++i){
            ans = ans + (fact[pp[i]-'0']);
        }
        res = to_string(ans);
        if(res==num)return "Possible";
        if(ss.count(res)){
            return "Impossible";
        }
        ss.insert(res);
        pp=res;
    }
    return "Impossible";
}
struct tree {
    struct tree* child[26];
    bool flag;
    int val = 0;
    tree() {
        for(int i=0;i<26;++i){
            this->child[i]=NULL;
        }
        this->flag=0;
        this->val=0;
    }
};
void insert(struct tree* root,string arr) {
    int nn = arr.length();
    struct tree* temp = root;
    for(int j=0;j<nn;++j){
        int xx = arr[j]-'a';
        if(temp->child[xx]!=NULL) {
            temp = temp->child[xx];
        }
        else{
            temp->child[xx]=new tree();
            temp = temp->child[xx];
        }
    }
    temp->flag=1;
    temp->val=1;
}
void dfs(struct tree * root, int &ans) {
    int bb = 0;
    for(int j=0;j<26;++j) {
        if(root->child[j]!=NULL){
            dfs(root->child[j],ans);
            if(root->flag == 1){
                root->val = root->val+root->child[j]->val;
                ans = max(ans,root->val);
            }
        }
    }
    ans = max(ans,root->val);
}
int printLongestSuffix(int n,char **arr) {
    int kk=strlen(arr[0]);
    struct tree* root = new tree();
    root->flag=1;
    for(int i=0;i<n;++i){
        string zz = "";
        int nn=strlen(arr[i]);
        for(int j=nn-1;j>=0;--j)zz.push_back(arr[i][j]);
        insert(root,zz);
    }
    int ans = 0;
    dfs(root,ans);
    return ans;
}
int main() {
    int n; cin>>n;
    char **arr = (char**)malloc(sizeof(char*)*n);
    for(int i=0;i<n;++i){
        arr[i]=(char*)malloc(sizeof(char*)*N);
        scanf("%s", arr[i]);
    }
    cout<<printLongestSuffix(n,arr);
	return 0;
}
