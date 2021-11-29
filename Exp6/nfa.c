// Program to find epsilon closure of a given NFA

#include <stdio.h>
#include <string.h>

char result[20][20], copy[3], states[20][20];

void add_state(char a[3], int i) {
    strcpy(result[i], a);
}

void display(int n) {
    int k = 0;
    printf("\n Epsilon closure of %s = { ", copy);
    while (k < n) {
        printf(" %s", result[k]);
        k++;
    }
    printf(" } \n");
}

void non_epsilon_nfa(char state[3], char epsilon_tran[3]) {
    int k = 0, end;
    FILE* INPUT = fopen("input.dat", "r");
    char state1[3], input[3], state2[3];
    printf("%s Transitions\n", state);

    // Self
    while(1){
        end = fscanf(INPUT, "%s%s%s", state1, input, state2);
        if (end == EOF) break;
        if (strcmp(state, state1) == 0 && strcmp(input, "e") != 0) {
            printf("%s %s %s \n", state1, input, state2);
        }
    }

    rewind(INPUT);

    // To Others
    while(1){
        end = fscanf(INPUT, "%s%s%s", state1, input, state2);
        if (end == EOF) break;
        if (strcmp(epsilon_tran, state1) == 0 && strcmp(state, state1) != 0 && strcmp(input, "e") != 0) {
            printf("%s %s %s \n", state, input, state2);
        }
    }


    
}

int main() {
    FILE *INPUT;
    INPUT = fopen("input.dat", "r");
    char state[3];
    int end, i = 0, n, k = 0;
    char state1[3], input[3], state2[3];
    printf("\nEnter the no of states: ");
    scanf("%d", &n);
    printf("\nEnter the states: \n");
    for (k = 0; k < n; k++) {
        scanf("%s", states[k]);
    }

    for (k = 0; k < n; k++) {
        i = 0;
        strcpy(state, states[k]);
        strcpy(copy, state);
        add_state(state, i++);
        while (1) {
            end = fscanf(INPUT, "%s%s%s", state1, input, state2);
            if (end == EOF) {
                break;
            }

            if (strcmp(state, state1) == 0) {
                if (strcmp(input, "e") == 0) {
                    non_epsilon_nfa(state,state2);
                    add_state(state2, i++);
                    strcpy(state, state2);
                }
            }
        }
        // display(i);
        printf("\n");
        rewind(INPUT);
    }

    return 0;
}