// بسم الله الرحمن الرحيم
// وَأَنْ لَيْسَ لِلْإِنسَانِ إِلَّا مَا سَعَىٰ
// Free Palestine
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define sz(x) (int)x.size()
#define nl '\n'

/*
    Shannon-Fano Algorithm:

    - Computes frequency of chars
    - Sorts them in descending order
    - Recursively splits into two groups with similar total frequency
    - Assigns:
        left group  → '0'
        right group → '1'

    Result: Prefix-free variable-length codes (not always optimal)
*/

class ShannonFano
{
private:
    unordered_map<char, string> encode;
    unordered_map<string, char> decode;
    unordered_map<char, double> freq;

    void buildFrequency(const string &s)
    {
        int n = s.size();

        for (char c : s)
            freq[c]++;

        for (auto &p : freq)
            p.second = (p.second / n) * 100.0; // percentage
    }

    void buildCodes(vector<pair<char, double>> &v, int l, int r)
    {
        if (l >= r)
            return;

        double total = 0;
        for (int i = l; i <= r; i++)
            total += v[i].second;

        double sum = 0;
        int split = l;

        for (int i = l; i <= r; i++)
        {
            sum += v[i].second;
            if (sum >= total / 2)
            {
                split = i;
                break;
            }
        }

        // assign 0
        for (int i = l; i <= split; i++)
            encode[v[i].first] += "0";

        // assign 1
        for (int i = split + 1; i <= r; i++)
            encode[v[i].first] += "1";

        buildCodes(v, l, split);
        buildCodes(v, split + 1, r);
    }

public:
    void build(const string &s)
    {
        buildFrequency(s);

        vector<pair<char, double>> v(freq.begin(), freq.end());

        sort(v.begin(), v.end(),
             [](auto &a, auto &b)
             {
                 return a.second > b.second;
             });

        buildCodes(v, 0, v.size() - 1);

        for (auto &p : encode)
            decode[p.second] = p.first;
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

    ShannonFano sf;

    string s;
    getline(cin, s);

    sf.build(s);

    string compressed = sf.compress(s);
    cout << "Compressed: " << compressed << nl;

    string decompressed = sf.decompress(compressed);
    cout << "Decompressed: " << decompressed << nl;

    return 0;
}