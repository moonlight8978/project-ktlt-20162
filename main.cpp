#include <iostream>
#include <vector>
#include <string.h>
#include<stdio.h>
#include <istream>
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
    Push vao Cong ty */
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

//tim nhan vien
Employee* findEmployee(char *manv,vector<Company*> &dsct){
    int i,j;
    int nosOfCo=dsct.size();
    for(i=0;i<nosOfCo;i++){
       vector<Employee*>* dsnv = &dsct[i]->dsnv;
        int nosOfEmp = (*dsnv).size();
        for(j=0;j<nosOfEmp;j++){
           if(strcmp((*dsnv)[j]->manv,manv)==0){
               return (*dsnv)[j];
           }
        }
    }
    return NULL;
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
                     << (*dsnv)[j]->ho << " "<<  (*dsnv)[j]->ten <<endl
                     << (*dsnv)[j]->chucvu<< endl
                     << (*dsnv)[j]->sinhnhat.ngay << "/" << (*dsnv)[j]->sinhnhat.thang << "/" << (*dsnv)[j]->sinhnhat.nam << endl
                     << (*dsnv)[j]->que << endl
                     << (*dsnv)[j]->diachi << endl
                     << (*dsnv)[j]->email <<endl
                     << (*dsnv)[j]->sdt << endl
                     << (*dsnv)[j]->ngaybd.ngay << "/" << (*dsnv)[j]->ngaybd.thang << "/" << (*dsnv)[j]->ngaybd.nam <<endl;
                for(int k=0;k<7;k++)
                {
                    cout << (*dsnv)[j]->ngaylv[k].ngay << "/" << (*dsnv)[j]->ngaylv[k].thang << "/" << (*dsnv)[j]->ngaylv[k].nam << ", "
                         << (*dsnv)[j]->gioden[k].gio << ":" << (*dsnv)[j]->gioden[k].phut << ", "
                         << (*dsnv)[j]->giove[k].gio << ":" << (*dsnv)[j]->giove[k].phut << endl ;
                }
                cout << endl;
            }
        }
    }
}

//cau 6
void updateEmp(vector<Company*> &dsct){
    cout<<endl<<"*********UPDATE*************"<<endl;
    char manv[4];
    do{
       cout<<"Xin moi nhap ma nhan vien:"<<endl;
       cin>>manv;
       if(findEmployee(manv,dsct)==NULL){
           cout<<"Sorry!!! Nhan vien nay khong ton tai. Vui long thu lai"<<endl<<endl;
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
        endl << "10.Thoat. "<<
        endl << "Nhap thao tac ban muon thuc hien: ";
        cin>>choice;
        if(choice==1){
           cout<<"Ho: ";
           cin>>emp->ho;
        }
        else if(choice==2){
           cout<<"Ten: ";
           cin>>emp->ten;
        }
        else if(choice==3){
           cout<<"Don vi: ";
           cin>>emp->congty;
        }
        else if(choice==4){
           cout<<"Ten: ";
           cin>>emp->chucvu;
        }
        else if(choice==5){
           cout<<"Ngay:"<<"  ";
           cin>>emp->sinhnhat.ngay;
           cout<<"Thang:"<<"  ";
           cin>>emp->sinhnhat.thang;
           cout<<"Nam:"<<"  ";
           cin>>emp->sinhnhat.nam;
        }
        else if(choice==6){
           cout<<"Que Quan: ";
           cin>>emp->que;
        }
        else if(choice==7){
           cout<<"Dia chi: ";
           cin>>emp->ten;
        }
        else if(choice==8){
           cout<<"Email: ";
           cin>>emp->email;
        }
        else if(choice==9){
           cout<<"So dien thoai: ";
           cin>>emp->sdt;
        }
        else if(choice==10){
           break;
        }
        cout<<"Ban co muon update them khong?(Y/N)=";
        cin>>redo;
    }while (redo=='y'||redo=='Y');
    cout<<"---------------------------------------------"<<endl;
    cout<<"Nhan vien duoi day da duoc update vao he thong!!!"<<endl;
    cout<<"Ten: "<<emp->ten<<endl;
    cout<<"Ho: "<<emp->ho<<endl;
    cout<<"Cong ty: "<<emp->congty<<endl;
    cout<<"Chuc vu: "<<emp->chucvu<<endl;
    cout<<"Ngay sinh:"<<emp->sinhnhat.ngay<<"/"<<emp->sinhnhat.thang<<"/"<<emp->sinhnhat.nam<<endl;
    cout<<"Que Quan: "<<emp->que<<endl;
    cout<<"Dia chi: "<<emp->diachi<<endl;
    cout<<"Email: "<<emp->email<<endl;
    cout<<"So dt: "<<emp->sdt<<endl;
}
int main() {
    cout << "Chuong trinh quan li nhan vien:" << endl;
    cout << "Dang doc file input.txt... ";
    const char *filePath = "/home/huuthang/Desktop/info.txt";
    FILE *file;
    file = fopen(filePath, "r");
    bool running=true;
    vector<Company*> dsct;
    int choice;
    read(file, dsct);
    cout << "Done." << endl;

    while(running) {
        cout <<
        endl << "Hay lua chon cac thao tac:" <<
        endl << "1. Hien thi cac thong tin co ban ve BKCorporation." <<
        endl << "2. Tim kiem nhan vien bang ho ten." <<
        endl << "3. Hien thi tinh trang lam viec cua nhan vien." <<
        endl << "4. Hien thi thong tin cua mot don vi." <<
        endl << "5. Them nhan vien moi." <<
        endl << "6. Cap nhat thong tin nhan vien." <<
        endl << "7: Thoat chuong trinh "<<endl<<
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
                print_donvi(dsct);
                break;
            }
            case 5: {
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