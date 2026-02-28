#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

//Bỏ luôn j, tẹo nữa có chuỗi cần mã hoá thì chạy 1 vòng lặp để đổi j thành i sau đó chạy thuật toán
char alphabet[27] = "abcdefghiklmnopqrstuvwxyz";
char codingArray[27];

void createCodingArray(char signature[27]) {
    int length = 26; //biến này để đếm độ dài của chuỗi mã hoá được cho vào
    for(int i=0; i<27; i++) {
        if(signature[i] == '\0') {
            length = i;
            break;
        }

        codingArray[i] = signature[i];
    }

    int counter = length; //biến này để hỗ trợ việc chèn các kí tự còn lại của bảng chữ cái vào sau chuỗi mã hoá
    for(int i = 0; i < 27; i++) {
        for(int j = 0; j < length; j++) {
            if(alphabet[i] == codingArray[j]) break;
            
            if(j == length-1) {
                codingArray[++counter] = alphabet[i];
                // cout << alphabet[i];
            }
        }
    }

}

void monitoringCoding() {
    for(int i = 0; i < 27; i++) {
        cout << codingArray[i];
    }
}

int main() {
    char array[] = "namanh";
    createCodingArray(array);
    monitoringCoding();

}