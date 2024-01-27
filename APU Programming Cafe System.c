#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define MAX 100

//----------------------------------------------------------------------------------------------------------------------
//login functions for admin, tutor and student
void detectLogin();

//password masking function
void maskPassword(char password[][MAX]);

//all menu functions for different users
int menu();
void adminMenu();
void studentMenu(char uid[][MAX]);
void tutorMenu(char uid[][MAX]);

//admin functions
void tutorReg();
void createSession();
void studentReg();
void stdEnrol();
void viewEnrolled();
void unEnroll();
void tutorPay();

//tutor functions
void tutorViewList(char uid[][MAX]);
void tutorViewPay(char uid[][MAX]);
void tutorChangePw(char uid[][MAX]);

//student functions
void studentViewList(char uid[][MAX]);
void studentUseEnrol(char uid[][MAX]);
void studentUnenrol(char uid[][MAX]);
void stdChangePw(char uid[][MAX]);


//---------------------------------------------------------------------------------------------------------------------

//to initialize, read and write for list of Tutors
void init_tutorList();
int read_tutorList();
void write_tutorList();

//to initialize, read and write for list of User Logins
void init_userList();
int read_userList();
void write_userList();

//to initialize, read and write for list of Available sessions
void init_session();
int read_session();
void write_session();

//to initialize, read and write for list of Students
int init_studentList();
int read_studentList();
void write_studentList();

//to initialize, read and write for list of Registered/Booked Sessions
int init_bookedList();
int read_bookedList();
void write_bookedList();

//to initialize, read and write for list of assigned tutor
void init_assignedList();
int read_assignedList();
void write_assignedList();


//function to initialize and write all lists of data
void init_allList();
void write_allList();

//-------------------------------------------------------------------------------------------------------------------------

//create struct for all 5 Lists with 2 array of structure for write and read purposes respectively
struct tutor {
	int id;
	char tutorID[50];
	char tutorName[50];
	char tutorSubject[50];
} readTutor[200], writeTutor[200];

struct user {
	int id;
	char uid[50];
	char pw[50];
	char role[50];
} readCredential[200], writeCredential[200];

struct session {
	int id;
	char sesCode[50];
	char sesTitle[50];
	char sesDay[50];
	char sesTime[50];
	char sesLocation[50];
	char sesTutorCode[50];
} readSes[500], writeSes[500];

struct student {
	int id;
	char studentName[50];
	char studentID[50];
} readStd[200], writeStd[200];

struct booked {
	int id;
	char bookedStd[50];
	char bookedSes[50];
	char bookedTutor[50];
	char bookedLocation[50];
} readBooked[200], writeBooked[200];

struct assignedList {
	int id;
	char tutorID[50];
	char tutorName[50];
} readAssigned[200], writeAssigned[200];


struct tutor tokeningTutor(char[]);
struct user tokeningUser(char[]);
struct session tokeningSession(char[]);
struct student tokeningStd(char[]);
struct booked tokeningB(char[]);
struct assignedList tokeningAS(char[]);

//-----------------------------------------------------------------------------------------------------------------------------


//structs used to tokenize a string using a comma as a delimiter.
//extracts variables and returns structure for all 6 Lists

struct tutor tokeningTutor(char str[200]) {
	struct tutor tempTutor;
	int position = 0;

	const char s[2] = ",";
	char* token;

	/*to obtain first token*/
	token = strtok(str, s);
	tempTutor.id = atoi(token);
	position = 1;

	/* get the first token */
	while (token != NULL) {
		token = strtok(NULL, s);
		if (position == 1) {
			strcpy(tempTutor.tutorID, token);
			position++;
		}
		else if (position == 2) {
			strcpy(tempTutor.tutorName, token);
			position++;
		}
		else {
			strcpy(tempTutor.tutorSubject, token);
			break;
		}
	}
	return tempTutor;
}

struct user tokeningUser(char str[200]) {
	struct user tempUser;
	int position = 0;

	const char s[2] = ",";
	char* token;

	/*to obtain first token*/
	token = strtok(str, s);
	tempUser.id = atoi(token);
	position = 1;

	/* walk through other tokens */
	while (token != NULL) {
		token = strtok(NULL, s);
		if (position == 1) {
			strcpy(tempUser.uid, token);
			position++;
		}
		else if (position == 2) {
			strcpy(tempUser.pw, token);
			position++;
		}
		else {
			strcpy(tempUser.role, token);
			break;
		}
	}
	return tempUser;
}

struct session tokeningSession(char str[500]) { 
	struct session tempSession;
	int position = 0;

	const char s[2] = ",";
	char* token;
	/*to obtain first token*/
	token = strtok(str, s);
	tempSession.id = atoi(token);

	/* walk through other tokens */
	while (token != NULL) {
		position++;
		token = strtok(NULL, s);
		if (token != NULL) {
			if (position == 1) {
				strcpy(tempSession.sesCode, token);
			}
			else if (position == 2) {
				strcpy(tempSession.sesTitle, token);
			}
			else if (position == 3) {
				strcpy(tempSession.sesDay, token);
			}
			else if (position == 4) {
				strcpy(tempSession.sesTime, token);
			}
			else if (position == 5) {
				strcpy(tempSession.sesLocation, token);
			}
			else {
				strcpy(tempSession.sesTutorCode, token);
				break;
			}
		}
	}
	return tempSession;
}

struct student tokeningStd(char str[200]) {
	struct student tempStd;
	int position = 0;

	const char s[2] = ",";
	char* token;

	/*to obtain first token*/
	token = strtok(str, s);
	tempStd.id = atoi(token);
	position = 1;

	/* walk through other tokens */
	while (token != NULL) {
		token = strtok(NULL, s);
		if (position == 1) {
			strcpy(tempStd.studentName, token);
			position++;
		}
		else {
			strcpy(tempStd.studentID, token);
			break;
		}
	}
	return tempStd;
}

struct booked tokeningB(char str[200]) {
	struct booked tempB;
	int position = 0;

	const char s[2] = ",";
	char* token;

	/*to obtain first token*/
	token = strtok(str, s);
	tempB.id = atoi(token);
	position = 1;

	/* walk through other tokens */
	while (token != NULL) {
		token = strtok(NULL, s);
		if (position == 1) {
			strcpy(tempB.bookedStd, token);
			position++;
		}
		else if (position == 2) {
			strcpy(tempB.bookedSes, token);
			position++;
		}
		else if (position == 3) {
			strcpy(tempB.bookedTutor, token);
			position++;
		}
		else {
			strcpy(tempB.bookedLocation, token);
			break;
		}
	}
	return tempB;
}

struct assignedList tokeningAS(char str[200]) {
	struct assignedList tempAS;
	int position = 0;

	const char s[2] = ",";
	char* token;

	/*to obtain first token*/
	token = strtok(str, s);
	tempAS.id = atoi(token);
	position = 1;

	/* walk through other tokens */
	while (token != NULL) {
		token = strtok(NULL, s);
		if (position == 1) {
			strcpy(tempAS.tutorID, token);
			position++;
		}
		else {
			strcpy(tempAS.tutorName, token);
			break;
		}
	}
	return tempAS;
}

//-----------------------------------------------------------------------------------------------------------------------------

//Data initialization for tutor, user, session, student and booked and enrol status lists
void init_tutorList() {
	FILE* tl;
	int i = 0;
	printf("Tutor data is being initialized...\n");

	tl = fopen("tutor.txt", "r");

	if (tl == NULL) {
		printf("Unable to initialize data...\nLoading default data...\n");
		//slots are empty if id = 0
		for (i = 0; i < 200; i++) {
			writeTutor[i].id = 0;
		}
		writeTutor[0].id = 1;
		strcpy(writeTutor[0].tutorID, "T01");
		strcpy(writeTutor[0].tutorName, "Albert");
		strcpy(writeTutor[0].tutorSubject, "Python Programming");

		writeTutor[1].id = 2;
		strcpy(writeTutor[1].tutorID, "T02");
		strcpy(writeTutor[1].tutorName, "Amad");
		strcpy(writeTutor[1].tutorSubject, "Java Programming");

		writeTutor[2].id = 3;
		strcpy(writeTutor[2].tutorID, "T03");
		strcpy(writeTutor[2].tutorName, "Steve");
		strcpy(writeTutor[2].tutorSubject, "C Programming");

		//to write data into tutor.txt
		tl = fopen("tutor.txt", "w");
		if (tl != NULL) {
			for (i = 0; i < 3; i++) {
				fprintf(tl, "%d,%s,%s,%s,\n", writeTutor[i].id, writeTutor[i].tutorID, writeTutor[i].tutorName, writeTutor[i].tutorSubject);
			}
			fclose(tl);
		}
		else {
			printf("Unable to open text file.\n");
		}
	}
	else {
		printf("Tutor data has already been initialized.\n");
		fclose(tl);
	}
}

void init_userList() {
	FILE* u;
	int i;
	printf("User data is being initialized...\n");

	u = fopen("user.txt", "r");

	if (u == NULL) {
		printf("Unable to initialize data...\nLoading default data...\n");
		//slots are empty if id = 0
		for (i = 0; i < 200; i++) {
			writeCredential[i].id = 0;
		}
		writeCredential[0].id = 1;
		strcpy(writeCredential[0].uid, "T01");
		strcpy(writeCredential[0].pw, "apu123");
		strcpy(writeCredential[0].role, "tutor");

		writeCredential[1].id = 2;
		strcpy(writeCredential[1].uid, "T02");
		strcpy(writeCredential[1].pw, "apu321");
		strcpy(writeCredential[1].role, "tutor");

		writeCredential[2].id = 3;
		strcpy(writeCredential[2].uid, "T03");
		strcpy(writeCredential[2].pw, "apu456");
		strcpy(writeCredential[2].role, "tutor");

		writeCredential[3].id = 4;
		strcpy(writeCredential[3].uid, "admin");
		strcpy(writeCredential[3].pw, "admin");
		strcpy(writeCredential[3].role, "admin");

		//to write data into user.txt
		u = fopen("user.txt", "w");
		if (u != NULL) {
			for (i = 0; i < 4; i++) {
				fprintf(u, "%d,%s,%s,%s,\n", writeCredential[i].id, writeCredential[i].uid, writeCredential[i].pw, writeCredential[i].role);
			}
			fclose(u);
		}
		else {
			printf("Unable to open text file.\n");
		}
	}
	else {
		printf("User data has already been initialized.\n");
		fclose(u);
	}
}

void init_session() {
	FILE* ses;
	int i;
	printf("Session data is being initialized...\n");

	ses = fopen("session.txt", "r");

	if (ses == NULL) {
		printf("Unable to initialize data...\nLoading default data...\n");
		//slots are empty if id = 0
		for (i = 0; i < 500; i++) {
			writeSes[i].id = 0;
		}
		writeSes[0].id = 1;
		strcpy(writeSes[0].sesCode, "PYP101");
		strcpy(writeSes[0].sesTitle, "Python Programming");
		strcpy(writeSes[0].sesDay, "Saturday");
		strcpy(writeSes[0].sesTime, "9.00am");
		strcpy(writeSes[0].sesLocation, "C-01-01");
		strcpy(writeSes[0].sesTutorCode, "T01");

		writeSes[1].id = 2;
		strcpy(writeSes[1].sesCode, "JAV102");
		strcpy(writeSes[1].sesTitle, "Java Programming");
		strcpy(writeSes[1].sesDay, "Sunday");
		strcpy(writeSes[1].sesTime, "9.00am");
		strcpy(writeSes[1].sesLocation, "C-01-02");
		strcpy(writeSes[1].sesTutorCode, "T02");

		writeSes[2].id = 3;
		strcpy(writeSes[2].sesCode, "CPL103");
		strcpy(writeSes[2].sesTitle, "C Programming");
		strcpy(writeSes[2].sesDay, "Saturday");
		strcpy(writeSes[2].sesTime, "2.00pm");
		strcpy(writeSes[2].sesLocation, "C-01-03");
		strcpy(writeSes[2].sesTutorCode, "T03");

		writeSes[3].id = 4;
		strcpy(writeSes[3].sesCode, "WEB104");
		strcpy(writeSes[3].sesTitle, "Web Development");
		strcpy(writeSes[3].sesDay, "Sunday");
		strcpy(writeSes[3].sesTime, "2.00pm");
		strcpy(writeSes[3].sesLocation, "C-01-04");
		strcpy(writeSes[3].sesTutorCode, "T04");

		writeSes[4].id = 5;
		strcpy(writeSes[4].sesCode, "CSP105");
		strcpy(writeSes[4].sesTitle, "C Sharp Programming");
		strcpy(writeSes[4].sesDay, "Monday");
		strcpy(writeSes[4].sesTime, "7.00pm");
		strcpy(writeSes[4].sesLocation, "C-01-05");
		strcpy(writeSes[4].sesTutorCode, "T05");
		//to write data into session.txt
		ses = fopen("session.txt", "w");
		if (ses != NULL) {
			for (i = 0; i < 5; i++) {
				fprintf(ses, "%d,%s,%s,%s,%s,%s,%s,\n", writeSes[i].id, writeSes[i].sesCode, writeSes[i].sesTitle, writeSes[i].sesDay, writeSes[i].sesTime, writeSes[i].sesLocation, writeSes[i].sesTutorCode);
			}
			fclose(ses);
		}
		else {
			printf("Unable to open text file.\n");
		}
	}
	else {
		printf("Session data has already been initialized.\n");
		fclose(ses);
	}
}

int init_studentList() {
	FILE* sl;
	int i;
	printf("Student data is being initialized...\n");
	//slots are empty if id = 0
	for (i = 0; i < 200; i++) {
		writeStd[i].id = 0;
	}
	sl = fopen("studentList.txt", "r");
	if (sl != NULL) {
		printf("Student file detected.\n");
	}
	else if (sl == NULL) {
		printf("No student file detected. Default data loaded instead.\n");
	}
	return 0;
}

int init_bookedList() {
	FILE* bl;
	printf("Booked session data is being initialized...\n");
	//slots are empty if id = 0
	for (int i = 0; i < 200; i++) {
		writeBooked[i].id = 0;
	}
	bl = fopen("bookedSessionList.txt", "r");
	if (bl != NULL) {
		printf("Booked file detected.\n");
		return 0;
	}
	else if (bl == NULL) {
		printf("No booked file detected. Default data loaded instead.\n");
	}
	return 0;
}

void init_assignedList() {
	FILE* a;
	int i;
	printf("Data for Assigned List is being initialized...\n");

	a = fopen("assignedList.txt", "r");

	if (a == NULL) {
		printf("Unable to initialize data...\nLoading default data...\n");
		//slots are empty if id = 0
		for (i = 0; i < 200; i++) {
			writeAssigned[i].id = 0;
		}
		writeAssigned[0].id = 1;
		strcpy(writeAssigned[0].tutorID, "T01");
		strcpy(writeAssigned[0].tutorName, "Albert");

		writeAssigned[1].id = 2;
		strcpy(writeAssigned[1].tutorID, "T02");
		strcpy(writeAssigned[1].tutorName, "Amad");

		writeAssigned[2].id = 3;
		strcpy(writeAssigned[2].tutorID, "T03");
		strcpy(writeAssigned[2].tutorName, "Steve");

		//to write data into assignedList.txt
		a = fopen("assignedList.txt", "w");
		if (a != NULL) {
			for (i = 0; i < 3; i++) {
				fprintf(a, "%d,%s,%s,\n", writeAssigned[i].id, writeAssigned[i].tutorID, writeAssigned[i].tutorName);
			}
			fclose(a);
		}
		else {
			printf("Unable to open text file.\n");
		}
	}
	else {
		printf("Data for Assigned List has already been initialized.\n");
		fclose(a);
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

//Read data from tutor, user, session, student, booked and assignedList txt file
int read_tutorList() {
	FILE* tl;
	char readstr[50];
	int i = 0;
	struct tutor tutorSt;

	tl = fopen("tutor.txt", "r");

	if (tl != NULL) {
		while (fgets(readstr, 50, tl) != NULL) {
			tutorSt = tokeningTutor(readstr);
			readTutor[i].id = tutorSt.id;
			strcpy(readTutor[i].tutorID, tutorSt.tutorID);
			strcpy(readTutor[i].tutorName, tutorSt.tutorName);
			strcpy(readTutor[i].tutorSubject, tutorSt.tutorSubject);
			i++;

		}
		fclose(tl);
	}
	else {
		printf("Unable to open file.\n");
	}
	return 0;
}

int read_userList() {
	FILE* u;
	char readstr[50];
	int i = 0;
	struct user userSt;

	u = fopen("user.txt", "r");

	if (u != NULL) {
		while (fgets(readstr, 50, u) != NULL) {
			userSt = tokeningUser(readstr);
			readCredential[i].id = userSt.id;
			strcpy(readCredential[i].uid, userSt.uid);
			strcpy(readCredential[i].pw, userSt.pw);
			strcpy(readCredential[i].role, userSt.role);
			i++;
		}
		fclose(u);
	}
	else {
		printf("Unable to open file.\n");
	}
	return 0;
}

int read_session() {
	FILE* s;
	char readstr[500];
	int i = 0;
	struct session sesSt;
	s = fopen("session.txt", "r");
	if (s != NULL) {
		while (fgets(readstr, 500, s) != NULL) {
			sesSt = tokeningSession(readstr);
			readSes[i].id = sesSt.id;
			strcpy(readSes[i].sesCode, sesSt.sesCode);
			strcpy(readSes[i].sesTitle, sesSt.sesTitle);
			strcpy(readSes[i].sesDay, sesSt.sesDay);
			strcpy(readSes[i].sesTime, sesSt.sesTime);
			strcpy(readSes[i].sesLocation, sesSt.sesLocation);
			strcpy(readSes[i].sesTutorCode, sesSt.sesTutorCode);
			i++;
		}
		fclose(s);
	}
	else {
		printf("Unable to open file.\n");
	}
	return 0;
}

int read_studentList() {
	FILE* std;
	char readstr[50];
	int i = 0;
	struct student stdSt;

	std = fopen("studentList.txt", "r");

	if (std != NULL) {
		while (fgets(readstr, 50, std) != NULL) {
			stdSt = tokeningStd(readstr);
			readStd[i].id = stdSt.id;
			strcpy(readStd[i].studentName, stdSt.studentName);
			strcpy(readStd[i].studentID, stdSt.studentID);
			i++;
		}
		fclose(std);
	}
	else {
		printf("Unable to open student file.\n");
	}
	return 0;
}

int read_bookedList() {
	FILE* bl;
	char readstr[100];
	int i = 0;
	struct booked bookedSt;

	bl = fopen("bookedSessionList.txt", "r");
	if (bl != NULL) {
		while (fgets(readstr, 100, bl) != NULL) {
			bookedSt = tokeningB(readstr);
			readBooked[i].id = bookedSt.id;
			strcpy(readBooked[i].bookedStd, bookedSt.bookedStd);
			strcpy(readBooked[i].bookedSes, bookedSt.bookedSes);
			strcpy(readBooked[i].bookedTutor, bookedSt.bookedTutor);
			strcpy(readBooked[i].bookedLocation, bookedSt.bookedLocation);
			i++;
		}
		fclose(bl);
	}
	else {
		printf("Unable to open bookedList file.\n");
	}
	return 0;
}

int read_assignedList() {
	FILE* a;
	char readstr[50];
	int i = 0;
	struct assignedList assignSt;

	a = fopen("assignedList.txt", "r");

	if (a != NULL) {
		while (fgets(readstr, 50, a) != NULL) {
			assignSt = tokeningAS(readstr);
			readAssigned[i].id = assignSt.id;
			strcpy(readAssigned[i].tutorID, assignSt.tutorID);
			strcpy(readAssigned[i].tutorName, assignSt.tutorName);
			i++;

		}
		fclose(a);
	}
	else {
		printf("Unable to open file.\n");
	}
	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------
// functions for different menu types

//main program menu
int menu(option) {
	int choice;
	system("color A");
	printf("\n\nThanks for using APU Programming Cafe Management System.\n\n");
	printf("Select user login (1) or exit program (2):\n\n\n");
	printf("1- User Login\n");
	printf("2- Exit Program\n\n");
	printf("User Input: ");
	scanf("%d", &choice);
	system("cls");
	return choice;
}

//admin menu
void adminMenu() {
	int adminChoice = 0;
	while (1) {
		printf("\nAdministrator Page\n");
		printf("------------------\n\n");
		printf("\nSelect an operation:\n");
		printf("\n1- Registration of Tutor\n");
		printf("2- Adding new programming cafe session\n");
		printf("3- Registration of Student\n");
		printf("4- Enrol student in a session\n");
		printf("5- List all sessions\n");
		printf("6- Unenroll student from a session\n");
		printf("7- View tutor pay\n");
		printf("8- Log out\n\n");
		printf("User Input: ");
		scanf("%d", &adminChoice);
		system("cls");
		if (adminChoice == 1) {
			tutorReg();
		}
		else if (adminChoice == 2) {
			createSession();
		}
		else if (adminChoice == 3) {
			studentReg();
		}
		else if (adminChoice == 4) {
			stdEnrol();
		}
		else if (adminChoice == 5) {
			viewEnrolled();
		}
		else if (adminChoice == 6) {
			unEnroll();
		}
		else if (adminChoice == 7) {
			tutorPay();
		}
		else if (adminChoice == 8) { //to exit program
			system("color 8");
			printf("\nAccount logged out successfully.\n\n\n");
			break;
		}
		else {
			printf("Invalid choice! Please try again.\n\n\n");
		}
	}
	return;
}
//tutor menu
void tutorMenu(char uid[][MAX]) {
	int tutorChoice = 0;
	while (1) {
		printf("\nTutor Page\n");
		printf("==========\n\n");
		printf("\nSelect an operation:\n");
		printf("\n1- View listing of your session(s)\n");
		printf("2- View pay\n");
		printf("3- Change account password\n");
		printf("4- Log out\n\n");
		printf("User Input: ");
		scanf("%d", &tutorChoice);
		system("cls");
		if (tutorChoice == 1) {
			tutorViewList(uid);
		}
		else if (tutorChoice == 2) {
			tutorViewPay(uid);
		}
		else if (tutorChoice == 3) {
			tutorChangePw(uid);
		}
		else if (tutorChoice == 4) { //to exit program
			system("color 8");
			system("cls");
			printf("\nAccount logged out successfully.\n\n\n");
			break;
		}
		else {
			printf("Invalid choice! Please try again.\n\n\n");
		}
	}
	return;
}
//student menu
void studentMenu(char uid[][MAX]) {
	int studentChoice = 0;
	while (1) {
		printf("\nStudent Page\n");
		printf("============\n\n");
		printf("\nSelect an operation:\n");
		printf("\n1- View listing of your session(s)");
		printf("\n2- Enrol into an available session");
		printf("\n3- Unenroll from a session");
		printf("\n4- Change account password");
		printf("\n5- Log out\n\n");
		printf("User Input: ");
		scanf("%d", &studentChoice);
		system("cls");
		if (studentChoice == 1) {
			studentViewList(uid);
		}
		else if (studentChoice == 2) {
			studentUseEnrol(uid); 
		}
		else if (studentChoice == 3) {
			studentUnenrol(uid);
		}
		else if (studentChoice == 4) {
			stdChangePw(uid);
		}
		else if (studentChoice == 5) { //to exit program
			system("color 8");
			system("cls");
			printf("\nAccount logged out successfully.\n\n\n");
			break;
		}
		else {
			printf("Invalid choice! Please try again.\n\n\n");
		}
	}
	return;
}

//-----------------------------------------------------------------------------------------------------------------------------
//function to initialize all data in main

void init_allList() {
	FILE* fp1;
	FILE* fp2;
	FILE* fp3;
	FILE* fp4;
	FILE* fp5;
	FILE* fp6;

	fp1 = fopen("tutor.txt", "r");
	//for first time running the code, files will be made and hardcoded in the init function
	init_tutorList();
	read_tutorList();
	


	//repeat for 4 remaining lists
	fp2 = fopen("user.txt", "r");
	//for first time running the code, files will be made and hardcoded in the init function
	init_userList();
	read_userList();
	


	fp3 = fopen("session.txt", "r");
	//for first time running the code, files will be made and hardcoded in the init function
	init_session();
	read_session();
	

	fp4 = fopen("studentList.txt", "r");
	//for first time running the code, files will be made and hardcoded in the init function
	init_studentList();
	read_studentList();
	


	fp5 = fopen("bookedSessionList.txt", "r");
	//for first time running the code, files will be made and hardcoded in the init function
	init_bookedList();
	read_bookedList();

	fp6 = fopen("assignedList.txt", "r");
	//for first time running the code, files will be made and hardcoded in the init function
	init_assignedList();
	read_assignedList();
	
}
//-----------------------------------------------------------------------------------------------------------------------------
//Login Menus for tutor and student\

//login for all users
void detectLogin() {
	char uid[MAX];
	char password[MAX];
	printf("User Login\n");
	printf("-------------\n\n");
	printf("Please enter your UID: ");
	scanf("%s", &uid);
	printf("Please enter your password: ");
	maskPassword(password);
	system("cls");

	int i;
	int match = 0;
	for (i = 0; i < 200; i++) {
		if (strcmp(readCredential[i].uid, uid) == 0 && strcmp(readCredential[i].pw, password) == 0 && strcmp(readCredential[i].role, "admin") == 0) {
			match = 1;
			break;
		}
		if (strcmp(readCredential[i].uid, uid) == 0 && strcmp(readCredential[i].pw, password) == 0 && strcmp(readCredential[i].role, "tutor") == 0) {
			match = 2;
			break;
		}
		if (strcmp(readCredential[i].uid, uid) == 0 && strcmp(readCredential[i].pw, password) == 0 && strcmp(readCredential[i].role, "student") == 0) {
			match = 3;
			break;
		}
	}

	if (match == 1) {
		adminMenu();
	}
	else if (match == 2) {
		tutorMenu(uid);
	}
	else if (match == 3) {
		studentMenu(uid);
	}
	else {
		printf("Invalid credentials!\n");
	}
}
//-----------------------------------------------------------------------------------------------------------------------------
//password masking function
void maskPassword(char password[MAX]) {
	int i = 0;
	char password_input;
	while ((password_input = _getch()) != 13) {
		if (password_input == 8) {  //to handle backspace
			if (i > 0) {
				i--;
				printf("\b \b");  //to move cursor back, overwrite with a space and then move the cursor back again
			}
		}
		else {
			password[i] = password_input;
			printf("*");
			i++;
		}
	}
	password[i] = '\0';
}
//-----------------------------------------------------------------------------------------------------------------------------
//admin functions

//tutor registration
void tutorReg() {
	char tutorID[50], tutorName[50], tutorSubject[50], pw[50];
	int i = 0, p = 0, exists = 0, emptyIndex = 0;

	printf("\nEnter new tutor ID: ");
	scanf("%s", &tutorID);

	//to check whether tutor ID is taken
	for (i = 0; i < 200; i++) {
		if (strcmp(readCredential[i].uid, tutorID) == 0) {
			exists = 1;
			break;
		}
	}
	if (exists) {
		printf("Tutor ID exists. Please register with a new Tutor ID.\n");
	}
	else {
		printf("Enter tutor name: ");
		scanf(" %[^\n]", &tutorName);
		printf("Enter title of subject: ");
		scanf(" %[^\n]", &tutorSubject);
		printf("Enter new password: ");
		scanf("%s", &pw);

		if (strcmp(tutorID, "T04") == 0) {
			system("cls");
			printf("Account successfully created for T04.\n");
			printf("\nPre-existing session is created for T04. Changing T04 status to 'assigned' status.");
			// update newly assigned tutor data to assignedList struct
			for (p = 0; p < 200; p++) {
				if (readAssigned[p].id == 0) {
					// update struct with the new assignedList data
					readAssigned[p].id = (p + 1);
					strcpy(readAssigned[p].tutorID, "T04");
					strcpy(readAssigned[p].tutorName, tutorName);
					break;  // stop iterating once an empty index is found

				}
			}
		}
		else if (strcmp(tutorID, "T05") == 0) {
			system("cls");
			printf("Account successfully created for T05.\n");
			printf("\nPre-existing session is created for T05. Changing T05 status to 'assigned' status.");
			//update newly assigned tutor data to assignedList struct
			for (p = 0; p < 200; p++) {
				if (readAssigned[p].id == 0) {
					// update struct with the new assignedList data
					readAssigned[p].id = (p + 1);
					strcpy(readAssigned[p].tutorID, "T05");
					strcpy(readAssigned[p].tutorName, tutorName);
					break;  // stop iterating once an empty index is found

				}
			}
		}
		// Update the user struct with the new user data
		for (emptyIndex = 0; emptyIndex < 200; emptyIndex++) {
			if (readCredential[emptyIndex].id == 0) {
				readCredential[emptyIndex].id = (emptyIndex + 1);
				strcpy(readCredential[emptyIndex].uid, tutorID);
				strcpy(readCredential[emptyIndex].pw, pw);
				strcpy(readCredential[emptyIndex].role, "tutor");
				break;  // Stop iterating once an empty index is found
			}
		}

		// Update the tutor struct with the new tutor data
		for (emptyIndex = 0; emptyIndex < 200; emptyIndex++) {
			if (readTutor[emptyIndex].id == 0) {
				readTutor[emptyIndex].id = (emptyIndex + 1);
				strcpy(readTutor[emptyIndex].tutorID, tutorID);
				strcpy(readTutor[emptyIndex].tutorName, tutorName);
				strcpy(readTutor[emptyIndex].tutorSubject, tutorSubject);
				break;  // Stop iterating once an empty index is found
			}
		}
		system("cls");
		printf("\nRecent activity: ");
		printf("\nNew tutor account successfully created.\n");
		printf("\nName of new tutor: %s", tutorName);
		printf("\nTutor subject %s", tutorSubject);
		printf("\nNew tutor ID: %s", tutorID);
		printf("\nPassword set: %s", pw);
	}
}

//student registration function
void  studentReg() {
	char studentID[50], studentName[50], pw[50];
	int i = 0, exists = 0, emptyIndex = 0;

	printf("\nEnter new student ID: ");
	scanf("%s", &studentID);

	//to check whether student ID is taken
	for (i = 0; i < 200; i++) {
		if (strcmp(readCredential[i].uid, studentID) == 0) {
			exists = 1;
			break;
		}
	}
	if (exists) {
		printf("Student ID exists. Please register with a new student ID.\n");
	}
	else {
		printf("Enter student name: ");
		scanf(" %[^\n]", &studentName);
		printf("Enter new password: ");
		scanf("%s", &pw);

		for (emptyIndex = 0; emptyIndex < 200; emptyIndex++) {
			if (readCredential[emptyIndex].id == 0) {
				// Update struct with the new user data
				readCredential[emptyIndex].id = (emptyIndex + 1);
				strcpy(readCredential[emptyIndex].uid, studentID);
				strcpy(readCredential[emptyIndex].pw, pw);
				strcpy(readCredential[emptyIndex].role, "student");
				break;  // Stop iterating once an empty index is found

			}
		}
		for (emptyIndex = 0; emptyIndex < 200; emptyIndex++) {
			if (readStd[emptyIndex].id == 0) {
				// Update struct with the new student data
				readStd[emptyIndex].id = (emptyIndex + 1);
				strcpy(readStd[emptyIndex].studentName, studentName);
				strcpy(readStd[emptyIndex].studentID, studentID);
				break;  // Stop iterating once an empty index is found
			}
		}
		system("cls");
		printf("\nRecent activity: ");
		printf("\nNew student account successfully created.\n");
		printf("\nName of new student: %s", studentName);
		printf("\nNew student ID: %s", studentID);
		printf("\nPassword set: %s", pw);
	}
}

//Adding new session function
void createSession() {
	int i = 0, j = 0, k = 0, m = 0, n = 0, p = 0, sesTutorAssigned = 0, tutorExist = 0, validTutor = 0;
	char sCode[MAX], sTitle[MAX], sDay[MAX], sTime[MAX], sLocation[MAX], sTutorCode[MAX], assignedTutorCode[MAX], assignedTutorName[MAX], newTutorName[MAX];
	printf("List of sessions: \n\n");
	printf("--------------------------------------------------------------------------------------------------------------------\n");
	printf("Session Code\t   Title\t\tDay\t\tStart Time\t\tLocation\t\tTutor Code\n");
	printf("--------------------------------------------------------------------------------------------------------------------\n");
	for (i = 0; i < 500; i++) {
		if (readSes[i].id != 0) {
			printf("%9s %21s %15s %15s %24s %22s\n", readSes[i].sesCode, readSes[i].sesTitle, readSes[i].sesDay, readSes[i].sesTime, readSes[i].sesLocation, readSes[i].sesTutorCode);
		}
	}
	int choice = 0;
	printf("\nWould you like to create a new session?\n1- Yes\n2- Return to Admin Menu\nUser input: ");
	scanf("%d", &choice);
	if (choice == 1) {
		printf("\nEnter Tutor Code for new session: ");
		scanf("%s", &sTutorCode);

		//checks whether tutor ID is registered
		tutorExist = 0;
		for (j = 0; j < 200; j++) {
			if (strcmp(readTutor[j].tutorID, sTutorCode) == 0) {
				strcpy(newTutorName,readTutor[j].tutorName);
				tutorExist = 1;
				break;
			}
		}
		if (tutorExist) {
			printf("Enter Session Title for new session: ");
			scanf(" %[^\n]", &sTitle);

			// to check whether tutor is responsible of tutoring its designated subject
			for (m = 0; m < 200; m++) {
				if ((strcmp(readTutor[m].tutorID, sTutorCode) == 0) && (strcmp(readTutor[m].tutorSubject, sTitle) == 0)) {
					validTutor = 1;
					break;
				}
			}
			if (validTutor) {
				//to check whether tutor is already assigned to a session
				for (n = 0; n < 200; n++) {
					if (strcmp(readAssigned[n].tutorID, sTutorCode) == 0) {
						sesTutorAssigned = 1;
						strcpy(assignedTutorCode,readAssigned[n].tutorID);
						strcpy(assignedTutorName,readAssigned[n].tutorName);
						break;
					}
				}
				if (sesTutorAssigned) {
					system("cls");
					printf("The following tutor has already been assigned into an existing session:");
					printf("\nName: %s", assignedTutorName);
					printf("\nTutor ID: %s", assignedTutorCode);
					printf("\nOne tutor is strictly assigned to one and only session at a time!!!\n");
					return;
				}
				else {
					printf("Enter Session Code for new session: ");
					scanf("%s", &sCode);
					printf("Enter Session Day for new session: ");
					scanf("%s", &sDay);
					printf("Enter Session Time for new session: ");
					scanf("%s", &sTime);
					printf("Enter Location for new session: ");
					scanf("%s", &sLocation);

					//update new session data to session struct
					for (k = 0; k < 500; k++) {
						if (readSes[k].id == 0) {
							// Update the user struct with the new session data
							readSes[k].id = (k + 1);
							strcpy(readSes[k].sesCode, sCode);
							strcpy(readSes[k].sesTitle, sTitle);
							strcpy(readSes[k].sesDay, sDay);
							strcpy(readSes[k].sesTime, sTime);
							strcpy(readSes[k].sesLocation, sLocation);
							strcpy(readSes[k].sesTutorCode, sTutorCode);
							break;  // Stop iterating once an empty index is found

						}
					}
					//update newly assigned tutor data to assignedList struct
					for (p = 0; p < 200; p++) {
						if (readAssigned[p].id == 0) {
							// Update the user struct with the new readAssigned data
							readAssigned[p].id = (p + 1);
							strcpy(readAssigned[p].tutorID, sTutorCode);
							strcpy(readAssigned[p].tutorName, newTutorName);
							break;  // Stop iterating once an empty index is found

						}
					}
					system("cls");
					printf("\nRecent activity: ");
					printf("New session created successfully.\n");
					printf("\nNew session code: %s", sCode);
					printf("\nNew session title: %s", sTitle);
					printf("\nDay of new session: %s", sDay);
					printf("\nNew session time: %s", sTime);
					printf("\nNew session location: %s", sLocation);
					printf("\nTutor assigned: %s", sTutorCode);
				}
			}
			else {
				system("cls");
				printf("Tutor is not designated to tutor the entered session.\n");
				return;
			}
		}
		else {
			system("cls");
			printf("Tutor ID not found.\n");
			printf("Please assign a new session with a registered tutor.\n");
			return;
		}
	}
	else if (choice == 2) {
		system("cls");
		printf("Returning to Admin Menu...\n");
	}
	else {
		printf("Invalid input! Please try again.\n");
	}
}

//Student enrolment
void stdEnrol() {
	int i = 0, j = 0, k = 0, m = 0, n = 0, stdExist = 0, sesExist = 0, sesValid = 0, bookedExist = 0;
	char stdID[MAX], sesCode[MAX], sesLocation[MAX], sesTutorCode[MAX], tempName[MAX];
	printf("Enter a student ID to enrol the student into a session:");
	scanf("%s",&stdID);

	for (i = 0; i < 200; i++) {
		if (strcmp(readStd[i].studentID, stdID) == 0) {
			strcpy(tempName, readStd[i].studentName);
			stdExist = 1;
			break;
		}
	}
	if (stdExist) {
		//display list of sessions
		printf("List of sessions: \n\n");
		printf("--------------------------------------------------------------------------------------------------------------------\n");
		printf("Session Code\t   Title\t\tDay\t\tStart Time\t\tLocation\t\tTutor Code\n");
		printf("--------------------------------------------------------------------------------------------------------------------\n");
		for (i = 0; i < 500; i++) {
			if (readSes[i].id != 0) {
				printf("%9s %21s %15s %15s %24s %22s\n", readSes[i].sesCode, readSes[i].sesTitle, readSes[i].sesDay, readSes[i].sesTime, readSes[i].sesLocation, readSes[i].sesTutorCode);
			}
		}
		//Request input for session code to enrol into
		printf("\nEnter an existing Session Code to enrol student:");
		scanf("%s",&sesCode);
		for (j = 0; j < 500; j++) {
			if (strcmp(readSes[j].sesCode, sesCode) == 0) {
				strcpy(sesLocation, readSes[j].sesLocation); 
				strcpy(sesTutorCode, readSes[j].sesTutorCode);
				sesExist = 1;
			}
		}
		if (sesExist) {
			//to check whether session is assigned to a tutor
			for (m = 0; m < 200; m++) {
				if (strcmp(readAssigned[m].tutorID, sesTutorCode) == 0) {
					sesValid = 1;
					break;
				}
			}
			if (sesValid) {
				for (n = 0; n < 200; n++) {
					if (readBooked[n].id!=0 && (strcmp(tempName,readBooked[n].bookedStd)==0)&&(strcmp(sesCode,readBooked[n].bookedSes)==0) && (strcmp(sesTutorCode, readBooked[n].bookedTutor)==0) && (strcmp(sesLocation, readBooked[n].bookedLocation)==0)) {
						bookedExist = 1;
						break;  // Stop iterating once an empty index is found
					}
				}
				if (bookedExist == 0) {
					for (k = 0; k < 200; k++) {
						if (readBooked[k].id == 0) {
							// Update the booked struct with the new booked data
							readBooked[k].id = (k + 1);
							strcpy(readBooked[k].bookedStd, tempName);
							strcpy(readBooked[k].bookedSes, sesCode);
							strcpy(readBooked[k].bookedTutor, sesTutorCode);
							strcpy(readBooked[k].bookedLocation, sesLocation);
							break;  // Stop iterating once an empty index is found

						}
					}
					system("cls");
					printf("\nRecent activity: ");
					printf("\nThe following student has been enrolled into the following session successfully:");
					printf("\nStudent Name: %s", tempName);
					printf("\nEnrolled Session Code: %s", sesCode);
					printf("\nSession location: %s", sesLocation);
					printf("\nTutor in charge: %s", sesTutorCode);
				}
				else {
					system("cls");
					printf("Duplicate data entry detected!\n");
					return;
				}
			}
			else {
				system("cls");
				printf("No tutor is assigned to this session!\n");
				return;
			}
		}
		else {
			system("cls");
			printf("Invalid session! Please try again.\n");
			return;
		}
	}
	else {
		system("cls");
		printf("Invalid student ID! Please try again.\n");
		return;
	}
}

//view enrol/booked list
void viewEnrolled() {
	int i = 0, back = 0;
	printf("List of Programming Cafe Sessions with participating students.\n");
	printf("--------------------------------------------------------------------------------------------\n");
	printf("Student Name\tSession Code\t   Tutor Code\t\tLocation\n");
	printf("--------------------------------------------------------------------------------------------\n");
	for (i = 0; i < 200; i++) {
		if (readBooked[i].id != 0) {
			printf("%11s %13s %15s %21s\n", readBooked[i].bookedStd, readBooked[i].bookedSes, readBooked[i].bookedTutor, readBooked[i].bookedLocation);
		}
	}
	while (1) {
		printf("\nEnter '1' to return to admin menu. ");
		printf("\nUser input: ");
		scanf("%d", &back);
		if (back) {
			system("cls");
			break;
		}
		else {
			printf("Invalid choice! Please try again.\n");
		}
	}
}

void unEnroll() {
	int i = 0 , stdExist = 0, n = 0, bookedExist = 0, deleteConfirm = 0;
	char stdID[MAX], sesCode[MAX], stdName[MAX];
	printf("Enter student ID to unenroll:");
	scanf("%s", &stdID);

	//to check whether student exists
	for (i = 0; i < 200; i++) {
		if (strcmp(readStd[i].studentID, stdID) == 0) {
			strcpy(stdName, readStd[i].studentName);
			stdExist = 1;
			break;
		}
	}
	if (stdExist) {
		printf("Enter session code of subject to unenroll from: ");
		scanf("%s",&sesCode);
		// to check whether booked session exists
		for (n = 0; n < 200; n++) {
			if ((strcmp(stdName, readBooked[n].bookedStd) == 0) && (strcmp(sesCode, readBooked[n].bookedSes) == 0)) {
				bookedExist = 1;
				break;  // Stop iterating once an empty index is found
			}
		}
		if (bookedExist) {
			printf("Enrolled session found!\nWould you like to unenroll student from session?");
			printf("\n1- Yes\n2- No\nUser Input:");
			scanf("%d", &deleteConfirm);
			if (deleteConfirm == 1) {
				readBooked[n].id = 0;
				system("cls");
				printf("Enrolled session has been removed successfully.\n");
				return;
			}
			else if (deleteConfirm == 2) {
				system("cls");
				printf("Aborting action...\n");
				return;
			}
			else {
				system("cls");
				printf("Invalid input! No actions performed.\n");
				return;
			}
		}
		else {
			system("cls");
			printf("Enrolled session not found!\n");
			return;
		}
	}
	else {
		system("cls");
		printf("Invalid student ID! Student ID is not registered.\n");
		return;
	}
}

void tutorPay() {
	int i = 0, back = 0;
	char tutorID[MAX], title[MAX];
	printf("Tutor list assigned to a tutor session and their Pay.\n");
	printf("Tutor ID\tTitle\t\t\tPay\n");
	printf("------------------------------------------------------------\n");
	
	//to display only tutors assigned to a session who will receive their pay
	for (i = 0; i < 200; i++) {
		if (readAssigned[i].id != 0) {
			strcpy(tutorID, readAssigned[i].tutorID);
			int j = 0;
			for (j = 0; j < 200; j++) {
				if (strcmp(readTutor[j].tutorID, tutorID) == 0) {
					strcpy(title, readTutor[j].tutorSubject);
					break;
				}
			}
			printf("%5s %25s\t\tRM100\n", tutorID, title);
		}
	}
	while (1) {
		printf("\nEnter '1' to return to admin menu. ");
		printf("\nUser input: ");
		scanf("%d", &back);
		if (back) {
			system("cls");
			break;
		}
		else {
			printf("Invalid choice! Please try again.\n");
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------------------
// tutor function
void tutorViewList(char uid[MAX]) {
	int i = 0, back = 0;
	printf("List of Programming Cafe Sessions with participating students.\n");
	printf("--------------------------------------------------------------------------------------------\n");
	printf("Student Name\tSession Code\t   Tutor Code\t\tLocation\n");
	printf("--------------------------------------------------------------------------------------------\n");
	for (i = 0; i < 200; i++) {
		if (readBooked[i].id != 0) {
			if (strcmp(readBooked[i].bookedTutor, uid) == 0) {
				printf("%11s %13s %15s %21s\n", readBooked[i].bookedStd, readBooked[i].bookedSes, readBooked[i].bookedTutor, readBooked[i].bookedLocation);
			}
		}
	}
	while (1) {
		printf("\nEnter '1' to return to tutor menu.");
		printf("\nUser input: ");
		scanf("%d", &back);
		if (back) {
			system("cls");
			break;
		}
		else {
			printf("Invalid choice! Please try again.\n");
		}
	}
}

void tutorViewPay(char uid[MAX]) {
	int i = 0, j = 0, k = 0,back = 0, matchingAssignment = 0;
	char tutorID[MAX], title[MAX], tutorName[MAX];
	
	//to obtain tutor's name and subject by comparing uid
	for (i = 0; i < 200; i++) {
		if (strcmp(readTutor[i].tutorID, uid) == 0) {
			strcpy(title, readTutor[i].tutorSubject);
			strcpy(tutorName, readTutor[i].tutorName);
			break;
		}
	}
	printf("Hello %s, this is your accumulated pay: \n\n",tutorName);
	printf("------------------------------------------------------------\n");
	printf("Tutor ID\tTitle\t\t\tPay\n");
	printf("------------------------------------------------------------\n");
	for (j = 0; j < 200; j++) {
		if (readAssigned[j].id != 0) {
			if (strcmp(readAssigned[j].tutorID, uid) == 0) {
				matchingAssignment = 1;
				printf("%5s %25s\t\tRM100\n", uid, title);
			}
		}
	}
	if (!matchingAssignment) {
		printf("%5s %25s\t\tRM0\n", uid, title);
	}
	while (1) {
		printf("\nEnter '1' to return to tutor menu. ");
		printf("\nUser input: ");
		scanf("%d", &back);
		if (back) {
			system("cls");
			break;
		}
		else {
			printf("Invalid choice! Please try again.\n");
		}
	}
}

void tutorChangePw(char uid[MAX]) {
	int i = 0, j = 0;
	char tutorName[MAX], oldPassword[MAX], newPassword[MAX], tutorUID[MAX];
	for (i = 0; i < 200; i++) {
		if (strcmp(readTutor[i].tutorID, uid) == 0) { 
			strcpy(tutorName, readTutor[i].tutorName);
			strcpy(tutorUID, readTutor[i].tutorID);
			break;
		}
	}
	system("cls");
	printf("Hi %s, please enter your old password:", tutorName);
	scanf("%s", oldPassword);

	//if password matches with password stored in struct, tutor can proceed to change account password
	for (j = 0; j < 200; j++) {
		if (readCredential[j].id != 0) {
			if ((strcmp(readCredential[j].uid, tutorUID) == 0) && (strcmp(readCredential[j].pw, oldPassword) == 0)){
				printf("Please enter your new password: ");
				scanf("%s", newPassword);
				strcpy(readCredential[j].pw, newPassword);
				system("cls");
				printf("New tutor password successfully changed to: %s", newPassword);
				printf("\n");
				return;
			}
		}
	}
	printf("Password does not match with uid!\n");
}

//-----------------------------------------------------------------------------------------------------------------------------
// student function
void studentViewList(char uid[MAX]) {
	int i = 0, j = 0, back = 0;
	char tempName[50];
	for (i = 0; i < 200; i++) {
		if (strcmp(readStd[i].studentID, uid) == 0) {
			strcpy(tempName, readStd[i].studentName);
			break;
		}
	}
	printf("List of Programming Cafe Sessions enrolled.\n");
	printf("--------------------------------------------------------------------------------------------\n");
	printf("Student Name\tSession Code\t   Tutor Code\t\tLocation\n");
	printf("--------------------------------------------------------------------------------------------\n");
	for (j = 0; j < 200; j++) {
		if (readBooked[j].id != 0) {
			if (strcmp(readBooked[j].bookedStd, tempName) == 0) {
				printf("%11s %13s %15s %21s\n", readBooked[j].bookedStd, readBooked[j].bookedSes, readBooked[j].bookedTutor, readBooked[j].bookedLocation);
			}
		}
	}
	while (1) {
		printf("\nEnter '1' to return to student menu.");
		printf("\nUser input: ");
		scanf("%d", &back);
		if (back) {
			system("cls");
			break;
		}
		else {
			printf("Invalid choice! Please try again.\n");
		}
	}
}

void studentUseEnrol(char uid[MAX]) {
	int i = 0, j = 0, k = 0, m = 0, n = 0, sesExist = 0, bookedExist = 0,sesValid = 0; 
	char sesCode[MAX], sesLocation[MAX], sesTutorCode[MAX], tempName[MAX];
	for (i = 0; i < 200; i++) {
		if (strcmp(readStd[i].studentID, uid) == 0) {
			strcpy(tempName, readStd[i].studentName);
			break;
		}
	}
	printf("List of sessions: \n\n");
	printf("--------------------------------------------------------------------------------------------------------------------\n");
	printf("Session Code\t   Title\t\tDay\t\tStart Time\t\tLocation\t\tTutor Code\n");
	printf("--------------------------------------------------------------------------------------------------------------------\n");
	for (i = 0; i < 500; i++) {
		if (readSes[i].id != 0) {
			printf("%9s %21s %15s %15s %24s %22s\n", readSes[i].sesCode, readSes[i].sesTitle, readSes[i].sesDay, readSes[i].sesTime, readSes[i].sesLocation, readSes[i].sesTutorCode);
		}
	}
	printf("\nEnter an existing Session Code to enrol:");
	scanf("%s", &sesCode);
	for (j = 0; j < 500; j++) {
		if (strcmp(readSes[j].sesCode, sesCode) == 0) {
			strcpy(sesLocation, readSes[j].sesLocation);
			strcpy(sesTutorCode, readSes[j].sesTutorCode);
			sesExist = 1;
			break;
		}
	}
	if (sesExist) {
		//to check whether session is assigned to a tutor
		for (k = 0; k < 200; k++) {
			if (strcmp(readAssigned[k].tutorID, sesTutorCode) == 0) {
				sesValid = 1;
				break;
			}
		}
		if (sesValid) {
			for (m = 0; m < 200; m++) {
				if (readBooked[m].id != 0 && (strcmp(tempName, readBooked[m].bookedStd) == 0) && (strcmp(sesCode, readBooked[m].bookedSes) == 0) && (strcmp(sesTutorCode, readBooked[m].bookedTutor) == 0) && (strcmp(sesLocation, readBooked[m].bookedLocation) == 0)) {
					bookedExist = 1;
					break;  // Stop iterating once an empty index is found

				}
			}
			if (bookedExist == 0) {
				for (n = 0; n < 200; n++) {
					if (readBooked[n].id == 0) {
						// Update the booked struct with the new booked data
						readBooked[n].id = (n + 1);
						strcpy(readBooked[n].bookedStd, tempName);
						strcpy(readBooked[n].bookedSes, sesCode);
						strcpy(readBooked[n].bookedTutor, sesTutorCode);
						strcpy(readBooked[n].bookedLocation, sesLocation);
						break;  // Stop iterating once an empty index is found

					}
				}
				system("cls");
				printf("\nRecent activity: ");
				printf("You have been enrolled into the following session successfully:");
				printf("\nStudent Name: %s", tempName);
				printf("\nEnrolled session Code: %s", sesCode);
				printf("\nSession location: %s", sesLocation);
				printf("\nTutor in charge: %s", sesTutorCode);
			}
			else {
				system("cls");
				printf("Duplicate data entry detected!\n");
				return;
			}
		}
		else {
			system("cls");
			printf("No tutor is assigned to this session!\n");
			return;
		}
	}
	else {
		system("cls");
		printf("Invalid session! Please try again.\n");
		return;
	}
}

void studentUnenrol(char uid[MAX]) {
	int i = 0, stdExist = 0, j = 0, bookedExist = 0, deleteConfirm = 0;
	char stdID[MAX], sesCode[MAX], stdName[MAX];
	for (i = 0; i < 200; i++) {
		if (strcmp(readStd[i].studentID, uid) == 0) { 
			strcpy(stdName, readStd[i].studentName); 
			break;
		}
	}
	printf("Enter session code of subject to unenroll from: ");
	scanf("%s", &sesCode);
	// to check whether booked session exists
	for (j = 0; j < 200; j++) {
		if ((strcmp(stdName, readBooked[j].bookedStd) == 0) && (strcmp(sesCode, readBooked[j].bookedSes) == 0)) {
			bookedExist = 1;
			break;  // Stop iterating once an empty index is found
		}
	}
	if (bookedExist) {
		printf("Enrolled session found!\nWould you like to be removed from session?");
		printf("\n1- Yes\n2- No\nUser Input:");
		scanf("%d", &deleteConfirm);
		if (deleteConfirm == 1) {
			readBooked[j].id = 0;
			system("cls");
			printf("Enrolled session has been removed successfully.\n");
			return;
		}
		else if (deleteConfirm == 2) {
			system("cls");
			printf("Aborting action...\n");
			return;
		}
		else {
			system("cls");
			printf("Invalid input! No actions performed.\n");
			return;
		}
	}
	else {
		system("cls");
		printf("Enrolled session not found!\n");
		return;
	}
}

void stdChangePw(char uid[MAX]) {
	int i = 0, j = 0;
	char stdName[MAX], oldPassword[MAX], newPassword[MAX];
	for (i = 0; i < 200; i++) {
		if (strcmp(readStd[i].studentID, uid) == 0) {
			strcpy(stdName, readStd[i].studentName);
			break;
		}
	}
	system("cls");
	printf("Hi %s, please enter your old password:", stdName);
	scanf("%s", oldPassword);

	//if password matches with password stored in struct, student can proceed to change account password
	for (j = 0; j < 200; j++) {
		if (readCredential[j].id != 0) {
			if ((strcmp(readCredential[j].uid, uid) == 0) && (strcmp(readCredential[j].pw, oldPassword) == 0)) {
				printf("Please enter your new password: ");
				scanf("%s", newPassword);
				strcpy(readCredential[j].pw, newPassword);
				system("cls");
				printf("New student password successfully changed to: %s", newPassword);
				printf("\n");
				return;
			}
		}
	}
	printf("Password does not match with uid!\n");
}
//-----------------------------------------------------------------------------------------------------------------------------
//write data from struct to file function

void write_tutorList() {
	FILE* tl;
	int i;
	tl = fopen("tutor.txt", "w");
	if (tl != NULL) {
		for (i = 0; i < 200; i++) {
			if (readTutor[i].id != 0) {
				fprintf(tl, "%d,%s,%s,%s,\n", readTutor[i].id, readTutor[i].tutorID, readTutor[i].tutorName, readTutor[i].tutorSubject);
			}
		}
		fclose(tl);
		printf("Tutor file successfully updated.\n");
	}
	else {
		printf("Unable to open tutor file.\n");
	}
};

void write_userList() {
	FILE* u;
	int i;
	u = fopen("user.txt", "w");
	if (u != NULL) {
		for (i = 0; i < 200; i++) {
			if (readCredential[i].id != 0) {
				fprintf(u, "%d,%s,%s,%s,\n", readCredential[i].id, readCredential[i].uid, readCredential[i].pw, readCredential[i].role);
			}
		}
		fclose(u);
		printf("User file successfully updated.\n");
	}
	else {
		printf("Unable to open user file.\n");
	}
};

void write_session() {
	FILE* ses;
	int i;
	ses = fopen("session.txt", "w");
	if (ses != NULL) {
		for (i = 0; i < 500; i++) {
			if (readSes[i].id != 0) {
				fprintf(ses, "%d,%s,%s,%s,%s,%s,%s,\n", readSes[i].id, readSes[i].sesCode, readSes[i].sesTitle, readSes[i].sesDay, readSes[i].sesTime, readSes[i].sesLocation, readSes[i].sesTutorCode);
			}
		}
		fclose(ses);
		printf("Session file successfully updated.\n");
	}
	else {
		printf("Unable to open session file.\n");
	}
};

void write_studentList() {
	FILE* std;
	int i;
	std = fopen("studentList.txt", "w");
	if (std != NULL) {
		for (i = 0; i < 200; i++) {
			if (readStd[i].id != 0) {
				fprintf(std, "%d,%s,%s,\n", readStd[i].id, readStd[i].studentName, readStd[i].studentID);
			}
		}
		fclose(std);
		printf("Student file successfully updated.\n");
	}
	else {
		printf("Unable to open student file.\n");
	}
};

void write_bookedList() {
	FILE* b;
	int i;
	b = fopen("bookedSessionList.txt", "w");
	if (b != NULL) {
		for (i = 0; i < 200; i++) {
			if (readBooked[i].id != 0) {
				fprintf(b, "%d,%s,%s,%s,%s,\n", readBooked[i].id, readBooked[i].bookedStd, readBooked[i].bookedSes, readBooked[i].bookedTutor, readBooked[i].bookedLocation);
			}
		}
		fclose(b);
		printf("Booked file successfully updated.\n");
	}
	else {
		printf("Unable to open booked file.\n");
	}
};

void write_assignedList() {
	FILE* a;
	int i;
	a = fopen("assignedList.txt", "w");
	if (a != NULL) {
		for (i = 0; i < 200; i++) {
			if (readAssigned[i].id != 0) {
				fprintf(a, "%d,%s,%s,\n", readAssigned[i].id, readAssigned[i].tutorID, readAssigned[i].tutorName);
			}
		}
		fclose(a);
		printf("Assigned List file successfully updated.\n");
	}
	else {
		printf("Unable to open Assigned List file.\n");
	}
};
//-----------------------------------------------------------------------------------------------------------------------------
//function to write data back to file before exiting program
void write_allList() {
	FILE* fp1;
	FILE* fp2;
	FILE* fp3;
	FILE* fp4;
	FILE* fp5;
	FILE* fp6;

	fp1 = fopen("tutor.txt", "r");
	write_tutorList();

	fp2 = fopen("user.txt", "r");
	write_userList();

	fp3 = fopen("session.txt", "r");
	write_session();

	fp4 = fopen("studentList.txt", "r");
	write_studentList();

	fp5 = fopen("bookedSessionList.txt", "r");
	write_bookedList();

	fp6 = fopen("assignedList.txt", "r");
	write_assignedList();
}


//-----------------------------------------------------------------------------------------------------------------------------
//main function

int main() {
	int flag = 1, mainPage, option = 0;
	init_allList();
	while (flag) {
		mainPage = menu(option);

		if (mainPage == 1) {
			detectLogin();
		}
		else if (mainPage == 2) { //to exit program
			system("color 3");
			write_allList();
			printf("\nExited program.\n");
			break;
		}
		else {
			printf("Invalid choice! Please try again.\n\n\n");
		}
	}
	return 0;
}