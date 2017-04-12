#include <iostream>

using namespace std;

struct Date {
	int ngay;
	int thang;
	int nam;
};

struct Time {
	int gio;
	int phut;
};

struct Employee {
	char 	manv[4];		// ma nhan vien
	char 	ho[30];
	char 	ten[10];
	char	congty[30];
	char	chucvu[30];
	Date	sinhnhat;
	char 	que[20];		// que quan
	char	diachi[50];
	char	email[50];
	int 	sdt;		// so dien thoai
	Date	ngaybd;		// ngay bat dau
	Date*   ngaylv;		// ngay lam viec
	Time*	gioden;		// gio den^'
	Time* 	giove;		// gio ve^`
};

Employee* createEmployee() {
	Employee* emp = new Employee;
	emp->ngaylv = new Date[7];
	emp->gioden = new Time[7];
	emp->giove = new Time[7];
	return emp;
}

void read(FILE* file) {
	Employee* emp = createEmployee();
	char* line = new char[100];
	fgets(emp->manv, 100, file);
	fgets(emp->ho, 100, file);
	fgets(emp->ten, 100, file);
	fgets(emp->congty, 100, file);
	fgets(emp->chucvu, 100, file);
	fgets(line, 100, file);
	sscanf(
		line, 
		"%d/%d/%d", 
		&emp->sinhnhat.ngay, &emp->sinhnhat.thang, &emp->sinhnhat.nam
	);
	fgets(emp->que, 100, file);
	fgets(emp->diachi, 100, file);
	fgets(emp->email, 100, file);
	//fgets(emp->sdt, 100, file);
	//sscanf(line, "%d/%d,%d/%d/%d,%d/%d", emp->);
	cout 	<< emp->sinhnhat.ngay 
			<< emp->sinhnhat.thang 
			<< emp->sinhnhat.nam;
}

int main() {
	const char *filePath = "E:/workspace/Cxxxxx/test-input/input.txt";
	FILE *file;

	file = fopen(filePath, "r");
	read(file);
	return 0;
}
