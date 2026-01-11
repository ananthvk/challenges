#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n, m, k, t;
    vector<int> a, b;
    cin >> n >> m >> k;

    // Desired apartment size
    for (int i = 0; i < n; i++)
    {
        cin >> t;
        a.push_back(t);
    }

    // Actual apartment sizes
    for (int i = 0; i < m; i++)
    {
        cin >> t;
        b.push_back(t);
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int j = 0;
    int answer = 0;
    // For each applicant
    for (int i = 0; i < n; i++)
    {
        while (j < m && a[i] > (b[j] + k))
        {
            j++;
        }
        if (j == m)
            break;
        // Check if an apartment exists for this person
        if (a[i] >= (b[j] - k) && a[i] <= (b[j] + k))
        {
            // Allot the apartment
            answer += 1;
            j++;
        }
    }
    cout << answer << endl;
}