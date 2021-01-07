#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    map<int, int> events;

    vector<int> a(n), b(n), p(n);

    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i] >> p[i];
        ++b[i];
        events[a[i]];
        events[b[i]];
    }

    int total = 0;
    for (auto &event : events) {
        event.second = total++;
    }

    vector<vector<pair<int, int>>> projects(total);

    for (int i = 0; i < n; ++i) {
        projects[events[b[i]]].emplace_back(events[a[i]], p[i]);
    }

    vector<long long> dp(total);

    for (int i = 0; i < total; ++i) {
        if (i) dp[i] = dp[i - 1];
        for (auto &project : projects[i]) {
            dp[i] = max(dp[i], dp[project.first] + project.second);
        }
    }

    cout << dp[total - 1] << endl;
}
