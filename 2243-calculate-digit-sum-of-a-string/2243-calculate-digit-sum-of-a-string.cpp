class Solution {
public:
    string digitSum(string s, int k) {
        while(s.size() > k) {
            string t;
            for(int i = 0; i < s.size(); i++){
                int sum = 0, j;
                for(j = i; j < s.size() && j - i < k; j++){
                    sum += s[j] - '0';
                }
                i = j - 1;
                t += to_string(sum);
            }
            s = t;
        }

        return s;
    }
};