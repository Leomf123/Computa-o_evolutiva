#ifndef OPERADORES_GENETICOS_H_INCLUDED
#define OPERADORES_GENETICOS_H_INCLUDED
/*----------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------
Biblioteca para operadores geneticos
criada por Leonardo Macedo Freire  2017

Para codificação binaria

estão implementados os seguintes operadores

Seleção
por Torneio
ou Roleta

cruzamento
por um ponto de corte
ou uniforme

mutação
por bit a bit
ou um bit

Elitismo, taxa de 1 individuo

E demais funções para manipulação dos vetores

------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>

#define M 30
#define l 36
#define Geracoes 50

using std::cout;
using std::endl;


void inicializa(int P[][l])
{
    srand( (unsigned)time(NULL) );
    //al de aleatoriedade
    float al;
    for(int i=0;i<M;i++){
        for(int j=0;j<l;j++){

            P[i][j]=0;

            al=rand()%10;
            al=al/10;

            if ( al <0.5  )
                P[i][j]=1;

             //cout<<al<<" ";

        }
        //cout<<endl;
    }
    //cout<<endl;
}

void imprime_individuo(int* individuo)
{
    for(int i=0;i<l;i++)
            cout<<individuo[i];
   cout<<endl;
}

int fitness(int individuo[])
{
  int fitness;

  fitness=9+individuo[1]*individuo[4]-individuo[22]*individuo[13]+individuo[23]*individuo[3];
  fitness=fitness-individuo[20]*individuo[9]+individuo[35]*individuo[14]-individuo[10]*individuo[25];
  fitness=fitness+individuo[15]*individuo[16]+individuo[2]*individuo[32];
  fitness=fitness+individuo[27]*individuo[18]+individuo[11]*individuo[33]-individuo[30]*individuo[31];
  fitness=fitness-individuo[21]*individuo[24]+individuo[34]*individuo[26]-individuo[28]*individuo[6];
  fitness=fitness+individuo[7]*individuo[12]-individuo[5]*individuo[8]+individuo[17]*individuo[19];
  fitness=fitness-individuo[0]*individuo[29]+individuo[22]*individuo[3]+individuo[20]*individuo[14];
  fitness=fitness+individuo[25]*individuo[15]+individuo[30]*individuo[11]+individuo[24]*individuo[18];
  fitness=fitness+individuo[6]*individuo[7]+individuo[8]*individuo[17]+individuo[0]*individuo[32];

  return fitness;
}

//Funções do Torneio-------------------------------------------------------------------

//retorna true se o fitness do individuo1 for maior que o 2
int maior_fitness(int* individuo1, int* individuo2)
{
       int fitness1, fitness2;

        fitness1=fitness(individuo1);
       // cout<<"Comparacao fitness:"<<endl<< "F1= "<<fitness1;
        fitness2=fitness(individuo2);
        //cout<<"   F2="<<fitness2<<endl;

        //verifica o melhor fitness
        if(fitness1>=fitness2)
            return 1;
        else
            return 0;
}

//retorna a posição do vencedor
int torneio_binario(int P[][l])
{
        int pos1=rand()%M;
        int pos2;

        do{

            pos2=rand()%M;

        }while(pos2==pos1);//impede que sejam os mesmos

        if(maior_fitness(P[pos1],P[pos2]))
           return pos1;//mating_pool recebe a posição do vencedor em P
        else
            return pos2;

}

//Funções Roleta-------------------------------------------------

float probabilidade(int P[][l], int individuo[])
{
    int soma=0;
    float prob;

    for(int i=0;i<M;i++)
        soma=soma+fitness(P[i]);

    prob=(float)(fitness(individuo))/soma;
   // cout<<"*proba= "<<prob<<endl;

    return prob;
}

void porcao_roleta(int P[][l],float* V)
{
    float Pos=0.0;
    for(int i=0;i<M;i++)
    {
        Pos=Pos+probabilidade(P,P[i]);
        V[i]=Pos;
        //cout<<"pro= "<<probabilidade(P,P[i])<<endl;
        //cout<<"Vi= "<<V[i]<<endl;
    }
}

//retorna a posição do individuo selecionado
//roleta com substiruição, ja que um individuo pode ser escolhido mais de uma vez
int roleta(int P[][l])
{
    float V[M];
    float al;
    al=((float)(rand())/RAND_MAX);//0 a 1, com 5 casas decimais de precisão
    porcao_roleta(P,V);//V ira conter a porcao da roleta dos individuos da população P, na ordem.
    for(int i=0;i<M;i++)
        //cout<<"  "<<V[i];
    //cout<<endl;
    for(int i=0;i<M;i++)
        if(al<=V[i])
        {
            /*cout<<"al= "<<al<<endl;
            cout<<"Vi= "<<V[i]<<endl;
            cout<<"i= "<<i<<endl;*/
            return i;
        }

}

//Seleção-----------------------------------------------

void selecao(int P[][l],int* mating_pool)
{
    for(int i=0;i<M;i++)
    {
         //mating_pool[i]=roleta(P);
        mating_pool[i]=torneio_binario(P);
    }
}

//Funções Um ponto de corte--------------------------------------------------------

//o individuo ind1 é inserido no ind_receptor
void insercao_individuo(int* ind_receptor, int* ind1)
{
    for(int i=0;i<l;i++)
    {
        ind_receptor[i]=ind1[i];
    }
}
void um_corte(int P[][l],int mating_pool[],int pos1,int pos2,int filhos[][l])
{

    int q;
    //ponto de corte
    q=rand()%l;

    for(int i=0;i<l;i++)
    {
        if(i<=q)
        {
            filhos[0][i]=P[mating_pool[pos2]][i];
            filhos[1][i]=P[mating_pool[pos1]][i];
        }
        else
        {
            filhos[0][i]=P[mating_pool[pos1]][i];
            filhos[1][i]=P[mating_pool[pos2]][i];
        }

    }

}

//Funções uniforme----------------------------------------------------

void uniforme(int P[][l],int mating_pool[],int pos1,int pos2,int filhos[][l])
{

    float al;
    int mascara[l];

    for(int j=0;j<l;j++)
    {
        mascara[j]=0;

        al=rand()%10;
        al=al/10;

        if ( al <0.5  )
            mascara[j]=1;
    }

    for(int i=0;i<l;i++)
    {
        if(mascara[i]==1)
        {
            filhos[0][i]=P[mating_pool[pos1]][i];
            filhos[1][i]=P[mating_pool[pos2]][i];
        }
        else
        {
            filhos[0][i]=P[mating_pool[pos2]][i];
            filhos[1][i]=P[mating_pool[pos1]][i];
        }

    }

}

//Cruzamento--------------------------------------------------------------------

void cruzamento(int P[][l],int mating_pool[],int nova_geracao[][l],float Pc)
{
    //al de aleatoriedade
    float al;
    int filhos[2][l];
    //valores usados como indice para inserir filho em nova_geracao
    int n=0,k;
    //aqui esta formando pares com posições aleatorias no mating_pool
    int pos1,pos2;

    //M/2 é o numero de pares em manting_pool, tamanho/2
    for(int i=0;i<(M/2);i++)
    {
        pos1=rand()%M;
        al=rand()%11;//0 a 10
        do{

        pos2=rand()%M;

        }while(mating_pool[pos2]==mating_pool[pos1]);//impede cruzamento entre copias dos mesmos
        //elementos, ja que mating_pool[] guarda uma posição em P, que pode ser as mesmas vindas do
        //torneio

        //compatibilizar com Pc
           al=al/10;

        //se a for menor que a probabilidade gera os dois filhos
        if (al <=Pc)
        {
             um_corte(P,mating_pool,pos1,pos2,filhos);
             //uniforme(P,mating_pool,pos1,pos2,filhos);

             k=n+1;

             //para i=0, n_g[0] n_g[1], i=1, n_g[2], n_g[3], ..., sem subst. elementos em g
             insercao_individuo(nova_geracao[i+n],filhos[0]);
             insercao_individuo(nova_geracao[i+k],filhos[1]);
             n++;
        }else
        {

             k=n+1;

             //para i=0, n_g[0] n_g[1], i=1, n_g[2], n_g[3], ..., sem subst. elementos em g
             insercao_individuo(nova_geracao[i+n],P[mating_pool[pos1]]);
             insercao_individuo(nova_geracao[i+k],P[mating_pool[pos2]]);
             n++;

        }
    }

}

//bit a bit--------------------------------------------------

void bit_bit(int* nova_geracao)
{
    float al, Pm;
    Pm=0.025;//taxa mutação
    for(int i=0;i<l;i++)
    {
        //al=rand()%11;
        //al=al/100;//adequando a taxa de mutação
        al=((float)(rand())/RAND_MAX);//0 a 1, com 5 casas decimais de precisão
        if (al<=Pm)
        {

            if(nova_geracao[i]==0)
                nova_geracao[i]=1;
            else
                nova_geracao[i]=0;
        }

    }
   // cout<<"c= "<<c<<endl;
}

//um bit----------------------------------------------------

void um_bit(int* nova_geracao)
{
    int al;
    al=rand()%l;
   // cout<<"al_m= "<<al<<endl;
    if(nova_geracao[al]==0)
                nova_geracao[al]=1;
            else
                nova_geracao[al]=0;
}

//Mutação---------------------------------------------------

void Mutacao(int nova_geracao[][l])
{
    for(int i=0;i<M;i++)
    {
        //bit_bit(nova_geracao[i]);
        bit_bit(nova_geracao[i]);
    }
}


//Funções para o elitismo---------------------------------------------------

int pior_fitness(int Q[][l])
{
    int pos, fit;
    fit=fitness(Q[0]);
    pos=0;

    for(int i=1;i<M;i++)
    {
       if(fitness(Q[i])<=fit)
       {
           fit=fitness(Q[i]);
           pos=i;
       }
    }
    return pos;
}

//mesmo nome de outra função, so essa recebe a população e guarda o maior fitness
int maior_fitness(int Q[][l])
{
    int pos, fit;
    fit=fitness(Q[0]);
    pos=0;

    for(int i=1;i<M;i++)
    {
       if(fitness(Q[i])>=fit)
       {
           fit=fitness(Q[i]);
           pos=i;
       }
    }
    return pos;
}

//Elitismo----------------------------------------------------------------------
void Elitismo(int P[][l],int nova_geracao[][l])
{
    int pos1,pos2,pos3;
    pos1=maior_fitness(P);
    pos2=maior_fitness(nova_geracao);
    pos3=pior_fitness(nova_geracao);

    if(fitness(P[pos1]) >= fitness(nova_geracao[pos2]))
    {

        insercao_individuo(nova_geracao[pos3],P[pos1]);//insere o melhor de P no pior de nova_geracao
    }
}

//media do fitness----------------------------------------------------------------------

float media_fitness(int Q[][l])
{
    float soma=0, media;
    for(int i=0;i<M;i++)
    {
       soma=soma+fitness(Q[i]);
    }
    media=(float)(soma/M);
    return media;
}



#endif // OPERADORES_GENETICOS_H_INCLUDED
