#include <iostream>
using namespace std;

class No{//Classe nó
public:
    No(int valor){ //Método construtor.
        this->valor = valor;
        this->prox = NULL;
    }
    int valor; //O valor a ser armazenado a cada item.
    No* prox; //O endereço do próximo item.
};
//Basicamente uma reimplementação da estrutura de dados LDE, que também é explicada neste repositório
class LDE{
public:
    /**
     * A Classe LDE possuirá somente o endereço do primeiro nó.
     */
    No* primeiro; //Ponteiro para o primeiro nó de toda a lista.
    int n; //Variavel de controle referente ao tamanho.

    LDE(){
        primeiro = NULL; //Ao iniciar a lista, não existe nenhum item, logo não há apontamento.
        n = 0;
    }

    bool insere(int valor){
        No* novo = new No(valor); //Cria um ponteiro para um novo Nó com o determinado valor. :)
        if(!novo)
            return false;
        /**
         *   Nessas linhas define-se o movimento dos endereços.
         */
        No* anterior = NULL;
        No* proximo = primeiro;

        while(proximo != NULL && proximo->valor < valor){
            anterior = proximo; //Anterior terá o endereço do próximo, mantendo o passo.
            proximo = proximo->prox; //O próximo campo do item inserido.
        }

        if(anterior)
            anterior->prox = novo;
        else{
            primeiro = novo;
        }
        novo->prox = proximo;
        n++;
        return true;
    }
    void imprime(){
        No* temp = primeiro;
        for(int i=0; i < n; i++){
            cout << temp->valor << " ";
            temp = temp->prox;
        }
    }

    No* busca(int valor){
        No* atual = primeiro;
        while(atual && atual->valor < valor)
            atual = atual->prox;

        if(atual && atual->valor == valor)
            return atual;

        return NULL;
    }

    bool remove(int valor){
        No* proximo = primeiro;
        No* anterior = NULL;
        for(int i=0; i < n && proximo->valor != valor; i++) {
            anterior = proximo;
            proximo = proximo->prox;
        }
        if(!proximo || proximo->valor != valor){
            return false;
        }
        if(anterior){
            anterior->prox = proximo->prox;
        }
        else{
            primeiro = proximo->prox;
        }
        delete[]proximo;
        n--;
        return true;
    }

    void limpa(){
        No* atual = primeiro;
        No* temp;
        while(atual){
            temp = atual->prox;
            delete atual;
            atual = temp;
        }
        primeiro = NULL;
    }

    ~LDE(){
        limpa();
    }
};

//Implementação da estrutura Hash
class Hash{
private:
    //Calcula a chave da Hash de acordo com o número recebido
    int calcHash(int num){
        return num%this->max;
    }

public:
    LDE* v;
    int max;
    int n;
    //Construtor da Hash, recebe o tamanho máximo, inicializa o número de elementos da hash com 0 e aloca com número max de LDE's.
    Hash(int max){
        this->n= 0;
        this->v = new LDE[max];
        this->max = max;
    }
    //Destrutor da Hash
    ~Hash(){
        delete[] this->v;
    }

    //Insere um número na LDE de chave correspondente ao número e verifica se não estoura o vetor.
    bool insere(int num){
        if(this->n < this->max && v[calcHash(num)].insere(num)){
            this->n++;
            return true;
        }
        return false;
    }

    //Remove um número da hash
    bool remove(int num){
        if(v[calcHash(num)].remove(num)){
            this->n--;
            return true;
        }
        return false;
    }

    //Pesquisa um número, e retorna o nó que o possui.
    No* busca(int num){
        return v[calcHash(num)].busca(num);
    }
};

//Verifica se existe o número na Hash
void testaBusca(Hash& h, int num){
    if(h.busca(num)){
        cout << " valor " << num << " encontrado " << endl;
    }
    else{
        cout << " valor " << num << " não encontrado " << endl;
    }
}

int main() {
    /* Testes
    Hash h(300);

    h.insere(20);
    h.insere(22);
    h.insere(19);
    h.insere(10);
    h.insere(11);
    h.insere(90);

    testaBusca(h,20);
    testaBusca(h,22);
    testaBusca(h,19);
    testaBusca(h,10);
    testaBusca(h,34);
    testaBusca(h,24);
    testaBusca(h,12);
    testaBusca(h,90);

    h.remove(20);
    h.remove(22);
    h.remove(19);
    h.remove(10);
    h.remove(11);
    h.remove(90);
    */
    
    return 0;
}
