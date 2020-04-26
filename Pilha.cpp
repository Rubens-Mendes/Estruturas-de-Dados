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
    virtual ~No(){};
};

/*Classe PilhaDinâmica possui o nó do topo da pilha no construtor, para que tenhamos melhor controle da remoção e inserção de elementos na lista.
  A ideia é que tenhamos uma pilha que aumente o tamanho conforme forem adicionados mais valores a lista. A remoção é sempre do item que está no
  topo da pilha.*/
class PilhaDinamica{
public:
    // Construtor
    PilhaDinamica(){
        topo = NULL;
    };

    //Método para adicionar um valor a pilha.
    bool empilha(int valor){
        No *novo = new No(valor);
        if(!novo)
            return false;

        novo->proximo = topo;
        topo = novo;

        return true;
    }

    //Remove o elemento do topo da pilha
    int desempilha(bool* ok = NULL){
        if(!topo) {
            if (ok)
                *ok = false;
            return -1;
        }

        No *temp = topo->proximo;
        int ret = topo->valor;
        delete topo;
        topo = temp;
        if(ok){
            *ok = true;
        }

        return ret;
    }

    //Limpa a pilha
    void limpa(){
        No* atual = topo;
        No* prox;

        while(atual){
            prox = atual->proximo;
            delete atual;
            atual = prox;
        }
    }

    //Imprime os números da pilha
    void imprime(){
        No* atual = topo;

        if(topo){
            while(atual){
                cout << atual->valor << endl ;
                atual = atual->proximo;
            }
        }
        else{
            cout << "Sem registros na lista." << endl;
        }
    }

    // Destrutor
    virtual ~PilhaDinamica(){
        limpa();
    };

private:
    No *topo;
};

//Sobrecarga do operador "<<" para a impressão da pilha com o cout
ostream& operator<< (ostream& os, PilhaDinamica &p){
    p.imprime();
    return os;
}
//Testes
int main() {
    PilhaDinamica p;
    PilhaDinamica p2;
    p.empilha(10);
    p.empilha(9);
    p.empilha(8);
    p.empilha(7);
    p.empilha(6);
    p.empilha(5);
    p.empilha(4);

    p2.empilha(4);
    p2.empilha(7);
    p2.empilha(1);
    p2.empilha(2);

    cout << p << endl;
    cout << p2 << endl;

    p.desempilha();
    p.desempilha();
    p2.desempilha();

    cout << p << endl;
    cout << p2 << endl;

    return 0;
}

