//
// Created by Shaotien Lee on 2020/9/10.
//
#include "list.h"

#ifndef ASSIGINMENT2_CODE_KDTREE_H
#define ASSIGINMENT2_CODE_KDTREE_H

typedef struct treeNode {

    char* location;
    double nodeX;
    double nodeY;

    char* name;
    int censusYear;
    int blockId;
    int propertyId;
    int basePropertyId;
    char* clueSmallArea;
    int industryCode;
    char* industryDescription;
    double xCoordinate;
    double yCoordinate;

    char dimension; // 'x' or 'y'
    struct treeNode* parentNode;
    struct node* next;
    struct treeNode* left;
    struct treeNode* right;
} treeNode_t;

typedef treeNode_t* treeNode_ptr;
#endif //ASSIGINMENT2_CODE_KDTREE_H
