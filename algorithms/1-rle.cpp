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
    Run-Length Encoding (RLE):
    A simple lossless compression algorithm that replaces consecutive
    repeated characters with a pair of:
    1) the number of repetitions
    2) the repeated character

    - It works best when the input contains long runs of the same value.

    Sample:
    Input  : AAABB
    Encoded: 3A2B

    Another sample:
    Input  : AABCC
    Encoded: 2A1B2C

    Note:
    I handled the spaces.
*/

string compression(const string &s)
{
    string ans = "";
    int n = sz(s);
    for (int i = 0; i < n;)
    {
        int freq = 0;
        char cur = s[i];
        while (i < n && s[i] == cur)
            freq++, i++;

        ans += to_string(freq) + cur;
    }

    return ans;
}

string decompression(const string &s)
{
    string ans = "";
    int n = sz(s);

    for (int i = 0; i < n;)
    {
        int freq = 0;
        while (i < n && isdigit(s[i]))
        {
            freq = freq * 10 + (s[i] - '0');
            i++;
        }

        char cur = s[i++];
        while (freq--)
            ans += cur;
    }

    return ans;
}

int main()
{
    string s;
    getline(cin, s);

    string compressed = compression(s);
    cout << "Compressed: " << compressed << nl;
    cout << "Decompressed: " << decompression(compressed) << nl;

    return 0;
}
