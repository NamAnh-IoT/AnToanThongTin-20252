#include <iostream>

using namespace std;

int get_degree(int n) {
    if (n == 0) return -1;
    int deg = 0;
    while (n >>= 1) deg++;
    return deg;
}

int gf_poly_div(int a, int b, int &rem) {
    int deg_a = get_degree(a);
    int deg_b = get_degree(b);
    if (deg_a < deg_b) {
        rem = a;
        return 0;
    }
    int quot = 0;
    rem = a;
    while (deg_a >= deg_b) {
        int shift = deg_a - deg_b;
        quot ^= (1 << shift);
        rem ^= (b << shift);
        deg_a = get_degree(rem);
    }
    return quot;
}

int gf_poly_mul(int a, int b) {
    int res = 0;
    while (b > 0) {
        if (b & 1) res ^= a;
        a <<= 1;
        b >>= 1;
    }
    return res;
}

void extended_euclidean(int a, int m = 1033) {
    int r0 = m, r1 = a;
    int v0 = 0, v1 = 1;
    int step = 1;

    cout << "Buoc 0: r = " << r0 << ", v = " << v0 << endl;
    cout << "Buoc 1: r = " << r1 << ", v = " << v1 << endl;

    while (r1 != 0) {
        int rem;
        int quot = gf_poly_div(r0, r1, rem);
        
        int v_next = v0 ^ gf_poly_mul(quot, v1);
        
        r0 = r1;
        r1 = rem;
        v0 = v1;
        v1 = v_next;

        step++;
        cout << "Buoc " << step << ": r = " << r0 << ", v = " << v0 << " (q = " << quot << ")" << endl;
        
        if (r0 == 1) break;
    }

    cout << "=> Nghich dao cua " << a << " la: " << v0 << endl;
    cout << "-----------------------------------" << endl;
}

int main() {
    cout << "Tim nghich dao cho a = 523:" << endl;
    extended_euclidean(523);

    cout << "Tim nghich dao cho b = 1015:" << endl;
    extended_euclidean(1015);

    return 0;
}