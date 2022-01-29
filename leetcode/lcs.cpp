/*
https://leetcode.com/problems/longest-increasing-subsequence/
*/

class Solution {
public:
    int lengthOfLIS(vector<int>& v) {
    int n=v.size();
    vector<int> d(n+2, INT_MAX);
    d[0]=INT_MIN;
    for(int i=0;i<n;++i){
        int xx = upper_bound(d.begin(),d.end(), v[i]) - d.begin();
        if(d[xx-1] < v[i] && d[xx]>v[i]){
            d[xx]=v[i];
        }
    }
    int ans = n+1;
    for(int i=n;i>=0;--i){
       // cout<<i<<" "<<d[i]<<" "<<endl;
        if(d[i]!=INT_MAX){
            ans = i;
            break;
        }
    }
        return ans;
    }
};
