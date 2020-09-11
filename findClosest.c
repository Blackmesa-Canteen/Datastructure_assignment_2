//
// Created by Shaotien Lee on 2020/9/11.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "kdTree.h"
#include "pointFunctions.h"
#include "dictFunctions.h"
#include "findClosest.h"

int searchCounter = 0;
/* get x coordinate from  input */
double getX(char* buffer) {
    double x = 0;
    char* xStr = NULL;
    int i = 0;
    while(i < strlen(buffer)) {
        if (buffer[i] != ' ') {
            i++;
            continue;
        }
        xStr = cutString(buffer, 0, i);
        break;
    }
    if (xStr != NULL) {
        x = strtod(xStr, NULL);
    }
    free(xStr);

    return x;
}

double getY(char* buffer) {
    double y = 0;
    char* yStr = NULL;
    int start = 0; //start from the number after the space
    int size = 0;
    while(start < strlen(buffer)) {
        if (buffer[start] != ' ') {
            start++;
            continue;
        }
        start++;
        break;
    }
    size = strlen(buffer) - start; // number of chars in Y part
    yStr = (char*) calloc(size + 1, sizeof(char));
    for(int i = 0; i < size; i++) {
        yStr[i] = buffer[start++];
    }
    yStr[size] = '\0';
    y = strtod(yStr, NULL);
    free(yStr);

    return y;
}

double distanceCalc(treeNode_ptr p_node, double targetX, double targetY) {
    double answer = sqrt(pow(p_node->nodeX - targetX, 2) + pow(p_node->nodeY - targetX ,2));

    return answer;
}

void searchCloseAndOutput(treeNode_ptr p_tree, treeNode_ptr ancestor,
                          FILE *outfile, double targetX, double targetY) {

    treeNode_ptr nearest = NULL;
    double distance = 0;

    if (p_tree == NULL) {
        distance = distanceCalc(ancestor, targetX, targetY);
        nearest = ancestor;


    } else if (p_tree->dimension == 'x' && targetX < p_tree->nodeX) {
        searchCloseAndOutput(p_tree->left, p_tree,
                outfile, targetX, targetY);
    } else if (p_tree->dimension == 'x' && targetX > p_tree->nodeX) {
        searchCloseAndOutput(p_tree->right, p_tree,
                             outfile, targetX, targetY);
    }

}

void searchClosest(treeNode_ptr root, FILE *outfile) {

    const char quitCommand[] = "quit!";
    char* whatToFind = NULL;
    size_t whatToFindNumber = 0;
    double targetX = 0;
    double targetY = 0;
    treeNode_ptr p_tree = NULL;

    while(1) {
        fflush(stdin);
        printf("\n$ Please input a business name to "
               "search (input \"quit!\" to stop input): ");
        if (getline(&whatToFind, &whatToFindNumber, stdin) == EOF) {
            /* detect ending of stdin if users use < operator in bash */
            break;
        }
        trimLastEnter(whatToFind); /* trim '\n' at the end of the string */
        if (!strcmp(quitCommand, whatToFind)) {
            printf("\nEnd of searching\n");
            break;
        }
        targetX = getX(whatToFind);
        targetY = getY(whatToFind);
        p_tree = root;
        searchCloseAndOutput(p_tree, NULL, outfile, targetX, targetY);
    }

    free(whatToFind);
}

