#include <bits/stdc++.h>

class String {
#define _MAX_STR_SIZE 10000000U
private :
    unsigned size_, capacity;
    char* str;
    char runout;
public :
    explicit String(unsigned size = 0);
    String(const char* src);
    String(const String & src);
    String(char ch);
    virtual ~String();
    String & operator = (const String & src);
    String & operator = (const char* src);
    String & operator = (char ch);
    String & ensure(unsigned size);
    String & adjust();

    char & operator [] (unsigned i);
    char operator [] (unsigned i) const;
    unsigned size() const {return size_;}
    unsigned length() const {return size_;}
    const char* c_str() const {return str;}
    bool operator == (const String & y) const;
    bool operator < (const String & y) const;
    bool operator > (const String & y) const;
    bool operator <= (const String & y) const;
    bool operator >= (const String & y) const;
    bool operator != (const String & y) const;
    String operator + (const String & y) const;
    String operator + (const char* y) const;
    String operator + (char ch) const;
    String & operator += (const String & y);
    String & operator += (const char* y);
    String & operator += (char ch);

    friend String operator + (const char* x, const String & y);
    friend String operator + (char ch, const String & str);
    friend std::ostream & operator << (std::ostream & os, const String & str) {return os << str.str;}
    friend std::istream & operator >> (std::istream & is, String & str);
};

String::String(char ch) {
    size_ = 1;
    capacity = std::min(size_ << 1, _MAX_STR_SIZE);
    str = new char[capacity + 1];
    str[0] = ch;
    str[size_] = runout = '\0';
}

String & String::operator = (char ch) {
    size_ = 1;
    adjust();
    str[0] = ch;
}

String operator + (char ch, const String & str) {
    String ans(str.size_ + 1);

    std::memcpy(ans.str, str.str, sizeof(char) * str.size_);
    ans.size_ = std::min(str.size_ + 1, _MAX_STR_SIZE);
    ans.str[str.size_] = ch;
    ans.str[ans.size_] = ans.runout = '\0';
    return ans;
}

String & String::operator += (char ch) {
    ensure(size_ + 1);
    str[size_] = ch;
    size_ = std::min(size_ + 1, _MAX_STR_SIZE);
    str[size_] = '\0';
    return *this;
}

String String::operator + (char ch) const {
    String ans(size_ + 1);

    std::memcpy(ans.str, str, sizeof(char) * size_);
    ans.size_ = std::min(size_ + 1, _MAX_STR_SIZE);
    ans.str[size_] = ch;
    ans.str[ans.size_] = ans.runout = '\0';
    return ans;
}

String & String::operator += (const char* y) {
    unsigned len = std::min((unsigned)std::strlen(y), _MAX_STR_SIZE);

    ensure(len + size_);
    std::memcpy(str + size_, y, sizeof(char) * std::min(len, capacity - size_));
    str[size_] = runout = '\0';
    return *this;
}

String String::operator + (const char* y) const {
    unsigned len = std::min((unsigned)std::strlen(y), _MAX_STR_SIZE);
    String ans(len + size_);

    std::memcpy(ans.str, str, sizeof(char) * size_);
    std::memcpy(ans.str + size_, y, sizeof(char) * std::min(len, ans.capacity - size_));
    ans.size_ = std::min(len + size_, _MAX_STR_SIZE);
    ans.str[ans.size_] = ans.runout = '\0';
    return ans;
}

String operator + (const char* x, const String & y) {
    unsigned len = std::min((unsigned)std::strlen(x), _MAX_STR_SIZE);
    String ans(len + y.size_);

    std::memcpy(ans.str, x, sizeof(char) * len);
    std::memcpy(ans.str + len, y.str, sizeof(char) * std::min(y.size_, ans.capacity - len));
    ans.size_ = std::min(len + y.size_, _MAX_STR_SIZE);
    ans.str[ans.size_] = ans.runout = '\0';
    return ans;
}

String String::operator + (const String & y) const {
    String x(size_ + y.size_);

    std::memcpy(x.str, str, sizeof(char) * size_);
    std::memcpy(x.str + size_, y.str, sizeof(char) * std::min(y.size_, x.capacity - size_));
    x.size_ = std::min(size_ + y.size_, _MAX_STR_SIZE);
    x.str[x.size_] = x.runout = '\0';
    return x;
}

String & String::operator += (const String & y) {
    ensure(size_ + y.size_);
    std::memcpy(str + size_, y.str, sizeof(char) * std::min(y.size_, capacity - size_));
    size_ = std::min(size_ + y.size_, _MAX_STR_SIZE);
    str[size_] = runout = '\0';
    return *this;
}

inline bool String::operator == (const String & y) const {
    if (size_ != y.size_) {
        return false;
    }
    return (std::strcmp(str, y.str) == 0);
}

inline bool String::operator != (const String & y) const {
    if (size_ != y.size_) {
        return true;
    }
    return (std::strcmp(str, y.str) != 0);
}

inline bool String::operator < (const String & y) const {
    return std::strcmp(str, y.str) < 0;
}

inline bool String::operator <= (const String & y) const {
    return std::strcmp(str, y.str) <= 0;
}

inline bool String::operator > (const String & y) const {
    return std::strcmp(str, y.str) > 0;
}

inline bool String::operator >= (const String & y) const {
    return std::strcmp(str, y.str) >= 0;
}

String & String::operator = (const char* src) {
    int newCapacity;

    size_ = std::min((unsigned)std::strlen(src), _MAX_STR_SIZE);
    newCapacity = std::min(size_ << 1, _MAX_STR_SIZE);
    if (capacity != newCapacity) {
        capacity = newCapacity;
        delete[] str;
        str = new char[capacity + 1];
    }
    std::memcpy(str, src, sizeof(char) * size_);
    str[size_] = runout = '\0';
    return *this;
}

String::String(const char* src) {
    size_ = std::min((unsigned)std::strlen(src), _MAX_STR_SIZE);
    capacity = std::min(size_ << 1, _MAX_STR_SIZE);
    str = new char[capacity + 1];
    std::memcpy(str, src, sizeof(char) * size_);
    str[size_] = runout = '\0';
}

std::istream & operator >> (std::istream & is, String & str) {
    char ch;

    str = "";
    while (~(ch = is.peek()) && (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')) {
        ch = is.get();
    }
    while (~(ch = is.peek()) && ch != ' ' && ch != '\t' && ch != '\n' && ch != '\r') {
        ch = is.get();
        str.str[str.size_++] = ch;
        if (str.ensure(str.size_).size_ == _MAX_STR_SIZE) {
            break;
        }
    }
    str.str[str.size_] = '\0';
    return is;
}

inline String & String::adjust() {
    char* newStr;
    int newCapacity;

    size_ = std::min(size_, _MAX_STR_SIZE);
    newCapacity = std::min(size_ << 1, _MAX_STR_SIZE);
    if (capacity != newCapacity) {
        capacity = newCapacity;
        newStr = new char[capacity + 1];
        std::memcpy(newStr, str, sizeof(char) * size_);
        delete[] str;
        str = newStr;
    }
    str[size_] = runout = '\0'; 
    return *this;
}

inline String & String::ensure(unsigned size) {
    char* newStr;

    size = std::min(size, _MAX_STR_SIZE);
    if (capacity < size) {
        capacity = std::min(size << 1, _MAX_STR_SIZE);
        newStr = new char[capacity + 1];
        std::memcpy(newStr, str, sizeof(char) * size_);
        delete[] str;
        str = newStr;
    }
    str[size_] = runout = '\0';
    return *this;
}

String::String(unsigned size) {
    size_ = 0;
    size = std::min(size, _MAX_STR_SIZE);
    capacity = std::min(size << 1, _MAX_STR_SIZE);
    str = new char[capacity + 1];
    str[size_] = runout = '\0';
}

String::~String() {
    delete[] str;
}

String::String(const String & src) {
    size_ = std::min(src.size_, _MAX_STR_SIZE);
    capacity = std::min(size_ << 1, _MAX_STR_SIZE);
    str = new char[capacity + 1];
    std::memcpy(str, src.str, sizeof(char) * size_);
    str[size_] = runout = '\0';
}

char & String::operator [] (unsigned i) {
    if (i >= size_) {
        return runout;
    }
    return str[i];
}

char String::operator [] (unsigned i) const {
    if (i >= size_) {
        return runout;
    }
    return str[i];
}

String & String::operator = (const String & src) {
    int newCapacity;

    size_ = std::min(src.size_, _MAX_STR_SIZE);
    newCapacity = std::min(size_ << 1, _MAX_STR_SIZE);
    if (capacity != newCapacity) {
        capacity = newCapacity;
        delete[] str;
        str = new char[capacity + 1];
    }
    std::memcpy(str, src.str, sizeof(char) * size_);
    str[size_] = runout = '\0';
    return *this;
}

using namespace std;

int main() {
    String s1, s2;

    cin >> s1 >> s2;
    cout << s1.size() << endl << s2.size() << endl << s1 + s2 << endl << s2 + s2 << endl << (s1 == s2);
    return 0;
}