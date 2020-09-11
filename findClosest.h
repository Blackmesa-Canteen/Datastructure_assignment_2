//
// Created by Shaotien Lee on 2020/9/11.
//
#include <stdio.h>

#include "kdTree.h"
#include "pointFunctions.h"
#include "dictFunctions.h"

#ifndef ASSIGINMENT2_CODE_FINDCLOSEST_H
#define ASSIGINMENT2_CODE_FINDCLOSEST_H
double getX(char* buffer);
double getY(char* buffer);
double distanceCalc(treeNode_ptr p_node, double targetX, double targetY);
void searchCloseAndOutput(treeNode_ptr root, FILE *outfile, double targetX, double targetY);
void searchClosest(treeNode_ptr root, FILE *outfile);
#endif //ASSIGINMENT2_CODE_FINDCLOSEST_H
