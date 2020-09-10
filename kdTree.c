//
// Created by Shaotien Lee on 2020/9/10.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "kdTree.h"
#include "list.h"
#include "pointFunctions.h"
#include "dictFunctions.h"

#define MAXLENGTH 512

/** 绝对不要直接传入字典头节点！！！！ */
node_ptr creatTreeNodes(treeNode_ptr parent, node_ptr dict) {

    if (parent == NULL) {
        parent = (treeNode_ptr) calloc(1, sizeof(treeNode_t));
        double midX = findMedianX(dict); // find median x
        node_ptr p_dict_midPoint = NULL;
        p_dict_midPoint = searchByX(dict, midX);

        parent->location = copyString(p_dict_midPoint->location);
        parent->nodeX = getXCoordinate(p_dict_midPoint->location);
        parent->nodeY = getYCoordinate(p_dict_midPoint->location);
        parent->name = copyString(p_dict_midPoint->key);
        parent->censusYear = p_dict_midPoint->censusYear;
        parent->blockId = p_dict_midPoint->blockId;
        parent->propertyId = p_dict_midPoint->propertyId;
        parent->basePropertyId = p_dict_midPoint->basePropertyId;
        parent->clueSmallArea = p_dict_midPoint->clueSmallArea;
        parent->industryCode = p_dict_midPoint->industryCode;
        parent->industryDescription = copyString(p_dict_midPoint->industryDescription);
        parent->xCoordinate = p_dict_midPoint->xCoordinate;
        parent->yCoordinate = p_dict_midPoint->yCoordinate;

        parent->dimension = 'x';
        parent->parentNode = NULL;
        parent->next = NULL;
        parent->left = NULL;
        parent->right = NULL;

        free(p_dict_midPoint);


    } else if (parent->dimension == 'x' &&
                getXCoordinate(dict->location) < parent->nodeX &&
                getYCoordinate(dict->location) != parent->nodeY) {

        dict = dict->next;
        parent->left = creatTreeNodes(parent->left, dict);

    } else if (parent->dimension == 'x' &&
               getXCoordinate(dict->location) >= parent->nodeX &&
               getYCoordinate(dict->location) != parent->nodeY) {

        dict = dict->next;
        parent->right = creatTreeNodes(parent->right, dict);

    } else if (parent->dimension == 'y' &&
               getXCoordinate(dict->location) != parent->nodeX &&
               getYCoordinate(dict->location) < parent->nodeY) {

        dict = dict->next;
        parent->left = creatTreeNodes(parent->left, dict);

    } else if (parent->dimension == 'y' &&
              getXCoordinate(dict->location) != parent->nodeX &&
              getYCoordinate(dict->location) >= parent->nodeY) {

        dict = dict->next;
        parent->right = creatTreeNodes(parent->right, dict);

    } else if (getXCoordinate(dict->location) == parent->nodeX &&
              getYCoordinate(dict->location) == parent->nodeY) {

        dict = dict->next;
        parent->right = creatTreeNodes(parent->right, dict);

    }


}
