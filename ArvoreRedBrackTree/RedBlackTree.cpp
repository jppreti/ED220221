#include <iostream>

using namespace std;

// estrutura representando um nó da arvore
typedef struct Node {
	int data;
	Node *parent; // ponteiro p/ o pai
	Node *left; // ponteiro p/ o filho da esquerda
	Node *right; // ponteiro p/ o filho da direita
	int color; // 0 -> PRETO , 1 -> VERMELHO
}*NodePtr;


// class RBTree : Implementação das operações na arvore
class RBTree {
private:
	NodePtr root;
	NodePtr TNULL;

	// inicialização dos nós
	// todos os ponteiros são inicializados apontando p/ o ponteiro vazio
	void initializeNULLNode(NodePtr node, NodePtr parent) {
		node->data = 0;
		node->parent = parent;
		node->left = nullptr;
		node->right = nullptr;
		node->color = 0;
	}

	void preOrderHelper(NodePtr node) {
		if (node != TNULL) {
			cout<<node->data<<" ";
			preOrderHelper(node->left);
			preOrderHelper(node->right);
		} 
	}

	void inOrderHelper(NodePtr node) {
		if (node != TNULL) {
			inOrderHelper(node->left);
			cout<<node->data<<" ";
			inOrderHelper(node->right);
		} 
	}

	void postOrderHelper(NodePtr node) {
		if (node != TNULL) {
			postOrderHelper(node->left);
			postOrderHelper(node->right);
			cout<<node->data<<" ";
		} 
	}

	NodePtr searchTreeHelper(NodePtr node, int key) {
		if (node == TNULL || key == node->data) {
			return node;
		}

		if (key < node->data) {
			return searchTreeHelper(node->left, key);
		} 
		return searchTreeHelper(node->right, key);
	}

	// função p/ correção da arvore após remoção de nós
	void fixDelete(NodePtr x) {
		NodePtr s;
		while (x != root && x->color == 0) {
			if (x == x->parent->left) {
				s = x->parent->right;
				if (s->color == 1) {
					// caso 3.1 : X tem o irmão VERMELHO
					s->color = 0;
					x->parent->color = 1;
					leftRotate(x->parent);
					s = x->parent->right;
				}

				if (s->left->color == 0 && s->right->color == 0) {
					// caso 3.2 : X tem o irmão PRETO e ambos sobrinhos PRETOS
					s->color = 1;
					x = x->parent;
				} else {
					if (s->right->color == 0) {
						// caso 3.3 : X tem o irmão PRETO, o sobrinho á esquerda VERMELHO e o sobrinho á direita PRETO
						s->left->color = 0;
						s->color = 1;
						rightRotate(s);
						s = x->parent->right;
					} 

					// caso 3.4 : X tem o irmão PRETO e o sobrinho á direita VERMELHO
					s->color = x->parent->color;
					x->parent->color = 0;
					s->right->color = 0;
					leftRotate(x->parent);
					x = root;
				}
			} else { // espelhados dos casos acima
				s = x->parent->left;
				if (s->color == 1) {
					// caso 3.1
					s->color = 0;
					x->parent->color = 1;
					rightRotate(x->parent);
					s = x->parent->left;
				}

				if (s->right->color == 0 && s->right->color == 0) {
					// caso 3.2
					s->color = 1;
					x = x->parent;
				} else {
					if (s->left->color == 0) {
						// caso 3.3
						s->right->color = 0;
						s->color = 1;
						leftRotate(s);
						s = x->parent->left;
					} 

					// caso 3.4
					s->color = x->parent->color;
					x->parent->color = 0;
					s->left->color = 0;
					rightRotate(x->parent);
					x = root;
				}
			} 
		}
		x->color = 0;
	}


	void rbTransplant(NodePtr u, NodePtr v){
		if (u->parent == nullptr) {
			root = v;
		} else if (u == u->parent->left){
			u->parent->left = v;
		} else {
			u->parent->right = v;
		}
		v->parent = u->parent;
	}

	void deleteNodeHelper(NodePtr node, int key) {
		// Busca pelo nó contendo o valor informado
		NodePtr z = TNULL;
		NodePtr x, y;
		while (node != TNULL){
			if (node->data == key) {
				z = node;
			}

			if (node->data <= key) {
				node = node->right;
			} else {
				node = node->left;
			}
		}

		if (z == TNULL) {
			cout<<"Não foi possivel localizar o valor informado"<<endl;
			return;
		} 

		y = z;
		int y_original_color = y->color;
		if (z->left == TNULL) {
			x = z->right;
			rbTransplant(z, z->right);
		} else if (z->right == TNULL) {
			x = z->left;
			rbTransplant(z, z->left);
		} else {
			y = minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z) {
				x->parent = y;
			} else {
				rbTransplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}

			rbTransplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		delete z;
		if (y_original_color == 0){
			fixDelete(x);
		}
	}
	
	// Corrige inserção na arvore
	void fixInsert(NodePtr k){
		NodePtr u;
		while (k->parent->color == 1) {
			if (k->parent == k->parent->parent->right) {
				u = k->parent->parent->left; // TIO
				if (u->color == 1) {
					// caso 3.1 : PAI e TIO são ambos VERMELHOS
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				} else {
					if (k == k->parent->left) {
						// caso 3.2.2 : PAI é o filho á direita e K é o filho á esquerda do PAI
						k = k->parent;
						rightRotate(k);
					}
					// case 3.2.1 : PAI é o filho á direita e K é o filho á direita do PAI
					k->parent->color = 0;
					k->parent->parent->color = 1;
					leftRotate(k->parent->parent);
				}
			} else { // espelhados dos casos acima
				u = k->parent->parent->right; // TIO

				if (u->color == 1) {
					// caso 3.1 
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;	
				} else {
					if (k == k->parent->right) {
						// caso 3.2.2 
						k = k->parent;
						leftRotate(k);
					}
					// caso 3.2.1 
					k->parent->color = 0;
					k->parent->parent->color = 1;
					rightRotate(k->parent->parent);
				}
			}
			if (k == root) {
				break;
			}
		}
		root->color = 0;
	}

	void printHelper(NodePtr root, string indent, bool last) {
		// imprime a estrutura da arvore "graficamente"
	   	if (root != TNULL) {
		   cout<<indent;
		   if (last) {
		      cout<<"R----";
		      indent += "     ";
		   } else {
		      cout<<"L----";
		      indent += "|    ";
		   }
            
           string sColor = root->color?"RED":"BLACK";
		   cout<<root->data<<"("<<sColor<<")"<<endl;
		   printHelper(root->left, indent, false);
		   printHelper(root->right, indent, true);
		}
	}

public:
	RBTree() {
		TNULL = new Node;
		TNULL->color = 0;
		TNULL->left = nullptr;
		TNULL->right = nullptr;
		root = TNULL;
	}

	// PreOrder 
	// Nó -> SubArvore Esquerda -> SubArvore Direita
	void preorder() {
		preOrderHelper(this->root);
	}

	// InOrder
	// SubArvore Esquerda -> Nó -> SubArvore Direita
	void inorder() {
		inOrderHelper(this->root);
	}

	// PostOrder
	// SubArvore Esquerda -> SubArvore Direita -> Nó
	void postorder() {
		postOrderHelper(this->root);
	}

	// Busca pelo valor informado e retorna o nó correspondente
	NodePtr searchTree(int k) {
		return searchTreeHelper(this->root, k);
	}

	// Localiza o nó de menor valor
	NodePtr minimum(NodePtr node) {
		while (node->left != TNULL) {
			node = node->left;
		}
		return node;
	}

	// Localiza o nó de maior valor
	NodePtr maximum(NodePtr node) {
		while (node->right != TNULL) {
			node = node->right;
		}
		return node;
	}
	
	void leftRotate(NodePtr x) {
		NodePtr y = x->right;
		x->right = y->left;
		if (y->left != TNULL) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->left) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void rightRotate(NodePtr x) {
		NodePtr y = x->left;
		x->left = y->right;
		if (y->right != TNULL) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->right) {
			x->parent->right = y;
		} else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	// insere o valor informado no local apropriado e corrige a arvore
	void insert(int key) {
		NodePtr node = new Node;
		node->parent = nullptr;
		node->data = key;
		node->left = TNULL;
		node->right = TNULL;
		node->color = 1; // todo nó novo deve ser VERMELHO

		NodePtr y = nullptr;
		NodePtr x = this->root;

		while (x != TNULL) {
			y = x;
			if (node->data < x->data) {
				x = x->left;
			} else {
				x = x->right;
			}
		}

		// Y é PAI de X
		node->parent = y;
		if (y == nullptr) {
			root = node;
		} else if (node->data < y->data) {
			y->left = node;
		} else {
			y->right = node;
		}

		// se o novo nó for a raiz, return
		if (node->parent == nullptr){
			node->color = 0;
			return;
		}

		if (node->parent->parent == nullptr) {
			return;
		}

		// corrige a arvore
		fixInsert(node);
	}

	NodePtr getRoot(){
		return this->root;
	}

	// deleta o nó informado
	void deleteNode(int data) {
		deleteNodeHelper(this->root, data);
	}

	// imprime a estrutura da arvore
	void prettyPrint() {
	    if (root) {
    		printHelper(this->root, "", true);
	    }
	}

};

int main() {
	RBTree bst;
	bst.insert(8);
	bst.insert(18);
	bst.insert(5);
	bst.insert(15);
	bst.insert(17);
	bst.insert(25);
	bst.insert(40);
	bst.insert(80);
	cout << endl << "Estrutura da Arvore: " << endl << endl;
    bst.prettyPrint();
	cout << endl; cout << "inOrder: "; bst.inorder(); cout << endl << endl;
    cout<< "##############################################" << endl;
    bst.deleteNode(5);
	bst.deleteNode(25);
	cout << "Removidos nós 5 e 25" << endl;
	cout << "Estrutura da Arvore: " << endl << endl;
	bst.prettyPrint();
	cout << endl; cout << "inOrder: "; bst.inorder(); cout << endl;
    cout<< "##############################################"<<endl;
	return 0;
}