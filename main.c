#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#pragma warning (disable:4996)
#define MAX_STAFF 50
#define MAX_MEMBER 50
//admin login id:admin pass:hello123

typedef struct {
	int id;
	char name[99];
	char password[99];
	char gender;
	char icNum[15];
	int age;
	char phoneNum[15];
} Member;

typedef struct {
	char train_id[99]; //exp:T1001
	char departure_station[99]; //exp:KL Sentral
	char arrival_station[99]; //exp:Kampar
	int departure_time; //exp:1152
	int arrival_time; //exp:1315
	int available_seats; //exp:214
} Train;

typedef struct {
	int memberId;
	int bookingId;
	char trainId[99];
	char bookingDate[15];
	char departureDate[15];
	char departureStation[99];
	char arrivalStation[99];
	int departureTime;
	int arrivalTime;
	char ticketType[30];
	int coach;
	int quantity;
	char paymentMethod[15];
	int totalAmount;
} Book;

int memberId = 0;

void registerMember();
void loginMember();
void loginStaff();
void adminTrainSchedule();
void addTrainSchedule();
void displayTrainSchedule();
void modifyTrainSchedule();
void modifyTrainDestination();
void adminBookMenu();
void adminAnalyseBook();
void adminDisplayRecord();
void adminModifyRecord();
void memberBookMenu();
void memberTrainBook();
void memberDisplayBook();
void memberTrainBook();
void memberDisplayRecord();
void memberAccount();
void adminAccountMenu();
void adminManageStaffMenu();
void adminAddStaff();
void adminStaffList();
void adminDeleteStaff();
void adminModifyStaff();
void adminManageMember();
void adminMemberList();
void adminDeleteMember();
void adminModifyMemberMenu();
void adminModifyMemberPassword();
void adminModifyMemberPoint();
void memberCancelBook();

void registerMember() {
	Member members, check;
	char choice;
	char result = 'n';
	int latestId = 1000;
	FILE* fPtr;
	rewind(stdin);
	system("cls");
	printf("============================================================\n");
	printf("\033[30m                     REGISTER AS MEMBER\n");
	printf("\033[30m============================================================\n");
	printf("\n\033[91m         Are You Sure You Want To Register (Y/N)? ");
	printf("\033[30m");
	scanf("%c", &choice);
	if (toupper(choice) == 'Y') {
		printf("\n");
		do {
			rewind(stdin);
			printf("\033[30m  Enter Your Name                         : ");
			printf("\033[0m");
			gets(members.name);
			if (strlen(members.name) > 0) {
				int found = 0;
				for (int i = 0; i < strlen(members.name); i++) {
					if (!isalpha(members.name[i])) {
						found++;
					}
				}
				if (found == 0) {
					for (int i = 0; i < strlen(members.name); i++) {
						members.name[i] = toupper(members.name[i]);
					}
					fPtr = fopen("members.bin", "rb");
					if (fPtr == NULL) {
						result = 'y';
					}
					else {
						while (fread(&check, sizeof(Member), 1, fPtr)) {
							if (strcmp(members.name, check.name) == 0) {
								result = 'n';
								printf("\033[91m  The name is taken!\n");
								break;
							}
							else {
								result = 'y';
							}
						}
						fclose(fPtr);
					}
				}
				else {
					printf("\033[91m  Please use alphabets only!\n");
				}
			}
			else {
				printf("Please fill up!\n");
			}
		} while (result != 'y');
		do {
			rewind(stdin);
			printf("\033[30m  Enter Your Age                          : ");
			printf("\033[0m");
			scanf("%d", &members.age);
			if (members.age < 0 || members.age > 100) {
				result = 'n';
				printf("\033[91m  Please enter a valid age!\n");
			}
			else {
				result = 'y';
			}
		} while (result != 'y');
		do {
			rewind(stdin);
			printf("\033[30m  Enter Your Password                     : ");
			printf("\033[0m");
			gets(members.password);
			if (strlen(members.password) > 0) {
				result = 'y';
			}
			else {
				result = 'n';
			}
		} while (result != 'y');
		do {
			rewind(stdin);
			printf("\033[30m  Enter Your Gender (F/M)                 : ");
			printf("\033[0m");
			members.gender = getchar();
			members.gender = toupper(members.gender);
			if (members.gender != 'F' && members.gender != 'M') {
				result = 'n';
				printf("\033[91m  Invalid gender type!\n");
			}
			else {
				result = 'y';
			}
		} while (result != 'y');
		do {
			rewind(stdin);
			printf("\033[30m  Enter Your IC Number (XXXXXX-XX-XXXX)   : ");
			printf("\033[0m");
			gets(members.icNum);
			if (strlen(members.icNum) == 14) {
				if (members.icNum[6] == '-' && members.icNum[9] == '-') {
					result = 'y';
					for (int i = 0; i < 14; i++) {
						if (i != 6 && i != 9) {
							if (!isdigit(members.icNum[i])) {
								printf("\033[91m  Please enter only numbers and dashes!\n");
								result = 'n';
								break;
							}
						}
					}
				}
				else {
					printf("\033[91m  Please use the correct format!\n");
					result = 'n';
				}
			}
			else {
				printf("\033[91m  Please enter the correct format!\n");
				result = 'n';
			}
		} while (result != 'y');
		do {
			rewind(stdin);
			printf("\033[30m  Enter Your Contact Number (XXX-XXXXXXX) : ");
			printf("\033[0m");
			gets(members.phoneNum);
			if (strlen(members.phoneNum) == 11) {
				if (members.phoneNum[3] == '-') {
					result = 'y';
					for (int i = 0; i < 11; i++) {
						if (i != 3) {
							if (!isdigit(members.phoneNum[i])) {
								printf("\033[91m  Please enter only numbers and dashes\n");
								result = 'n';
								break;
							}
						}
					}
				}
				else {
					printf("\033[91m  Please enter the correct format!\n");
					result = 'n';
				}
			}
			else {
				printf("\033[91m  Please enter the correct format!\n");
				result = 'n';
			}
		} while (result != 'y');

		fPtr = fopen("members.bin", "rb");
		if (fPtr != NULL) {
			while (fread(&check, sizeof(Member), 1, fPtr)) {
				if (check.id > latestId) {
					latestId = check.id;
				}
			}
			fclose(fPtr);
		}
		members.id = latestId + 1;

		fPtr = fopen("members.bin", "a");

		fwrite(&members, sizeof(Member), 1, fPtr);
		fclose(fPtr);
		printf("\n\033[30m============================================================\n");
		printf("\033[38;2;75;177;13m             YOU HAVE SUCCESSFULLY REGISTERED!\n");
		printf("\033[30m============================================================\n\n");
	}
	system("pause");
}

void loginMember() {
	Member members, check, check2;
	FILE* fPtr;
	FILE* fPtr2;
	char result = 'n';
	char passwordCopy[99];
	int nameFound = 0;
	int choice;
	system("cls");
	printf("\033[30m============================================================\n");
	printf("\033[30m                       MEMBER LOGIN\n");
	printf("\033[30m============================================================\n\n");
	do {
		rewind(stdin);
		printf("\033[30m              Enter Name          : ");
		printf("\033[0m");
		gets(members.name);

		if (strlen(members.name) == 0) {
			printf("\033[31m                  Please enter your name!\n");
			continue;
		}

		fPtr = fopen("members.bin", "rb");
		if (fPtr == NULL) {
			printf("File not found!\n");
			exit(-1);
		}

		for (int i = 0; i < strlen(members.name); i++) {
			members.name[i] = toupper(members.name[i]);
		}

		nameFound = 0;
		while (fread(&check, sizeof(Member), 1, fPtr)) {
			if (strcmp(members.name, check.name) == 0) {
				nameFound++;
				rewind(stdin);
				printf("\033[30m              Enter Your Password : ");
				printf("\033[0m");
				gets(members.password);

				if (strlen(members.password) == 0) {
					printf("\033[31m              Please enter your password!\n");
					result = 'n';
					break;
				}

				rewind(fPtr);
				fPtr2 = fopen("members.bin", "rb");
				while (fread(&check2, sizeof(Member), 1, fPtr2)) {
					if (strcmp(members.name, check2.name) == 0) {
						strcpy(passwordCopy, check2.password);
						break;
					}
				}
				if (strcmp(members.password, passwordCopy) == 0) {
					printf("\n\033[30m============================================================\n");
					printf("\033[38;2;75;177;13m                  SUCCESSFULLY LOGGED IN!\n");
					printf("\033[30m============================================================\n\n");
					memberId = check.id;
					result = 'y';
					break;
				}
				else {
					printf("\033[31m              Wrong password!\n");
					result = 'n';
					break;
				}
				fclose(fPtr2);
			}
		}
		fclose(fPtr);

		if (nameFound == 0 && result != 'y') {
			printf("\033[31m              No such name found!\n");
			result = 'n';
		}
	} while (result != 'y');

	if (result == 'y') {
		system("pause");
		memberBookMenu();
	}
}

void loginStaff() {
	Member staffs, check, check2;
	FILE* fPtr;
	FILE* fPtr2;
	char result = 'n';
	char passwordCopy[99];
	int nameFound = 0;
	int choice;
	system("cls");
	printf("\033[30m============================================================\n");
	printf("\033[30m                        STAFF LOGIN\n");
	printf("\033[30m============================================================\n\n");
	do {
		rewind(stdin);
		printf("\033[30m              Enter Name          : ");
		printf("\033[0m");
		gets(staffs.name);

		if (strlen(staffs.name) == 0) {
			printf("\033[31m              Please enter your name!\n");
			continue;
		}

		fPtr = fopen("staffs.bin", "rb");
		if (fPtr == NULL) {
			printf("File not found!\n");
		}

		for (int i = 0; i < strlen(staffs.name); i++) {
			staffs.name[i] = toupper(staffs.name[i]);
		}

		nameFound = 0;
		while (fread(&check, sizeof(staffs), 1, fPtr)) {
			if (strcmp(staffs.name, check.name) == 0) {
				nameFound++;
				rewind(stdin);
				printf("\033[30m              Enter Your Password : ");
				printf("\033[0m");
				gets(staffs.password);

				if (strlen(staffs.password) == 0) {
					printf("\033[31m              Please enter your password!\n");
					result = 'n';
					break;
				}

				rewind(fPtr);
				fPtr2 = fopen("staffs.bin", "rb");
				while (fread(&check2, sizeof(Member), 1, fPtr2)) {
					if (strcmp(staffs.name, check2.name) == 0) {
						strcpy(passwordCopy, check2.password);
						break;
					}
				}
				if (strcmp(staffs.password, passwordCopy) == 0) {
					printf("\n\033[30m============================================================\n");
					printf("\033[38;2;75;177;13m                  SUCCESSFULLY LOGGED IN!\n");
					printf("\033[30m============================================================\n\n");
					result = 'y';
					break;
				}
				else {
					printf("\033[31m              Wrong password!\n");
					result = 'n';
					break;
				}
				fclose(fPtr2);
			}
		}
		fclose(fPtr);

		if (nameFound == 0 && result != 'y') {
			printf("\033[31m              No such name found!\n");
			result = 'n';
			continue;
		}
	} while (result != 'y');

	if (result == 'y') {
		system("pause");
		system("cls");
		do {
			system("cls");
			printf("\033[30m============================================================\n");
			printf("\033[30m                        ADMIN PANEL\n");
			printf("\033[30m============================================================\n");
			printf("\n\033[0;35m                ENTER [1] -> TRAIN SCHEDULE\n");
			printf("\033[0;35m                ENTER [2] -> TRAIN BOOKING\n");
			printf("\033[0;35m                ENTER [3] -> ACCOUNT MANAGE\n");
			printf("\033[0;35m                ENTER [4] -> LOGOUT\n\n");
			rewind(stdin);
			printf("\033[30m                Enter Your Choice: ");
			scanf("%d", &choice);
			switch (choice) {
			case 1: adminTrainSchedule(); break;
			case 2: adminBookMenu(); break;
			case 3: adminAccountMenu(); break;
			case 4:
				printf("\n============================================================\n");
				printf("\033[31m                          LOGGING OUT...\n");
				printf("\033[30m============================================================\n\n");
				system("pause");
				break;
			default:
				printf("\n============================================================\n");
				printf("\033[31m                      INVALID CHOICE!\n");
				printf("\033[30m============================================================\n\n");
				system("pause");
			}
		} while (choice != 4);
	}
}

void main() {
	int choice;
	do {
		system("cls");
		printf("============================================================\n");
		printf("             WELCOME TO TBS BUS TICKETING SYSTEM\n");
		printf("============================================================\n\n");
		printf("\033[0;35m               ENTER [1] -> REGISTER AS MEMBER\n");
		printf("\033[0;35m               ENTER [2] -> LOGIN AS MEMBER\n");
		printf("\033[0;35m               ENTER [3] -> LOGIN AS STAFF\n");
		printf("\033[0;35m               ENTER [4] -> EXIT\n\n");
		rewind(stdin);
		printf("\033[30m               Enter Your Choice: ");
		scanf("%d", &choice);
		switch (choice) {
		case 1: registerMember(); break;
		case 2: loginMember(); break;
		case 3: loginStaff(); break;
		}
	} while (choice != 4);
}

void adminTrainSchedule() {
	int choice;

	do {
		system("cls");
		printf("============================================================\n");
		printf("\033[30m                 TRAIN SCHEDULE MANAGEMENT\n");
		printf("\033[30m============================================================\n\n");
		printf("\033[0;35m              ENTER [1] -> ADD TRAIN SCHEDULE\n");
		printf("\033[0;35m              ENTER [2] -> DISPLAY TRAIN SCHEDULE\n");
		printf("\033[0;35m              ENTER [3] -> MODIFY TRAIN DESTINATION\n");
		printf("\033[0;35m              ENTER [4] -> MODIFY TRAIN SCHEDULE\n");
		printf("\033[0;35m              ENTER [5] -> EXIT\n\n");
		rewind(stdin);
		printf("\033[30m              Enter Your Choice: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			addTrainSchedule();
			break;
		case 2:
			displayTrainSchedule();
			break;
		case 3:
			modifyTrainDestination();
			break;
		case 4:
			modifyTrainSchedule();
			break;
		case 5:
			printf("\n============================================================\n");
			printf("\033[31m                          EXITING...\033[30m\n");
			printf("============================================================\n\n");
			system("pause");
			break;
		default:
			printf("\n============================================================\n");
			printf("\033[31m        INVALID CHOICE. PLEASE ENTER A VALID OPTION.\033[30m\n");
			printf("============================================================\n");
			system("pause");
		}
	} while (choice != 5);
}

void addTrainSchedule() {

	Train new_Train, temp;
	char result = 'n';
	FILE* fPtr;
	int found = 0;
	system("cls");
	printf("============================================================\n");
	printf("\033[30m                     ADD TRAIN SCHEDULE\n");
	printf("\033[30m============================================================\n");

	rewind(stdin);
	do {
		found = 0;
		printf("\n               Enter Train ID (Txxxx)      : ");
		scanf("%[^\n]", &new_Train.train_id);
		rewind(stdin);

		for (int i = 0; i < strlen(new_Train.train_id); i++) {
			new_Train.train_id[i] = toupper(new_Train.train_id[i]);
		}

		fPtr = fopen("train_schedule.txt", "r");
		if (fPtr != NULL) {
			while (fscanf(fPtr, "%[^|]|%[^|]|%[^|]|%d|%d|%d\n", &temp.train_id, &temp.departure_station, &temp.arrival_station, &temp.departure_time, &temp.arrival_time, &temp.available_seats) != EOF) {
				if (strcmp(new_Train.train_id, temp.train_id) == 0) {
					found++;
				}
			}
			fclose(fPtr);
		}
		if (found != 0) {
			printf("\033[31m               Train ID already exist!\033[30m\n");
			result = 'n';
		}
		else if (strlen(new_Train.train_id) != 5 || new_Train.train_id[0] != 'T' || !isdigit(new_Train.train_id[1]) || !isdigit(new_Train.train_id[2])
			|| !isdigit(new_Train.train_id[3]) || !isdigit(new_Train.train_id[4])) {
			printf("\033[31m               Invalid Format\033[30m\n");
			result = 'n';
		}
		else {
			result = 'y';
		}

	} while (result != 'y');

	printf("               Enter Departure Station     : ");
	scanf("%[^\n]", &new_Train.departure_station);
	rewind(stdin);

	printf("               Enter Arrival Station       : ");
	scanf("%[^\n]", &new_Train.arrival_station);
	rewind(stdin);

	do {
		printf("               Enter Departure Time (HHMM) : ");
		scanf("%d", &new_Train.departure_time);
		rewind(stdin);

		if (new_Train.departure_time < 0000 || new_Train.departure_time > 2359) {
			printf("\033[31m               Invalid time!\033[30m\n");
		}

	} while (new_Train.departure_time < 0000 || new_Train.departure_time > 2359);

	do {
		printf("               Enter Arrival Time (HHMM)   : ");
		scanf("%d", &new_Train.arrival_time);
		rewind(stdin);

		if (new_Train.arrival_time < 0000 || new_Train.departure_time > 2359) {
			printf("\033[31m               Invalid time!\033[30m\n");
		}
	} while (new_Train.arrival_time < 0000 || new_Train.departure_time > 2359);

	printf("               Enter Available Seats       : ");
	scanf("%d", &new_Train.available_seats);
	rewind(stdin);

	FILE* fp = fopen("train_schedule.txt", "a");
	if (fp == NULL) {
		printf("Error opening file!\n");
		return;
	}

	fprintf(fp, "%s|%s|%s|%d|%d|%d\n", new_Train.train_id, new_Train.departure_station, new_Train.arrival_station, new_Train.departure_time, new_Train.arrival_time, new_Train.available_seats);

	printf("\n============================================================\n");
	printf("\033[38;2;75;177;13m             TRAIN DETAILS ADDED SUCCESSFULLY!\n");
	printf("\033[30m============================================================\n");
	system("pause");

	fclose(fp);

	displayTrainSchedule();
}

void displayTrainSchedule() {
	memberDisplayBook();
	system("pause");
}

void modifyTrainSchedule() {
	char trainID[99];
	FILE* fp;
	Train new_Train;
	Train trains;
	char con;

	fp = fopen("train_schedule.txt", "r");
	system("cls");
	printf("==============================================================\n");
	printf("\033[30m                    MODIFY TRAIN SCHEDULE\n");
	printf("\033[30m==============================================================\n\n");
	printf("| %-5s | %-20s | %-20s | %s |\n", "TRAIN", "     DEPARTURE", "      ARRIVAL", "SEAT");
	if (fp != NULL) {
		while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%d|%d|%d\n", &trains.train_id, &trains.departure_station, &trains.arrival_station, &trains.departure_time, &trains.arrival_time, &trains.available_seats) != EOF) {
			double newDepTime = 0.0;
			double newArrTime = 0.0;
			char time[3] = "AM";
			char time2[3] = "AM";
			if (trains.departure_time > 1299) {
				newDepTime = ((double)trains.departure_time - 1200) / 100;
				strcpy(time, "PM");
			}
			else if (trains.departure_time >= 1200) {
				newDepTime = ((double)trains.departure_time) / 100;
				strcpy(time, "PM");
			}
			else {
				newDepTime = ((double)trains.departure_time) / 100;
				strcpy(time, "AM");
			}

			if (trains.arrival_time > 1299) {
				newArrTime = ((double)trains.arrival_time - 1200) / 100;
				strcpy(time2, "PM");
			}
			else if (trains.arrival_time >= 1200) {
				newArrTime = ((double)trains.arrival_time) / 100;
				strcpy(time2, "PM");
			}
			else {
				newArrTime = ((double)trains.arrival_time) / 100;
				strcpy(time2, "AM");
			}

			printf("\033[0;35m| %-5s | %-11s(%5.2f%s) | %-11s(%5.2f%s) | %-4d |\033[30m\n", trains.train_id, trains.departure_station, newDepTime, time, trains.arrival_station, newArrTime, time2, trains.available_seats);
		}
		fclose(fp);
		printf("\n==============================================================\n");
	}
	do {
		con = 'n';
		printf("                Enter Train ID To Modify: ");
		scanf("%s", trainID);

		trainID[0] = toupper(trainID[0]);

		FILE* fp2;
		Train current_Train;

		fp2 = fopen("train_schedule.txt", "r+");
		if (fp2 == NULL) {
			printf("Error opening file!\n");
			return;
		}

		int found = 0;
		FILE* tempFile = fopen("temp_schedule.txt", "w");
		if (tempFile == NULL) {
			printf("Error creating temporary file!\n");
			fclose(fp2);
			return;
		}

		while (fscanf(fp2, "%[^|]|%[^|]|%[^|]|%d|%d|%d\n",
			current_Train.train_id,
			current_Train.departure_station,
			current_Train.arrival_station,
			&current_Train.departure_time,
			&current_Train.arrival_time,
			&current_Train.available_seats) != EOF) {

			if (strcmp(current_Train.train_id, trainID) == 0) {
				found = 1;
				printf("\033[31m                Train found!\033[30m\n");

				printf("                Enter New Departure Time (HHMM): ");
				scanf("%d", &current_Train.departure_time);

				printf("                Enter New Arrival Time (HHMM)  : ");
				scanf("%d", &current_Train.arrival_time);

				fprintf(tempFile, "%s|%s|%s|%d|%d|%d\n",
					current_Train.train_id,
					current_Train.departure_station,
					current_Train.arrival_station,
					current_Train.departure_time,
					current_Train.arrival_time,
					current_Train.available_seats);

				con = 'y';
				printf("\n==============================================================\n");
				printf("\033[38;2;75;177;13m            TRAIN SCHEDULE MODIFIED SUCCESSFULLY!\033[30m\n");
				printf("==============================================================\n");
			}
			else {
				fprintf(tempFile, "%s|%s|%s|%d|%d|%d\n",
					current_Train.train_id,
					current_Train.departure_station,
					current_Train.arrival_station,
					current_Train.departure_time,
					current_Train.arrival_time,
					current_Train.available_seats);
			}
		}

		fclose(fp2);
		fclose(tempFile);

		remove("train_schedule.txt");
		rename("temp_schedule.txt", "train_schedule.txt");

		if (!found) {
			printf("\033[31m                Train not found with the given ID!\033[30m\n");

		}

	} while (con != 'y');
	system("pause");
}

void modifyTrainDestination() {
	char trainID[99];
	FILE* fp;
	Train trains;
	char con;

	fp = fopen("train_schedule.txt", "r");
	system("cls");
	printf("==============================================================\n");
	printf("\033[30m                   MODIFY TRAIN DESTINATIONS\n");
	printf("\033[30m==============================================================\n\n");
	printf("| %-5s | %-20s | %-20s | %s |\n", "TRAIN", "     DEPARTURE", "      ARRIVAL", "SEAT");
	if (fp != NULL) {
		while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%d|%d|%d\n", &trains.train_id, &trains.departure_station, &trains.arrival_station, &trains.departure_time, &trains.arrival_time, &trains.available_seats) != EOF) {
			double newDepTime = 0.0;
			double newArrTime = 0.0;
			char time[3] = "AM";
			char time2[3] = "AM";
			if (trains.departure_time > 1299) {
				newDepTime = ((double)trains.departure_time - 1200) / 100;
				strcpy(time, "PM");
			}
			else if (trains.departure_time >= 1200) {
				newDepTime = ((double)trains.departure_time) / 100;
				strcpy(time, "PM");
			}
			else {
				newDepTime = ((double)trains.departure_time) / 100;
				strcpy(time, "AM");
			}

			if (trains.arrival_time > 1299) {
				newArrTime = ((double)trains.arrival_time - 1200) / 100;
				strcpy(time2, "PM");
			}
			else if (trains.arrival_time >= 1200) {
				newArrTime = ((double)trains.arrival_time) / 100;
				strcpy(time2, "PM");
			}
			else {
				newArrTime = ((double)trains.arrival_time) / 100;
				strcpy(time2, "AM");
			}

			printf("\033[0;35m| %-5s | %-11s(%5.2f%s) | %-11s(%5.2f%s) | %-4d |\033[30m\n", trains.train_id, trains.departure_station, newDepTime, time, trains.arrival_station, newArrTime, time2, trains.available_seats);
		}
		fclose(fp);
		printf("\n==============================================================\n\n");
	}
	do {
		con = 'n';
		printf("              Enter Train ID To Modify    : ");
		scanf("%s", trainID);

		trainID[0] = toupper(trainID[0]);
		FILE* fp2;
		Train temp, temp2;

		fp2 = fopen("train_schedule.txt", "r+");
		if (fp2 == NULL) {
			printf("Error opening file!\n");
			exit(-1);
		}

		FILE* tempFile = fopen("temp_schedule.txt", "w");
		if (tempFile == NULL) {
			printf("Error creating temporary file!\n");
			exit(-1);
		}

		int found = 0;

		while (fscanf(fp2, "%[^|]|%[^|]|%[^|]|%d|%d|%d\n",
			&temp.train_id,
			&temp.departure_station,
			&temp.arrival_station,
			&temp.departure_time,
			&temp.arrival_time,
			&temp.available_seats) != EOF) {
			if (strcmp(temp.train_id, trainID) == 0) {
				found = 1;
				printf("\033[31m              Train found!\033[30m\n");
				printf("              Enter New Departure Station : ");
				scanf(" %[^\n]", &temp2.departure_station);
				printf("              Enter New Arrival Station   : ");
				scanf(" %[^\n]", &temp2.arrival_station);

				fprintf(tempFile, "%s|%s|%s|%d|%d|%d\n",
					temp.train_id,
					temp2.departure_station,
					temp2.arrival_station,
					temp.departure_time,
					temp.arrival_time,
					temp.available_seats);

				con = 'y';
				printf("\n==============================================================\n");
				printf("\033[38;2;75;177;13m           TRAIN DESTINATION MODIFIED SUCCESSFULLY!\033[30m\n");
				printf("==============================================================\n");
			}
			else {
				fprintf(tempFile, "%s|%s|%s|%d|%d|%d\n",
					temp.train_id,
					temp.departure_station,
					temp.arrival_station,
					temp.departure_time,
					temp.arrival_time,
					temp.available_seats);
			}
		}
		fclose(fp2);
		fclose(tempFile);

		remove("train_schedule.txt");
		rename("temp_schedule.txt", "train_schedule.txt");

		if (found == 0) {
			printf("\033[31m              Train not found with the given ID!\033[30m\n");
		}
	} while (con != 'y');
	system("pause");
}

void adminBookMenu() {
	int choice;

	do {
		system("cls");
		printf("============================================================\n");
		printf("\033[30m                  TRAIN BOOKING MANAGEMENT\n");
		printf("\033[30m============================================================\n\n");
		printf("\033[0;35m            ENTER [1] -> DISPLAY BOOKING RECORD\n");
		printf("            ENTER [2] -> MODIFY BOOKING RECORD\n");
		printf("            ENTER [3] -> ANAYLSE BOOKING RECORD\n");
		printf("            ENTER [4] -> EXIT\033[30m\n");
		rewind(stdin);
		printf("\n\033[30m            Enter Your Choice: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			adminDisplayRecord();
			system("pause");
			break;
		case 2:
			adminModifyRecord();
			break;
		case 3:
			adminAnalyseBook();
			break;
		case 4:
			printf("\n============================================================\n");
			printf("\033[31m                          EXITING...\033[30m\n");
			printf("============================================================\n\n");
			system("pause");
			break;
		default:
			printf("\n============================================================\n");
			printf("\033[31m        INVALID CHOICE. PLEASE ENTER A VALID OPTION.\033[30m\n");
			printf("============================================================\n");
			system("pause");
		}
	} while (choice != 4);
}

void adminDisplayRecord() {
	Book temp;
	Train trains;
	FILE* fPtr;
	char result = 'n';
	char trainId[6];
	int count = 0;
	memberDisplayBook();
	do {
		fPtr = fopen("train_schedule.txt", "r");
		rewind(stdin);
		printf("                 Select Train ID To View: ");
		scanf("%[^\n]", &trainId);

		for (int i = 0; i < strlen(trainId); i++) {
			trainId[i] = toupper(trainId[i]);
		}

		if (fPtr != NULL) {
			while (fscanf(fPtr, "%[^|]|%[^|]|%[^|]|%d|%d|%d\n", &trains.train_id, &trains.departure_station, &trains.arrival_station,
				&trains.departure_time, &trains.arrival_time, &trains.available_seats) != EOF) {
				if (strcmp(trainId, trains.train_id) == 0) {
					count++;
				}
			}
			fclose(fPtr);
			if (count > 0) {
				result = 'y';
				break;
			}
			else {
				printf("\033[31m                 Invalid train id!\033[30m\n");
				result = 'n';
			}
		}
	} while (result != 'y');
	system("cls");
	printf("==================================================================================================================\n");
	printf("                                                  BOOKING RECORD\n");
	printf("==================================================================================================================\n");
	fPtr = fopen("booking.txt", "r");
	printf("%-10s %-11s %-9s %-11s %-10s %-8s %-12s %-5s %-8s %-14s %-10s\n", "MEMBER ID", "BOOKING ID", "TRAIN ID", "DATE", "DEPARTURE", "ARRIVAL", "TICKRT TYPE", "COACH", "QUANTITY", "PAYMENT", "AMOUNT");
	if (fPtr != NULL) {
		count = 0;
		while (fscanf(fPtr, "%d|%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%[^|]|%d\n", &temp.memberId,
			&temp.bookingId, &temp.trainId, &temp.bookingDate, &temp.departureStation,
			&temp.arrivalStation, &temp.ticketType, &temp.coach, &temp.quantity, &temp.paymentMethod,
			&temp.totalAmount) != EOF) {
			if (strcmp(trainId, temp.trainId) == 0) {
				printf("\033[0;35m%-10d %-11d %-9s %-11s %-10s %-8s %-12s %-5d %-8d %-14s %-10d\033[0;30m\n",
					temp.memberId, temp.bookingId, temp.trainId, temp.bookingDate,
					temp.departureStation, temp.arrivalStation, temp.ticketType,
					temp.coach, temp.quantity, temp.paymentMethod, temp.totalAmount);
				count++;
			}
		}
		printf("==================================================================================================================\n");
		fclose(fPtr);
		if (count == 0) {
			printf("\033[31m                                                    No data found!\033[30m\n\n");
		}
	}
}

void adminModifyRecord() {
	Book temp, temp2, input;
	Train trains;
	FILE* fPtr;
	FILE* fPtr2;
	char result = 'n';
	int count = 0;
	int bookingId;
	int type, select2;
	int ticketPrice[6] = { 55, 15, 70, 50, 25 };
	memberDisplayBook();
	do {
		fPtr = fopen("train_schedule.txt", "r");
		rewind(stdin);
		printf("                 Select Train ID To View: ");
		scanf("%[^\n]", &input.trainId);

		for (int i = 0; i < strlen(input.trainId); i++) {
			input.trainId[i] = toupper(input.trainId[i]);
		}

		if (fPtr != NULL) {
			count = 0;
			while (fscanf(fPtr, "%[^|]|%[^|]|%[^|]|%d|%d|%d\n", &trains.train_id, &trains.departure_station, &trains.arrival_station,
				&trains.departure_time, &trains.arrival_time, &trains.available_seats) != EOF) {
				if (strcmp(input.trainId, trains.train_id) == 0) {
					count++;
				}
			}
			fclose(fPtr);
			if (count > 0) {
				result = 'y';
				break;
			}
			else {
				printf("\033[31m                 Invalid Train ID!\033[30m\n");
				result = 'n';
			}
		}
	} while (result != 'y');
	fPtr = fopen("booking.txt", "r");
	int found = 0;
	if (fPtr != NULL) {
		found = 0;
		while (fscanf(fPtr, "%d|%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%[^|]|%d\n", &temp.memberId,
			&temp.bookingId, &temp.trainId, &temp.bookingDate, &temp.departureStation,
			&temp.arrivalStation, &temp.ticketType, &temp.coach, &temp.quantity, &temp.paymentMethod,
			&temp.totalAmount) != EOF) {
			if (strcmp(input.trainId, temp.trainId) == 0) {
				found++;
			}
		}
		fclose(fPtr);
		if (found > 0) {
			system("cls");
			printf("==================================================================================================================\n");
			printf("                                                  BOOKING RECORD\n");
			printf("==================================================================================================================\n");
			fPtr = fopen("booking.txt", "r");
			printf("%-10s %-11s %-9s %-11s %-10s %-8s %-12s %-5s %-8s %-14s %-10s\n", "MEMBER ID", "BOOKING ID", "TRAIN ID", "DATE", "DEPARTURE", "ARRIVAL", "TICKET TYPE", "COACH", "QUANTITY", "PAYMENT", "AMOUNT");
			if (fPtr != NULL) {
				while (fscanf(fPtr, "%d|%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%[^|]|%d\n", &temp.memberId,
					&temp.bookingId, &temp.trainId, &temp.bookingDate, &temp.departureStation,
					&temp.arrivalStation, &temp.ticketType, &temp.coach, &temp.quantity, &temp.paymentMethod,
					&temp.totalAmount) != EOF) {
					if (strcmp(input.trainId, temp.trainId) == 0) {
						printf("\033[0;35m%-10d %-11d %-9s %-11s %-10s %-8s %-12s %-5d %-8d %-14s %-10d\033[30m\n",
							temp.memberId, temp.bookingId, temp.trainId, temp.bookingDate,
							temp.departureStation, temp.arrivalStation, temp.ticketType,
							temp.coach, temp.quantity, temp.paymentMethod, temp.totalAmount);
						count++;
					}
				}
				fclose(fPtr);
				if (count == 0) {
					printf("\033[31m                 Invalid train id!\033[30m\n");
				}
			}
			count = 0;
			do {
				fPtr = fopen("booking.txt", "r");
				rewind(stdin);
				printf("==================================================================================================================\n");
				printf("                                          Select booking id to modify: ");
				scanf("%d", &input.bookingId);

				if (fPtr != NULL) {
					while (fscanf(fPtr, "%d|%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%[^|]|%d\n", &temp.memberId,
						&temp.bookingId, &temp.trainId, &temp.bookingDate, &temp.departureStation,
						&temp.arrivalStation, &temp.ticketType, &temp.coach, &temp.quantity, &temp.paymentMethod,
						&temp.totalAmount) != EOF) {
						if (input.bookingId == temp.bookingId) {
							count++;
						}
					}
					fclose(fPtr);
					if (count > 0) {
						result = 'y';
						break;
					}
					else {
						printf("\033[31m                 Invalid train id!\033[30m\n");
						result = 'n';
					}
				}
			} while (result != 'y');

			if (result == 'y') {
				system("cls");
				printf("==================================================================================================================\n");
				printf("                                               ORIGINAL DETAILS\n");
				printf("==================================================================================================================\n");
				printf("%-10s %-11s %-9s %-11s %-10s %-8s %-12s %-5s %-8s %-14s %-10s\n", "MEMBER ID", "BOOKING ID", "TRAIN ID", "DATE", "DEPARTURE", "ARRIVAL", "TICKRT TYPE", "COACH", "QUANTITY", "PAYMENT", "AMOUNT");
				fPtr = fopen("booking.txt", "r");
				while (fscanf(fPtr, "%d|%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%[^|]|%d\n", &temp.memberId,
					&temp.bookingId, &temp.trainId, &temp.bookingDate, &temp.departureStation,
					&temp.arrivalStation, &temp.ticketType, &temp.coach, &temp.quantity, &temp.paymentMethod,
					&temp.totalAmount) != EOF) {
					if (input.bookingId == temp.bookingId) {
						printf("\033[0;35m%-10d %-11d %-9s %-11s %-10s %-8s %-12s %-5d %-8d %-14s %-10d\033[30m\n",
							temp.memberId, temp.bookingId, temp.trainId, temp.bookingDate,
							temp.departureStation, temp.arrivalStation, temp.ticketType,
							temp.coach, temp.quantity, temp.paymentMethod, temp.totalAmount);
						break;
					}
				}
				fclose(fPtr);
				printf("==================================================================================================================\n");
				printf("                                                     EDITING\n");
				printf("==================================================================================================================\n");
				do {
					printf("                                                   Ticket Type\n\n");
					printf("\033[0;35m                                             ENTER [1] -> Sleeper\n");
					printf("\033[0;35m                                             ENTER [2] -> Off-Peak\n");
					printf("\033[0;35m                                             ENTER [3] -> First Class\n");
					printf("\033[0;35m                                             ENTER [4] -> Business Class\n");
					printf("\033[0;35m                                             ENTER [5] -> Economy Class\n");
					rewind(stdin);
					printf("\n\033[30m                                             Select Your Type               : ");
					scanf("%d", &type);
					switch (type) {
					case 1: strcpy(input.ticketType, "Sleeper"); result = 'y'; break;
					case 2: strcpy(input.ticketType, "Off-peak"); result = 'y'; break;
					case 3: strcpy(input.ticketType, "First Class"); result = 'y'; break;
					case 4: strcpy(input.ticketType, "Business"); result = 'y'; break;
					case 5: strcpy(input.ticketType, "Economy"); result = 'y'; break;
					default:
						printf("                                             \033[31mInvalid ticket type!\033[30m\n");
					}
				} while (result != 'y');


				do {
					rewind(stdin);
					printf("                                             Select Your Coach (1-10)       : ");
					scanf("%d", &input.coach);
				} while (input.coach < 0 || input.coach > 10);

				rewind(stdin);
				printf("                                             Enter Quantity You Want To Book: ");
				scanf("%d", &input.quantity);

				input.totalAmount = 0;

				if (strcmp(input.ticketType, "Sleeper") == 0) {
					input.totalAmount = ticketPrice[0] * input.quantity;
				}
				else if (strcmp(input.ticketType, "Off-peak") == 0) {
					input.totalAmount = ticketPrice[1] * input.quantity;
				}
				else if (strcmp(input.ticketType, "First Class") == 0) {
					input.totalAmount = ticketPrice[2] * input.quantity;
				}
				else if (strcmp(input.ticketType, "Business") == 0) {
					input.totalAmount = ticketPrice[3] * input.quantity;
				}
				else if (strcmp(input.ticketType, "Economy") == 0) {
					input.totalAmount = ticketPrice[4] * input.quantity;
				}

				do {
					printf("\n                                    Which Payment Method Do You Wish To Use?\n\n");
					printf("\033[0;35m                                            ENTER [1] -> Credit Card\n");
					printf("\033[0;35m                                            ENTER [2] -> Debit Card\n");
					printf("\033[0;35m                                            ENTER [3] -> E-Wallet\n");
					printf("\033[0;35m                                            ENTER [4] -> Bank Transfer\033[30m\n");
					rewind(stdin);
					printf("\n                                            Select Your Payment Method (1-4): ");
					scanf("%d", &select2);
					switch (select2) {
					case 1: strcpy(input.paymentMethod, "Credit Card"); result = 'y'; break;
					case 2: strcpy(input.paymentMethod, "Debit Card"); result = 'y'; break;
					case 3: strcpy(input.paymentMethod, "E-Wallet"); result = 'y'; break;
					case 4: strcpy(input.paymentMethod, "Bank Transfer"); result = 'y'; break;
					default: printf("                                            \033[31mInvalid payment method!\033[30m\n");
					}
				} while (result != 'y');
				printf("\n                                            Payment Method: %s\n", input.paymentMethod);
				printf("                                            Total Payment: RM %d\n", input.totalAmount);
				printf("\n==================================================================================================================\n");
				printf("                                                  \033[38;2;75;177;13mEDIT SUCCESSFULLY!\033[30m\n");
				printf("==================================================================================================================\n");
				system("pause");
			}

			fPtr = fopen("booking.txt", "r");
			fPtr2 = fopen("tempBooking.txt", "w");
			if (fPtr != NULL && fPtr2 != NULL) {
				while (fscanf(fPtr, "%d|%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%[^|]|%d\n", &temp2.memberId,
					&temp2.bookingId, &temp2.trainId, &temp2.bookingDate, &temp2.departureStation,
					&temp2.arrivalStation, &temp2.ticketType, &temp2.coach, &temp2.quantity, &temp2.paymentMethod,
					&temp2.totalAmount) != EOF) {
					if (input.bookingId == temp2.bookingId) {
						fprintf(fPtr2, "%d|%d|%s|%s|%s|%s|%s|%d|%d|%s|%d\n", temp2.memberId, temp2.bookingId,
							temp2.trainId, temp2.bookingDate, temp2.departureStation, temp2.arrivalStation,
							input.ticketType, input.coach, input.quantity, input.paymentMethod, input.totalAmount);
					}
					else {
						fprintf(fPtr2, "%d|%d|%s|%s|%s|%s|%s|%d|%d|%s|%d\n", temp2.memberId, temp2.bookingId,
							temp2.trainId, temp2.bookingDate, temp2.departureStation, temp2.arrivalStation,
							temp2.ticketType, temp2.coach, temp2.quantity, temp2.paymentMethod, temp2.totalAmount);
					}
				}
				fclose(fPtr);
				fclose(fPtr2);
				remove("booking.txt");
				rename("tempBooking.txt", "booking.txt");
				printf("Successfully modified!\n");
			}
		}
		else {
			printf("\033[31m                 No booking record found!\033[30m\n");
			system("pause");
		}
	}
	else {
		printf("\033[31m                 No booking record found!\033[30m\n");
		system("pause");
	}

}

void adminAnalyseBook() {
	FILE* fPtr;
	FILE* fPtr2;
	Book temp2, temp;
	Train trains;
	int count[50] = { 0 };
	int totalSeatBooked[50] = { 0 };
	int total[50] = { 0 };
	int i = 0;
	int highest = 0;
	int highestSeat = 0;
	int highestEarn = 0;
	int numOfTrains = 0;
	char highestBookTrain[7] = "";
	char highestBookTrainSeat[7] = "";
	char highestEarnTrain[7] = "";
	int j = 0;
	int tempCount = 0;

	fPtr = fopen("train_schedule.txt", "r");
	if (fPtr != NULL) {
		while (fscanf(fPtr, "%[^|]|%[^|]|%[^|]|%d|%d|%d\n", &trains.train_id, &trains.departure_station, &trains.arrival_station, &trains.departure_time, &trains.arrival_time, &trains.available_seats) != EOF) {
			fPtr2 = fopen("booking.txt", "r");
			if (fPtr2 != NULL) {
				while (fscanf(fPtr2, "%d|%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%[^|]|%d\n", &temp.memberId,
					&temp.bookingId, &temp.trainId, &temp.bookingDate, &temp.departureStation,
					&temp.arrivalStation, &temp.ticketType, &temp.coach, &temp.quantity, &temp.paymentMethod,
					&temp.totalAmount) != EOF) {
					if (strcmp(temp.trainId, trains.train_id) == 0) {
						count[i]++;
					}
				}
				fclose(fPtr2);
			}
			i++;
		}
		numOfTrains = i;
		fclose(fPtr);
	}

	fPtr = fopen("train_schedule.txt", "r");
	if (fPtr != NULL) {
		while (fscanf(fPtr, "%[^|]|%[^|]|%[^|]|%d|%d|%d\n", &trains.train_id, &trains.departure_station, &trains.arrival_station, &trains.departure_time, &trains.arrival_time, &trains.available_seats) != EOF) {
			if (count[j] > highest) {
				highest = count[j];
				strcpy(highestBookTrain, trains.train_id);
			}
			j++;
		}
		fclose(fPtr);
	}

	fPtr = fopen("train_schedule.txt", "r");
	if (fPtr != NULL) {
		while (fscanf(fPtr, "%[^|]|%[^|]|%[^|]|%d|%d|%d\n", &trains.train_id, &trains.departure_station, &trains.arrival_station, &trains.departure_time, &trains.arrival_time, &trains.available_seats) != EOF) {
			fPtr2 = fopen("booking.txt", "r");
			if (fPtr2 != NULL) {
				while (fscanf(fPtr2, "%d|%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%[^|]|%d\n", &temp.memberId,
					&temp.bookingId, &temp.trainId, &temp.bookingDate, &temp.departureStation,
					&temp.arrivalStation, &temp.ticketType, &temp.coach, &temp.quantity, &temp.paymentMethod,
					&temp.totalAmount) != EOF) {
					if (strcmp(temp.trainId, trains.train_id) == 0) {
						totalSeatBooked[i] += temp.quantity;
					}

				}
				fclose(fPtr2);
			}
			i++;
		}
		fclose(fPtr);
	}

	fPtr = fopen("train_schedule.txt", "r");
	if (fPtr != NULL) {
		while (fscanf(fPtr, "%[^|]|%[^|]|%[^|]|%d|%d|%d\n", &trains.train_id, &trains.departure_station, &trains.arrival_station, &trains.departure_time, &trains.arrival_time, &trains.available_seats) != EOF) {
			if (totalSeatBooked[j] > highestSeat) {
				highestSeat = totalSeatBooked[j];
				strcpy(highestBookTrainSeat, trains.train_id);
			}
			j++;
		}
		fclose(fPtr);
	}

	fPtr = fopen("train_schedule.txt", "r");
	if (fPtr != NULL) {
		while (fscanf(fPtr, "%[^|]|%[^|]|%[^|]|%d|%d|%d\n", &trains.train_id, &trains.departure_station, &trains.arrival_station, &trains.departure_time, &trains.arrival_time, &trains.available_seats) != EOF) {
			fPtr2 = fopen("booking.txt", "r");
			if (fPtr2 != NULL) {
				while (fscanf(fPtr2, "%d|%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%[^|]|%d\n", &temp.memberId,
					&temp.bookingId, &temp.trainId, &temp.bookingDate, &temp.departureStation,
					&temp.arrivalStation, &temp.ticketType, &temp.coach, &temp.quantity, &temp.paymentMethod,
					&temp.totalAmount) != EOF) {
					if (strcmp(temp.trainId, trains.train_id) == 0) {
						total[i] += temp.totalAmount;
					}

				}
				fclose(fPtr2);
			}
			i++;
		}
		fclose(fPtr);
	}

	fPtr = fopen("train_schedule.txt", "r");
	if (fPtr != NULL) {
		while (fscanf(fPtr, "%[^|]|%[^|]|%[^|]|%d|%d|%d\n", &trains.train_id, &trains.departure_station, &trains.arrival_station, &trains.departure_time, &trains.arrival_time, &trains.available_seats) != EOF) {
			if (total[j] > highestEarn) {
				highestEarn = total[j];
				strcpy(highestEarnTrain, trains.train_id);
			}
			j++;
		}
		fclose(fPtr);
	}
	system("cls");
	printf("============================================================\n");
	printf("                   ANAYLSE BOOKING RECORD\n");
	printf("============================================================\n");
	printf("\n\033[0;35m                   Highest Member Booked\n");
	printf("                   Train ID     : %s\n", highestBookTrain);
	printf("                   Member Booked: %d\n\n", highest);

	printf("                   Highest Seat Booked\n");
	printf("                   Train ID     : %s\n", highestBookTrainSeat);
	printf("                   Seat Booked  : %d\n\n", highestSeat);

	printf("                   Highest Earn Train\n");
	printf("                   Train ID     : %s\n", highestEarnTrain);
	printf("                   Earned Amount: RM %d\n\n", highestEarn);

	printf("\033[30m============================================================\n");
	printf("                  ANALYSIS FOR EACH TRAIN\n");
	printf("============================================================\n\n");

	double percentBook = 0;
	fPtr = fopen("train_schedule.txt", "r");
	if (fPtr != NULL) {
		while (fscanf(fPtr, "%[^|]|%[^|]|%[^|]|%d|%d|%d\n", &trains.train_id, &trains.departure_station, &trains.arrival_station, &trains.departure_time, &trains.arrival_time, &trains.available_seats) != EOF) {
			fPtr2 = fopen("booking.txt", "r");
			if (fPtr2 != NULL) {
				tempCount = 0;
				while (fscanf(fPtr2, "%d|%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%[^|]|%d\n", &temp.memberId,
					&temp.bookingId, &temp.trainId, &temp.bookingDate, &temp.departureStation,
					&temp.arrivalStation, &temp.ticketType, &temp.coach, &temp.quantity, &temp.paymentMethod,
					&temp.totalAmount) != EOF) {
					if (strcmp(temp.trainId, trains.train_id) == 0) {
						tempCount += temp.quantity;
					}

				}
				fclose(fPtr2);
				percentBook = ((double)tempCount / trains.available_seats) * 100;
				printf("                   \033[0;35mTrain ID: %s\n", trains.train_id);
				printf("                   Seat    : %d/%d (%.2f%%)\033[30m\n\n", tempCount, trains.available_seats, percentBook);
			}

			i++;
		}
		fclose(fPtr);
	}
	system("pause");
}

void memberBookMenu() {
	int choice;

	do {
		system("cls");
		printf("============================================================\n");
		printf("\033[30m                  USER TRAIN BOOKING MENU\n");
		printf("\033[30m============================================================\n");
		printf("\n\033[0;35m         ENTER [1] -> DISPLAY ALL AVAILABLE TRAINS\n");
		printf("\033[0;35m         ENTER [2] -> BOOK TRAIN TICKET\n");
		printf("\033[0;35m         ENTER [3] -> VIEW BOOKING RECORDS\n");
		printf("\033[0;35m         ENTER [4] -> CANCEL BOOKING\n");
		printf("\033[0;35m         ENTER [5] -> NAVIGATE YOUR ACCOUNT\n");
		printf("\033[0;35m         ENTER [6] -> LOGOUT\n\n");
		rewind(stdin);
		printf("\033[30m         Enter Your Choice: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			memberDisplayBook();
			system("pause");
			break;
		case 2:
			memberTrainBook();
			break;
		case 3:
			memberDisplayRecord();
			system("pause");
			break;
		case 4:
			memberCancelBook();
			break;
		case 5:
			memberAccount();
			break;
		case 6:
			printf("\n============================================================\n");
			printf("\033[31m                          LOGGING OUT...\033[30m\n");
			printf("============================================================\n\n");
			system("pause");
			break;
		default:
			printf("\n============================================================\n");
			printf("         \033[31mINVALID CHOICE. PLEASE ENTER A VALID OPTION.\033[30m\n");
			printf("============================================================\n\n");
			system("pause");
		}
	} while (choice != 6);
}

void memberCancelBook() {
	Book temp;
	FILE* fPtr;
	FILE* fPtr2;
	char result = 'n';
	int bookid;
	int countBook = 0;
	char tempPayment[30];
	int refundAmount;
	char select;
	memberDisplayRecord();
	fPtr = fopen("booking.txt", "r");
	if (fPtr != NULL) {
		while (fscanf(fPtr, "%d|%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%[^|]|%d\n", &temp.memberId,
			&temp.bookingId, &temp.trainId, &temp.bookingDate, &temp.departureStation,
			&temp.arrivalStation, &temp.ticketType, &temp.coach, &temp.quantity, &temp.paymentMethod,
			&temp.totalAmount) != EOF) {
			if (memberId == temp.memberId) {
				countBook++;
			}
		}
		fclose(fPtr);
	}
	if (countBook > 0) {
		do {
			int count = 0;
			rewind(stdin);
			printf("                                Enter The Booking ID You Wish To Cancel: ");
			scanf("%d", &bookid);

			fPtr = fopen("booking.txt", "r");
			if (fPtr != NULL) {
				while (fscanf(fPtr, "%d|%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%[^|]|%d\n", &temp.memberId,
					&temp.bookingId, &temp.trainId, &temp.bookingDate, &temp.departureStation,
					&temp.arrivalStation, &temp.ticketType, &temp.coach, &temp.quantity, &temp.paymentMethod,
					&temp.totalAmount) != EOF) {
					if (bookid == temp.bookingId) {
						count++;
						strcpy(tempPayment, temp.paymentMethod);
						refundAmount = temp.totalAmount;
					}
				}
				fclose(fPtr);
				if (count > 0) {
					rewind(stdin);
					printf("                                Booking record found!\n");
					printf("                                Are you sure you want to delete (Y / N) ? ");
					scanf("%c", &select);
					select = toupper(select);
					if (select == 'Y') {
						fPtr = fopen("tempBooking.txt", "a");
						fPtr2 = fopen("booking.txt", "r");
						if (fPtr2 != NULL) {
							while (fscanf(fPtr2, "%d|%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%[^|]|%d\n", &temp.memberId,
								&temp.bookingId, &temp.trainId, &temp.bookingDate, &temp.departureStation,
								&temp.arrivalStation, &temp.ticketType, &temp.coach, &temp.quantity, &temp.paymentMethod,
								&temp.totalAmount) != EOF) {
								if (temp.bookingId != bookid) {
									fprintf(fPtr, "%d|%d|%s|%s|%s|%s|%s|%d|%d|%s|%d\n", temp.memberId,
										temp.bookingId, temp.trainId, temp.bookingDate, temp.departureStation,
										temp.arrivalStation, temp.ticketType, temp.coach, temp.quantity, temp.paymentMethod,
										temp.totalAmount);
								}
							}
							fclose(fPtr);
							fclose(fPtr2);
							remove("booking.txt");
							rename("tempBooking.txt", "booking.txt");
							printf("==========================================================================================================\n");
							printf("\033[38;2;75;177;13m                                   Successfully cancelled your booking!\033[30m\n");
							printf("==========================================================================================================\n");
							printf("                                RM %d has refunded to your ", refundAmount);
							if (strcmp(tempPayment, "Bank Transfer") == 0 || strcmp(tempPayment, "Credit Card") == 0 || strcmp(tempPayment, "Debit Card") == 0) {
								printf("bank account!\n");
							}
							else {
								printf("e-wallet account!\n");
							}
						}
						result = 'y';
					}
					else {
						printf("==========================================================================================================\n");
						printf("\033[31m                                        EXITING...\033[30m\n");
						printf("==========================================================================================================\n");
						result = 'y';
					}
				}
				else {
					printf("==========================================================================================================\n");
					printf("\033[31m                                         NO SUCH BOOKING ID FOUND!\033[30m\n");
					printf("==========================================================================================================\n");
				}
			}
		} while (result != 'y');
	}
	else {
		printf("                             You do not have booking available to be cancel!\n\n");
	}
	printf("                             \n");
	system("pause");
}

void memberDisplayBook() {
	Train trains;
	FILE* fPtr;
	fPtr = fopen("train_schedule.txt", "r");
	system("cls");
	printf("==============================================================\n");
	printf("\033[30m                  ALL TRAINS AVAILABLE TO BOOK\n");
	printf("\033[30m==============================================================\n\n");
	printf("| %-5s | %-20s | %-20s | %s |\n", "TRAIN", "     DEPARTURE", "      ARRIVAL", "SEAT");
	if (fPtr != NULL) {
		while (fscanf(fPtr, "%[^|]|%[^|]|%[^|]|%d|%d|%d\n", &trains.train_id, &trains.departure_station, &trains.arrival_station, &trains.departure_time, &trains.arrival_time, &trains.available_seats) != EOF) {
			double newDepTime = 0.0;
			double newArrTime = 0.0;
			char time[3] = "AM";
			char time2[3] = "AM";
			if (trains.departure_time > 1299) {
				newDepTime = ((double)trains.departure_time - 1200) / 100;
				strcpy(time, "PM");
			}
			else if (trains.departure_time >= 1200) {
				newDepTime = ((double)trains.departure_time) / 100;
				strcpy(time, "PM");
			}
			else {
				newDepTime = ((double)trains.departure_time) / 100;
				strcpy(time, "AM");
			}

			if (trains.arrival_time > 1299) {
				newArrTime = ((double)trains.arrival_time - 1200) / 100;
				strcpy(time2, "PM");
			}
			else if (trains.arrival_time >= 1200) {
				newArrTime = ((double)trains.arrival_time) / 100;
				strcpy(time2, "PM");
			}
			else {
				newArrTime = ((double)trains.arrival_time) / 100;
				strcpy(time2, "AM");
			}

			printf("\033[0;35m| %-5s | %-11s(%5.2f%s) | %-11s(%5.2f%s) | %-4d |\033[30m\n", trains.train_id, trains.departure_station, newDepTime, time, trains.arrival_station, newArrTime, time2, trains.available_seats);
		}
		fclose(fPtr);
		printf("\n==============================================================\n");
	}
	else {
		printf("\n==============================================================");
		printf("\n\033[31m                 THERE IS NO AVAILABLE TRAIN!\033[30m\n");
		printf("==============================================================\n");

	}
}

void memberTrainBook() {
	memberDisplayBook();
	char selectedBookId[10];
	FILE* fPtr;
	FILE* fPtr2;
	FILE* fPtr3;
	Train trains, check;
	Book temp, check2;
	int count = 0;
	char result = 'n';
	int type;
	int ticketPrice[6] = { 55, 15, 70, 50, 25 };
	int point[6] = { 35, 5, 45, 30, 15 };
	int totalPoint = 0;
	int select2;
	char select, select3;
	int bookingId = 2000;
	time_t currentTime;
	struct tm* localTime;
	int found = 0;
	double newDepTime, newArrTime;

	fPtr3 = fopen("train_schedule.txt", "r");
	if (fPtr3 != NULL) {
		do {
			rewind(stdin);

			printf("\n\033[30m          Enter Your Selection (TXXXX): ");
			scanf("%[^\n]", &selectedBookId);

			for (int i = 0; i < strlen(selectedBookId); i++) {
				selectedBookId[i] = toupper(selectedBookId[i]);
			}

			if (strlen(selectedBookId) > 0) {
				fPtr = fopen("train_schedule.txt", "r");
				if (fPtr != NULL) {
					while (fscanf(fPtr, "%[^|]|%[^|]|%[^|]|%d|%d|%d\n", &check.train_id, &check.departure_station, &check.arrival_station, &check.departure_time, &check.arrival_time, &check.available_seats) != EOF) {
						if (strcmp(selectedBookId, check.train_id) == 0) {
							found++;
							break;
						}
					}
					fclose(fPtr);
				}
				else {
					printf("          \033[31mNo such train ID found!\n");
				}
			}
			if (found > 0) {
				result = 'y';
			}
			else {
				printf("          \033[31mInvalid train ID!\n");
			}
		} while (result != 'y');
		fPtr = fopen("train_schedule.txt", "r");
		if (result = 'y') {
			while (fscanf(fPtr, "%[^|]|%[^|]|%[^|]|%d|%d|%d\n", &trains.train_id, &trains.departure_station, &trains.arrival_station, &trains.departure_time, &trains.arrival_time, &trains.available_seats) != EOF) {
				if (strcmp(trains.train_id, selectedBookId) == 0) {
					strcpy(temp.trainId, selectedBookId);
					strcpy(temp.departureStation, trains.departure_station);
					strcpy(temp.arrivalStation, trains.arrival_station);
					temp.departureTime = trains.departure_time;
					temp.arrivalTime = trains.arrival_time;
					break;
				}
			}
			fclose(fPtr);
			char times[3] = "AM";
			char times2[3] = "AM";
			if (temp.departureTime > 1259) {
				newDepTime = ((double)temp.departureTime - 1200) / 100;
				strcpy(times, "PM");
			}
			else if (temp.departureTime >= 1200 || temp.departureTime < 1300) {
				newDepTime = ((double)temp.departureTime) / 100;
				strcpy(times, "PM");
			}
			else {
				newDepTime = ((double)temp.departureTime) / 100;
			}

			if (temp.arrivalTime > 1259) {
				newArrTime = ((double)temp.arrivalTime - 1200) / 100;
				strcpy(times2, "PM");
			}
			else if (temp.arrivalTime >= 1200 || temp.arrivalTime < 1300) {
				newArrTime = ((double)temp.arrivalTime) / 100;
				strcpy(times2, "PM");
			}
			else {
				newArrTime = ((double)temp.arrivalTime) / 100;
			}
			system("cls");
			printf("============================================================");
			printf("\n\033[30m                       TRAIN DETAILS");
			printf("\n\033[30m============================================================\n\n");
			printf("                   Train ID         : %s\n", temp.trainId);
			printf("                   Departure Station: %s\n", temp.departureStation);
			printf("                   Arrival Station  : %s\n", temp.arrivalStation);
			printf("                   Departure Time   : %.2f%s\n", newDepTime, times);
			printf("                   Arrival Time     : %.2f%s\n", newArrTime, times2);
			result = 'n';
			do {
				printf("\n============================================================\n");
				printf("\033[30m                        TICKET TYPE\n");
				printf("\033[30m============================================================\n\n");
				printf("\033[0;35m                    ENTER [1] -> Sleeper\n");
				printf("                    ENTER [2] -> Off-peak\n");
				printf("                    ENTER [3] -> First Class\n");
				printf("                    ENTER [4] -> Business\n");
				printf("                    ENTER [5] -> Economy\033[30m\n\n");
				rewind(stdin);
				printf("     Select Your Type               : ");
				scanf("%d", &type);
				switch (type) {
				case 1: strcpy(temp.ticketType, "Sleeper"); result = 'y'; break;
				case 2: strcpy(temp.ticketType, "Off-peak"); result = 'y'; break;
				case 3: strcpy(temp.ticketType, "First Class"); result = 'y'; break;
				case 4: strcpy(temp.ticketType, "Business"); result = 'y'; break;
				case 5: strcpy(temp.ticketType, "Economy"); result = 'y'; break;
				default:
					printf("\n============================================================\n");
					printf("                    \033[31mINVALID TICKET TYPE!\n");
					printf("\033[30m============================================================\n");
					system("pause");
					system("cls");
					printf("============================================================");
					printf("\n\033[30m                       TRAIN DETAILS");
					printf("\n\033[30m============================================================\n\n");
					printf("\n                   Train ID         : %s\n", temp.trainId);
					printf("                   Departure Station: %s\n", temp.departureStation);
					printf("                   Arrival Station  : %s\n", temp.arrivalStation);
					printf("                   Departure Time   : %.2f%s\n", newDepTime, times);
					printf("                   Arrival Time     : %.2f%s\n", newArrTime, times2);
				}
			} while (result != 'y');


			do {
				rewind(stdin);
				printf("\033[30m     Select Your Coach (1-10)       : ");
				scanf("%d", &temp.coach);
				if (temp.coach < 0 || temp.coach > 10) {
					printf("\033[31m     INVALID CHOICE\n");
				}
			} while (temp.coach < 0 || temp.coach > 10);

			rewind(stdin);
			printf("     Enter Quantity You Want To Book: ");
			scanf("%d", &temp.quantity);

			temp.totalAmount = 0;

			if (strcmp(temp.ticketType, "Sleeper") == 0) {
				temp.totalAmount = ticketPrice[0] * temp.quantity;
				totalPoint = point[0] * temp.quantity;
			}
			else if (strcmp(temp.ticketType, "Off-peak") == 0) {
				temp.totalAmount = ticketPrice[1] * temp.quantity;
				totalPoint = point[1] * temp.quantity;
			}
			else if (strcmp(temp.ticketType, "First Class") == 0) {
				temp.totalAmount = ticketPrice[2] * temp.quantity;
				totalPoint = point[2] * temp.quantity;
			}
			else if (strcmp(temp.ticketType, "Business") == 0) {
				temp.totalAmount = ticketPrice[3] * temp.quantity;
				totalPoint = point[3] * temp.quantity;
			}
			else if (strcmp(temp.ticketType, "Economy") == 0) {
				temp.totalAmount = ticketPrice[4] * temp.quantity;
				totalPoint = point[4] * temp.quantity;
			}

			fPtr = fopen("booking.txt", "r");
			if (fPtr != NULL) {
				while (fscanf(fPtr, "%d|%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%[^|]|%d\n", &check2.memberId,
					&check2.bookingId, &check2.trainId, &check2.bookingDate, &check2.departureStation,
					&check2.arrivalStation, &check2.ticketType, &check2.coach, &check2.quantity, &check2.paymentMethod,
					&check2.totalAmount) != EOF) {
					if (check2.bookingId >= bookingId) {
						bookingId = check2.bookingId;
						bookingId++;
					}
				}
				fclose(fPtr);
			}

			temp.memberId = memberId;
			temp.bookingId = bookingId;

			time(&currentTime);
			localTime = localtime(&currentTime);
			strftime(temp.bookingDate, sizeof(temp.bookingDate), "%d-%m-%Y", localTime);

			rewind(stdin);
			printf("\n============================================================\n");
			printf("\033[31m          ARE YOU SURE YOU WANT TO BOOK FOLLOWING?\n");
			printf("\033[30m============================================================\n\n");
			printf("                 Train ID         : %s\n", temp.trainId);
			printf("                 Departure Station: %s\n", temp.departureStation);
			printf("                 Arrival Station  : %s\n", temp.arrivalStation);
			printf("                 Departure Time   : %.2f%s\n", newDepTime, times);
			printf("                 Arrival Time     : %.2f%s\n", newArrTime, times);
			printf("                 Ticket Type      : %s\n", temp.ticketType);
			printf("                 Coach            : %d\n", temp.coach);
			printf("                 Quantity         : %d\n", temp.quantity);
			printf("                 Total Payment    : RM %d\n", temp.totalAmount);
			printf("                 (Y/N)? ");
			scanf("%c", &select);

			result = 'n';
			if (toupper(select) == 'Y') {
				do {
					printf("\n============================================================\n");
					printf("\033[31m          WHICH PAYMENT METHOD DO YOU WISH TO USE?\n");
					printf("\033[30m============================================================\n\n");
					printf("                 ENTER [1] -> Credit Card\n");
					printf("                 ENTER [2] -> Debit Card\n");
					printf("                 ENTER [3] -> E-Wallet\n");
					printf("                 ENTER [4] -> Bank Transfer\n\n");
					rewind(stdin);
					printf("                 Select Your Payment Method: ");
					scanf("%d", &select2);
					switch (select2) {
					case 1: strcpy(temp.paymentMethod, "Credit Card"); result = 'y'; break;
					case 2: strcpy(temp.paymentMethod, "Debit Card"); result = 'y'; break;
					case 3: strcpy(temp.paymentMethod, "E-Wallet"); result = 'y'; break;
					case 4: strcpy(temp.paymentMethod, "Bank Transfer"); result = 'y'; break;
					default: printf("\033[31m                 Invalid payment method!\033[30m\n");
					}
				} while (result != 'y');
				char payment, cardName[30], expiryDate[10];
				int cardNum, securityCode;
				if (select2 == 1) {
					printf("\n============================================================\n");
					printf("\033[31m                            PAYMENT\n");
					printf("\033[30m============================================================\n\n");
					rewind(stdin);
					printf("                 Enter Your Card Number  : ");
					scanf(" %d", &cardNum);
					rewind(stdin);
					printf("                 Enter Your Card Name    : ");
					scanf(" %[^\n]", &cardName);
					rewind(stdin);
					printf("                 Enter Your Expiry Date  : ");
					scanf(" %[^\n]", &expiryDate);
					rewind(stdin);
					printf("                 Enter Your Security Code: ");
					scanf(" %d", &securityCode);
				}
				else if (select2 == 2) {
					printf("\n============================================================\n");
					printf("\033[31m                            PAYMENT\n");
					printf("\033[30m============================================================\n\n");
					rewind(stdin);
					printf("                 Enter Your Card Number  : ");
					scanf(" %d", &cardNum);
					rewind(stdin);
					printf("                 Enter Your Card Name    : ");
					scanf(" %[^\n]", &cardName);
					rewind(stdin);
					printf("                 Enter Your Expiry Date  : ");
					scanf(" %[^\n]", &expiryDate);
					rewind(stdin);
					printf("                 Enter Your Security Code: ");
					scanf(" %d", &securityCode);
				}
				else if (select2 == 3) {
					printf("\n============================================================\n");
					printf("\033[31m                            PAYMENT\n");
					printf("\033[30m============================================================\n\n");
					printf("                 Transfer to following\n");
					printf("                 Name           : TBS MALAYSIA\n");
					printf("                 Account Number : 8938378474743848484\n");
					rewind(stdin);
					system("pause");
				}
				else if (select2 == 4) {
					printf("\n============================================================\n");
					printf("\033[31m                            PAYMENT\n");
					printf("\033[30m============================================================\n\n");
					printf("                 Transfer to following\n");
					printf("                 Name           : TBS MALAYSIA\n");
					printf("                 Account Number : 7630148425\n");
					printf("                 Bank           : CIMB Bank\n");
					rewind(stdin);
					printf("                 ");
					system("pause");
				}
				printf("\n============================================================\n");
				printf("\033[31m                    BOOKING CONFIRMATION\n");
				printf("\033[30m============================================================\n\n");
				printf("                 Payment Method: %s\n", temp.paymentMethod);
				printf("                 Total Payment : RM %d\n", temp.totalAmount);
				rewind(stdin);
				printf("                 Confirm (Y/N)?  ");
				scanf(" %c", &select3);

				if (toupper(select3) == 'Y') {
					fPtr = fopen("booking.txt", "a");
					fprintf(fPtr, "%d|%d|%s|%s|%s|%s|%s|%d|%d|%s|%d\n", temp.memberId,
						temp.bookingId, temp.trainId, temp.bookingDate, temp.departureStation,
						temp.arrivalStation, temp.ticketType, temp.coach, temp.quantity, temp.paymentMethod,
						temp.totalAmount);
					fclose(fPtr);
					if (totalPoint > 0) {
						fPtr2 = fopen("memberPoint.txt", "a");
						fprintf(fPtr2, "%d|%d\n", temp.memberId, totalPoint);
						fclose(fPtr2);
					}
					printf("\n============================================================\n");
					printf("\033[38;2;75;177;13m                    SUCESSFULLY BOOKED!\n");
					printf("\033[30m============================================================\n");
					system("pause");
				}
				printf("%c", select3);
			}
		}
		else {
			printf("============================================================\n");
			printf("\033[31m                  NO SUCH TRAIN ID FOUND!\n");
			printf("\033[30m============================================================\n");
		}
	}
	else {
		system("pause");
	}
}

void memberDisplayRecord() {
	FILE* fPtr;
	Book temp;
	int count = 0;
	fPtr = fopen("booking.txt", "r");

	if (fPtr != NULL) {
		system("cls");
		printf("==========================================================================================================\n");
		printf("\033[30m                                              BOOKING RECORD\n");
		printf("\033[30m==========================================================================================================\n");
		printf("\n|%-7s|%-8s|%-12s| %-11s|  %-11s|%-11s|%-5s|%-8s|   %-11s|%-5s|\n", "Book ID", "Train ID", "Booking Date", "Departure", "Arrival", "Ticket Type", "Coach", "Quantity", "Payment", "Total");
		while (fscanf(fPtr, "%d|%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%[^|]|%d\n", &temp.memberId,
			&temp.bookingId, &temp.trainId, &temp.bookingDate, &temp.departureStation,
			&temp.arrivalStation, &temp.ticketType, &temp.coach, &temp.quantity, &temp.paymentMethod,
			&temp.totalAmount) != EOF) {
			if (memberId == temp.memberId) {
				printf("\033[0;35m| %-6d| %-7s| %-11s|  %-10s|  %-11s|%-11s|  %-3d|  %-6d|%-14s|%-5d|\033[30m\n",
					temp.bookingId, temp.trainId, temp.bookingDate,
					temp.departureStation, temp.arrivalStation, temp.ticketType,
					temp.coach, temp.quantity, temp.paymentMethod, temp.totalAmount);
				count++;
			}
		}
		fclose(fPtr);
		if (count == 0) {
			printf("\n==========================================================================================================\n");
			printf("\033[31m                                        NO BOOKING RECORDS FOUND!\n");
			printf("\033[30m==========================================================================================================\n");
		}
	}
	else {
		printf("\==========================================================================================================\n");
		printf("\033[31m                                        NO BOOKING RECORDS FOUND!\n");
		printf("\033[30m==========================================================================================================\n");
	}
	printf("\n\033[30m==========================================================================================================\n");
}

void memberAccount() {
	int totalPoint = 0;
	int id, point;
	Member members;
	FILE* fPtr;
	FILE* fPtr2;

	fPtr = fopen("members.bin", "rb");
	system("cls");
	printf("============================================================\n");
	printf("\033[30m                   NAVIGATE YOUR ACCOUNT\n");
	printf("\033[30m============================================================\n");

	if (fPtr != NULL) {
		while (fread(&members, sizeof(Member), 1, fPtr)) {
			if (members.id == memberId) {
				printf("\n\033[0;35m                     Member ID    : %d\n", members.id);
				printf("                     Gender       : ");
				if (members.gender == 'M') {
					printf("Male\n");
				}
				else if (members.gender == 'F') {
					printf("Female\n");
				}
				printf("                     Age          : %d\n", members.age);
				printf("                     IC Number    : %s\n", members.icNum);
				printf("                     Phone Number : %s\n", members.phoneNum);
				fPtr2 = fopen("memberPoint.txt", "r");
				if (fPtr2 != NULL) {
					while (fscanf(fPtr2, "%d|%d\n", &id, &point) != EOF) {
						if (members.id == id) {
							totalPoint += point;
						}
					}
					fclose(fPtr2);
				}
				printf("                     Member Point : %d\n", totalPoint);
			}
		}
	}
	printf("                     Member Type  : ");
	if (totalPoint > 3000) {
		printf("VVIP\n");
	}
	else if (totalPoint > 2000) {
		printf("VIP\n");
	}
	else if (totalPoint > 1500) {
		printf("Diamond\n");
	}
	else if (totalPoint > 1000) {
		printf("Gold\n");
	}
	else if (totalPoint > 500) {
		printf("Silver\n");
	}
	else {
		printf("Normal\n");
	}
	printf("\n\033[30m============================================================\n");
	system("pause");
}

void adminAccountMenu() {
	int choice;

	do {
		system("cls");
		printf("============================================================\n");
		printf("\033[30m                  ACCOUNT MANAGEMENT MENU\n");
		printf("\033[30m============================================================\n\n");
		printf("\033[0;35m             ENTER [1] -> MANAGE STAFF ACCOUNT\n");
		printf("             ENTER [2] -> MANAGE MEMBER ACCOUNT\n");
		printf("             ENTER [3] -> EXIT\033[30m\n\n");
		rewind(stdin);
		printf("             Enter your choice: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			adminManageStaffMenu();
			break;
		case 2:
			adminManageMember();
			break;
		case 3:
			printf("\n============================================================\n");
			printf("\033[31m                         EXITING...\033[30m\n");
			printf("============================================================\n");
			system("pause");
			break;
		default:
			printf("\n============================================================\n");
			printf("\033[31m        INVALID CHOICE. PLEASE ENTER A VALID OPYION.\033[30m\n");
			printf("============================================================\n");
			system("pause");
		}
	} while (choice != 3);
}

void adminManageStaffMenu() {
	int choice;

	do {
		system("cls");
		printf("============================================================\n");
		printf("\033[30m               STAFF ACCOUNT MANAGEMENT MENU\n");
		printf("\033[30m============================================================\n\n");
		printf("\033[0;35m         ENTER [1] -> VIEW STAFF LIST\n");
		printf("         ENTER [2] -> ADD EXISTING MEMBER TO STAFF\n");
		printf("         ENTER [3] -> DELETE STAFF ACCOUNT\n");
		printf("         ENTER [4] -> MODIFY STAFF ACCOUNT PASSWORD\n");
		printf("         ENTER [5] -> EXIT\033[30m\n\n");
		rewind(stdin);
		printf("         Enter your choice: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			adminStaffList();
			system("pause");
			break;
		case 2:
			adminAddStaff();
			break;
		case 3:
			adminDeleteStaff();
			break;
		case 4:
			adminModifyStaff();
			break;
		case 5:
			printf("\n============================================================\n");
			printf("\033[31m                         EXITING...\033[30m\n");
			printf("============================================================\n");
			system("pause");
			break;
		default:
			printf("\n============================================================\n");
			printf("\033[31m        INVALID CHOICE. PLEASE ENTER A VALID OPYION.\033[30m\n");
			printf("============================================================\n");
			system("pause");
		}
	} while (choice != 5);
}

void adminAddStaff() {
	Member members, temp, staffs;
	FILE* fPtr;
	FILE* fPtr2;
	int count = 1;
	int choice;
	int found = 0;
	char select;

	system("cls");
	printf("============================================================================\n");
	printf("\033[30m                        ADD EXISTING MEMBER TO STAFF\n");
	printf("\033[30m============================================================================\n\n");
	fPtr = fopen("members.bin", "rb");
	printf("%-3s %-10s %-10s %-10s %-8s %-14s %-3s %-11s\n", "NO", "STAFF ID", "NAME", "PASSWORD", "GENDER", "IC", "AGE", "PHONE");
	if (fPtr != NULL) {
		temp;
		while (fread(&members, sizeof(Member), 1, fPtr)) {
			printf("\033[0;35m%d.  %-10d %-10s %-10s %-8c %-14s %-3d %s\033[30m\n", count, members.id, members.name, members.password, members.gender, members.icNum, members.age, members.phoneNum);
			count++;
		}
		do {
			rewind(stdin);

			printf("\n                         Select One Number To Add: ");
			scanf("%d", &choice);
			if (choice < 0 || choice >= count) {
				printf("\n============================================================================\n");
				printf("\033[31m                              INVALID CHOICE!\n");
				printf("\033[30m============================================================================\n");
			}
		} while (choice < 0 || choice >= count);
		fclose(fPtr);
		count = 1;
		fPtr = fopen("members.bin", "rb");
		while (fread(&members, sizeof(Member), 1, fPtr)) {
			if (count == choice) {
				temp = members;
			}
			count++;
		}
		fclose(fPtr);
		printf("\n============================================================================\n");
		printf("\033[31m           ARE YOU SURE YOU WANT TO ADD FOLLOWING TO STAFF LIST?\033[30m\n");
		printf("============================================================================\n");
		printf("\n%-10s %-10s %-10s %-8s %-14s %-3s %-11s\n", "STAFF ID", "NAME", "PASSWORD", "GENDER", "IC", "AGE", "PHONE");
		printf("%-10d %-10s %-10s %-8c %-14s %-3d %s\n", temp.id, temp.name, temp.password, temp.gender, temp.icNum, temp.age, temp.phoneNum);
		printf("\n\033[31m                              Confirm (Y/N)?\033[30m ");
		rewind(stdin);
		scanf("%c", &select);
		select = toupper(select);
		if (select == 'Y') {
			fPtr = fopen("staffs.bin", "rb");
			if (fPtr != NULL) {
				while (fread(&staffs, sizeof(Member), 1, fPtr)) {
					if (strcmp(staffs.name, temp.name) == 0) {
						found++;
					}
				}
				fclose(fPtr);
				if (found > 0) {
					printf("\n============================================================================\n");
					printf("\033[31m                   THE MEMBER IS ALREADY A STAFF MEMBER!\033[30m\n");
					printf("============================================================================\n");
					system("pause");
				}
				else {
					fPtr = fopen("staffs.bin", "ab");
					fwrite(&temp, sizeof(Member), 1, fPtr);
					fclose(fPtr);
					printf("\n============================================================================\n");
					printf("\033[38;2;75;177;13m               SUCCESSFULLY ADDED %s AS STAFF MEMBER!\033[30m\n", temp.name);
					printf("============================================================================\n");
					system("pause");
				}
			}
			else {
				printf("File not found!\n");
				exit(-1);
			}
		}
	}
	else {
		printf("File not found!\n");
		exit(-1);
	}

}

void adminStaffList() {
	FILE* fPtr;
	Member staffs;
	int count = 1;
	system("cls");
	printf("============================================================================\n");
	printf("\033[30m                                 STAFF LIST\n");
	printf("\033[30m============================================================================\n\n");
	fPtr = fopen("staffs.bin", "rb");
	printf("%-3s %-10s %-10s %-10s %-8s %-14s %-3s %-11s\n", "NO", "STAFF ID", "NAME", "PASSWORD", "GENDER", "IC", "AGE", "PHONE");
	if (fPtr != NULL) {
		while (fread(&staffs, sizeof(Member), 1, fPtr)) {
			printf("\033[0;35m%d.  %-10d %-10s %-10s %-8c %-14s %-3d %s\033[30m\n", count, staffs.id, staffs.name, staffs.password, staffs.gender, staffs.icNum, staffs.age, staffs.phoneNum);
			count++;
		}
		fclose(fPtr);
	}
	else {
		printf("File not found!\n");
		exit(-1);
	}
	printf("\n============================================================================\n\n");
}

void adminDeleteStaff() {
	FILE* fPtr;
	Member staffs[MAX_STAFF];
	int count = 0;
	int choice;
	int countAdmin = 0;

	system("cls");
	printf("============================================================================\n");
	printf("\033[30m                            DELETE STAFF ACCOUNT\n");
	printf("\033[30m============================================================================\n\n");

	fPtr = fopen("staffs.bin", "rb");
	printf("%-3s %-10s %-10s %-10s %-8s %-14s %-3s %-11s\n", "NO", "STAFF ID", "NAME", "PASSWORD", "GENDER", "IC", "AGE", "PHONE");
	if (fPtr != NULL) {
		while (fread(&staffs[count], sizeof(Member), 1, fPtr)) {
			printf("\033[0;35m%d.  %-10d %-10s %-10s %-8c %-14s %-3d %s\033[30m\n", count + 1, staffs[count].id, staffs[count].name, staffs[count].password, staffs[count].gender, staffs[count].icNum, staffs[count].age, staffs[count].phoneNum);
			count++;
		}
		fclose(fPtr);
		if (count == 1) {
			printf("\n============================================================================\n");
			printf("\033[31m                   YOU CAN'T DELETE ANYMORE STAFF ACCOUNT!\033[30m\n");
			printf("============================================================================\n");
			system("pause");
		}
		else {
			do {
				printf("\n                         Select Number To Delete: ");
				scanf("%d", &choice);
				if (choice < 0 || choice >= count + 1) {
					printf("\n============================================================================\n");
					printf("\033[31m                              INVALID CHOICE!\n");
					printf("\033[30m============================================================================\n");
				}
			} while (choice < 0 || choice >= count + 1);
			if (choice == 1) {
				printf("\n============================================================================\n");
				printf("\033[31m                 YOU CAN'T DELETE THE DEFAULT STAFF ACCOUNT!\033[30m\n");
				printf("============================================================================\n");
				system("pause");
			}
			else {
				if (choice > 0) {
					choice -= 1;
					for (int i = choice; i < count - 1; i++) {
						staffs[i] = staffs[i + 1];
					}
					fPtr = fopen("staffs.bin", "wb");
					fwrite(&staffs, sizeof(Member), count - 1, fPtr);
					fclose(fPtr);
					printf("\n============================================================================\n");
					printf("\033[38;2;75;177;13m                  SUCCESSFULLY DELETED THE STAFF ACCOUNT!\033[30m\n");
					printf("============================================================================\n");
					system("pause");
				}
			}
		}
	}
	else {
		printf("File not found!\n");
		exit(-1);
	}
}

void adminModifyStaff() {
	FILE* fPtr;
	Member staffs[MAX_STAFF];
	int count = 0;
	int choice;
	int countAdmin = 0;

	system("cls");
	printf("============================================================================\n");
	printf("\033[30m                       MODIFY STAFF ACCOUNT PASSWORD\n");
	printf("\033[30m============================================================================\n\n");

	fPtr = fopen("staffs.bin", "rb");
	printf("%-3s %-10s %-10s %-10s %-8s %-14s %-3s %-11s\n", "NO", "STAFF ID", "NAME", "PASSWORD", "GENDER", "IC", "AGE", "PHONE");
	if (fPtr != NULL) {
		while (fread(&staffs[count], sizeof(Member), 1, fPtr)) {
			printf("\033[0;35m%d.  %-10d %-10s %-10s %-8c %-14s %-3d %s\033[30m\n", count + 1, staffs[count].id, staffs[count].name, staffs[count].password, staffs[count].gender, staffs[count].icNum, staffs[count].age, staffs[count].phoneNum);
			count++;
		}
		fclose(fPtr);
		if (count == 1) {
			printf("\n============================================================================\n");
			printf("\033[31m          YOU CAN'T MODIFY DEFAULT STAFF ACCOUNT PASSWORD!\033[30m\n");
			printf("============================================================================\n");
			system("pause");
		}
		else {
			do {
				printf("\n                         Select Number To Modify: ");
				scanf("%d", &choice);
				if (choice < 0 || choice >= count + 1) {
					printf("                         \033[31mInvalid choice!\033[30m\n");
				}
			} while (choice < 0 || choice >= count + 1);
			if (choice == 1) {
				printf("\n============================================================================\n");
				printf("\033[31m                YOU CAN'T MODIFY THE DEFAULT STAFF PASSWORD!\033[30m\n");
				printf("============================================================================\n");
				system("pause");
			}
			else {
				if (choice > 0) {
					choice -= 1;
					rewind(stdin);
					printf("\n                    Enter New Password For %s: ", staffs[choice].name);
					scanf("%[^\n]", &staffs[choice].password);
					fPtr = fopen("staffs.bin", "wb");
					fwrite(&staffs, sizeof(Member), count, fPtr);
					fclose(fPtr);
					printf("\n============================================================================\n");
					printf("\033[38;2;75;177;13m              SUCCESSFULLY MODIFIED THE STAFF ACCOUNT PASSWORD!\033[30m\n");
					printf("============================================================================\n");
					system("pause");
				}
			}
		}
	}
	else {
		printf("File not found!\n");
		exit(-1);
	}
}

void adminManageMember() {
	int choice;

	do {
		system("cls");
		printf("============================================================\n");
		printf("\033[30m               MEMBER ACCOUNT MANAGEMENT MENU\n");
		printf("\033[30m============================================================\n\n");
		printf("\033[0;35m             ENTER [1] -> VIEW MEMBER LIST\n");
		printf("             ENTER [2] -> DELETE MEMBER ACCOUNT\n");
		printf("             ENTER [3] -> MODIFY MEMBER ACCOUNT\n");
		printf("             ENTER [4] -> EXIT\033[30m\n\n");
		rewind(stdin);
		printf("             Enter Your Choice: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			adminMemberList();
			system("pause");
			break;
		case 2:
			adminDeleteMember();
			break;
		case 3:
			adminModifyMemberMenu();
			break;
		case 4:
			printf("\n============================================================\n");
			printf("\033[31m                         EXITING...\033[30m\n");
			printf("============================================================\n");
			system("pause");
			break;
		default:
			printf("\n============================================================\n");
			printf("\033[31m        INVALID CHOICE. PLEASE ENTER A VALID OPYION.\033[30m\n");
			printf("============================================================\n");
			system("pause");
		}
	} while (choice != 4);
}

void adminMemberList() {
	FILE* fPtr;
	Member members;
	int count = 1;

	system("cls");
	printf("============================================================================\n");
	printf("\033[30m                                MEMBER LIST\n");
	printf("\033[30m============================================================================\n\n");
	fPtr = fopen("members.bin", "rb");
	printf("%-3s %-10s %-10s %-10s %-8s %-14s %-3s %-11s\n", "NO", "MEMBER ID", "NAME", "PASSWORD", "GENDER", "IC", "AGE", "PHONE");
	if (fPtr != NULL) {
		while (fread(&members, sizeof(Member), 1, fPtr)) {
			printf("\033[0;35m%d.  %-10d %-10s %-10s %-8c %-14s %-3d %s\033[30m\n", count, members.id, members.name, members.password, members.gender, members.icNum, members.age, members.phoneNum);
			count++;
		}
		fclose(fPtr);
	}
	else {
		printf("File not found!\n");
		exit(-1);
	}
	printf("\n============================================================================\n");
}

void adminDeleteMember() {
	FILE* fPtr;
	FILE* fPtr2;
	Member members[MAX_MEMBER], tempMembers;
	int count = 0, count2 = 0;
	int choice;
	int countAdmin = 0;
	int tempId;
	Book temp;
	char tempName[99];
	int tempPoint;
	char select;

	system("cls");
	printf("============================================================================\n");
	printf("\033[30m                           DELETE MEMBER ACCOUNT\n");
	printf("\033[30m============================================================================\n\n");

	fPtr = fopen("members.bin", "rb");
	printf("%-3s %-10s %-10s %-10s %-8s %-14s %-3s %-11s\n", "NO", "MEMBER ID", "NAME", "PASSWORD", "GENDER", "IC", "AGE", "PHONE");
	if (fPtr != NULL) {
		while (fread(&members[count], sizeof(Member), 1, fPtr)) {
			printf("\033[0;35m%d.  %-10d %-10s %-10s %-8c %-14s %-3d %s\033[30m\n", count + 1, members[count].id, members[count].name, members[count].password, members[count].gender, members[count].icNum, members[count].age, members[count].phoneNum);
			count++;
		}
		fclose(fPtr);
		if (count == 0) {
			printf("\n============================================================================\n");
			printf("\033[31m                  YOU CAN'T DELETE ANYMORE MEMBER ACCOUNT!\033[30m\n");
			printf("============================================================================\n");
			system("pause");
		}
		else {
			do {
				printf("\n                         Select Number To Delete: ");
				scanf("%d", &choice);
				if (choice < 0 || choice >= count + 1) {
					printf("\n============================================================================\n");
					printf("\033[31m                              INVALID CHOICE!\n");
					printf("\033[30m============================================================================\n");
				}
			} while (choice < 0 || choice >= count + 1);
			rewind(stdin);
			printf("\n\033[31m                Are You Sure To You Want To Delete? (Y/N)?\033[30m ");
			scanf("%c", &select);
			select = toupper(select);
			if (select == 'Y') {
				if (choice > 0) {
					choice -= 1;
					fPtr = fopen("members.bin", "rb");
					while ((fread(&tempMembers, sizeof(Member), 1, fPtr))) {
						if (count2 == choice) {
							tempId = tempMembers.id;
							break;
						}
						count2++;
					}
					for (int i = choice; i < count - 1; i++) {
						members[i] = members[i + 1];
					}
					fPtr = fopen("members.bin", "wb");
					fwrite(&members, sizeof(Member), count - 1, fPtr);
					fclose(fPtr);
					fPtr = fopen("booking.txt", "r");
					if (fPtr != NULL) {
						fPtr2 = fopen("tempBooking.txt", "w");
						while (fscanf(fPtr, "%d|%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%[^|]|%d\n", &temp.memberId,
							&temp.bookingId, &temp.trainId, &temp.bookingDate, &temp.departureStation,
							&temp.arrivalStation, &temp.ticketType, &temp.coach, &temp.quantity, &temp.paymentMethod,
							&temp.totalAmount) != EOF) {
							if (tempId != temp.memberId) {
								fprintf(fPtr2, "%d|%d|%s|%s|%s|%s|%s|%d|%d|%s|%d\n", temp.memberId,
									temp.bookingId, temp.trainId, temp.bookingDate, temp.departureStation,
									temp.arrivalStation, temp.ticketType, temp.coach, temp.quantity, temp.paymentMethod,
									temp.totalAmount);
							}
						}
						fclose(fPtr);
						fclose(fPtr2);
						remove("booking.txt");
						rename("tempBooking.txt", "booking.txt");
					}
					fPtr = fopen("memberPoint.txt", "r");
					if (fPtr != NULL) {
						fPtr2 = fopen("tempMemberPoint.txt", "w");
						while (fscanf(fPtr, "%d|%d\n", &temp.memberId, &tempPoint) != EOF) {
							if (tempId != temp.memberId) {
								fprintf(fPtr2, "%d|%d\n", temp.memberId, tempPoint);
							}
						}
						fclose(fPtr);
						fclose(fPtr2);
						remove("memberPoint.txt");
						rename("tempMemberPoint.txt", "memberPoint.txt");
					}
					printf("\n============================================================================\n");
					printf("\033[38;2;75;177;13m                 SUCCESSFULLY DELETED THE MEMBER ACCOUNT!\033[30m\n");
					printf("============================================================================\n");
					system("pause");
				}
			}
		}
	}
	else {
		printf("File not found!\n");
		exit(-1);
	}
}

void adminModifyMemberMenu() {
	int choice;

	do {
		system("cls");
		printf("============================================================\n");
		printf("\033[30m                  MEMBER ACCOUNT MODIFY MENU\n");
		printf("\033[30m============================================================\n\n");
		printf("\033[0;35m            ENTER [1] -> MODIFY ACCOUNT PASSWORD\n");
		printf("            ENTER [2] -> MODIFY MEMBER POINT\n");
		printf("            ENTER [3] -> EXIT\033[30m\n\n");
		rewind(stdin);
		printf("            Enter Your Choice: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			adminModifyMemberPassword();
			system("pause");
			break;
		case 2:
			adminModifyMemberPoint();
			break;
		case 3:
			printf("\n============================================================\n");
			printf("\033[31m                         EXITING...\033[30m\n");
			printf("============================================================\n");
			system("pause");
			break;
		default:
			printf("\n============================================================\n");
			printf("\033[31m        INVALID CHOICE. PLEASE ENTER A VALID OPTION.\033[30m\n");
			printf("============================================================\n");
			system("pause");
		}
	} while (choice != 3);
}

void adminModifyMemberPassword() {
	FILE* fPtr;
	Member members[MAX_MEMBER];
	int count = 0;
	int choice;

	system("cls");
	printf("============================================================================\n");
	printf("\033[30m                      MODIFY MEMBER ACCOUNT PASSWORD\n");
	printf("\033[30m============================================================================\n\n");

	fPtr = fopen("members.bin", "rb");
	printf("%-3s %-10s %-10s %-10s %-8s %-14s %-3s %-11s\n", "NO", "MEMBER ID", "NAME", "PASSWORD", "GENDER", "IC", "AGE", "PHONE");
	if (fPtr != NULL) {
		while (fread(&members[count], sizeof(Member), 1, fPtr)) {
			printf("\033[0;35m%d.  %-10d %-10s %-10s %-8c %-14s %-3d %s\033[30m\n", count + 1, members[count].id, members[count].name, members[count].password, members[count].gender, members[count].icNum, members[count].age, members[count].phoneNum);
			count++;
		}
		fclose(fPtr);
		do {
			printf("\n                     Select Number To Modify Password: ");
			scanf("%d", &choice);
			if (choice < 0 || choice >= count + 1) {
				printf("\n============================================================================\n");
				printf("\033[31m                              INVALID CHOICE!\n");
				printf("\033[30m============================================================================\n");
			}
		} while (choice < 0 || choice >= count + 1);
		if (choice > 0) {
			choice -= 1;
			rewind(stdin);
			printf("                     Enter New Password For %s: ", members[choice].name);
			scanf("%[^\n]", &members[choice].password);
			fPtr = fopen("members.bin", "wb");
			fwrite(&members, sizeof(Member), count, fPtr);
			fclose(fPtr);

			printf("\n============================================================================\n");
			printf("\033[38;2;75;177;13m                    SUCCESSFULLY MODIFIED THE PASSWORD!\033[30m\n");
			printf("============================================================================\n");
		}
	}
	else {
		printf("\n============================================================================\n");
		printf("\033[31m                         THERE IS NO MEMBER FOUND!\033[30m\n");
		printf("============================================================================\n");
	}
}

void adminModifyMemberPoint() {
	FILE* fPtr;
	FILE* fPtr2;
	Member members[MAX_MEMBER];
	int count = 0;
	int choice;
	int tempId, tempPoint;
	int totalPoint[MAX_MEMBER] = { 0 };
	int inputPoint;
	int pointToModify = 0;

	system("cls");
	printf("============================================================\n");
	printf("\033[30m                    MODIFY MEMBER POINT\n");
	printf("\033[30m============================================================\n");

	fPtr = fopen("members.bin", "rb");
	printf("               %-3s %-10s %-10s %-10s\n", "NO", "MEMBER ID", "NAME", "POINT");
	if (fPtr != NULL) {
		fPtr2 = fopen("memberPoint.txt", "r");
		if (fPtr2 != NULL) {
			while (fread(&members[count], sizeof(Member), 1, fPtr)) {
				rewind(fPtr2);
				while (fscanf(fPtr2, "%d|%d\n", &tempId, &tempPoint) != EOF) {
					if (members[count].id == tempId) {
						totalPoint[count] += tempPoint;
					}
				}
				printf("\033[0;35m               %d.  %-10d %-10s %-10d\033[30m\n", count + 1, members[count].id, members[count].name, totalPoint[count]);
				count++;
			}
			fclose(fPtr);
			fclose(fPtr2);
			do {
				rewind(stdin);
				printf("\n           Select Number To Modify Member Point: ");
				scanf("%d", &choice);

				if (choice < 0 || choice >= count + 1) {
					printf("\n============================================================================\n");
					printf("\033[31m                              INVALID CHOICE!\n");
					printf("\033[30m============================================================================\n");
				}
			} while (choice < 0 || choice >= count + 1);
			choice -= 1;
			do {
				printf("           Enter Amount To Wish To Set It: ");
				scanf("%d", &inputPoint);
			} while (inputPoint < 0);
			for (int i = 0; i < count; i++) {
				if (choice == i) {
					pointToModify = inputPoint - totalPoint[i];
				}
			}
			fPtr = fopen("memberPoint.txt", "a");
			fprintf(fPtr, "%d|%d\n", members[choice].id, pointToModify);
			fclose(fPtr);
			printf("\n============================================================\n");
			printf("\033[38;2;75;177;13m              SUCCESSFULLY EDIT MEMBER POINT!\033[30m\n");
			printf("============================================================\n");
			system("pause");
		}
		else {
			printf("\n============================================================\n");
			printf("                  NO MEMBER POINT RECORD!\033[30m\n");
			printf("===============================================================\n");
			system("pause");
		}
	}
	else {
		printf("\n============================================================\n");
		printf("                  THERE IS NO MEMBER FOUND!\033[30m\n");
		printf("============================================================\n");
		system("pause");
	}
}