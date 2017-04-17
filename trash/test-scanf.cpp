#include <iostream>

using namespace std;

int main() {
	char* ten = "123,123";
	int* loz = NULL;
	int* cac = NULL;
	sscanf(ten, "%d, %d", loz, cac);
	cout << loz << " " << cac;
	return 0;
}
