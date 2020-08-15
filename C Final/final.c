//Steven Kalis
//Final Exam

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


struct Student
{
	int id;
	char name[20];
	char address[30];	
	char city[20];
	char state[2];
	int zip;
};

struct Grade
{
	int id;
	int assignment;
	int quiz;	
	int test;
	int final;
};

int readStudentsFile(struct Student students[20]);
int readGradesFile(struct Grade grades[20]);
int findStudentDataByName(struct Student students[20],int numOfStudents);
void getStudentGrades(struct Grade grades[20],int numOfGrades,int studentID,int *assignP,int *quizP,int *testP,int *finalP);
void printStudentGradeReport(struct Student students[20],int numOfStudents,int studentID,int assignGrade,int quizGrade,int testGrade,int finalGrade);
int main()
{
	
	int numOfStudents,numOfGrades,studentID,assignGrade,quizGrade,testGrade,finalGrade;
	char question;
	struct Student students[20];
	struct Grade grades[20];
	do
	{
		if(question=='Y')
			getchar();
	numOfStudents = readStudentsFile(students);
	
	numOfGrades = readGradesFile(grades);
	
	studentID = findStudentDataByName(students,numOfStudents);
	
	if(studentID!=0)
	{
	getStudentGrades(grades,numOfGrades,studentID,&assignGrade,&quizGrade,&testGrade,&finalGrade);

	printStudentGradeReport(students,numOfStudents,studentID,assignGrade,quizGrade,testGrade,finalGrade);
	}
	
	do
	{
	
	printf("\n\n\nWould you like to search for another student? Y/N ");
	scanf("%c",&question);
	
	if(question>=97&&question<=122)
		question = question - 32;
		
	if(question!='Y'&&question!='N')
	{
		getchar();
		printf("\nError - Not a valid answer, try again!");
	}
	}while(question!='Y'&&question!='N');
	
	}while(question=='Y');
	
	if(question=='N')
		return 0;
}

int readStudentsFile(struct Student students[20])
{
	int x;
	char *sp,line[100];
	FILE *fp;
	
	x = 0;
	
	fp = fopen("Students.csv","r");
	
	if(fp == NULL)
	{
		printf("Error - Cannot find Students file!");
		exit(0);
	}
	
	while(fgets(line,100,fp)!=NULL)
	{
		sp = strtok(line,",");
		
		students[x].id = atoi(sp);
		
		sp = strtok(NULL,",");
		
		strcpy(students[x].name,sp);
		
		sp = strtok(NULL,",");
		
		strcpy(students[x].address,sp);
		
		sp = strtok(NULL,",");
		
		strcpy(students[x].city,sp);
		
		sp = strtok(NULL,",");
		
		strcpy(students[x].state,sp);
		
		sp = strtok(NULL,",");
		
		students[x].zip = atoi(sp);
		
		x++;
		
	}
	
	return x;
}

int readGradesFile(struct Grade grades[20])
{
	int x;
	char *sp,line[100];
	FILE *fp;
	
	x = 0;
	
	fp = fopen("Grades.csv","r");
	
	if(fp == NULL)
	{
		printf("Error - Cannot find Grades file!");
		exit(0);
	}
	
	while(fgets(line,100,fp)!=NULL)
	{
		sp = strtok(line,",");
		
		grades[x].id = atoi(sp);
		
		sp = strtok(NULL,",");
		
		grades[x].assignment = atoi(sp);
		
		sp = strtok(NULL,",");
		
		grades[x].quiz = atoi(sp);
		
		sp = strtok(NULL,",");
		
		grades[x].test = atoi(sp);
		
		sp = strtok(NULL,",");
		
		grades[x].final = atoi(sp);

		x++;
		
	}
	
	return x;
}

int findStudentDataByName(struct Student students[20],int numOfStudents)
{
	int x,found,studentID;
	found = 0;
	char userInput[20];
	
		printf("\nPlease enter a student name: ");
		gets(userInput);
		
		
		for(x=0;x<numOfStudents;x++)
		{
			if (strcmp(userInput, students[x].name)==0) //means they match
				{
					found = 1;	
					studentID = students[x].id;
					break;
				
				}		
		}	
		
		if(found==1)
			return studentID;
		else
		{
			printf("Student does not exist!");
			return 0;
		}
}

void getStudentGrades(struct Grade grades[20],int numOfGrades,int studentID,int *assignP,int *quizP,int *testP,int *finalP)
{
	int x;
	for(x=0;x<numOfGrades;x++)
	{
		if(studentID == grades[x].id)
		{
			*assignP = grades[x].assignment;
			
			*quizP = grades[x].quiz;
			
			*testP = grades[x].test;
			
			*finalP = grades[x].final;
		}
		
	}
	
	
}

void printStudentGradeReport(struct Student students[20],int numOfStudents,int studentID,int assignGrade,int quizGrade,int testGrade,int finalGrade)
{
	int x,totalGrade;
	char decision,fileName[20];
	FILE *fp;
	totalGrade = assignGrade + quizGrade + testGrade + finalGrade; 
	
	printf("\nDo you wish to print to a file? "); 
	scanf("%c",&decision);
	
	if(decision>=97&&decision<=122)
			decision = decision - 32;
	
	for(x=0;x<numOfStudents;x++)
		{
			if (studentID==students[x].id)
				break;					
		}	
	
	if(decision == 'N')
	{
		getchar();
		printf("\n\nStudent Number: %d",studentID);
		
		
		printf("\n\n%s",students[x].name);	
		printf("\n\n%s",students[x].address);
		printf("\n\n%s, %s  %d",students[x].city,students[x].state,students[x].zip);
		printf("\n\n\nAssignments\t:%4d %%",assignGrade);
		printf("\n\nQuizzes\t\t:%4d %%",quizGrade);
		printf("\n\nTests\t\t:%4d %%",testGrade);
		printf("\n\nFinal Exam\t:%4d %%",finalGrade);
		printf("\n\n\nOverall Grade\t:%4d %%",totalGrade);
	}
	else if(decision == 'Y')
	{
		
		printf("\nEnter the name of the report file:  "); getchar();
		gets(fileName);
		
		fp = fopen(fileName,"w");
		
		if(fp==NULL)
		{
			printf("Error - Could not create %s",fileName);
			exit(0);
		}
		else
			printf("\n%s Successfully Created!",fileName);
		
		fprintf(fp,"\n\nStudent Number: %d",studentID);
		fprintf(fp,"\n\n%s",students[x].name);	
		fprintf(fp,"\n\n%s",students[x].address);
		fprintf(fp,"\n\n%s, %s  %d",students[x].city,students[x].state,students[x].zip);
		fprintf(fp,"\n\n\nAssignments\t:%4d %%",assignGrade);
		fprintf(fp,"\n\nQuizzes\t\t:%4d %%",quizGrade);
		fprintf(fp,"\n\nTests\t\t:%4d %%",testGrade);
		fprintf(fp,"\n\nFinal Exam\t:%4d %%",finalGrade);
		fprintf(fp,"\n\n\nOverall Grade\t:%4d %%",totalGrade);
		
		fclose(fp);
	}
	
}
