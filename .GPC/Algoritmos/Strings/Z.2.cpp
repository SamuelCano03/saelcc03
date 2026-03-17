#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> calculateZArray(const string& str) {
    int n = str.length();
    vector<int> Z(n, 0);

    int left = 0, right = 0;
    for (int i = 1; i < n; i++) {
        if (i <= right) {
            Z[i] = min(right - i + 1, Z[i - left]);
        }

        while (i + Z[i] < n && str[Z[i]] == str[i + Z[i]]) {
            Z[i]++;
        }

        if (i + Z[i] - 1 > right) {
            left = i;
            right = i + Z[i] - 1;
        }
    }

    return Z;
}

void searchPattern(const string& text, const string& pattern) {
    string concat = pattern + "$" + text;
    int patternLength = pattern.length();
    int concatLength = concat.length();

    vector<int> Z = calculateZArray(concat);

    for (int i = patternLength + 1; i < concatLength; i++) {
        if (Z[i] == patternLength) {
            cout << "Pattern found at index " << (i - patternLength - 1) << endl;
        }
    }
}

int main() {
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABAAABA";
    auto v=calculateZArray(pattern);
    for(auto e: v)cout<<e<<" ";
    cout<<endl;
    searchPattern(text, pattern);

    return 0;
}
