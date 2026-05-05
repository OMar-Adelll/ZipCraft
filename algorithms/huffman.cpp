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

//  NOTE : i made this template Using AI -> co-pilot

/*
    Huffman Algorithm:

    - Builds optimal prefix-free binary codes.
    - Uses frequency of characters.
    - Greedy approach with min-heap (priority queue).

    Steps:
    1. Count frequency
    2. Build min heap
    3. Build binary tree
    4. Generate codes
    5. Compress / Decompress
*/

class Huffman
{
public:
    unordered_map<char, string> encode;
    unordered_map<string, char> decode;

    struct Node
    {
        char ch;
        int freq;
        Node *left, *right;

        Node(char c, int f)
        {
            ch = c;
            freq = f;
            left = right = nullptr;
        }
    };

    struct cmp
    {
        bool operator()(Node *a, Node *b)
        {
            return a->freq > b->freq;
        }
    };

    Node *root = nullptr;

    void build(const string &s)
    {
        unordered_map<char, int> freq;

        for (char c : s)
            freq[c]++;

        priority_queue<Node *, vector<Node *>, cmp> pq;

        for (auto &p : freq)
            pq.push(new Node(p.first, p.second));

        while (pq.size() > 1)
        {
            Node *left = pq.top();
            pq.pop();
            Node *right = pq.top();
            pq.pop();

            Node *parent = new Node('\0', left->freq + right->freq);
            parent->left = left;
            parent->right = right;

            pq.push(parent);
        }

        root = pq.top();

        generateCodes(root, "");
    }

    void generateCodes(Node *node, string code)
    {
        if (!node)
            return;

        if (!node->left && !node->right)
        {
            encode[node->ch] = code;
            decode[code] = node->ch;
        }

        generateCodes(node->left, code + "0");
        generateCodes(node->right, code + "1");
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
    Huffman h;

    string s;
    getline(cin, s);

    h.build(s);

    string compressed = h.compress(s);
    cout << "Compressed: " << compressed << nl;

    string decompressed = h.decompress(compressed);
    cout << "Decompressed: " << decompressed << nl;

    return 0;
}