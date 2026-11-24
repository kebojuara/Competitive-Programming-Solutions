#include <cstdio>
#include <cstdlib>

template<typename T>
T getNum(){
    T res = 0;
    char c;
    while (1){
        c = getchar_unlocked();
        if (c >= '0' && c <= '9'){
            res = 10 * res + c - '0';
        }
        else break;
    }
    return res;
}

class Calculator {
private:
    const double underLimit = 1e-100;
    const double overLimit = 1e100;
    int bufferSize = 16;

    bool active, hasDot;
    int digits;
    char value[16];
    int len;


    double accumulator;
    bool isError;
    char pendingOp;


    void resetNumBuilder() {
        active = false; //gaada angka lagi di calculator
        hasDot = false;
        digits = 0;
        value[0] = '0';
        value[1] = '\0';
        len = 1;
    }

    double getAbs(double x) {
        return x < 0.0 ? -x : x;
    }

    bool checkMinVal(double a) {
        return (getAbs(a) <= underLimit);
    }
    
    bool checkMaxVal(double a) {
        return (getAbs(a) >= overLimit);
    }
    
    int decimalPrecision(double v) {
        if (v < 10.0) return 7;
        else if (v < 100.0) return 6;
        else if (v < 1000.0) return 5;
        else if (v < 10000.0) return 4;
        else if (v < 100000.0) return 3;
        else if (v < 1000000.0) return 2;
        else if (v < 10000000.0) return 1;
        else if (v < 100000000.0) return 0;
        return -1;
    }

    bool isOpr(char k) {
        return (k == '+' || k == '-' || k == 'x' || k == ':' || k == '=');
    }

    double operate(double a, char op, double b) {
        double r = 0.0;

        if (op == '+') r = a + b;
        else if (op == '-') r = a - b;
        else if (op == 'x') r = a * b;
        else if (op == ':') {
            if (b == 0.0) isError = true;
            else r = a / b;
        }
        else if (op == '=') r = b;

        if (checkMaxVal(r)) isError = true;

        return r;
    }

    void scientific(double x, char *buf, char *out) {
        int idx = 0;
        int end = 5;
        
        if (x < 0.0) out[idx++] = '-';
        while (buf[end] == '0') end--;

        for (int i = 0; i <= end; ++i)
            out[idx++] = buf[i];

        out[idx++] = (buf[7] == '-') ? '-' : ' ';
        out[idx++] = buf[8];
        out[idx++] = buf[9];
        
        out[idx] = '\0';
    }

    void decimal(char *s, int len) {
        while (len > 0 && s[len-1] == '0') len--;
        s[len] = '\0';
    }

    void format(double x, char *output) {
        double ax = getAbs(x);
        int prec = decimalPrecision(ax);

        if (ax < 1e-7 || ax >= 1e8) {
            char raw[bufferSize];
            snprintf(raw, bufferSize, "%.4e", ax);
            scientific(x, raw, output);
        }
        else {
            int len = snprintf(output, bufferSize, "%.*f", prec, x);
            if (prec == 0) output[len++] = '.';
            decimal(output, len);
        }
    }
    
    void processKey(char k) {
        if (k >= '0' && k <= '9') {
            active = true;

            if (digits < 8 && !(digits == 0 && k == '0')) {
                value[len++] = k;
                value[len] = '\0';
                digits++;
            }
        }

        else if (k == '.' && !hasDot) {
            if (len == 1) {
                active = true;
                digits++;
            }
            value[len++] = '.';
            value[len] = '\0';
            hasDot = true;
        }

        else if (isOpr(k)) {
            if (active) {
                double v = strtod(value, nullptr);
                resetNumBuilder();
                accumulator = operate(accumulator, pendingOp, v);
            }
            pendingOp = k;
        }
    }
    
    void getDisplay() {
        if (isError) {
            printf("    Error.\n");
        } else if (checkMinVal(accumulator)) {
            printf("        0.\n");
        } else {
            char result[bufferSize];
            format(accumulator, result);
            printf("%10s\n", result);
        }
    }

public:
    Calculator() { reset(); }

    void reset() {
        accumulator = 0.0;
        isError = false;
        pendingOp = '=';
        resetNumBuilder();
    }

    void pressKeys() {
        char buffer[512];
        int idx = 0;
        
        while (1) {
            getchar_unlocked();
            char k = getchar_unlocked();
            getchar_unlocked();
            
            if (k == 'C') idx = 0;
            else buffer[idx++] = k;
            
            if (getchar_unlocked() != ' ') break;
        }

        for(int i = 0; i < idx; i++) {
            if (isError) break;
            processKey(buffer[i]);
        }
        getDisplay();
    }

};

int main() {
    int T = getNum<int>();

    while (T--) {
        Calculator calc;
        calc.pressKeys();
    }

    return 0;
}