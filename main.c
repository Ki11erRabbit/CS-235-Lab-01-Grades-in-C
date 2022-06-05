#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* firstName;
    char* lastName;
    int* grades[];
} studentData;

int main(int argc, char** argv) {

    FILE* readFile;
    FILE* writeFile;
    if (argc < 2) {
        exit(1);
    }
    printf("%s\n",argv[1]);
    printf("%s\n",argv[2]);
    readFile = fopen(argv[1],"r");
    writeFile= fopen(argv[2],"w");

    char buff[255];
    int numStudents, numGrades;
    fscanf(readFile, "%s", buff);
    numStudents = atoi(buff);
    fscanf(readFile, "%s", buff);
    numGrades = atoi(buff);
    printf("%d %d \n", numStudents, numGrades);

    studentData studentList[numStudents];
    for (int i = 0; i < numStudents; i++) {
        *studentList[i].grades = calloc(numGrades, sizeof(int));
    }
    int numReads = 0;
    char* newBuff;
    size_t newBuffSize = 50;
    while (getline(&newBuff, &newBuffSize, readFile)) {//fgets(readFile, 255, buff)) {

        if (newBuff[0] != '\n') {
            char* token = strtok(newBuff, " ");
            studentList[numReads].firstName = calloc(sizeof(*token),sizeof(char));
            strcpy(studentList[numReads].firstName, token);
            printf("%s\n", studentList[numReads].firstName);
            token = strtok(NULL, " ");

            studentList[numReads].lastName = calloc(sizeof(*token),sizeof(char));
            strcpy(studentList[numReads].lastName, token);
            printf("%s\n", studentList[numReads].lastName);
            token = strtok(NULL, " ");
            int count = 0;
            while (token != NULL) {
                studentList[numReads].grades[count] = atoi(token);
                printf(" %s\n", token);
                token = strtok(NULL, " ");
            }
            //printf("%s\n",newBuff);


        }


        numReads++;
        if (numReads == numStudents +1) break;
    }



    printf("Hello, World!\n");

    for (int i = 0; i < numStudents; i++) {
        //free(studentList[i].firstName);
        //free(studentList[i].lastName);
        free(*studentList[i].grades);
    }

    return fclose(readFile) + fclose(writeFile);
    return 0;
}
