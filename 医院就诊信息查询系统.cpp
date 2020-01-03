#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct record {     //�����¼��Ϣ�ṹ��
	char id[20];
	char name[20];
	int date;
	char proom[20];
	char symptom[20];
	record* next;
};
typedef struct patient {    //������Ϣ�ṹ��
	char id[20];
	char proom[20];
	char name[20];
	char idnum[20];
	char address[20];
	char tel[20];
	patient* next1;
	record* next2;
};
typedef struct room {      //������Ϣ�ṹ��
	char id[20];
	char name[20];
	char address[20];
	char tel[20];
	patient* next1;
	room* next2;
};
void insert();//¼����Ϣ��������
void modify();//�޸���Ϣ��������
void mydelete();//ɾ����Ϣ��������
void search();// ��ѯ��Ϣ��������
void statistics();// ����ͳ�ƺ�������
void openfile();//���ѱ�����ļ��򿪵ĺ�������
FILE* fp;//�����ļ�ȫ�ֱ���
room* room_head = NULL, * room_tail = NULL, * room_p = NULL;
patient* patient_tail = NULL, * patient_p = NULL;
record* record_p = NULL, * record_tail = NULL;
int main() {
	printf("------------------------------------\n");
	printf("****��ӭ����ҽԺ������Ϣ��ѯϵͳ****\n");
	printf("------------------------------------\n");
	int mainorder;
	openfile();
	while (1) {
		printf("1.¼�������Ϣ\n");
		printf("2.�޸ľ�����Ϣ\n");
		printf("3.ɾ��������Ϣ\n");
		printf("4.��ѯ��Ϣ\n");
		printf("5.�鿴����ͳ�ƽ��\n");
		printf("0.�˳�\n");
		printf("����������ķ����ţ�\n");
		scanf("%d", &mainorder);
		switch (mainorder) {
		     case 1:insert(); break;
			 case 2:modify(); break;
			 case 3:mydelete(); break;
			 case 4:search(); break;
			 case 5:statistics(); break;
			 case 0:return 0;
			 default:printf("��������ȷ�ı��\n"); break;
		}
	}
}
void insert()  {  //¼����Ϣ����
	while (1) {
		printf("-----------------------\n");
		printf("||��ѡ��            ||\n");
		printf("||1.¼����һ�����Ϣ  ||\n");
		printf("||2.¼�벡�˻�����Ϣ  ||\n");
		printf("||3.¼�벡�˾����¼  ||\n");
		printf("||0.����              ||\n");
		printf("-----------------------\n");
		int order, n, i,date;
		int flag1 = 0; //flag��flag1���������ڱ��
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
		case 1: //¼�������Ϣ
			if ((fp = fopen("room.txt", "a+")) == NULL) {
				printf("�ļ���ʧ��\n");
				exit(0);
			}
			printf("������¼���������\n");
			scanf("%d", &n);
			printf("�밴�ա����ұ�� �������� ���ҵ�ַ ��ϵ�绰���ĸ�ʽ����\n");
			for (i = 0; i < n; i++) {
			start1:scanf("%s %s %s %s", id, name, address, tel);
				for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
					if (strcmp(room_p->id, id) == 0) {
						printf("�������ظ��ı�ţ�����������\n");
						goto start1;
					}
				}
				fprintf(fp, "����%s %s %s %s\n", id, name, address, tel);
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
				printf("�ļ��޷��ر�\n");
				exit(0);
			}
			printf("�ɹ�¼��%d��\n", n);
			break;
		case 2: //¼�벡����Ϣ
			flag = 1; //��Ǳ�����ԭ
			if ((fp = fopen("patient.txt", "a+")) == NULL) {
				printf("�ļ���ʧ��\n");
				exit(0);
			}
			printf("������¼���������\n");
			scanf("%d", &n);
			printf("�밴�ա����˱�� ������ұ�� �������� ���֤�� סַ ��ϵ�绰���ĸ�ʽ����\n");
			for (i = 0; i < n; i++) {
			start2:scanf("%s %s %s %s %s %s", id, proom, name, idnum, address, tel);
				patient_p = (patient*)malloc(sizeof(patient));
				for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
					for (patient_p = room_p->next1; patient_p != NULL; patient_p = patient_p->next1) {
						if (strcmp(patient_p->id, id) == 0) {
							printf("�������ظ��ı�ţ�����������\n");
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
						printf("����Ŀ��ұ�Ų����ڣ�����������\n");
						goto start2;
					}
				fprintf(fp, "%s ����%s %s %s %s %s\n", id, proom, name, idnum, address, tel);
			}
			if (fclose(fp)) {
				printf("�ļ��޷��ر�\n");
				exit(0);
			}
			printf("�ɹ�¼��%d��\n", n);
			break;
		case 3://¼������¼
			flag = 1;     //��Ǳ�����ԭ
			if ((fp = fopen("record.txt", "a+")) == NULL) {
				printf("�ļ���ʧ��\n");
				exit(0);
			}
			printf("������¼���������\n");
			scanf("%d", &n);
			printf("�밴�ա����˱�� �������� ����ʱ�䣨�����λ���֣�����20191230��������ұ�� ֢״��Ϣ���ĸ�ʽ����\n");
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
					printf("����Ŀ��һ��߲��˱�Ų����ڣ�����������\n");
					goto start3;
				}
				fprintf(fp, "%s %s %d ����%s %s\n", id, name, date, proom, symptom);
			}
			if (fclose(fp)) {
				printf("�ļ��޷��ر�\n");
				exit(0);
			}
			printf("�ɹ�¼��%d��\n", n);
			break;
		case 0: return;
		default:printf("��������ȷ�ı��\n"); break;
		}
	}
}
void modify() {   //�޸���Ϣ����
	while (1) {
		int flag = 1,flag1=0; //���ڱ���Ƿ��ҵ�Ŀ��ı���
		int order,i,n;
		char arr[20];
		char name[20];
		char idnum[20];
		char address[20];
		char tel[20];
		char symptom[20];
		int date;
		printf("-----------------------\n");
		printf("||��ѡ��            ||\n");
		printf("||1.�޸Ŀ��һ�����Ϣ  ||\n");
		printf("||2.�޸Ĳ��˻�����Ϣ  ||\n");
		printf("||3.�޸Ĳ��˾����¼  ||\n");
		printf("||0.����              ||\n");
		printf("-----------------------\n");
		scanf("%d", &order);
		switch (order) {
		case 1:
			flag = 1;
			printf("��������Ҫ�޸ĵĿ��ұ�ţ�");
			scanf("%s", arr);
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
				if (strcmp(room_p->id, arr) == 0) {
					printf("�������޸ĵ���Ϣ�����ա��������� ���ҵ�ַ ��ϵ�绰���ĸ�ʽ����\n");
					scanf("%s %s %s", name, address, tel);
					strcpy(room_p->name, name);
					strcpy(room_p->address, address);
					strcpy(room_p->tel, tel);
					flag = 0;
					break;
				}
			}
			if (flag) {
				printf("δ�ҵ��ÿ��ұ��\n");
				break;
			}
			if ((fp = fopen("room.txt", "w+")) == NULL) {
				printf("�ļ���ʧ��\n");
				exit(0);
			}
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2)
				fprintf(fp, "����%s %s %s %s\n", room_p->id, room_p->name, room_p->address, room_p->tel);
			if (fclose(fp)) {
				printf("�ļ��޷��ر�\n");
				exit(0);
			}
			printf("�޸ĳɹ���\n");
			break;
		case 2:
			flag = 1;
			printf("��������Ҫ�޸ĵĲ��˱�ţ�");
			scanf("%s", arr);
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
				for (patient_p = room_p->next1; patient_p != NULL; patient_p = patient_p->next1) {
					if (strcmp(patient_p->id, arr) == 0) {
						printf("�������޸ĵ���Ϣ������������ ���֤�� סַ ��ϵ�绰���ĸ�ʽ����\n");
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
				printf("δ�ҵ��ò���\n");
				break;
			}
			if ((fp = fopen("patient.txt", "w+")) == NULL) {
				printf("�ļ���ʧ��\n");
				exit(0);
			}
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
				for (patient_p = room_p->next1; patient_p != NULL; patient_p = patient_p->next1) {
					fprintf(fp, "%s ����%s %s %s %s %s\n", patient_p->id, patient_p->proom, patient_p->name, patient_p->idnum, patient_p->address, patient_p->tel);
				}
			}
			if (fclose(fp)) {
				printf("�ļ��޷��ر�\n");
				exit(0);
			}
			printf("�޸ĳɹ���\n");
			break;
		case 3:
			flag = 1;
			flag1 = 0;
			printf("��������Ҫ�޸ľ����¼�Ĳ��˱�ţ�");
			scanf("%s", arr);
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
				for (patient_p = room_p->next1; patient_p != NULL; patient_p = patient_p->next1) {
					if (strcmp(patient_p->id, arr) == 0) {
						i = 1;
						for (record_p = patient_p->next2; record_p != NULL; record_p = record_p->next) {
							printf("%d:%s %s %d ����%s %s\n", i,record_p->id, record_p->name, record_p->date, record_p->proom, record_p->symptom);
							i++;
						}
						printf("��ѡ��Ҫ�޸ĵľ����¼��");
						scanf("%d", &n);
						printf("�������޸ĵ���Ϣ�����ա�����ʱ�䣨�����λ���֣�����20191230�� ֢״��Ϣ���ĸ�ʽ����\n");
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
				printf("δ�ҵ��ò���\n");
				break;
			}
			if ((fp = fopen("record.txt", "w+")) == NULL) {
				printf("�ļ���ʧ��\n");
				exit(0);
			}
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2)
				for (patient_p = room_p->next1; patient_p != NULL; patient_p = patient_p->next1)
					for (record_p = patient_p->next2; record_p != NULL; record_p = record_p->next)
						fprintf(fp, "%s %s %d ����%s %s %s\n", record_p->id, record_p->name, record_p->date, record_p->proom, record_p->symptom);
			if (fclose(fp)) {
				printf("�ļ��޷��ر�\n");
				exit(0);
			}
			printf("�޸ĳɹ���\n");
			break;
		case 0:return;
		default:printf("��������ȷ�ı��\n"); break;
		}
	}
}
void mydelete() { //ɾ����Ϣ����
	while (1) {
		int order;
		int flag = 1,flag1=0;
		int i, n;
		char arr[20];
		room* room_p1 = NULL;
		patient* patient_p1 = NULL;
		record * record_p1 = NULL;
		printf("-----------------------\n");
		printf("||��ѡ��            ||\n");
		printf("||1.ɾ������          ||\n");
		printf("||2.ɾ������          ||\n");
		printf("||3.ɾ�����˾����¼  ||\n");
		printf("||0.����              ||\n");
		printf("-----------------------\n");
		scanf("%d", &order);
		switch (order) {
		case 1:
			flag=1;
			room_p = (room*)malloc(sizeof(room));
			printf("��������Ҫɾ���Ŀ��ұ�ţ�\n");
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
					printf("δ�ҵ��ÿ��ұ��\n");
					break;
				}
			}
			if ((fp = fopen("room.txt", "w+")) == NULL) {
				printf("�ļ���ʧ��\n");
				exit(0);
			}
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2)
				fprintf(fp, "����%s %s %s %s\n", room_p->id, room_p->name, room_p->address, room_p->tel);
			if (fclose(fp)) {
				printf("�ļ��޷��ر�\n");
				exit(0);
			}
			printf("ɾ���ɹ���\n");
			break;
		case 2:
			flag = 1;
			flag1 = 0;
			printf("��������Ҫɾ���Ĳ��˱�ţ�\n");
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
				printf("δ�ҵ��ò���\n");
				break;
			}
			if ((fp = fopen("patient.txt", "w+")) == NULL) {
				printf("�ļ���ʧ��\n");
				exit(0);
			}
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
				for (patient_p = room_p->next1; patient_p != NULL; patient_p = patient_p->next1) {
					fprintf(fp, "%s ����%s %s %s %s %s\n", patient_p->id, patient_p->proom, patient_p->name, patient_p->idnum, patient_p->address, patient_p->tel);
				}
			}
			if (fclose(fp)) {
				printf("�ļ��޷��ر�\n");
				exit(0);
			}
			printf("ɾ���ɹ���\n");
			break;
		case 3:
			flag = 1;
			flag1 = 0;
			printf("��������Ҫɾ�������¼�Ĳ��˱�ţ�");
			scanf("%s", arr);
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
				for (patient_p = room_p->next1; patient_p != NULL; patient_p = patient_p->next1) {
					if (strcmp(patient_p->id, arr) == 0) {
						i = 1;
						for (record_p = patient_p->next2; record_p != NULL; record_p = record_p->next) {
							printf("%d:%s %s %d ����%s %s\n", i, record_p->id, record_p->name, record_p->date, record_p->proom, record_p->symptom);
							i++;
						}
						printf("��ѡ��Ҫɾ���ľ����¼��");
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
				printf("δ�ҵ��ò���\n");
				break;
			}
			if ((fp = fopen("record.txt", "w+")) == NULL) {
				printf("�ļ���ʧ��\n");
				exit(0);
			}
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2)
				for (patient_p = room_p->next1; patient_p != NULL; patient_p = patient_p->next1)
					for (record_p = patient_p->next2; record_p != NULL; record_p = record_p->next)
						fprintf(fp, "%s %s %d ����%s %s\n", record_p->id, record_p->name, record_p->date, record_p->proom, record_p->symptom);
			if (fclose(fp)) {
				printf("�ļ��޷��ر�\n");
				exit(0);
			}
			printf("ɾ���ɹ���\n");
			break;
		case 0:return;
		default:printf("��������ȷ�ı��\n"); break;
		}
	}
}
void search() {  // ��ѯ��Ϣ����
	char arr[20];
	int flag = 1, flag1 = 0;
	char idnum[20];
	char proom[20];
	int date;
	while (1) {
		int order;
		printf("-----------------------\n");
		printf("||��ѡ��            ||\n");
		printf("||1.��ѯ������Ϣ      ||\n");
		printf("||2.��ѯ���˾����¼  ||\n");
		printf("||3.��ȷ��ѯ�����¼  ||\n");
		printf("||0.����              ||\n");
		printf("-----------------------\n");
		scanf("%d", &order);
		switch (order) {
		case 1:
			flag = 1;
			flag1 = 0;
			printf("��������Ҫ��ѯ�Ŀ��ұ�ţ�\n");
			scanf("%s", arr);
			room_p = (room*)malloc(sizeof(room));
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
				if (strcmp(room_p->id, arr) == 0) {
					printf("����% s % s % s % s\n", room_p->id, room_p->name, room_p->address, room_p->tel);
					flag = 0;
					break;
				}
			}
			if (flag) {
				printf("δ�ҵ��ÿ��ұ��\n");
				break;
			}
			break;
		case 2:
			flag = 1;
			printf("��������Ҫ��ѯ�����¼�Ĳ��˱�ţ�\n");
			scanf("%s", arr);
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
				for (patient_p = room_p->next1; patient_p != NULL; patient_p = patient_p->next1) {
					if (strcmp(patient_p->id, arr) == 0) {
						for (record_p = patient_p->next2; record_p != NULL; record_p = record_p->next) 
							printf("%s %s %d ����%s %s\n", record_p->id, record_p->name, record_p->date, record_p->proom, record_p->symptom);
							flag=0;
					}
				}
			}
			if (flag) {
				printf("δ�ҵ��ò���\n");
				break;
			}
			break;
		case 3:
			flag = 1;
			flag1 = 0;
			printf("��������Ҫ��ѯ�����¼�Ĳ������֤�š����ұ�ţ��������ڣ������λ���֣�����20191230����\n");
			scanf("%s %s %d", idnum, proom, &date);
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
				for (patient_p = room_p->next1; patient_p != NULL; patient_p = patient_p->next1) {
					if (strcmp(patient_p->idnum, idnum) == 0 && strcmp(patient_p->proom, proom) == 0) {
						for (record_p = patient_p->next2; record_p != NULL; record_p = record_p->next) {
							if (record_p->date == date) {
								printf("%s %s %d ����%s %s\n", record_p->id, record_p->name, record_p->date, record_p->proom, record_p->symptom);
								flag = 0;
							}

						}
					}
					if (flag1) break;
				}
			}
			if (flag) {
				printf("δ�ҵ��ü�¼\n");
				break;
			}
			break;
		case 0:return;
		default:printf("��������ȷ�ı��\n"); break;
		}
	}
}
void statistics() { // ����ͳ�ƺ���
	int  order;
	char arr[20];
	int flag = 1, flag1 = 0;
	int count = 0;
	int date;
	int count1 = 0, count2 = 0, count3 = 0, count4 = 0;
	int birthday = 0, i;
	while (1) {
		printf("------------------------------\n");
		printf("||��ѡ��                   ||\n");
		printf("||1.�鿴�վ�������           ||\n");
		printf("||2.�鿴�������վ�������     ||\n");
		printf("||3.�鿴������ξ����������� ||\n");
		printf("||4.�鿴���˾�����ʷ         ||\n");
		printf("||0.����                     ||\n");
		printf("------------------------------\n");
		scanf("%d", &order);
		switch (order) {
		case 1:
			count = 0;
			printf("��������Ҫ��ѯ�����ڣ������λ���֣�����20191230����\n");
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
				printf("����û�м�¼\n");
				break;
			}
			else printf("���վ�������Ϊ��%d\n", count);
			break;
		case 2:
			count = 0;
			printf("��������Ҫ��ѯ�����ڣ������λ���֣�����20191230����\n");
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
				printf("����%s��%d  ", room_p->id, count);
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
					for (i = 6; i <= 13; i++) birthday = birthday * 10 + patient_p->idnum[i] - '0'; //��ȡ���֤���е����ղ�ת��Ϊint������
					if (birthday >= 19900000) count1++;
					else if (birthday >= 19700000) count2++;
					else if (birthday >= 19500000) count3++;
					else count4++;
				}
			}
			printf("30�����£�%d��  30-50�꣺%d��  50-70�꣺%d��  70�����ϣ�%d��\n", count1, count2, count3, count4);
			break;
		case 4:
			flag = 1;
			flag1 = 0;
			printf("��������Ҫ��ѯ�Ĳ��˱�ţ�\n");
			scanf("%s", arr);
			for (room_p = room_head; room_p != NULL; room_p = room_p->next2) {
				for (patient_p = room_p->next1; patient_p != NULL; patient_p = patient_p->next1) {
					if (strcmp(patient_p->id, arr) == 0) {
						for (record_p = patient_p->next2; record_p != NULL; record_p = record_p->next)
							printf("%s %s %d ����%s %s\n", record_p->id, record_p->name, record_p->date, record_p->proom, record_p->symptom);
					}
				}
				if (flag1) break;
			}
			if (flag) {
				printf("δ�ҵ��ò���\n");
				break;
			}
			break;
		case 0:return;
		default:printf("��������ȷ�ı��\n"); break;
		}
	}
}
void openfile() {  //���ѱ�����ļ��򿪵ĺ���
	char id[20];
	char proom[20];
	char name[20];
	char idnum[20];
	char address[20];
	char tel[20];
	char symptom[20];
	int date;
	if ((fp = fopen("room.txt", "a+")) == NULL) { //��room.txt
		printf("�ļ���ʧ��\n");
		exit(0);
	}
	while(!feof(fp)){
		fscanf(fp, "����%s %s %s %s\n", id, name, address, tel);
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
		printf("�ļ��޷��ر�\n");
		exit(0);
	}
	if ((fp = fopen("patient.txt", "a+")) == NULL) {  //��patient.txt
		printf("�ļ���ʧ��\n");
		exit(0);
	}
	while(!feof(fp)) {
	    fscanf(fp,"%s ����%s %s %s %s %s\n", id, proom, name, idnum, address, tel);
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
		printf("�ļ��޷��ر�\n");
		exit(0);
	}
	if ((fp = fopen("record.txt", "a+")) == NULL) {//��record.txt
		printf("�ļ���ʧ��\n");
		exit(0);
	}
	while(!feof(fp)){
	    fscanf(fp,"%s %s %d ����%s %s\n", id, name, &date, proom, symptom);
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
		printf("�ļ��޷��ر�\n");
		exit(0);
	}
}
