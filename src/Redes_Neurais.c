#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Redes_Neurais.h"


double **leituraVetorGrama(){

    double **matrizGrama = (double **)malloc(50*sizeof(double));
    double numGrama;

    FILE *grama;
    grama = fopen("../projeto 2/Vetores/vetorGrass.txt" ,"r");

    if(grama == NULL){
        printf("Erro grama\n");
        exit(0);
    }

    for(int i=0; i<50; i++){

        matrizGrama[i] = (double *)malloc(536*sizeof(double));

        for(int j=0; j<536; j++){
            fscanf(grama, "%lf", &numGrama);
            matrizGrama[i][j] = numGrama;
        }
    }

    /* for(int i=0; i<25;i++){
        for(int j=0; j<536; j++){
            printf("Grama: %lf\n", matrizGrama[i][j]);
        }
    } */

    return matrizGrama;
}

double **leituraVetorAsfalto(){

    double **matrizAsfalto = (double **)malloc(50*sizeof(double));
    double numAsfalto;

    FILE *asfalto;
    asfalto = fopen("../projeto 2/Vetores/vetorAsphalt.txt" ,"r");

    if(asfalto == NULL){
        printf("Leu asfalto\n");
        exit(0);
    }

    for(int i=0; i<50; i++){

        matrizAsfalto[i] = (double *)malloc(536*sizeof(double));

        for(int j=0; j<536; j++){
            fscanf(asfalto, "%lf", &numAsfalto);
            matrizAsfalto[i][j] = numAsfalto;
        }
    }

    /* for(int i=0; i<25;i++){
        for(int j=0; j<536; j++){
            printf("Asfalto: %lf\n", matrizAsfalto[i][j]);
        }
    } */

    return matrizAsfalto;
}


int *criarVetorStatusTreinamento(){

    srand(time(NULL));

    int *vetorStatusTreinamento = (int *)malloc(50*sizeof(int));

    int Asfalto = 25, Grama = 25;

    for(int i=0; i<50; i++){

        int auxAleat = rand() % 2; // auxAleat = 0 -> A | auxAleat = 1 -> B

        if(Asfalto > 0 && Grama > 0){
            if(auxAleat == 0){
                vetorStatusTreinamento[i] = 0;
                //printf("%d - Status Asfalto[%d]: %d\n", i+1, Asfalto, vetorStatusTreinamento[i]);
                Asfalto --;
            }
            else if(auxAleat == 1){
                vetorStatusTreinamento[i] = 1;
                //printf("%d -                                     Status Grama[%d]: %d\n", i+1, Grama, vetorStatusTreinamento[i]);
                Grama --;
            }
        }
        else{
            if(Asfalto == 0){
                vetorStatusTreinamento[i] = 1;
                //printf("%d -                                     Status Grama:[%d]: %d\n", i+1, Grama, vetorStatusTreinamento[i]);
                Grama --;
            }
            else if(Grama == 0){
                vetorStatusTreinamento[i] = 0;
                //printf("%d - Status Asfalto[%d]: %d\n", i+1, Asfalto, vetorStatusTreinamento[i]);
                Asfalto --;
            }
        }
    }

    return vetorStatusTreinamento;
}

double **criarMatrizTreinamento(int *VetorStatusTreinamento){

    double **matrizAsfalto = leituraVetorAsfalto();
    double **matrizGrama = leituraVetorGrama();

    /* for(int i=0; i<25;i++){
        for(int j=0; j<536; j++){
            printf("Asfalto: %lf\n", matrizAsfalto[i][j]);
        }
    }

    for(int i=0; i<25;i++){
        for(int j=0; j<536; j++){
            printf("Grama: %lf\n", matrizGrama[i][j]);
        }
    } */

    double **matrizTreinamento = (double **)malloc(50*sizeof(double));

    int a = 0, g = 0;

    for(int i=0; i<50; i++){

        matrizTreinamento[i] = (double *)malloc(536*sizeof(double));

        //vetorStatusTreinamento: 0 -> Asfalto | 1 -> Grama
        if(VetorStatusTreinamento[i] == 0){
            matrizTreinamento[i] = matrizAsfalto[a];
            //printf("A: %d\n", a);
            a++;
        }
        else{
            matrizTreinamento[i] = matrizGrama[g];
            //printf("B:            %d\n", g);
            g++;
        }
    }

    /* for(int i=0; i<50; i++){
        for(int j=0; j<536; j++){
            printf("treino[%d]: %lf\n", i, matrizTreinamento[i][j]);
        }
    } */


    return matrizTreinamento;
}


int *criarVetorStatusTeste(){

    srand(time(NULL));

    int *vetorStatusTeste = (int *)malloc(50*sizeof(int));

    int Asfalto = 25, Grama = 25;

    for(int i=0; i<50; i++){

        int auxAleat = rand() % 2; // auxAleat = 0 -> A | auxAleat = 1 -> B

        if(Asfalto > 0 && Grama > 0){
            if(auxAleat == 0){
                vetorStatusTeste[i] = 0;
                //printf("%d - Status Asfalto[%d]: %d\n", i+1, Asfalto, vetorStatusTeste[i]);
                Asfalto --;
            }
            else if(auxAleat == 1){
                vetorStatusTeste[i] = 1;
                //printf("%d -                                     Status Grama[%d]: %d\n", i+1, Grama, vetorStatusTeste[i]);
                Grama --;
            }
        }
        else{
            if(Asfalto == 0){
                vetorStatusTeste[i] = 1;
                //printf("%d -                                     Status Grama:[%d]: %d\n", i+1, Grama, vetorStatusTeste[i]);
                Grama --;
            }
            else if(Grama == 0){
                vetorStatusTeste[i] = 0;
                //printf("%d - Status Asfalto[%d]: %d\n", i+1, Asfalto, vetorStatusTeste[i]);
                Asfalto --;
            }
        }
    }

    return vetorStatusTeste;
}

double **criarMatrizTeste(int *criarVetorStatusTeste){

    double **matrizAsfalto = leituraVetorAsfalto();
    double **matrizGrama = leituraVetorGrama();

    double **matrizTeste = (double **)malloc(50*sizeof(double));


    int a = 25, g = 25;

    for(int i=0; i<50; i++){

        matrizTeste[i] = (double *)malloc(536*sizeof(double));

        //criarVetorStatusTeste: 0 -> Asfalto | 1 -> Grama
        if(criarVetorStatusTeste[i] == 0){
            matrizTeste[i] = matrizAsfalto[a];
            //printf("A: %d\n", a);
            a++;
        }
        else{
            matrizTeste[i] = matrizGrama[g];
            //printf("B:            %d\n", g);
            g++;
        }
    }

    /* for(int i=0; i<50; i++){
        for(int j=0; j<536; j++){
            printf("teste[%d]: %lf\n", i, matrizTeste[i][j]);
        }
    } */

    return matrizTeste;
}


Neuronio *criarCamadaOculta(int parametro) {

    Neuronio **ponteiroPosicaoOculto;
    ponteiroPosicaoOculto = malloc(parametro * sizeof(Neuronio*));

    for (int i = 0; i < parametro; i++) {

        ponteiroPosicaoOculto[i] = malloc(sizeof(Neuronio));
        ponteiroPosicaoOculto[i]->d = 0;



        for (size_t j = 0; j < 536; j++) {
          double aux;

          //printf("aux: %lf\n", ponteiroPosicaoOculto[i]->w[j]);
        }


        double aux2;
        aux2 = (rand() % 31999) - 16000;

        ponteiroPosicaoOculto[i]->b = aux2;
        //  printf("aux2: %lf\n", ponteiroPosicaoOculto[i]->b);
        ponteiroPosicaoOculto[i]->v = 0;
    }

    return *ponteiroPosicaoOculto;
}


Neuronio *criarCamadaEntrada(){

    Neuronio **ponteiroPosicaoEntrada;
    ponteiroPosicaoEntrada = malloc(536 * sizeof(Neuronio*));

    for (int i = 0; i < 536; i++) {

        ponteiroPosicaoEntrada[i] = malloc(sizeof(Neuronio));
        ponteiroPosicaoEntrada[i]->d = 0;

        double aux;
        aux = (rand() % 31999) - 16000;
        ponteiroPosicaoEntrada[i]->b = aux;
        ponteiroPosicaoEntrada[i]->v = 0;
 
    }

    return *ponteiroPosicaoEntrada;
}


double **criarMatriz_W_Entrada(){
    //double **matrizTeste = (double **)malloc(50*sizeof(double));
    double  **matriz_W_Entrada = (double **)malloc(536*sizeof(double));
    
    for(int i=0; i<536; i++){


        //matrizTeste[i] = (double *)malloc(536*sizeof(double));
        matriz_W_Entrada[i] = (double *)malloc(536*sizeof(double));
        
        for(int j=0; j<536; j++){
            double aux;
            aux = (rand() % 31999) - 16000;

            matriz_W_Entrada[i][j] = aux;
        }
    }

    return matriz_W_Entrada;
}

double **criarMatriz_W_Oculto(int parametro){
    //double **matrizTeste = (double **)malloc(50*sizeof(double));
    double  **matriz_W_Oculto = (double **)malloc(parametro*sizeof(double));
    
    for(int i=0; i<parametro; i++){

        matriz_W_Oculto[i] = (double *)malloc(536*sizeof(double));
        
        for(int j=0; j<536; j++){
            double aux;
            aux = (rand() % 31999) - 16000;

            matriz_W_Oculto[i][j] = aux;
        }
    }

    return matriz_W_Oculto;

}

void criarNeuronioSaida(int tamanho){
    double d = 0;
    double w[tamanho];
    double b = 0;
    double v = 0;
}

double calculoEntrada(int i, double **matriz, Neuronio *ponteiroPosicao, double **vetorEntradaW){

    double somatorio = 0;
    double aux = 0;

    double v;
    printf("i: %d\n\n", i);
    for(int j=0; j<536;j++){
        //printf("                            vetorEntradaW: %lf\n", vetorEntradaW[i][j]);
        //printf("matriz %lf\n", matriz[i][j]);
        somatorio += vetorEntradaW[i][j] * (matriz[1][j]);
    }

    aux =  somatorio + ponteiroPosicao[i].b;
    ponteiroPosicao[i].v = 1/(1 + exp(-aux));
    
    v = ponteiroPosicao[i].v;
    //printf("%lf\n", v);

    return v;
}





//void RedeneuralTreinamento(int *VetorStatusTreinamento,int *VetorStatusTreinamento,double **matrizTreinamento,double **matrizTeste,int parametro){
//
//}


/* void liberacamada2(int *parametro){
  for (size_t i = 0; i < *parametro; i++){
    free ponteiroPosicaoOculto[i];
  }
  free ponteiroPosicaoOculto;
} */
