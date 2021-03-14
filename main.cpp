#include <iostream>
#pragma once
#ifndef BIGNUMBER_H
#define BIGNUMBER_H
#include <string>
#include <iostream>
using namespace std;

class BigNumber
{
private:
    friend ostream& operator<<(ostream&, const BigNumber&);
    friend istream& operator>>(istream&, BigNumber&);
    friend void cns(BigNumber&);
    friend int lengthBig(const BigNumber&);
    static const int length = 100;
    int number[length] = {0};
public:
    BigNumber();
    BigNumber(const long long int&);
    BigNumber(const char*);
    ~BigNumber();
    BigNumber operator+(const BigNumber&)const;
    BigNumber operator+(const int&)const;
    BigNumber operator+(const char*)const;
    BigNumber operator-(const BigNumber&)const;
    BigNumber operator-(const int&)const;
    BigNumber operator-(const char*)const;
    BigNumber operator*(const BigNumber&)const;
    BigNumber operator*(const int&)const;
    BigNumber operator*(const char*)const;
    BigNumber operator/(const BigNumber&)const;
    BigNumber operator/(const int&)const;
    BigNumber operator/(const char*)const;
    const BigNumber& operator+=(const BigNumber&);
    const BigNumber& operator+=(const int&);
    const BigNumber& operator+=(const char *);
    const BigNumber& operator-=(const BigNumber&);
    const BigNumber& operator-=(const int&);
    const BigNumber& operator-=(const char *);
    const BigNumber& operator*=(const BigNumber&);
    const BigNumber& operator*=(const int&);
    const BigNumber& operator*=(const char *);
    const BigNumber& operator/=(const BigNumber&);
    const BigNumber& operator/=(const int&);
    const BigNumber& operator/=(const char *);
    const BigNumber operator++(int);//postfix
    const BigNumber& operator++();//postfix
    const BigNumber operator--(int);//postfix
    const BigNumber& operator--();//postfix
    bool operator==(const BigNumber&)const;
    bool operator!=(const BigNumber&)const;
    bool operator<(const BigNumber&)const;
    bool operator>(const BigNumber&)const;
    bool operator<=(const BigNumber&)const;
    bool operator>=(const BigNumber&)const;
};
#endif
int main() {
    BigNumber a("999999999999999999999");
    BigNumber b(5);
    BigNumber c;
    BigNumber d("999999999999999999999");
    cout << "a=" << a << endl << "b=" << b << endl << "c=" << c << endl << endl;
    cout << "c += a * 2 - b";
    c += a * 2 - b;
    cout << "a=" << a << endl << "b=" << b << endl << "c=" << c << endl << endl;
    cout << "c -= a / d";
    c -= a / d;
    cout << "a=" << a << endl << "b=" << b << endl << "c=" << c << endl << endl;
    cout << "c -= a";
    c -= a;
    cout << "a=" << a << endl << "b=" << b << endl << "c=" << c << endl << endl;
    cout << "c = b--";
    c = b--;
    cout << "a=" << a << endl << "b=" << b << endl << "c=" << c << endl << endl;
    cout << "c = --b";
    c = --b;
    cout << "a=" << a << endl << "b=" << b << endl << "c=" << c << endl << endl;
    if (a == b)
        cout << "equal\n";
    else
        cout << "Not equal\n";
    return 0;
}

ostream& operator<<(ostream& output, const BigNumber& x) {
    int counter = 100 - lengthBig(x);
    if (counter == 100) {
        output << 0;
        return output;
    }
    for (int j = counter; j < 100; j++) {
        output << x.number[j];
    }
    return output;
}

istream& operator>>(istream& input, BigNumber& x) {
    string str;
    char a1[100] = {0};
    getline(input,str);
    for (int i = 0; i < str.size(); i++) {
        a1[i] = str[i];
    }
    BigNumber a(a1);
    x = a;
    return input;
}

void cns(BigNumber& a) {
    for (int i = 0; i < 100; i++) {
        a.number[i] = 0;
    }
}

BigNumber::BigNumber() {
    cns(*this);
}

BigNumber::BigNumber(const long long int& a) {
    cns(*this);
    int i = 99;
    long long int b = a;
    while (b / 10 > 0) {
        number[i] = b % 10;
        b /= 10;
        i--;
    }
    number[i] = b % 10;
}

BigNumber::BigNumber(const char* a) {
    cns(*this);
    int count = 0;
    for (int i = 99; i >= 0; i--) {
        if (a[99 - i] == '\0')
            break;
        else
            count++;
    }
    for (int i = count-1; i >=0 ; i--) {
        this->number[99-count+i+1] = a[i]-48;
    }
}

BigNumber::~BigNumber() {

}

BigNumber BigNumber::operator+(const BigNumber& a)const {
    BigNumber c;
    for (int i = 99; i >= 0; i--) {
        int x = this->number[i] + a.number[i];
        c.number[i] += x % 10;
        if (i - 1 < 0)
            break;
        else
            c.number[i - 1] += x / 10;
    }
    return c;
}
BigNumber BigNumber::operator+(const int& a)const {
    BigNumber a1(a);
    return *this + a1;
}
BigNumber BigNumber::operator+(const char* a)const {
    BigNumber a1(a);
    return *this + a1;
}

BigNumber BigNumber::operator-(const BigNumber& a)const {
    BigNumber d,th = *this;
    if (th >= a) {
        for (int i = 99; i >= 0; i--) {
            if (th.number[i] < a.number[i]) {
                th.number[i] += 10;
                if (i - 1 < 0)
                    break;
                th.number[i - 1]--;
            }
            d.number[i] = th.number[i] - a.number[i];
        }
        return d;
    }
    BigNumber mines(-1);
    return mines;
}
BigNumber BigNumber::operator-(const int& a)const {
    BigNumber a1(a);
    return *this - a1;
}
BigNumber BigNumber::operator-(const char* a)const {
    BigNumber a1(a);
    return *this - a1;
}

BigNumber BigNumber::operator*(const BigNumber& a)const {
    BigNumber sum;
    long long int temp = 0, power = 1;
    /*for (int i = 99; i >= 0; i--) {
        temp = a.number[i] * power;
        for (long long int j = 0; j < temp; j++) {
            sum += *this;
        }
        power *= 10;
    }*/
    int p = 0;
    BigNumber t ,sec,first;
    if (*this >= a) {
        first = *this;
        sec = a;
    }
    else {
        first = a;
        sec = *this;
    }
    for (int i = 99; i >= 100 - lengthBig(sec); i--) {
        t.number[99 - p] = sec.number[i];
        if (sec.number[i] != 0) {
            for (BigNumber j; j < t; j++)
                sum += first;
        }
        cout << t << endl;
        p++;
        cns(t);
    }
    return sum;
}
BigNumber BigNumber::operator*(const int &a)const {
    BigNumber a1(a);
    return *this * a1;
}
BigNumber BigNumber::operator*(const char*a)const {
    BigNumber a1(a);
    return *this * a1;
}

BigNumber BigNumber::operator/(const BigNumber&a)const {
    BigNumber s = *this, ziro;
    BigNumber counter;
    while ((s - a) >= ziro) {
        if (s == ziro)
            break;
        s -= a;
        counter++;
    }
    return counter;
}
BigNumber BigNumber::operator/(const int&a)const {
    BigNumber a1(a);
    return *this / a1;
}
BigNumber BigNumber::operator/(const char*a)const {
    BigNumber a1(a);
    return *this / a1;
}

const BigNumber& BigNumber::operator+=(const BigNumber& a) {
    BigNumber c;
    c = *this + a;
    *this = c;
    return *this;
}
const BigNumber& BigNumber::operator+=(const int& a) {
    BigNumber a1(a);
    *this += a1;
    return *this;
}
const BigNumber& BigNumber::operator+=(const char *a) {
    BigNumber a1(a);
    *this += a1;
    return *this;
}

const BigNumber& BigNumber::operator-=(const BigNumber& a) {
    BigNumber c;
    c = *this - a;
    *this = c;
    return *this;
}
const BigNumber& BigNumber::operator-=(const int& a) {
    BigNumber a1(a);
    *this -= a1;
    return *this;
}
const BigNumber& BigNumber::operator-=(const char *a) {
    BigNumber a1(a);
    *this -= a1;
    return *this;
}

const BigNumber& BigNumber::operator*=(const BigNumber&a) {
    BigNumber c;
    c = *this * a;
    *this = c;
    return *this;
}
const BigNumber& BigNumber::operator*=(const int&a) {
    BigNumber a1(a);
    *this *= a1;
    return *this;
}
const BigNumber& BigNumber::operator*=(const char *a) {
    BigNumber a1(a);
    *this *= a1;
    return *this;
}

const BigNumber& BigNumber::operator/=(const BigNumber&a) {
    BigNumber c;
    c = *this / a;
    *this = c;
    return *this;
}
const BigNumber& BigNumber::operator/=(const int&a) {
    BigNumber a1(a);
    *this /= a1;
    return *this;
}
const BigNumber& BigNumber::operator/=(const char *a) {
    BigNumber a1(a);
    *this /= a1;
    return *this;
}

const BigNumber BigNumber::operator++(int) {//postfix a++
    BigNumber temp = *this;
    *this += 1;
    return temp;

}
const BigNumber& BigNumber::operator++() {//postfix
    *this += 1;
    return *this;
}
const BigNumber BigNumber::operator--(int) {//postfix
    BigNumber temp = *this;
    *this -= 1;
    return temp;
}
const BigNumber& BigNumber::operator--() {//postfix
    *this -= 1;
    return *this;
}

bool BigNumber::operator==(const BigNumber&a)const {
    bool flag=true;
    for (int i = 0; i < 100; i++) {
        if (this->number[i] != a.number[i]) {
            flag = false;
            return flag;
        }
    }
    return flag;
}
bool BigNumber::operator!=(const BigNumber&a)const {
    if (a == *this)
        return false;
    else
        return true;
}

bool BigNumber::operator<(const BigNumber&a)const {
    int length1 = lengthBig(*this);
    int length2 = lengthBig(a);
    if (length1 == length2) {
        for (int i = 100-length; i<=99; i++) {
            if (this->number[i] < a.number[i])
                return true;
        }
        return false;
    }
    else if (length1 < length2)
        return true;
    else
        return false;
}

bool BigNumber::operator>(const BigNumber&a)const {
    if (*this < a)
        return false;
    else if (*this == a)
        return false;
    else
        return true;
}

bool BigNumber::operator<=(const BigNumber&a)const {
    if (*this > a)
        return false;
    return true;
}
bool BigNumber::operator>=(const BigNumber&a)const {
    if (*this < a)
        return false;
    return true;
}


int lengthBig(const BigNumber& a) {
    int c = 0;
    for (int i = 0; i < 100; i++) {
        if (a.number[i] == 0)
            c++;
        else
            return 100-c;
    }
    return 0;
}
