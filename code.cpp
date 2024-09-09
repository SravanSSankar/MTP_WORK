#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    
    vector<int> dijkstra(int V, vector<vector<int>> adj[], int S,vector<int>&par)
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> distTo(V, INT_MAX);
        distTo[S] = 0;
        pq.push({0, S});
        while (!pq.empty())
        {
            int node = pq.top().second;
            int dis = pq.top().first;
            pq.pop();
            for (auto it : adj[node])
            {
                int v = it[0];
                int w = it[1];
                if (dis + w < distTo[v])
                {
                    par[v]=node;
                    distTo[v] = dis + w;
                    pq.push({dis + w, v});
                }
            }
        }
        return distTo;
    }
    
    void findgamma(vector<int>&capacity,vector<int>&timetocharge,
    vector<int>&currvehcharging,vector<int>&gam)
    {
            priority_queue<pair<int,int>>pq1;

            for(int i=0;i<3;i++)
            {
                if(capacity[i]>=currvehcharging[i])pq1.push({0,i});
                else
                {
                    int rem=currvehcharging[i]-capacity[i];
                    int res=rem*timetocharge[i];
                    pq1.push({res,i});
                }
            }
            int we=3;
            int prev=-1;
            int factor=-1;
            while(!pq1.empty())
            {
                auto it=pq1.top();
                int ind=it.second;
                pq1.pop();
                if(it.first==prev)
                {
                    gam[ind]=factor;
                }
                else gam[ind]=we;
                prev=it.first;
                factor=we;

                we--;

            }


    }
    void findbeta(vector<int>&price,vector<int>&bet)
    {
        set<pair<int,int>>st;
        for(int i=0;i<3;i++)
        {
            st.insert({price[i],i});
        }
        int w=1;
        int prev=-1;
        int factor=-1;
        while(!st.empty())
        {
            auto it=*(st.begin());
            
            int ind=it.second;
            if(it.first==prev)
            {
                bet[ind]=factor;
            }
            else bet[ind]=w;
            prev=it.first;
            factor=w;
            st.erase(it);

            w++;
        }
    

    }
    void findalpha(vector<int>&alp,vector<int>&res)
    {
        priority_queue<pair<int,int>>pq;
        for(int i=1;i<=3;i++)
        {
            pq.push({res[i],i});
        }
        
        
        int weight=3;
        int prev=-1;
        int factor=-1;
        while(!pq.empty())
        {
            auto it=pq.top();
            pq.pop();
            int ind=it.second;
            if(it.first==prev)
            {
                alp[ind-1]=factor;
            }
            else alp[ind-1]=weight;
            prev=it.first;
            factor=weight;
            weight--;

        }

    }
};

int main()
{
    // Driver code.


    int V = 5, S = 0;//v=vertices,S=source
    vector<vector<int>> adj[V];
    vector<int>par(V,0);
    for(int i=0;i<V;i++)
    {
        par[i]=i;
    }
    vector<vector<int>> edges;
    vector<int> v1{1, 50}, v2{2, 30}, v3{2, 20}, v4{3, 70}, v5{1, 20}, v6{3, 30},v7{4,50};
    int i = 0;
    adj[0].push_back(v1);
    adj[0].push_back(v2);
    adj[1].push_back(v3);
    adj[1].push_back(v4);
    adj[2].push_back(v5);
    adj[2].push_back(v6);
    adj[3].push_back(v7);

    Solution obj;
    vector<int> res = obj.dijkstra(V, adj, S,par);
    cout << "The distance vector is ";
    for (int i = 0; i < V; i++)
    {
        cout<<res[i] << " ";
    }
    
   
    cout << "\nThe parent of each node is ";
    for (int i = 0; i < V; i++)
    {
        cout <<par[i] << " ";
    }
    
    vector<int>price={60,50,40};     //price at charging station 1,2 and 3
    vector<int>capacity={20,10,15};        //capacity of charging station 1,2 and 3
    vector<int>timetocharge={30,20,25};   //Time to charge at charging station 1,2 and 3
    vector<int>currvehcharging={30,18,12}; //Current no of vehicles at charging station 1,2 and 3

    vector<int> alp(3, 0);  //for distance
    vector<int> bet(3, 0);  //for price
    vector<int> gam(3, 0);  //for capacity
   
    obj.findgamma(capacity,timetocharge,currvehcharging,gam);
    cout << "\nThe watingtime/qeueue constant of each station 1,2 and 3 is is ";
    for(auto it:gam)
    {
        cout<<it<<" ";
    }

    obj.findbeta(price,bet); //for pricing differentiation
    cout << "\nThe pricing constant of each station 1,2 and 3 is is ";
    for(auto it:bet)
    {
        cout<<it<<" ";
    }


    obj.findalpha(alp,res);
     cout << "\nThe distance/travelling time constant of each station 1,2 and 3 is is ";
    for(auto it:alp)
    {
        cout<<it<<" ";
    }

    int ind=-1;
    int mini=INT_MAX;
    vector<int>cost(3,0);  // total utility cost at each gas station
    for(int i=0;i<3;i++)
    {
        long long c=0;
        c=(bet[i]*price[i])+(gam[i]*capacity[i])+(alp[i]*res[i+1]);
        cost[i]=c;
        if(c<mini)
        {
            mini=c;
            ind=i;

        }

    }


    //cout<<i<<endl;
    for(int i=1;i<=3;i++)
    {
        cout<<"\nThe overall cost using gas station "<<i<<" is "<<cost[i-1]<<endl;
    }

    cout<<"The user prefers gas station "<<ind+1<<" having cost = "<<cost[ind]<<endl;
    cout<<"The path taken to reach gas station is ";
    int node=ind+1;
    string s="";
    while(par[node]!=node)
    {
      
        s=to_string(node)+s;
        node=par[node];
    }
     s=to_string(node)+s;
   
    for(int i=0;i<s.length();i++)
    {
        if(i!=s.length()-1)cout<<s[i]<<"=>";
        else cout<<s[i]<<endl;

    }


    
    return 0;
}
