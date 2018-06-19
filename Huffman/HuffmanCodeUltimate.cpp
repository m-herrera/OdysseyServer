#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <sstream>
#include "HuffmanCodeUltimate.h"
#include "Node.h"

using namespace std;
Node* HuffmanCodeUltimate::getNode(char ch, int freq, Node *left, Node *right) {
    Node* node = new Node();

    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}

struct comp
{
    bool operator()(Node* l, Node* r)
    {
        return l->freq > r->freq;
    }
};
void HuffmanCodeUltimate::encode(Node *root, string str, map<char, string> &huffmanCode) {
    if (root == nullptr){
        return;
}
    if (root->left== nullptr && root->right== nullptr) {
        huffmanCode[root->ch] = str;
    }
        encode(root->left, str + "0", huffmanCode);
        encode(root->right, str + "1", huffmanCode);

}
 //descomprime el codigo de huffman, el root es el del arbol que se hace cuando se envia
string HuffmanCodeUltimate::decode(Node *root, string str) {
    string ans = "";
    Node* curr = root;
    for (int i=0;i<str.size();i++)
    {
        if (str[i] == '0')
            curr = curr->left;
        else
            curr = curr->right;

        // reached leaf node
        if (curr->left==NULL && curr->right==NULL)
        {
            ans += curr->ch;
            curr = root;
        }
    }
     cout<<ans<<endl;
    return ans;
}
//este codigo es el que comprime, retorna ek string de huffman
string HuffmanCodeUltimate::buildHuffmanTree(string text) {
    map<char, int> freq;
    for (char ch: text) {
        freq[ch]++;
    }

    queue<Node*>* pq= new queue<Node*>();
    for (auto pair: freq) {
        Node* nodo=getNode(pair.first, pair.second, nullptr, nullptr);
        pq->push(nodo);
        cout<<nodo->ch;
    }
    while (pq->size() != 1)
    {
        Node *left = pq->front();
        pq->pop();
        Node *right = pq->front();
        pq->pop();
        int sum = left->freq +right->freq;
        pq->push(getNode('\0', sum, left, right));
    }


    Node* root = pq->front();
    map<char, string> huffmanCode;
    encode(root, "", huffmanCode);

    cout << "Huffman Codes are :\n" << '\n';
    for (auto pair: huffmanCode) {
        cout << pair.first << " " << pair.second << '\n';
    }

    cout << "\nOriginal string was :\n" << text << '\n';

    string sb;
    for (int i = 0 ; i < text.length(); i++) {
        sb+=huffmanCode.at(text[i]);
    }


    cout << "\nEncoded string is :\n" << sb << '\n';
    return sb;
}
/*
int main()
{
    HuffmanCodeUltimate::buildHuffmanTree("Que onda que pez");
    return 0;
}*/
