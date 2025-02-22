/*inclusao de bibliotecas diversas*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


FILE* rank; /*variavel global para o arquivo que contem o ranking*/
FILE* base_two; /*variavel global para o arquivo que contem as pecas do jogo*/
int  matriz[10][5]; /*inicializa a matriz principal do jogo*/
int colunas[5];  /*array que guardara a altura das colunas*/
long long int high_score = 0;
char file[15] = "numeros.txt"; /*abre o arquivo com os numeros de leitura*/
char binario[] = "ranking.bin";
int martelo=0; /*variavel para quardar a quantidade de martelos*/
int contador_martelo=0; /*e a frequencia com que ele ganhara martelos*/ 

/*chamada para limpeza da tela*/
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif




/*struct para guardar o ranking,conforme solicitado*/
typedef struct {
	char nickname[20];   /*guarda o nome do jogador*/
	long long int pontuacao;    /*guarda quantos pontos ele fez*/
} dadosJogador;
/*funcao que mostra o menu de boas-vindas e guarda o nome do jogador*/
dadosJogador info; /*variavel global para gravar no ranking a nova pontuacao*/

/*funcao para trocar as posicoes no ranking durante bubblesort*/
void trocar(dadosJogador *a, dadosJogador *b) {
    dadosJogador temp = *a;
    *a = *b;
    *b = temp;
}

void bubblesort(dadosJogador testa[], int cont){ /*funcao bubblesort para ordenar o ranking em ordem decrescente*/

	int i, j;
    int troca;
    for (i = 0; i < cont - 1; i++) {
        troca = 0;
        for (j = 0; j < cont - i - 1; j++) {
            if (testa[j].pontuacao < testa[j + 1].pontuacao) {
                trocar(&testa[j], &testa[j + 1]);
                troca = 1;
            }
        }
       
        if (!troca)
            break;
    }

}

void ordenararquivobinario(){/*abre o arquivo binario depois do player jogar para atualizar com a nova*/
rank = fopen(binario,"rb");
dadosJogador testa[1000];
int acaba = 0;

while (fread(&testa[acaba], sizeof(dadosJogador), 1, rank)==1) {
	acaba++;

}
fclose(rank);
bubblesort(testa, acaba);

rank = fopen(binario,"wb");
fwrite(testa, sizeof(dadosJogador), acaba, rank);
fclose(rank);
}



void menu1() {
	printf("Seja bem-vindo ao Dpop Meros!\n");
	printf("Digite seu nome para dar inicio ao jogo: \n");
	scanf("%s",info.nickname); /*guarda o nick do jogador atual para posteriormente guarda-lo no ranking*/
	getchar();
}
void limpatela() { /*funcao para limpar a tela*/
	system(CLEAR);
}
int options() { /*se o jogador pressionar 2*/
	system(CLEAR);
	printf("Bem-Vindo!\n");
	printf("\n");
	printf("1 - Jogar!\n");
	printf("\n");
	printf("2 - Configuracoes\n");
	printf("\n");
	printf("3 - Instrucoes\n");
	printf("\n");
	printf("4 - Ranking\n");
	printf("\n");
	printf("5 - SAIR...\n");
	printf("\n");
	printf("E ai, qual vai ser? : \n");
	int selecao;  /*ve qual opcao o jogador escolhe*/
	char c; /*previne loop infinito*/

    while(1) {
        if (scanf("%d", &selecao) != 1) { /*limpa o buffer se a opcao for invalida*/
            
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Opcao invalida\n");
            printf("\nE ai, qual vai ser? : ");
            continue;
        }

        switch(selecao) { /*se a entrada foi valida, vai para as outras opcoes do menu*/
            case 1: return 1;
            case 2: return 2;
            case 3: return 3;
            case 4: return 4;
            case 5: return 5;
            default:
                printf("Opcao invalida\n");
                printf("\nE ai, qual vai ser? : ");
        }
    }
	
}
void configs() { /*tela das configuracoes, retorna um valor caso tenha sido pressionado o 3*/
	limpatela();
	char input[10];  // Buffer para capturar a entrada do usuário
	do { /*loop para garantir que o player vai selecionar uma opcao valida*/

		printf("***CONFIGURACOES***\n");

		printf("\n");

		printf("1 - Zerar Ranking\n");
		printf("\n");
		printf("2 - Dificuldade\n");
		printf("\n");

		printf("3 - Voltar ao menu\n");
		printf("\n");
		printf("O que deseja fazer?\n");

		fgets(input, sizeof(input), stdin);  /*evita loop infinito se entrada for invalida*/
		int opcao;

		

		if (sscanf(input, "%d", &opcao) != 1) {
           
			limpatela();
            continue;  
        }

		if(opcao==3) { /*se selecionou o 3, volta a mostrar o menu*/
			return;
		}

		switch(opcao) {/*se selecionou uma opcao errada, o deixa preso dentro do loop*/

		case 1:
		rank = fopen(binario,"wb");
		fclose(rank);

			printf("Ranking zerado!\n");
			printf("\n");

			break;

		case 2:
			printf("Ainda nao disponivel\n");
			printf("\n");

			break;

			default:
                limpatela();
                break;
		}
	} while(1);
}

void instrucoes() {
	system(CLEAR);
	printf("O objetivo do jogo e dar merge em todos os numeros antes do grid ser totalmente preenchido!\n");
	printf("A cada merge, o numero que voce colocou sera multiplicado por 2 elevado a quantidade de vizinhos\n");
	printf("A cada 10000 pontos obtidos voce ganha um martelo\n");
	printf("Ao pressionar 7, voce vai ter a opcao de remover um bloco do grid, gastando um martelo\n");
	printf("Se o grid for totalmente preenchido voce perdera o jogo\n");
	printf("O jogo nao acaba enquanto voce nao gastar todos os martelos\n");
	printf("\n");
	printf("pressione <1> para voltar ao menu\n");
	printf("\n");
	char entrada[10]; /*evita loop infinito*/
	do {

		int exit;

		fgets(entrada, sizeof(entrada), stdin);  /*nao buga*/

		if (sscanf(entrada, "%d", &exit) == 1 && exit == 1) {
            return;  
        } 
	} while(1);

}

void ranking () {
	limpatela();
		rank = fopen(binario, "rb");
		
	
		dadosJogador jogador;
		printf("Ranking dos Jogadores:\n");
		while (fread(&jogador, sizeof(dadosJogador), 1, rank) == 1) {
			printf("%s - %lld pontos\n", jogador.nickname, jogador.pontuacao);
		}
		fclose(rank);
	int espera;
	printf("Pressione qualquer numero para voltar ao menu");
	scanf("%d",&espera);
}
int encerra() {

}
void grid(int nro,int nro_seguinte) { /*funcao fornecida pela professora*/

	int i,j;
	limpatela();

	printf("           +----+  +----+\n");
	printf("           |%4d|  |%4d|\n",nro,nro_seguinte);
	printf("           +----+  +----+\n");
	for (i=9; i>=0; i--) {
		printf("  +----+----+----+----+----+\n");
		printf("  |");
		for(j=0; j<5; j++) {
			if (matriz[i][j] != 0)
				printf("%4d|",matriz[i][j]);
			else
				printf("    |");
		}
		printf("\n");
	}
	printf("  +----+----+----+----+----+\n");
	printf("  +----+----+----+----+----+\n");
	printf("  |  1 |  2 |  3 |  4 |  5 |\n");
	printf("  +----+----+----+----+----+\n");

	printf("Score: %lld      Martelos: %d",high_score, martelo);
}
void apaga_array() {
	for (int i=0; i < 5 ; i++) { /*preenche o array de altura*/
		colunas[i] = 0;

	}
}

void verifica_altura() { /*atualiza a coluna*/

	for(int j=0; j<5; j++) { /*verifica de coluna em coluna*/

		int b = 0; /*fara a verificacao correta da altura da coluna*/

		for(int i=0; i<10; i++) { /*anda bloco por bloco da coluna*/

			if(matriz[i][j]!=0) { /*a quantidade de numeros diferentes de zero indica a altura*/

				b++; /*atualiza o tamanho daquela coluna*/

			}
		}
		colunas[j] = b; /*poe o tamanho da coluna atualizado no array de colunas*/
	}


}

/*desce os blocos*/
void cai_blocos() {

	for(int j=0; j<5; j++) { /*verifica uma coluna por vez*/

		for(int i=9; i>=1; i--) { /*garante que toda a coluna sera percorrida de cima para baixo*/

			if(matriz[i][j]!=0 && matriz[i - 1][j]==0) { /*se o numero nao for zero e o numero abaixo dele for zero, deve cair*/
				matriz[i - 1][j] = matriz[i][j];/*desce o bloco*/
				matriz[i][j]=0; /*o bloco que caiu agora virou zero*/
				i=0; /*reseta o valor de i para rever a coluna caso mais de um bloco deva cair*/

			}

		}
	}
}






int check(int linha,int put) { /*funcao para verificar vizinhos, recebe o input de coluna do player*/
	int ret=0;/*verifica se houve mudanC'as para fins de recursividade*/
	int altura_direita=0; /*verificador para alterar tamanho da coluna*/
	int altura_meio=0; /*verificador para alterar tamanho da coluna*/
	int altura_esquerda=0; /*verificador para alterar tamanho da coluna*/


	/*se todas coincidem*/
	if((colunas[linha]>0  && (matriz[colunas[linha]][put]==matriz[colunas[linha] - 1 ][put])) && (put < 4 && (matriz[colunas[linha]][put]==matriz[colunas[linha]][put + 1])) && (put > 0 && (matriz[colunas[linha]][put]==matriz[colunas[linha]][put - 1]))) {

        if(matriz[colunas[linha]][put]*8>=8192){ /*nao excede o limite*/
            matriz[colunas[linha] - 1][put] = 8192;
			high_score= high_score + 8192;
			contador_martelo = contador_martelo + 8192;
        }
        else{
            
		matriz[colunas[linha] - 1][put] = matriz[colunas[linha]][put]*8;/*se coincide, multiplica o valor por 8 e coloca abaixo*/
		high_score = high_score + matriz[colunas[linha]][put]*8;
		contador_martelo = contador_martelo +  matriz[colunas[linha]][put]*8;
        }
		 
		
		
		if(contador_martelo>10000){
			martelo = martelo + contador_martelo/10000; /*garante que o jogador recebera a quantidade certa de martelos*/
           contador_martelo=0;
		}
		matriz[colunas[linha]][put] = 0; /*se o bloco colocado caiu, agora ele e zero*/
		matriz[colunas[linha]][put + 1] = 0; /*o da direita zera*/
		matriz[colunas[linha]][put - 1] = 0; /*o da esquerda zera*/

		altura_meio++;/*verificador para alterar tamanho da coluna*/
		altura_direita++;/*verificador para alterar tamanho da coluna*/
		altura_esquerda++;/*verificador para alterar tamanho da coluna*/


		ret++;
	}


	/*se direita e esquerda coincidem*/
	else if(((matriz[colunas[linha]][put]==matriz[colunas[linha]][put + 1])&& put<4) && ((matriz[colunas[linha]][put]==matriz[colunas[linha]][put - 1])&& put >0)) {
               
        if(matriz[colunas[linha]][put]*4>=8192){
                matriz[colunas[linha]][put] = 8192;
				high_score= high_score + 8192;
			contador_martelo = contador_martelo + 8192;
               }
               else{
                matriz[colunas[linha]][put] = matriz[colunas[linha]][put]*4; /*se coincide, multiplica o valor por 4*/
				high_score = high_score + matriz[colunas[linha]][put]*4;
		contador_martelo = contador_martelo + matriz[colunas[linha]][put]*4;
               }
			  
		
		if(contador_martelo>10000){
			martelo = martelo + contador_martelo/10000; /*garante que o jogador recebera a quantidade certa de martelos*/
           contador_martelo=0;
		}

		matriz[colunas[linha]][put + 1] = 0; /*o da direita zera*/
		matriz[colunas[linha]][put - 1] = 0; /*o da esquerda zera*/

		altura_direita++;/*verificador para alterar tamanho da coluna*/
		altura_esquerda++;/*verificador para alterar tamanho da coluna*/


		ret++;
	}


	/*se baixo e esquerda coincidem*/
	else if(((matriz[colunas[linha]][put]==matriz[colunas[linha] - 1][put]) && colunas[linha] >0) && ((matriz[colunas[linha]][put]==matriz[colunas[linha]][put - 1])&& put >0)) {

        if(matriz[colunas[linha] - 1][put]*4>=8192){
			high_score= high_score + 8192;
			contador_martelo = contador_martelo + 8192;
    matriz[colunas[linha] - 1][put]=8192;
}

      else{
    matriz[colunas[linha] - 1][put] = matriz[colunas[linha] - 1][put]*4; /*se coincide, multiplica o valor por 4 e poe abaixo*/
	high_score = high_score +  matriz[colunas[linha] - 1][put]*4;
		contador_martelo = contador_martelo +  matriz[colunas[linha] - 1][put]*4;
}
		
		
		if(contador_martelo>10000){
			martelo = martelo + contador_martelo/10000; /*garante que o jogador recebera a quantidade certa de martelos*/
           contador_martelo=0;
		}
		matriz[colunas[linha]][put] = 0; /*se o bloco colocado caiu, agora ele e zero*/
		matriz[colunas[linha]][put - 1] = 0; /*o da esquerda zera*/

		altura_meio++;/*verificador para alterar tamanho da coluna*/
		altura_esquerda++;/*verificador para alterar tamanho da coluna*/

		ret++;
	}


	/*se baixo e direita coincidem*/
	else if(((matriz[colunas[linha]][put]==matriz[colunas[linha] - 1][put]) && colunas[linha]>0) && ((matriz[colunas[linha]][put]==matriz[colunas[linha]][put + 1])&& put < 4)) {
         
        if(matriz[colunas[linha]][put]*4>=8192){
            matriz[colunas[linha] - 1][put] = 8192;
			high_score= high_score + 8192;
			contador_martelo = contador_martelo + 8192;
         }
         else{
            matriz[colunas[linha] - 1][put] = matriz[colunas[linha]][put]*4; /*se coincide, multiplica o valor por 4 e poe abaixo*/
			high_score = high_score + matriz[colunas[linha]][put]*4;
			contador_martelo = contador_martelo +  matriz[colunas[linha]][put]*4;
         }
		
		
		if(contador_martelo>10000){
			martelo = martelo + contador_martelo/10000; /*garante que o jogador recebera a quantidade certa de martelos*/
           contador_martelo=0;
		}
		matriz[colunas[linha]][put + 1] = 0; /*o da direita zera*/
		matriz[colunas[linha]][put] = 0; /*se o bloco colocado caiu, agora ele e zero*/

		altura_meio++;/*verificador para alterar tamanho da coluna*/
		altura_direita++;/*verificador para alterar tamanho da coluna*/

		ret++;
	}


	/*se somente a direita coincide*/
	else if(((matriz[colunas[linha]][put]==matriz[colunas[linha]][put + 1])&& put < 4)) {
        if(matriz[colunas[linha]][put]*2>=8192){
            matriz[colunas[linha]][put] = 8192;
			high_score= high_score + 8192;
			contador_martelo = contador_martelo + 8192;
        }
        else{
            matriz[colunas[linha]][put] = matriz[colunas[linha]][put]*2; /*se coincide, multiplica o valor por 2*/
			high_score = high_score + matriz[colunas[linha]][put]*2;
			contador_martelo = contador_martelo +  matriz[colunas[linha]][put]*2;
        }

		
		
		if(contador_martelo>10000){
			martelo = martelo + contador_martelo/10000; /*garante que o jogador recebera a quantidade certa de martelos*/
           contador_martelo=0;
		}
		matriz[colunas[linha]][put + 1] = 0; /*o da direita zera*/

		altura_direita++;/*verificador para alterar tamanho da coluna*/

		ret++;
	}


	/*se somente esquerda coincide*/
	else if(((matriz[colunas[linha]][put]==matriz[colunas[linha]][put - 1])&& put >0)) {
        if(matriz[colunas[linha]][put]*2>=8192){
            matriz[colunas[linha]][put] = 8192;
			high_score= high_score + 8192;
			contador_martelo = contador_martelo + 8192;
        }
        else{
            matriz[colunas[linha]][put] = matriz[colunas[linha]][put]*2; /*se coincide, multiplica o valor por 2*/
			high_score = high_score + matriz[colunas[linha]][put]*2;
			contador_martelo = contador_martelo +  matriz[colunas[linha]][put]*2;
        }

		
		
		if(contador_martelo>10000){
			martelo = martelo + contador_martelo/10000; /*garante que o jogador recebera a quantidade certa de martelos*/
           contador_martelo=0;
		}
		matriz[colunas[linha]][put - 1] = 0; /*o da esquerda zera*/

		altura_esquerda++;/*verificador para alterar tamanho da coluna*/


		ret++;
	}


	/*se somente o de baixo coincide*/
	else if(((matriz[colunas[linha]][put]==matriz[colunas[linha] - 1][put]) && colunas[linha] >0)) {

        if(matriz[colunas[linha]][put]*2>=8192){

            matriz[colunas[linha] -  1][put] = 8192;
			high_score= high_score + 8192;
			contador_martelo = contador_martelo + 8192;
        }
        else{
            matriz[colunas[linha] -  1][put] = matriz[colunas[linha]][put]*2; /*se coincide, multiplica o valor por 2 e coloca abaixo*/
			high_score = high_score + matriz[colunas[linha]][put]*2;
			contador_martelo = contador_martelo + matriz[colunas[linha]][put]*2;
        }
		
		
		if(contador_martelo>10000){
			martelo = martelo + contador_martelo/10000; /*garante que o jogador recebera a quantidade certa de martelos*/
           contador_martelo=0;
		}
		matriz[colunas[linha]][put] = 0; /*se o do meio caiu, nao ha nada em cima*/

		altura_meio++;/*verificador para alterar tamanho da coluna*/


		ret++;
	}

	verifica_altura();/*atualiza o array de alturas*/
	cai_blocos(); /*desce os blocos necessC!rios*/


	return ret;




}
int check2(int linha,int put) { /*funcao para verificar vizinhos, recebe o input de coluna do player*/

	int ret=0;/*verifica se houve mudancas para fins de recursividade*/
	int altura_direita=0; /*verificador para alterar tamanho da coluna*/
	int altura_meio=0; /*verificador para alterar tamanho da coluna*/
	int altura_esquerda=0; /*verificador para alterar tamanho da coluna*/


	/*se todas coincidem*/
	if((linha>0  && (matriz[linha][put]==matriz[linha - 1 ][put])) && (put < 4 && (matriz[linha][put]==matriz[linha][put + 1])) && (put > 0 && (matriz[linha][put]==matriz[linha][put - 1]))) {
       if(matriz[linha][put]*8>=8192){
        matriz[linha - 1][put] = 8192;
		high_score= high_score + 8192;
			contador_martelo = contador_martelo + 8192;
       }
       else{
        matriz[linha - 1][put] = matriz[linha][put]*8; /*se coincide, multiplica o valor por 8 e coloca abaixo*/
		high_score = high_score + matriz[linha][put]*8;
		contador_martelo = contador_martelo + matriz[linha][put]*8;
       }
		
		
		if(contador_martelo>10000){
			martelo = martelo + contador_martelo/10000; /*garante que o jogador recebera a quantidade certa de martelos*/
           contador_martelo=0;
		}
		matriz[linha][put] = 0; /*se o bloco colocado caiu, agora ele e zero*/
		matriz[linha][put + 1] = 0; /*o da direita zera*/
		matriz[linha][put - 1] = 0; /*o da esquerda zera*/

		altura_meio++;/*verificador para alterar tamanho da coluna*/
		altura_direita++;/*verificador para alterar tamanho da coluna*/
		altura_esquerda++;/*verificador para alterar tamanho da coluna*/


		ret++;
	}


	/*se direita e esquerda coincidem*/
	else if(((matriz[linha][put]==matriz[linha][put + 1])&& put<4) && ((matriz[linha][put]==matriz[linha][put - 1])&& put >0)) {
           if(matriz[linha][put]*4>=8192){
            matriz[linha][put]= 8192;
			high_score= high_score + 8192;
			contador_martelo = contador_martelo + 8192;
           }
		else{
            matriz[linha][put] = matriz[linha][put]*4; /*se coincide, multiplica o valor por 4*/
			high_score = high_score + matriz[linha][put]*4;
		contador_martelo = contador_martelo + matriz[linha][put]*4;
        }
		
		if(contador_martelo>10000){
			martelo = martelo + contador_martelo/10000; /*garante que o jogador recebera a quantidade certa de martelos*/
           contador_martelo=0;
		}
		matriz[linha][put + 1] = 0; /*o da direita zera*/
		matriz[linha][put - 1] = 0; /*o da esquerda zera*/

		altura_direita++;/*verificador para alterar tamanho da coluna*/
		altura_esquerda++;/*verificador para alterar tamanho da coluna*/


		ret++;
	}


	/*se baixo e esquerda coincidem*/
	else if(((matriz[linha][put]==matriz[linha - 1][put]) && linha >0) && ((matriz[linha][put]==matriz[linha][put - 1])&& put >0)) {
        if(matriz[linha - 1][put]*4>=8192){
            matriz[linha - 1][put] = 8192;
			high_score= high_score + 8192;
			contador_martelo = contador_martelo + 8192;
        }
		else{
            matriz[linha - 1][put] = matriz[linha - 1][put]*4; /*se coincide, multiplica o valor por 4 e poe abaixo*/
			high_score = high_score +  matriz[linha - 1][put]*4;
		contador_martelo = contador_martelo +  matriz[linha - 1][put]*4;
        }
		
		if(contador_martelo>10000){
			martelo = martelo + contador_martelo/10000; /*garante que o jogador recebera a quantidade certa de martelos*/
           contador_martelo=0;
		}
		matriz[linha][put] = 0; /*se o bloco colocado caiu, agora ele e zero*/
		matriz[linha][put - 1] = 0; /*o da esquerda zera*/

		altura_meio++;/*verificador para alterar tamanho da coluna*/
		altura_esquerda++;/*verificador para alterar tamanho da coluna*/

		ret++;
	}


	/*se baixo e direita coincidem*/
	else if(((matriz[linha][put]==matriz[linha - 1][put]) && linha>0) && ((matriz[linha][put]==matriz[linha][put + 1])&& put < 4)) {
      if(matriz[linha][put]*4>=8192){
        matriz[linha - 1][put] = 8192;
		high_score= high_score + 8192;
			contador_martelo = contador_martelo + 8192;
      }
		else{
            matriz[linha - 1][put] = matriz[linha][put]*4; /*se coincide, multiplica o valor por 4 e poe abaixo*/
			high_score = high_score +  matriz[linha][put]*4;
		contador_martelo = contador_martelo + matriz[linha][put]*4;
        }
		
		if(contador_martelo>10000){
			martelo = martelo + contador_martelo/10000; /*garante que o jogador recebera a quantidade certa de martelos*/
           contador_martelo=0;
		}
		matriz[linha][put + 1] = 0; /*o da direita zera*/
		matriz[linha][put] = 0; /*se o bloco colocado caiu, agora ele e zero*/

		altura_meio++;/*verificador para alterar tamanho da coluna*/
		altura_direita++;/*verificador para alterar tamanho da coluna*/

		ret++;
	}


	/*se somente a direita coincide*/
	else if(((matriz[linha][put]==matriz[linha][put + 1])&& put < 4)) {
       if(matriz[linha][put]*2>=8192){
        matriz[linha][put] = 8192;
		high_score= high_score + 8192;
			contador_martelo = contador_martelo + 8192;
       }
		else{
            matriz[linha][put] = matriz[linha][put]*2; /*se coincide, multiplica o valor por 2*/
			high_score = high_score +  matriz[linha][put]*2;
		contador_martelo = contador_martelo + matriz[linha][put]*2;
        }
		
		if(contador_martelo>10000){
			martelo = martelo + contador_martelo/10000; /*garante que o jogador recebera a quantidade certa de martelos*/
           contador_martelo=0;
		}
		matriz[linha][put + 1] = 0; /*o da direita zera*/

		altura_direita++;/*verificador para alterar tamanho da coluna*/

		ret++;
	}


	/*se somente esquerda coincide*/
	else if(((matriz[linha][put]==matriz[linha][put - 1])&& put >0)) {
        if(matriz[linha][put]*2>=8192){
            matriz[linha][put] = 8192;
			high_score= high_score + 8192;
			contador_martelo = contador_martelo + 8192;
        }
        else{
            matriz[linha][put] = matriz[linha][put]*2; /*se coincide, multiplica o valor por 2*/
			high_score = high_score +  matriz[linha][put]*2;
		contador_martelo = contador_martelo + matriz[linha][put]*2;
        }

		
		
		if(contador_martelo>10000){
			martelo = martelo + contador_martelo/10000; /*garante que o jogador recebera a quantidade certa de martelos*/
           contador_martelo=0;
		}
		matriz[linha][put - 1] = 0; /*o da esquerda zera*/

		altura_esquerda++;/*verificador para alterar tamanho da coluna*/


		ret++;
	}


	/*se somente o de baixo coincide*/
	else if(((matriz[linha][put]==matriz[linha - 1][put]) && linha >0)) {
        if(matriz[linha][put]*2>=8192){
            matriz[linha -  1][put] = 8192;
			high_score= high_score + 8192;
			contador_martelo = contador_martelo + 8192;
        }
		else{
            matriz[linha -  1][put] = matriz[linha][put]*2; /*se coincide, multiplica o valor por 2 e coloca abaixo*/
			high_score = high_score +  matriz[linha][put]*2;
		contador_martelo = contador_martelo + matriz[linha][put]*2;
        }
		
		if(contador_martelo>10000){
			martelo = martelo + contador_martelo/10000; /*garante que o jogador recebera a quantidade certa de martelos*/
           contador_martelo=0;
		}
		matriz[linha][put] = 0; /*se o do meio caiu, nao ha nada em cima*/

		altura_meio++;/*verificador para alterar tamanho da coluna*/


		ret++;
	}

	verifica_altura();/*atualiza o array de alturas*/
	cai_blocos(); /*desce os blocos necessC!rios*/


	return ret;




}

void pos_play() { /*funcao para ver se ha mais uma soma no grid apos input do player*/

	int mudou;
	do {
		mudou = 0; /*variavel para ver mudancas*/
		for(int i = 0; i < 10; i++) { /*percorre todo o grid*/
			for(int j = 0; j < 5; j++) { /*percorre todo o grid*/
				if(matriz[i][j] != 0 && check2(i, j)) { /*se nao for zero,faz a checagem para ver se tem vizinhos*/
					mudou = 1; /*se havia vizinhos,reseta e volta a contar novamente*/
					i = 0; /*reset*/
					j = 0; /*reset*/
					break; /*sai do loop j*/
				}
			}
			if(mudou) break; /*sai do loop do i*/
		}
	} while(mudou); /*age enquanto ha mudancas*/

}

int evita_loop() {
    char troca[20];  /*garante que nao bugara*/
    int numero;

    while (1) {
        printf("Digite um numero: ");
        fgets(troca, sizeof(troca), stdin);  /*le como string*/
        
        /*tranforma em inteiro*/
        if (sscanf(troca, "%d", &numero) == 1) {
            return numero;  /*se foi valido,retorna o inteiro*/
        }

        printf("Entrada invalida! Digite um numero valido.\n");
    }
}
/*inicio da main*/

int main() {

    base_two = fopen(file,"a+");

	if (base_two == NULL) {
		printf("Erro\n");


	}
    /*ajusta a condicao de parada*/
	int fim=5;
	fprintf(base_two,"%d\n",fim);
	fprintf(base_two,"%d",fim);
	fclose(base_two);

	dadosJogador player1;/*aqui serao armazenados os dados do jogador*/


	menu1(player1); /*chama a funcao para dar as boas-vindas e manda como argumento a variavel em que serao guardados os dados do jogador*/

	while(1) { /*loop que rodara ate que o player selecione a opcao de jogar*/
		int out = 0; /*variavel temporaria para seber se o jogador quer comeC'ar o jogo*/

		switch(options()) {

		case 1: /*jogador optou por comeC'ar o jogo*/
			out++;
			break;

		case 2: /*se selecionou 2 nas opcoes, chama as configuracoes*/
			configs();
			break;

		case 3: /*se selecionou 3, abre as instrucoes*/
			instrucoes();
			break;

		case 4: /*se retornou 4, abre o ranking*/
			ranking();
			break;


		case 5:
			printf("Tchau!\n"); /*se retornou 5, fecha o programa*/
			return 0;
		}
		if(out!=0) {

			for(int i=0; i<10; i++) { /*se o jogador decidiu jogar, coloca matriz em seu estado inicial*/
				for(int j=0; j<5; j++) {
					matriz[i][j] = 0;
				}
			}
			break;
		}
	}
	limpatela();
	printf("Que comecem os jogos!\n");











	base_two = fopen(file,"r");
	if (base_two == NULL) {
		printf("Erro\n");

	}

	rewind(base_two); /*vai para o inicio do arquivo*/

	int crr, next; /*variaveis que guardarao os numeros a serem jogados(crr== current)*/
	apaga_array();




int mudou = 0; /*verificador de derrota*/
	/*Game_Loop*/
	fscanf(base_two,"%d",&crr); /*no arquivo os numeros estao dispostos verticalmente*/

	while(fscanf(base_two,"%d",&next)!=EOF) { /*se o arquivo retornar EOF,acaba*/
if(crr==5){
        break;
	}


		grid(crr,next);

		int input; /*variavel para ler aonde o bloco vai*/
		printf("\n");
		printf("Em qual coluna o bloco deve ser colocado?\n");
		int quebra_col;
		int quebra_linha;

		while(1) { /*loop que garante que a entrada e valida*/
			

			input = evita_loop();
			if( (input!=1 && input!=2 && input!=3 && input!=4 && input!=5 && input!=7) ||  (colunas[input - 1]==10 && matriz[9][input - 1]!=crr) || (input==7 && martelo==0) ) {


				printf("Opcao invalida\n");
				printf("Em qual coluna o bloco deve ser colocao?\n");
				continue;
			}

			else{
				break;
			}

		}
                
                
				
				 if(input==7){ /*se o player tem um martelo e decide usa-lo*/

                   
				   while(1){ /*garante uma entrada valida*/

					printf("Escolha uma coluna\n");
				   scanf("%d", &quebra_col); /*verifica qual vai ser a coluna que sera usado o martelo*/

				   if(quebra_col !=1 && quebra_col !=2 && quebra_col !=3 && quebra_col !=4 && quebra_col !=5){
					printf("Opcao invalida\n");
					continue;
				   }
				
				   else{
					break;
				   }
				}  
				while(1){ /*loop que garante uma entrada valida*/

					printf("Escolha uma linha\n");
					scanf("%d",&quebra_linha);/*recebe qual a linha em que o martelo sera usado*/
					if(quebra_linha !=1 && quebra_linha !=2 && quebra_linha !=3 && quebra_linha !=4 && quebra_linha !=5){
						printf("Opcao invalida\n");
						continue;
					   }
					
					   else{
						break;
					   }
				}
                        matriz[quebra_linha - 1][quebra_col - 1]=0;/*tira o numero daquele bloco*/
						cai_blocos(); /*derruba os blocos*/
						pos_play(); /*reverifica o grid*/
						martelo--; /*gasta um martelo*/
				        verifica_altura();/*nao buga*/
				 }
				
			
			
		
		else{ /*se ele nao usou o martelo,prossegue o jogo normalmente*/

		int pos = input - 1;/*facilita a compreensao do codigo*/


		matriz[colunas[pos]][pos] = crr; /*verifica qual coluna foi selecionada pelo jogador*/
		if(check(pos,pos)) {
			pos_play();
		}











		crr = next; /*no arquivo os numeros estao dispostos verticalmente*/
		

	}
    if((colunas[0]==10 && colunas[1]==10 && colunas[2]==10 && colunas[3]==10 && colunas[4]==10) && (crr!=matriz[9][0] && crr!=matriz[9][1] && crr!=matriz[9][2] && crr!=matriz[9][3] && crr!=matriz[9][4] ) && martelo==0){
        mudou++;
        break;
    }
	}/*fim do game_loop*/

	if(mudou==0){
		printf("Voce ganhou!\n");
	}	
	else{
		printf("Voce perdeu\n");
	}


info.pontuacao = high_score;

rank = fopen(binario,"a+b");

fwrite(&info,sizeof(dadosJogador),1,rank);
fclose(rank);
ordenararquivobinario();
printf("pressione 1 para sair\n");
int sair;
scanf("%d",&sair);





	return 0;
}
