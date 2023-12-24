#include <iostream>
#include <vector>

using namespace std;

// price: price for given length
// length: length of the bar
int rod_cutting_maximum_profit(vector<int> price, int length) {
    vector<int> dp(length + 1, 0);

    dp[0] = 0;
    for (int i = 1; i <= length; i++) {
        int maximum_profit = 0;
        for (int j = 1; j <= i; j++) {
            int profit = price[j] + dp[i - j];
            if (profit > maximum_profit) {
                maximum_profit = profit;
            }
        }
        dp[i] = maximum_profit;
    }
    return dp[length];
}

int main() {
    vector<int> price = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int length = 4;
    int max_profit = rod_cutting_maximum_profit(price, length);
    cout << "The maximum profit is: " << max_profit << endl;
    return 0;
}
