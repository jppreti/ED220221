#include "Huffman.hpp"

using namespace std;

//Constroi a arvore, codifica e decodifica a string informada.
void buildHuffmanTree(string text)
{
    // #DEFINE EMPTY_STRING "" : Nada informado(string vazia). 
    if (text == EMPTY_STRING) {
        return;
    }
 
    //Registra desordenadamente a frequencia que cada caractere aparece na string
    unordered_map<char, int> freq;
    for (char ch: text) {
        freq[ch]++;
    }
 
    //Cria uma lista prioritaria p/ armazenar os caracteres.
    priority_queue<Node*, vector<Node*>, comp> pq;
 
    //Gera uma folha p/ cada caractere e adiciona na fila
    for (auto pair: freq) {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }
 
    //Roda até ter mais de um node na fila.
    while (pq.size() != 1)
    {
        //Remove os dois nodes com maior prioridade da fila.
 
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
 
        //Cria um node "pai" com os dois nodes de maior prioridade removidos da fila como "filhos" e com a frequencia equivalente a soma da frequencia dos "filhos". 
        //Adiciona o novo node "pai" na fila p/ ordenação

        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));
    }
 
    // Variavel "root" p/ armazenar a raiz da arvore.
    Node* root = pq.top();
 

    //Percorre a arvore e armazena cada caractere codificado em um "mapa".
    //Imprime o caractere e seu codigo.
    unordered_map<char, string> huffmanCode;
    encode(root, EMPTY_STRING, huffmanCode);
    
    //Imprime os codigos que foram armazenados no "mapa".
    cout << "\nTabela de codigos:\n" << endl;
    for (auto pair: huffmanCode) {
        cout << "  --  " << pair.first << "  -->  " << pair.second << endl;
    }

    //Imprime a string original.
    cout << "\nString original:\n" << text << endl;
 
    //Imprime ambas strings codificada e decodificada
    string str;
    for (char ch: text) {
        str += huffmanCode[ch];
    }
 
    cout << "\nString codificada:\n" << str << endl;
    cout << "\nString decodificada:\n";
 
    if (isLeaf(root))
    {
        //P/ casos como: a, aa, aaa...
        while (root->freq--) {
            cout << root->ch;
        }
    }
    else {
        //Percorre a arvore novamente e decodifica a string
        int index = -1;
        while (index < (int)str.size() - 1) {
            decode(root, index, str);
        }
    }
    cout << "\n\n";
}
 

int main()
{
    // https://www.random.org/strings/?num=10&len=20&upperalpha=on&loweralpha=on&unique=off&format=html&rnd=new

    string text = "jVNLHWrhnFyjOmtCBbOI SgMMFqjiXtVPAHefxzRk aIpiHLWTFyqltNwuhsIw etHygmWIGQkdjkuViWoU qobuClWzFCDjoJRwvhSQ RoNJecQqgZNTMCtiwnGS pnglsnkGvdQqTpxlAuAo DaBPnJGELuoxxdkuoQLE jjvSDQmtxfrTeCNkBPQH kcaVHRKpjxCeZUefkxRD";
    buildHuffmanTree(text);
 
    return 0;
}