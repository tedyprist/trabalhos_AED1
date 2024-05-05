#include <stdio.h>
#include <stdlib.h>

#define N 9

void lerMatriz(unsigned char matriz[][N]){
    unsigned char i, j;
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            scanf("%hhu", &matriz[i][j]);
        }
    }
}

void eliminarCelulas(unsigned char matriz[][N], unsigned char numCelulasEliminadas, unsigned seed){
   srand(seed);
   unsigned int i, j;
   for (int x=0; x < numCelulasEliminadas; x++){
        i = rand() % N;
        j = rand() % N;
        if(matriz[i][j] != 0){
            matriz[i][j] = 0;
		}
        else{
            x -= 1;
        }
        /*
            Se as coordenadas (i, j) se repetirem em todas as iterações do loop teu programa vai eliminar só uma célula
            por exemplo, se a quantidade de celulas eliminadas fosse 3 e nas 3 iterações a coordenada (1, 3) fosse gerada tu ia 
            eliminar só a célula da coordenada (1, 3) e sairia do loop
        */
    }
}
void imprimirMatriz(unsigned char matriz[][N]){
    unsigned char i, j;
    
    printf("-------------------------\n");
    for(i = 0; i < N; i++){
        printf("| ");
        for(j = 0; j < N; j++){
            if(matriz[i][j] == 0)
                printf("_ ");
            else if(matriz[i][j] < 10)
                printf("%hhu ", matriz[i][j]);
            else
                printf("%hhu ", matriz[i][j] - 9);
            if((j+1) % 3 == 0)
                printf("| ");
            
        }
        if((i+1) % 3 == 0)
                printf("\n-------------------------");
        printf("\n");
    }
}

char preencherCelula(unsigned char matriz[][N], unsigned char x, unsigned char y, unsigned char valor){
    if((matriz[x][y] == 0) && (0 <= x && x <= 8) && (0 <= y && y <= 8) && (0 < valor && valor <= 9)){
        matriz[x][y] = valor + 9;
        return 1;
    }
    else{
        return 0;
    }
}

char verificarLinha(unsigned char matriz[][N], unsigned char x, unsigned char y){
    int somatorio = 0;
    for(int j=0; j < N; j++){
        if(matriz[x][j] > 9){
            matriz[x][j] = matriz[x][j] - 9;
        }
        somatorio += matriz[x][j];
    }
    if(somatorio == 45){
        return 1;
    }
    else{
        return 0;
    }
}

char verificarColuna(unsigned char matriz[][N], unsigned char x, unsigned char y){
    int somatorio = 0;
    for(int i=0; i < N; i++){
        if(matriz[i][y] > 9){
            matriz[i][y] = matriz[i][y] - 9;
        }
        somatorio += matriz[i][y];
    }
    if(somatorio == 45){
        return 1;
    }
    else{
        return 0;
    }
}

char verificarBloco(unsigned char matriz[][N], unsigned char x, unsigned char y){
    int somatorio = 0;
    int blocox = (x/3)*3;
    int blocoy = (y/3)*3;
    for(int i=blocox; i < blocox + 3; i++){
        for(int j=blocoy; j < blocoy + 3; j++){
            if(matriz[i][j] > 9){
                matriz[i][j] = matriz[i][j] - 9;
            }
            somatorio += matriz[i][j];
        }
    }
    if(somatorio == 45){
        return 1;
    }
    else{
        return 0;
    }
}

/*
Deveria retorna 1 caso a jogada fosse inválida e 0 caso contrário
*/
char jogadaInvalida(unsigned char matriz[][N], unsigned char x, unsigned char y){

    if(verificarLinha(matriz, x, y) && verificarColuna(matriz, x, y) && verificarBloco(matriz, x, y)){
        return 0;
    }
    else{
        return 1;
    }
}

char ganhouJogo(unsigned char matriz[][N]){
    for (int x = 0; x < N; x++){
        for (int y = 0; y < N; y++){
            if (matriz[x][y] > 9 ){
                if(jogadaInvalida(matriz, x, y)){
                    return 0;
                }
            }
        }
    }
    return 1;
}

int main(){
    unsigned seed;
    unsigned char numCelulasEliminadas, x, y, valor; 
    unsigned char matriz[N][N];
    lerMatriz(matriz);
    scanf("%u %hhu", &seed, &numCelulasEliminadas);
    eliminarCelulas(matriz, numCelulasEliminadas, seed);
    imprimirMatriz(matriz);
    for(int i=0; i < numCelulasEliminadas; i++){

        scanf("%hhu %hhu %hhu", &x, &y, &valor);
        setbuf(stdout, NULL);

        if(preencherCelula(matriz, x, y, valor)){
            ;
        }
        else{
            printf("Jogada invalida\n");
            i -=1;
        }
        imprimirMatriz(matriz);
    }
    /*
    Tu ta imprimindo a matriz uma vez a mais do que deveria aqui
    */
    //imprimirMatriz(matriz);

    if(ganhouJogo(matriz)){
        printf("Parabens voce ganhou\n");
    }
    else{
        printf("Voce perdeu\n");
    }
    return 0;
}
