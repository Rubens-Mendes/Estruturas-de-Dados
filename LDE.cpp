#include <iostream>
using namespace std;
/**
 * Uma lista dinâmica encadeada trata-se de uma lista onde os itens
 * não estão alocados em sequência na memória, mas sim, vários blocos em vários
 * lugares diferentes da memória.
 * Portanto, cada item, terá o número e o endereço (duas informações) para o próximo item.
 * o problema desse tipo de estrutura é o tempo para percorrer as informações, dado que,
 * para ir à um item específico, será necessário acessar todos anteriores antes dele.
 */
class No{//Classe nó
public:
    No(int valor){ //Método construtor.
        this->valor = valor;
        this->prox = NULL;
    }
    int valor; //O valor a ser armazenado a cada item.
    No* prox; //O endereço do próximo item.
};
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
        //Caso já haja um nó na estrutura, o próximo dele vira o nó novo
        if(anterior)
            anterior->prox = novo;
        //Senão o novo nó é o primeiro.
        else{
            primeiro = novo;
        }
        novo->prox = proximo;
        n++;
        return true;
    }

    //Função para imprimir todos os números da estrutura, inicia o loop pelo primeiro nó
    void imprime(){
        No* temp = primeiro;
        for(int i=0; i < n; i++){
            cout << temp->valor << " ";
            temp = temp->prox;
        }
    }

    //Função de busca que recebe um inteiro
    int busca(int valor){
        No* temp = primeiro;
        for(int i=0; i < n; i++) {
            if (temp->valor == valor)
                return i;
            temp = temp->prox;
        }
        return -1;
    }

    //A remoção é feita recebendo um valor inteiro, após achar o nó, são refeitos os devidos apontamentos
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
};

int main() {
    /* Testes
    cout << "INICIO" << endl;
    LDE x;
    x.insere(10);
    x.insere(3);
    x.insere(45);
    x.insere(6);

    int a = x.busca(45);
    cout << a << endl;

    if(x.remove(6)) {
        x.imprime();
    }
    */
    return 0;
}
