// ��� ����
#include <stdio.h>
#include <string.h>

// ��� ����
#define MAX_STRING 32
#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

EXEC SQL INCLUDE SQLCA.H;

EXEC SQL BEGIN DECLARE SECTION;

	char username[20];
	char password[20];

	//host variable
	char CID[15];
	char CNAME[15];
	char CADDR[30];
	char CNUM[30];

	char LID[15];
	char LNAME[30];
	char LADDR[30];
	char LNUM[30];

	char BID[15];
	char BNAME[30];
	char AUTHOR[30];
	char TYPE[30];
	int YEAR;
	int PAGE;

	char PID[15];
	char PNAME[30];
	char PADDR[30];
	char PNUM[30];

	char ANUM[15];

    char result_id[15];

	int cnt;

EXEC SQL END DECLARE SECTION;

// �Լ� ����
void join();
void doTask();

// ���� ����
FILE* in_fp, *out_fp;
int i=1;

int main()
{
	// ���� ������� ���� �ʱ�ȭ
	in_fp = fopen(INPUT_FILE_NAME, "r+");
	out_fp = fopen(OUTPUT_FILE_NAME, "w+");

	strcpy(username, "dbteam");
	strcpy(password, "abcd");
	EXEC SQL CONNECT :username
	IDENTIFIED BY :password;

	EXEC SQL CREATE TABLE customer
	(
		cid varchar2(15) primary key,
		cname varchar2(15) not null,
		caddr varchar2(30),
		cnum varchar2(30)
	);

	EXEC SQL CREATE TABLE library
	(
		lid varchar2(15) primary key,
		lname varchar2(30) not null,
		laddr varchar2(30),
		lnum varchar2(30)
	);

	EXEC SQL CREATE TABLE books
	(
		bid varchar2(15) primary key,
		bname varchar2(30) not  null,
		author varchar2(30),
		type varchar2(30),
		year number(4),
		page number(4),
		lid varchar2(15),
		FOREIGN KEY (lid) REFERENCES  library
	);

	EXEC SQL CREATE TABLE librarian
	(
		pid varchar2(15) primary key,
		pname varchar2(30) not null,
		paddr varchar2(30),
		pnum varchar2(30),
		lid varchar2(15),
		FOREIGN KEY (lid) REFERENCES library
	);

	EXEC SQL CREATE TABLE appointment
	(
		cid varchar2(15),
		bid varchar2(15),
		lid varchar2(15),
		anum varchar2(15),
		FOREIGN KEY (cid) REFERENCES customer,
		FOREIGN KEY (bid) REFERENCES books,
		FOREIGN KEY (lid)	REFERENCES library
	);

	printf("==================================\n");			//fprintf�� �� �ʿ�� ����?
	printf("1.1. ȸ������\n 1.2. �α���\n 1.3. ����\n");
	doTask();

	EXEC SQL DROP TABLE appointment;
	EXEC SQL DROP TABLE librarian;
	EXEC SQL DROP TABLE books;
	EXEC SQL DROP TABLE library;
	EXEC SQL DROP TABLE customer;

	EXEC SQL COMMIT WORK RELEASE;
	return 0;
}

void doTask()
{
	// �޴� �Ľ��� ���� level ������ ���� ����
	int menu_level_1 = 0, menu_level_2 = 0;

	char t_anum[15];
    char input_id[15];


	// ���� �޴�(1.3)�� �ԷµǱ� ������ �ݺ���
	while(menu_level_1 != 1 || menu_level_2 != 3)
	{
		// �Է����Ͽ��� �޴� ���� 2���� �б�
		fscanf(in_fp, "%d %d ", &menu_level_1, &menu_level_2);

		// �޴� ���� �� �ش� ���� ����
		switch(menu_level_1)
		{
		case 1:
			{
				switch(menu_level_2)
				{
				case 1:   // "1.1. ȸ�����ԡ� �޴� �κ�
					{
						// join() �Լ����� �ش� ��� ����
						join();
						break;
					}
				 case 2:	//1.2 �α��� �޴� �κ�
					{
						fscanf(in_fp, "%s", input_id);
						strcpy(CID, input_id);

						EXEC SQL SELECT COUNT(*) AS cnt
						INTO :cnt
				  		FROM customer
				   		WHERE cid = :CID;

			 		/*	EXEC SQL SELECT cid INTO :result_id
						FROM customer
						WHERE cid = :CID; */

						if(strcmp(input_id, "admin") == 0 && cnt == 1){
							fprintf(out_fp, "1.2. �α���\n");
							fprintf(out_fp, "> %s\n", result_id);
							printf("==================================\n");
							printf("3.1. ������ ���� ���\n3.2. ������ ���� ����\n3.3. ���� ���� ���\n3.4. ���� ���� ����\n3.5. �缭 ���� ���\n3.6. �缭 ���� ����\n3.7. ������ ���� ��ü ��ȸ\n3.8. ������ ���� �̸� ��ȸ\n3.9. �缭 ���� ��ü ��ȸ\n3.10. ���� ���� ��ü ��ȸ\n3.11. ���� ���� �����̸� ��ȸ\n3.12. ���� ���� ���̸� ��ȸ\n3.13. �α׾ƿ�\n");
						}
						
						else if(cnt == 1){
							fprintf(out_fp, "1.2. �α���\n");
							fprintf(out_fp, "> %s\n", result_id);
							printf("==================================\n");
							printf("2.1. ȸ�� ���� ��ȸ\n2.2. ���� ����\n2.3. ���� ���� ��ȸ\n2.4. ���� ���� ����\n2.5. ȸ��Ż��\n2.6. �α׾ƿ�\n");
							}
						else{
		
							fprintf(out_fp, "��ġ�ϴ� id�� �����ϴ�.\n");
							printf("==================================\n");
							printf("1.1. ȸ������\n 1.2. �α���\n 1.3. ����\n");
						}
                        break;
                    }
				case 3:
					{
						fprintf(out_fp, "1.3. ����\n");
						return 0;
					}
				}
				break;
			}
		case 2:
			{
				switch(menu_level_2)
				{
				case 1:   // "2.1 ȸ�� ���� ��ȸ�� �޴� �κ�
					{
						EXEC SQL SELECT cname, caddr, cnum INTO :CNAME, :CADDR, :CNUM
						FROM customer
						WHERE cid = :CID;

						fprintf(out_fp, "2.1. ȸ�� ���� ��ȸ\n");
						fprintf(out_fp, "> %s %s %s %s\n", CID, CNAME, CADDR, CNUM);

						break;
					}
				case 2:	//2.2 ���� ���� �޴� �κ�
					{
						fscanf(in_fp, "%s", BNAME);

						sprintf(t_anum, "R%03d", i);
						strcpy(ANUM, t_anum);

						EXEC SQL SELECT bid, bname, author, type, year, page, lid
						INTO :BID, :BNAME, :AUTHOR, :TYPE, :YEAR, :PAGE, :LID
						FROM books
						WHERE bname = :BNAME;

						EXEC SQL INSERT INTO appointment VALUES
						(:CID, :BID, :LID, :ANUM);
						i++;

						fprintf(out_fp, "2.2. ���� ����\n");
						fprintf(out_fp, "> %s %s %s %s %d %d\n", ANUM, BNAME, AUTHOR, TYPE, YEAR, PAGE);

						break;
					}
				case 3:	// 2.3 ���� ���� ��ȸ �޴� �κ�
					{
						EXEC SQL DECLARE c1 CURSOR FOR
						SELECT a.anum, b.bname, b.author, b.type, b.year, b.page
						FROM books b, appointment a
						WHERE a.cid=:CID and b.bid=a.bid;

						fprintf(out_fp, "2.3. ���� ���� ��ȸ\n");

						EXEC SQL OPEN c1;
						for(;;)
						{
							EXEC SQL FETCH c1 INTO :ANUM, :BNAME, :AUTHOR, :TYPE, :YEAR, :PAGE;
							if(sqlca.sqlcode != 0)
							{
								if(sqlca.sqlcode != 1403)
								{
									printf("Error Occured : %d\n", sqlca.sqlcode);
									EXEC SQL ROLLBACK RELEASE;
									return 0;
								}
								else
								{
									break;
								}
							}
							fprintf(out_fp, "> %s %s %s %s %d %d\n", ANUM, BNAME, AUTHOR, TYPE, YEAR, PAGE);
						}

						EXEC SQL CLOSE c1;

						break;
					}
				case 4:	// 2.4 ���� ���� ���� �޴� �κ�
					{
						fscanf(in_fp, "%s", ANUM);

						EXEC SQL DELETE FROM appointment
						WHERE anum = :ANUM;

						// ��� ����
						fprintf(out_fp, "2.4. ���� ���� ����\n");
						fprintf(out_fp, "> %s\n", ANUM);

						break;
					}
				case 5:	// 2.5 ȸ��Ż�� �޴� �κ�
					{
						// ��� ����
						fprintf(out_fp, "2.5. ȸ��Ż��\n");
						fprintf(out_fp, "> %s\n", CID);

						EXEC SQL DELETE FROM customer
						WHERE cid = :CID;

						break;
					}
				case 6:
					{
						fprintf(out_fp, "2.6. �α׾ƿ�\n");
						printf("==================================\n");
						printf("1.1. ȸ������\n 1.2. �α���\n 1.3. ����\n");
						break;
					}
				}
				break;
			}
		case 3:
			{
				switch (menu_level_2)
				{
				case 1:		 // "3.1 ������ ���� ��ϡ� �޴� �κ�
					{

						fscanf(in_fp, "%s %s %s %s", LID, LNAME, LADDR, LNUM);

						EXEC SQL INSERT INTO library VALUES(:LID, :LNAME, :LADDR, :LNUM);

						// ��� ����
						fprintf(out_fp, "3.1. ������ ���� ���\n");
						fprintf(out_fp, "> %s %s %s %s\n", LID, LNAME, LADDR, LNUM);
						break;
					}
				case 2:		 // "3.2 ������ ���� ������ �޴� �κ�
					{
						fscanf(in_fp, "%s", LID);

						EXEC SQL DELETE FROM library
						WHERE lid = :LID;

						// ��� ����
						fprintf(out_fp, "3.2. ������ ���� ����\n");
						fprintf(out_fp, "> %s\n", LID);
						break;
					}
				case 3:         // "3.3 ���� ����  ���" �޴� �κ�
                    {
                        fscanf(in_fp, "%s %s %s %s %d %d %s", BID, BNAME, AUTHOR, TYPE, YEAR, PAGE, LID);
 
                        EXEC SQL INSERT INTO books VALUES
                        (:BID, :BNAME, :AUTHOR, :TYPE, :YEAR, :PAGE, :LID);
 
                        // ��� ����
                        fprintf(out_fp, "3.3. ���� ���� ���\n");
                        fprintf(out_fp, "> %s %s %s %s %d %d %s\n", BID, BNAME, AUTHOR, TYPE, &YEAR, &PAGE, LID);
                        break;
                    }
				case 4:				// "3.4. ���� ���� ����" �޴� �κ�
					{
						fscanf(in_fp, "%s", BID);

						EXEC SQL DELETE FROM books
						WHERE bid = :BID;

						// ��� ����
						fprintf(out_fp, "3.4. ���� ���� ����\n");
						fprintf(out_fp, "> %s\n", BID);
						break;
					}
				case 5:				// "3.5. �缭 ���� ���" �޴� �κ�
					{
						fscanf(in_fp, "%s %s %s %s %s", PID, PNAME, PADDR, PNUM, LID);

						EXEC SQL INSERT INTO librarian VALUES
						(:PID, :PNAME, :PADDR, :PNUM, :LID);

						// ��� ����
						fprintf(out_fp, "3.5. �缭 ���� ���\n");
						fprintf(out_fp, "> %s %s %s %s %s\n", PID, PNAME, PADDR, PNUM, LID);
						break;
					}
				case 6:				// "3.6. �缭 ���� ����" �޴� �κ�
					{
						fscanf(in_fp, "%s", PID);

						EXEC SQL DELETE FROM librarian
						WHERE pid = :PID;

						// ��� ����
						fprintf(out_fp, "3.6. �缭 ���� ����\n");
						fprintf(out_fp, "> %s\n", PID);
						break;
					}
				case 7:				// "3.7. ������ ���� ��ü ��ȸ" �޴� �κ�
					{
						EXEC SQL DECLARE c2 CURSOR FOR
						SELECT lid, lname, laddr, lnum
						FROM library;

						fprintf(out_fp, "3.7 ������ ���� ��ü ��ȸ\n");

						EXEC SQL OPEN c2;
						for(;;)
						{
							EXEC SQL FETCH c2 INTO :LID, :LNAME, :LADDR, :LNUM;
							if(sqlca.sqlcode != 0)
							{
								if(sqlca.sqlcode != 1403)
								{
									printf("Error Occured : %d\n", sqlca.sqlcode);
									EXEC SQL ROLLBACK RELEASE;
									return 0;
								}
								else
								{
									break;
								}
							}
							fprintf(out_fp, "> %s %s %s %s\n", LID, LNAME, LADDR, LNUM);
						}

						EXEC SQL CLOSE c2;

						break;
					}
				case 8:				// "3.8. ������ ���� �̸� ��ȸ" �޴� �κ�
					{
						fscanf(in_fp, "%s", LNAME);

						EXEC SQL SELECT lid, lname, laddr, lnum
						INTO :LID, :LNAME, :LADDR, :LNUM
						FROM library
						WHERE lname = :LNAME;

						fprintf(out_fp, "3.8. ������ ���� �̸� ��ȸ\n");

						fprintf(out_fp, "> %s %s %s %s\n", LID, LNAME, LADDR, LNUM);

						break;
					}
				case 9:				// "3.9. �缭 ���� ��ü ��ȸ" �޴� �κ�
					{
						EXEC SQL DECLARE c3 CURSOR FOR
						SELECT pid, pname, paddr, pnum, lid
						FROM librarian;

						fprintf(out_fp, "3.9. �缭 ���� ��ü ��ȸ\n");

						EXEC SQL OPEN c3;
						for(;;)
						{
							EXEC SQL FETCH c3 INTO :PID, :PNAME, :PADDR, :PNUM, :LID;
							if(sqlca.sqlcode != 0)
							{
								if(sqlca.sqlcode != 1403)
								{
									printf("Error Occured : %d\n", sqlca.sqlcode);
									EXEC SQL ROLLBACK RELEASE;
									return 0;
								}
								else
								{
									break;
								}
							}
							fprintf(out_fp, "> %s %s %s %s %s\n", PID, PNAME, PADDR, PNUM, LID);
						}

						EXEC SQL CLOSE c3;

						break;
					}
				case 10:			// "3.10. ���� ���� ��ü ��ȸ" �޴� �κ�
					{
						EXEC SQL DECLARE c4 CURSOR FOR
						SELECT a.anum, a.cid, b.bname, b.author
						FROM appointment a, books b
						WHERE a.bid = b.bid;

						fprintf(out_fp, "3.10. ���� ���� ��ü ��ȸ\n");

						EXEC SQL OPEN c4;
						for(;;)
						{
							EXEC SQL FETCH c4 INTO :ANUM, :CID, :BNAME, :AUTHOR;
							if(sqlca.sqlcode != 0)
							{
								if(sqlca.sqlcode != 1403)
								{
									printf("Error Occured : %d\n", sqlca.sqlcode);
									EXEC SQL ROLLBACK RELEASE;
									return 0;
								}
								else
								{
									break;
								}
							}
							fprintf(out_fp, "> %s %s %s %s\n", ANUM, CID, BNAME, AUTHOR);
						}

						EXEC SQL CLOSE c4;

						break;
					}
				case 11:			// "3.11. ���� ���� �����̸� ��ȸ" �޴� �κ�
					{
						fscanf(in_fp, "%s", BNAME);

						EXEC SQL DECLARE c5 CURSOR FOR
						SELECT a.anum, a.cid, b.bname, b.author
						FROM appointment a, books b
						WHERE a.bid = b.bid and b.bname = :BNAME;


						fprintf(out_fp, "3.11. ���� ���� �����̸� ��ȸ\n");

						EXEC SQL OPEN c5;
						for(;;)
						{
							EXEC SQL FETCH c5 INTO :ANUM, :CID, :BNAME, :AUTHOR;
							if(sqlca.sqlcode != 0)
							{
								if(sqlca.sqlcode != 1403)
								{
									printf("Error Occured : %d\n", sqlca.sqlcode);
									EXEC SQL ROLLBACK RELEASE;
									return 0;
								}
								else
								{
									break;
								}
							}
							fprintf(out_fp, "> %s %s %s %s\n", ANUM, CID, BNAME, AUTHOR);
						}

						EXEC SQL CLOSE c5;

						break;
					}
				case 12:			// "3.12. ���� ���� ���̸� ��ȸ" �޴� �κ�
					{
						fscanf(in_fp, "%s", CNAME);

						EXEC SQL DECLARE c6 CURSOR FOR
						SELECT a.anum, a.cid, b.bname, b.author
						FROM appointment a, books b, customer c
						where a.bid = b.bid and a.cid = c.cid and c.cname = :CNAME;

						fprintf(out_fp, "3.12 ���� ���� ���̸� ��ȸ\n");

						EXEC SQL OPEN c6;
						for(;;)
						{
							EXEC SQL FETCH c6 INTO :ANUM, :CID, :BNAME, :AUTHOR;
							if(sqlca.sqlcode != 0)
							{
								if(sqlca.sqlcode != 1403)
								{
									printf("Error Occured : %d\n", sqlca.sqlcode);
									EXEC SQL ROLLBACK RELEASE;
									return 0;
								}
								else
								{
									break;
								}
							}
							fprintf(out_fp, "> %s %s %s %s\n", ANUM, CID, BNAME, AUTHOR);
						}

						EXEC SQL CLOSE c6;

						break;
					}
				case 13:
					{
						fprintf(out_fp, "3.13 �α׾ƿ�\n");
						fprintf(out_fp, "> admin\n");

						printf("==================================\n");
						printf("1.1. ȸ������\n 1.2. �α���\n 1.3. ����\n");
						break;
					}
				}
				break;
			}
		}
	}
}

void join()
{
	char ID[MAX_STRING], name[MAX_STRING], gender[MAX_STRING], phone_num[MAX_STRING], address[MAX_STRING];
	int age;

	// �Է� ���� : �ֹι�ȣ, �̸�, �ּ�, ��ȭ��ȣ�� ���Ϸκ��� ����
	fscanf(in_fp, "%s %s %s %s\n", ID, name, address, phone_num);

	// DB ������ �����Ͽ� �ش� ��� ����
	strcpy(CID, ID);
	strcpy(CNAME, name);
	strcpy(CADDR, address);
	strcpy(CNUM, phone_num);

	EXEC SQL INSERT INTO customer(cid, cname, caddr, cnum) VALUES
	(:CID, :CNAME, :CADDR, :CNUM);

	// ��� ����
	fprintf(out_fp, "1.1. ȸ������\n");
	fprintf(out_fp, "%s %s %s %s\n", ID, name, address, phone_num);

	return 0;
}
