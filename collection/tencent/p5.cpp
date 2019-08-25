#include<iostream>
#include<vector>
#include<stack>
#include<map>
#include<utility>
#include<set>
#include<algorithm>
using namespace std;
long long int solver(vector<vector<int>>& vec,int n,int i,int j,bool negative)
{
    if(j<0||j>2) return INT32_MIN;
    if(i==n-1&&negative) return -vec[i][j];
    if(i==n-1&&!negative) return vec[i][j];
    if(vec[i][j]==0)
    {
        negative=!negative;
        long long int ans=INT32_MIN;
        for(int k=-1;k<=1;k++)
        {   
            if (i + k < 0)
                continue
            if (i + k >= 3)
                break
            int temp=solver(vec,n,i+1,j+k,negative);
            if(ans<temp) ans=temp;
        }
        return ans;
    }
    else
    {
        long long int ans=INT32_MIN;
        for(int k=-1;k<=1;k++)
        {
            if (i + k < 0)
                continue
            if (i + k >= 3)
                break
            int temp=solver(vec,n,i+1,j+k,negative);
            if(ans<temp) ans=temp;
        }
        if(negative) 
            return ans-(long long) vec[i][j];
        else 
            return ans+(long long) vec[i][j];
    }
} 

int main()
{
    int n;
    cin>>n;
    vector<vector<int>>vec(n,vector<int>(3));
    for(int i=0;i<n;i++)
        for(int j=0;j<3;j++)
        {
            cin>>vec[i][j];
        }
    long long ans=INT32_MIN;
    for(int i=0;i<3;i++)
    {
        long long temp=solver(vec,n,0,i,false);
        if(temp>ans) ans=temp;
    }
    cout<<ans<<endl;
    return 0;
}