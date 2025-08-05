#include <iostream>

using namespace std;

/************************************************* CLASSES ************************************************************/

// Classe para o nó da Árvore
class node {
    public:
        node *left;
        node *right;
        int chave;
        int altura;

        // Construtor de nó
        node(int chave) {
            this->chave = chave;
            left = nullptr;
            right = nullptr;
            altura = 1;
        }
};

/*********************************************************************************************************************/

// Classe para a Árvore AVL
class BinTreeAVL {
    public:
        // Ponteiro para a raiz da Árvore
        node* raiz;

        // Construtor da raiz
        BinTreeAVL() { 
            raiz = nullptr;
        }

        void insert(int chave) { 
            raiz = insert(raiz, chave);
        }

        // Método para remove um nó
        void remove(int chave) { 
            raiz = remove(raiz, chave);
        }

        // Método para achar a altura de um nó
        int altura(node* no) const {
            return no ? no->altura : 0;
        }

        // Método para calcular o fator de balanceamento
        int fatorBalanceamento(node* no) const {
            return altura(no->left) - altura(no->right);
        }

        void atualizarAltura(node* no) {
            if (no) {
                no->altura = 1 + max(altura(no->left), altura(no->right));
            }
        }

        // Método de rotação Simples à Esquerda
        node* rotacaoSimplesEsquerda(node* no) {
            node* novaRaiz = no->right;

            no->right = novaRaiz->left;
            novaRaiz->left = no;
            atualizarAltura(no);
            atualizarAltura(novaRaiz);

            return novaRaiz;
        }

        // Método de rotação Simples à Direita
        node* rotacaoSimplesDireita(node* no) {
            node* novaRaiz = no->left;

            no->left = novaRaiz->right;
            novaRaiz->right = no;
            atualizarAltura(no);
            atualizarAltura(novaRaiz);
            
            return novaRaiz;
        }

        // Método para realizar Rotações Direita-Esquerda e Esquerda-Direita
        node* balancear(node* no) {
            atualizarAltura(no);
            int balanceamento = fatorBalanceamento(no);

            // Rotação Esquerda-Direita
            if (balanceamento > 1) {
                if (fatorBalanceamento(no->left) < 0) {
                    no->left = rotacaoSimplesEsquerda(no->left);
                }
                return rotacaoSimplesDireita(no);
            }

            // Rotação Direita-Esquerda
            if (balanceamento < -1) {
                if (fatorBalanceamento(no->right) > 0) {
                    no->right = rotacaoSimplesDireita(no->right);
                }
                return rotacaoSimplesEsquerda(no);
            }

            return no;
        }

        // Método para inserção de nó
        node* insert(node* no, int chave) {
            if (!no) {
                return new node(chave);
            }

            if (chave < no->chave) {
                no->left = insert(no->left, chave);
            } 
            else if (chave > no->chave) {
                no->right = insert(no->right, chave);
            } else {
                return no;
            }

            return balancear(no);
        }

        // Método para encontrar o nó com a maior chave da subárvore esquerda.
        node* encontrarMaximo(node* no) const {
            while (no && no->right) {
                no = no->right;
            }

            return no;
        }

        // Método para a remoção de nó
        node* remove(node* no, int chave) {
            if (!no) {
                return nullptr;
            }

            if (chave < no->chave) {
                no->left = remove(no->left, chave);
            } 
            else if (chave > no->chave) {
                no->right = remove(no->right, chave);
            } else {
                if (!no->left) {
                    node* temp = no->right;
                    delete no;
                    return temp;
                } 
                else if (!no->right) {
                    node* temp = no->left;
                    delete no;
                    return temp;
                }

                node* noMaximo = encontrarMaximo(no->left);
                no->chave = noMaximo->chave;
                no->left = remove(no->left, noMaximo->chave);
            }

            return balancear(no);
        }

        void preOrdem(node *n) {
            if (n != NULL) {
                cout << n->chave << ' ';
                preOrdem(n->left);
                preOrdem(n->right);
            }
        }

        void emOrdem(node *n) {
            if (n != NULL) {
                emOrdem(n->left);
                cout << n->chave << ' ';
                emOrdem(n->right);
            }
        }

        void posOrdem(node *n) {
            if (n != NULL) {
                posOrdem(n->left);
                posOrdem(n->right);
                cout << n->chave << ' ';
            }
        }
};

/********************************************** FUNÇÕES **************************************************************/

// Função para preecher um vetor alocado dinamicamente com números aleatórios
void preencherVetor(int vetor[], int vectorSize) {
    int numeroAnterior = 0;
    int x;

    for (int i = 0; i < vectorSize; i++) {
        x = rand() % 1001; // Soteia valores de 0 até 1000 (só para evitar a geração de números gigantescos)
        while (x == numeroAnterior) { // Evita valores repetidos
            x = rand() % 1001;
        }

        vetor[i] = x;
        numeroAnterior = x;
    }
};

// Função para impressão do vetor
void printVector(int vector[], int vectorSize) {
    cout << "Vetor inicial: [ ";

    for (int i = 0; i < vectorSize; i++) {
        cout << vector[i] << ' ';
    }

    cout << ']' << '\n' << '\n';
}

// Preenche a Árvore AVL com os elementos do vetor
BinTreeAVL preencherArvore(int vector[], int vectorSize) {
    BinTreeAVL arvore;

    for (int i = 0; i < vectorSize; i++) {
        arvore.insert(vector[i]);
    }

    return arvore;
}

// Função principal
int main() {
    
    BinTreeAVL arvoreAVL; // Objeto para a árvore AVL
    int tamanhoVetor; // Variável para o tamanho do vetor

    cout << "Insira o tamanho do vetor: ";
    cin >> tamanhoVetor; // Leitura pelo teclado do tamanho do vetor

    int *vetor = new int[tamanhoVetor]; // Aloca o vetor dinâmicamente

    preencherVetor(vetor, tamanhoVetor); // Preenche o vetor com números aleatórios
    arvoreAVL = preencherArvore(vetor, tamanhoVetor); // Preenche a Árvore com os elementos do vetor

    printVector(vetor, tamanhoVetor); // Imprime o vetor

    // Realiza os precursos de impressão da Árvore
    cout << "Em-Ordem: ";
    arvoreAVL.emOrdem(arvoreAVL.raiz);
    cout << '\n';
    cout << "Pre-Ordem: ";
    arvoreAVL.preOrdem(arvoreAVL.raiz);
    cout << '\n';
    cout << "Pós-Ordem: ";
    arvoreAVL.posOrdem(arvoreAVL.raiz);
    cout << '\n';

    delete[] vetor; // Desaloca o vetor

    return 0;
}
