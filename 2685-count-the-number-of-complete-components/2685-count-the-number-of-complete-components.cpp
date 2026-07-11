class Solution {
public:
    void dfs(int node, vector<vector<int>>& adj, vector<int>& vis,
             int &nodes, int &edgeCount) {

        vis[node] = 1;
        nodes++;
        edgeCount += adj[node].size();

        for (int next : adj[node]) {
            if (!vis[next])
                dfs(next, adj, vis, nodes, edgeCount);
        }
    }

    int countCompleteComponents(int n, vector<vector<int>>& edges) {

        vector<vector<int>> adj(n);

        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<int> vis(n, 0);
        int ans = 0;

        for (int i = 0; i < n; i++) {

            if (vis[i])
                continue;

            int nodes = 0;
            int edgeCount = 0;

            dfs(i, adj, vis, nodes, edgeCount);

            edgeCount /= 2;

            if (edgeCount == nodes * (nodes - 1) / 2)
                ans++;
        }

        return ans;
    }
};
