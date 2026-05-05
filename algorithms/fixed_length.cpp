// بسم الله الرحمن الرحيم
// وَأَنْ لَيْسَ لِلْإِنسَانِ إِلَّا مَا سَعَىٰ
// Free Palestine
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define sz(x) (int)x.size()
#define nl '\n'

#include <bits/stdc++.h>
using namespace std;

class FixedLength
{
private:
    unordered_map<char, string> encode;
    unordered_map<string, char> decode;
    int fixedLen;

public:
    void build(const string &s)
    {
        set<char> unique;

        for (char c : s)
            unique.insert(c);

        vector<char> symbols(unique.begin(), unique.end());

        int n = symbols.size();

        if (n == 0)
            return;

        fixedLen = ceil(log2(n));

        for (int i = 0; i < n; i++)
        {
            string code = bitset<16>(i).to_string();
            code = code.substr(16 - fixedLen);

            encode[symbols[i]] = code;
            decode[code] = symbols[i];
        }
    }

    string compress(const string &s)
    {
        string res;

        for (char c : s)
        {
            res += encode[c];
        }

        return res;
    }

    string decompress(const string &bits)
    {
        string res;

        if (fixedLen == 0)
            return "";

        for (int i = 0; i < (int)bits.size(); i += fixedLen)
        {
            string cur = bits.substr(i, fixedLen);
            res += decode[cur];
        }

        return res;
    }
};

int main()
{

    FixedLength f;

    string s;
    getline(cin, s);

    f.build(s);

    string compressed = f.compress(s);
    cout << "Compressed: " << compressed << nl;

    string decompressed = f.decompress(compressed);
    cout << "Decompressed: " << decompressed << nl;

    return 0;
}
