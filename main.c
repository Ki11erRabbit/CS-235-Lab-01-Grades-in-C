#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* firstName;
    char* lastName;
    int* grades;
} studentData;


int main(int argc, char** argv) {

    FILE* readFile;
    FILE* writeFile;
    if (argc < 2) {
        exit(1);
    }
    //printf("%s\n",argv[0]);
    //printf("%s\n",argv[1]);
    //printf("%s\n",argv[2]);
    readFile = fopen(argv[1],"r");
    writeFile= fopen(argv[2],"w");

    char buff[255];
    int numStudents, numGrades;
    fscanf(readFile, "%s", buff);
    numStudents = atoi(buff);
    fscanf(readFile, "%s", buff);
    numGrades = atoi(buff);
    //printf("%d %d \n", numStudents, numGrades);

    studentData studentList[numStudents];
    for (int i = 0; i < numStudents; i++) {
        studentList[i].grades = calloc(numGrades ,sizeof(int));
    }
    int numReads = 0;
    char* newBuff;
    size_t newBuffSize = 50;
    while (getline(&newBuff, &newBuffSize, readFile)) {

        if (newBuff[0] != '\n') {
            char* token = strtok(newBuff, " ");
            studentList[numReads].firstName = strdup(token);

            token = strtok(NULL, " ");
            studentList[numReads].lastName = strdup(token);

            //printf("%s %s\n",studentList[numReads].firstName, studentList[numReads].lastName);
            //printf("%s %s\n",studentList[0].firstName, studentList[0].lastName);

            token = strtok(NULL, " ");

            int count = 0;
            while (token != NULL) {
                studentList[numReads].grades[count] = atoi(token);
                //printf(" %d\n", studentList[numReads].grades[count]);
                token = strtok(NULL, " ");
                count++;
            }

            //printf("%s\n",newBuff);
            numReads++;
        }
        if (numReads == numStudents) break;
    }
    free(newBuff);

    printf("Student Scores:\n");
    for (int i = 0; i < numStudents; i++) {
        printf("%10s %-10s\t", studentList[i].firstName, studentList[i].lastName);
        for (int j = 0; j < numGrades; j++) {
            printf("%3d   ", studentList[i].grades[j]);
        }
        printf("\n");
    }

    //Averages Exams
    double avgExamScore[numGrades];
    int totalSum = 0; // is used much later
    for (int i = 0; i < numGrades; i++) {
        int sum = 0;
        for (int j = 0; j < numStudents; j++) {
            sum += studentList[j].grades[i];
            totalSum += studentList[j].grades[i];
        }
        avgExamScore[i] = ((double)sum)/((double)numStudents);
    }
    printf("Exam Averages:\n");
    for (int i = 0; i < numGrades; i++) {
        printf ("\tExam %d Average =\t%.1f\n",i, avgExamScore[i]);
    }


    //Compares Student Grades to a crappy ABCDE grade scale and keeps track of the number of ABCDE grades
    int totalLetterGrades[numGrades][5];
    for (int i = 0; i < numGrades; i++) {
        for (int j = 0; j < 5; j ++) {
            totalLetterGrades[i][j] = 0;
        }
    }
    printf("Student Exam Grades:\n");
    for (int i = 0; i < numStudents; i++) {
        printf("%10s %-10s\t", studentList[i].firstName, studentList[i].lastName);
        for (int j = 0; j < numGrades; j++) {
            char letterGrade = ' ';
            if (studentList[i].grades[j] > avgExamScore[j]) {
                if (studentList[i].grades[j] - avgExamScore[j] < 15 && studentList[i].grades[j] - avgExamScore[j] > 5) {
                    letterGrade = 'B';
                    totalLetterGrades[j][1] += 1;
                }
                else if (studentList[i].grades[j] - avgExamScore[j] >= 15) {
                    letterGrade = 'A';
                    totalLetterGrades[j][0] += 1;
                }
                else if (studentList[i].grades[j] - avgExamScore[j] <= 5) {
                    letterGrade = 'C';
                    totalLetterGrades[j][2] += 1;
                }
            }
            else {
                if (avgExamScore[j] - studentList[i].grades[j] < 15 && avgExamScore[j] - studentList[i].grades[j] > 5) {
                    letterGrade = 'D';
                    totalLetterGrades[j][3] += 1;
                }
                else if (avgExamScore[j] - studentList[i].grades[j] >= 15) {
                    letterGrade = 'E';
                    totalLetterGrades[j][4] += 1;
                }
                else if (avgExamScore[j] - studentList[i].grades[j] <= 5) {
                    letterGrade = 'C';
                    totalLetterGrades[j][2] += 1;
                }
                else {
                    letterGrade = 'D';
                    totalLetterGrades[j][3] += 1;
                }
            }
            printf("%3d(%c)   ", studentList[i].grades[j], letterGrade);
        }
        printf("\n");
    }

    printf("Exam Grades:\n");
    for (int i = 0; i < numGrades; i++) {
        printf("\tExam %2d   %2d(A)   %2d(B)   %2d(C)   %2d(D)   %2d(E)\n",i,totalLetterGrades[i][0],
               totalLetterGrades[i][1], totalLetterGrades[i][2],totalLetterGrades[i][3],totalLetterGrades[i][04]);
    }

    printf("Student Final Grades:\n");
    double classAvg = ((double)totalSum)/((double)(numStudents*numGrades));
    for (int i = 0; i < numStudents; i++) {
        printf("%10s %-10s\t", studentList[i].firstName, studentList[i].lastName);
        int sum = 0;
        for (int j = 0; j < numGrades; j++) {
            sum += studentList[i].grades[j];
        }
        double studentFinalGrade = ((double)sum)/(double)numGrades;
        char letterGrade = ' ';
        if (studentFinalGrade > classAvg) {
            if (studentFinalGrade - classAvg < 15 && studentFinalGrade - classAvg > 5) {
                letterGrade = 'B';
            }
            else if (studentFinalGrade - classAvg >= 15) {
                letterGrade = 'A';
            }
            else if (studentFinalGrade - classAvg <= 5) {
                letterGrade = 'C';
            }
        }
        else {
            if (classAvg - studentFinalGrade < 15 && classAvg - studentFinalGrade > 5) {
                letterGrade = 'D';
            }
            else if (classAvg - studentFinalGrade >= 15) {
                letterGrade = 'E';
            }
            else if (classAvg - studentFinalGrade <= 5) {
                letterGrade = 'C';
            }
            else {
                letterGrade = 'D';
            }
        }

        printf("%.1f(%c)   \n", studentFinalGrade,letterGrade);
    }
    printf("Class Average Score = %.1f", classAvg);




    for (int i = 0; i < numStudents; i++) {
        free(studentList[i].firstName);
        free(studentList[i].lastName);
        free(studentList[i].grades);
    }

    return fclose(readFile) + fclose(writeFile);
}

