#include <iostream>
#define COUNT 10
using namespace std;

class No
{
public:
  int valor;
  int altura;
  No *pai;
  No *fDir;
  No *fEsq;
  No()
  { //Construtor
    pai = NULL;
    fDir = NULL;
    fEsq = NULL;
    altura = 0; //Todo novo nó inserido é uma folha, logo altura = 0.
  }
};

class ArvBusca
{
private:
  No *raiz;
  int qntElementos;
  //Método que imprime todos os nós de maneira recursiva in-order.
  void imprime(No *r)
  {
    if (r == NULL)
    {
      return;
    }
    imprime(r->fEsq);
    cout << r->valor << " (Altura = " << r->altura << ")"<< endl;
    imprime(r->fDir);
  }

  bool removeNos(No* encontrado){
    No *pai;   
    //Caso
    if(encontrado == NULL){
      return false;
    }
    pai = encontrado->pai; //Encontra o pai do nó atual;
    if (encontrado->fEsq == NULL && encontrado->fDir == NULL){ //Primeiro caso: exclusão de uma folha (um nó sem filhos)
      if(pai){
        if (pai->valor >= encontrado->valor) //Se o valor do pai é maior que o valor a ser deletado, quer dizer que o nó
            pai->fEsq = NULL;     //a ser deletado está à esquerda
        else
            pai->fDir = NULL;
      }
      else 
        raiz=NULL;
    }
    else if (encontrado->fEsq && encontrado->fDir){ 
        //terceiro caso: o nó tem dois filhos.
        //Na definição do antecessor, deve-se ir ao primeiro nó à esquerda e percorrer todos os nós à direita
        //a partir deste, até que não existam mais nós à direita, logo o while percorre todos os nós a direita,
        //até chegar em um nó que não possui mais nós à direita.
        No *antecessor = encontrado->fEsq;
        
        while (antecessor->fDir != NULL)
          antecessor = antecessor->fDir;

        //Ao invés de trocar todos os ponteiros de lugar, simplesmente adota-se
        //o valor do nó a excluir como o valor do antecessor, logo após exclui-se o antecessor
        //de forma recursiva, na qual poderá cair em algum das duas condições (nenhum ou um filho)
        encontrado->valor = antecessor->valor;
        return removeNos(antecessor);        
    }
    else
      {
        //Segundo caso: exclusão de um nó que contenha somente um filho.
        //Como existe somente um filho, verifica-se qual lado o filho está, logo cria-se um nó filho que terá o valor
        //do nó existente, seja o direito ou esquerdo, logo, verifica-se se existe por exemplo o filho esquerdo,
        //se o operador ternário for verdadeiro filho = encontrado->fEsq, caso contrário filho = encontrado->fDir;
        No *filho = (encontrado->fEsq) ? encontrado->fEsq : encontrado->fDir;

        //Se remove um nó intermediário deve-se refazer a ligação entre o pai do nó excluido com o nó filho do atual.
        filho->pai = pai;
        if (pai->valor >= encontrado->valor)
          pai->fEsq = filho;
        else
          pai->fDir = filho;
      }

      delete encontrado;
      qntElementos--;
      while(pai){ //Update de altura para todos nós da árvore.
        pai->altura = altura(pai);
        balanceamento(pai);
        pai = pai->pai; //Acessa o nó avô (se existir) percorrendo os ancestrais do novo nó.
      }
      return true;
  }

  /**
   * Método que adquire o número máximo entre dois números dados.
   */
  int maximo(int a, int b){
    return ((a<b)?b:a);
  }

  /**
   * Método que calcula recursivamente a altura do nó dado.
   * Percorrendo todos os seus filhos, e os filhos dos filhos se houver.
   */
  int altura(No* n){
      if(!n)
        return -1;
      return (1 + maximo(altura(n->fEsq), altura(n->fDir)));
  }

  /**
   * Método que calcula o fator de balanceamento a partir de um nó dado. 
   */
  int fatorBalanceamento(No* n){
    return(altura(n->fDir) - altura(n->fEsq));
  }

  /**
   * Método que verifica a necessidade de executar algum dos tipos de rotação.
   */
  void balanceamento(No* n){
    int fb = fatorBalanceamento(n);
    if(fb > 1 && (fatorBalanceamento(n->fDir) > 0)){
      cout<<"--->Left Rotate iniciado"<<endl;
      leftRotate(n, true);
      cout<<"--->Left Rotate finalizado"<<endl;
    }
    else if(fb < -1 && (fatorBalanceamento(n->fEsq) < 0)){
      cout<<"--->right Rotate iniciado"<<endl;
      rightRotate(n, true);
      cout<<"--->right Rotate finalizado"<<endl;
    }
    //Rotação à esquerda depois direita
    else if(fb < -1 && (fatorBalanceamento(n->fEsq) > 0)){
      cout<<"--->Left Right Rotate iniciado"<<endl;
      print2D();
      leftRotate(n->fEsq, false);
      print2D();
      rightRotate(n,false);
      cout<<"--->Left Right Rotate finalizado\n"<<endl;
      
    }
    //Rotação à direita depois esquerda
    else if(fb > 1 && (fatorBalanceamento(n->fDir) < 0)){
      cout<<"--->Right Left Rotate iniciado"<<endl;
      print2D();
      rightRotate(n->fDir, false);
      print2D();
      leftRotate(n, false);
      cout<<"--->Right Left Rotate finalizado\n"<<endl;
    }
  }

  /**
   * Método LEFT-ROTATE
   */
  void leftRotate(No* desbalanceado, bool rotacaoSimples){
    No* temp;
    No* subArvore;
    No* avo;

    cout<<"Desbalanceado: "<<desbalanceado->valor<<endl;
    temp = desbalanceado->fDir;
    subArvore = temp->fEsq;
    avo = desbalanceado->pai;

    if(desbalanceado == raiz)
      raiz = temp;
    
    //Explicação da condição na linha 204
    if(avo){
      if(rotacaoSimples)
        avo->fDir = temp;
      else
        avo->fEsq = temp;
    }
      
    if(subArvore)
      subArvore->pai = desbalanceado;

    temp->pai = avo;
    temp->fEsq = desbalanceado;
    desbalanceado->fDir = subArvore;
    desbalanceado->pai = temp;
    desbalanceado->altura = altura(desbalanceado);
    temp->altura = altura(temp);
  }

  /**
   * Método RIGHT-ROTATE
   */
  void rightRotate(No* desbalanceado, bool rotacaoSimples){
    No* temp;
    No* subArvore;
    No* avo;

    cout<<"Desbalanceado: "<<desbalanceado->valor<<endl;
    temp = desbalanceado->fEsq;
    subArvore = temp->fDir;
    avo = desbalanceado->pai;

    if(desbalanceado == raiz)
      raiz = temp;
    
    //Verificação de existência de ancestrais do nó a ser rotacionado
    //A fim que realizar todos os re-apontamentos após a rotação.
    if(avo){
      //rotação simples envolve o caso da subárvore a ser rotacionada se
      //comportar como uma LDDE.
      if(rotacaoSimples)
        //Nesse caso, simplesmente liga-se o ancestral ao filho do nó desbalanceado
        avo->fEsq = temp;
      else
        //Caso contrário, não é possível ligar o ancestral ao filho diretamente, pois
        //mudaria a estrutura da árvore.
        avo->fDir = temp;
    }

    if(subArvore)
      subArvore->pai = desbalanceado;

    temp->pai = avo;
    temp->fDir = desbalanceado;
    desbalanceado->fEsq = subArvore;
    desbalanceado->pai = temp;
    
    //Atualização da altura
    desbalanceado->altura = altura(desbalanceado);
    temp->altura = altura(temp);
  }

public:
  ArvBusca()
  {
    raiz = NULL;
    qntElementos = 0;
  }

  bool insere(int valor)
  {
    No *pai = NULL;   //Um ponteiro para o pai do nó atual (para manter a relação)
    No *atual = raiz; //Nó atual da árvore, partindo sempre da raiz.
    No *novo = new No;
    novo->valor = valor; //inicia o novo nó com o valor dado para a inserção

    if (raiz == NULL)
    { //Não existe nenhum elemento na árvore, logo, o novo elemento será a raiz
      novo->altura = 0;
      raiz = novo;
      qntElementos++;
      return true;
    }

    while (atual)
    {              //Enquanto houver nós na árvore
      pai = atual; //Garante o apontamento para o nó passado.
      if (valor <= atual->valor)
      {                      //Verifica se o número a ser inserido é menor que o número do atual (inserção à esquerda)
        atual = atual->fEsq; //Se existe nó à esquerda do atual, sobreescrevemos o nó atual como sendo o próximo nó
                             //preparando para a próxima iteração.
      }
      else
      {
        atual = atual->fDir; //Se existe nó à direita do atual, sobreescrevemos o nó atual como sendo o próximo nó
                             //preparando para a próxima iteração.
      }
    }

    novo->pai = pai; //Após sair do while, já teremos onde o novo valor será inserido, e também
                     //qual será o nó pai do atual.

    if (valor <= pai->valor) //Se não houver nós à esquerda, o novo nó será inserido imediatamente após o nó atual
      pai->fEsq = novo;
    else
      pai->fDir = novo;

    qntElementos++;

    while(pai){ //Update de altura para todos nós da árvore.
      pai->altura = altura(pai);
      balanceamento(pai);
      pai = pai->pai; //Acessa o nó avô (se existir) percorrendo os ancestrais do novo nó.
    }

    return true;
  }

  void imprime()
  {
    imprime(raiz);
    cout << endl;
  }

  No *busca(int valor, bool *resposta)
  {
    No *atual = raiz;
    if (raiz && raiz->valor == valor)
    { //Se o valor procurado já é a raiz da árvore (e também se a raiz existe).
      if (resposta)
        *resposta = true;
      return raiz;
    }
    while (atual)
    { //Deslocamento entre os nós da árvore
      if (valor == atual->valor)
      {
        if (resposta)
          *resposta = true;
        return atual;
      }
      else if (valor < atual->valor)
        atual = atual->fEsq;
      else
        atual = atual->fDir;
    }
    if (resposta)
      *resposta = false;
    return NULL;
  }

  bool removeNos(int valor){
    return(removeNos(busca(valor, NULL)));
  }

  void destroiNo(No * atual)
    {                    //Método recursivo para a desalocação de memória, pos-order.
                         //com pos-order, é acessado o lado esquerdo, desalocado totalmente, logo após desalocado
                         //o lado direito totalmente e por último a raiz.
      if (atual == NULL) //Caso base da recursão
        return;
      destroiNo(atual->fEsq);
      destroiNo(atual->fDir);
      delete atual;
    }

  virtual ~ArvBusca()
  {
    destroiNo(raiz);
    cout << "Memoria desalocada com sucesso" << endl;
  }

  void print2DUtil(No *root, int space)  
  {  
      //Caso base  
      if (root == NULL)  
          return;  
    
      //Aumenta o espaço entre cada nó (espaçamento entre níveis) 
      space += COUNT;  
    
      //Percorre todo o lado direito da árvore. 
      print2DUtil(root->fDir, space);  
    
      //Printa o nó encontrado, com o espaço definido.
      cout<<endl;  
      for (int i = COUNT; i < space; i++)  
          cout<<" ";  
      cout<<root->valor<<"\n";  
    
      //Percorre todo o lado esquerdo da árvore.
      print2DUtil(root->fEsq, space);  
  }  
    
  void print2D()  
  {  
      cout<<"Arvore deitada: \n\n"<<endl;
      print2DUtil(raiz, 0);  
  }  
};
  

  int main(int argc, char *argv[])
  {
    // abrindo escopo para verificar o destrutor assim que o escopo se fechar
    {
      ArvBusca a;
      bool ok;
      a.insere (99);
      a.insere (34);
      a.insere (100);
      a.insere (29);
      a.insere (64);
      a.insere (52);
      a.insere (68);
      a.insere (79);
      a.insere (14);
      a.insere (55);
      a.print2D();
      a.removeNos (100);
      a.print2D();
      a.removeNos (99);
      a.print2D();
    }
    return 0;

  }
