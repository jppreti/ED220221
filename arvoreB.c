/*
creditos para mateus pinto
https://gist.github.com/mateuspinto/1714915f1c67467b89f4a6a4ef79ec04

*/
#include<stdlib.h>
#include<stdio.h>
#define M 2 // Declarando a Ordem
#define MM  (M * 2) //Ordem -1 ; Dobrando a metade , que eh a ordem.
#define FALSE 0
#define TRUE  1

typedef long TipoChave;
typedef struct TipoRegistro {
  TipoChave Chave;
  /*outros componentes*/
} TipoRegistro;
typedef struct TipoPagina* TipoApontador;
typedef struct TipoPagina {
  short n;
  TipoRegistro r[MM]; // Colcoando espaço para 4 chaves.
  TipoApontador p[MM + 1]; // Colocando espaço para 5 ponteiros
} TipoPagina;

void Inicializa(TipoApontador *Dicionario)
{  *Dicionario = NULL; } // Incializa uma pagina

void inOrder(TipoApontador tree){ // esssa funcao demonstra a pagina a ordem
    int i;

    if(tree != NULL){

        for(i=0; i<tree->n; i++){
            inOrder(tree->p[i]);
            printf("%ld ", tree->r[i].Chave);
        }

        inOrder(tree->p[i]);
    }
    return;
}

void Pesquisa(TipoChave x, TipoApontador Ap)
{ long i = 1;
  if (Ap == NULL) 
  { printf("TipoRegistro nao esta presente na arvore\n"); // Caso o apontador nao exista
    return;
  }
  while (i < Ap->n && x > Ap->r[i-1].Chave) i++; // navega dentro da pagina
  if (x == Ap->r[i-1].Chave) // Caso encontra a chave, parabens encontrou
  { //*x = Ap->r[i-1];
    printf("(%ld)\n",i);
	  return;
  }
  if (x < Ap->r[i-1].Chave){ // caso o valor for maior que a chave entreno ponteiro
	  Pesquisa(x, Ap->p[i-1]); printf("[%ld]",i-1);
  }  
  else{
	  Pesquisa(x, Ap->p[i]); printf("[%ld]",i);
  } 
} 

void InsereNaPagina(TipoApontador Ap, TipoRegistro Reg, TipoApontador ApDir)
{ short NaoAchouPosicao;
  int k;
  k = Ap->n;  NaoAchouPosicao = (k > 0);
  while (NaoAchouPosicao) // navegacao dentro da pagina 
    { if (Reg.Chave >= Ap->r[k-1].Chave) 
      { NaoAchouPosicao = FALSE;
        break;
      }
      Ap->r[k] = Ap->r[k-1];
      Ap->p[k+1] = Ap->p[k];
      k--;
      if (k < 1) NaoAchouPosicao = FALSE;
    }
  Ap->r[k] = Reg; 
  Ap->p[k+1] = ApDir;
  Ap->n++;
} // Somente insere a chave na pagina

void Ins(TipoRegistro Reg, TipoApontador Ap, short *Cresceu, 
         TipoRegistro *RegRetorno,  TipoApontador *ApRetorno)
{ long i = 1; // Posição provavel do vetor em que novo indice sera inserido
  long j;
  TipoApontador ApTemp;

  if (Ap == NULL) // Critério de parada da recursão. Pode ser usado para arvore vazia, arvore com espaço em folhas ou arvore que explode
  { *Cresceu = TRUE; (*RegRetorno) = Reg; (*ApRetorno) = NULL;
    return;
  }

  while (i < Ap->n && Reg.Chave > Ap->r[i-1].Chave)  i++; // Percorrendo vetores dos nós para encontrar valor maior (ou igual) que o novo indice
  // Ate o limite da pagina enquanto a chave for maior que o item.
  if (Reg.Chave == Ap->r[i-1].Chave) 
  { printf(" Erro: Registro ja esta presente\n"); *Cresceu = FALSE;
    return;
  }

  if (Reg.Chave < Ap->r[i-1].Chave) i--; // Como o valor nao é igual, só pode ser maior, entao volta-se uma posição

  Ins(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno); // Chama-se recursivo para descer na arvore

  if (!*Cresceu) return; // Caso não cresca, encerra por aqui.

  if (Ap->n < MM)   /* Pagina tem espaco */
    { InsereNaPagina(Ap, *RegRetorno, *ApRetorno); // Chama insere na página pq tem esoaço
      *Cresceu = FALSE;
      return;
    } // nao precisa crescer entao volta False o Cresceu

  /* Overflow: Pagina tem que ser dividida */ // Página nao tem espaço suficiente
  ApTemp = (TipoApontador)malloc(sizeof(TipoPagina)); // Cria nova pagina pra ser raiz da subarvore que vem do split
  ApTemp->n = 0;  ApTemp->p[0] = NULL; // Ela começa com zero indices e primeiro filho pra NULL
    if (i < M + 1) // Aqui se observa se o que ha de ser inserido fica na esquerda ou direita
    { InsereNaPagina(ApTemp, Ap->r[MM-1], Ap->p[MM]); // manda o ultimo para a nova folha
      Ap->n--;
      InsereNaPagina(Ap, *RegRetorno, *ApRetorno); // insere na folha trabalhada
    } 
    else InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno); // insere na folha nova
    for (j = M + 2; j <= MM; j++) 
      InsereNaPagina(ApTemp, Ap->r[j-1], Ap->p[j]); // Manda o ultimo para a folha nova
    Ap->n = M;  ApTemp->p[0] = Ap->p[M+1]; // vai para tamanho 2
    *RegRetorno = Ap->r[M];  *ApRetorno = ApTemp; // Retorna a chave e o ponteiro topo [naturalmente o 3 item]
}

void Insere(TipoRegistro Reg, TipoApontador *Ap)
{ short Cresceu;
  TipoRegistro RegRetorno;
  TipoPagina *ApRetorno, *ApTemp;
  Ins(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno); // Chamando funcao insere auxiliar
  if (Cresceu)  /* Arvore cresce na altura pela raiz */
  { ApTemp = (TipoPagina *)malloc(sizeof(TipoPagina)); // Criando nova raiz
    ApTemp->n = 1;  // Definindo que a nova raiz só terá um índice
    ApTemp->r[0] = RegRetorno; // Definindo valor do unico indice da raiz
    ApTemp->p[1] = ApRetorno; // Definindo filho da direita da raiz, resultado do split que causou explosao no tamanho
    ApTemp->p[0] = *Ap;   // Definindo filho da esquerda da raiz, resultado do split que causou explosao no tamanho 
    *Ap = ApTemp; // Enderençando nova raiz
  }
}

void Reconstitui(TipoApontador ApPag, TipoApontador ApPai, 
                 int PosPai, short *Diminuiu)
{ TipoPagina *Aux;  long DispAux, j;
  if (PosPai < ApPai->n)  /* Aux = TipoPagina a direita de ApPag */
  { Aux = ApPai->p[PosPai+1];  DispAux = (Aux->n - M + 1) / 2;
    ApPag->r[ApPag->n] = ApPai->r[PosPai];
    ApPag->p[ApPag->n + 1] = Aux->p[0];  ApPag->n++;
    if (DispAux > 0)  /* Existe folga: transfere de Aux para ApPag */
    { for (j = 1; j < DispAux; j++)
        InsereNaPagina(ApPag, Aux->r[j-1], Aux->p[j]);
      ApPai->r[PosPai] = Aux->r[DispAux-1];  Aux->n -= DispAux;
      for (j = 0; j < Aux->n; j++) Aux->r[j] = Aux->r[j + DispAux];
      for (j = 0; j <= Aux->n; j++) Aux->p[j] = Aux->p[j + DispAux];
      *Diminuiu = FALSE;
    }
    else /* Fusao: intercala Aux em ApPag e libera Aux *///Ou seja exclui.
      { for (j = 1; j <= M; j++)
          InsereNaPagina(ApPag, Aux->r[j-1], Aux->p[j]);
        free(Aux);
        for (j = PosPai + 1; j < ApPai->n; j++) 
          { ApPai->r[j-1] = ApPai->r[j]; 
	    ApPai->p[j] = ApPai->p[j+1]; 
	  }
        ApPai->n--;
        if (ApPai->n >= M) *Diminuiu = FALSE;
      }
  }
  else /* Aux = TipoPagina a esquerda de ApPag */
    { Aux = ApPai->p[PosPai-1]; DispAux = (Aux->n - M + 1) / 2;
      for (j = ApPag->n; j >= 1; j--) ApPag->r[j] = ApPag->r[j-1];
      ApPag->r[0] = ApPai->r[PosPai-1];
      for (j = ApPag->n; j >= 0; j--) ApPag->p[j+1] = ApPag->p[j];
      ApPag->n++;
      if (DispAux > 0) /* Existe folga: transf. de Aux para ApPag */
      { for (j = 1; j < DispAux; j++)
          InsereNaPagina(ApPag, Aux->r[Aux->n - j], 
	                 Aux->p[Aux->n - j + 1]);
        ApPag->p[0] = Aux->p[Aux->n - DispAux + 1];
        ApPai->r[PosPai-1] = Aux->r[Aux->n - DispAux];
        Aux->n -= DispAux;  *Diminuiu = FALSE;
      }
      else /* Fusao: intercala ApPag em Aux e libera ApPag */
        { for (j = 1; j <= M; j++)
            InsereNaPagina(Aux, ApPag->r[j-1], ApPag->p[j]);
          free(ApPag);  ApPai->n--;
          if (ApPai->n >= M)  *Diminuiu = FALSE;
        }
    }
}

void Antecessor(TipoApontador Ap, int Ind, 
                TipoApontador ApPai, short *Diminuiu)
{ if (ApPai->p[ApPai->n] != NULL) // Se o ultimo ponteiro pai for usado, visto que precisará encaixar
  { Antecessor(Ap, Ind, ApPai->p[ApPai->n], Diminuiu);
    if (*Diminuiu) 
    Reconstitui(ApPai->p[ApPai->n], ApPai, (long)ApPai->n, Diminuiu);
    return;
  }
  Ap->r[Ind-1] = ApPai->r[ApPai->n - 1]; //Aqui ele diminuiu um e avisa se diminuiu
  ApPai->n--;  *Diminuiu = (ApPai->n < M); // Diminuiu (a arvore) se ficou abaixo da metade
} 

void Ret(TipoChave Ch, TipoApontador *Ap, short *Diminuiu)
{ long j, Ind = 1;
  TipoApontador Pag;
  if (*Ap == NULL) 
  { printf("Erro: registro nao esta na arvore\n"); *Diminuiu = FALSE;
    return;
  }
  Pag = *Ap;
  while (Ind < Pag->n && Ch > Pag->r[Ind-1].Chave) Ind++; // Buscando dentro da pagina
  if (Ch == Pag->r[Ind-1].Chave) 
  { if (Pag->p[Ind-1] == NULL)   /* TipoPagina folha */
    { Pag->n--;
      *Diminuiu = (Pag->n < M); // Detecta underflow
      for (j = Ind; j <= Pag->n; j++) // Deslocando vetor
        { Pag->r[j-1] = Pag->r[j];  Pag->p[j] = Pag->p[j+1]; }
      return;
    }
    /* TipoPagina nao e folha: trocar com antecessor */
    Antecessor(*Ap, Ind, Pag->p[Ind-1], Diminuiu);
    if (*Diminuiu) 
    Reconstitui(Pag->p[Ind-1], *Ap, Ind - 1, Diminuiu);
    return;
  }
  if (Ch > Pag->r[Ind-1].Chave) Ind++;
  Ret(Ch, &Pag->p[Ind-1], Diminuiu); // faz o mesmo processo com o sucessor
  if (*Diminuiu) Reconstitui(Pag->p[Ind-1], *Ap, Ind - 1, Diminuiu);
}  

void Retira(TipoChave Ch, TipoApontador *Ap)
{ short Diminuiu;
  TipoApontador Aux;
  Ret(Ch, Ap, &Diminuiu);
  if (Diminuiu && (*Ap)->n == 0)  /* Arvore diminui na altura */
  { Aux = *Ap;   *Ap = Aux->p[0]; // Elimina antiga raiz
    free(Aux);
  }
}  

void ImprimeI(TipoApontador p, int nivel)
{ long i;
  if (p == NULL) return;
  printf("Nivel %d : ", nivel);
  for (i = 0; i < p->n; i++)
    printf("%ld ",(long)p->r[i].Chave);
  putchar('\n');
  nivel++;
  for (i = 0; i <= p->n; i++)
    ImprimeI(p->p[i], nivel);
} 

void Imprime(TipoApontador p)
{ int  n = 0; ImprimeI(p, n); } 

void TestaI(TipoApontador p, int pai, short direita)
{ int i;
  int antecessor = 0;
  if (p == NULL) return;
  if (p->r[0].Chave > pai && direita == FALSE) 
  { printf("Erro: filho %12ld maior que pai %d\n", p->r[0].Chave, pai);
    return;
  }
  for (i = 0; i < p->n; i++) 
    { if (p->r[i].Chave <= antecessor) 
      { printf("Erro: irmao %ld maior que irmao a esquerda %d\n",
        (long)p->r[i].Chave, antecessor);
        return;
      }
      antecessor = p->r[i].Chave;
    }
  for (i = 0; i < p->n; i++) 
    TestaI(p->p[i], p->r[i].Chave, FALSE);
  TestaI(p->p[p->n], p->r[i].Chave, TRUE);
}

void Testa(TipoApontador p)
{ int i;
  if (p == NULL) return;
  for (i = 0; i < p->n; i++) 
    TestaI(p->p[i], p->r[i].Chave, FALSE);
  TestaI(p->p[p->n], p->r[i].Chave, TRUE);
}

int main(int argc, char *argv[])
{ // inicializacao
	TipoRegistro x;
  	TipoPagina *D;
 	Inicializa(&D);
	
	
	int opcao;
	while(1){
		
		printf("\nO que deseja fazer?\n 1 - Adicionar\n 2 - Remover\n 3 - Para verficar presença\n 0 - Para sair\n");
		scanf("%d",&opcao);
		if(opcao == 1){
			printf("Digite a entrada\n");
			printf("Chave: ");
  			scanf("%ld%*[^\n]", &x.Chave);
			getchar();
			
			Insere(x, &D);
    		Imprime(D); 
    		inOrder(D);
    		printf("\n");
    	}else if (opcao == 2){
			printf("Digite o que quer remover\n");
			printf("Chave: ");
			scanf("%ld%*[^\n]", &x.Chave);
			getchar();
			Retira(x.Chave, &D);
			Imprime(D);
		}else if (opcao == 3){
			printf("Digite o que quer buscar\n");
			printf("Chave: ");
			scanf("%ld%*[^\n]", &x.Chave);
			getchar();
			Pesquisa(x.Chave, D);
			Imprime(D);
		}else if( opcao == 0){
			break;
		}
	}
return 0;
}