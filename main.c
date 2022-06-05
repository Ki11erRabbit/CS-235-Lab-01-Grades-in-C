#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char firstName[30];
    char lastName[30];
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
    while (numReads < numStudents) {//fgets(readFile, 255, buff)) {
        fscanf(readFile, "%[^\n]", buff );
        //strncpy(studentList[numReads].firstName, buff, strcspn(buff, " ") );
        *studentList[numReads].firstName = strtok(buff, " ");
        //strncpy(studentList[numReads].lastName, buff, strcspn(buff, " ") );
        *studentList[numReads].lastName = strtok(buff, " ");
        for (int i = 0; i < numGrades; i++) {
            studentList[numReads].grades[i] = atoi(strtok(buff, " "));
            printf("%d\n", studentList[numReads].grades[i]);
        }
        printf("\n");
        numReads++;
    }



    printf("Hello, World!\n");

    for (int i = 0; i < numStudents; i++) {
        free(*studentList[i].grades);
    }

    return fclose(readFile) + fclose(writeFile);
    return 0;
}
