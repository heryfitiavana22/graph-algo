#include <stdio.h>

#define MAX_SIZE 6
#define MAX_INT 2147483647

typedef int Matrice[MAX_SIZE][MAX_SIZE];
typedef int Tab[MAX_SIZE];

Matrice g;
Tab sbarre, pcc;
int n;

void fillMatrix(Matrice graph, Tab s) {
    int i, j;
    int values[6][6] = {
        {0, 4, 0, 2, 3, 0},
        {3, 0, 3, 8, 2, 0},
        {5, 0, 0, 6, 0, 0},
        {0, 2, 8, 0, 0, 3},
        {0, 0, 2, 0, 1, 15},
        {0, 0, 0, 3, 4, 0}
    };
    for (i = 0; i < MAX_SIZE; i++) {
        for (j = 0; j < MAX_SIZE; j++) {
            graph[i][j] = values[i][j];
        }
        s[i] = i + 1;
    }
}

int getSuccessor(Tab suc, int sommet) {
    int i, count = 0;
    for (i = 0; i < n; i++) {
        if (g[sommet - 1][i] != 0) {
            suc[count] = i + 1;
            count++;
        }
    }
    return count;
}

int getPredecessor(Tab prev, int sommet) {
    int i, count = 0;
    for (i = 0; i < n; i++) {
        if (g[i][sommet - 1] != 0) {
            prev[count] = i + 1;
            count++;
        }
    }
    return count;
}

void initValue(Matrice graph, Tab pcc, Tab s, int origine) {
    int i, j;
    Tab successeur;
    s[origine - 1] = 0;
    getSuccessor(successeur, origine);
    j = 0;
    for (i = 0; i < n; i++) {
        if (i + 1 == successeur[j]) {
            pcc[i] = graph[origine - 1][i];
            j++;
        } else {
            pcc[i] = MAX_INT;
        }
    }
    pcc[origine - 1] = 0;
}

int isSummitEmpty(Tab s) {
    int i;
    for (i = 0; i < n; i++) {
        if (s[i] != 0) {
            return 0;
        }
    }
    return 1;
}

int getIndiceMin(Tab pcc, Tab s) {
    int i, min;
    for (i = 0; i < n; i++) {
        if (s[i] != 0) {
            min = i;
            break;
        }
    }
    for (i = 0; i < n; i++) {
        if (pcc[i] < pcc[min] && s[i] != 0) {
            min = i;
        }
    }
    return min;
}

int isRemoved(Tab s, int sommet) {
    int i;
    for (i = 0; i < n; i++) {
        if (s[i] == sommet) {
            return 0;
        }
    }
    return 1;
}

void searchPCC(Matrice graph, Tab pcc, Tab s, int origine) {
    int i, minSommet, min, nbSuc;
    Tab successeur;
    while (!isSummitEmpty(s)) {
        minSommet = getIndiceMin(pcc, s);
        s[minSommet] = 0;
        nbSuc = getSuccessor(successeur, minSommet + 1);
        for (i = 0; i < nbSuc; i++) {
            if (!isRemoved(s, successeur[i])) {
                if (pcc[successeur[i] - 1] > (pcc[minSommet] + graph[minSommet][successeur[i] - 1])) {
                    min = pcc[minSommet] + graph[minSommet][successeur[i] - 1];
                } else {
                    min = pcc[successeur[i] - 1];
                }
                pcc[successeur[i] - 1] = min;
            }
        }
    }
}

void displayPCC(Tab pcc) {
    int i;
    printf("origine => sommet = pcc \n");
    for (i = 0; i < n; i++) {
        printf("1 => %d = %d \n", i + 1, pcc[i]);
    }
    printf("\n");
}

int main() {
    n = 6;
    fillMatrix(g, sbarre);
    initValue(g, pcc, sbarre, 1);
    searchPCC(g, pcc, sbarre, 1);
    displayPCC(pcc);
    return 0;
}
