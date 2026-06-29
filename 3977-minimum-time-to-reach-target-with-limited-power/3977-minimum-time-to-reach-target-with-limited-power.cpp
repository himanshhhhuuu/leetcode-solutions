class Solution {
public:
    vector<long long> minTimeMaxPower(int n, vector<vector<int>>& edges, int power, vector<int>& cost, int source, int target) {
         vector<vector<pair<int,int>>> graph(n);
        for (auto &e : edges) {
            graph[e[0]].push_back({e[1], e[2]});
        }

        const long long INF = 4e18;

        vector<vector<long long>> dist(n, vector<long long>(power + 1, INF));

        priority_queue<
            tuple<long long,int,int>,
            vector<tuple<long long,int,int>>,
            greater<tuple<long long,int,int>>
        > pq;

        dist[source][power] = 0;
        pq.push({0, power, source});

        while (!pq.empty()) {
            auto [t, rem, u] = pq.top();
            pq.pop();

            if (t != dist[u][rem]) continue;

            if (rem < cost[u]) continue;

            int nxtPower = rem - cost[u];

            for (auto &[v, w] : graph[u]) {
                long long nt = t + w;
                if (nt < dist[v][nxtPower]) {
                    dist[v][nxtPower] = nt;
                    pq.push({nt, nxtPower, v});
                }
            }
        }

        long long bestTime = INF;
        int bestPower = -1;

        for (int p = 0; p <= power; p++) {
            if (dist[target][p] < bestTime) {
                bestTime = dist[target][p];
                bestPower = p;
            } else if (dist[target][p] == bestTime) {
                bestPower = max(bestPower, p);
            }
        }

        // source == target (no movement)
        if (source == target) {
            if (0 < bestTime || bestTime == INF)
                return {0, power};
        }

        if (bestTime == INF) return {-1, -1};

        return {bestTime, (long long)bestPower};
        
    }
};