#include <iostream>
#include<algorithm>
using namespace std; 
struct envelope 
{
    int a;
    int b;
    int area;
};

bool comp (envelope &e1, envelope e2) 
{
    return e1.area > e2.area; 
} 

int main()
{ 
    int n;
    cout<<"enter the number of envelops : -In": cin>>n; 
    struct envelope env[n];
    cout<<"enter the dimensions for envelops : -In"; 
    for (int i=0;i<n;++) 
    {
        cin>>env[i].a>>env[i].b;
    }
    // calculating area of the envelops 
    for (int i=0;i<n;i++)
    {
        env[i].area = env[i].a*env[i].b;
    }
    /* we will have to sort the envelops according to the area, then only we can ensure that for a
    envelope E, all the possible envelops which can be put inside the E are on the right side of it (assuming we are
    sorting in decreasing value of area). */

    sort(env,env+n,comp); // sort the envelops in decreasing value of area of envelops 
    int dp[n][2];
    // there are two orientation possible for each envelope (a,b) and (b, a)
    // dp[i][0] => maxium number of envelops nested using first i envelops(ith one on the top) and ith envelope having orientation (a, b)
    // dp[i][1] => maxium number of envelops nested using first i envelops(ith one on the top) and ith envelope having orientation (b, a)
    // initialize all dp values with 1 
    for (int i=0;i<n;i++) 
    {
        dp[i][0] = dp[i][1] = 1;
    }
    // This implementation is little modification of the standard problem of Longest decreasing subsequence
    for(int i=1;i<n;i++) 
    { // first orientation for dp[i][0] 
        int x = env[i].a;
        int y = env[i].b; 
        for(int j=0;j<i;j++)
        {
            if (env[j].a>x && env[j].b>y)// checking with first orientation of jth envelope 
            { 
                dp[i][0] = max(dp[i][0], dp[j][0]+1);
            }
            else if (env[j].b>x && env[j].a>y)//checking with second orientation of jth envelope
            {
                dp[i][0] = max(dp[i][0],dp[j][1]+1);
            }
        }
        //second orientation of jth envelope dp[i][1]
        x = env[i].b;
        y = env[i].a;
        for (int j=0;j<i;j++)
        {
            if (env[j].a>x && env[j].b>y)
            {
                dp[i][1] = max(dp[i][1],dp[j][1]+1);
            }
            else if (env[j].b>x && env[j].a>y)
            {
                dp[i][1] = max(dp[i][1],dp[j][1]+1);
            }
        }

    }
    int res = 0;
    // now result will be the max of all possible dp states 
    for(int i=0;i<n;i++)
    {
        res = max(res,dp[i][0]);
        res = max(res,dp[i][1]);
    }
    cout<<"maximum possible number of envelops nested :"<<res<<endl; 
}
