#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define nl '\n'
#define all(x) (x).begin(), (x).end()

struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char ch, int freq) {
        left = right = nullptr;
        this->ch = ch;
        this->freq = freq;
    }
};

struct Compare {
    bool operator()(Node *l, Node *r) { return l->freq > r->freq; }
};

// DFS traversal to generate and store prefix codes
void generateCodes(Node *root, const string &str,
                   unordered_map<char, string> &huffmanCode) {
    if (root == nullptr) return;

    // If it's a leaf node, assign the code
    if (!root->left && !root->right) {
        huffmanCode[root->ch] =
            (str != "") ? str : "1"; // "1" handles single-character strings
        return;
    }

    generateCodes(root->left, str + "0", huffmanCode);
    generateCodes(root->right, str + "1", huffmanCode);
}

// Decodes the binary string back to original text
string decodeString(Node *root, const string &encodedString) {
    string decodedStr = "";
    Node *curr = root;
    for (char bit : encodedString) {
        if (bit == '0') curr = curr->left;
        else curr = curr->right;

        // Reached leaf node
        if (!curr->left && !curr->right) {
            decodedStr += curr->ch;
            curr = root;
        }
    }
    return decodedStr;
}

void buildHuffmanTree(const string &text) {
    if (text.empty()) return;

    // 1. Count frequencies of characters
    unordered_map<char, int> freqMap;
    for (char ch : text) {
        freqMap[ch]++;
    }

    // 2. Create a min-heap and insert all characters
    priority_queue<Node *, vector<Node *>, Compare> pq;
    for (auto pair : freqMap) {
        pq.push(new Node(pair.first, pair.second));
    }

    // 3. Build the tree
    while (pq.size() > 1) {
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();

        // Create a new internal node with character '\0' and sum of frequencies
        int sum = left->freq + right->freq;
        Node *internalNode = new Node('\0', sum);
        internalNode->left = left;
        internalNode->right = right;
        pq.push(internalNode);
    }

    // Root of the Huffman Tree
    Node *root = pq.top();

    // 4. Generate prefix codes
    unordered_map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    // Print the codes
    cout << "Huffman Codes:\n";
    for (auto pair : huffmanCode) {
        cout << pair.first << " : " << pair.second << "\n";
    }

    // 5. Encode the input string
    string encodedString = "";
    for (char ch : text) {
        encodedString += huffmanCode[ch];
    }
    cout << "\nEncoded String:\n" << encodedString << "\n";

    // 6. Decode the string
    string decodedString = decodeString(root, encodedString);
    cout << "\nDecoded String:\n" << decodedString << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    string text = "huffman coding";
    buildHuffmanTree(text);
    return 0;
}