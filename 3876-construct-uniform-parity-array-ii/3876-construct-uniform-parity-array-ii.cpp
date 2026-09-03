class Solution {
public:
    bool uniformArray(vector<int>& a) {
        int mn = INT_MAX, oddCnt = 0;
        for (int x : a) {
            mn = min(mn, x);
            if (x % 2 == 1) oddCnt++;
        }
        // min Element is ODD(remaining even > min) or All Even!
        return mn % 2 || oddCnt == 0; 
    }
};