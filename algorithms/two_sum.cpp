#include <iostream>
#include <vector>

using namespace std;

// v: sorted by default
pair<int, int> two_sum(vector<int> v, int target) {
    int i = 0;
    int j = v.size() - 1;

    // suppose we have a pair (a,b) that satisfies v[a] + v[b] == target, with a minimum and b maximum.
    // we notice that v[a] + v[j] > target for every j > b, and that v[i] + v[b] < target for every i < a.
    // at each step, j - i decreases by one, and if i == a is reached before j == b, then j > b and
    // we'll have v[i] + v[j] > target until j == b -- and vice versa. so the correctness of the algorithm is proved.
    while (j > i) {
        if (v[i] + v[j] < target) {
            i++;
        } else if (v[i] + v[j] > target) {
            j--;
        } else {
            return {i, j};
        }
    }
    return {-1, -1};
}

int main() {
    vector<int> nums = {2, 7, 11, 13, 15};
    int target = 20;
    pair<int, int> indices = two_sum(nums, target);
    cout << "Indices: " << indices.first << ", " << indices.second << endl;

    return 0;
}
