#include <iostream>
using namespace std;
/**
 * Uma lista dinâmica duplamente encadeada trata-se de uma lista onde os itens
 * não estão alocados em sequência na memória, mas sim, vários blocos em vários
 * lugares diferentes da memória.
 * Portanto, cada item, terá o valor e os endereços dos itens vizinhos(sucessores e antecessores).
 * o problema desse tipo de estrutura é o tempo para percorrer as informações, dado que,
 * para ir à um item específico, será necessário acessar todos anteriores antes dele.
 */
class No{//Classe nó
public:
    No(int valor){ //Método construtor.
        this->valor = valor;
        this->prox = NULL;
        this->ante = NULL;
    }
    int valor; //O valor a ser armazenado a cada item.
    No* prox; //O endereço do próximo item.
    No* ante; //O endereço do item anterior
};
class LDDE{
public:
    /**
     * A Classe LDDE possuirá o endereço do primeiro e do último nó.
     */
    No* primeiro; //Ponteiro para o primeiro nó de toda a lista.
    No* ultimo; //Ponteiro para o último nó de toda a lista.
    int n; //Variavel de controle referente ao tamanho.

    LDDE(){
        primeiro = NULL; //Ao iniciar a lista, não existe nenhum item, logo não há apontamento.
        ultimo = NULL;
        n = 0;
    }

    //A insersão é feita em ordem crescente
    bool insere(int valor){
        No* novo = new No(valor); //Cria um ponteiro para um novo Nó com o determinado valor.
        if(!novo)
            return false;
        No* atual = primeiro;
        No* anterior = NULL;

        while(atual != NULL && atual->valor < valor){
            anterior = atual;
            atual = atual->prox; //O próximo campo do item inserido.
        }

        if(anterior) {
            //O ponteiro anterior aponta para o novo
            anterior->prox = novo;
            //O novo aponta para o anterior
            novo->ante = anterior;
        }
            //Se não houver anteriores, o novo número será o primeiro.
        else{
            primeiro = novo;
        }

        if(atual)
            //Como atual é o primeiro número maior que o número novo, significa que o anterior vira o novo nó.
            atual->ante = novo;
        else{
            //Senão significa que o novo nó é o último.
            ultimo = novo;
        }
        novo->prox = atual;
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

    //A busca retorna o index do valor digitado
    int busca(int valor){
        No* temp = primeiro;
        for(int i=0; i < n; i++) {
            if (temp->valor == valor)
                return i;
            temp = temp->prox;
        }
        return -1;
    }

    bool remove(int valor){
        No* proximo = primeiro;
        No* anterior = NULL;
        for(int i=0; i < n && proximo->valor != valor; i++) {
            anterior = proximo;
            proximo = proximo->prox;
        }
        //Se o ponteiro não existir ou o valor do nó for diferente do valor recebido, retorna falso
        if(!proximo || proximo->valor != valor){
            return false;
        }

        //Se anterior existir, significa que o nó a ser excluído não é o primeiro, então, o proximo do anterior vira o próximo do atual
        if(anterior){
            anterior->prox = proximo->prox;
        }
            //Senão significa que o nó a ser deletado é o primeiro.
        else{
            primeiro = proximo->prox;
        }

        //Se o próximo existir, significa que o nó a ser excluído não é o último, então o anterior do próximo vira o anterior do atual
        if(proximo->prox)
            proximo->prox->ante = anterior;
            //Senão significa que o nó a ser deletado é o último.
        else
            ultimo = anterior;

        delete proximo;
        n--;
        return true;
    }
};

//Testes
int main() {
    LDDE x;
    x.insere(10);
    x.insere(3);
    x.insere(45);
    x.insere(6);

    int a = x.busca(6);
    cout << "O valor esta na posicao: " << a << endl;

    x.imprime();
    cout << endl;

    x.remove(6);
    x.imprime();
    return 0;
}
