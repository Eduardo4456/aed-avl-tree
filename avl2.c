#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
<<<<<<< HEAD
#include <assert.h>
=======
>>>>>>> 0bedc7be508e06fb8981682ca228c9db49bfd31f

//estrutura de um nó da árvore
typedef struct node {
    int value;//valor do nó
    struct node *left, *right;//ponteiros para os filhos
    short heig;//altura do nó
}Node;

//função que cria um novo nó
Node* newNode(int x) {
    Node *new = malloc(sizeof(Node));

    //verifica se a alocação foi bem sucedida
    if(new) {
        //inicializa os valores do nó, esquerda e direita como NULL e altura como 0
        new->value = x;
        new->left = NULL;
        new->right = NULL;
        new->heig = 0;
    } else {
        printf("\nerro ao alocar um novo nó.");
    }
    
    //retorna o ponteiro para o novo nó
    return new;
}

//descobre a altura da subarvores a esquerda e direita e compara os valores
short bigger(short a, short b) {
    return (a > b)? a:b;
}

//dado um nó ela retorna a altura dele
short heigNode(Node *node) {
    if(node == NULL) {
        return -1;
    } else {
        return node->heig;
    }
}

//calcular e retornar o fator de balanceamento de um nó
short balancingFactor(Node *node) {
    if(node) {
        return (heigNode(node->left) - heigNode(node->right));
    } else {
        return 0;
    }
}

//função de rotação a esquerda
Node* leftRotation(Node *r) {
    
    Node *y, *f;

    //y recebe o filho direito de r e f recebe o filho esquerdo de y
    y = r->right;
    f = y->left;

    //realiza a rotação
    y->left = r;
    r->right = f;

    //recauculando altura após a rotação
    r->heig = bigger(heigNode(r->left), heigNode(r->right)) + 1;//a altura de r é recalculada como o maior valor entre a altura do filho esquerdo e a altura do filho direito, somando 1
    y->heig = bigger(heigNode(y->left), heigNode(y->right)) + 1;//a altura de y é recalculada da mesma forma

    //retorna o novo nó raiz da subárvore após a rotação
    return y;
}

//função de rotação a direita
Node* rightRotation(Node *r) {
    
    Node *y, *f;

    //y recebe o filho esquerdo de r e f recebe o filho direito de y
    y = r->left;
    f = y->right;

    //realiza a rotação
    y->right = r;
    r->left = f;

    //recauculando altura após a rotação
    r->heig = bigger(heigNode(r->left), heigNode(r->right)) + 1;
    y->heig = bigger(heigNode(y->left), heigNode(y->right)) + 1;

    return y;
}

//Rotação dupla direita esquerda
Node* rightLeftRotation(Node *r) {
    //realiza a rotação direita no filho direito de r e depois realiza a rotação esquerda em r
    r->right = rightRotation(r->right);
    return leftRotation(r);
}

//Rotação dupla esquerda direita
Node* leftRightRotation(Node *r) {
    //realiza a rotação esquerda no filho esquerdo de r e depois realiza a rotação direita em r
    r->left = leftRotation(r->left);
    return rightRotation(r);
}

//função que balanceia a árvore
Node* balance(Node *root) {
    //calcula o fator de balanceamento do nó raiz
    short fb = balancingFactor(root);

    //o fator de balanceamento decide como a árvore vai rotacionar

    //rotação a esquerda
    if(fb < -1 && balancingFactor(root->right) <= 0) {
        root = leftRotation(root);
    } 
    //rotação a direita
    else if(fb > 1 && balancingFactor(root->left) >= 0){
        root = rightRotation(root);
    } 
    //rotação dupla a esquerda
    else if(fb > 1 && balancingFactor(root->left) < 0) {
        root = leftRightRotation(root);
    } 
    //rotação dupla a direita
    else if(fb < -1 && balancingFactor(root->right) > 0) {
        root = rightLeftRotation(root);
    }

    return root;
}

/*
    Insere o novo nó na árvore
    root -> raiz da árvore
    x -> valor a ser inserido
*/

Node* insert(Node *root, int x) {
    //verifica se a raiz é NULL, caso seja cria um novo nó com o valor x
    if(root == NULL) {
        return newNode(x);
    //caso contrário, verifica se o valor x é menor ou maior que o valor do nó raiz e chama a função insert recursivamente para inserir o novo nó na subárvore esquerda ou direita
    } else {
        if(x < root->value) {
            root->left = insert(root->left, x);
        } else if(x > root->value) {
            root->right = insert(root->right, x);
        } else {
            printf("\ninserção não realizada.");
        }
    }

    //recalcula a altura de todos os nós entre a raiz e o novo nó inserido
    root->heig = bigger(heigNode(root->left), heigNode(root->right)) + 1;

    //balanceia a árvore após a inserção do novo nó
    root = balance(root);

    //retorna a raiz da árvore após a inserção e balanceamento
    return root;
}

//remoção de um nó
Node* removeNode(Node *root, int key) {
    
    if(root == NULL) {
        printf("valor não encontrado\n");
        return NULL;
    } else { //procura um nó para remover
        //verifica se o valor do nó raiz é igual ao valor a ser removido
        if(root->value == key) {
            //remover nós folhas (nós sem filhos)
            if(root->left == NULL && root->right == NULL){
                free(root);//libera a memória do nó
                printf("elemento folha removido: %d !\n", key);//informa nó removido
                return NULL;//retorna NULL para o ponteiro do nó removido
            }
            else {
                //remoção de nós com dois filhos
                if(root->left != NULL && root->right != NULL) {
                    //procura o maior valor da subárvore esquerda
                    Node *aux = root->left;
                    while(aux->right != NULL) {
                        aux = aux->right;
                    }
                    //troca o valor do nó raiz com o maior valor da subárvore esquerda
                    root->value = aux->value;
                    //remove o nó que foi trocado
                    aux->value = key;
                    printf("elemento trocado: %d !\n", key);
                    //chama a função removeNode recursivamente para remover o nó que foi trocado
                    root->left = removeNode(root->left, key);

                    //recalculando altura e chamando balance
                    root->heig = bigger(heigNode(root->left), heigNode(root->right)) + 1;
                    //balanceia a árvore após a remoção do nó
                    return balance(root);
                } else {
                    //remoção de nós com só um filho
                    Node *aux;
                    //verifica se o filho esquerdo do nó raiz é diferente de NULL
                    if(root->left != NULL) {
                        //aux recebe o filho esquerdo do nó raiz
                        aux = root->left;
                    } else {
                        //aux recebe o filho direito do nó raiz
                        aux = root->right;
                    }
                    //libera a memória do nó raiz
                    free(root);
                    printf("elemento com 1 filho removido: %d !\n", key);
                    //retorna o ponteiro para o filho do nó removido
                    return aux;
                }
            }
        } else {
            //verifica se o valor a ser removido é menor ou maior que o valor do nó raiz
            if(key < root->value) {
                //chama a função removeNode recursivamente para remover o nó na subárvore esquerda
                root->left = removeNode(root->left, key);
            } else {
                //chama a função removeNode recursivamente para remover o nó na subárvore direita
                root->right = removeNode(root->right, key);
            }
        }
        //recalcula altura e chama balance
        root->heig = bigger(heigNode(root->left), heigNode(root->right)) + 1;

        root = balance(root);

        //retorna a raiz da árvore após a remoção e balanceamento
        return root;
    }
}

//função que imprime a árvore em ordem, com a raiz no topo e os filhos à esquerda e à direita
void printTree(Node *root, int level) {
    //verifica se a raiz é NULL, caso seja retorna
    if(root == NULL) return;

    //chama a função printTree recursivamente para imprimir a subárvore direita, aumentando o nível em 1
    printTree(root->right, level + 1);

    //imprime espaços em branco para representar o nível da árvore
    for(int i = 0; i < level; i++) printf("    ");
    //imprime o valor do nó raiz
    printf("%d (h=%d)\n", root->value, root->heig);
    //chama a função printTree recursivamente para imprimir a subárvore esquerda, aumentando o nível em 1
    printTree(root->left, level + 1);
}

<<<<<<< HEAD
// Função de comparação
int int_comp(const void *a, const void *b)
{   
    //converte os ponteiros para inteiros e retorna a diferença entre eles
    return (*(int *)a - *(int *)b);
}
=======
/*------------------------------------------------------------------------------
 * Permutação de um Arranjo
 *
 * Implementan o algoritmo iterativo de Narayana Pandita para a permutação de
 * um arranjo em ordem lexicográfica.
 */

 //Função auxiliar para trocar dois elementos de um arranjo
void swap(int *a, int *b)
{
    const int temp = *a;
    *a = *b;
    *b = temp;
}

//Função auxiliar para inverter um arranjo entre os índices inicio e fim
void perm_invert(int *arr, int inicio, int fim)
{
    while (inicio < fim) {
        swap(&arr[inicio], &arr[fim]);
        inicio++;
        fim--;
    }
}

//Função que gera a próxima permutação lexicográfica de um arranjo
bool perm_next(int *arr, int tamanho)
{
    int i = tamanho - 2;

    while (i >= 0 && arr[i] >= arr[i + 1]) {
        i--;
    }

    if (i < 0) {
        return false;
    }

    int j = tamanho - 1;
    while (arr[j] <= arr[i]) {
        j--;
    }

    swap(&arr[i], &arr[j]);

    perm_invert(arr, i + 1, tamanho - 1);

    return true;
}

/*------------------------------------------------------------------------------
 * Funções Auxiliares
 */

 //Função que imprime os elementos de um arranjo
void data_print(const int * const data, const int N)
{
    printf("data: [ ");
    for (int i = 0; i < N; i++) {
        printf("%02d ", data[i]);
    }
    printf("]\n");
}

//Função que remove todas as ocorrências de um valor em um arranjo e retorna o novo tamanho do arranjo
int arr_remove(int *arr, int N, int value)
{
    for (int i = 0; i < N; i++) {
        if (arr[i] == value) {
            for (int j = i; j < N - 1; j++) {
                arr[j] = arr[j + 1];
            }
            N--;
            i--;
        }
    }

    return N;
}

int main() {
    Node *root = NULL;
    root = insert(root, 2);
    root = insert(root, 10);
    root = insert(root, 1);
    root = insert(root, 3);
    root = insert(root, 4);
    root = insert(root, 5);
    printTree(root, 0);
>>>>>>> 0bedc7be508e06fb8981682ca228c9db49bfd31f

//função que calcula o tamanho da árvore
int avl_size(Node *x)
{  
    if (x == NULL) 
        return 0;
    else
        return 1 + avl_size(x->left) + avl_size(x->right);
}

//função para armazenar os valores da árvore em um arranjo em ordem crescente
void avl_store(Node *nd, int *arr, int *index)
{   
    if (nd) {
        avl_store(nd->left, arr, index);
        arr[(*index)++] = nd->value;
        avl_store(nd->right, arr, index);
    }
}

//função que verifica se a árvore contém os mesmos valores que o arranjo fornecido
bool avl_check(Node *nd, const int * const data, const int N) {
    const int tsize = avl_size(nd);

    if (tsize != N) {
        return false;
    }
    if (N == 0) {
        return true;
    }

    int *arr = (int *)malloc(sizeof(int) * N);
    memcpy(arr, data, sizeof(int) * N);
    qsort(arr, N, sizeof(int), int_comp);

    int *tarr = (int *)malloc(sizeof(int) * tsize);
    int index = 0;
    avl_store(nd, tarr, &index);

    bool match = true;
    for (int i = 0; i < N && match; i++) {
        if (arr[i] != tarr[i]) {
            match = false;
        }
    }

    free(tarr);
    free(arr);

    return match;
}

/*------------------------------------------------------------------------------
 * Permutação de um Arranjo
 *
 * Implementan o algoritmo iterativo de Narayana Pandita para a permutação de
 * um arranjo em ordem lexicográfica.
 */

 //função para trocar dois elementos de um arranjo
void swap(int *a, int *b)
{
    const int temp = *a;
    *a = *b;
    *b = temp;
}

//função para inverter um arranjo entre os índices inicio e fim
void perm_invert(int *arr, int inicio, int fim)
{
    while (inicio < fim) {
        swap(&arr[inicio], &arr[fim]);
        inicio++;
        fim--;
    }
}

//função que gera a próxima permutação lexicográfica de um arranjo
bool perm_next(int *arr, int tamanho)
{
    int i = tamanho - 2;

    while (i >= 0 && arr[i] >= arr[i + 1]) {
        i--;
    }

    if (i < 0) {
        return false;
    }

    int j = tamanho - 1;
    while (arr[j] <= arr[i]) {
        j--;
    }

    swap(&arr[i], &arr[j]);

    perm_invert(arr, i + 1, tamanho - 1);

    return true;
}

/*------------------------------------------------------------------------------
 * Funções Auxiliares
 */

 //função que imprime os elementos de um arranjo
void data_print(const int * const data, const int N)
{
    printf("data: [ ");
    for (int i = 0; i < N; i++) {
        printf("%02d ", data[i]);
    }
    printf("]\n");
}

//função que remove todas as ocorrências de um valor em um arranjo e retorna o novo tamanho do arranjo
int arr_remove(int *arr, int N, int value)
{
    for (int i = 0; i < N; i++) {
        if (arr[i] == value) {
            for (int j = i; j < N - 1; j++) {
                arr[j] = arr[j + 1];
            }
            N--;
            i--;
        }
    }

    return N;
}

int main() {
    
    // Dados de teste para inserção e remoção
    int DATA_INSERT[] = {10, 25, 40, 55, 70}; // DEVE estar ordenado!
    int DATA_REMOVE[] = {10, 25, 40, 55, 70}; // DEVE estar ordenado!
    const int N = 5; // tamanho dos arranjos de inserção e remoção
    
    //ponteiros para os dados de inserção e remoção
    int *data_insert, *data_remove;
    
    //aloca memória para os dados de inserção e cópia dos dados base
    data_insert = (int *)malloc(sizeof(int) * N);
    memcpy(data_insert, DATA_INSERT, sizeof(int) * N);
    
    do { // Loop de Inserção
        
        //aloca memória para os dados de remoção e cópia dos dados base
        data_remove = (int *)malloc(sizeof(int) * N);
        memcpy(data_remove, DATA_REMOVE, sizeof(int) * N);

        do { // Loop de Remoção
            Node *root = NULL;

            printf("--------------------------------------------\n");
            printf("Dados para Insercao:\n\t");
            data_print(data_insert, N);
            
            //inserção dos elementos na árvore
            for (int i = 0; i < N; i++) {
                printf("Inserindo: %02d\n", data_insert[i]);
                root = insert(root, data_insert[i]);
                printTree(root, 0);
                //verifica se a árvore contém os mesmos valores que o arranjo de inserção
                assert(avl_check(root, data_insert, i + 1));
            }
            
            printf("Arvore apos todas as INSERCOES:\n");
            printTree(root, 0);

            printf("Dados para Remocao:\n\t");
            data_print(data_remove, N);
            //aloca memória para um arranjo auxiliar que armazena os elementos da árvore
            int *arr = (int *)malloc(sizeof(int) * N);
            int asize = N;
            memcpy(arr, data_insert, sizeof(int) * asize);
            
            //remoção dos elementos da árvore
            for (int i = 0; i < N; i++) {
                printf("Removendo: %02d\n", data_remove[i]);
                root = removeNode(root, data_remove[i]);
                printTree(root, 0);
                asize = arr_remove(arr, asize, data_remove[i]);
                //verifica se a árvore contém os mesmos valores que o arranjo auxiliar
                assert(avl_check(root, arr, asize));
            }
            
            printf("Arvore apos todas as REMOCOES:\n");
            printTree(root, 0);
            //libera a memória do arranjo auxiliar
            free(arr);

        //Faz enquanto houverem permutações possíveis para os dados de remoção
        } while (perm_next(data_remove, N));
        
        //libera a memória dos dados de remoção
        free(data_remove);
    //Faz enquanto houverem permutações possíveis para os dados de inserção
    } while (perm_next(data_insert, N));
    
    //libera a memória dos dados de inserção
    free(data_insert);

    return EXIT_SUCCESS;
}
