// بسم الله الرحمن الرحيم
// وَأَنْ لَيْسَ لِلْإِنسَانِ إِلَّا مَا سَعَىٰ
// Free Palestine
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define sz(x) (int)x.size()
#define nl '\n'

/*
    Variable-Length Coding (Prefix-Free + Frequency-based idea):

    - Assigns shorter codes to more frequent characters
    - Ensures prefix-free property using predefined structure
*/

class VariableLength
{
private:
    unordered_map<char, string> encode;
    unordered_map<string, char> decode;
    unordered_map<char, double> freq;

    void buildFrequency(const string &s) // to get freq percentage of each char
    {
        int n = s.size();

        for (char c : s)
            freq[c]++;

        for (auto &p : freq)
            p.second = (p.second / n) * 100;
    }

    void buildCodes(const string &s) // build codes based on percentage
    {
        set<char> unique(s.begin(), s.end());

        vector<pair<char, double>> v;
        for (char c : unique)
            v.push_back({c, freq[c]});

        sort(v.begin(), v.end(), [](auto &a, auto &b)
             { return a.second > b.second; });

        vector<string> codes = {"0", "10", "110", "111", "1010", "1011", "1000", "1001"};

        for (int i = 0; i < v.size(); i++)
        {
            encode[v[i].first] = codes[i];
            decode[codes[i]] = v[i].first;
        }
    }

public:
    void build(const string &s)
    {
        buildFrequency(s);
        buildCodes(s);
    }

    string compress(const string &s)
    {
        string res;
        for (char c : s)
            res += encode[c];
        return res;
    }

    string decompress(const string &bits)
    {
        string res, cur;

        for (char b : bits)
        {
            cur += b;

            if (decode.count(cur))
            {
                res += decode[cur];
                cur.clear();
            }
        }

        return res;
    }
};

int main()
{

    VariableLength v;

    string s;
    getline(cin, s);

    v.build(s);

    string compressed = v.compress(s);
    cout << "Compressed: " << compressed << nl;

    string decompressed = v.decompress(compressed);
    cout << "Decompressed: " << decompressed << nl;

    return 0;
}