#include <iostream>
using namespace std;

/*A LDS é uma das estruturas mais simples que existe, ela é composta de um vetor de tamanho fixo, portanto as inserções
 *são feitas linearmente até que seja atingido o limite do vetor. Porém uma particularidade da LDS é que ao atingir
 *seu limite, o tamanho do vetor é dobrado, e caso o número de elementos deste fique pela metade, o mesmo é dividido por 2*/
class LDS{
public:
    int *v; //Ponteiro para o início um vetor
    int n; //Variavel de controle n.
    int m; //Tamanho máximo do vetor
    LDS(){ //Método construtor.
        this->n = 0; //Inicializa o n.
        this->m = 5;
        this->v = new int[this->m];
    }

    //Dobra ou divide o tamanho do vetor.
    bool realocar(int capacidade){
        int* vCopia = new int[capacidade];
        if(vCopia == NULL){
            return false;
        }
        m = capacidade;
        for(int i=0; i < n; i++){
            vCopia[i] = v[i];
        }
        delete[] v;
        v = vCopia;
        return true;
    }
    bool insere(int valor){//Método que insere valores.
        if(n == m){ //Verifica se há espaços para inserir novos valores.
            //metodo realocar
            if(!realocar(this->m*2)){
                return false;
            }
        }

        if(n == 0){ //Verificação para inserir no indice 0, evitando lixo de memória.
            v[0] = valor;
            n++;
        }
        else {
            //Procura local de inserção
            int pos;
            for (pos = 0; v[pos] <= valor && pos < n; pos++);

            //Deslocamento de elementos
            for (int j = n - 1; j >= pos; j--) {
                v[j + 1] = v[j];
            }

            //Inserção do novo elemento
            v[pos] = valor;

            //Retorno e incremento
            n++;
        }

        return true;
    }

    void imprime(){
        for(int i = 0; i < n; i++){
            cout << v[i] << " ";
        }
        cout << "\n";
    }

    //Retorna o index do valor no vetor
    int busca(int valor){
        for(int i = 0; i < n; i++){
            if(v[i] == valor){
                return i;
            }
        }
        return -1;
    }

    //Faz uma remoção pelo index do valor e divide o tamanho do vetor por 2 caso o número de elementos fique pela metade
    bool remove(int index){
        for(int j = index; j < n -1; j++){
            v[j] = v[j+1];
        }
        n--;
        if(n==m/2){
            realocar(this->m/2);
        }
        return true;
    }
    //Destrutor
    ~LDS(){
        delete[] this->v;
        this-> m = 0;
        this-> n = 0;
    }
};
//Testes
int main() {
    LDS l;
    l.insere(3);
    l.imprime();
    l.insere(10);
    l.imprime();
    l.insere(7);
    l.imprime();
    l.insere(1);
    l.imprime();
    l.insere(5);
    l.imprime();
    l.insere(11);
    l.imprime();
    int x = l.busca(7);
    if(l.remove(x)){
        l.imprime();
    }
    return 0;
}
