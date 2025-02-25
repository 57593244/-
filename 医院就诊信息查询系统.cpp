#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct record {     //就诊记录信息结构体
	char id[20];
	char name[20];
	int date;
	char proom[20];
	char symptom[20];
	record* next;
};
typedef struct patient {    //病人信息结构体
	char id[20];
	char proom[20];
	char name[20];
	char idnum[20];
	char address[20];
	char tel[20];
	patient* next1;
	record* next2;
};
typedef struct room {      //科室信息结构体
	char id[20];
	char name[20];
	char address[20];
	char tel[20];
	patient* next1;
	room* next2;
};
void insert();//录入信息函数申明
void modify();//修改信息函数申明
void mydelete();//删除信息函数申明
void search();// 查询信息函数申明
void statistics();// 数据统计函数申明
void openfile();//将已保存的文件打开的函数申明
FILE* fp;//定义文件全局变量
room* room_head = NULL, * room_tail = NULL, * room_p = NULL;
patient* patient_tail = NULL, * patient_p = NULL;
record* record_p = NULL, * record_tail = NULL;
int main() {
	printf("------------------------------------\n");
	printf("****欢迎进入医院就诊信息查询系统****\n");
	printf("------------------------------------\n");
	int mainorder;
	openfile();
	while (1) {
		printf("1.录入就诊信息\n");
		printf("2.修改就诊信息\n");
		printf("3.删除就诊信息\n");
		printf("4.查询信息\n");
		printf("5.查看数据统计结果\n");
		printf("0.退出\n");
		printf("请输入所需的服务编号：\n");
		scanf("%d", &mainorder);
		switch (mainorder) {
		     case 1:insert(); break;
			 case 2:modify(); break;
			 case 3:mydelete(); break;
			 case 4:search(); break;
			 case 5:statistics(); break;
			 case 0:return 0;
			 default:printf("请输入正确的编号\n"); break;
		}
	}
}
void insert()  {  //录入信息函数
	while (1) {
		printf("-----------------------\n");
		printf("||请选择：            ||\n");
		printf("||1.录入科室基本信息  ||\n");
		printf("||2.录入病人基本信息  ||\n");
		printf("||3.录入病人就诊记录  ||\n");
		printf("||0.返回              ||\n");
		printf("-----------------------\n");
		int order, n, i,date;
		int flag1 = 0; //flag和flag1变量都用于标记
		int flag = 1;
		char id[20];
		char proom[20];
		char name[20];
		char idnum[20];
		char address[20];
		char tel[20];
		char symptom[20];
		scanf("%d", &order);
		switch (order) {
		case 1: //录入科室信息
			if ((fp = fopen("room.txt", "a+")) == NULL) {
				printf("文件打开失败\n");
				exit(0);
			}
			printf("请输入录入的数量：\n");
			scanf("%d", &n);
			printf("请按照“科室编号 科室名称 科室地址 联系电话”的格式输入\n");
			for (i = 0; i < n; i++) {
			start1:scanf("%s %s %s %s", id, name, address, tel);
				for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
					if (strcmp(room_p->id, id) == 0) {
						printf("输入了重复的编号，请重新输入\n");
						goto start1;
					}
				}
				fprintf(fp, "科室%s %s %s %s\n", id, name, address, tel);
				room_p = (room*)malloc(sizeof(room));
				strcpy(room_p->id, id);
				strcpy(room_p->name, name);
				strcpy(room_p->address, address);
				strcpy(room_p->tel, tel);
				room_p->next1 = NULL;
				room_p->next2 = NULL;
				if (room_head == NULL) room_head = room_p;
				else room_tail->next2 = room_p;
				room_tail = room_p;
			}
			if (fclose(fp)) {
				printf("文件无法关闭\n");
				exit(0);
			}
			printf("成功录入%d个\n", n);
			break;
		case 2: //录入病人信息
			flag = 1; //标记变量还原
			if ((fp = fopen("patient.txt", "a+")) == NULL) {
				printf("文件打开失败\n");
				exit(0);
			}
			printf("请输入录入的数量：\n");
			scanf("%d", &n);
			printf("请按照“病人编号 就诊科室编号 病人姓名 身份证号 住址 联系电话”的格式输入\n");
			for (i = 0; i < n; i++) {
			start2:scanf("%s %s %s %s %s %s", id, proom, name, idnum, address, tel);
				patient_p = (patient*)malloc(sizeof(patient));
				for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
					for (patient_p = room_p->next1; patient_p != NULL; patient_p = patient_p->next1) {
						if (strcmp(patient_p->id, id) == 0) {
							printf("输入了重复的编号，请重新输入\n");
							goto start2;
						}
					}
				}
				for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
					if (strcmp(room_p->id,proom)==0) {
						patient_p = (patient*)malloc(sizeof(patient));
						strcpy(patient_p->id, id);
						strcpy(patient_p->proom, proom);
						strcpy(patient_p->name, name);
						strcpy(patient_p->idnum, idnum);
						strcpy(patient_p->address, address);
						strcpy(patient_p->tel, tel);
						patient_p->next1 = NULL;
						patient_p->next2 = NULL;
						if (room_p->next1 == NULL) room_p->next1 = patient_p;
						else patient_tail->next1 = patient_p;
						patient_tail = patient_p;
						flag = 0;
					}
				}
					if (flag) {
						printf("输入的科室编号不存在，请重新输入\n");
						goto start2;
					}
				fprintf(fp, "%s 科室%s %s %s %s %s\n", id, proom, name, idnum, address, tel);
			}
			if (fclose(fp)) {
				printf("文件无法关闭\n");
				exit(0);
			}
			printf("成功录入%d个\n", n);
			break;
		case 3://录入就诊记录
			flag = 1;     //标记变量还原
			if ((fp = fopen("record.txt", "a+")) == NULL) {
				printf("文件打开失败\n");
				exit(0);
			}
			printf("请输入录入的数量：\n");
			scanf("%d", &n);
			printf("请按照“病人编号 病人姓名 就诊时间（输入八位数字，例如20191230）就诊科室编号 症状信息”的格式输入\n");
			for (i = 0; i < n; i++) {
			start3:scanf("%s %s %d %s %s", id, name, &date, proom, symptom);
				room_p = (room*)malloc(sizeof(room));
				patient_p = (patient*)malloc(sizeof(patient));
				for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
					if (strcmp(room_p->id, proom) == 0) {
						for (patient_p = room_p->next1; patient_p != NULL; patient_p = patient_p->next1) {
							if (strcmp(patient_p->id, id) == 0) {
								record_p = (record*)malloc(sizeof(record));
								strcpy(record_p->id, id);
								strcpy(record_p->name, name);
								record_p->date = date;
								strcpy(record_p->proom, proom);
								strcpy(record_p->symptom, symptom);
								record_p->next = NULL;
								if (patient_p->next2 == NULL) patient_p->next2 = record_p;
								else record_tail->next = record_p;
								record_tail = record_p;
								flag = 0;
								flag1 = 1;
								break;
							}
						}
					}
					if (flag1) break;
				}
				if (flag) {
					printf("输入的科室或者病人编号不存在，请重新输入\n");
					goto start3;
				}
				fprintf(fp, "%s %s %d 科室%s %s\n", id, name, date, proom, symptom);
			}
			if (fclose(fp)) {
				printf("文件无法关闭\n");
				exit(0);
			}
			printf("成功录入%d个\n", n);
			break;
		case 0: return;
		default:printf("请输入正确的编号\n"); break;
		}
	}
}
void modify() {   //修改信息函数
	while (1) {
		int flag = 1,flag1=0; //用于标记是否找到目标的变量
		int order,i,n;
		char arr[20];
		char name[20];
		char idnum[20];
		char address[20];
		char tel[20];
		char symptom[20];
		int date;
		printf("-----------------------\n");
		printf("||请选择：            ||\n");
		printf("||1.修改科室基本信息  ||\n");
		printf("||2.修改病人基本信息  ||\n");
		printf("||3.修改病人就诊记录  ||\n");
		printf("||0.返回              ||\n");
		printf("-----------------------\n");
		scanf("%d", &order);
		switch (order) {
		case 1:
			flag = 1;
			printf("请输入需要修改的科室编号：");
			scanf("%s", arr);
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
				if (strcmp(room_p->id, arr) == 0) {
					printf("请输入修改的信息，按照“科室名称 科室地址 联系电话”的格式输入\n");
					scanf("%s %s %s", name, address, tel);
					strcpy(room_p->name, name);
					strcpy(room_p->address, address);
					strcpy(room_p->tel, tel);
					flag = 0;
					break;
				}
			}
			if (flag) {
				printf("未找到该科室编号\n");
				break;
			}
			if ((fp = fopen("room.txt", "w+")) == NULL) {
				printf("文件打开失败\n");
				exit(0);
			}
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2)
				fprintf(fp, "科室%s %s %s %s\n", room_p->id, room_p->name, room_p->address, room_p->tel);
			if (fclose(fp)) {
				printf("文件无法关闭\n");
				exit(0);
			}
			printf("修改成功！\n");
			break;
		case 2:
			flag = 1;
			printf("请输入需要修改的病人编号：");
			scanf("%s", arr);
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
				for (patient_p = room_p->next1; patient_p != NULL; patient_p = patient_p->next1) {
					if (strcmp(patient_p->id, arr) == 0) {
						printf("请输入修改的信息，“病人姓名 身份证号 住址 联系电话”的格式输入\n");
						scanf("%s %s %s %s", name, idnum, address, tel);
						strcpy(patient_p->name, name);
						strcpy(patient_p->address, address);
						strcpy(patient_p->tel, tel);
						flag = 0;
						break;
					}
				}
			}
			if (flag) {
				printf("未找到该病人\n");
				break;
			}
			if ((fp = fopen("patient.txt", "w+")) == NULL) {
				printf("文件打开失败\n");
				exit(0);
			}
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
				for (patient_p = room_p->next1; patient_p != NULL; patient_p = patient_p->next1) {
					fprintf(fp, "%s 科室%s %s %s %s %s\n", patient_p->id, patient_p->proom, patient_p->name, patient_p->idnum, patient_p->address, patient_p->tel);
				}
			}
			if (fclose(fp)) {
				printf("文件无法关闭\n");
				exit(0);
			}
			printf("修改成功！\n");
			break;
		case 3:
			flag = 1;
			flag1 = 0;
			printf("请输入需要修改就诊记录的病人编号：");
			scanf("%s", arr);
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
				for (patient_p = room_p->next1; patient_p != NULL; patient_p = patient_p->next1) {
					if (strcmp(patient_p->id, arr) == 0) {
						i = 1;
						for (record_p = patient_p->next2; record_p != NULL; record_p = record_p->next) {
							printf("%d:%s %s %d 科室%s %s\n", i,record_p->id, record_p->name, record_p->date, record_p->proom, record_p->symptom);
							i++;
						}
						printf("请选择要修改的就诊记录：");
						scanf("%d", &n);
						printf("请输入修改的信息，按照“就诊时间（输入八位数字，例如20191230） 症状信息”的格式输入\n");
						scanf("%d %s", &date, symptom);
						record_p = patient_p->next2; 
						i = 1; 
						while (record_p != NULL && i < n)  record_p = record_p->next;
						record_p->date = date;
						strcpy(record_p->symptom, symptom);
						flag = 0;
						flag1 = 1;
						break;
					}
				}
				if (flag1) break;
			}
			if (flag) {
				printf("未找到该病人\n");
				break;
			}
			if ((fp = fopen("record.txt", "w+")) == NULL) {
				printf("文件打开失败\n");
				exit(0);
			}
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2)
				for (patient_p = room_p->next1; patient_p != NULL; patient_p = patient_p->next1)
					for (record_p = patient_p->next2; record_p != NULL; record_p = record_p->next)
						fprintf(fp, "%s %s %d 科室%s %s %s\n", record_p->id, record_p->name, record_p->date, record_p->proom, record_p->symptom);
			if (fclose(fp)) {
				printf("文件无法关闭\n");
				exit(0);
			}
			printf("修改成功！\n");
			break;
		case 0:return;
		default:printf("请输入正确的编号\n"); break;
		}
	}
}
void mydelete() { //删除信息函数
	while (1) {
		int order;
		int flag = 1,flag1=0;
		int i, n;
		char arr[20];
		room* room_p1 = NULL;
		patient* patient_p1 = NULL;
		record * record_p1 = NULL;
		printf("-----------------------\n");
		printf("||请选择：            ||\n");
		printf("||1.删除科室          ||\n");
		printf("||2.删除病人          ||\n");
		printf("||3.删除病人就诊记录  ||\n");
		printf("||0.返回              ||\n");
		printf("-----------------------\n");
		scanf("%d", &order);
		switch (order) {
		case 1:
			flag=1;
			room_p = (room*)malloc(sizeof(room));
			printf("请输入需要删除的科室编号：\n");
			scanf("%s", arr);
			if (strcmp(room_head->id, arr) == 0) {
				room_head = room_head->next2;
				flag = 0;
			}
			else {
				room_p = room_head; 
				while (room_p != NULL  ) {
					if (strcmp(room_p->next2->id, arr) == 0) {
						room_p1 = (room*)malloc(sizeof(room));
						room_p1 = room_p->next2;
						room_p->next2 = room_p1->next2;
						free(room_p1);
						flag = 0;
						break;
					}
					room_p = room_p->next2;
				}
				if (flag) {
					printf("未找到该科室编号\n");
					break;
				}
			}
			if ((fp = fopen("room.txt", "w+")) == NULL) {
				printf("文件打开失败\n");
				exit(0);
			}
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2)
				fprintf(fp, "科室%s %s %s %s\n", room_p->id, room_p->name, room_p->address, room_p->tel);
			if (fclose(fp)) {
				printf("文件无法关闭\n");
				exit(0);
			}
			printf("删除成功！\n");
			break;
		case 2:
			flag = 1;
			flag1 = 0;
			printf("请输入需要删除的病人编号：\n");
			scanf("%s", arr);
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
				if (strcmp(room_p->next1->id, arr) == 0) {
					room_p->next1 = room_p->next1->next1;
					flag = 0;
					break;
				}
				else {
					patient_p = room_p->next1;
					while (patient_p != NULL) {
						if (strcmp(patient_p->next1->id, arr) == 0) {
							patient_p1 = patient_p->next1;
							patient_p->next1 = patient_p1->next1;
							free(patient_p1);
							flag = 0;
							flag1 = 1;
							break;
						}
						patient_p = patient_p->next1;
					}
				}
				if (flag1) break;
			}
			if (flag) {
				printf("未找到该病人\n");
				break;
			}
			if ((fp = fopen("patient.txt", "w+")) == NULL) {
				printf("文件打开失败\n");
				exit(0);
			}
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
				for (patient_p = room_p->next1; patient_p != NULL; patient_p = patient_p->next1) {
					fprintf(fp, "%s 科室%s %s %s %s %s\n", patient_p->id, patient_p->proom, patient_p->name, patient_p->idnum, patient_p->address, patient_p->tel);
				}
			}
			if (fclose(fp)) {
				printf("文件无法关闭\n");
				exit(0);
			}
			printf("删除成功！\n");
			break;
		case 3:
			flag = 1;
			flag1 = 0;
			printf("请输入需要删除就诊记录的病人编号：");
			scanf("%s", arr);
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
				for (patient_p = room_p->next1; patient_p != NULL; patient_p = patient_p->next1) {
					if (strcmp(patient_p->id, arr) == 0) {
						i = 1;
						for (record_p = patient_p->next2; record_p != NULL; record_p = record_p->next) {
							printf("%d:%s %s %d 科室%s %s\n", i, record_p->id, record_p->name, record_p->date, record_p->proom, record_p->symptom);
							i++;
						}
						printf("请选择要删除的就诊记录：");
						scanf("%d", &n);
						record_p = patient_p->next2;
						i = 1;
						if (n == 1) {
							record_p = record_p->next;
							flag = 0;
							flag1 = 1;
							break;
						}
						else {
							while (record_p != NULL && i < n-1)  record_p = record_p->next;
							record_p1 = record_p->next;
							record_p->next = record_p1->next;
							free(record_p1);
							flag = 0;
							flag1 = 1;
							break;
						}
					}
				}
				if (flag1) break;
			}
			if (flag) {
				printf("未找到该病人\n");
				break;
			}
			if ((fp = fopen("record.txt", "w+")) == NULL) {
				printf("文件打开失败\n");
				exit(0);
			}
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2)
				for (patient_p = room_p->next1; patient_p != NULL; patient_p = patient_p->next1)
					for (record_p = patient_p->next2; record_p != NULL; record_p = record_p->next)
						fprintf(fp, "%s %s %d 科室%s %s\n", record_p->id, record_p->name, record_p->date, record_p->proom, record_p->symptom);
			if (fclose(fp)) {
				printf("文件无法关闭\n");
				exit(0);
			}
			printf("删除成功！\n");
			break;
		case 0:return;
		default:printf("请输入正确的编号\n"); break;
		}
	}
}
void search() {  // 查询信息函数
	char arr[20];
	int flag = 1, flag1 = 0;
	char idnum[20];
	char proom[20];
	int date;
	while (1) {
		int order;
		printf("-----------------------\n");
		printf("||请选择：            ||\n");
		printf("||1.查询科室信息      ||\n");
		printf("||2.查询病人就诊记录  ||\n");
		printf("||3.精确查询就诊记录  ||\n");
		printf("||0.返回              ||\n");
		printf("-----------------------\n");
		scanf("%d", &order);
		switch (order) {
		case 1:
			flag = 1;
			flag1 = 0;
			printf("请输入需要查询的科室编号：\n");
			scanf("%s", arr);
			room_p = (room*)malloc(sizeof(room));
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
				if (strcmp(room_p->id, arr) == 0) {
					printf("科室% s % s % s % s\n", room_p->id, room_p->name, room_p->address, room_p->tel);
					flag = 0;
					break;
				}
			}
			if (flag) {
				printf("未找到该科室编号\n");
				break;
			}
			break;
		case 2:
			flag = 1;
			printf("请输入需要查询就诊记录的病人编号：\n");
			scanf("%s", arr);
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
				for (patient_p = room_p->next1; patient_p != NULL; patient_p = patient_p->next1) {
					if (strcmp(patient_p->id, arr) == 0) {
						for (record_p = patient_p->next2; record_p != NULL; record_p = record_p->next) 
							printf("%s %s %d 科室%s %s\n", record_p->id, record_p->name, record_p->date, record_p->proom, record_p->symptom);
							flag=0;
					}
				}
			}
			if (flag) {
				printf("未找到该病人\n");
				break;
			}
			break;
		case 3:
			flag = 1;
			flag1 = 0;
			printf("请输入需要查询就诊记录的病人身份证号、科室编号，就诊日期（输入八位数字，例如20191230）：\n");
			scanf("%s %s %d", idnum, proom, &date);
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
				for (patient_p = room_p->next1; patient_p != NULL; patient_p = patient_p->next1) {
					if (strcmp(patient_p->idnum, idnum) == 0 && strcmp(patient_p->proom, proom) == 0) {
						for (record_p = patient_p->next2; record_p != NULL; record_p = record_p->next) {
							if (record_p->date == date) {
								printf("%s %s %d 科室%s %s\n", record_p->id, record_p->name, record_p->date, record_p->proom, record_p->symptom);
								flag = 0;
							}

						}
					}
					if (flag1) break;
				}
			}
			if (flag) {
				printf("未找到该记录\n");
				break;
			}
			break;
		case 0:return;
		default:printf("请输入正确的编号\n"); break;
		}
	}
}
void statistics() { // 数据统计函数
	int  order;
	char arr[20];
	int flag = 1, flag1 = 0;
	int count = 0;
	int date;
	int count1 = 0, count2 = 0, count3 = 0, count4 = 0;
	int birthday = 0, i;
	while (1) {
		printf("------------------------------\n");
		printf("||请选择：                   ||\n");
		printf("||1.查看日就诊人数           ||\n");
		printf("||2.查看各科室日就诊人数     ||\n");
		printf("||3.查看各年龄段就诊人数数据 ||\n");
		printf("||4.查看病人就诊历史         ||\n");
		printf("||0.返回                     ||\n");
		printf("------------------------------\n");
		scanf("%d", &order);
		switch (order) {
		case 1:
			count = 0;
			printf("请输入需要查询的日期（输入八位数字，例如20191230）：\n");
			scanf("%d", &date);
			flag = 1;
			flag1 = 0;
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
				for (patient_p = room_p->next1; patient_p != NULL; patient_p = patient_p->next1) {
					flag1=0;
						for (record_p = patient_p->next2; record_p != NULL; record_p = record_p->next) {
							if (flag1) break;
							if (record_p->date == date) {
								count++;
								flag = 0;
								flag1=1;
								break;
							}
						}
				}
			}
			if (flag) {
				printf("该日没有记录\n");
				break;
			}
			else printf("该日就诊人数为：%d\n", count);
			break;
		case 2:
			count = 0;
			printf("请输入需要查询的日期（输入八位数字，例如20191230）：\n");
			scanf("%d", &date);
			flag = 1;
			flag1=0;
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
				count = 0;
				for (patient_p = room_p->next1; patient_p != NULL; patient_p = patient_p->next1) {
					flag1=0;
					for (record_p = patient_p->next2; record_p != NULL; record_p = record_p->next) {
						if(flag1) break;
						if (record_p->date == date) {
							count++;
							flag = 0;
							flag1=1;
							break;
						}
					}
				}
				printf("科室%s：%d  ", room_p->id, count);
			}
			printf("\n");
			break;
		case 3:
			count1 = 0;
			count2 = 0;
			count3 = 0;
			count4 = 0;
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
				for (patient_p = room_p->next1; patient_p != NULL; patient_p = patient_p->next1) {
					birthday = 0;
					for (i = 6; i <= 13; i++) birthday = birthday * 10 + patient_p->idnum[i] - '0'; //提取身份证号中的生日并转化为int型整数
					if (birthday >= 19900000) count1++;
					else if (birthday >= 19700000) count2++;
					else if (birthday >= 19500000) count3++;
					else count4++;
				}
			}
			printf("30岁以下：%d人  30-50岁：%d人  50-70岁：%d人  70岁以上：%d人\n", count1, count2, count3, count4);
			break;
		case 4:
			flag = 1;
			flag1 = 0;
			printf("请输入需要查询的病人编号：\n");
			scanf("%s", arr);
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
				for (patient_p = room_p->next1; patient_p != NULL; patient_p = patient_p->next1) {
					if (strcmp(patient_p->id, arr) == 0) {
						for (record_p = patient_p->next2; record_p != NULL; record_p = record_p->next)
							printf("%s %s %d 科室%s %s\n", record_p->id, record_p->name, record_p->date, record_p->proom, record_p->symptom);
					}
				}
				if (flag1) break;
			}
			if (flag) {
				printf("未找到该病人\n");
				break;
			}
			break;
		case 0:return;
		default:printf("请输入正确的编号\n"); break;
		}
	}
}
void openfile() {  //将已保存的文件打开的函数
	char id[20];
	char proom[20];
	char name[20];
	char idnum[20];
	char address[20];
	char tel[20];
	char symptom[20];
	int date;
	if ((fp = fopen("room.txt", "a+")) == NULL) { //打开room.txt
		printf("文件打开失败\n");
		exit(0);
	}
	while(!feof(fp)){
		fscanf(fp, "科室%s %s %s %s\n", id, name, address, tel);
		room_p = (room*)malloc(sizeof(room));
		strcpy(room_p->id, id);
		strcpy(room_p->name, name);
		strcpy(room_p->address, address);
		strcpy(room_p->tel, tel);
		room_p->next1 = NULL;
		room_p->next2 = NULL;
		if (room_head == NULL) room_head = room_p;
		else room_tail->next2 = room_p;
		room_tail = room_p;
		if (feof(fp)) break;
	}
	if (fclose(fp)) {
		printf("文件无法关闭\n");
		exit(0);
	}
	if ((fp = fopen("patient.txt", "a+")) == NULL) {  //打开patient.txt
		printf("文件打开失败\n");
		exit(0);
	}
	while(!feof(fp)) {
	    fscanf(fp,"%s 科室%s %s %s %s %s\n", id, proom, name, idnum, address, tel);
		patient_p = (patient*)malloc(sizeof(patient));
		room_p = (room*)malloc(sizeof(room));
		for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
			if (strcmp(room_p->id, proom)==0) {
				patient_p = (patient*)malloc(sizeof(patient));
				strcpy(patient_p->id, id);
				strcpy(patient_p->proom, proom);
				strcpy(patient_p->name, name);
				strcpy(patient_p->idnum, idnum);
				strcpy(patient_p->address, address);
				strcpy(patient_p->tel, tel);
				patient_p->next1 = NULL;
				patient_p->next2 = NULL;
				if (room_p->next1 == NULL) room_p->next1 = patient_p;
				else patient_tail->next1 = patient_p;
				patient_tail = patient_p;
			}
		}
		if (feof(fp)) break;
	}
	if (fclose(fp)) {
		printf("文件无法关闭\n");
		exit(0);
	}
	if ((fp = fopen("record.txt", "a+")) == NULL) {//打开record.txt
		printf("文件打开失败\n");
		exit(0);
	}
	while(!feof(fp)){
	    fscanf(fp,"%s %s %d 科室%s %s\n", id, name, &date, proom, symptom);
		for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
			if (strcmp(room_p->id, proom) == 0) {
				for (patient_p = room_p->next1; patient_p != NULL; patient_p = patient_p->next1) {
					if (strcmp(patient_p->id, id) == 0) {
						strcpy(record_p->id, id);
						strcpy(record_p->name, name);
						record_p->date = date;
						strcpy(record_p->proom, proom);
						strcpy(record_p->symptom, symptom);
						record_p->next = NULL;
						if (patient_p->next2 == NULL) patient_p->next2 = record_p;
						else record_tail->next = record_p;
						record_tail = record_p;
					}
				}
			}
		}
		if (feof(fp)) break;
	}
	if (fclose(fp)) {
		printf("文件无法关闭\n");
		exit(0);
	}
}
