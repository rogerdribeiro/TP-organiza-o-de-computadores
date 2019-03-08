#include <iostream>
#include <algorithm>
#include <vector>
#include "time.h"
#include <fstream>
#include <iomanip>
#include "tamanhoMemorias.h"
#include "GeradorDeInstrucoes.h"


#define VAZIO -1
#define NAO_ENCONTRADO -2
#define PROB_INTERRUPCAO 0

using namespace std;

typedef struct {
    int endBloco;
    int endPalavra;
}Endereco;

typedef struct{
    int opcode;
    Endereco ad1;
    Endereco ad2;
    Endereco ad3;
}Instrucao;

typedef struct{
    int palavra[4];
    int endBloco = VAZIO;
    int qnt_acessos = 0;
    bool alterado = false;
}BlocoMP;

typedef  struct{
    int palavra[4];
    int endBloco;
    int qnt_acessos = 0;
    bool alterado = false;
}LinhaCache;

int cont =0;
int pc = 0;
int pc_i = 0;
int cacheMissC1 = 0;
int cacheHitC1 = 0;
int cacheMissC2 = 0;
int cacheHitC2 = 0;
int cacheMissC3 = 0;
int cacheHitC3 = 0;
int ramHit;
int ramMiss;

bool aleatorio = false;
bool interrupcao;


int sum(int a, int b){
    //if(aleatorio== true)
      cout<<"SOMA:"<<setw(10)<<a<<setw(3)<<"  +  " <<b<<setw(3)<<"    = "<<setw(5)<<a+b<<endl;
    return a+b;
}

int sub(int a, int b){
    if (aleatorio == true)
        cout<<"SUBTRAÇÃO:"<<setw(5)<<a<<setw(3)<<"  -  " <<b<<setw(3)<<"    = "<<setw(5)<<a+b<<endl;
    return a-b;
}

int getAleatorio(int max){
    return rand() % max;
}
//*************** TP3 ****************************

void lerProgramaAleatorio(Instrucao *inst){

    fstream arq;
    arq.open("instrucoes.txt");
    if(arq.is_open()){

        for (int i = 0; i < TAM_INST; i++) {
            arq >> inst[i].opcode;
            arq >> inst[i].ad1.endBloco;
            arq >> inst[i].ad1.endPalavra;

            arq >> inst[i].ad2.endBloco;
            arq >> inst[i].ad2.endPalavra;

            arq >> inst[i].ad3.endBloco;
            arq >> inst[i].ad3.endPalavra;
        }
        arq.close();
        cout<<"Arquivo lido com sucesso!"<<endl;
    }else
        cout<<"Erro ao abrir arquivo"<<endl;
}

void criarProgramaAleatorio(){

    fstream arq;
    arq.open("instrucoes.txt");
    if(arq.is_open()) {

        for (int i = 0; i < TAM_INST - 1; i++) {
            arq << getAleatorio(2);
            arq << setw(5);
            arq << getAleatorio(TAM_HD - 100);
            arq << setw(2);
            arq << getAleatorio(4);
            arq << setw(4);
            arq << getAleatorio(TAM_HD - 100);
            arq << setw(2);
            arq << getAleatorio(4);
            arq << setw(4);
            arq << getAleatorio(TAM_HD - 100);
            arq << setw(2);
            arq << getAleatorio(4);
            arq << endl;
        }
        arq << -1;
        arq << "   ";
        arq << -1;
        arq << " ";
        arq << -1;
        arq << "   ";
        arq << -1;
        arq << " ";
        arq << -1;
        arq << "   ";
        arq << -1;
        arq << " ";
        arq << -1;
        arq << endl;
        arq.close();
        cout<<"Arquivo editado com sucesso!"<<endl;
    }else
        cout<<"Erro ao abrir arquivo"<<endl;
}

void criarProgramaMultiplicao(int a, int b){

    ofstream arq;
    arq.open("instrucoesMultiplicacao.txt");
    if(arq.is_open()) {
        arq << 2;
        arq <<setw(5)<< 0;
        arq <<setw(2)<< 0;

        arq <<setw(4)<< 0;
        arq <<setw(2)<< 0;
        arq<<endl;

        arq << 2;
        arq <<setw(4)<< a;
        arq <<setw(2)<< 0;

        arq <<setw(4)<< 1;
        arq <<setw(2)<< 0;
        arq<<endl;

        b+=2;
        for (int i = 2; i < b; i++) {
            arq<< 0;
            arq <<setw(5)<< 0;
            arq <<setw(2)<< 0;

            arq <<setw(4)<< 1;
            arq <<setw(2)<< 0;

            arq <<setw(4)<< 0;
            arq <<setw(2)<< 0;
            arq <<endl;
        }
        //imprimir
        arq<< 3;
        arq <<setw(5)<< 0;
        arq <<setw(2)<< 0;

        arq <<setw(4)<< 0;
        arq <<setw(2)<< 0;

        arq <<setw(4)<< 0;
        arq <<setw(2)<< 0;
        //terminar
        arq<< -1;
        arq <<setw(4)<< 0;
        arq <<setw(2)<< 0;

        arq <<setw(4)<< 0;
        arq <<setw(2)<< 0;

        arq <<setw(4)<< 0;
        arq <<setw(2)<< 0;

        arq.close();
        cout<<"Arquivo editado com sucesso!"<<endl;
    }else
        cout<<"Erro ao abrir arquivo para criação do programa "<<endl;

}

void lerProgramaMultiplicacao(Instrucao *inst, int a, int b) {

    fstream arq;
    arq.open("instrucoesMultiplicacao.txt");
    if(arq.is_open()) {
        arq >> inst[0].opcode;
        arq >> inst[0].ad1.endBloco;
        arq >> inst[0].ad1.endPalavra;

        arq >> inst[0].ad3.endBloco;
        arq >> inst[0].ad3.endPalavra;

        arq >> inst[1].opcode;
        arq >> inst[1].ad1.endBloco;
        arq >> inst[1].ad1.endPalavra;

        arq >> inst[1].ad3.endBloco;
        arq >> inst[1].ad3.endPalavra;

        b += 2;
        for (int i = 2; i < b; i++) {
            arq >> inst[i].opcode;
            arq >> inst[i].ad1.endBloco;
            arq >> inst[i].ad1.endPalavra;

            arq >> inst[i].ad2.endBloco;
            arq >> inst[i].ad2.endPalavra;

            arq >> inst[i].ad3.endBloco;
            arq >> inst[i].ad3.endPalavra;
        }
        //imprimir
        arq >> inst[b].opcode;
        arq >> inst[b].ad1.endBloco;
        arq >> inst[b].ad1.endPalavra;

        arq >>inst[b].ad2.endBloco;
        arq >>inst[b].ad2.endPalavra;

        arq >>inst[b].ad3.endBloco;
        arq >>inst[b].ad3.endPalavra;
        //terminar
        arq >>inst[b + 1].opcode ;
        arq >>inst[b + 1].ad1.endBloco;
        arq >>inst[b + 1].ad1.endPalavra;

        arq >>inst[b + 1].ad2.endBloco;
        arq >>inst[b + 1].ad2.endPalavra;

        arq >>inst[b + 1].ad3.endBloco;
        arq >>inst[b + 1].ad3.endPalavra;

        arq.close();
    }else {
        cout<<"Erro ao abrir arquivo para leitura"<<endl;
    }

}

void lerGeradorInst(Instrucao *inst){

    fstream arq;
    arq.open("instrucoes.txt");
    if(arq.is_open()) {
        aleatorio = true;
        for (int i = 0; i < TAM_INST; i++) {
            arq >> inst[i].opcode;

            arq >> inst[i].ad1.endBloco;
            arq >> inst[i].ad1.endPalavra;

            arq >> inst[i].ad2.endBloco;
            arq >> inst[i].ad2.endPalavra;

            arq >> inst[i].ad3.endBloco;
            arq >> inst[i].ad3.endPalavra;
        }
        arq.close();
        cout<<"Arquivo lido com sucesso!"<<endl;
    }else
        cout<<"Erro ao abrir arquivo"<<endl;
}


//***************INICIALIZAÇÕES*********************

void iniciaMemoriaRAM(BlocoMP *memoriaPrincipal){

    for ( int i=0; i<TAM_RAM; i++){
        for(int j=0; j<4; j++) {
            memoriaPrincipal[i].palavra[j] = VAZIO;
        }
        memoriaPrincipal[i].endBloco = VAZIO;
        memoriaPrincipal[i].alterado = false;
        memoriaPrincipal[i].qnt_acessos = 0;
    }
}

void iniciarCaches(LinhaCache *cache, int tam){
    for(int i=0; i<tam; i++){
        cache[i].endBloco = VAZIO;
        cache[i].qnt_acessos = 0;
        for(int j=0; j<4; j++)
            cache[i].palavra[j] = VAZIO;
    }
}

//***************PROGRAMAS*********************

void ProgramaAleatorio(Instrucao *inst){

    for(int i=0; i<TAM_INST-1; i++){
        inst[i].opcode = getAleatorio(2);
        inst[i].ad1.endBloco = getAleatorio(TAM_HD-100);
        inst[i].ad1.endPalavra = getAleatorio(4);

        inst[i].ad2.endBloco = getAleatorio(TAM_HD-100);
        inst[i].ad2.endPalavra = getAleatorio(4);

        inst[i].ad3.endBloco = getAleatorio(TAM_HD-100);
        inst[i].ad3.endPalavra = getAleatorio(4);
    }
    inst[TAM_INST-1].opcode = -1;
}

void programaMultiplicacao(Instrucao *inst, int a, int b) {

    inst[0].opcode = 2;
    inst[0].ad1.endBloco = 0;
    inst[0].ad3.endBloco = 0;
    inst[0].ad3.endPalavra = 0;

    inst[1].opcode = 2;
    inst[1].ad1.endBloco = a;
    inst[1].ad3.endBloco = 1;
    inst[1].ad3.endPalavra = 0;

    b+=2;
    for (int i = 2; i < b; i++) {
        inst[i].opcode = 0;
        inst[i].ad1.endBloco = 0;
        inst[i].ad1.endPalavra = 0;

        inst[i].ad2.endBloco = 1;
        inst[i].ad2.endPalavra = 0;

        inst[i].ad3.endBloco = 0;
        inst[i].ad3.endPalavra = 0;
    }
    //imprimir
    inst[b].opcode = 3;
    inst[b].ad1.endBloco = 0;
    inst[b].ad1.endPalavra = 0;

    inst[b].ad2.endBloco = 0;
    inst[b].ad2.endPalavra = 0;

    inst[b].ad3.endBloco = 0;
    inst[b].ad3.endPalavra = 0;
    //terminar
    inst[b+1].opcode = -1;
    inst[b+1].ad1.endBloco = 0;
    inst[b+1].ad1.endPalavra = 0;

    inst[b+1].ad2.endBloco = 0;
    inst[b+1].ad2.endPalavra = 0;

    inst[b+1].ad3.endBloco = 0;
    inst[b+1].ad3.endPalavra = 0;

}

void programaDivisao(Instrucao *inst, int a, int b){

    inst[0].opcode = 2;
    inst[0].ad1.endBloco = 0;
    inst[0].ad3.endBloco = 0;
    inst[0].ad3.endPalavra = 0;

    inst[1].opcode = 2;
    inst[1].ad1.endBloco = 1;
    inst[1].ad3.endBloco = 1;
    inst[1].ad3.endPalavra = 0;

    int j=2;
    for (int i = a; i >= b; i-=b) {
        inst[j].opcode = 0;
        inst[j].ad1.endBloco = 0;
        inst[j].ad1.endPalavra = 0;

        inst[j].ad2.endBloco = 1;
        inst[j].ad2.endPalavra = 0;

        inst[j].ad3.endBloco = 0;
        inst[j].ad3.endPalavra = 0;
        j++;
    }
    //imprimir
    inst[j].opcode = 3;
    inst[j].ad1.endBloco = 0;
    inst[j].ad1.endPalavra = 0;

    inst[j].ad2.endBloco = 0;
    inst[j].ad2.endPalavra = 0;

    inst[j].ad3.endBloco = 0;
    inst[j].ad3.endPalavra = 0;
    //terminar
    inst[j+1].opcode = -1;
    inst[j+1].ad1.endBloco = 0;
    inst[j+1].ad1.endPalavra = 0;

    inst[j+1].ad2.endBloco = 0;
    inst[j+1].ad2.endPalavra = 0;

    inst[j+1].ad3.endBloco = 0;
    inst[j+1].ad3.endPalavra = 0;

}

void programaPA(Instrucao *inst, int a1, int tam, int r ){

    //c->memoria[0] = 0;
    //c->memoria[1] = r;
    //c->memoria[2] = a1;

    inst[0].opcode = 2;
    inst[0].ad1.endBloco = 0;
    inst[0].ad3.endBloco = 0;
    inst[0].ad3.endPalavra = 0;

    inst[1].opcode = 2;
    inst[1].ad1.endBloco = r;
    inst[1].ad3.endBloco = 1;
    inst[1].ad3.endPalavra = 0;


    inst[2].opcode = 2;
    inst[2].ad1.endBloco = a1;
    inst[2].ad3.endBloco = 2;
    inst[2].ad3.endPalavra = 0;


//montando sequencia

    for(int i=3; i<(tam+2); i++){
        inst[i].opcode = 0;
        inst[i].ad1.endBloco = 1;
        inst[i].ad1.endPalavra = 0;

        inst[i].ad2.endBloco = i-1;
        inst[i].ad2.endPalavra = 0;

        inst[i].ad3.endBloco = i;
        inst[i].ad3.endPalavra = 0;

    }
    int k=2;
    int tam2 = (2*tam)+2;

    //montando a soma da pa
    for(int i=tam+2; i<tam2; i++) {

        inst[i].opcode = 0;
        inst[i].ad1.endBloco = 0;
        inst[i].ad1.endPalavra = 0;

        inst[i].ad2.endBloco = k;
        inst[i].ad2.endPalavra = 0;

        inst[i].ad3.endBloco = 0;
        inst[i].ad3.endPalavra = 0;

        k++;
    }
    //imprimir
    inst[tam2].opcode = 3;
    inst[tam2].ad1.endBloco = 0;
    inst[tam2].ad1.endPalavra = 0;
    inst[tam2].ad2.endBloco = 0;
    inst[tam2].ad2.endPalavra = 0;
    inst[tam2].ad3.endBloco = 0;
    inst[tam2].ad3.endPalavra = 0;

    tam2++;
    //  terminar
    inst[tam2].opcode = -1;
    inst[tam2].ad1.endBloco = 0;
    inst[tam2].ad2.endBloco = 0;
    inst[tam2].ad3.endBloco = 0;
}

void programaFibonacci(Instrucao *inst, int n){

    inst[0].opcode = 2;
    inst[0].ad1.endBloco = 0;
    inst[0].ad3.endBloco = 0;
    inst[0].ad3.endPalavra = 0;

    inst[1].opcode = 2;
    inst[1].ad1.endBloco = 1;
    inst[1].ad3.endBloco = 1;
    inst[1].ad3.endPalavra = 0;


    n+=2;
    for(int i=2; i<n; i++){
        inst[i].opcode = 0;
        inst[i].ad1.endBloco = i-2;
        inst[i].ad1.endPalavra = 0;
        inst[i].ad2.endBloco = i-1;
        inst[i].ad2.endPalavra = 0;
        inst[i].ad3.endBloco = i;
        inst[i].ad3.endPalavra = 0;
    }

    inst[n].opcode = 0;
    inst[n].ad1.endBloco = n-4;
    inst[n].ad1.endPalavra = 0;

    inst[n].ad2.endBloco = n-3;
    inst[n].ad2.endPalavra = 0;

    inst[n].ad3.endBloco = 0;
    inst[n].ad3.endPalavra = 0;

    n++;
    //imprimir
    inst[n].opcode = 3;
    inst[n].ad1.endBloco = 0;
    inst[n].ad1.endPalavra = 0;

    inst[n].ad2.endBloco = 0;
    inst[n].ad2.endPalavra = 0;

    inst[n].ad3.endBloco = 0;
    inst[n].ad3.endPalavra = 0;
    //terminar
    inst[n+1].opcode = -1;
    inst[n+1].ad1.endBloco = 0;
    inst[n+1].ad2.endBloco = 0;
    inst[n+1].ad3.endBloco = 0;
}

void programaAreaQuadrado(Instrucao *inst, int lado) {

    inst[0].opcode = 2;
    inst[0].ad1.endBloco = 0;
    inst[0].ad3.endBloco = 0;
    inst[0].ad3.endPalavra = 0;

    inst[1].opcode = 2;
    inst[1].ad1.endBloco = lado;
    inst[1].ad3.endBloco = 1;
    inst[1].ad3.endPalavra = 0;

    lado+=2;
    for (int i = 2; i < lado; i++) {
        inst[i].opcode = 0;
        inst[i].ad1.endBloco = 0;
        inst[i].ad1.endPalavra = 0;

        inst[i].ad2.endBloco = 1;
        inst[i].ad2.endPalavra = 0;

        inst[i].ad3.endBloco = 0;
        inst[i].ad3.endPalavra = 0;
    }
    //imprimir
    inst[lado].opcode = 3;
    inst[lado].ad1.endBloco = 0;
    inst[lado].ad1.endPalavra = 0;

    inst[lado].ad2.endBloco = 0;
    inst[lado].ad2.endPalavra = 0;

    inst[lado].ad3.endBloco = 0;
    inst[lado].ad3.endPalavra = 0;

    //terminar
    inst[lado+1].opcode = -1;
    inst[lado+1].ad1.endBloco = 0;
    inst[lado+1].ad1.endPalavra = 0;

    inst[lado+1].ad2.endBloco = 0;
    inst[lado+1].ad2.endPalavra = 0;

    inst[lado+1].ad3.endBloco = 0;
    inst[lado+1].ad3.endPalavra = 0;

}

void programaAreaRetangulo(Instrucao *inst, int lado, int altura) {

    inst[0].opcode = 2;
    inst[0].ad1.endBloco = 0;
    inst[0].ad3.endBloco = 0;
    inst[0].ad3.endPalavra = 0;

    inst[1].opcode = 2;
    inst[1].ad1.endBloco = altura;
    inst[1].ad3.endBloco = 1;
    inst[1].ad3.endPalavra = 0;

    lado+=2;
    for (int i = 2; i < lado; i++) {
        inst[i].opcode = 0;
        inst[i].ad1.endBloco = 0;
        inst[i].ad1.endPalavra = 0;

        inst[i].ad2.endBloco = 1;
        inst[i].ad2.endPalavra = 0;

        inst[i].ad3.endBloco = 0;
        inst[i].ad3.endPalavra = 0;
    }
    //imprimir
    inst[lado].opcode = 3;
    inst[lado].ad1.endBloco = 0;
    inst[lado].ad1.endPalavra = 0;

    inst[lado].ad2.endBloco = 0;
    inst[lado].ad2.endPalavra = 0;

    inst[lado].ad3.endBloco = 0;
    inst[lado].ad3.endPalavra = 0;

    //terminar
    inst[lado+1].opcode = -1;
    inst[lado+1].ad1.endBloco = 0;
    inst[lado+1].ad1.endPalavra = 0;

    inst[lado+1].ad2.endBloco = 0;
    inst[lado+1].ad2.endPalavra = 0;

    inst[lado+1].ad3.endBloco = 0;
    inst[lado+1].ad3.endPalavra = 0;

}

void programaVolumeCubo(Instrucao *inst, int lado){

    inst[0].opcode = 2;
    inst[0].ad1.endBloco = 0;
    inst[0].ad3.endBloco = 0;
    inst[0].ad3.endPalavra = 0;


    inst[1].opcode = 2;
    inst[1].ad1.endBloco = lado;
    inst[1].ad3.endBloco = 1;
    inst[1].ad3.endPalavra= 0;


    int k=2;
    for( int j=0; j<lado; j++) {
        for (int i = 0; i < lado; i++) {
            inst[k].opcode = 0;
            inst[k].ad1.endBloco = 0;
            inst[k].ad1.endPalavra = 0;

            inst[k].ad2.endBloco = 1;
            inst[k].ad3.endPalavra = 0;

            inst[k].ad3.endBloco = 0;
            inst[k].ad3.endPalavra = 0;

            k++;
        }
    }
    //imprimir
    inst[k].opcode = 3;
    inst[k].ad1.endBloco = 0;
    inst[k].ad1.endPalavra = 0;

    inst[k].ad2.endBloco = 0;
    inst[k].ad2.endPalavra = 0;

    inst[k].ad3.endBloco = 0;
    inst[k].ad3.endPalavra = 0;

    k++;
    //terminar
    inst[k].opcode = -1;
    inst[k].ad1.endBloco = 0;
    inst[k].ad2.endBloco = 0;
    inst[k].ad3.endBloco = 0;
}

void programaVolumeCilindo(Instrucao *inst, int raio, int altura){

    inst[0].opcode = 2;
    inst[0].ad1.endBloco = 0;
    inst[0].ad3.endBloco = 0;
    inst[0].ad3.endPalavra = 0;


    inst[1].opcode = 2;
    inst[1].ad1.endBloco = raio;
    inst[1].ad1.endPalavra = 0;

    inst[1].ad3.endBloco = 1;
    inst[1].ad3.endPalavra = 0;


    int k=2;
    for( int j=0; j<3*altura; j++) {
        for (int i = 0; i < raio; i++) {
            inst[k].opcode = 0;
            inst[k].ad1.endBloco = 0;
            inst[k].ad1.endPalavra = 0;

            inst[k].ad2.endBloco = 1;
            inst[k].ad2.endPalavra = 0;

            inst[k].ad3.endBloco = 0;
            inst[k].ad3.endPalavra = 0;

            k++;
        }
    }
    //imprimir
    inst[k].opcode = 3;
    inst[k].ad1.endBloco = 0;
    inst[k].ad1.endPalavra = 0;

    inst[k].ad2.endBloco = 0;
    inst[k].ad2.endPalavra = 0;

    inst[k].ad3.endBloco = 0;
    inst[k].ad3.endPalavra = 0;

    //terminar
    k++;
    inst[k].opcode = -1;
    inst[k].ad1.endBloco = 0;
    inst[k].ad2.endBloco = 0;
    inst[k].ad3.endBloco= 0;
}

//*************** FUNÇÕES PARA TESTES *********************

void printMemoriaRAM(BlocoMP *memoriaPrincipal){
    cout<<"\n>>>Memória RAM <<<\n";
    for (int i=0; i<TAM_RAM; i++) {
        cout<<i<<" - ";
        for (int j = 0; j < 4; j++) {
            cout<<memoriaPrincipal[i].palavra[j] << "\t";
        }
        cout<<"\t endBloco-> "<<memoriaPrincipal[i].endBloco;
        cout<<endl;
    }
}

void printInstrucoes(Instrucao *inst){
    cout<<"INST  |      AD1     |     AD2      |       AD3       "<<endl;
    cout<<"______________________________________________________"<<endl;

    for(int i=0; i<TAM_INST-1; i++){
        cout<<inst[i].opcode<<"     |     ";
        cout<< inst[i].ad1.endBloco<<"  ,  ";
        cout<< inst[i].ad1.endPalavra<<"  |  ";
        cout<< inst[i].ad2.endBloco<<"  , ";
        cout<< inst[i].ad2.endPalavra<<"  |  ";
        cout<< inst[i].ad3.endBloco<<"  ,  ";
        cout<< inst[i].ad3.endPalavra<<"  |    "<<endl;
    }
}

void printMemoriaHD(){

    FILE *Arq;
    BlocoMP aux;
    Arq = fopen("DiscoRigido.bin","rb");
    if(Arq!=NULL){
        cout<<"lendo arquivo binário..."<<endl;
        for(int i=0; i<TAM_HD; i++) {
            //cout<<endl;
            fread(&aux, sizeof(BlocoMP), 1, Arq);
            for (int j = 0; j < 4; j++) {
                cout << "\t" << aux.palavra[j];
                //}
            }
            cout << endl;
        }
    } else
        cout<<"Erro ao abrir arquivo para leitura"<<endl;
    fclose(Arq);
}

void mostrarEstatisticas(){

    int acessoC1 = cacheHitC1+cacheMissC1;
    int acessoC2 = cacheHitC2+cacheMissC2;
    int acessoC3 = cacheHitC3+cacheMissC3;
    //int taxaRAM = (cacheMissC1+cacheMissC2+cacheMissC3)*100/(acessoC1+acessoC2+acessoC3);
    cout<<endl;
    cout<<"**************************ESTATISTICAS************************************"<<endl<<endl;
    cout<<"TOTAL DE ACESSOS: "<<cont<<endl;
    cout<<"__________________________CACHE HITS______________________________________"<<endl;
    cout<<"Cache1 hit: "<<cacheHitC1<<"\t\t=\t\t"<<(cacheHitC1*100/(cont))<<" % "<<endl;
    cout<<"Cache2 hit: "<<cacheHitC2<<"\t\t=\t\t"<<cacheHitC2*100/(cont)<<" % "<<endl;
    cout<<"Cache3 hit: "<<cacheHitC3<<"\t\t=\t\t"<<cacheHitC3*100/(cont)<<" % "<<endl;
    cout<<endl;
    cout<<"__________________________CACHE MISS______________________________________"<<endl;
    cout<<"Cache miss: "<<cacheMissC1<< "\t\t=\t\t"<<(cacheMissC1*100/cont)<<" % "<<endl;
    cout<<"Cache2 miss: "<<cacheMissC2<< "\t\t=\t\t"<<cacheMissC2*100/(cont)<<" % "<<endl;
    cout<<"Cache3 miss: "<<cacheMissC3<< "\t\t=\t\t"<<cacheMissC3*100/(cont)<<" % "<<endl;
    cout<<endl;
    cout<<"__________________________TAXA RAM/CACHE__________________________________"<<endl;
    cout<<"Taxa de cache: "<<cacheHitC1+cacheHitC2+cacheHitC3 <<"\t\t=\t\t"<<(cacheHitC1+cacheHitC2+cacheHitC3)*100/(cont)<<" % "<<endl;
    cout<<"Taxa de ram: "<<ramHit <<"\t\t\t=\t\t"<< (ramHit*100)/cont<<"%"<<endl;
    cout<<"Taxa de Disco: "<<ramMiss<<"\t\t=\t\t"<<ramMiss*100/cont<<"%"<<endl;
    cout<<"**************************************************************************"<<endl<<endl;
}

//*************** GERENCIAMENTO DE MEMORIA *********************

int percorrerCache(LinhaCache *cache, int tam_cache, int endBloco){

    for(int i=0; i<tam_cache; i++){
        if (cache[i].endBloco == endBloco){
            cache[i].qnt_acessos++;
            return i;
        }
    }
    return NAO_ENCONTRADO ;
}

int percorrerRAM(BlocoMP *memoriaPrincipal, int tam_ram, int endBloco){

    for(int i=0; i<tam_ram; i++){
        if (memoriaPrincipal[i].endBloco == endBloco){
            memoriaPrincipal[i].qnt_acessos++;
            return i;
        }
    }
    return NAO_ENCONTRADO ;
}

int transferirParaOutraCache(LinhaCache* origem, LinhaCache *destino,int tam_destino, int end) {

    for(int i=0; i<tam_destino; i++) {
        if (destino[i].endBloco == VAZIO) {
            destino[i].qnt_acessos++;
            destino[i].endBloco = origem[end].endBloco;
            for(int k=0; k<4; k++){
                destino[i].palavra[k] = origem[end].palavra[k];
                origem[end].palavra[k] = VAZIO;
            }
            origem[end].endBloco = VAZIO;
            origem[end].qnt_acessos = 0;
            return i;
        }
    }
    LinhaCache cacheAux;
    if(destino[tam_destino-1].endBloco != VAZIO){    // se a cache estiver cheia
        vector<int>acessos;
        for(int i=0; i<tam_destino; i++){
            acessos.push_back(destino[i].qnt_acessos);
        }
        sort(acessos.begin(),acessos.end());
        int procurar = acessos[0];
        for(int i=0; i<tam_destino; i++){
            if(destino[i].qnt_acessos == procurar){
                cacheAux = destino[i];
                destino[i] = origem[end];
                origem[end] = cacheAux;
                 return i;
            }
        }
    }
}

int memoriaRAMParaCache(BlocoMP *memoriaRAM,LinhaCache *cache, int tam_cache, int endBloco){

    int endereco = memoriaRAM[endBloco].endBloco;

    for(int i=0; i<tam_cache; i++){
        if(cache[i].endBloco == VAZIO){
            cache[i].endBloco = endereco;
            for (int j = 0; j < 4; j++){
                cache[i].palavra[j] = memoriaRAM[endBloco].palavra[j];
            }
            return i;
        }

        else if(cache[tam_cache-1].endBloco != VAZIO){ // se a cache estiver cheia
            vector<int>acessos;
            for(int i=0; i<tam_cache; i++){
                acessos.push_back(cache[i].qnt_acessos);
            }
            sort(acessos.begin(),acessos.end());
            int procurar = acessos[0];
            LinhaCache aux;

            for(int i=0; i<tam_cache; i++){
                if(cache[i].qnt_acessos == procurar){
                    aux = cache[i];

                    cache[i].endBloco = endereco;
                    cache[i].qnt_acessos = memoriaRAM[endBloco].qnt_acessos;
                    cache[i].alterado = memoriaRAM[endBloco].alterado;

                    for (int j = 0; j < 4; j++){
                        cache[i].palavra[j] = memoriaRAM[endBloco].palavra[j];
                        memoriaRAM[endBloco].palavra[j] = aux.palavra[j];
                    }
                    memoriaRAM[endBloco].alterado = aux.alterado;
                    memoriaRAM[endBloco].endBloco = aux.endBloco;
                    memoriaRAM[endBloco].qnt_acessos = aux.qnt_acessos;

                    return i;
                }
            }
        }
    }
}

void atualizarMemoriaHD(BlocoMP memoriaRAM, int end){

    FILE* Arq = fopen("DiscoRigido.bin", "r+b");
    fseek(Arq,(end)*sizeof(BlocoMP), SEEK_SET);
    fwrite(&memoriaRAM, sizeof(BlocoMP), 1, Arq);
    fclose(Arq);
}

int memoriaHDparaMemoriaRam(BlocoMP *memoriaRAM, BlocoMP DiscoHD, int tam_ram){

    for(int i=0; i<tam_ram; i++){
        if(memoriaRAM[i].endBloco == VAZIO){
            memoriaRAM[i] = DiscoHD;
            return i;
        }
        else if(memoriaRAM[tam_ram-1].endBloco != VAZIO){ // se a RAM estiver cheia
            vector<int>acessos;
            for(int i=0; i<tam_ram; i++){
                acessos.push_back(memoriaRAM[i].qnt_acessos);
            }
            sort(acessos.begin(),acessos.end());
            int procurar = acessos[0];
            for(int i=0; i<tam_ram; i++){
                if(memoriaRAM[i].qnt_acessos == procurar){
                    if(memoriaRAM[i].alterado){ // atualizar o dado na memoria caso tenha alguma alteração
                        int endereco = memoriaRAM[i].endBloco;
                        //ir no disco e atualizar o bloco
                        BlocoMP memoriaRam = memoriaRAM[i];
                        atualizarMemoriaHD(memoriaRam,endereco);
                    }
                    memoriaRAM[i] = DiscoHD;
                    memoriaRAM[i].alterado = false;
                    return i;
                }
            }
        }
    }
}

void criarMemoriaHD(){

    //cout<<"Criando arquivo binário..."<<endl;
    BlocoMP aux;
    FILE *Arq = fopen("DiscoRigido.bin", "wb");
    for(int i = 0; i < TAM_HD; i++){
        //cout<<"i = "<<i<<"\t";
        for(int j = 0; j < 4; j++){
            aux.palavra[j] = getAleatorio(50);
            aux.endBloco = i;
           // cout<<"\t"<<aux.palavra[j];
        }
        fwrite(&aux, sizeof(BlocoMP), 1, Arq);
        //cout<<endl;
    }
    fclose(Arq);
}

BlocoMP buscarNaMemoriaHD(int MAR){

    BlocoMP bloco;
    FILE* Arq = fopen("DiscoRigido.bin", "rb");
    fseek(Arq,MAR*sizeof(BlocoMP), SEEK_SET);
    fread(&bloco, sizeof(BlocoMP), 1, Arq);
    fclose(Arq);
    return bloco;
}

int MMU(LinhaCache *cache1,LinhaCache *cache2, LinhaCache *cache3, BlocoMP *memoriaRAM, int endBloco){
    cont++;
    int bloco = percorrerCache(cache1,TAM_CACHE1,endBloco); // procurando na cache 1
    if(bloco == NAO_ENCONTRADO){
        cacheMissC1++;

        bloco = percorrerCache(cache2,TAM_CACHE2,endBloco); // procurando na cache 2
        if(bloco == NAO_ENCONTRADO){
            cacheMissC2++;

            bloco = percorrerCache(cache3,TAM_CACHE3,endBloco); //procurando na cache 3
            if(bloco == NAO_ENCONTRADO){
                cacheMissC3++;

                bloco = percorrerRAM(memoriaRAM,TAM_RAM,endBloco); // procurando na RAM
                if(bloco == NAO_ENCONTRADO){ //PIOR CASO, NÃO ACHOU NAS CACHES E NEM NA RAM, VAI TER QUE IR NO DISCO RÍGIDO
                    ramMiss++;
                    //procurar no disco , retornar do disco para a ram, cache 3, cache 2, cache 1, e return para cpu

                    BlocoMP blocoHD = buscarNaMemoriaHD(endBloco);
                    bloco = memoriaHDparaMemoriaRam(memoriaRAM,blocoHD,TAM_RAM);
                    bloco = memoriaRAMParaCache(memoriaRAM, cache3, TAM_CACHE3, bloco);
                    bloco = transferirParaOutraCache(cache3, cache2, TAM_CACHE2, bloco);
                    bloco = transferirParaOutraCache(cache2, cache1, TAM_CACHE1, bloco);
                    return bloco;
                }else{
                    ramHit++;
                    bloco = memoriaRAMParaCache(memoriaRAM, cache3, TAM_CACHE3, endBloco);
                    bloco = transferirParaOutraCache(cache3, cache2, TAM_CACHE2, bloco);
                    bloco = transferirParaOutraCache(cache2, cache1, TAM_CACHE1, bloco);
                    return bloco;
                }
            }else{
                cacheHitC3++;
                bloco = transferirParaOutraCache(cache3,cache2,TAM_CACHE2,bloco);
                bloco = transferirParaOutraCache(cache2,cache1,TAM_CACHE1,bloco);
                return bloco;
            }
        }else{
            cacheHitC2++;
            bloco = transferirParaOutraCache(cache2,cache1,TAM_CACHE1,bloco);
            return bloco;
        }
    }else{
        cacheHitC1++;
        return bloco;
    }
}

//*************** CPU *********************
void CPU(BlocoMP *memoriaPrincipal, Instrucao *inst, Instrucao *inst_interrupcao, LinhaCache *cache1, LinhaCache *cache2,LinhaCache *cache3){

    int IR = inst[pc].opcode;
    int MAR1,MAR1p;
    int MAR2,MAR2p;
    int MAR3, MAR3p;

    while (inst[pc].opcode != -1) {

        int probabilidade = getAleatorio(100);
;
        if(PROB_INTERRUPCAO > probabilidade){
            cout<<"\n-------------- ENTROU NA INTERRUPÇÃO ---------------"<<endl;

            IR =  inst_interrupcao[pc_i].opcode;
            Instrucao MBR = inst_interrupcao[pc_i];
            MAR1 = MBR.ad1.endBloco;
            MAR1p = MBR.ad1.endPalavra;
            MAR2 = MBR.ad2.endBloco;
            MAR2p = MBR.ad2.endPalavra;
            MAR3 = MBR.ad3.endBloco;
            MAR3p = MBR.ad3.endPalavra;
            pc_i++;
            interrupcao = true;
        }else{
                IR = inst[pc].opcode;
                Instrucao MBR = inst[pc];
                MAR1 = MBR.ad1.endBloco;
                MAR1p = MBR.ad1.endPalavra;
                MAR2 = MBR.ad2.endBloco;
                MAR2p = MBR.ad2.endPalavra;
                MAR3 = MBR.ad3.endBloco;
                MAR3p = MBR.ad3.endPalavra;
                interrupcao = false;
                pc++;
        }

        int a,b,c,bloco;
        //cout<<"MAR1: "<<MAR1<<endl;
        //cout<<"MAR2: "<<MAR2<<endl;

        switch (IR){

            case 0: // SOMA

                bloco = MMU(cache1,cache2,cache3,memoriaPrincipal,MAR1);
                b = cache1[bloco].palavra[MAR1p];

                bloco = MMU(cache1,cache2,cache3,memoriaPrincipal,MAR2);
                c = cache1[bloco].palavra[MAR2p];

                a = sum(b,c);
                bloco = MMU(cache1,cache2,cache3,memoriaPrincipal,MAR3);
                cache1[bloco].palavra[MAR3p] = a;
                cache1[bloco].alterado = true;
                break;
cout<<"MAR1: "<<MAR1<<endl;

            case 1: // SUB
                bloco = MMU(cache1,cache2,cache3,memoriaPrincipal,MAR1);
                b = cache1[bloco].palavra[MAR1p];

                bloco = MMU(cache1,cache2,cache3,memoriaPrincipal,MAR2);
                c = cache1[bloco].palavra[MAR2p];

                a = sub(b,c);
                bloco = MMU(cache1,cache2,cache3,memoriaPrincipal,MAR3);
                cache1[bloco].palavra[MAR3p] = a;
                cache1[bloco].alterado = true;
                break;

            case 2: //ATRIBRUIR VALOR A MEMÓRIA

                bloco = MMU(cache1,cache2,cache3,memoriaPrincipal,MAR3);
                cache1[bloco].palavra[MAR3p] = MAR1;
                cache1[bloco].alterado = true;
                break;

            case 3: //IMPRIMIR
                bloco = MMU(cache1,cache2,cache3,memoriaPrincipal,MAR3);
                a = cache1[bloco].palavra[MAR3p];
                cout<<endl<<"Resultado: "<<a<<endl;
        }
        if(interrupcao){
            cout<<"-------------- SAIU DA INTERRUPÇÃO ---------------"<<endl<<endl;
        }
       // cout<<"PC >>> "<<pc<<endl;
    }
    //cout<<"Total de instrucoes feitas: "<<pc<<endl;
}

int main() {

    srand((unsigned) time(NULL));

    BlocoMP *memoriaRAM = new BlocoMP[TAM_RAM];
    Instrucao *inst = new Instrucao[TAM_INST];
    Instrucao *inst_interrupcao = new Instrucao[TAM_INST];
    LinhaCache *cache1 = new LinhaCache[TAM_CACHE1];
    LinhaCache *cache2 = new LinhaCache[TAM_CACHE2];
    LinhaCache *cache3 = new LinhaCache[TAM_CACHE3];

    iniciarCaches(cache1, TAM_CACHE1);
    iniciarCaches(cache2, TAM_CACHE2);
    iniciarCaches(cache3, TAM_CACHE3);
    iniciaMemoriaRAM(memoriaRAM);
    criarMemoriaHD();
    //printMemoriaHD();

    bool prog_interrupcao = false;    // gerador de instrucoes INTERRUPCAO
    bool prog_multiplicacao = true; // 5 x 100
    bool prog_aleatorio = false;      // gerador de instrucoes

    if(prog_interrupcao) {
        geradorInstrucoes(TAM_INST);
        lerGeradorInst(inst_interrupcao);
    }

    if(prog_aleatorio) {
        geradorInstrucoes(TAM_INST);
        lerGeradorInst(inst);
    }

    if(prog_multiplicacao) {
        criarProgramaMultiplicao(5,100);
        lerProgramaMultiplicacao(inst,5,100);
    }

    //programaMultiplicacao(inst,10,10);
    //programaDivisao(inst,100,1);
    //programaPA(inst,1,100,1);
    //programaFibonacci(inst,100);
    //programaAreaQuadrado(inst,10);
    //programaVolumeCubo(inst,10);
    //programaVolumeCilindo(inst,10,10);

    CPU(memoriaRAM, inst,inst_interrupcao, cache1, cache2, cache3);
    mostrarEstatisticas();

    delete [] memoriaRAM;
    delete [] inst;
    delete [] cache1;
    delete [] cache2;
    delete [] cache3;

    return 0;
}