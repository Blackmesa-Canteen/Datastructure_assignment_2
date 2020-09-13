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

/* get y coordinate from  input */
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

/* calc distance between two tree nodes */
double distanceCalc(treeNode_ptr p_node, treeNode_ptr p_target) {
    double answer = sqrt(pow(p_node->nodeX - p_target->nodeX, 2) +
            pow(p_node->nodeY - p_target->nodeY ,2));

    return answer;
}

/* used to count compares */
void countCompare(int *compareCounter) {

    *compareCounter = *compareCounter + 1;
}

/* find nearest point, p_best will point to it */
void nearest(treeNode_ptr p_root, treeNode_ptr p_target,
            treeNode_ptr* p_best, double *best_D, int *compareCounter)
{
    double d, dMQ;

    countCompare(compareCounter);
    if (p_root == NULL) return; // found potential nearest point
    d = distanceCalc(p_root, p_target);
    if(p_root->dimension == 'x') {
        dMQ = p_root->nodeX - p_target->nodeX;
    } else if (p_root->dimension == 'y') {
        dMQ = p_root->nodeY - p_target->nodeY;
    }

    if (*p_best == NULL || d < *best_D) {
        *best_D = d;
        *p_best = p_root;
    }

    /* if it is the same position */
    if (*best_D == 0) return;
    if (dMQ > 0) {
        nearest(p_root->left, p_target, p_best, best_D, compareCounter);
    } else {
        nearest(p_root->right, p_target, p_best, best_D, compareCounter);
    }

    /* do we need to check the other side? */
    if (pow(dMQ, 2) >= pow((*best_D), 2)) return;
    /* check the other side */
    if (dMQ > 0) {
        nearest(p_root->right, p_target, p_best, best_D, compareCounter);
    } else {
        nearest(p_root->left, p_target, p_best, best_D, compareCounter);
    }
}

void searchClosest(treeNode_ptr root, FILE *outfile) {

    const char quitCommand[] = "quit!";
    char* whatToFind = NULL;
    size_t whatToFindNumber = 0;
    double targetX = 0;
    double targetY = 0;
    treeNode_ptr p_root = NULL;
    treeNode_ptr p_target = NULL;
    treeNode_ptr p_best = NULL;
    double bestD;
    int compareCounter;

    while(1) {
        fflush(stdin);
        if (getline(&whatToFind, &whatToFindNumber, stdin) == EOF) {
            /* detect ending of stdin if users use < operator in bash */
            break;
        }
        trimLastEnter(whatToFind); /* trim '\n' at the end of the string */
        if (!strcmp(quitCommand, whatToFind)) {
            break;
        }

        targetX = getX(whatToFind);
        targetY = getY(whatToFind);
        free(whatToFind);
        whatToFind = NULL;

        p_root = root;
        p_target = (treeNode_ptr) calloc(1, sizeof(treeNode_t));
        p_target->nodeX = targetX;
        p_target->nodeY = targetY;
        compareCounter = 0;
        nearest(p_root, p_target, &p_best, &bestD, &compareCounter);
        /* output compare times through stdout */
        printf("%.9g %.9g --> %d\n", targetX, targetY, compareCounter);

        while(p_best != NULL) {
            fprintf(outfile,"%.9g %.9g --> ", targetX, targetY);
            fprintf(outfile, "Census year: %d || ", p_best -> censusYear);
            fprintf(outfile, "Block ID: %d || ", p_best -> blockId);
            fprintf(outfile, "Property ID: %d || ", p_best -> propertyId);
            fprintf(outfile, "Base property ID: %d || ", p_best -> basePropertyId);
            fprintf(outfile, "CLUE small area: %s || ", p_best -> clueSmallArea);
            fprintf(outfile, "Industry (ANZSIC4) code: %d || ", p_best -> industryCode);
            fprintf(outfile, "Industry (ANZSIC4) description: %s || ", p_best -> industryDescription);
            fprintf(outfile, "x coordinate: %.5f || ", p_best -> xCoordinate);
            fprintf(outfile, "y coordinate: %.5f || ", p_best -> yCoordinate);
            fprintf(outfile, "Location: %s || \n", p_best -> location);

            p_best = p_best->next;
        }
        free(p_target);

    }
    free(whatToFind);
}

