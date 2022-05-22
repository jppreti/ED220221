#include <iostream>
#include <string>
#include <queue> 
#include <unordered_map>

using namespace std;
 
#define EMPTY_STRING ""
 
//Arvore.
struct Node
{
    char ch;
    int freq;
    Node *left, *right;
};
 
//Função de alocação de novos nodes.
Node* getNode(char ch, int freq, Node* left, Node* right)
{
    Node* node = new Node();
 
    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;
 
    return node;
}
 
//Objeto de comparação para ordenação do heap.
struct comp
{
    bool operator()(const Node* l, const Node* r) const
    {
        //O item com menor frequencia tem maior prioridade -> MENOR FREQUENCIA = MAIOR PRIORIDADE.
        return l->freq > r->freq;
    }
};
 
//Função p/ checar se a arvore tem apenas um node.
bool isLeaf(Node* root) {
    return root->left == nullptr && root->right == nullptr;
}
 
//Percorre a arvore e gera um mapa com os codigos.
void encode(Node* root, string str, unordered_map<char, string> &huffmanCode)
{
    if (root == nullptr) {
        return;
    }
 
    // found a leaf node
    if (isLeaf(root)) {
        huffmanCode[root->ch] = (str != EMPTY_STRING) ? str : "1";
    }
 
    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}
 
//Percorre a arvore e decodifica a string codificada.
void decode(Node* root, int &index, string str)
{
    if (root == nullptr) {
        return;
    }
 
    //Alcançou uma folha da arvore.
    if (isLeaf(root))
    {
        cout << root->ch;
        return;
    }
 
    index++;
 
    if (str[index] == '0') {
        decode(root->left, index, str);
    }
    else {
        decode(root->right, index, str);
    }
}