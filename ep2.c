/*********************************************************************/
/**   ACH2001 - Introducao a Programacao                            **/
/**   EACH-USP - Primeiro Semestre de 2022                          **/
/**   Turma 02 - Prof. Marcos Lordello Chaim                        **/
/**                                                                 **/
/**   Segundo Exercicio-Programa                                   **/
/**                                                                 **/
/**   <Kaique de Jesus Pessoa Santos>                   <14677144>  **/
/**                                                                 **/
/*********************************************************************/
//strcmp compara strings
//strncpy copiar o segundo elemento para dentro do primeiro
//para salvar arquivos tem uma estrutura fixa

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NumeroMaxTimes 20
#define NumeroMaxRodadas 38
#define NumeroMaxJogos NumeroMaxTimes * NumeroMaxRodadas

typedef struct auxtime {
  int PontosGanhos;
  int GolsMarcados;
  int GolsSofridos;
  int SaldoDeGols;
  int Vitorias;
  int Empates;
  int Derrotas;
  float GolAverage;
  char nome[31];
} time;

typedef struct auxjogo {
  char local[30];
  char visitante[30];
  int golslocal;
  int golsvisitante;
} jogo;

void lenometime(char *s) {
  int i;
  s[0] = '\0';
  char c;
  c = getchar();
  for (i = 0; c != ',' && i < 30; ++i) {
    s[i] = c;
    c = getchar();
  }
  s[i] = '\0';
}



// ORDENA EM ORDEM DECRESCENTE OS PONTOS GANHOS E, EM CASO DE EMPATE, PELO SALDO DE GOLS
void bubbleordenaPontosEsaldo(time *timescampeonato, int numerodetimes) {
  int i, ult;
  time aux;

  for (ult = 0; ult < numerodetimes - 1; ult++){
    for (i = 0; i < numerodetimes - ult - 1; i++){
      if ((timescampeonato[i].PontosGanhos < timescampeonato[i + 1].PontosGanhos) || ((timescampeonato[i].PontosGanhos == timescampeonato[i + 1].PontosGanhos) && (timescampeonato[i].SaldoDeGols < timescampeonato[i + 1].SaldoDeGols))) {
        aux = timescampeonato[i];
        timescampeonato[i] = timescampeonato[i + 1];
        timescampeonato[i + 1] = aux;
}
                                                 }
  }
}


// ENCONTRA SE O TIME ESTÁ NO ARRAY DE TIMES DO CAMPEONATO
int encontratime(time *timescampeonato, char *nome, int numerodetimes) {
  int i = 0;
  while (i < numerodetimes){
    if (strcmp(timescampeonato[i].nome, nome) == 0){
      return i;
                                                   }
    i++;
                           }
  return -1;
}


// CRIA A LISTA DE TIMES DO CAMPEONATO A PARTIR DOS NUMEROJOGOS
int crialistatimes(time *timescampeonato, jogo *dadosjogos, int numerojogos) {
  int i, numerodetimes = 0;
  for (i = 0; i < numerojogos; i++) {
    int posicaoLocal = encontratime(timescampeonato, dadosjogos[i].local, numerodetimes);
    if (posicaoLocal == -1) {
      strncpy(timescampeonato[numerodetimes].nome, dadosjogos[i].local, 30);
      timescampeonato[numerodetimes].PontosGanhos = 0;
      timescampeonato[numerodetimes].GolsMarcados = 0;
      timescampeonato[numerodetimes].GolsSofridos = 0;
      timescampeonato[numerodetimes].SaldoDeGols = 0;
      timescampeonato[numerodetimes].Vitorias = 0;
      timescampeonato[numerodetimes].Empates = 0;
      timescampeonato[numerodetimes].Derrotas = 0;
      numerodetimes++;
    }

    int posicaoVisitante = encontratime(timescampeonato, dadosjogos[i].visitante, numerodetimes);
    if (posicaoVisitante == -1) {
      strncpy(timescampeonato[numerodetimes].nome, dadosjogos[i].visitante, 30);
      timescampeonato[numerodetimes].PontosGanhos = 0;
      timescampeonato[numerodetimes].GolsMarcados = 0;
      timescampeonato[numerodetimes].GolsSofridos = 0;
      timescampeonato[numerodetimes].SaldoDeGols = 0;
      timescampeonato[numerodetimes].Vitorias = 0;
      timescampeonato[numerodetimes].Empates = 0;
      timescampeonato[numerodetimes].Derrotas = 0;
      numerodetimes++;
    }
  }
  return numerodetimes;
}


void atualizaDadosTime(time *time, int golsMarcados, int golsSofridos){

//SOMANDO A QUANTIDADE DE GOLS MARCADOS
  time->GolsMarcados = time->GolsMarcados + golsMarcados;

//SOMANDO A QUANTIDADE DE GOLS SOFRIDOS
  time->GolsSofridos = time->GolsSofridos + golsSofridos;

//GOLS MARCADOS MENOS GOLS SOFRIDOS
  time->SaldoDeGols = time->GolsMarcados - time->GolsSofridos;

//ESTA SOMANDO AS VITÓRIAS
//VITÓRIA DA +3 PONTOS PRO TIME QUE VENCEU  
  if (golsMarcados > golsSofridos){
    time->Vitorias = time->Vitorias + 1;
    time->PontosGanhos = time->PontosGanhos + 3;
                                  }

//DERROTA DA 0 PONTOS PRO TIME QUE PERDEU  
//ESTA SOMANDO AS DERROTAS
  else if (golsMarcados < golsSofridos){
    time->Derrotas = time->Derrotas + 1;
                                       }

//ESTA SOMANDO OS EMPATES
//EMPATE DA 1 PONTO PARA OS DOIS TIMES  
  else{
    time->Empates = time->Empates + 1;
    time->PontosGanhos = time->PontosGanhos + 1;
      }

//CALCULA A AVERAGE DO TIME
//CASO GOLS SOFRIDOS SEJA MAIOR QUE ZERO PARA A DIVISÃO NÃO DAR ZERO
  if (time->GolsSofridos > 0){
    time->GolAverage = (float) time->GolsMarcados / time->GolsSofridos;
                             }
//SE GOLS SOFRIDOS FOR IGUAL A ZERO A MÉDIA É IGUAL AOS GOLS MARCADOS                             
  else{
    time->GolAverage = (float) time->GolsMarcados;
      }
}


void computadadostimes(time *timescampeonato, int numerodetimes, jogo *dadosjogos, int numerojogos){
  for (int i = 0; i < numerojogos; i++){

//ENCONTRA A POSIÇÃO DO TIME LOCAL NO ARRAY
    int posicaoLocal = encontratime(timescampeonato, dadosjogos[i].local, numerodetimes);

//ENCONTRA A POSIÇÃO DO TIME VISITANTE NO ARRAY
    int posicaoVisitante = encontratime(timescampeonato, dadosjogos[i].visitante, numerodetimes);

//ATUALIZA OS DADOS DO TIME LOCAL   
    atualizaDadosTime(&timescampeonato[posicaoLocal], dadosjogos[i].golslocal, dadosjogos[i].golsvisitante);

//ATUALIZA OS DADOS DO TIME VISITANTE
    atualizaDadosTime(&timescampeonato[posicaoVisitante], dadosjogos[i].golsvisitante, dadosjogos[i].golslocal);
                                      }
}

void imprimeclassificacao(time *timescampeonato, int numerodetimes){  
// Ordenar times por pontos e depois por saldo de gols (chamar a função bubbleordenaPontosEsaldo)
 bubbleordenaPontosEsaldo(timescampeonato, numerodetimes);

// Imprimir a classificação formatada
printf("%s,%s,%s,%s,%s,%s,%s,%s\n", "Posicao","Nome","Pontos Ganhos","Vitorias","Empates","Derrotas","Saldo de Gols","Gol Average");

int i;
for(i=0; i<numerodetimes;i++){  
printf("%d,%s,%d,%d,%d,%d,%d,%.3f\n", i + 1, timescampeonato[i].nome, timescampeonato[i].PontosGanhos, timescampeonato[i].Vitorias, timescampeonato[i].Empates, timescampeonato[i].Derrotas, timescampeonato[i].SaldoDeGols, timescampeonato[i].GolAverage);
                             }
}


//Salva os dados da classificação dos tipos em arquivo no disco
void salvaclassificacao(time * timescampeonato,int numerodetimes, char * arquivo){
  FILE *arq = fopen(arquivo, "w");
  if (arq == NULL){
    printf("Erro ao criar o arquivo.\n");
    return;
  }

  fprintf(arq, "%s,%s,%s,%s,%s,%s,%s,%s\n", "Posicao", "Nome", "Pontos Ganhos", "Vitorias", "Empates", "Derrotas", "Saldo de Gols", "Gol Average");

  int i = 0;
  while (i < numerodetimes) {
    fprintf(arq, "%d,%s,%d,%d,%d,%d,%d,%.3f\n", i + 1, timescampeonato[i].nome, timescampeonato[i].PontosGanhos, timescampeonato[i].Vitorias, timescampeonato[i].Empates, timescampeonato[i].Derrotas, timescampeonato[i].SaldoDeGols, timescampeonato[i].GolAverage);
    i++;
  }

  fclose(arq);
}


int main() {
  time times[NumeroMaxTimes];
  jogo jogos[NumeroMaxJogos];
  int i, nojogos, golslocal = 0, golsvisitante = 0;
  char local[30],visitante[30];

  printf("Entre os jogos no formato \"time local, time visitante, golslocal, golsvisitante\" (gols local negativo encerra a entrada de dados)\n");
  for(i = 0; i < NumeroMaxJogos; ++i) {
    lenometime(local);
    lenometime(visitante);
    scanf("%d,%d",&golslocal,&golsvisitante);
    getchar(); // consome o enter do scanf
    
    if (golslocal < 0)
      break; // termina a entrada de dados

    if(strcmp(local,visitante) == 0)
      continue; // possui o mesmo nome time local e visitante

    strncpy(jogos[i].local,local,30);
    strncpy(jogos[i].visitante,visitante,30);

    jogos[i].golslocal = golslocal;
    jogos[i].golsvisitante = golsvisitante;
  }
  nojogos = i;


  int nometimes = crialistatimes(times,jogos,nojogos);

  computadadostimes(times,nometimes,jogos,nojogos);

  imprimeclassificacao(times,nometimes);

  
  salvaclassificacao(times, nometimes,"campeonatoIP.dat");

return 0;
}


