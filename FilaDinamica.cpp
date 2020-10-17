#include <iostream>
using namespace std;

/*A classe nó possui o valor, e o endereço do próximo nó.*/
class No{
public:
    int valor;
    No *proximo;

    // Construtor
    No(int valor){
        this->valor = valor; //Atribui um valor ao nó
        proximo = NULL;
    };
    // Destrutor
    virtual ~No(){
    };
};

/*Classe FilaDinamica possui o primeiro e ultimo nó no construtor, para que tenhamos melhor controle da remoção e inserção de elementos na lista.
  A ideia é que tenhamos uma fila que aumente o tamanho conforme forem adicionados mais valores a lista. A remoção é sempre do item que está na primeira
  posição da fila.*/
class FilaDinamica{
public:
    // Construtor
    FilaDinamica(){
        primeiro = NULL;
        ultimo = NULL;
    };

    //Método para adicionar um valor a fila.
    bool enfileira(int valor){
        No *novo = new No(valor);
        if(!novo)
            return false;

        //Se o último existir, o próximo dele passa a ser o novo nó
        if(ultimo)
            ultimo->proximo = novo;
        //Se não significa que o novo nó é o primeiro
        else
            primeiro = novo;

        //O último nó passa a ser o novo
        ultimo = novo;

        return true;
    }

    int desenfileira(bool *ok = NULL){
        //Se não houver números na fila retorna false
        if(!primeiro){
            if(ok)
                *ok = false;

            return 0;
        }

        //Passa o segundo nó para o primeiro
        int temp = primeiro->valor;
        primeiro = primeiro->proximo;
        if(ok)
            *ok = true;

        return temp;
    }

    //Limpa a fila
    void limpa(){
        No* atual = primeiro;
        No* prox;

        while(atual){
            prox = atual->proximo;
            delete atual;
            atual = prox;
        }
    }

    //Imprime os números da fila
    void imprime(){
        No* atual = primeiro;

        if(primeiro){
            while(atual){
                cout << atual->valor << " ";
                atual = atual->proximo;
            }
        }
        else{
            cout << "Sem registros na lista." << endl;
        }
    }

    // Destrutor
    virtual ~FilaDinamica(){
        limpa();
    };

private:
    No *primeiro;
    No *ultimo;
};

//Sobrecarga do operador "<<" para a impressão da fila com o cout
ostream& operator<< (ostream& os, FilaDinamica &f){
    f.imprime();
    return os;
}

int main() {
    /* Teste
    FilaDinamica f;
    FilaDinamica f2;
    f.enfileira(2);
    f.enfileira(8);
    f.enfileira(7);
    f.enfileira(6);
    f.enfileira(8);
    f.enfileira(6);

    f.desenfileira();
    f.desenfileira();

    f2.enfileira(4);
    f2.enfileira(7);
    f2.enfileira(1);
    f2.enfileira(2);

    f2.desenfileira();

    cout << f << endl;
    cout << f2 << endl;
    */
    
    return 0;
}

