//Tuần 4
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

vector<int> KSA(const string& key) {
    vector<int> S(256);

    for (int i = 0; i < 256; i++) {
        S[i] = i;
    }

    int j = 0;
    int key_length = key.length();
    
    // Trộn mảng S dựa vào khóa
    for (int i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % key_length]) % 256;
        swap(S[i], S[j]);
    }
    return S;
}

vector<unsigned char> RC4(const string& key, const string& data) {
    vector<int> S = KSA(key);
    vector<unsigned char> result;
    
    int i = 0;
    int j = 0;
    
    for (size_t n = 0; n < data.length(); n++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]); // Hoán đổi S[i] và S[j]
        
        // Lấy giá trị K từ mảng S
        int K = S[(S[i] + S[j]) % 256];
        
        // XOR byte dữ liệu gốc với byte khóa K
        result.push_back(data[n] ^ K);
    }
    
    return result;
}

int main() {
    string key = "khoabimat";
    string plaintext = "Xin chao VS Code bang C++!";

    cout << "--- THUAT TOAN MA HOA RC4 (C++) ---\n";
    cout << "Khoa (Key): " << key << "\n";
    cout << "Van ban goc: " << plaintext << "\n";
    vector<unsigned char> ciphertext = RC4(key, plaintext);
    
    cout << "Ban ma (Hex): ";
    
    for (unsigned char c : ciphertext) {
        
        cout << hex << uppercase << setfill('0') << setw(2) << (int)c;
    }
    cout << dec << "\n";

    string ciphertext_str(ciphertext.begin(), ciphertext.end());
    vector<unsigned char> decrypted = RC4(key, ciphertext_str);
    
    cout << "Van ban giai ma: ";
    for (unsigned char c : decrypted) {
        cout << c;
    }
    cout << "\n";

    return 0;
}