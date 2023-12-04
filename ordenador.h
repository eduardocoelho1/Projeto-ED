#ifndef ORDENACAO_H_
#define ORDENACAO_H_

#include "call911.h"
using namespace std;

struct arquivos{
	ifstream arq;
	bool* ativo;
	call911* buffer;
};

void intercala(call911* v, int p, int q, int r);

void mergesort(call911* a, int inicio, int fim);

void salva_buffer(fstream& arquivoBin, call911* buffer_saida, int tamanho);

void encher_buffer(arquivos& arquivo, int tamanho_buffer);

call911 encontra_menor(int& posicao_arquivo, arquivos* arqs, int* posicoes_buffer_entrada, int numero_de_arquivos);

void intercala_externo(fstream& arquivoBin, int numero_de_arquivos, string* nome_dos_arquivos, int quantidade_de_registros_totais);

void ordena_arquivo(fstream& arq, int tamanho_do_arquivo);

void dividir_arquivo(fstream& arquivoBin, int numero_de_arquivos, string* nome_dos_arquivos, int structs_por_arquivo);
	
void ordenacao_externa();

#endif