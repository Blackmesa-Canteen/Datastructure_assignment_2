/**
 *  Created by Xiaotian Li on 9/10/2020.
 *
 *  This program is a simple dictionary based on a linked list to store information from
 *  the City of Melbourne Census of Land Use and Employment (CLUE). A user can search this
 *  dictionary to retrieve information about businesses in Melbourne using the business name.
 *
 *  Input:
 *  > This program can take two command line arguments: (1) the name of the source file (.csv
 *    file stores CLUE data), and (2) the name of an output file. When the program is running,
 *    a user could input one business name (key) from the screen at a time. The program keeps
 *    asking the user to enter key values until 'quit!' is typed.
 *  > This program can also take four command line arguments: (1) the name of the source file
 *    (the .csv file stores CLUE data), (2) the name of an output file, (3)  the word "from",
 *    and (4) the name of the key file. The key file should contain keys to be searched, one
 *    per line.
 *  > Users can also use the UNIX operator < to redirect input from a file that has keys to
 *    be searched, one per line.
 *
 *  Output:
 *  program will look up each key and output the matched record to the output file specified by
 *  the second command line parameter. If the key is not found, NOT FOUND would be output.
 *
 *  Input Example 1:                Input Example 2:
 *  ~$ ./dict test.csv out.txt      ~$ ./dict test.csv out < keyfile
 *  ~$ Vacant
 *  ~$ Hello, world                 Input Example3:
 *     ...                          ~$ ./dict test.csv out.txt from keyfile
 *  ~$ quit!
 */

#include <stdio.h>
#include <string.h>

#include "list.h"
#include "pointFunctions.h"
#include "kdTree.h"

int main(int argc, char  **argv) {

    char* inputFileName = NULL;
    char* outputFileName = NULL;
    char* keyFileName = NULL;
    int inputMethod = 0;

    if (argc == 3) {
        inputFileName = argv[1];
        outputFileName = argv[2];
        inputMethod = 1;
    }
    else if (argc == 5 && !strcmp(argv[3], "from")){
        inputFileName = argv[1];
        outputFileName = argv[2];
        keyFileName = argv[4];
        inputMethod = 2;
    } else {
        printf("ERROR: parameters!\n");
        return -1;
    }

    /* Open the input file with the given filename for reading */
    FILE *fp = fopen(inputFileName, "r");
    if (!fp) {
        printf("can't opening file '%s'\n", inputFileName);
        return -1;
    }

    /* creat link List that contains data */
    node_ptr dictList = creatNodes(fp);
    fclose(fp);

    /* creat output file */
//    fp = fopen(outputFileName, "w");
//    if (!fp) {
//        printf("can't create file '%s'\n", outputFileName);
//        return -1;
//    }
//
//    if (inputMethod == 2) {
//        searchByKeyFile(dictList, fp, keyFileName);
//    } else {
//        searchByStdin(dictList, fp);
//    }

    treeNode_ptr p_root = deployKdTree(dictList);
    freeList(dictList);
    fclose(fp);
    printf("\n*********Thank you for using. *********\n");
    fflush(stdout);

    return 0;
}
