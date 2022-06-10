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
    //fprintf(writeFile,"%s\n",argv[0]);
    //fprintf(writeFile,"%s\n",argv[1]);
    //fprintf(writeFile,"%s\n",argv[2]);
    readFile = fopen(argv[1],"r");
    writeFile= fopen(argv[2],"w");

    char buff[255];
    int numStudents, numGrades;
    fscanf(readFile, "%s", buff);
    numStudents = atoi(buff);
    fscanf(readFile, "%s", buff);
    numGrades = atoi(buff);
    //fprintf(writeFile,"%d %d \n", numStudents, numGrades);

    studentData studentList[numStudents];
    for (int i = 0; i < numStudents; i++) {
        studentList[i].grades = calloc(numGrades ,sizeof(int));
    }
    //fprintf(writeFile,"calloced\n");
    int numReads = 0;
    char* newBuff = NULL;
    size_t newBuffSize = 50;
    while (getline(&newBuff, &newBuffSize, readFile)) {
        //fprintf(writeFile,"Got line \n");
        if (newBuff[0] != '\n') {
            char* token = strtok(newBuff, " ");
            studentList[numReads].firstName = strdup(token);

            token = strtok(NULL, " ");
            studentList[numReads].lastName = strdup(token);

            //fprintf(writeFile,"%s %s\n",studentList[numReads].firstName, studentList[numReads].lastName);
            //fprintf(writeFile,"%s %s\n",studentList[0].firstName, studentList[0].lastName);

            token = strtok(NULL, " ");

            int count = 0;
            while (token != NULL) {
                studentList[numReads].grades[count] = atoi(token);
                //fprintf(writeFile," %d\n", studentList[numReads].grades[count]);
                token = strtok(NULL, " ");
                count++;
            }

            //fprintf(writeFile,"%s\n",newBuff);
            numReads++;
        }
        free(newBuff);
        newBuff = NULL;
        if (numReads == numStudents) break;
    }


    fprintf(writeFile,"Student Scores:\n");
    for (int i = 0; i < numStudents; i++) {
        fprintf(writeFile,"%10s %-10s\t", studentList[i].firstName, studentList[i].lastName);
        for (int j = 0; j < numGrades; j++) {
            fprintf(writeFile,"%3d   ", studentList[i].grades[j]);
        }
        fprintf(writeFile,"\n");
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
    fprintf(writeFile,"Exam Averages:\n");
    for (int i = 0; i < numGrades; i++) {
        fprintf(writeFile,"\tExam %d Average =\t%.1f\n",i, avgExamScore[i]);
    }


    //Compares Student Grades to a crappy ABCDE grade scale and keeps track of the number of ABCDE grades
    int totalLetterGrades[numGrades][5];//Creates an VLA that keeps track of the amount of ABCDE grades for n amount of exams
    for (int i = 0; i < numGrades; i++) {
        for (int j = 0; j < 5; j ++) {
            totalLetterGrades[i][j] = 0;
        }
    }
    fprintf(writeFile,"Student Exam Grades:\n");
    for (int i = 0; i < numStudents; i++) {
        fprintf(writeFile,"%10s %-10s\t", studentList[i].firstName, studentList[i].lastName);
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
            fprintf(writeFile,"%3d(%c)   ", studentList[i].grades[j], letterGrade);
        }
        fprintf(writeFile,"\n");
    }

    fprintf(writeFile,"Exam Grades:\n");
    for (int i = 0; i < numGrades; i++) {
        fprintf(writeFile,"\tExam %2d   %2d(A)   %2d(B)   %2d(C)   %2d(D)   %2d(E)\n",i,totalLetterGrades[i][0],
               totalLetterGrades[i][1], totalLetterGrades[i][2],totalLetterGrades[i][3],totalLetterGrades[i][04]);
    }

    fprintf(writeFile,"Student Final Grades:\n");
    double classAvg = ((double)totalSum)/((double)(numStudents*numGrades));
    for (int i = 0; i < numStudents; i++) {
        fprintf(writeFile,"%10s %-10s\t", studentList[i].firstName, studentList[i].lastName);
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

        fprintf(writeFile,"%.1f(%c)   \n", studentFinalGrade,letterGrade);
    }
    fprintf(writeFile,"Class Average Score = %.1f", classAvg);




    for (int i = 0; i < numStudents; i++) {
        free(studentList[i].firstName);
        free(studentList[i].lastName);
        free(studentList[i].grades);
    }

    return fclose(readFile);// + fclose(writeFile);
}

