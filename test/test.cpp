#include <iostream>
#include <stack>

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
	char 	manv[4];	    // ma nhan vien
	char 	ho[30];
	char 	ten[10];
	char	congty[30];
	char	chucvu[30];
	Date	sinhnhat;
	char 	que[20];	    // que quan
	char	diachi[50];
	char	email[50];
	char 	sdt[50];	    // so dien thoai
	Date	ngaybd;		    // ngay bat dau
	Date    ngaylv[7];		// ngay lam viec
	Time	gioden[7];		// gio den^'
	Time 	giove[7];		// gio ve^`
};


stack<Employee*> read(FILE* file) {
	stack<Employee*> stack;
	Employee* emp = new Employee;
	char line[100];
	int i;
	fgets(emp->manv, 100, file);
	fgets(emp->ho, 100, file);
	fgets(emp->ten, 100, file);
	fgets(emp->congty, 100, file);
	fgets(emp->chucvu, 100, file);
	fgets(line, 100, file);
	sscanf(
		line, "%d/%d/%d", 
		&emp->sinhnhat.ngay, &emp->sinhnhat.thang, &emp->sinhnhat.nam
	);
	fgets(emp->que, 100, file);
	fgets(emp->diachi, 100, file);
	fgets(emp->email, 100, file);
	fgets(emp->sdt, 100, file);
	fgets(line, 100, file);
	sscanf(
		line, "%d/%d/%d", 
		&emp->ngaybd.ngay, &emp->ngaybd.thang, &emp->ngaybd.nam
	);
	for (i = 0; i < 7; i += 1) {
	    fgets(line, 100, file);
	    sscanf(
		    line, "%d/%d/%d,%d:%d,%d:%d", 
		    &emp->ngaylv[i].ngay, &emp->ngaylv[i].thang, &emp->ngaylv[i].nam,
		    &emp->gioden[i].gio, &emp->gioden[i].phut,
		    &emp->giove[i].gio, &emp->giove[i].phut
        );
    }
	/*cout 	<< emp->ngaylv[0].ngay   << "/"
			<< emp->ngaylv[0].thang  << "/"
			<< emp->ngaylv[0].nam    << " "
			<< emp->gioden[0].gio    << ":"
			<< emp->gioden[0].phut   << " "
			<< emp->giove[0].gio     << ":"
			<< emp->giove[0].phut    << " "
			<< emp->sdt;*/
	stack.push(emp);
	return stack;
}

int main() {
	const char *filePath = "E:/Bach/workspace/GitHub/project-ktlt-20162/test/input.txt";
	FILE *file;
    file = fopen(filePath, "r");
    stack<Employee*> stack;
    
	stack = read(file);
	cout << stack.top()->ten;
	
	return 0;
}
