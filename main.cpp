#include <iostream>
#include <vector>
#include <string.h>

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
    char manv[4];	    //  ma nhan vien
    char ho[30];
    char ten[10];
    char congty[30];
    char chucvu[30];
    Date sinhnhat;
    char que[20];	    //  que quan
    char diachi[50];
    char email[50];
    char sdt[50];	    //  so dien thoai
    Date ngaybd;		    //  ngay bat dau
    Date ngaylv[7];		//  ngay lam viec
    Time gioden[7];		//  gio den^'
    Time giove[7];		//  gio ve^`
};

struct Company {
    char            label[30];  //  ten cong ty
    vector<Employee*>	dsnv;       //  danh sach nhan vien
};

    //  push 1 nhan vien vao cong ty
void pushEmployee(vector<Company*> &dsct, Employee* emp) {	//  dsct: danh sach cong ty
	if (dsct.empty()) {
		Company* co = new Company;
		strcpy(co->label, emp->congty);
		co->dsnv.push_back(emp);
		dsct.push_back(co);
		return;
	}
    vector<Company*>::iterator co = dsct.begin();
    bool found = false;
    for (
        vector<Company*>::iterator co = dsct.begin();
        co != dsct.end();
        co ++ 
    ) {
        if(strcmp((*co)->label, emp->congty) == 0) {
            found = true;
            (*co)->dsnv.push_back(emp);
            break;
            return;
        }
    }
    if (!found) {
        Company* co = new Company;
		strcpy(co->label, emp->congty);
		co->dsnv.push_back(emp);
		dsct.push_back(co);
    }
}

    // Fix loi fgets chua \n
void fixNewLine(Employee* emp) {
	int size_ten  = strlen(emp->ten) - 1;
	if (*emp->ten && emp->ten[size_ten] == '\n') 
    	emp->ten[size_ten] = '\0';
    int size_ho  = strlen(emp->ho) - 1;
	if (*emp->ho && emp->ho[size_ho] == '\n') 
    	emp->ho[size_ho] = '\0';
    int size_manv  = strlen(emp->manv) - 1;
	if (*emp->manv && emp->manv[size_manv] == '\n') 
    	emp->manv[size_manv] = '\0';
    int size_congty  = strlen(emp->congty) - 1;
	if (*emp->congty && emp->congty[size_congty] == '\n') 
    	emp->congty[size_congty] = '\0';
    int size_chucvu  = strlen(emp->chucvu) - 1;
	if (*emp->chucvu && emp->chucvu[size_chucvu] == '\n') 
    	emp->chucvu[size_chucvu] = '\0';
    int size_que  = strlen(emp->que) - 1;
	if (*emp->que && emp->que[size_que] == '\n') 
    	emp->que[size_que] = '\0';
    int size_diachi  = strlen(emp->diachi) - 1;
	if (*emp->diachi && emp->diachi[size_diachi] == '\n') 
    	emp->diachi[size_diachi] = '\0';
    int size_email  = strlen(emp->email) - 1;
	if (*emp->email && emp->email[size_email] == '\n') 
    	emp->email[size_email] = '\0';
    int size_sdt  = strlen(emp->sdt) - 1;
	if (*emp->sdt && emp->sdt[size_sdt] == '\n') 
    	emp->sdt[size_sdt] = '\0';
}

    /*  Doc file
        Luu thong tin nhan vien vao struct Employee
        Push vao cong ty */
void read(FILE* file, vector<Company*> &dsct) {
    while (!feof(file)) {
        Employee* emp = new Employee;
        char line[100];   //  luu ket qua fgets
        int i;
        //  tien hanh doc 1 nhan vien
        fgets(emp->manv, 100, file);
        fgets(emp->ho, 100, file);
        fgets(emp->ten, 100, file);
        fgets(emp->congty, 100, file);
        fgets(emp->chucvu, 100, file);
        fgets(line, 100, file);
        sscanf(
            line, "%d/%d/%d\n", 
            &emp->sinhnhat.ngay, &emp->sinhnhat.thang, &emp->sinhnhat.nam
        );
        fgets(emp->que, 100, file);
        fgets(emp->diachi, 100, file);
        fgets(emp->email, 100, file);
        fgets(emp->sdt, 100, file);
        fgets(line, 100, file);
        sscanf(
            line, "%d/%d/%d\n", 
            &emp->ngaybd.ngay, &emp->ngaybd.thang, &emp->ngaybd.nam
        );
        for (i = 0; i < 7; i += 1) {
            fgets(line, 100, file);
            sscanf(
                line, "%d/%d/%d,%d:%d,%d:%d\n", 
                &emp->ngaylv[i].ngay, &emp->ngaylv[i].thang, &emp->ngaylv[i].nam,
                &emp->gioden[i].gio, &emp->gioden[i].phut,
                &emp->giove[i].gio, &emp->giove[i].phut
            );
        }
        fixNewLine(emp);
        if (strcmp(emp->ten, "Sau") == 0)
            cout << emp->ho << " " << emp->ten << endl; // in Ly Mac Sau
            /*  doc xong 1 nhan vien
                push vao cong ty */
        pushEmployee(dsct, emp);
    }
}

int main() {
    const char *filePath = "E:/workspace/GitHub/project-ktlt-20162/input.txt";
    FILE *file;
    file = fopen(filePath, "r");
    vector<Company*> dsct;

    read(file, dsct);

    cout << dsct.size() << endl; // 3 cong ty
    cout << dsct[0]->label << ": " << dsct[0]->dsnv.size() << " nhan vien" << endl; // 2 nhan vien
    cout << dsct[1]->label << ": " << dsct[1]->dsnv.size() << " nhan vien" << endl; // 8 nhan vien
    cout << dsct[2]->label << ": " << dsct[2]->dsnv.size() << " nhan vien" << endl; // 3 nhan vien

    return 0;
}
