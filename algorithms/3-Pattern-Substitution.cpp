// بسم الله الرحمن الرحيم
// وَأَنْ لَيْسَ لِلْإِنسَانِ إِلَّا مَا سَعَىٰ
// Free Palestine
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define sz(x) (int)x.size()
#define nl '\n'

/*
    LZ77 (Dictionary-based Compression - Sliding Window):

    A lossless text compression algorithm that replaces repeated
    substrings with references to previous occurrences in the text.

    - It does NOT use a fixed dictionary.
    - Instead, it uses a sliding window over previously processed data.
    - Repeated patterns are encoded as (offset, length, next_char).

    Each token means:
    - offset: how far back in the already processed text the match starts
    - length: how many characters are matched
    - next_char: the next new character after the match

    Sample:
    Input : ABAABABAABAAA
    Output: (0,0,A) (0,0,B) (2,1,B) (3,3,B) (3,3,A)

    Decompression:
    The original text is reconstructed by following backward references
    and copying characters from previously decoded output.

    Note:
    [1] LZ77 is widely used in real-world compression systems like ZIP,
    PNG, and other lossless compression formats.
    [2] Spaces are handled
*/

struct TAG
{
    int prv;
    int len;
    char nxt;
};

vector<TAG> compression(const string &s)
{
    int n = sz(s);
    vector<TAG> tags;
    for (int i = 0; i < n;)
    {
        int len = 0, prv = 0;
        for (int j = 0; j < i; j++)
        {
            int curLen = 0;
            while (i + curLen < n && s[j + curLen] == s[i + curLen])
                curLen++;

            if (curLen > len)
                len = curLen, prv = i - j;
        }

        if (len == 0)
        {
            tags.push_back({0, 0, s[i++]});
        }
        else
        {
            char nxt = (i + len < n ? s[i + len] : '\0');
            tags.push_back({prv, len, nxt});
            i += len + 1;
        }
    }

    return tags;
}

string decompression(const vector<TAG> &tags)
{
    string ans = "";
    int n = sz(tags);
    for (int i = 0; i < n; i++)
    {
        int prv = tags[i].prv, len = tags[i].len;
        char nxt = tags[i].nxt;

        if (prv == 0 && len == 0)
        {
            ans += nxt;
        }
        else
        {
            int st = sz(ans) - prv;
            for (int j = 0; j < len; j++)
                ans += ans[st + j];

            if (nxt != '\0')
                ans += nxt;
        }
    }

    return ans;
}

int main()
{

    string s;
    getline(cin, s);
    vector<TAG> ans = compression(s);
    cout << "Compression TAGs: " << nl;
    for (int i = 0; i < sz(ans); i++)
        cout << "<" << ans[i].prv << "," << ans[i].len << "," << ans[i].nxt << ">" << nl;

    cout << nl;
    cout << "Decompression: " << decompression(ans) << nl;

    return 0;
}
