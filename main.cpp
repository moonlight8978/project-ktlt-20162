#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <istream>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>


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

struct NgayLamViec {
    Date ngay;
    Time gioden;
    Time giove;
};

struct Employee {
    char manv[10];  //  ma nhan vien
    char ho[30];
    char ten[10];
    char congty[30];
    char chucvu[30];
    Date sinhnhat;
    char que[20];   // que quan
    char diachi[50];
    char email[50];
    char sdt[50];   // so dien thoai
    Date ngaybd;    // ngay bat dau
    vector<NgayLamViec> ngaylv;   // ngay lam viec
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
    char manvBackup[100];
    fgets(manvBackup, 100, file);
    while (!feof(file)) {
        Employee* emp = new Employee;
        char fgetsResult[100];
        bool toNextEmp = false;
        // Tien hanh doc 1 nhan vien
        strcpy(emp->manv, manvBackup);
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
        while (!toNextEmp) {
            if (feof(file))
                break;
            fgets(fgetsResult, 100, file);
            if (fgetsResult[0] == 'N') {
                strcpy(manvBackup, fgetsResult);
                toNextEmp = true;
            } else {
                NgayLamViec ngaylv;
                sscanf(
                    fgetsResult, "%d/%d/%d,%d:%d,%d:%d\n",
                    &ngaylv.ngay.ngay, &ngaylv.ngay.thang, &ngaylv.ngay.nam,
                    &ngaylv.gioden.gio, &ngaylv.gioden.phut,
                    &ngaylv.giove.gio, &ngaylv.giove.phut
                );
                emp->ngaylv.push_back(ngaylv);
            }
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


double calTime(clock_t start) {
    return (double)(clock() - start) / CLOCKS_PER_SEC;
}

// cac ham kiem tra input

bool isInputEmpty(char* input) {
    if (input[0] == '\0')
        return true;
    return false;
}

bool isNameInvalid(char* input) {
    if ('A' <= input[0] && input[0] <= 'Z' ||
        'a' <= input[0] && input[0] <= 'z')
        return false;
    return true;
}

bool isManvInvalid(char* input) {
    if (input[0] == 'N' && input[1] == 'V' &&
        input[2] >= '1' && input[2] <= '9')
        return false;
    return true;
}

bool isDayInvalid(int input) {
    if (input >= 1 && input <= 31)
        return false;
    return true;
}

bool isMonthInvalid(int input) {
    if (input >= 1 && input <= 12)
        return false;
    return true;
}

bool isYearInvalid(int input) {
    if (input >= 1900 && input <=2017)
        return false;
    return true;
}

bool isCharacter(const char Character)
{
	return ( (Character >= 'a' && Character <= 'z') || 
			 (Character >= 'A' && Character <= 'Z'));
}

bool isValidEmailAddress(const char * email)
{
	if (!email)
		return 0;
	if (!isCharacter(email[0]))
		return 0;
	int AtOffset = -1;
	int DotOffset = -1;
	unsigned int Length = strlen(email);

	for(unsigned int i = 0; i < Length; i++)
	{
		if (email[i] == '@')
			AtOffset = (int)i;
		else if (email[i] == '.')
			DotOffset = (int)i;
	}

	if (AtOffset == -1 || DotOffset == -1)
		return 0;
	if (AtOffset > DotOffset)
		return 0;
	return !(DotOffset >= ((int)Length-1));
}
bool isInputChoose(char* input){
	if(input=="y"||input=="n"||input=="Y"||input=="N")
		return false;
	return true;
}

// cau 1
void showBKCorp(vector<Company*> &dsct) {
    clock_t start = clock();
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
                cout
                    << (*dsnv)[j]->chucvu << ": "
                    << (*dsnv)[j]->ho << " " << (*dsnv)[j]->ten << endl;
        }
        cout
            << "Tong so nhan vien: " << nosOfEmp
            << endl;
    }
    cout
        << endl
        << "Hoan thanh trong " << calTime(start) << " giay" << endl;
}

// cau2

// Tim kiem theo ten
void search_By_firstName(vector<Company*> &dsct) {
    char firstName[20];
    cout << "Nhap vao ten nhan vien: ";
    bool error = true;
    while (error) {
        fflush(stdin);
        gets(firstName);
        error = (!isInputEmpty(firstName) && !isNameInvalid(firstName)) ? false : true;
        if (error)
            cout << "Ten nhap vao khong hop le! Hay nhap lai: ";
    }

    clock_t start = clock();
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
    cout
        << endl
        << "Hoan thanh trong " << calTime(start) << " giay" << endl;
}

// Tim kiem theo ho
void search_By_lastName(vector<Company*> &dsct) {
    char lastName[30];
    cout << "Nhap vao ho nhan vien: ";
    bool error = true;
    while (error) {
        fflush(stdin);
        gets(lastName);
        error = (!isInputEmpty(lastName) && !isNameInvalid(lastName)) ? false : true;
        if (error)
            cout << "Ho nhap vao khong hop le! Hay nhap lai: ";
    }

    clock_t start = clock();
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
    cout
        << endl
        << "Hoan thanh trong " << calTime(start) << " giay" << endl;
}

// Tim kiem theo ho & ten
void  search_By_fullName(vector<Company*> &dsct) {
    cout << ">>>TIM KIEM THEO HO & TEN<<< " << endl << endl;
    char input_fullName[40];
    cout << "Nhap vao ho & ten nhan vien: ";
    bool error = true;
    while (error) {
        fflush(stdin);
        gets(input_fullName);
        error = (!isInputEmpty(input_fullName) && !isNameInvalid(input_fullName)) ? false : true;
        if (error)
            cout << "Ho ten nhap vao khong hop le! Hay nhap lai: ";
    }

    clock_t start = clock();
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
    cout
        << endl
        << "Hoan thanh trong " << calTime(start) << " giay" << endl;
}

void search_stuff(vector<Company*> &dsct) {
    cout << "~~~*** TIM KIEM NHAN VIEN ***~~~";
    bool running = true;
    int choice;
    while (running) {
        cout <<
        endl << "Cac kieu tim kiem:" <<
        endl << "1. Tim kiem theo ho" <<
        endl << "2. Tim kiem theo ten" <<
        endl << "3. Tim kiem theo ho & ten" <<
        endl << "4: Khong tim kiem nua" << endl <<
        endl << "Nhap thao tac ban muon thuc hien: ";

        cin >> choice;
        cout << endl;

        switch (choice) {
        case 1: {
            search_By_lastName(dsct);
            break; }
        case 2: {
            search_By_firstName(dsct);
            break; }
        case 3: {
            search_By_fullName(dsct);
            break; }
        case 4: {
            running = false;
            cout << endl;
            break; }
        default: {
            cout << "Khong co chuc nang nay!" << endl;
            break; }
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
        return false; }
    case 4: {
        if (date.ngay == 30)
            return true;
        return false; }
    case 5: {
        if (date.ngay == 1)
            return true;
        return false; }
    case 9: {
        if (date.ngay == 2)
            return true;
        return false; }
    default: {
        return false; }
    }
}


bool dateMatchInput(Date date, int input_month, int input_year) {
    if (date.thang == input_month && date.nam == input_year)
        return true;
    return false;
}

int calDeficientTime(Time& gioden, Time& giove) {
    int giohut = 0,
        phuthut;
    if (gioden.gio >= 7) {
        phuthut = gioden.phut - 30;
        giohut += gioden.gio - 7;
        if (phuthut > 0)
            giohut += 1;
    }
    if (giove.gio <= 17) {
        phuthut = 30 - giove.phut;
        giohut += 17 - giove.gio;
        if (phuthut > 0)
            giohut += 1;
    }
    return giohut;
}

//  cau 3
void showInfoEmp(vector<Company*>& dsct) {
    cout << "~~~*** KIEM TRA THONG TIN NHAN VIEN ***~~~" << endl;
    bool running = true;
    while (running) {
        char* input_manv = new char[10];
        int input_month, input_year;
        int i = 0;
        bool error;

        cout << "Nhap vao ma nhan vien (MaNV co dang NV*): ";
        error = true;
        while (error) {
            cin >> input_manv;
            error = (!isInputEmpty(input_manv) && !isManvInvalid(input_manv)) ? false : true;
            if (error)
                cout << "Ten nhap vao khong hop le! Hay nhap lai: ";
        }
        cout << "Nhap vao thang can kiem tra: ";
        error = true;
        while (error) {
            cin >> input_month;
            if (!cin) {
                cin.clear();
                cin.ignore();
                cout << "Khong hop le. Nhap lai: ";
            } else
                error = false;
        }
        cout << "Nhap vao nam can kiem tra: ";
        error = true;
        while (error) {
            cin >> input_year;
            if (!cin) {
                cin.clear();
                cin.ignore();
                cout << "Khong hop le. Nhap lai: ";
            } else
                error = false;
        }

        clock_t start = clock();
        Employee* emp = findEmployee(input_manv, dsct);
        // khong tim thay => end
        if (emp == NULL) {
            cout << "Khong co nhan vien ma so " << input_manv << endl;
        } else {
	        int giohut = 0;
	        Date* date;
            int nosOfDay = emp->ngaylv.size();
	        for (i = 0; i < nosOfDay; i += 1) {
	            date = &emp->ngaylv[i].ngay;
	            bool invalid =
	                !dateMatchInput(*date, input_month, input_year) ||
	                isWeekends(*date) ||
	                isHoliday(*date);
	            if (invalid)
	                continue;

	            giohut += calDeficientTime(emp->ngaylv[i].gioden, emp->ngaylv[i].giove);
	        }

	        cout
	            << endl
	            << ">>>>> Ket qua tra cuu <<<<<" << endl;
	        printf(
	            "Trong thang %d nam %d, %s (%s %s) lam hut: %d gio \n",
	            input_month, input_year, input_manv, emp->ho, emp->ten, giohut
	        );
	    }

        cout
            << endl
            << "Hoan thanh trong " << calTime(start) << " giay" << endl << endl

            << "Ban muon kiem tra nhan vien khac khong? (Y/N): ";
        char choice = '\0'; // reset choice
        while (choice != 'Y' && choice != 'y' && choice != 'n' && choice != 'N')
            cin >> choice;
        if (choice == 'n' || choice == 'N')
            running = false;
    }
}

//  cau 4
void print_donvi(vector<Company*> &dsct)
{
	cout << "~~~**** HIEN THI THONG TIN 1 DON VI ****~~~" << endl;
    char donvi[50];
    
    bool running = true;
    while (running) {
    	cout << "Nhap ten don vi: ";
	    bool error = true;
	    while (error) {
	    	fflush(stdin);
	        gets(donvi);
	        error = (!isInputEmpty(donvi) && !isNameInvalid(donvi)) ? false : true;
	        if (error)
	            cout << "Ten don vi nhap vao khong hop le! Hay nhap lai: ";
	    }
	    bool found = false;
	    clock_t start = clock();
	    int i, j;
	    int nosOfCo = dsct.size();
	    for (i = 0; i < nosOfCo; i++)
	    {
	        if(strcmp(donvi, dsct[i]->label) == 0)
	        {	
	        	found = true;
	        	break;
	        }
	    }
	    if (found) {
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
	    } else
	    	cout << "Khong co cong ty nao la: " << donvi << endl;
	    cout << endl
	         << "Hoan thanh trong " << calTime(start) << " giay" << endl << endl;

	    cout << "Ban muon kiem tra nhan vien khac khong? (Y/N): ";
	    char choice = '\0'; // reset choice
        while (choice != 'Y' && choice != 'y' && choice != 'n' && choice != 'N')
            cin >> choice;
        if (choice == 'n' || choice == 'N')
            running = false;
	} 
}
//cau 5

void addEmp(vector<Company*> &dsct){
char flag;
	do{
	Employee* emp = new Employee;
    cout<< endl<< "*********Them nhan vien moi ahihi !*************" << endl;
    char manv[10];
    cout << "Xin moi nhap thong tin cua nhan vien moi" << endl;
    bool error=true;
	do{
       cout<< "Xin moi nhap ma nhan vien  (VD:NV01): ";
       error = true;
       while (error) {
            cin >> manv;
            error = (!isInputEmpty(manv) && !isManvInvalid(manv)) ? false : true;
            if (error)
                cout << "Ma nhan vien khong hop le! nhap lai: ";
       }
       if(findEmployee(manv,dsct)!=NULL){
           cout<< "Ma nhan vien nay da TON TAI vui long thu lai" << endl<< endl;
       																		}
    	}while(findEmployee(manv,dsct)!=NULL);
		
		cout<< "Ho:";fflush(stdin);
		error=true;
       	while (error) {
            gets(emp->ho);
            error = (!isInputEmpty(emp->ho) && !isNameInvalid(emp->ho)) ? false : true;
            if (error)
                cout << "Khong hop le! Moi nhap lai: ";
      	 }
		
		cout<< "Ten:";fflush(stdin);
		error=true;
		while (error) {
            gets(emp->ten);
            error = (!isInputEmpty(emp->ten) && !isNameInvalid(emp->ten)) ? false : true;
            if (error)
                cout << " Khong hop le! Moi nhap lai: ";
   		}
   		
		cout<< "Don vi:";fflush(stdin);
		error=true;
		while (error) {
            gets(emp->congty);
            error = (!isInputEmpty(emp->congty)) ? false : true;
            if (error)
                cout << "Khong hop le! Moi nhap lai: ";
       }
       
        cout<< "Chuc vu: ";fflush(stdin);
        error=true;
		while (error) {
            gets(emp->chucvu);
            error = (!isInputEmpty(emp->chucvu) && !isNameInvalid(emp->chucvu)) ? false : true;
            if (error)
                cout << "Khong hop le! Moi nhap lai: ";
       }
       
        cout<< "Ngay thang nam sinh:  " << endl;
		cout<< "Ngay:";fflush(stdin);
		error=true;
		while (error) {
            cin>>emp->sinhnhat.ngay;
            if (!cin || isDayInvalid(emp->sinhnhat.ngay)) {
                cin.clear();
                cin.ignore();
                cout << "Khong hop le. Moi nhap lai - Ngay: ";
            } else
                error = false;
          }
          
        cout<< "Thang:";
        error=true;
		while (error) {
            cin>>emp->sinhnhat.thang;
            if (!cin || isMonthInvalid(emp->sinhnhat.thang)) {
                cin.clear();
                cin.ignore();
                cout << "Khong hop le. Moi nhap lai - Thang: ";
            } else
                error = false;
    	}
    	
        cout<< "Nam:";
        error=true;
        while (error) {
            cin>>emp->sinhnhat.nam;
            if (!cin || isYearInvalid(emp->sinhnhat.nam)) {
                cin.clear();
                cin.ignore();
                cout << "Khong hop le. Moi nhap lai - Nam: ";
            } else
                error = false;
          }

       	cout<< "Que Quan:";
		fflush(stdin);
		gets(emp->que);
		
		cout<< "Dia chi: ";
		fflush(stdin);
		gets(emp->diachi);
		
		cout<< "Email: ";
		error=true;
           while (error) {
               cin>>emp->email;
               if (!isValidEmailAddress (emp->email)) {
                   cout<< "Email khong hop le. Vui long thu lai: ";
               }
               else {
                   error = false;
               }
           }
        
		cout<< "So dien thoai: ";
        cin>>emp->sdt;
       
        cout<<"Ngay bat dau lam viec : "<<endl;
        cout<<"Ngay : ";
        error=true;
        while (error) {
            cin>>emp->ngaybd.ngay;
            if (!cin || isDayInvalid(emp->ngaybd.ngay)) {
                cin.clear();
                cin.ignore();
                cout << "Khong hop le. Moi nhap lai - Ngay: ";
            } else
                error = false;
          }
          
    	cout<<"Thang :";
    	error=true;
        while (error) {
            cin>>emp->ngaybd.thang;
            if (!cin || isMonthInvalid(emp->ngaybd.thang)) {
                cin.clear();
                cin.ignore();
                cout << "Khong hop le. Moi nhap lai - Thang: ";
            } else
                error = false;
          }
        
    	cout<<"Nam :";
    	error=true;
        while (error) {
            cin>>emp->ngaybd.nam;
            if (!cin || isYearInvalid(emp->ngaybd.nam)) {
                cin.clear();
                cin.ignore();
                cout << "Khong hop le. Moi nhap lai - Nam: ";
            } else
                error = false;
          }
	// ^ ket thuc nhap thong tin

	clock_t start = clock();
	pushEmployee(dsct, emp);
	cout 
		<< "---------------------------------------------" << endl
	 	<< "Nhan vien duoi day da duoc Them vao he thong!!!" << endl
	 	<< "Ten: " 
	 		<< emp->ten << endl
		<< "Ho: " 
			<< emp->ho << endl
		<< "Cong ty: " 
			<< emp->congty << endl
		<< "Chuc vu: " 
			<< emp->chucvu << endl
		<< "Ngay sinh:" 
			<< emp->sinhnhat.ngay << "/" 
			<< emp->sinhnhat.thang << "/" 
			<< emp->sinhnhat.nam << endl
		<< "Que Quan: " 
			<< emp->que << endl
		<< "Dia chi: " 
			<< emp->diachi << endl
		<< "Email: " 
			<< emp->email << endl
		<< "So dt: " 
			<< emp->sdt << endl <<endl
		<<" Ngay bat dau lam viec :"
			<<emp->ngaybd.ngay<<"/"
			<<emp->ngaybd.thang<<"/"
			<<emp->ngaybd.nam<<endl;

	cout << "Hoan thanh trong " << calTime(start) << " giay" << endl
	<<"========================================================================="<<endl;
		cout<<" Ban co muon them nhan vien nua khong,(Y=co/N=khong) :  ";
		cin>>flag;
	}while(flag=='y'||flag=='Y');
}

//cau 6
void updateEmp(vector<Company*> &dsct) {
	cout << endl<< "********* UPDATE *************" << endl;
	char manv[4];
	bool error;
	clock_t start;
	double totalTime;

	do {
		cout << "Xin moi nhap ma nhan vien: " << endl;
		error = true;
		while (error) {
			cin >> manv;
			error = (!isInputEmpty(manv) && !isManvInvalid(manv)) ? false : true;
			if (error)
				cout << "Ten nhap vao khong hop le! Moi nhap lai: ";
		}
		start = clock();
		Employee* empNeedToFind = findEmployee(manv, dsct);
		if (empNeedToFind == NULL) {
			cout << "Sorry!!! Nhan vien nay khong ton tai. Vui long thu lai" << endl << endl;
		}
		totalTime = calTime(start);
	} while (findEmployee(manv, dsct) == NULL);

	Employee *emp = findEmployee(manv, dsct);
	int choice;
    char redo;	//co hieu
    do {
    	cout << 
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
    	endl << "10.Thoat." <<
    	endl << "Nhap thao tac ban muon thuc hien: ";
    	cin >> choice;
    	if (choice == 1) {
    		cout << "Ho: ";
    		fflush(stdin);
    		cin.getline (emp->ho, 30);
    	}
    	else if (choice == 2) {
    		cout << "Ten: ";
    		cin >> emp->ten;
    	}
    	else if (choice == 3) {
    		cout << "Don vi: ";
    		cin >> emp->congty;
    	}
    	else if (choice == 4) {
    		cout << "Ten: ";
    		cin >> emp->chucvu;
    	}
    	else if (choice == 5) {
    		cout << "Ngay: " << "  ";
    		error = true;
    		while (error) {
    			cin >> emp->sinhnhat.ngay;
    			if (!cin || isDayInvalid(emp->sinhnhat.ngay)) {
    				cin.clear();
    				cin.ignore();
    				cout << "Khong hop le. Moi nhap lai - Ngay: ";
    			} else
    			error = false;
    		}

    		cout << "Thang: " << "  ";
    		error = true;
    		while (error) {
    			cin >> emp->sinhnhat.thang;
    			if (!cin || isMonthInvalid(emp->sinhnhat.thang)) {
    				cin.clear();
    				cin.ignore();
    				cout << "Khong hop le. Moi nhap lai - Thang: ";
    			} else
    			error = false;
    		}
    		cout << "Nam: " << "  ";
    		error = true;
    		while (error) {
    			cin >> emp->sinhnhat.nam;
    			if (!cin || isYearInvalid(emp->sinhnhat.nam)) {
    				cin.clear();
    				cin.ignore();
    				cout << "Khong hop le. Moi nhap lai - Nam: ";
    			} else
    			error = false;
    		}
    	}
    	else if (choice == 6) {
    		cout << "Que Quan: ";
    		cin >> emp->que;
    	}
    	else if (choice == 7) {
    		cout << "Dia chi: ";
    		cin >> emp->ten;
    	}
    	else if (choice == 8) {
    		cout << "Email: ";
    		error = true;
    		while (error) {
    			cin >> emp->email;
    			if (!isValidEmailAddress (emp->email)) {
    				cout << "Email khong hop le. Vui long thu lai: ";
    			}
    			else {
    				error = false;
    			}
    		}
    	}
    	else if (choice == 9) {
    		cout << "So dien thoai: ";
    		cin>> emp->sdt;
    	}

    	else if (choice == 10) {
    		break;
    	}
    	cout << "Ban co muon update them khong? (Y/N) = ";
    	cin >> redo;
    } while (redo == 'y' || redo == 'Y');

    cout << "---------------------------------------------" << endl;
    cout << "Nhan vien duoi day da duoc update vao he thong!!!" << endl;
    cout << "Ten: " 
    	 << emp->ten << endl;
    cout << "Ho: " 
    	 << emp->ho << endl;
    cout << "Cong ty: " 
    	 << emp->congty << endl;
    cout << "Chuc vu: " 
    	 << emp->chucvu << endl;
    cout << "Ngay sinh: " 
    	 << emp->sinhnhat.ngay << "/" 
    	 << emp->sinhnhat.thang << "/" 
    	 << emp->sinhnhat.nam << endl;
    cout << "Que Quan: " 
    	 << emp->que<< endl;
    cout << "Dia chi: " 
    	 << emp->diachi<< endl;
    cout << "Email: " 
    	 << emp->email<< endl;
    cout << "So dt: " 
    	 << emp->sdt<< endl;

    cout << "Hoan thanh trong "
    	 << totalTime << " giay" << endl;
}

int main() {
    cout << "~~~***  CHUONG TRINH QUAN LI NHAN VIEN  ***~~~" << endl << endl;

    cout << "Dang doc file input.txt... ";
    const char *filePath = "input.txt";
    FILE *file;
    file = fopen(filePath, "r");
    vector<Company*> dsct;
    read(file, dsct);
    cout << "Done." << endl;

    int choice;
    bool running = true;
    while (running) {
        cout <<
        endl << "Hay lua chon cac thao tac:" <<
        endl << "1. Hien thi cac thong tin co ban ve BKCorporation" <<
        endl << "2. Tim kiem nhan vien bang ho ten" <<
        endl << "3. Hien thi tinh trang lam viec cua nhan vien" <<
        endl << "4. Hien thi thong tin cua mot don vi" <<
        endl << "5. Them nhan vien moi" <<
        endl << "6. Cap nhat thong tin nhan vien" <<
        endl << "7: Thoat chuong trinh" << endl <<
        endl << "Nhap thao tac ban muon thuc hien: ";

        cin  >> choice;
        cout << endl;

        switch (choice) {
        case 1: {
            showBKCorp(dsct);
            break; }
        case 2: {
            search_stuff(dsct);
            break; }
        case 3: {
            showInfoEmp(dsct);
            break; }
        case 4: {
            print_donvi(dsct);
            break; }
        case 5: {
            addEmp(dsct);
		    break; }
        case 6: {
            updateEmp(dsct);
            break; }
        case 7: {
            running = false;
            cout << "Nhan phim bat ki de ket thuc.";
            break; }
        }
    }

    return 0;
}
