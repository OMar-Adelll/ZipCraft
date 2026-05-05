// بسم الله الرحمن الرحيم
// وَأَنْ لَيْسَ لِلْإِنسَانِ إِلَّا مَا سَعَىٰ
// Free Palestine
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define sz(x) (int)x.size()
#define nl '\n'
#define all(x) x.begin(), x.end()

/*
    Simple Repetition Suppression (SRS):
    A simple text reduction algorithm that removes consecutive
    repeated characters and keeps only one copy of each run.

    - It works by scanning the string from left to right.
    - If the current character is different from the previous one,
      it is added to the result.

    Sample:
    Input : aaabbbccdaa
    Output: abcda

    Another sample:
    Input : Hellooo    Wooorld
    Output: Helo World

    Note:
    Spaces are handled because the input is read using getline().
*/

string suppress_repetition(const string &s)
{
    string ans = "";
    int n = sz(s);
    for (int i = 0; i < n; i++)
    {
        if (ans.empty() || s[i] != ans.back())
            ans += s[i];
    }

    return ans;
}

int main()
{
    string s;
    getline(cin, s);
    cout << suppress_repetition(s) << nl;

    return 0;
}
