#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int editDistance(string str1, string str2) {
    int m = str1.length();
    int n = str2.length();

    vector<int> dp(n + 1);

    for (int i = 0; i <= n; ++i) {
        dp[i] = i;
    }

    int prev;
    for (int i = 1; i <= m; ++i) {
        prev = dp[0];
        dp[0] = i;

        for (int j = 1; j <= n; ++j) {
            int temp = dp[j];
            if (str1[i - 1] == str2[j - 1]) {
                dp[j] = prev;
            } else {
                dp[j] = 1 + min({ prev, dp[j], dp[j - 1] });
            }
            prev = temp;
        }
    }

    return dp[n];
}

int main() {
    string str1, str2;
    int distance = editDistance(str1, str2);
    cout << "The edit distance between \"" << str1 << "\" and \"" << str2 << "\" is: " << distance << endl;

    return 0;
}
