#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include "operadores_geneticos.h"

#define M 30
#define l 36
#define Geracoes 50

using namespace std;


//Gravar as saidas------------------------------------------------------------------------

void gravar_arquivo(int melhor_fitness[], float media_fitness[])
{
    ofstream Arquivo("melhor_fit.text",ios_base::app);
    ofstream Arquivo2("media_fit.text",ios_base::app);
    //ofstream Arquivo3("ind_diferentes.text",ios_base::app);


    if(!Arquivo)
    {
        cout<<"Falhou arquivo!"<<endl;
        return;
    }
    if(!Arquivo2)
    {
        cout<<"Falhou arquivo!"<<endl;
        return;
    }

    for(int i=0;i<(Geracoes+1);i++)
    {
       Arquivo<< melhor_fitness[i]<<"  ";
       Arquivo2<< media_fitness[i]<<"  ";
      // Arquivo3<< diferentes[i]<<"  ";
    }

    Arquivo<<endl;
    Arquivo2<<endl;
    //Arquivo3<<endl;

}

//Fitness diferentes------------------------------------------------------------------------

/*int diferentes(int Q[][l])
{
    int V[l],difer=0,controle=0;
    for(int i=0;i<(M-1);i++)
    {
        insercao_individuo(V,Q[i]);

        for(int j=i+1;j<M;j++)
        {

            for(int w=0;w<l;w++)
            {
                if(V[w]!=Q[j][w])
                {
                    difer++;
                    break;
                }
            }
        }
    }
    return difer;
}*/


void algoritmo_genetico()
{
    srand( (unsigned)time(NULL) );
    int P[M][l], mating_pool[M],nova_geracao[M][l];
    int melhor_fit[Geracoes+1];
    float media_fit[Geracoes+1];
    int difer[Geracoes+1];

    float Pc=0.8;

    inicializa(P);
    cout<<"Primeira geracao= "<<endl;
    for(int i=0;i<M;i++){
        for(int j=0;j<l;j++)
            cout<<P[i][j]<<" ";

        cout<<"Fitness= "<<fitness(P[i])<<endl;
        cout<<endl<<endl;
    }

    //Gerações
    for(int i=0;i<Geracoes;i++)
    {
        //guarda no arquivo
        melhor_fit[i]=fitness(P[ maior_fitness(P) ]);
        media_fit[i]=media_fitness(P);
        //difer[i]=diferentes(P);
       // cout<<"diferentes= "<<difer[i]<<endl;

        //Operadores geneticos
        selecao(P,mating_pool);
        cruzamento(P,mating_pool,nova_geracao,Pc);
        Mutacao(nova_geracao);

        Elitismo(P,nova_geracao);

        //População recebe nova geração
        for(int j=0;j<M;j++)
            insercao_individuo(P[j], nova_geracao[j]);
    }

    cout<<"Ultima geracao= "<<endl;
    for(int i=0;i<M;i++){
        for(int j=0;j<l;j++)
            cout<<P[i][j]<<" ";

        cout<<"Fitness= "<<fitness(P[i])<<endl;
        cout<<endl<<endl;
    }

    //guarda no arquivo, insere no ultimo elemento
    melhor_fit[Geracoes]=fitness(P[ maior_fitness(P) ]);
    media_fit[Geracoes]=media_fitness(P);
//    difer[Geracoes]=diferentes(P);

    gravar_arquivo(melhor_fit,media_fit);

}



int main()
{
    srand( (unsigned)time(NULL) );

    //for(int i=0;i<2;i++)
        algoritmo_genetico();

    return 0;
}










