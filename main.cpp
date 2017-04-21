#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <istream>
#include <stdint.h>
#include <stdlib.h>

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
    char manv[10];	    //  ma nhan vien
    char ho[30];
    char ten[10];
    char congty[30];
    char chucvu[30];
    Date sinhnhat;
    char que[20];	    // que quan
    char diachi[50];
    char email[50];
    char sdt[50];	    // so dien thoai
    Date ngaybd;		// ngay bat dau
    Date ngaylv[7];		// ngay lam viec
    Time gioden[7];		// gio den^'
    Time giove[7];		// gio ve^`
};

struct Company {
    char                label[30];  // ten cong ty
    vector<Employee*>	dsnv;       // danh sach nhan vien
};

// Ham push 1 nhan vien vao cong ty
void pushEmployee(vector<Company*> &dsct, Employee* emp) {	// dsct: danh sach cong ty
    // dsct rong => tao cong ty, them nhan vien vao
    if (dsct.empty()) {
        Company* co = new Company;
        strcpy(co->label, emp->congty);
        co->dsnv.push_back(emp);
        dsct.push_back(co);
        return;
    }
    // dsct ko rong => duyet cong ty
    int i = 0;
    int nosOfCo = dsct.size();
    bool found = false;
    for (i = 0; i < nosOfCo; i += 1) {
        if(strcmp(dsct[i]->label, emp->congty) == 0) {
            found = true;   // found => them nhan vien
            break;
        }
    }
    if (found) {
        dsct[i]->dsnv.push_back(emp);
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

// Doc file
// Luu thong tin nhan vien vao struct Employee
// Push vao Cong ty
void read(FILE* file, vector<Company*> &dsct) {
    while (!feof(file)) {
        Employee* emp = new Employee;
        char fgetsResult[100];
        int i;
        // Tien hanh doc 1 nhan vien
        fgets(emp->manv, 100, file);
        fgets(emp->ho, 100, file);
        fgets(emp->ten, 100, file);
        fgets(emp->congty, 100, file);
        fgets(emp->chucvu, 100, file);
        fgets(fgetsResult, 100, file);
        sscanf(
            fgetsResult, "%d/%d/%d\n",
            &emp->sinhnhat.ngay, &emp->sinhnhat.thang, &emp->sinhnhat.nam
        );
        fgets(emp->que, 100, file);
        fgets(emp->diachi, 100, file);
        fgets(emp->email, 100, file);
        fgets(emp->sdt, 100, file);
        fgets(fgetsResult, 100, file);
        sscanf(
            fgetsResult, "%d/%d/%d\n",
            &emp->ngaybd.ngay, &emp->ngaybd.thang, &emp->ngaybd.nam
        );
        for (i = 0; i < 7; i += 1) {
            fgets(fgetsResult, 100, file);
            sscanf(
                fgetsResult, "%d/%d/%d,%d:%d,%d:%d\n",
                &emp->ngaylv[i].ngay, &emp->ngaylv[i].thang, &emp->ngaylv[i].nam,
                &emp->gioden[i].gio, &emp->gioden[i].phut,
                &emp->giove[i].gio, &emp->giove[i].phut
            );
        }
        fixNewLine(emp);
        // Doc xong 1 nhan vien => Push
        pushEmployee(dsct, emp);
    }
}

Employee* findEmployee(char *manv, vector<Company*> &dsct){
    int i, j;
    int nosOfCo = dsct.size();
    for(i = 0; i < nosOfCo; i ++){
        vector<Employee*>* dsnv = &dsct[i]->dsnv;
        int nosOfEmp = (*dsnv).size();
        for(j = 0; j < nosOfEmp; j ++){
            if(strcmp((*dsnv)[j]->manv, manv) == 0) {
                return (*dsnv)[j];
            }
        }
    }
    return NULL;
}

// cau 1
void showBKCorp(vector<Company*> &dsct) {
    int i, j;
    int nosOfCo = dsct.size();
    for (i = 0; i < nosOfCo; i += 1) {
        cout
            << "-----**-----"
            << dsct[i]->label
            << "-----**-----" << endl;

        vector<Employee*>* dsnv = &dsct[i]->dsnv;
        int nosOfEmp = (*dsnv).size();
        for (j = 0; j < nosOfEmp; j += 1) {
            bool matchChucVu =
                strcmp((*dsnv)[j]->chucvu, "Truong phong") == 0 ||
                strcmp((*dsnv)[j]->chucvu, "Pho phong")    == 0 ||
                strcmp((*dsnv)[j]->chucvu, "Giam doc")     == 0 ||
                strcmp((*dsnv)[j]->chucvu, "Pho giam doc") == 0 ||
                strcmp((*dsnv)[j]->chucvu, "Pho chu tich") == 0 ||
                strcmp((*dsnv)[j]->chucvu, "Chu tich")     == 0;
            if (matchChucVu)
                cout << (*dsnv)[j]->chucvu << ": "
                     << (*dsnv)[j]->ho << " " << (*dsnv)[j]->ten << endl;
        }
        cout
            << "Tong so nhan vien: " << nosOfEmp
            << endl << endl;
    }
}

// cau2

// Tim kiem theo ten
void search_By_firstName(vector<Company*> &dsct) {
    char firstName[20];
    cout << "Nhap vao ten nhan vien: ";
    fflush(stdin);
    gets(firstName);

    int i, j;
    bool found = false;
    int nosOfCo = dsct.size();
    for (i = 0; i < nosOfCo; i += 1) {
        vector<Employee*>* dsnv = &dsct[i]->dsnv;
        int nosOfEmp = (*dsnv).size();
        for(j = 0; j < nosOfEmp; j ++) {
            if(strcmp((*dsnv)[j]->ten, firstName) == 0) {
                found = true;
                cout
                    << "--KET QUA SAU 1 HOI TIM KIEM:--" << endl
                    << "Ma nhan vien:" << " "
                        << (*dsnv)[j]->manv << endl
                    << "Ho va ten:" << " "
                        << (*dsnv)[j]->ho << " " << (*dsnv)[j]->ten << endl
                    << "Chuc vu:" << " "
                        << (*dsnv)[j]->chucvu<< endl
                    << "Ngay/thang/namsinh:" << " "
                        << (*dsnv)[j]->sinhnhat.ngay << "/"
                        << (*dsnv)[j]->sinhnhat.thang << "/"
                        << (*dsnv)[j]->sinhnhat.nam << endl
                    << "Que quan:"           << " "
                        << (*dsnv)[j]->que << endl
                    << "Dia chi :"           << " "
                        << (*dsnv)[j]->diachi << endl
                    << "Email :"             << " "
                        << (*dsnv)[j]->email << endl
                    << "SDT :"               << " "
                        << (*dsnv)[j]->sdt << endl
                    << "Ngay bat dau lam :"  << " "
                        << (*dsnv)[j]->ngaybd.ngay << "/"
                        << (*dsnv)[j]->ngaybd.thang << "/"
                        << (*dsnv)[j]->ngaybd.nam << endl;
            }
        }
    }
    if (!found)
        cout << "Khong thay ten nhan vien nao co ten la: " << firstName << endl;
}

// Tim kiem theo ho
void search_By_lastName(vector<Company*> &dsct) {
    char lastName[30];
    cout << "Nhap vao ho nhan vien: ";
    fflush(stdin);
    gets(lastName);

    int i, j;
    bool found = false;
    int nosOfCo = dsct.size();
    for (i = 0; i < nosOfCo; i += 1) {
        vector<Employee*>* dsnv = &dsct[i]->dsnv;
        int nosOfEmp = (*dsnv).size();
        for(j = 0; j < nosOfEmp; j ++) {
            if (strcmp((*dsnv)[j]->ho, lastName) == 0) {
                found = true;
                cout
                    << "--KET QUA SAU 1 HOI TIM KIEM:--" << endl
                    << "Ma nhan vien:" << " "
                        << (*dsnv)[j]->manv << endl
                    << "Ho va ten:" << " "
                        << (*dsnv)[j]->ho << " " << (*dsnv)[j]->ten << endl
                    << "Chuc vu:" << " "
                        << (*dsnv)[j]->chucvu<< endl
                    << "Ngay/thang/namsinh:" << " "
                        << (*dsnv)[j]->sinhnhat.ngay << "/"
                        << (*dsnv)[j]->sinhnhat.thang << "/"
                        << (*dsnv)[j]->sinhnhat.nam << endl
                    << "Que quan:"           << " "
                        << (*dsnv)[j]->que << endl
                    << "Dia chi :"           << " "
                        << (*dsnv)[j]->diachi << endl
                    << "Email :"             << " "
                        << (*dsnv)[j]->email << endl
                    << "SDT :"               << " "
                        << (*dsnv)[j]->sdt << endl
                    << "Ngay bat dau lam :"  << " "
                        << (*dsnv)[j]->ngaybd.ngay << "/"
                        << (*dsnv)[j]->ngaybd.thang << "/"
                        << (*dsnv)[j]->ngaybd.nam << endl;
            }
        }
    }
    if (!found)
        cout << "Khong thay ten nhan vien nao co ho la: " << lastName << endl;
}

// Tim kiem theo ho & ten
void  search_By_fullName(vector<Company*> &dsct) {
    cout << ">>>TIM KIEM THEO HO & TEN<<< " << endl << endl;
    char input_fullName[40];

    cout << "Nhap vao ho & ten nhan vien: ";
    fflush(stdin);
    gets(input_fullName);

    int i, j;
    bool found = false;
    int nosOfCo = dsct.size();
    for (i = 0; i < nosOfCo; i += 1) {
        vector<Employee*>* dsnv = &dsct[i]->dsnv;
        int nosOfEmp = (*dsnv).size();
        char* fullName;
        for (j = 0; j < nosOfEmp; j ++) {
            fullName = new char[40];
	        strcpy(fullName, (*dsnv)[j]->ho);
            strcat(fullName, " ");
            strcat(fullName, (*dsnv)[j]->ten);
            if (strcmp(fullName, input_fullName) == 0) {
                found = true;
                cout
                    << "--KET QUA SAU 1 HOI TIM KIEM:--" << endl
                    << "Ma nhan vien:" << " "
                        << (*dsnv)[j]->manv << endl
                    << "Ho va ten:" << " "
                        << (*dsnv)[j]->ho << " " << (*dsnv)[j]->ten << endl
                    << "Chuc vu:" << " "
                        << (*dsnv)[j]->chucvu<< endl
                    << "Ngay/thang/namsinh:" << " "
                        << (*dsnv)[j]->sinhnhat.ngay << "/"
                        << (*dsnv)[j]->sinhnhat.thang << "/"
                        << (*dsnv)[j]->sinhnhat.nam << endl
                    << "Que quan:"           << " "
                        << (*dsnv)[j]->que << endl
                    << "Dia chi :"           << " "
                        << (*dsnv)[j]->diachi << endl
                    << "Email :"             << " "
                        << (*dsnv)[j]->email << endl
                    << "SDT :"               << " "
                        << (*dsnv)[j]->sdt << endl
                    << "Ngay bat dau lam :"  << " "
                        << (*dsnv)[j]->ngaybd.ngay << "/"
                        << (*dsnv)[j]->ngaybd.thang << "/"
                        << (*dsnv)[j]->ngaybd.nam << endl;
            }
        }
    }
    if (!found)
        cout << "Khong thay ten nhan vien nao la:" << input_fullName << endl;
}

void search_stuff(vector<Company*> &dsct) {
    bool running = true;
    int choice;
    while (running) {
        cout <<
        endl << "Cac kieu tim kiem:" <<
        endl << "1. Tim kiem theo ho." <<
        endl << "2. Tim kiem theo ten." <<
        endl << "3. Tim kiem theo ho & ten." <<
        endl << "4: Thoat chuong trinh." << endl <<
        endl << "Nhap thao tac ban muon thuc hien: ";

        cin >> choice;
        cout << endl;

        switch (choice) {
        case 1: {
            search_By_lastName(dsct);
            break;
        }
        case 2: {
            search_By_firstName(dsct);
            break;
        }
        case 3: {
            search_By_fullName(dsct);
            break;
        }
        case 4: {
            running = false;
            cout << "Nhan phim bat ki de ket thuc.";
            break;
        }
        }
    }
}

//  check t7, CN
bool isWeekends(Date date) {
    int thang = date.thang,
        nam = date.nam,
        day;
    if (date.thang < 3) {
        thang = date.thang + 12;
        nam = date.nam - 1;
    }
    day = (date.ngay + 2 * thang + (3 * (thang + 1)) / 5 + nam + (nam / 4)) % 7;
    if (day == 0 || day == 6)
        return true;
    return false;
}

//  check ngay le
bool isHoliday(Date date) {
    switch (date.thang) {
        case 1: {
            if (date.ngay == 1)
                return true;
            return false;
        }
        case 4: {
            if (date.ngay == 30)
                return true;
            return false;
        }
        case 5: {
            if (date.ngay == 1)
                return true;
            return false;
        }
        case 9: {
            if (date.ngay == 2)
                return true;
            return false;
        }
        default: {
            return false;
        }
    }
}


bool dateMatchInput(Date date, int input_month, int input_year) {
    if (date.thang == input_month && date.nam == input_year)
        return true;
    return false;
}

//  cau 3
void showInfoEmp(vector<Company*> &dsct) {
    char* input_manv = new char[10];
    int input_month, input_year;
    int i = 0;

    cout << "Nhap vao ma nhan vien: ";
    cin >> input_manv;
    cout << "Nhap vao thang can kiem tra: ";
    cin >> input_month;
    cout << "Nhap vao nam can kiem tra: ";
    cin >> input_year;

    Employee* emp = findEmployee(input_manv, dsct);
    // khong tim thay => end
    if (emp == NULL) {
        cout << "Khong co nhan vien ma so " << input_manv << endl;
        return;
    }
    // tim thay
    int giohut = 0;
    int phuthut;
    Date* date;
    for (i = 0; i < 7; i += 1) {
        date = &emp->ngaylv[i];
        bool invalid =
            !dateMatchInput(*date, input_month, input_year) ||
            isWeekends(*date) ||
            isHoliday(*date);
        if (invalid)
            continue;

        int gioden = emp->gioden[i].gio,
            phutden = emp->gioden[i].phut,
            giove = emp->giove[i].gio,
            phutve = emp->giove[i].phut;
        if (gioden >= 7) {
            phuthut = phutden - 30;
            giohut += gioden - 7;
            if (phuthut > 0)
                giohut += 1;
        }
        if (giove <= 17) {
            phuthut = 30 - phutve;
            giohut += 17 - giove;
            if (phuthut > 0)
                giohut += 1;
        }
    }

    cout
        << endl
        << ">>>>> Ket qua tra cuu <<<<<"
        << endl;
    printf(
        "Trong thang %d nam %d, %s lam hut: %d gio",
        input_month, input_year, input_manv, giohut
    );
    cout << endl;
}

//  cau 4
void print_donvi(vector<Company*> &dsct)
{
    char donvi[100];
    cout << "nhap ten don vi:" ;
    cin >> donvi;
    int i, j;
    int nosOfCo = dsct.size();
    for (i = 0; i < nosOfCo; i++)
    {
        if(strcmp(donvi, dsct[i]->label) == 0)
        {
            vector<Employee*>* dsnv = &dsct[i]->dsnv;
            int nosOfEmp = (*dsnv).size();
            for(j = 0; j < nosOfEmp; j++)
            {
                cout << (*dsnv)[j]->manv << endl
                     << (*dsnv)[j]->ho << " " <<  (*dsnv)[j]->ten << endl
                     << (*dsnv)[j]->chucvu<< endl
                     << (*dsnv)[j]->sinhnhat.ngay << "/" << (*dsnv)[j]->sinhnhat.thang << "/" << (*dsnv)[j]->sinhnhat.nam << endl
                     << (*dsnv)[j]->que << endl
                     << (*dsnv)[j]->diachi << endl
                     << (*dsnv)[j]->email << endl
                     << (*dsnv)[j]->sdt << endl
                     << (*dsnv)[j]->ngaybd.ngay << "/" << (*dsnv)[j]->ngaybd.thang << "/" << (*dsnv)[j]->ngaybd.nam << endl;
                cout << endl;
            }
        }
    }
}
//cau 5

void addEmp(vector<Company*> &dsct){
	Employee* emp = new Employee;
    cout<< endl<< "*********Them nhan vien moi ahihi !*************" << endl;
    char manv[10];
    cout << "Xin moi nhap thong tin cua nhan vien moi" << endl;
	do{
       cout<< "Xin moi nhap ma nhan vien:";
       cin>>manv;
       if(findEmployee(manv,dsct)!=NULL){
           cout<< "Ma nhan vien nay da TON TAI vui long thu lai" << endl<< endl;
       }
    }while(findEmployee(manv,dsct)!=NULL);
	pushEmployee(dsct,emp);
		cout<< "Ho:";
       fflush(stdin);
	    gets(emp->ho);
		cout<< "Ten:";
		fflush(stdin);
        gets(emp->ten);
		cout<< "Don vi:";
        cin>>emp->congty;
		cout<< "Chuc vu: ";
        cin>>emp->chucvu;
        cout<< "Ngay thang nam sinh:  " << endl;
		cout<< "Ngay:";
        cin>>emp->sinhnhat.ngay;
        cout<< "Thang:";
        cin>>emp->sinhnhat.thang;
        cout<< "Nam:";
        cin>>emp->sinhnhat.nam;
		cout<< "Que Quan: ";
		cin>>emp->que;
		cout<< "Dia chi: ";
        cin>>emp->ten;
		cout<< "Email: ";
        cin>>emp->email;
		cout<< "So dien thoai: ";
        cin>>emp->sdt;
	    cout<< "---------------------------------------------" << endl;
	    cout<< "Nhan vien duoi day da duoc Them vao he thong!!!" << endl;
	    cout<< "Ten: " <<emp->ten<< endl;
	    cout<< "Ho: " <<emp->ho<< endl;
	    cout<< "Cong ty: " <<emp->congty<< endl;
	    cout<< "Chuc vu: " <<emp->chucvu<< endl;
	    cout<< "Ngay sinh:" <<emp->sinhnhat.ngay<< "/" <<emp->sinhnhat.thang<< "/" <<emp->sinhnhat.nam<< endl;
	    cout<< "Que Quan: " <<emp->que<< endl;
	    cout<< "Dia chi: " <<emp->diachi<< endl;
	    cout<< "Email: " <<emp->email<< endl;
	    cout<< "So dt: " <<emp->sdt<< endl;
	}

//cau 6
void updateEmp(vector<Company*> &dsct){
    cout<< endl<< "*********UPDATE*************" << endl;
    char manv[4];
    do{
       cout<< "Xin moi nhap ma nhan vien:" << endl;
       cin>>manv;
       if(findEmployee(manv,dsct)==NULL){
           cout<< "Sorry!!! Nhan vien nay khong ton tai. Vui long thu lai" << endl<< endl;
       }
    }while(findEmployee(manv,dsct)==NULL);

    Employee *emp=findEmployee(manv,dsct);
    int choice;
    char redo;//co hieu
    do{
        cout << endl << endl;
        cout<<
        endl << "Xin moi nhap 1 so ung voi du lieu can update:" <<
        endl << "1. Ho." <<
        endl << "2. Ten." <<
        endl << "3. Don vi." <<
        endl << "4. Chuc vu." <<
        endl << "5. Ngay sinh." <<
        endl << "6. Que quan." <<
        endl << "7. Dia chi." <<
        endl << "8. Email." <<
        endl << "9. So dien thoai." <<
        endl << "10.Thoat. " <<
        endl << "Nhap thao tac ban muon thuc hien: ";
        cin>>choice;
        if(choice==1){
           cout<< "Ho: ";
           cin>>emp->ho;
        }
        else if(choice==2){
           cout<< "Ten: ";
           cin>>emp->ten;
        }
        else if(choice==3){
           cout<< "Don vi: ";
           cin>>emp->congty;
        }
        else if(choice==4){
           cout<< "Ten: ";
           cin>>emp->chucvu;
        }
        else if(choice==5){
           cout<< "Ngay:" << "  ";
           cin>>emp->sinhnhat.ngay;
           cout<< "Thang:" << "  ";
           cin>>emp->sinhnhat.thang;
           cout<< "Nam:" << "  ";
           cin>>emp->sinhnhat.nam;
        }
        else if(choice==6){
           cout<< "Que Quan: ";
           cin>>emp->que;
        }
        else if(choice==7){
           cout<< "Dia chi: ";
           cin>>emp->ten;
        }
        else if(choice==8){
           cout<< "Email: ";
           cin>>emp->email;
        }
        else if(choice==9){
           cout<< "So dien thoai: ";
           cin>>emp->sdt;
        }
        else if(choice==10){
           break;
        }
        cout<< "Ban co muon update them khong?(Y/N)=";
        cin>>redo;
    }while (redo=='y'||redo=='Y');
    cout<< "---------------------------------------------" << endl;
    cout<< "Nhan vien duoi day da duoc update vao he thong!!!" << endl;
    cout<< "Ten: " <<emp->ten<< endl;
    cout<< "Ho: " <<emp->ho<< endl;
    cout<< "Cong ty: " <<emp->congty<< endl;
    cout<< "Chuc vu: " <<emp->chucvu<< endl;
    cout<< "Ngay sinh:" <<emp->sinhnhat.ngay<< "/" <<emp->sinhnhat.thang<< "/" <<emp->sinhnhat.nam<< endl;
    cout<< "Que Quan: " <<emp->que<< endl;
    cout<< "Dia chi: " <<emp->diachi<< endl;
    cout<< "Email: " <<emp->email<< endl;
    cout<< "So dt: " <<emp->sdt<< endl;
}
int main() {
    cout << "Chuong trinh quan li nhan vien:" << endl;
    cout << "Dang doc file input.txt... ";
    const char *filePath = "input.txt";
    FILE *file;
    file = fopen(filePath, "r");
    bool running=true;
    vector<Company*> dsct;
    int choice;
    read(file, dsct);
    cout << "Done." << endl;

    cout << dsct.size() << endl;

    while(running) {
        cout <<
        endl << "Hay lua chon cac thao tac:" <<
        endl << "1. Hien thi cac thong tin co ban ve BKCorporation." <<
        endl << "2. Tim kiem nhan vien bang ho ten." <<
        endl << "3. Hien thi tinh trang lam viec cua nhan vien." <<
        endl << "4. Hien thi thong tin cua mot don vi." <<
        endl << "5. Them nhan vien moi." <<
        endl << "6. Cap nhat thong tin nhan vien." <<
        endl << "7: Thoat chuong trinh " << endl<<
        endl << "Nhap thao tac ban muon thuc hien: ";

        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1: {
                showBKCorp(dsct);
                break;
            }
            case 2: {
                search_stuff(dsct);
                break;
            }
            case 3: {
                showInfoEmp(dsct);
                break;
            }
            case 4: {
                print_donvi(dsct);
                break;
            }
            case 5: {
                addEmp(dsct);
			    break;
            }
            case 6: {
                updateEmp(dsct);
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
