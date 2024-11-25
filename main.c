#include <stdlib.h>
#include <stdio.h>

// Declare dynamic arrays/vectors and global variables
int numResources = 0;
int numProcesses = 0;
int* resource;
int* available;
int** maxclaim;
int** allocated;
int** need;
char* titles[] = {"Resources", "Available", "Max Claim", "Allocated", "Need"};

void prtVector(int *vector, char *title) {
    printf("\n%s: \n", title);
    printf("\t");
    for(int i = 0; i < numResources; i++) {
        printf("r%d\t", i);
    }
    printf("\n\t");
    for(int i = 0; i < numResources; i++) {
        printf("%d\t", vector[i]);
    }
    printf("\n");
    return;
}

void prtMatrix(int **matrix, char *title) {
    printf("\n%s: \n", title);
    printf("\t");
    for(int i = 0; i < numResources; i++) {
        printf("r%d\t", i);
    }
    printf("\n");
    for(int i = 0; i < numProcesses; i++) {
        printf("p%d\t", i);
        for(int j = 0; j < numResources; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

// TODO: Finish up option 1
void enterGraph() {
    printf("Enter number of resources: ");
    scanf("%d", &numResources);
    while (getchar() != '\n');
    
    resource = (int*)malloc(numResources * sizeof(int));
    available = (int*)malloc(numResources * sizeof(int));

    printf("Enter number of units for resources (r%d to r%d): ", 0, numResources-1);
    for(int i = 0; i < numResources; i++) {
        scanf("%d", &resource[i]);
        available[i] = resource[i];
    }
    while (getchar() != '\n');
    
    printf("Enter number of processes: ");
    scanf("%d", &numProcesses);
    while (getchar() != '\n');

    maxclaim = (int**)malloc(numProcesses * sizeof(int*));
    allocated = (int**)malloc(numProcesses * sizeof(int*));
    need = (int**)malloc(numProcesses * sizeof(int*));
    for (int i = 0; i < numProcesses; i++) {
        maxclaim[i] = (int*)malloc(numResources * sizeof(int));
        allocated[i] = (int*)malloc(numResources * sizeof(int));
        need[i] = (int*)malloc(numResources * sizeof(int));
    }

    for(int i = 0; i < numProcesses; i++) {
        printf("Enter max num of units process p%d will claim from each resource (r%d to r%d): ", i, 0, numResources-1);
        for(int j = 0; j < numResources; j++) {
            scanf("%d", &maxclaim[i][j]);
        }
        while (getchar() != '\n');
    }

    for(int i = 0; i < numProcesses; i++) {
        printf("Enter num of units each resource (r%d to r%d) currently allocated to process p%d: ", 0, numResources-1, i);
        for(int j = 0; j < numResources; j++) {
            scanf("%d", &allocated[i][j]);
        }
        while (getchar() != '\n');
    }

    for(int i = 0; i < numProcesses; i++) {
        for(int j = 0; j < numResources; j++) {
            available[j] -= allocated[i][j];
            need[i][j] = maxclaim[i][j] - allocated[i][j];
        }
    }

    prtVector(resource, titles[0]);
    prtVector(available, titles[1]);
    prtMatrix(maxclaim, titles[2]);
    prtMatrix(allocated, titles[3]);
    prtMatrix(need, titles[4]);
    return;
}

int main(void)
{
    int choice;
    do
    {
        printf("\n\nBanker's Algorithm\n");
        printf("------------------");
        printf("\n1) Enter claim graph");
        printf("\n2) Request resource");
        printf("\n3) Release resource");
        printf("\n4) Determine safe sequence");
        printf("\n5) Quit program\n");
        printf("\nEnter selection: ");
        scanf("%d", &choice);
        while (getchar() != '\n');
        switch (choice) {
            case 1:
                enterGraph();
                break;
            case 2:
                printf("\nRequest resource");
                break;
            case 3:
                printf("\nRelease resource");
                break;
            case 4:
                printf("\nDetermine safe sequence");
                break;
            case 5:
                printf("\nQuitting program");
                break;
            default:
                printf("\nINVALID Input, try again");
                break;
        }
    } while (choice != 5);
    
    return 0;
}
