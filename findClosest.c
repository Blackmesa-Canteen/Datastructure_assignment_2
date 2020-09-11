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

//treeNode_ptr searchPotentialClose(treeNode_ptr p_tree, treeNode_ptr ancestor,
//                          FILE *outfile, double targetX, double targetY) {
//    treeNode_ptr nearest = NULL;
//    double D = 0;
//
//    if (p_tree == NULL) {
//        nearest = ancestor;
//
//    } else if (p_tree->dimension == 'x' && targetX < p_tree->nodeX) {
//        nearest = searchPotentialClose(p_tree->left, p_tree,
//                outfile, targetX, targetY);
//    } else if (p_tree->dimension == 'x' && targetX > p_tree->nodeX) {
//        nearest = searchPotentialClose(p_tree->right, p_tree,
//                             outfile, targetX, targetY);
//    } else if (p_tree->dimension == 'x' && targetX == p_tree->nodeX &&
//                targetY != p_tree->nodeY) {
//        nearest = searchPotentialClose(p_tree->right, p_tree,
//                                       outfile, targetX, targetY);
//    } else if (p_tree->dimension == 'y' && targetY < p_tree->nodeY) {
//        nearest = searchPotentialClose(p_tree->left, p_tree,
//                                       outfile, targetX, targetY);
//    } else if (p_tree->dimension == 'y' && targetY > p_tree->nodeY) {
//        nearest = searchPotentialClose(p_tree->right, p_tree,
//                                       outfile, targetX, targetY);
//    } else if (p_tree->dimension == 'y' && targetY == p_tree->nodeY &&
//               targetX != p_tree->nodeX) {
//        nearest = searchPotentialClose(p_tree->right, p_tree,
//                                       outfile, targetX, targetY);
//    } else if (targetY == p_tree->nodeY && targetX == p_tree->nodeX) {
//        nearest = p_tree;
//    }
//
//    return nearest;
//}

/* used to count compares */
void countCompare(int *compareCounter) {
    int a;
    a = *compareCounter;
    free(compareCounter);
    compareCounter = NULL;
    a += 1;
    compareCounter = &a;
}

/* find nearest point, p_best will point to it */
void nearest(treeNode_ptr p_root, treeNode_ptr p_target,
            treeNode_ptr p_best, double *best_D, int *compareCounter)
{
    double d, dMQ, dMQ2;

    if (p_root == NULL) return;
    d = distanceCalc(p_root, p_target);
    if(p_root->dimension == 'x') {
        dMQ = p_root->nodeX - p_target->nodeX;
        dMQ2 = pow(dMQ, 2);
    } else if (p_root->dimension == 'y') {
        dMQ = p_root->nodeY - p_target->nodeY;
        dMQ2 = pow(dMQ, 2);
    }

    if (p_best == NULL || d < *best_D) {
        *best_D = d;
        p_best = p_root;
    }

    /* if it is the same position */
    if (*best_D == 0) return;
    if (dMQ > 0) {
        nearest(p_root->left, p_target, p_best, best_D, compareCounter);
        countCompare(compareCounter);
    } else {
        nearest(p_root->right, p_target, p_best, best_D, compareCounter);
        countCompare(compareCounter);
    }

    if (dMQ2 >= pow((*best_D), 2)) return; // if the circle is bigger than distance MQ
    nearest(dMQ > 0 ? p_root->right : p_root->left, p_target, p_best, best_D, compareCounter);
    countCompare(compareCounter);
}

void searchClosest(treeNode_ptr root, FILE *outfile) {

    const char quitCommand[] = "quit!";
    char* whatToFind = NULL;
    size_t whatToFindNumber = 0;
    double targetX = 0;
    double targetY = 0;
    double d = 0;
    treeNode_ptr p_root = NULL;
    treeNode_ptr p_target = NULL;
    treeNode_ptr p_best = NULL;
    double bestD;
    int compareCounter;

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

        p_root = root;
        p_target = (treeNode_ptr) calloc(1, sizeof(treeNode_t));
        p_target->nodeX = targetX;
        p_target->nodeY = targetY;
        compareCounter = 0;
        nearest(p_root, p_target, p_best, &bestD, &compareCounter);

        /* output compare times through stdout */
        printf("%f %f --> %d\n", targetX, targetY, compareCounter);

        //d = distanceCalc(p_close, targetX, targetY);


    }

    free(whatToFind);
}

