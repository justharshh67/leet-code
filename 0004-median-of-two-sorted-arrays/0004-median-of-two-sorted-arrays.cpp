class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // Ensure nums1 is the smaller array so binary search is on the smaller one
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }

        int m = nums1.size(), n = nums2.size();
        int total = m + n;
        int half = (total + 1) / 2; // left partition size

        int lo = 0, hi = m;

        while (lo <= hi) {
            int cut1 = (lo + hi) / 2;       // partition in nums1
            int cut2 = half - cut1;          // partition in nums2

            int L1 = (cut1 == 0) ? INT_MIN : nums1[cut1 - 1];
            int R1 = (cut1 == m) ? INT_MAX : nums1[cut1];
            int L2 = (cut2 == 0) ? INT_MIN : nums2[cut2 - 1];
            int R2 = (cut2 == n) ? INT_MAX : nums2[cut2];

            if (L1 <= R2 && L2 <= R1) {
                // Found the correct partition
                if (total % 2 == 0) {
                    return (max(L1, L2) + min(R1, R2)) / 2.0;
                } else {
                    return max(L1, L2);
                }
            } else if (L1 > R2) {
                hi = cut1 - 1; // move partition left in nums1
            } else {
                lo = cut1 + 1; // move partition right in nums1
            }
        }

        return -1.0; // unreachable if inputs are valid sorted arrays
    }
};