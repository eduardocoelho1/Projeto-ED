/* Equipe:
 * Estevão Augusto da Fonseca Santos
 * Felipe Geraldo de Oliveira
 * Eduardo Cesar Cauduro Coelho
 */


#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>

using namespace std;

struct call911{
	int e;
	int id; //atributo secundario
	float lat, lng, zip;
	char addr[66]; //atributo primario
	char desc[121], title[37];
	char timeStamp[20], twp[18];
};

struct arquivos{
	ifstream arq;
	bool* ativo;
	call911* buffer;
};

void intercala(call911* v, int p, int q, int r) {
    int i = p, j = q + 1;
    int tamanho = r - p + 1;
    call911 w[tamanho]; // vetor auxiliar
	int resultado;
    int k = 0;

    while ((i <= q) && (j <= r)) {
		resultado = strcmp(v[i].addr,v[j].addr);
		
		// resultado = 1, significa que o v[i].addr é maior que v[j].addr
		// resultado = -1, significa que o v[i].addr é menor que v[j].addr
		// resultado = 0, significa que o v[i].addr é igual a v[j].addr
        if (0 > resultado) {
            w[k++] = v[i++];
        } else if(resultado > 0) {
            w[k++] = v[j++];
        }
		else{ //se forem iguais compara-se com os ids
			if (v[i].id < v[j].id) {
        	    w[k++] = v[i++];
        	} else {
            	w[k++] = v[j++];
        	}
		}
    }

    // terminou um dos vetores, agora copia o outro
    while (i <= q) {
        w[k++] = v[i++];
    }

    while (j <= r) {
        w[k++] = v[j++];
    }

    // agora copiamos do vetor auxiliar aux[] em v[p:r]
    for (int m = 0; m < tamanho; m++) {
        v[p + m] = w[m];
    }
}

void mergesort(call911* a, int inicio, int fim) {
    int meio;
    if (inicio < fim) {
        meio = (inicio + fim) / 2;
        mergesort(a, inicio, meio);
        mergesort(a, meio + 1, fim);
        intercala(a, inicio, meio, fim);
    }
}

void salva_buffer(fstream& arquivoBin, call911* buffer_saida, int tamanho){
	for(int i = 0; i < tamanho; i++){ 
		arquivoBin.write((const char *) &buffer_saida[i], sizeof(call911)); //salva no arquivo binario principal
	}
}

void encher_buffer(arquivos& arquivo, int tamanho_buffer){
	for(int i = 0; i < tamanho_buffer; i++){
		if(arquivo.arq.read((char *) &arquivo.buffer[i], sizeof(call911))){ //escreve os dados do arquivo no buffer
			arquivo.ativo[i] = true; //como os dados foram escritos, define a posicao como true, ou apta.
		}
		else
			arquivo.ativo[i] = false; //caso ainda reste posicoes no buffer mas os dados do arquivo acabaram, coloca essas posicoes restantes como false, ou inaptas.
	}
}

call911 encontra_menor(int& posicao_arquivo, arquivos* arqs, int* posicoes_buffer_entrada, int numero_de_arquivos){
	posicao_arquivo = 0;
	while(arqs[posicao_arquivo].ativo[posicoes_buffer_entrada[posicao_arquivo]] == false){ //ate encontrar uma posicao ativa 
		posicao_arquivo++;
	}
	for(int i = posicao_arquivo + 1; i < numero_de_arquivos; i++){ //esse for encontra qual arquivo possui o registro com menor addr, caso tenha empate, ele verifica o ID
		if(0 > strcmp(arqs[i].buffer[posicoes_buffer_entrada[i]].addr, arqs[posicao_arquivo].buffer[posicoes_buffer_entrada[posicao_arquivo]].addr)){
			if(arqs[i].ativo[posicoes_buffer_entrada[i]] == true)
			posicao_arquivo = i;
		}
		else if(0 == strcmp(arqs[i].buffer[posicoes_buffer_entrada[i]].addr, arqs[posicao_arquivo].buffer[posicoes_buffer_entrada[posicao_arquivo]].addr)){
			if(arqs[i].buffer[posicoes_buffer_entrada[i]].id < arqs[posicao_arquivo].buffer[posicoes_buffer_entrada[posicao_arquivo]].id){
				if(arqs[i].ativo[posicoes_buffer_entrada[i]] == true)
				posicao_arquivo = i;
			}
		}
	}
	return arqs[posicao_arquivo].buffer[posicoes_buffer_entrada[posicao_arquivo]]; 
}

void intercala_externo(fstream& arquivoBin, int numero_de_arquivos, string* nome_dos_arquivos, int quantidade_de_registros_totais){
	arquivos* arqs = new arquivos[numero_de_arquivos];
	int tamanho_buffer = 15;
	for(int i = 0; i < numero_de_arquivos; i++){
		arqs[i].arq.open(nome_dos_arquivos[i], ios::binary);
		arqs[i].ativo = new bool[tamanho_buffer]; //esse atributo ativo eh para verificar se a posicao do buffer esta apta a ser interacalada
		arqs[i].buffer = new call911[tamanho_buffer];
		encher_buffer(arqs[i], tamanho_buffer);
	}
	call911* buffer_saida = new call911[tamanho_buffer];
	int posicao_arquivo = 0;
	int quantidade_de_registros_atual = 0;
	arquivoBin.seekg(0, ios::beg);
	int posicao_buffer_saida = 0;
	int posicoes_buffer_entrada[numero_de_arquivos]{0}; 
	while(quantidade_de_registros_atual < quantidade_de_registros_totais){

		buffer_saida[posicao_buffer_saida] = encontra_menor(posicao_arquivo, arqs, posicoes_buffer_entrada, numero_de_arquivos);

		posicao_buffer_saida++; //como o buffer de saida recebeu um registro, adianta-se uma posicao no vetor
		posicoes_buffer_entrada[posicao_arquivo]++; //como o buffer de entrada de um arquivo específico foi escrito no buffer de saída, adianta-se uma posicao no vetor
		quantidade_de_registros_atual++;

		if(posicao_buffer_saida == tamanho_buffer){ //caso já tenham sido escritos 15 registros no buffer de saída
			salva_buffer(arquivoBin, buffer_saida, tamanho_buffer);
			posicao_buffer_saida = 0; //reseta a posicao pra 0
		}
		if(posicoes_buffer_entrada[posicao_arquivo] == tamanho_buffer){//caso os registros de determinado buffer de entrada ja tenham sido escritos no buffer de saida
			encher_buffer(arqs[posicao_arquivo], tamanho_buffer);
			posicoes_buffer_entrada[posicao_arquivo] = 0; //reseta a posicao pra 0
		}
	}
	if(posicao_buffer_saida != 0)
		salva_buffer(arquivoBin, buffer_saida, posicao_buffer_saida); //caso ainda reste dados no buffer de saída que nao foram escritos no arquivo principal, pois sao escritos de 15 em 15

	delete buffer_saida; //o que ocorre aqui é a desalocação de memória alocada, fecha os arquivos temporarios e os deleta.
	for(int i = 0; i < numero_de_arquivos; i++){
		delete arqs[i].ativo;
		delete arqs[i].buffer;
		arqs[i].arq.close();
		remove(nome_dos_arquivos[i].c_str());
	}
	delete arqs;
}

void ordena_arquivo(fstream& arq, int tamanho_do_arquivo){
	call911 vetor[tamanho_do_arquivo];	
	arq.seekg(0, ios::beg);
	for(int i = 0; i < tamanho_do_arquivo; i++){ //le os dados dos arquivos menores para um vetor
		arq.read((char *) &vetor[i], sizeof(call911));
	}
	mergesort(vetor, 0, tamanho_do_arquivo-1); //ordena o vetor
	arq.seekp(0, ios::beg);
	for(int i = 0; i < tamanho_do_arquivo; i++){
		arq.write((const char *) &vetor[i], sizeof(call911)); //reescreve os dados ordenados do vetor nos arquivos
	}
	arq.close();
}

void dividir_arquivo(fstream& arquivoBin, int numero_de_arquivos, string* nome_dos_arquivos, int structs_por_arquivo){
	call911 dado;
	int tamanho_do_arquivo = 0;
	arquivoBin.seekg(0, ios::beg);
	for(int i = 0; i < numero_de_arquivos; i++){
		tamanho_do_arquivo = 0;
		nome_dos_arquivos[i] = "arquivo" + to_string(i+1) + ".dat"; //cria arquivo1.dat, arquivo2.dat... etc
		ofstream arq(nome_dos_arquivos[i], ios::binary);
		for(int j = 0; j < structs_por_arquivo; j++){
			if(arquivoBin.read((char *) &dado, sizeof(call911))){ //escreve os dados do arquivo binario maior nos arquivos menores 
				arq.write((const char *) &dado, sizeof(call911));
				tamanho_do_arquivo++;
			}
		}	
		arq.close();
		fstream arq_in_out(nome_dos_arquivos[i], ios::binary|ios::in|ios::out);
		ordena_arquivo(arq_in_out, tamanho_do_arquivo);
		arq_in_out.close();
	}
}
	
void ordenacao_externa(){
    fstream arquivoBin("binario.dat", ios::binary|ios::in|ios::out);
    if(arquivoBin){ //caso o binario.dat exista
		arquivoBin.seekg(0, ios::end);
		int numero_de_structs = arquivoBin.tellg()/sizeof(call911);
		int numero_de_arquivos;
		if(numero_de_structs%1000 == 0){ //1000 é o numero maximo de registros por arquivo
			numero_de_arquivos = numero_de_structs/1000;
		} else {
			numero_de_arquivos = numero_de_structs/1000 + 1;
			string nome_dos_arquivos[numero_de_arquivos];
			dividir_arquivo(arquivoBin, numero_de_arquivos, nome_dos_arquivos, 1000);
			arquivoBin.close(); 
			fstream arquivoBin1("binario.dat", ios::binary|ios::out);
			intercala_externo(arquivoBin1, numero_de_arquivos, nome_dos_arquivos, numero_de_structs);
			cout << endl << "Ordenacao Externa Concluida!" << endl << endl;
		}
	} else { //caso o binario.dat nao exista
		arquivoBin.close();
		cout << "Arquivo binario nao existe!" << endl;
	}
}

int main(){
	char opcao;
	
	do{
		cout << "=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#" << endl;
		cout << "       Ordenador de Arquivos Binarios" << endl;
		cout << "=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#" << endl << endl;
	
		cout << "0)Sair" << endl;
		cout << "1)Ordenar arquivo" << endl << endl;
		
		cout << "=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#" << endl;
		cout << "Sua resposta: ";
		
		
		cin >> opcao;
		
		switch(opcao){
			case '0':
				break;
			case '1':
				ordenacao_externa();
				break;
			default:
				cout << "Opcao inexistente" << endl;
		}
	}while(opcao != '0');
	
	return 0;
}

