//
// Created by Shaotien Lee on 2020/9/11.
//
#include <stdio.h>
#include <math.h>

#include "kdTree.h"
#include "pointFunctions.h"
#include "dictFunctions.h"

#ifndef ASSIGINMENT2_CODE_FINDCLOSEST_H
#define ASSIGINMENT2_CODE_FINDCLOSEST_H
double getX(char* buffer);
double getY(char* buffer);
double distanceCalc(treeNode_ptr p_node, treeNode_ptr p_target);
//double distanceCalc(treeNode_ptr p_node, double targetX, double targetY);
void countCompare(int *compareCounter);
void nearest(treeNode_ptr p_root, treeNode_ptr p_target,
             treeNode_ptr* p_best, double *best_D, int *compareCounter);
void searchClosest(treeNode_ptr root, FILE *outfile);
#endif //ASSIGINMENT2_CODE_FINDCLOSEST_H
