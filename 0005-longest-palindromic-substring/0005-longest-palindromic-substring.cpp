class Solution {
public:
    string longestPalindrome(string s) {
        if  (s.empty()) return "";
        int start = 0, maxLen = 1;

        auto expand = [&](int left, int right) {
            while (left >= 0 && right < (int)s.size() && s[left] == s[right]) {
                --left;
                ++right;
            }
            // Restore last valid bounds
            ++left; --right;
            if (right - left + 1 > maxLen) {
                maxLen = right - left + 1;
                start  = left;
            }
        };

        for (int i = 0; i < (int)s.size(); ++i) {
            expand(i, i);       // Odd-length  ("racecar")
            expand(i, i + 1);   // Even-length ("abba")
        }

        return s.substr(start, maxLen);
       
        
    }
};