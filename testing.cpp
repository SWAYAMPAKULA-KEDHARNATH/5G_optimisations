#include <bits/stdc++.h>

using namespace std;

int Maxbitrate(vector<vector<pair<int,int>>> &input,vector<vector<int>> &parent,int P)
{
    vector<vector<int>> dp(input.size()+1,vector<int> (P+1,0));
    int n=input.size();
    
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=P;j++)
        {
            for(int k=0;k<=j;k++)
            {
                int bitrate=input[i-1][k].second;
                
                if(dp[i][j]<bitrate+dp[i-1][j-k])
                {
                    dp[i][j]=bitrate+dp[i-1][j-k];
                    parent[i][j]=k;
                }
            }
        }
    }
    return dp[n][P];
}

vector<vector<pair<int,int>>> preprocessing(vector<vector<pair<int,int>>> &input,int &P)
{
    int n=input.size();
    vector<vector<pair<int,int>>> temp(n);
    
    for(int i=0;i<n;i++)
    {
        int m=input[i].size()-1;
        int maxbitrate=input[i][m].second;
        
        for(int j=0;j<=P;j++)
        {
            if(j>m)
            temp[i].push_back({j,maxbitrate});
            else
            temp[i].push_back(input[i][j]);
        }
    }    
    return temp;
}

vector<pair<int,int>> allocate(vector<vector<int>> &parent,int P,int &n)
{
    vector<pair<int,int>> distribution;
    
    for(int i=n;i>0;i--)
    {
        distribution.insert(distribution.begin(),{i,parent[i][P]});
        P-=parent[i][P];
    }
    
    return distribution;
}

int print(vector<pair<int,int>> &distribution,int &n)
{
    int total_power_used=0;
    
    for(int i=0;i<n;i++)
    {
        cout<<"power for channel"<<i+1<<" is "<<distribution[i].second<<endl;
        total_power_used+=distribution[i].second;
    }
    
    return total_power_used;
}
int main()
{
    int P;
    cin>>P;
    
    vector<vector<pair<int, int>>> input = {
        {{0,0},{1,1},{2,5},{3,7},{4,9}},
        {{0,0},{1,1},{2,2},{3,3},{4,4}},
        {{0,0},{1,5},{2,6},{3,7},{4,8}},
        {{0,0},{1,4},{2,5},{3,6},{4,9}}
    };
    
    int n=input.size();
    
    vector<vector<pair<int,int>>> temp=preprocessing(input,P);
    vector<vector<int>> parent(n+1,vector<int>(P+1,-1));
    
    int maxbitrate=Maxbitrate(temp,parent,P);
    
    vector <pair<int,int>> distribution=allocate(parent,P,n);
    
    int total_power_used=print(distribution,n);
    
    cout<<"Maxbitrate for power "<<P<<" is "<<maxbitrate<<endl;
    
    cout<<"Power wastage is "<<P-total_power_used<<endl;
    
    return 0;
}
