#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Bảng chữ cái Playfair (không có j, tổng 25 ký tự)
char alphabet[26] = "abcdefghiklmnopqrstuvwxyz";
char codingArray[25]; // Dùng mảng 1 chiều sau đó xử lý coi như mảng 2 chiều được xếp trên cùng 1 chiều

// 1. Hàm tạo bảng mã từ key
void createCodingArray(string signature) {
    bool used[26] = {false};
    int count = 0;

    // Đưa từ khóa vào trước
    for (char c : signature) {
        if (c == 'j') c = 'i';
        if (!used[c - 'a']) {
            codingArray[count++] = c;
            used[c - 'a'] = true;
        }
    }
    used['j' - 'a'] = true; // Đánh dấu j đã dùng chung với i

    // Điền nốt bảng chữ cái còn thiếu
    for (int i = 0; i < 25; i++) {
        if (!used[alphabet[i] - 'a']) {
            codingArray[count++] = alphabet[i];
            used[alphabet[i] - 'a'] = true;
        }
    }
}

// 2. Hàm xử lý chuỗi: Xóa khoảng trắng, đổi j->i, tách cặp trùng nhau
string preprocess(string text) {
    string temp = "";
    for (char c : text) {
        if (c == ' ') continue;
        if (c == 'j') c = 'i';
        temp += c;
    }

    string result = "";
    for (int i = 0; i < temp.length(); i++) {
        result += temp[i];
        // Nếu ký tự tiếp theo giống ký tự hiện tại (trong cùng 1 cặp)
        if (i + 1 < temp.length()) {
            if (temp[i] == temp[i + 1]) {
                result += 'x'; // Thêm x vào giữa
            } else {
                result += temp[++i]; // Lấy ký tự tiếp theo
            }
        } else {
            result += 'x'; // Nếu lẻ thì thêm x ở cuối
        }
    }
    return result;
}

// 3. Hàm tìm vị trí trong mảng 1 chiều
int findPos(char c) {
    for (int i = 0; i < 25; i++) {
        if (codingArray[i] == c) return i;
    }
    return -1;
}

// 4. Hàm mã hóa chính
string encrypt(string input) {
    string text = preprocess(input);
    string cipher = "";

    for (int i = 0; i < text.length(); i += 2) {
        int pos1 = findPos(text[i]);
        int pos2 = findPos(text[i + 1]);

        int r1 = pos1 / 5, c1 = pos1 % 5;
        int r2 = pos2 / 5, c2 = pos2 % 5;

        if (r1 == r2) { // Cùng hàng -> Dịch phải
            cipher += codingArray[r1 * 5 + (c1 + 1) % 5];
            cipher += codingArray[r2 * 5 + (c2 + 1) % 5];
        } else if (c1 == c2) { // Cùng cột -> Dịch xuống
            cipher += codingArray[((r1 + 1) % 5) * 5 + c1];
            cipher += codingArray[((r2 + 1) % 5) * 5 + c2];
        } else { // Khác hàng cột -> Quy tắc hình chữ nhật
            cipher += codingArray[r1 * 5 + c2];
            cipher += codingArray[r2 * 5 + c1];
        }
    }
    return cipher;
}

int main() {
    string code = "monarchy";
    string content = "do you like to study a cryptography course";

    createCodingArray(code);
    
    // In bảng mã để kiểm tra
    cout << "Bang ma 5x5: " << endl;
    for(int i=0; i<25; i++) {
        cout << codingArray[i] << " ";
        if((i+1)%5 == 0) cout << endl;
    }

    string cipherText = encrypt(content);
    cout << "\nBan ro sau xu ly: " << preprocess(content) << endl;
    cout << "Ket qua ma hoa: " << cipherText << endl;

    return 0;
}