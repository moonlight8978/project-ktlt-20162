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
    char                label[30];  //  ten cong ty
    vector<Employee*>	dsnv;       //  danh sach nhan vien
};

    //  Ham push 1 nhan vien vao cong ty
    /*  kiem tra dsct rong
        neu rong => tao cong ty, them nhan vien vao
        ko rong => duyet cong ty 
        => found => them nhan vien
        => not found => tao cong ty, them nhan vien */
void pushEmployee(vector<Company*> &dsct, Employee* emp) {	//  dsct: danh sach cong ty
    if (dsct.empty()) {
        Company* co = new Company;
        strcpy(co->label, emp->congty);
        co->dsnv.push_back(emp);
        dsct.push_back(co);
        return;
    }
    int i = 0;
    int nosOfCo = dsct.size();
    bool found = false;
    for (i = 0; i < nosOfCo; i += 1) {
        if(strcmp(dsct[i]->label, emp->congty) == 0) {
            found = true;
            dsct[i]->dsnv.push_back(emp);
            break;
        }
    }
    if (found) {
        return;
    } else {
        Company* co = new Company;
        strcpy(co->label, emp->congty);
        co->dsnv.push_back(emp);
        dsct.push_back(co);
    }
}

    // Fix loi fgets chua' \n
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
            /*  doc xong 1 nhan vien
                push vao cong ty */
        pushEmployee(dsct, emp);
    }
}

    // cau 1
void showBKCorp(vector<Company*> &dsct) {
    int i, j;   //  counting variables
    int nosOfCo = dsct.size();
    for (i = 0; i < nosOfCo; i += 1) {
        cout << "-----"
             << dsct[i]->label 
             << "-----" << endl;
        vector<Employee*>* dsnv = &dsct[i]->dsnv;
        int nosOfEmp = (*dsnv).size();
        for (j = 0; j < nosOfEmp; j += 1) {
            if ((strcmp((*dsnv)[j]->chucvu, "Chu tich") == 0) ||
                (strcmp((*dsnv)[j]->chucvu, "Pho chu tich") == 0) ||
                (strcmp((*dsnv)[j]->chucvu, "Giam doc") == 0) ||
                (strcmp((*dsnv)[j]->chucvu, "Pho giam doc") == 0) ||
                (strcmp((*dsnv)[j]->chucvu, "Truong phong") == 0) ||
                (strcmp((*dsnv)[j]->chucvu, "Pho phong") == 0)) {
                cout << (*dsnv)[j]->chucvu << ": " 
                     << (*dsnv)[j]->ho << " " << (*dsnv)[j]->ten << endl;
            }
        }
        cout << "Tong so nhan vien: "
             << nosOfEmp << endl;
    }
}

int main() {
    cout << "Chuong trinh quan li nhan vien:" << endl;
    cout << "Dang doc file input.txt... ";
    const char *filePath = "E:/workspace/GitHub/project-ktlt-20162/input.txt";
    FILE *file;
    file = fopen(filePath, "r");
    vector<Company*> dsct;
    bool running = true;
    int choice;
    read(file, dsct);
    cout << "Done." << endl;

    while (running) {
        cout << 
        endl << "Hay lua chon cac thao tac:" <<
        endl << "1. Hien thi cac thong tin co ban ve BKCorporation." <<
        endl << "2. Tim kiem nhan vien bang ho ten." <<
        endl << "3. Hien thi tinh trang lam viec cua nhan vien." <<
        endl << "4. Hien thi thong tin cua mot don vi." <<
        endl << "5. Them nhan vien moi." <<
        endl << "6. Cap nhat thong tin nhan vien." <<
        endl << "7. Thoat chuong trinh." << endl <<
        endl << "Nhap thao tac ban muon thuc hien: ";
        
        cin >> choice;
        cout << endl;
        
        switch (choice) {
            case 1: {
                showBKCorp(dsct);
                break;
            }
            case 2: {
                break;
            }
            case 3: {
                break;
            }
            case 4: {
                break;
            }
            case 5: {
                break;
            }
            case 6: {
                break;
            }
            case 7: {
                running = false;
                cout << "Nhan phim bat ki de ket thuc.";
                break;
            }
        }
    }

    return 0;
}
