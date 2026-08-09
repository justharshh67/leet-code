class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        vector<int> suffix(n + 1, 0);
        for (int i = n - 1; i >= 0; i--)
            suffix[i] = suffix[i + 1] + piles[i];

        // dp[i][M]: best score current player can get from piles[i..] with given M
        vector<vector<int>> dp(n, vector<int>(n + 1, -1));

        function<int(int, int)> solve = [&](int i, int M) -> int {
            if (i >= n) return 0;
            // If we can take all remaining piles in one move
            if (2 * M >= n - i) return suffix[i];

            if (dp[i][M] != -1) return dp[i][M];

            int best = 0;
            for (int X = 1; X <= 2 * M; X++) {
                // current player takes piles[i..i+X-1],
                // then opponent plays optimally on the rest,
                // current player gets total remaining minus opponent's best
                int opponentBest = solve(i + X, max(M, X));
                int mine = suffix[i] - opponentBest;
                best = max(best, mine);
            }

            dp[i][M] = best;
            return best;
        };

        return solve(0, 1);
    }
};