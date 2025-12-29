#include <bits/stdc++.h>
using namespace std;
int dp[520520], a[520520];
int lengthOfLDS(vector<int> &nums) {
  vector<int> tails;
  for (int num : nums) {
    auto it = upper_bound(tails.begin(), tails.end(), num, greater<int>());
    if (it == tails.end()) {
      tails.push_back(num);
    } else {
      *it = num;
    }
  }
  return tails.size();
}
int lengthOfLIS(vector<int> &nums) {
  vector<int> tails;
  for (int num : nums) {
    auto it = lower_bound(tails.begin(), tails.end(), num);
    if (it == tails.end()) {
      tails.push_back(num);
    } else {
      *it = num;
    }
  }
  return tails.size();
}
int main() {
  int n;
  cin >> n;
  if (n == 0) {
    return 0;
  }
  vector<int> d(n + 1), nums(n + 1);
  for (int i = 0; i < n; i++)
    cin >> nums[i];
  int len = 1;
  d[len] = nums[0];
  for (int i = 1; i < n; ++i) {
    if (nums[i] > d[len]) {
      d[++len] = nums[i];
    } else {
      int l = 1, r = len, pos = 0;
      while (l <= r) {
        int mid = (l + r) >> 1;
        if (d[mid] < nums[i]) {
          pos = mid;
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
      d[pos + 1] = nums[i];
    }
  }
  return len;
}