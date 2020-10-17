#include <iostream>

using namespace std;

//Classe nó da Árvore Binária, contém o valor, os nós filhos que ficarão à esquerda e direita, e o nó pai.
class No{
public:
    int valor;
    No* esq;
    No* dir;
    No* pai;
};

//Classe da Árvore Binária, com os métodos de inserir, imprimir e buscar
class Arv {
public:
    No* raiz;
    int quant;

    Arv(){
        raiz = NULL;
        quant = 0;
    }

    bool insere(int valor){
        No* pai = NULL;
        No* filho = raiz;

        No* novo = new No;
        novo->valor = valor;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->pai = NULL;

        //Caso não haja uma raiz, significa que a árvore está vazia, portanto o novo nó vira a raiz.
        if(raiz == NULL){
            raiz = novo;
            quant++;
            return true;
        }

        //Caso haja uma raiz, significa que ela pode ter filhos, portanto vira o nó pai
        while(filho) {
            pai = filho;
            //Se o valor do filho for menor que o do pai, o filho é alocado à esquerda.
            if (valor <= filho->valor) {
                filho = filho->esq;
            }
                //Se o valor do filho for maior que o do pai, o filho é alocado à direita.
            else {
                filho = filho->dir;
            }
        }

        //Agora faz os devidos apontamentos, seguindo a mesma lógica acima.
        novo->pai = pai;
        if(valor <= pai->valor){
            pai->esq = novo;
        }
        else{
            pai->dir = novo;
        }

        quant++;
        return true;
    }

    No* buscaArv(int valor){
        No* atual;
        if(raiz)
            atual = raiz;
        else
            return NULL;

        if(raiz->valor == valor)
            return raiz;

        while(atual){
            if(valor == atual->valor)
                return atual;
            else if(valor >= atual->valor)
                atual = atual->dir;
            else if(valor <= atual->valor)
                atual = atual->esq;
        }

        return NULL;
    }

    //Chamada recursiva para a impressão.
    void imprime (No* r) {
        if(r == NULL){
            return;
        }
        imprime(r->esq);
        imprime(r->dir);
        cout << r->valor << endl;
    }

    void imprime () {
        imprime(raiz);
    }

    No* buscaSucessor(No* atual){
        atual = atual->dir;
        if(atual->esq) {
            while (atual->esq) {
                atual = atual->esq;
            }
        }
        return atual;
    }

    bool remove(No* atual){
        No* pai = atual->pai;
        No* sucessor;

        if(!atual->esq && !atual->dir){ //Verifica se é um nó folha
            if(pai->valor > atual->valor)
                pai->esq = NULL;
            else
                pai->dir = NULL;
            delete atual;
        }
        else if(!atual->esq && atual->dir) {//Verifica se só tem o filho direito
            atual->dir->pai = pai;
            pai->dir = atual->dir;
            delete atual;
        }
        else if(!atual->dir && atual->esq) { //Verifica se só tem o filho esquerdo
            atual->esq->pai = pai;
            pai->esq = atual->esq;
            delete atual;
        }
        else{
            sucessor = buscaSucessor(atual);
            atual->valor = sucessor->valor;
            if(!atual->dir->esq)
                atual->dir = sucessor->dir;
            else
                sucessor->pai->esq = sucessor->esq;
            delete sucessor;
        }
        quant--;
        return true;
    }

    bool remove(int valor){
        return(remove(buscaArv(valor)));
    }

    //Chamada recursiva para destruir a árvore.
    void destrutorRecursivo(No* r){
        if(r){
            //Se o nó esquerdo do elemento existir, chama novamente a função, até que não haja nós no lado esquerdo
            if(r->esq)
                destrutorRecursivo(r->esq);
            //Se o nó direito do elemento existir, chama novamente a função, até que não haja nós no lado direito
            if(r->dir)
                destrutorRecursivo(r->dir);
            cout << "Deletando o Nó de valor:" << r->valor << endl;
            delete r;
        }
    }

    friend class Arv;

    virtual ~Arv(){
        destrutorRecursivo(raiz);
    }
};

using namespace std;
int main()
{
    /* Testes
    Arv a;
    int num;
    a.insere(40);
    a.insere(35);
    a.insere(46);
    a.insere(43);
    a.insere(51);
    a.insere(47);
    a.insere(54);
    a.insere(41);

    a.imprime(a.raiz);
    */

    //A funcionalidade da busca está implementada na função remove.
    return 0;
}
