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
    vector<int> mostFrequentInRows(const vector<vector<int>>& matrix) {
    vector<int> result;
    
    for (const auto& row : matrix) {
        unordered_map<int, int> freq;
        int maxFreq = 0;
        int mostFrequent = row[0];
        
        // Count the frequency of each element in the row
        for (int num : row) {
            freq[num]++;
            // Update the most frequent number
            if (freq[num] > maxFreq) {
                maxFreq = freq[num];
                mostFrequent = num;
            }
        }
        
        result.push_back(mostFrequent);
    }
    
    return result;
}
void generateCombinations(const vector<string>& strategies, vector<string>& combination, int player, vector<vector<string>>& allCombinations) {
    if (player == 3) {
        // Store the current combination
        allCombinations.push_back(combination);
        return;
    }

    // Loop through each strategy for the current player
    for (const string& strategy : strategies) {
        combination[player] = strategy;
        generateCombinations(strategies, combination, player + 1, allCombinations);
    }
}
// Function to find and print all Nash Equilibrium profiles
vector<vector<string>> findAllNashEquilibria(const map<vector<string>, tuple<int, int, int>>& payoffs) {
    vector<vector<string>> nashEquilibria;
    vector<string> strategies = {"G1", "G2", "G3"};
    
    // Iterate over all possible strategy profiles
    for (auto it = payoffs.begin(); it != payoffs.end(); ++it) {
        vector<string> profile = it->first;
        tuple<int, int, int> currentPayoff = it->second;
        bool isNash = true;

        // Check if Player 1 can improve by changing strategy
        for (const auto& s1 : strategies) {
            if (s1 != profile[0]) {
                vector<string> newProfile = {s1, profile[1], profile[2]};
                if (payoffs.find(newProfile) != payoffs.end() &&
                    get<0>(payoffs.at(newProfile)) < get<0>(currentPayoff)) {
                    isNash = false;
                    break;
                }
            }
        }

        // Check if Player 2 can improve by changing strategy
        if (isNash) {
            for (const auto& s2 : strategies) {
                if (s2 != profile[1]) {
                    vector<string> newProfile = {profile[0], s2, profile[2]};
                    if (payoffs.find(newProfile) != payoffs.end() &&
                        get<1>(payoffs.at(newProfile)) < get<1>(currentPayoff)) {
                        isNash = false;
                        break;
                    }
                }
            }
        }

        // Check if Player 3 can improve by changing strategy
        if (isNash) {
            for (const auto& s3 : strategies) {
                if (s3 != profile[2]) {
                    vector<string> newProfile = {profile[0], profile[1], s3};
                    if (payoffs.find(newProfile) != payoffs.end() &&
                        get<2>(payoffs.at(newProfile)) < get<2>(currentPayoff)) {
                        isNash = false;
                        break;
                    }
                }
            }
        }

        // If no player can improve, add the profile to Nash Equilibria
        if (isNash) {
            nashEquilibria.push_back(profile);
        }
    }

    // Print all Nash Equilibrium profiles
    cout << "Nash Equilibrium Profiles:\n";
    for (const auto& profile : nashEquilibria) {
        cout << "Profile: ";
        for (const auto& strategy : profile) {
            cout << strategy << " ";
        }
        auto payoff = payoffs.at(profile);
        cout << "(Payoffs: " << get<0>(payoff) << ", " << get<1>(payoff) << ", " << get<2>(payoff) << ")\n";
    }

    return nashEquilibria;
}



// Function to check if a profile is an approximate Nash Equilibrium by minimizing payoffs within an epsilon range
bool isApproximateNashEquilibrium(const vector<string>& profile, double epsilon, map<vector<string>, tuple<int, int, int>>& payoffs) {
    auto currentPayoff = payoffs[profile];
    vector<string> strategies = {"G1", "G2", "G3"};

    // Check if Player 1 can improve by changing strategy within epsilon range
    for (const auto& s1 : strategies) {
        if (s1 != profile[0]) {
            vector<string> newProfile = {s1, profile[1], profile[2]};
            if (get<0>(payoffs[newProfile]) < get<0>(currentPayoff) - epsilon) {
                return false;
            }
        }
    }

    // Check if Player 2 can improve by changing strategy within epsilon range
    for (const auto& s2 : strategies) {
        if (s2 != profile[1]) {
            vector<string> newProfile = {profile[0], s2, profile[2]};
            if (get<1>(payoffs[newProfile]) < get<1>(currentPayoff) - epsilon) {
                return false;
            }
        }
    }

    // Check if Player 3 can improve by changing strategy within epsilon range
    for (const auto& s3 : strategies) {
        if (s3 != profile[2]) {
            vector<string> newProfile = {profile[0], profile[1], s3};
            if (get<2>(payoffs[newProfile]) < get<2>(currentPayoff) - epsilon) {
                return false;
            }
        }
    }

    return true;
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
    //vector<int> v1{1, 50}, v2{2, 30}, v3{2, 20}, v4{3, 70}, v5{1, 20}, v6{3, 30},v7{4,50};
    vector<int> v1{1, 4}, v2{2, 3}, v3{2, 2}, v4{3, 7}, v5{1, 2}, v6{3, 3},v7{4,5};
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
    /*cout << "The distance vector is ";
    for (int i = 0; i < V; i++)
    {
        cout<<res[i] << " ";
    }
    
   
    cout << "\nThe parent of each node is ";
    for (int i = 0; i < V; i++)
    {
        cout <<par[i] << " ";
    }
    */
    vector<int>price={3,4,3};     //price at charging station 1,2 and 3
    vector<int>capacity={3,2,2};        //capacity of charging station 1,2 and 3
    vector<int>timetocharge={30,20,25};   //Time to charge at charging station 1,2 and 3
    vector<int>currvehcharging={30,18,12}; //Current no of vehicles at charging station 1,2 and 3

    vector<int> alp(3, 3);  //for distance
    vector<int> bet(3, 4);  //for price
    vector<int> gam(3, 4);  //for capacity
   
    /*obj.findgamma(capacity,timetocharge,currvehcharging,gam);
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
    }*/
   
   vector<int>gascostorder;
    for(int user=1;user<=10;user++)
    {

    
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
            capacity[ind]=capacity[ind]+1;


    //cout<<i<<endl;
    for(int i=1;i<=3;i++)
    {
        cout<<"\nThe overall cost using gas station "<<i<<" is "<<cost[i-1]<<endl;
    }

    cout<<"The user prefers gas station "<<ind+1<<" having cost = "<<cost[ind]<<endl;
    gascostorder.push_back(ind+1);


    }
   
    
    vector<string> strategies = {"G1", "G2", "G3"};
    vector<string> combination(3);
    vector<vector<string>> allCombinations;

    // Generate all combinations
    obj.generateCombinations(strategies, combination, 0, allCombinations);
    map<vector<string>, tuple<int, int, int>> payoffs;

    // Print all stored combinations
    unordered_map<string,int>gastoind;
    gastoind["G1"]=1;
    gastoind["G2"]=2;
    gastoind["G3"]=3;
    cout << "All Strategy Combinations:" << endl;
    for (const auto& combo : allCombinations) {
        vector<string>combvector;

        vector<int> comboPayoffs;

        for (const string& no : combo) {
            combvector.push_back(no);
            cout << no << " ";

        }
        cout<<"( ";
        for(auto it:combvector)
        {
            long long c=0;
            c=(bet[gastoind[it]-1]*price[gastoind[it]-1])+(gam[gastoind[it]-1]*capacity[gastoind[it]-1])+
            (alp[gastoind[it]-1]*res[gastoind[it]]);
            comboPayoffs.push_back(c);

            capacity[gastoind[it]-1]+=1;
            cout<<c<<" ";
            
        }
        cout<<")";
        payoffs[combo] = make_tuple(comboPayoffs[0], comboPayoffs[1], comboPayoffs[2]);


        
        cout << endl;
    }

  obj.findAllNashEquilibria(payoffs);


     double epsilon = 5.0; // Define the epsilon value for approximation
    cout << "Approximate Nash Equilibrium Profiles (with epsilon = " << epsilon << "):" << endl;

    // Iterate over all strategy combinations
    for (const auto& entry : payoffs) {
        if (obj.isApproximateNashEquilibrium(entry.first, epsilon,payoffs)) {
            cout << "Profile: ";
            for (const string& strategy : entry.first) {
                cout << strategy << " ";
            }
            cout << "(Payoffs: " << get<0>(entry.second) << ", "
                 << get<1>(entry.second) << ", " << get<2>(entry.second) << ")" << endl;
        }
    }


    


    return 0;
}
/*sddition to that*/