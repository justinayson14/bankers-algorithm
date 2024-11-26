#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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

// Option 1
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

// Option 2
void reqResource() {
    int selProc = 0;
    int selRes = 0;
    int numReq = 0;

    printf("Enter requesting process: p");
    scanf("%d", &selProc);
    while(getchar() != '\n');
    printf("Enter requested resource: r");
    scanf("%d", &selRes);
    while(getchar() != '\n');
    printf("Enter num of units process p%d is requesting from resource r%d: ", selProc, selRes);
    scanf("%d", &numReq);
    while(getchar() != '\n');

    if(available[selRes] >= numReq && numReq < need[selProc][selRes]) {
        available[selRes] -= numReq;
        allocated[selProc][selRes] += numReq;
        need[selProc][selRes] -= numReq;

        prtVector(available, titles[1]);
        prtMatrix(allocated, titles[3]);
        prtMatrix(need, titles[4]);
    } else {
        printf("ERROR: Request denied!");
    }
    return;
}

// Option 3
void releaseResource() {
    int selProc = 0;
    int selRes = 0;
    int numRel = 0;

    printf("Enter releasing processor: p");
    scanf("%d", &selProc);
    while(getchar() != '\n');
    printf("Enter released resource: r");
    scanf("%d", &selRes);
    while(getchar() != '\n');
    printf("Enter num of units process p%d is releasing from resource r%d: ", selProc, selRes);
    scanf("%d", &numRel);
    while(getchar() != '\n');

    if(allocated[selProc][selRes] >= numRel) {
        available[selRes] += numRel;
        allocated[selProc][selRes] -= numRel;
        need[selProc][selRes] += numRel;

        prtVector(available, titles[1]);
        prtMatrix(allocated, titles[3]);
        prtMatrix(need, titles[4]);
    } else {
        printf("ERROR: Release denied!");
    }
    return;
}

// Option 4
void determSafeSeq() {
    int* finish = (int*)calloc(numProcesses, sizeof(int));
    int* safeSeq = (int*)malloc(numProcesses * sizeof(int));
    int count = 0;

    while(count < numProcesses) {
        for(int i = 0; i < numProcesses; i++) {
            if(finish[i] == 0) {
                printf("Comparing: < ");
                for(int j = 0; j < numResources; j++) {
                    printf("%d ", need[i][j]);
                }
                printf("> <= < ");
                for(int j = 0; j < numResources; j++) {
                    printf("%d ", available[j]);
                }
                printf("> : ");
                bool isAvail = true;
                for(int j = 0; j < numResources; j++) {
                    if(available[j] < need[i][j]) {
                        printf("Process p%d can't be sequenced\n", i);
                        isAvail = false;
                        break;
                    }
                }
                if(isAvail) {
                    printf("Process p%d can be sequenced\n", i);
                    for(int j = 0; j < numResources; j++)
                        available[j] += allocated[i][j];
                    finish[i] = 1;
                    safeSeq[count] = i;
                    count++;
                }
            }
        }
        if(count == 0) {
            printf("System is in deadlock!");
            free(finish);
            free(safeSeq);
            return;
        }
    }
    printf("Safe sequence of processes:");
    for(int i = 0; i < numProcesses; i++) 
        printf("p%d ", safeSeq[i]);
    free(finish);
    free(safeSeq);
    return;
}

// Option 5
void quitProgram() {
    printf("Quitting program...");
    if(resource != NULL)
        free(resource);
    if(available != NULL)
        free(available);
    if(maxclaim != NULL) {
        for (int i = 0; i < numProcesses; i++) {
            if (maxclaim[i] != NULL)
                free(maxclaim[i]);
        }
        free(maxclaim);
    }
    if(allocated != NULL) {
        for (int i = 0; i < numProcesses; i++) {
            if (allocated[i] != NULL)
                free(allocated[i]);
        }
        free(allocated);
    }
    if(need != NULL) {
        for (int i = 0; i < numProcesses; i++) {
            if (need[i] != NULL)
                free(need[i]);
        }
        free(need);
    }
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
                reqResource();
                break;
            case 3:
                releaseResource();
                break;
            case 4:
                determSafeSeq();
                break;
            case 5:
                quitProgram();
                break;
            default:
                printf("\nINVALID Input, try again");
                break;
        }
    } while (choice != 5);
    return 0;
}
