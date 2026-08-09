class Solution {
public:
    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        long long lo = 1, hi = 1;
        int minTime = *min_element(workerTimes.begin(), workerTimes.end());
        // upper bound: fastest worker does everything alone
        hi = (long long)minTime * mountainHeight * (mountainHeight + 1) / 2;

        auto canFinish = [&](long long mid) -> bool {
            long long totalReduced = 0;
            for (int t : workerTimes) {
                long long work = mid / t;
                // find max k such that k*(k+1)/2 <= work
                long long k = (long long)((-1.0 + sqrt(1.0 + 8.0 * (double)work)) / 2.0);
                // adjust for floating point errors
                while (k * (k + 1) / 2 > work) k--;
                while ((k + 1) * (k + 2) / 2 <= work) k++;
                totalReduced += k;
                if (totalReduced >= mountainHeight) return true;
            }
            return totalReduced >= mountainHeight;
        };

        while (lo < hi) {
            long long mid = lo + (hi - lo) / 2;
            if (canFinish(mid)) hi = mid;
            else lo = mid + 1;
        }

        return lo;
    }
};