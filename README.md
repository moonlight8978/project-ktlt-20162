# **Bài tập lớn KTLT 20162 - Nhóm 19**

### **Đề tài 1:**

#### Quản lý nhân viên của một công ty:

<p>
Xây dựng hệ thống quản lý nhân viên của một tổng công ty BKCorporation. Cấu trúc tổ chức của công ty được phân cấp như sau:
</p>

<p>
Đứng đầu tổng công ty BKCorporation là Chủ tịch tập đoàn, dưới là các Phó Chủ tịch tập đoàn. Bên dưới tổng công ty là các công ty con BKEntertainment, BKFood, BKTech,… Mỗi công ty con được quản lý bởi giám đốc công ty và các phó giám đốc công ty. Bên dưới công ty là các phòng, ban trực thuộc công ty. Mỗi phòng, ban được quản lý bởi trưởng và phó phòng. Mỗi một phòng, ban có thể có một số lượng không giới hạn các nhân viên.
</p>

<p>
Mỗi một nhân viên hay người quản lý trong BKCorporation cần được quản lý những thông tin như: tên, ngày tháng năm sinh, quê quán, địa chỉ, email, số điện thoại, ngày bắt đầu làm việc và các thông tin liên quan đến mỗi ngày làm việc của nhân viên.
</p>

<p>
Xây dựng chương trình đọc thông tin của nhân viên từ file text được lưu như sau
</p>

```
Số thứ tự (mã số nhân viên, bắt đầu bằng ký tự NV)
Họ
Tên
Đơn vị
Chức vụ
Ngày tháng năm sinh
Quê quán
Địa chỉ
Email
Số điện thoại
Ngày bắt đầu làm việc
Ngày làm việc, thời gian đến, thời gian về
```

#### Ví dụ:

```
NV1
Trần Văn
A
BKCorporation
Chủ tịch
10/01/1980
Hà Nội
Số 1, Tạ Quang Bửu
tranvana@gmail.com
0123456789
22/02/2016
22/02/2016,7:49,18:00
23/02/2016,7:51,18:05
24/02/2016,7:45,12:30
NV2
Nguyễn Thị
B
BKEntertainment
Nhân viên
…
```

#### Chương trình cần thực hiện được các chức năng sau:

1. Hiển thị các thông tin cơ bản về BKCorporation (Tên chủ tịch, tên các công ty con và giám đốc, phó giám đốc tương ứng, tên các phòng ban và trưởng, phó phòng tương ứng, tổng số nhân viên của công ty)

2. Tìm kiếm thông tin của nhân viên: Nhập vào một chuỗi tìm kiếm, đưa ra tất cả các nhân viên có họ và tên tương ứng và các thông tin cơ bản về người đó.

3. Hiển thị tình trạng làm việc của nhân viên: Nhập vào mã nhân viên, đưa ra thông tin làm việc của nhân viên trong tháng hiện tại. Tính số giờ thiếu hụt của nhân viên (đi muộn, về sớm. Làm tròn lên 1 giờ. Không tính thứ 7 và chủ nhật và các ngày lễ)

4. Hiển thị thông tin của một đơn vị: Nhập vào một đơn vị (công ty con hoặc phòng, ban), liệt kê tất cả các nhân viên trong đơn vị đó.

5. Thêm nhân viên mới.

6. Cập nhật thông tin cơ bản của nhân viên đang làm việc tại công ty.

7. Thoát chương trình.

### Ứng dụng

#### Môi trường:

* Cài đặt G++: download tại [đây](https://sourceforge.net/projects/mingw/files/Installer/)

#### Chạy ứng dụng

* Biên dịch: `$ g++ main.cpp -o main.exe`

* Chạy: `$ ./main.exe`
