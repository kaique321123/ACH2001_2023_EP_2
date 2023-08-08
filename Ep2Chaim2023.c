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


//ORDENA EM ORDEM DECESCENTE OS PONTOS GANHOS
void bubbleordenaPontos(time * timescampeonato, int numerodetimes){
int i, ult;
time aux;

for(ult=0; ult<numerodetimes -1; ult++){
    for(i=0; i<numerodetimes -ult -1; i++){
      if(timescampeonato[i].PontosGanhos < timescampeonato[i + 1].PontosGanhos){
          aux=timescampeonato[i];
          timescampeonato[i] = timescampeonato[i + 1];
          timescampeonato[i + 1] = aux;
                                                                               }
                                          }
                                      }  
}

//ORDENA EM ORDEM DECESCENTE O SALDO DE GOLS
void  bubbleordenaSaldoGols(time * timescampeonato, int numerodetimes){
int i, ult;
time aux;

for(ult=0; ult<numerodetimes -1; ult++){
    for(i=0; i<numerodetimes -ult -1; i++){
      if(timescampeonato[i].SaldoDeGols < timescampeonato[i + 1].SaldoDeGols){
          aux=timescampeonato[i];
          timescampeonato[i] = timescampeonato[i + 1];
          timescampeonato[i + 1] = aux;
                                                                               }
                                          }
                                      }  
}

//ENCONTRA SE O TIME ESTÁ NO ARRAJO DE TIMES DO CAMPEONATO
int encontratime(time *timescampeonato, char *nome, int numerodetimes) {
  int i = 0;
  while (i < numerodetimes) {
    if (strcmp(timescampeonato[i].nome, nome) == 0) {
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

void computadadostimes(time *timescampeonato, int numerodetimes, jogo *dadosjogos, int numerojogos) {
  for (int i = 0; i < numerojogos; i++) {
//ENCONTRA A POSIÇÃO DO TIME LOCAL NO ARRAY
    int posicaoLocal = encontratime(timescampeonato, dadosjogos[i].local, numerodetimes);

//ENCONTRA A POSIÇÃO DO TIME VISITANTE NO ARRAY
    int posicaoVisitante = encontratime(timescampeonato, dadosjogos[i].visitante, numerodetimes);

//ATUALIZA OS DADOS DO TIME LOCAL
    timescampeonato[posicaoLocal].GolsMarcados = timescampeonato[posicaoLocal].GolsMarcados + dadosjogos[i].golslocal;
    timescampeonato[posicaoLocal].GolsSofridos = timescampeonato[posicaoLocal].GolsSofridos + dadosjogos[i].golsvisitante;

//ATUALIZA OS DADOS DO TIME VISITANTE
    timescampeonato[posicaoVisitante].GolsMarcados =  timescampeonato[posicaoVisitante].GolsMarcados + dadosjogos[i].golsvisitante;
    timescampeonato[posicaoVisitante].GolsSofridos =  timescampeonato[posicaoVisitante].GolsSofridos + dadosjogos[i].golslocal;

//TIME LOCAL VENCEU VITÓRIA VALE 3
    if (dadosjogos[i].golslocal > dadosjogos[i].golsvisitante) {
      timescampeonato[posicaoLocal].Vitorias++;
      timescampeonato[posicaoLocal].PontosGanhos = timescampeonato[posicaoLocal].PontosGanhos + 3;
      timescampeonato[posicaoVisitante].Derrotas++;
    } 
    
//TIME VISITANTE VENCEU VITÓRIA VALE 3
    else if(dadosjogos[i].golslocal < dadosjogos[i].golsvisitante) {
      timescampeonato[posicaoVisitante].Vitorias++;
      timescampeonato[posicaoVisitante].PontosGanhos = timescampeonato[posicaoVisitante].PontosGanhos + 3;
      timescampeonato[posicaoLocal].Derrotas++;
    }

//EMPATE VALE 1
    else{
      timescampeonato[posicaoLocal].Empates++;
      timescampeonato[posicaoLocal].PontosGanhos = timescampeonato[posicaoLocal].PontosGanhos + 1;
      timescampeonato[posicaoVisitante].Empates++;
      timescampeonato[posicaoVisitante].PontosGanhos = timescampeonato[posicaoVisitante].PontosGanhos + 1;
        }

//CALCULA A AVERAGE DO TIME
    if(timescampeonato[posicaoLocal].GolsSofridos > 0){
      timescampeonato[posicaoLocal].GolAverage = (float)timescampeonato[posicaoLocal].GolsMarcados / timescampeonato[posicaoLocal].GolsSofridos;
                                                      }
    else {
      timescampeonato[posicaoLocal].GolAverage = (float)timescampeonato[posicaoLocal].GolsMarcados;
         }
    if(timescampeonato[posicaoVisitante].GolsSofridos > 0){
      timescampeonato[posicaoVisitante].GolAverage = (float)timescampeonato[posicaoVisitante].GolsMarcados / timescampeonato[posicaoVisitante].GolsSofridos;
                                                          }
    else {
      timescampeonato[posicaoVisitante].GolAverage = (float)timescampeonato[posicaoVisitante].GolsMarcados;
         }

  }
}

void imprimeclassificacao(time *timescampeonato, int numerodetimes) {
// Ordenar times por pontos ou saldo de gols (chamar funções bubbleordenaPontos e bubbleordenaSaldoGols)
  bubbleordenaPontos(timescampeonato, numerodetimes);
  bubbleordenaSaldoGols(timescampeonato, numerodetimes);

// Imprimir a classificação formatada
printf("%s,%s,%s,%s,%s,%s,%s,%s\n", "Posicao","Nome","Pontos Ganhos","Vitorias","Empates","Derrotas","Saldo de Gols","Gol Average");

int i;
for(i=0; i<numerodetimes;i++){
    printf("%d,%s,%d,%d,%d,%d,%d,%.4f\n", i + 1, timescampeonato[i].nome, timescampeonato[i].PontosGanhos, timescampeonato[i].Vitorias, timescampeonato[i].Empates, timescampeonato[i].Derrotas, timescampeonato[i].SaldoDeGols, timescampeonato[i].GolAverage);
}
}

/*Salva os dados da classificação dos tipos em arquivo no disco
void salvaclassificacao(time * timescampeonato,int notimes, char * arquivo){
 Adicione seu código*/ 
 

int main() {
  time times[NumeroMaxTimes];
  jogo jogos[NumeroMaxJogos];
  int i;
  int nojogos, golslocal = 0, golsvisitante = 0;
  char local[30],visitante[30];

  printf("Entre os jogos no formato \"time local, time visitante, golslocal, golsvisitante\" (gols local negativo encerra a entrada de dados)\n");
  for(i = 0; i < NumeroMaxJogos; ++i) {
    lenometime(local);
    lenometime(visitante);
    scanf("%d,%d",&golslocal,&golsvisitante);
    getchar(); // consome o enter do scanf
    //printf("local %s visitante %s ", local, visitante);
    //printf("golslocal %d, golsvisitante %d\n", golslocal,golsvisitante);
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

  // Confirmando os valores lidos
  // for(i=0; i < nojogos;++i)
  //   printf("%d:%s,%s,%d,%d\n",i+1,jogos[i].local,jogos[i].visitante,jogos[i].golslocal,jogos[i].golsvisitante);

  int numerodetimes = crialistatimes(times, jogos, nojogos);
  // printf("Notimes: %d\n", notimes);
  // printf("\nTimes:\n");
  // for(i=0; i < notimes;++i)
  //   printf("%2d:%s\n",i+1,times[i].nome);

  computadadostimes(times, numerodetimes, jogos, nojogos);
  // printf("\nResultado da computação dos dados dos jogos:\n");
  // for(i=0; i < notimes;++i)
  //   {
  //   printf("%d:%s\n",i,times[i].nome);
  //   printf("Pontos ganhos: %d\n",times[i].PontosGanhos);
  //   printf("Gols marcados: %d\n",times[i].GolsMarcados);
  //   printf("Gols sofridos: %d\n",times[i].GolsSofridos);
  //   printf("Vitorias: %d\n",times[i].Vitorias);
  //   printf("Saldo de gols: %d\n",times[i].SaldoDeGols);
  //   printf("Gols average: %2.3f\n",times[i].GolAverage);
  // }

  imprimeclassificacao(times,numerodetimes);

  // Opcional
  //salvaclassificacao(times,numerodetimes,"campeonatoIP.dat");
return 0;
}
