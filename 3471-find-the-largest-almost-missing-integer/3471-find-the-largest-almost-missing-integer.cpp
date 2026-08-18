class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = -1;

        for (int x : nums) {
            int cnt = 0;

            // Check every subarray of size k
            for (int i = 0; i <= n - k; i++) {
                bool found = false;

                for (int j = i; j < i + k; j++) {
                    if (nums[j] == x) {
                        found = true;
                        break;
                    }
                }

                if (found)
                    cnt++;
            }

            if (cnt == 1)
                ans = max(ans, x);
        }

        return ans;
    }
};