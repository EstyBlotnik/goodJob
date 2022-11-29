#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define INFN "input.txt"
#define OUTFN "output.txt"
#define N 20
#define S 15
#define EOLN '\r'
struct Employee
{
	char first_name[S];
	char last_name[S];
	char gender[S];
	char id[S];
	int age;
	char phone_number[S];
	int password;
	char Email[25];
	char living_area[5];
	char Driving_License[5];
	char Education_level[N];
	char Employment_Catagory[N];
	int apply_jobs[10];
};
struct Employer
{
	char first_name[S];
	char last_name[S];
	char gender[S];
	char id[S];
	int age;
	char phone_number[S];
	int password;
	char Email[25];
	char company_name[N];

};
typedef struct
{
	char name_of_job[N];
	char name_of_company[N];
	char employment_catagory[N];//תחום המשרה
	char location_area[N];//מיקום 
	char scope_of_the_job[N];//היקף המשרה
	char salary_range[N];//טווח השכר לשעה
	int index_boss;
	int arr_index_worker[100];//את מערך כל המגישים לאתחל לנאל?????????????
	int code;//מספר קוד של משרה

}Job;
Job* refresh();
Job* pop_jobs();
void printf_employee_details(struct Employee w);
struct Employee* Change_personal_details(int index, struct Employee* z);
void put_data_file_employee(struct Employee* worker, int size);
void push_jobs(Job* jobs);
void add_job(int index);
void print_job(Job job);
void WorkerPersonalArea(int index, struct Employee workers[100], struct Employer bosses[100], Job* jobs);
void EmployerPersonalArea(int index, struct Employee workers[100], struct Employer bosses[100], Job* jobs);
void job_search_no_filter(Job* jobs);
void printf_employer_details(struct Employer w);
struct Employee read_Employee_Data_File(FILE* fp/*, struct Employee* employee*/);
void print_data_file_employer(struct Employer emp);
void print_data_file_employee(struct Employee worker);
void logIn(struct Employee workers[100], struct Employer bosses[100], Job* jobs);
void Viewing_nominees_search(int index, struct Employee* workers, Job* jobs);
void Viewing_nominees(int index, struct Employee emp[100]);
struct Employer read_Employer_Data_File(FILE* fp);
void init_employee();
struct Employer init_employer();
void Registration_Process();
void job_search_filter(Job* arr_jobs);
Job* applying(int index, Job* jobs, struct Employee* workers);
int main()
{
	FILE* fp = fopen("Employer.txt", "a");
	FILE* fpi = fopen("Employee.txt", "a");
	fclose(fp);
	fclose(fpi);
	Job* jobs1 = refresh();
	push_jobs(jobs1);
	struct Employee workers[100];
	struct Employer employer[100];
	int size = 100;
	int option;
	Job* jobs = pop_jobs();

	printf("Please Choose an option:\n1.Sign-up\n2.Sign-In\n");
	scanf("%d", &option);
	switch (option)
	{
	case 1:
		Registration_Process(&employer, size, &workers);
	case 2:
		fp = fopen("Employer.txt", "r");
		fpi = fopen("Employee.txt", "r");
		//fp = fopen("C:\\Users\\Administrator\\source\\repos\\good job\\Employer.txt", "r");
		//fpi = fopen("C:\\Users\\Administrator\\source\\repos\\good job\\Employee.txt", "r");
		for (int i = 0; i < 100; ++i)
		{
			workers[i] = read_Employee_Data_File(fpi);
			employer[i] = read_Employer_Data_File(fp);
			/*printf("\n\nemployer %d:\n", i + 1);
			printf_employer_details(employer[i]);*/
			/*printf("\nworker %d:\n", i + 1);
			printf_employee_details(workers[i], 100);*/
		}
		//printf("%d",findLength(workers));
		fclose(fp);
		fclose(fpi);
		logIn(workers, employer, jobs);
	}
	//push_jobs(jobs1);
	return 0;
}
Job* refresh()
{
	Job jobsArr[1000];
	for (int i = 0; i < 1000; ++i)
	{
		strcpy(jobsArr[i].name_of_job, "NULL");
		strcpy(jobsArr[i].name_of_company, "NULL");
		strcpy(jobsArr[i].employment_catagory, "NULL");
		strcpy(jobsArr[i].location_area, "NULL");
		strcpy(jobsArr[i].scope_of_the_job, "NULL");
		strcpy(jobsArr[i].salary_range, "NULL");
		jobsArr[i].index_boss = 0;
		for (int j = 0; j < 100; ++j)
			jobsArr[i].arr_index_worker[j] = -1;
		jobsArr[i].code = 0;
	}
	//Job* arr_jobs = jobsArr;
	//push_jobs(arr_jobs);
	//push_jobs(jobsArr);
	return jobsArr;

}
Job* pop_jobs()
{
	Job jobs[1000];
	FILE* fp = fopen("jobs.txt", "r");

	for (int i = 0; i < 1000; ++i)
	{
		fscanf(fp, "%s ", jobs[i].name_of_job);
		fscanf(fp, "%s ", jobs[i].name_of_company);
		fscanf(fp, "%s ", jobs[i].employment_catagory);
		fscanf(fp, "%s ", jobs[i].location_area);
		fscanf(fp, "%s ", jobs[i].scope_of_the_job);
		fscanf(fp, "%s ", jobs[i].salary_range);
		fscanf(fp, "%d ", &jobs[i].index_boss);
		for (int j = 0; j < 100; ++j)
			fscanf(fp, "%d ", &jobs[i].arr_index_worker[j]);
		fscanf(fp, "%d \n", &jobs[i].code);
	}
	fclose(fp);
	return jobs;
}
void push_jobs(Job* jobs)
{
	FILE* fp = fopen("jobs.txt", "w");
	for (int i = 0; i < 1000; ++i)
	{
		fprintf(fp, "%s ", jobs[i].name_of_job);
		fprintf(fp, "%s ", jobs[i].name_of_company);
		fprintf(fp, "%s ", jobs[i].employment_catagory);
		fprintf(fp, "%s ", jobs[i].location_area);
		fprintf(fp, "%s ", jobs[i].scope_of_the_job);
		fprintf(fp, "%s ", jobs[i].salary_range);
		fprintf(fp, "%d ", jobs[i].index_boss);
		for (int j = 0; j < 100; ++j)
			fprintf(fp, "%d ", jobs[i].arr_index_worker[j]);
		fprintf(fp, "%d\n", jobs[i].code);
	}
	fclose(fp);
	return;
}
void add_job(int index)
{
	Job* arr_jobs = pop_jobs();
	int index_boss = index;
	int count = 0;

	char name_of_job[N];
	char name_of_company[N];
	char location[5][N] = { "North", "South","West","East" };
	char employment_catagory[5][N] = { "Education","Engineering","Medicene","Office" };
	char scope_of_the_job[5][N] = { "Full_time","Part_time","Third_job","Shifts" };//היקף המשרה
	char salary_range[5][N] = { "Minimum_wage","35_to_50_per_hour","50_to_100_per_hour", "100_or_more_per_hour" };//טווח השכר
	int code;
	int arr_index_worker[101];
	int choose;

	for (int i = index * 10; i < (index * 10) + 10; ++i)//לכל בוס יש מערך של 10 משרות
	{
		if (strcmp(arr_jobs[i].name_of_job, "NULL") == 0)//אם המיקום פנוי
		{
			arr_jobs[i].code = i;
			code = i;
			break;
			//נוסיף כאן את המשרה	
		}
		++count;
	}
	if (count == 10)
	{
		printf("Dear Boss You have finished your maximum job quota\n");
		return;
	}
	arr_jobs[code].index_boss = index;

	printf("Enter please name of the job:\n");
	scanf("%s", arr_jobs[code].name_of_job);

	printf("Enter please name of the company:\n");
	scanf("%s", arr_jobs[code].name_of_company);

	do {
		printf("Please Choose location Area:\n1.North\n2.South\n3.West\n4.East\n");
		scanf_s("%d", &choose);
		strcpy(arr_jobs[code].location_area, location[choose - 1]);
	} while (choose > 4 || choose < 1);

	do {
		printf("Please Choose Employment Catagory:\n1.Education\n2.Engineering\n3.Medicne\n4.Office\n");
		scanf_s("%d", &choose);
		strcpy(arr_jobs[code].employment_catagory, employment_catagory[choose - 1]);

	} while (choose > 4 || choose < 1);

	do {
		printf("Please Choose scope of the job:\n1.Full time\n2.Part time\n3.Third job\n4.Shifts\n");
		scanf_s("%d", &choose);
		strcpy(arr_jobs[code].scope_of_the_job, scope_of_the_job[choose - 1]);

	} while (choose > 4 || choose < 1);

	do {
		printf("Please Choose the salary range of the job:\n1-Minimum_wage\n2-35_to_50 per hour\n3-50 to 100 per hour\n4 -100 or more per hour\n");
		scanf_s("%d", &choose);
		strcpy(arr_jobs[code].salary_range, salary_range[choose - 1]);

	} while (choose > 4 || choose < 1);
	push_jobs(arr_jobs);
	printf("The job was successfully added");
	//לאסתייייייייייי לדחוף את מערך המשרות לקובץ בחזרה ולסגור	
}
void print_job(Job job)
{
	printf("\nname of job: %s\n", job.name_of_job);
	printf("name of company: %s\n", job.name_of_company);
	printf("employment catagory: %s\n", job.employment_catagory);
	printf("location area: %s\n", job.location_area);
	printf("scope of the job: %s\n", job.scope_of_the_job);
	printf("salary_range: %s\n", job.salary_range);
	//printf("index boss: %d\n", job.index_boss);
	/*for (int j = 0; j < 100; ++j)
		if (job.arr_index_worker[j] >= 0)
			printf("%d\n", job.arr_index_worker[j]);*/
	printf("code: %d\n", job.code);
}
void Viewing_nominees(int index, struct Employee* emp, Job* jobs)
{
	int jobInd, counter = 0, temp;
	do {
		printf("To view candidates who have applied for a particular position,\nenter a number between 0-9 \n(depending on the order in which the jobs are added to the database).");
		scanf("%d", &jobInd);
	} while (jobInd >= 10 || jobInd < 0);
	jobInd += (10 * index);
	for (int i = 0; i < 20; ++i)
	{
		temp = jobs[jobInd].arr_index_worker[i];
		if (temp >= 0 && temp <= 100)
		{
			printf_employee_details(emp[temp]);
			counter++;
		}
	}
	if (counter == 0)
		printf("No one has applied for this job\n");
}
void WorkerPersonalArea(int index, struct Employee workers[100], struct Employer bosses[100], Job* jobs)
{
	char choise;
	int choos, caseCh, counter, k;
	
	do {
		printf("Hello %s!\nWelcome to your personal area:)\n", workers[index].first_name);
		printf("Enter your choise:\n1. Edit his personal details\n2. View the history of his submissions\n3. Apply for a joband apply\n4. Disconnect from the system\n");
		//scanf("%c", &choise);
		scanf("%d", &choos);
		//choos = choise - '0';
		switch (choos)
		{
		case 1:
			workers = Change_personal_details(index, workers);
			printf("\nYour details after the apdate are:\n");
			printf_employee_details(workers[index]);
			//put_data_file_employee(workers, 100);
			printf("\n");

			break;
		case 2:
			k = 1;
			counter = 0;
			for (int i = 0; i < 300; ++i)
			{
				for (int j = 0; j < 100; ++j)
				{
					if (jobs[i].arr_index_worker[j] == index)
					{
						printf("job %d\n", k);
						++k;
						print_job(jobs[i]);
						++counter;
						printf("\n");
						break;
					}

				}
			}
			if (counter == 0)
				printf("You haven't submitted a job offer yet\n");

			break;
		case 3:
			do {
				printf("enter:\n1- To view all published jobs\n2- To view published jobs by filtering\n3- To apply for a job\n4-Back to Main Menu\n");
				scanf("%d", &caseCh);

				switch (caseCh)
				{
				case 1:
					job_search_no_filter(jobs);
					break;
				case 2:
					job_search_filter(jobs);
					break;
				case 3:
					jobs = applying(index, jobs, workers);
					break;
				default:
					break;
				}
			} while (caseCh != 4);
			break;
		case 4:
			break;
		default:
			break;
		}
	} while (choos != 4);
	push_jobs(jobs);
}
void EmployerPersonalArea(int index, struct Employee workers[100], struct Employer bosses[100], Job* jobs)
{
	int choos = 0;
	do {
		printf("Hello %s:\nWelcome to your personal area:)\n", bosses[index].first_name);
		printf("Enter your choice:\n1 - Job posting history\n2 - Personal details\n3 - Creating and advertising a new job\n4 - Viewing candidates who have applied - without filtering\n5 - Viewing candidates who have applied - by screening\n6  - Disengagement from the system\n");
		scanf("%d", &choos);
		switch (choos)
		{

		case 1:
			/*	for (int i = 0; i < 10; ++i)
				{
					if (cmp(jobs[index * 10 + i].name_of_job, "NULL") != 0)
					{
						print_job(jobs[index * 10 + i]);
					}
				}*/
			break;
		case 2:
			printf_employer_details(bosses[index]);
			break;
		case 3:
			add_job(index);
			break;
		case 4:
			Viewing_nominees(index, workers, jobs);
			break;
		case 5:
			//Viewing_nominees_search(index, workers, jobs);
			break;
		case 6:
			printf("Good buy");
			break;
		default:
			break;
		}

	} while (choos != 6);
}
void job_search_no_filter(Job* jobs)
{
	int counter = 1;
	printf("The vacancies are:\n");
	for (int x = 0; x < 900; ++x)
	{
		if (strcmp(jobs[x].name_of_company, "NULL") != 0)
		{
			printf("%d:\n", counter);
			++counter;
			print_job(jobs[x]);
			printf("\n");
		}
	}
	if (counter == 1)
		printf("No vacancy at this time");
}
void printf_employee_details(struct Employee w)// פרטי עובד
{
	printf("first name: ");
	puts(w.first_name);
	printf("last name: ");
	puts(w.last_name);
	printf("gender: ");
	puts(w.gender);
	printf("id: ");
	printf("%s\n", w.id);
	printf("age: ");
	printf("%d\n", w.age);
	printf("phone number: ");
	puts(w.phone_number);
	printf("password: ");
	printf("%d\n", w.password);
	printf("emmail: ");
	puts(w.Email);
	printf("living area: ");
	puts(w.living_area);
	printf("Driving_License: ");
	puts(w.Driving_License);
	printf("Education_level: ");
	puts(w.Education_level);
	printf("Employment_Catagory: ");
	puts(w.Employment_Catagory);
}
void printf_employer_details(struct Employer w)// פרטי מעביד
{
	printf("first name: ");
	puts(w.first_name);
	printf("last name: ");
	puts(w.last_name);
	printf("gender: ");
	puts(w.gender);
	printf("id: ");
	printf("%s", w.id);
	printf("\nage: ");
	printf("%d\n", w.age);
	printf("phone number: ");
	puts(w.phone_number);
	printf("password: ");
	printf("%d\n", w.password);
	printf("emmail: ");
	puts(w.Email);
}
struct Employee read_Employee_Data_File(FILE* fp)
{
	struct Employee employee;
	//FILE* fp = fopen("C:\\Users\\Administrator\\source\\repos\\good job\\Employee.txt", "r");
	if (!fp)
	{
		printf("Couldn't Open File!\n");
		exit(-1);
	}
	fscanf(fp, "%s %s %s %s %d %s %d %s %s %s %s %s ", employee.first_name, employee.last_name, employee.gender, employee.id, &employee.age, employee.phone_number, &employee.password, employee.Email, employee.living_area, employee.Driving_License, employee.Education_level, employee.Employment_Catagory);
	for (int j = 0; j < 10; ++j)
	{
		fscanf(fp, "%d ", &employee.apply_jobs[j]);
	}
	return employee;
}
void print_data_file_employer(struct Employer emp)
{
	FILE* fp = fopen("Employer.txt", "a");
	if (!fp)
		return;
	fprintf(fp, "%s %s %s %s %d %s %d %s %s\n", emp.first_name, emp.last_name, emp.gender, emp.id, &emp.age, emp.phone_number, emp.password, emp.Email, emp.company_name);
	fclose(fp);
	return;
}
void print_data_file_employee(struct Employee worker)
{
	FILE* fp = fopen("Employee.txt", "a");
	fprintf(fp, "%s ", worker.first_name);
	fprintf(fp, "%s ", worker.last_name);
	fprintf(fp, "%s ", worker.gender);
	fprintf(fp, "%s ", worker.id);
	fprintf(fp, "%d ", worker.age);
	fprintf(fp, "%s ", worker.phone_number);
	fprintf(fp, "%d ", worker.password);
	fprintf(fp, "%s ", worker.Email);
	fprintf(fp, "%s ", worker.living_area);
	fprintf(fp, "%s ", worker.Driving_License);
	fprintf(fp, "%s ", worker.Education_level);
	fprintf(fp, "%s ", worker.Employment_Catagory);
	for (int j = 0; j < 10; ++j)
		fprintf(fp, "%d ", -1);
	fprintf(fp, "\n");
	fclose(fp);
}
void put_data_file_employee(struct Employee* worker, int size)
{
	FILE* fp = fopen("Employee.txt", "w");
	for (int i = 0; i < size; ++i)
	{
		if (worker[i].first_name!=NULL) {
			fprintf(fp, "%s ", worker[i].first_name);
			fprintf(fp, "%s ", worker[i].last_name);
			fprintf(fp, "%s ", worker[i].gender);
			fprintf(fp, "%s ", worker[i].id);
			fprintf(fp, "%d ", worker[i].age);
			fprintf(fp, "%s ", worker[i].phone_number);
			fprintf(fp, "%d ", worker[i].password);
			fprintf(fp, "%s ", worker[i].Email);
			fprintf(fp, "%s ", worker[i].living_area);
			fprintf(fp, "%s ", worker[i].Driving_License);
			fprintf(fp, "%s ", worker[i].Education_level);
			fprintf(fp, "%s ", worker[i].Employment_Catagory);
			for (int j = 0; j < 10; ++j)
				fprintf(fp, "%d ", worker[i].apply_jobs[j]);
			fprintf(fp, "\n");
		}
	}
	fclose(fp);
}
void logIn(struct Employee workers[100], struct Employer bosses[100], Job* jobs)//המשתמש נכנס למערכת
{
	int numOfBosses = 100;
	int numOfWorkers = 100;
	char id[10];
	int temp;
	int index = -1;
	int password;
	printf("-------Login-------:\n ");// user inserts id number,system checks if its exists.
	do {
		printf("Enter Your Id:\n");
		scanf("%s", id);
		for (int i = 0; i < numOfWorkers; ++i)
		{
			if (strcmp(workers[i].id, id) == 0)
				index = i;
		}
		if (index == -1)
		{
			for (int i = 0; i < numOfBosses; ++i)
			{
				if (strcmp(bosses[i].id, id) == 0)
					index = (i + numOfWorkers);
			}
		}
		if (index == -1)
			printf("error!\n There is no user with this id please try again");
	} while (index == -1);
	do {
		temp = 0;
		printf("Please insert your password\n");//המשתמש מכניס את הסיסמא שלו והמערכת בודקת האם הסיסמא נכונה
		scanf_s("%d", &password);
		if (index < numOfWorkers)
		{
			if (password != workers[index].password)
			{
				printf("error!\n Your password is incorrect please try again");
				++temp;
			}
		}
		if (index >= numOfWorkers)
		{
			if (password != bosses[index - numOfWorkers].password)
			{
				printf("error!\n Your password is incorrect please try again");
				++temp;
			}
		}
	} while (temp > 0);
	if (index < numOfWorkers)
	{
		WorkerPersonalArea(index, workers, bosses, jobs);
	}
	if (index >= numOfWorkers)
	{
		EmployerPersonalArea(index - numOfWorkers, workers, bosses, jobs);
	}
	return;
}
struct Employer read_Employer_Data_File(FILE* fp)
{
	struct Employer employer;
	int i = 0;
	//FILE* fp = fopen("C:\\Users\\Administrator\\source\\repos\\good job\\Employer.txt", "r");
	if (!fp)
	{
		printf("Couldn't Open File!\n");
		exit(-1);
	}


	fscanf(fp, "%s , ", employer.first_name);
	fscanf(fp, "%s , ", employer.last_name);
	fscanf(fp, "%s , ", employer.gender);
	fscanf(fp, "%s , ", (employer.id));
	fscanf(fp, "%d , ", &(employer.age));
	fscanf(fp, "%s , ", employer.phone_number);
	fscanf(fp, "%d , ", &(employer.password));
	fscanf(fp, "%s , ", (employer.Email));
	fscanf(fp, "%s , ", (employer.company_name));

	//fclose(fp);
	return employer;
}
void init_employee()
{
	int gender_choose, licence, level_educ, policies;
	struct Employee worker;
	char other1[20];
	char location[5][20] = { "North", "South","West","East" };
	char employment_catagory[20][20] = { "education","engineering","medicene","office" };
	char educ_level[4][30] = { "SchoolYears" ,"Student" ,"BA" , "MA" };
	char Driving_License[3][7] = { "yes", "no" };
	int choose, choose_educ;
	printf("Please Enter First Name:\n");
	scanf("%s", (worker.first_name));
	//printf("%s\n", worker.first_name);
	printf("Please Enter Last Name:\n");
	scanf("%s", (worker.last_name));
	//printf("%s\n", worker.last_name);
	do {
		printf("Please Enter ID Number (9 digits):\n");
		scanf("%s", (worker.id));
		if (strlen(worker.id) != 9)
		{
			printf("Invaild ID Number!\n");
		}
	} while (strlen(worker.id) != 9);
	//printf("%s\n", worker.id);
	do {
		printf("Please Enter Your Age:\n");
		scanf("%d", &(worker.age));
		if (worker.age < 16 || worker.age > 60)
		{
			printf("Illegal age to look for a job.\n");
		}
		//printf("%d\n", worker.age);
	} while (worker.age < 16 || worker.age > 60);
	do {
		printf("Enter Your Phone Number (10 digits):\n");
		scanf("%s", (worker.phone_number));
		if (strlen(worker.phone_number) != 10)
		{
			printf("Phone Number Must Contain 10 Digits.\n");
		}
	} while (strlen(worker.phone_number) != 10);
	//printf("%s\n", worker.phone_number);
	do {
		printf("Please Choose Your Password (password must contain 6-10 digits):\n");
		scanf("%d", &worker.password);
		if (worker.password < 100000 || worker.password > 9999999999)
			printf("Expected 6-10 Digits.");
	} while (worker.password < 100000 || worker.password > 9999999999);
	//printf("%d\n", worker.password);
	do {
		printf("Please Choose a Gender:\n1.Male\n2.Female\n");
		scanf("%d", &gender_choose);
		if (gender_choose == 1)
			strcpy(worker.gender, "Male");
		if (gender_choose == 2)
			strcpy(worker.gender, "Female");
	} while (gender_choose > 2 && gender_choose < 1);
	//printf("%s\n", worker.gender);
	printf("Please Enter Your Email Address:\n");
	scanf("%s", (worker.Email));
	//printf("%s\n", worker.Email);
	do {
		printf("Please Choose Living Area:\n1.North\n2.South\n3.West\n4.East\n");
		scanf("%d", &choose);
		strcpy(worker.living_area, location[choose - 1]);
		//	printf("%s\n", worker.living_area);//check=good
	} while (choose > 4 && gender_choose < 1);
	do {
		printf("Do You Own A Driving License?\n1.yes\n2.No\n");
		scanf("%d", &licence);
		if (licence == 1)
			strcpy(worker.Driving_License, "yes");
		//fprintf(fp, "%s", (worker.Driving_License));
		if (licence == 2)
			strcpy(worker.Driving_License, "No");
	} while (licence < 1 || licence>2);
	//	printf("%s\n", worker.Driving_License);//check=good
	printf("Please Enter Employment Catagory:\n1.Education\n2.Engineering\n3.Medicne\n4.Office\n");
	scanf("%d", &choose_educ);
	strcpy(worker.Employment_Catagory, employment_catagory[choose_educ - 1]);
	//printf("%s", worker.Employment_Catagory);//check=good
	printf("Please Select education Level:\n1.12 school years\n2.student\n3.B.A\n4.M.A\n");
	scanf("%d", &level_educ);
	strcpy(worker.Education_level, educ_level[level_educ - 1]);
	//printf(worker.Education_level);//check=good
	printf("Final Step: In Order To Complete The Registration Process Please Enter 1 To Approve Our Webstite's Policies:\n");
	for (int j = 0; j < 10; ++j)
		worker.apply_jobs[j] = -1;
	scanf("%d", &policies);
	if (policies != 1)
	{
		while (policies != 1)
		{
			printf("Please Enter 1 To Approve Our Policies and Regulations\n");
			scanf("%d", &policies);
			if (policies == 1)
			{
				break;
			}
		}
	}

	else
	{
		printf("%s , Welcome To Our Website! You Have Succesfuly Signed-up.\n", worker.first_name);
		print_data_file_employee(worker);
	}
	//return worker;
}
struct Employer init_employer()
{
	int gender_choose, policies;
	//char first_name[S];
	struct Employer emp;
	printf("Please Enter First Name:\n");
	scanf("%s", (emp.first_name));
	//printf("%s\n", emp.first_name);
	//char last_name[S];
	printf("Please Enter Last Name:\n");
	scanf("%s", (emp.last_name));
	//printf("%s\n", emp.last_name);
	//char gender[S];
	printf("Please Choose a Gender:\n1.Male\n2.Female\n");
	scanf("%d", &gender_choose);
	if (gender_choose == 1)
		strcpy(emp.gender, "Male");
	if (gender_choose == 2)
		strcpy(emp.gender, "Female");
	//printf("%s\n", emp.gender);
	//char id[S];
	do {
		printf("Please Enter ID Number (9 digits):\n");
		scanf("%s", (emp.id));
		//printf("%s\n", emp.id);
		if (strlen(emp.id) != 9)
			printf("Invaild ID Number!\n");
	} while (strlen(emp.id) != 9);

	//int age;
	do {
		printf("Please Enter Your Age:\n");
		scanf("%d", &(emp.age));
		//printf("%d\n", emp.age);
		if (emp.age < 16 || emp.age > 60)
			printf("Illegal age to look for a job.");
	} while (emp.age < 16 || emp.age > 60);
	//char phone_number[S];
	do {
		printf("Enter Your Phone Number (10 digits):\n");
		scanf("%s", (emp.phone_number));
		if (strlen(emp.phone_number) != 10)
			printf("Phone Number Must Contain 10 Digits.\n");
	} while (strlen(emp.phone_number) != 10);

	//int password;
	do {
		printf("Please Choose Your Password (password must contain 6-10 digits):\n");
		scanf("%d", &(emp.password));
		if (emp.password < 99999 || emp.password>9999999999)
			printf("Expected 6-10 Digits.");
	} while (emp.password < 99999 || emp.password>9999999999);
	printf("Please Enter Your Company Name (use _ instead of space):\n");
	scanf("%s", (emp.company_name));
	//printf("%s", (emp.company_name));
	printf("Please Enter Your Email Address:\n");
	scanf("%s", (emp.Email));
	//printf("%s", (emp.Email));
	printf("Final Step: In Order To Complete The Registration Process Please Enter 1 To Approve Our Webstite's Policies:\n");
	scanf("%d", &policies);
	if (policies != 1)
		while (policies != 1)
		{
			printf("Please Enter 1 To Approve Our Policies and Regulations\n");
			scanf("%d", &policies);
		}
	printf("%s , Welcome To Our Website! You Have Succesfuly Signed-up.\n", emp.first_name);
	print_data_file_employer(emp);
	return emp;
}
void Registration_Process()
{
	int option;
	printf("Hello User! , In Order To Start With The Registration Process, Follow The Next Steps:");
	printf("\nPlease Select Type Of User:\n1.Employee\n2.Employer\n");
	scanf("%d", &option);
	switch (option)
	{
	case 1:
		init_employee();
		break;
	case 2:

		init_employer();
		break;
	}
}
void job_search_filter(Job* arr_jobs)
{
	int choose, j = 1;//*, code_of_job*/;
	char location[5][N] = { "North", "South","West","East" };
	char employment_catagory[5][N] = { "Education","Engineering","Medicene","Office" };
	char scope_of_job[5][N] = { "Full_time","Part_time","Third_job","Shifts" };//היקף המשרה
	char salary_range[5][N] = { "Minimum_wage","35_to_50_per_hour","50_to_100_per_hour", "100_or_more_per_hour" };//טווח השכר

	char temp_catagory[N], temp_area[N], temp_scope[N], temp_salary[N];//תחום,איזור,היקף,שכר
	do {
		printf("Please Choose the location area of the work:\n1.North\n2.South\n3.West\n4.East\n");
		scanf("%d", &choose);
		strcpy(temp_area, location[choose - 1]);
		printf(temp_area);//check=good
	} while (choose > 4 || choose < 1);

	do {
		printf("Please Choose Employment Catagory:\n1.Education\n2.Engineering\n3.Medicne\n4.Office\n");
		scanf("%d", &choose);
		strcpy(temp_catagory, employment_catagory[choose - 1]);
		printf(temp_catagory);//check=good
	} while (choose > 4 || choose < 1);

	do {
		printf("Please Choose scope of the job : \n1.Full time\n2.Part time\n3.Third job\n4.Shifts\n");
		scanf("%d", &choose);
		strcpy(temp_scope, scope_of_job[choose - 1]);
		printf(temp_scope);//check=good
		printf("\n");
	} while (choose > 4 || choose < 1);
	do {
		printf("Please Choose the salary range of the job:\n1.Minimum wage\n2.35 to 50 per hour\n3.50 to 100 per hour\n4.100 or more per hour\n");
		scanf("%d", &choose);
		strcpy(temp_salary, salary_range[choose - 1]);
		printf(temp_salary);//check=good
		printf("\n");
	} while (choose > 4 || choose < 1);
	printf("The jobs found are right for you:\n");
	for (int x = 0; x < 1000; ++x)
	{
		if (strcmp(arr_jobs[x].employment_catagory, temp_catagory) == 0 &&
			strcmp(arr_jobs[x].location_area, temp_area) == 0 &&
			strcmp(arr_jobs[x].scope_of_the_job, temp_scope) == 0 &&
			strcmp(arr_jobs[x].salary_range, temp_salary) == 0)
		{
			printf("\n%d:\n", j);
			print_job(arr_jobs[x]);
			++j;
		}

	}
	if (j == 1)
		printf("No vacancy for the filter you requested");
	return;
}
Job* applying(int index, Job jobs[1000], struct Employee* workers)
{
	int code;
	int j = 0, i;
	printf("Enter the code of the job you choose\n");
	scanf("%d", &code);
	//(j < 10)
	if (strcmp(jobs[code].name_of_company, "NULL") != 0)
	{
		for (i = 0; i < 100; ++i)
		{

			if (jobs[code].arr_index_worker[i] < 0)
			{
				jobs[code].arr_index_worker[i] = index;
				break;
			}
		}
	}
	printf("Your job offer was successfully accepted\n\n");
	return jobs;
}
void Viewing_nominees_search(int index, struct Employee* workers, Job* jobs)
{
	int choose, agefirst, agelast;
	int firstage[] = { 18,25,35,45 };
	int lastage[] = { 25,35,45,120 };
	char location[5][N] = { "North", "South","West","East" };
	char employment_catagory[5][N] = { "Education","Engineering","Medicene","Office" };
	char temp_catagory[N], temp_area[N];//תחום,איזור,היקף,שכר
	int jobInd = 0;
	do {
		printf("enter job index");
		scanf("%d", &jobInd);
	} while (jobInd > 10 || jobInd <= 0);
	jobInd += (10 * index);
	do {
		printf("Please Choose the location area of the work:\n1.North\n2.South\n.3.West\n4.East\n");
		scanf("%d", &choose);
		strcpy(temp_area, location[choose - 1]);
		printf(temp_area);//check=good
	} while (choose > 4 || choose < 1);

	do {
		printf("Please Choose Employment Catagory:\n1.Education\n2.Engineering\n3.Medicne\n4.Office\n");
		scanf("%d", &choose);
		strcpy(temp_catagory, employment_catagory[choose - 1]);
		printf(temp_catagory);//check=good
	} while (choose > 4 || choose < 1);
	do {
		printf("Please select the age:\n1.18-25\n2.25-35\n3.35-45\n4.40+\n");
		scanf("%d", &choose);
		agefirst = firstage[choose - 1];
		agelast = lastage[choose - 1];
		printf("%d , %d", agefirst, agelast);//check=good
	} while (choose > 4 || choose < 1);
	printf("The people who applied for this job are:\n");
	for (int x = 0; x < 1000; ++x)
	{
		int temp = jobs[jobInd].arr_index_worker[x];
		if (temp > -1)
			if (workers[temp].age >= agefirst && workers[temp].age <= agelast && strcmp(workers[temp].living_area, temp_area) == 0 && strcmp(workers[temp].Employment_Catagory, temp_catagory) == 0)
				printf_employee_details(workers[x]);

	}


	for (int i = 0; i < 100; ++i)
	{
		if (jobs[jobInd].arr_index_worker[i] > -1)
			printf_employee_details(workers[i]);
	}
}
struct Employee* Change_personal_details(int index, struct Employee* workers)
{
	char Location[5][N] = { "North","South","West","East" };
	int y, temp;
	char f[S], r[N];
	printf("You can change the personal details according to the number you choose:\n1. Change of last name\n2. Change of living area\n3. Phone change\n4. Change email address\n");
	scanf_s("%d", &y);
	while (y <1 || y >4)
	{
		printf("You can change the personal details according to the number you choose:\n1. Change last name\n2. Change living area\n3. Change puone number\n4. Change email address\n");
		scanf("%d", &y);
	}
	if (y == 1)// שינוי שם משפחה 
	{
		printf("Please press the new last name\n");
		scanf("%s", f);
		//gets(f,S);
		strcpy(workers[index].last_name, f);
		//temp = strlen(f);
		//z[index].last_name[temp + 1] = '\0';
	}
	else if (y == 2)// שינוי מקום מגורים
	{
		printf("Select a number of the new living area:\n1 - North\n2 - South\n3 - West\n4 - East\n");
		scanf("%d", &temp);
		if (temp == 1 || temp == 2 || temp == 3 || temp == 4)
		{
			strcpy(workers[index].living_area, Location[temp - 1]);
		}

	}
	else if (y == 3)// שינוי סיסמה
	{
		printf("Please type the new phone number up to 10 characters\n");
		scanf("%s", f);
		strcpy(workers[index].phone_number, f);

	}
	else if (y == 4)//שינוי מייל
	{
		printf("Please type the new email\n");
		scanf("%s", r);
		strcpy(workers[index].Email, r);
	}
	printf("The change was created successfully\n");
	return workers;
}
