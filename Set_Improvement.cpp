#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

typedef struct order_pair {
    int PI[2];
    char PCH[2];
    string PSTR0, PSTR1;
} Repair;

class SET;
ostream& operator<<(ostream& os, SET& S);  // SET类重载<<声明

class SET {
   public:
    void setup();
    SET operator*(const SET& t);                               //交集
    SET operator&(const SET& t);                               //并集
    SET operator-(const SET& t);                               //差集
    void power(int i, SET T, SET* Res);                        //幂集
    SET Symmetrical_difference(const SET& S1, const SET& S2);  //对称差
    void Cartesian_product(const SET& S2);                     //笛卡尔积
    void Global_relationship();                                //全域关系
    void Identity_relationship();                              //恒等关系
    void LA();       //小于或等于关系
    SET domR();      //定义域
    SET ranR();      //值域
    void fldR();     //域
    void inverse();  //逆关系
    void judgement(string str);
    void judgement_OP(string str_OP);
    bool judgement_binary_relation();  //判断是否为二元关系
    inline size_t size() const;
    size_t SETHash() const;
    inline SET power();
    void display();
    void display_Relationship_matrix();  //显示矩阵
    inline void push(int IN);
    inline void push(char ch);
    inline void push(string str);
    inline void push(SET Set);
    inline void push_I(char IN);
    inline void push_CH(char CHAR);
    inline void push_STR(string STRING);
    inline void show(int x, int y);
    inline void judgement_domR(int x);
    inline bool operator<(const SET& S) const;        //重载<
    friend ostream& operator<<(ostream& os, SET& S);  //声明重载符号<<(友元)
    friend istream& operator>>(istream& in, SET& S);  //声明重载符号>>(友元)

   private:
    set<int> I;
    set<char> CH;
    set<string> STR;
    set<SET> SETS;
    vector<order_pair> OP;  //用来存储序偶

    string str_in;
    int cnt_OP;  //用来存储序偶的个数
};

void SET::setup() {
    // cout << "输入集合:" << endl;
    // getline(cin, str_in);
    ifstream in("input1.txt");
    while (!in.eof()) {
        getline(in, str_in);
    }
    in.close();
    cnt_OP = 0;
    str_in += " ";
    judgement(str_in);
    // display();
}
bool SET::judgement_binary_relation() {  //判断是否为二元关系
    if (size() == 0 && OP.size() != 0)
        return true;
    else
        return false;
}
void SET::Cartesian_product(const SET& S2) {  //笛卡尔积
    cout << "The Cartesian_product are:" << endl;
    set<int>::iterator itint = I.begin();
    for (int i = 0; i < I.size(); i++) {
        set<int>::iterator itint_j = S2.I.begin();
        for (int j = 0; j < S2.I.size(); j++) {
            cout << "<";
            cout << *itint << ",";
            cout << *itint_j;
            cout << "> , ";
            ++itint_j;
        }
        set<char>::iterator itch_j = S2.CH.begin();
        for (int j = 0; j < S2.CH.size(); j++) {
            cout << "<";
            cout << *itint << ",";
            cout << *itch_j;
            cout << "> , ";
            ++itch_j;
        }
        set<string>::iterator itstring_j = S2.STR.begin();
        for (int j = 0; j < S2.STR.size(); j++) {
            cout << "<";
            cout << *itint << ",";
            cout << *itstring_j;
            cout << "> , ";
            ++itstring_j;
        }
        ++itint;
    }
    set<char>::iterator itchar = CH.begin();
    for (int i = 0; i < CH.size(); i++) {
        set<int>::iterator itint_j = S2.I.begin();
        for (int j = 0; j < S2.I.size(); j++) {
            cout << "<";
            cout << *itchar << ",";
            cout << *itint_j;
            cout << "> , ";
            ++itint_j;
        }
        set<char>::iterator itch_j = S2.CH.begin();
        for (int j = 0; j < S2.CH.size(); j++) {
            cout << "<";
            cout << *itchar << ",";
            cout << *itch_j;
            cout << "> , ";
            ++itch_j;
        }
        set<string>::iterator itstring_j = S2.STR.begin();
        for (int j = 0; j < S2.STR.size(); j++) {
            cout << "<";
            cout << *itchar << ",";
            cout << *itstring_j;
            cout << "> , ";
            ++itstring_j;
        }
        ++itchar;
    }
    set<string>::iterator itstring = STR.begin();
    for (int i = 0; i < STR.size(); i++) {
        set<int>::iterator itint_j = S2.I.begin();
        for (int j = 0; j < S2.I.size(); j++) {
            cout << "<";
            cout << *itstring << ",";
            cout << *itint_j;
            cout << "> , ";
            ++itint_j;
        }
        set<char>::iterator itch_j = S2.CH.begin();
        for (int j = 0; j < S2.CH.size(); j++) {
            cout << "<";
            cout << *itstring << ",";
            cout << *itch_j;
            cout << "> , ";
            ++itch_j;
        }
        set<string>::iterator itstring_j = S2.STR.begin();
        for (int j = 0; j < S2.STR.size(); j++) {
            cout << "<";
            cout << *itstring << ",";
            cout << *itstring_j;
            cout << "> , ";
            ++itstring_j;
        }
        ++itstring;
    }
}
void SET::Global_relationship() {  //全域关系
    cout << "The Globalrelationship is :";
    set<int>::iterator itint = I.begin();
    for (int i = 0; i < I.size(); i++) {
        set<int>::iterator itint_temp = I.begin();
        for (int j = 0; j < I.size(); j++) {
            cout << "<";
            cout << *itint << ",";
            cout << *itint_temp;
            cout << "> , ";
            ++itint_temp;
        }
        set<char>::iterator itchar_temp = CH.begin();
        for (int j = 0; j < CH.size(); j++) {
            cout << "<";
            cout << *itint << ",";
            cout << *itchar_temp;
            cout << "> , ";
            ++itchar_temp;
        }
        set<string>::iterator itstring_temp = STR.begin();
        for (int j = 0; j < STR.size(); j++) {
            cout << "<";
            cout << *itint << ",";
            cout << *itstring_temp;
            cout << "> , ";
            ++itstring_temp;
        }
        ++itint;
    }
    set<char>::iterator itchar = CH.begin();
    for (int i = 0; i < CH.size(); i++) {
        set<int>::iterator itint_temp = I.begin();
        for (int j = 0; j < I.size(); j++) {
            cout << "<";
            cout << *itchar << ",";
            cout << *itint_temp;
            cout << "> , ";
            ++itint_temp;
        }
        set<char>::iterator itchar_temp = CH.begin();
        for (int j = 0; j < CH.size(); j++) {
            cout << "<";
            cout << *itchar << ",";
            cout << *itchar_temp;
            cout << "> , ";
            ++itchar_temp;
        }
        set<string>::iterator itstring_temp = STR.begin();
        for (int j = 0; j < STR.size(); j++) {
            cout << "<";
            cout << *itchar << ",";
            cout << *itstring_temp;
            cout << "> , ";
            ++itstring_temp;
        }
        ++itchar;
    }
    set<string>::iterator itstring = STR.begin();
    for (int i = 0; i < STR.size(); i++) {
        set<int>::iterator itint_temp = I.begin();
        for (int j = 0; j < I.size(); j++) {
            cout << "<";
            cout << *itstring << ",";
            cout << *itint_temp;
            cout << "> , ";
            ++itint_temp;
        }
        set<char>::iterator itchar_temp = CH.begin();
        for (int j = 0; j < CH.size(); j++) {
            cout << "<";
            cout << *itstring << ",";
            cout << *itchar_temp;
            cout << "> , ";
            ++itchar_temp;
        }
        set<string>::iterator itstring_temp = STR.begin();
        for (int j = 0; j < STR.size(); j++) {
            cout << "<";
            cout << *itstring << ",";
            cout << *itstring_temp;
            cout << "> , ";
            ++itstring_temp;
        }
        ++itstring;
    }
    cout << endl;
}
void SET::Identity_relationship() {  //恒等关系
    cout << "The identity relationship are :";
    set<int>::iterator itint = I.begin();
    for (int i = 0; i < I.size(); i++) {
        cout << "<";
        cout << *itint << ",";
        cout << *itint;
        cout << "> , ";
        ++itint;
    }
    set<char>::iterator itchar = CH.begin();
    for (int i = 0; i < CH.size(); i++) {
        cout << "<";
        cout << *itchar << ",";
        cout << *itchar;
        cout << "> , ";
        ++itchar;
    }
    set<string>::iterator itstring = STR.begin();
    for (int i = 0; i < STR.size(); i++) {
        cout << "<";
        cout << *itstring << ",";
        cout << *itstring;
        cout << "> , ";
        ++itstring;
    }
    cout << endl;
}
void SET::LA() {  //小于或等于关系
    cout << "The LA is :";
    set<int>::iterator itint = I.begin();
    for (int i = 0; i < I.size(); i++) {
        set<int>::iterator itint_temp = itint;
        for (int j = i; j < I.size(); j++) {
            cout << "<";
            cout << *itint << ",";
            cout << *itint_temp;
            cout << "> , ";
            ++itint_temp;
        }
        ++itint;
    }
    set<char>::iterator itchar = CH.begin();
    for (int i = 0; i < CH.size(); i++) {
        set<char>::iterator itchar_temp = itchar;
        for (int j = i; j < CH.size(); j++) {
            cout << "<";
            cout << *itchar << ",";
            cout << *itchar_temp;
            cout << "> , ";
            ++itchar_temp;
        }
        ++itchar;
    }
    set<string>::iterator itstring = STR.begin();
    for (int i = 0; i < STR.size(); i++) {
        set<string>::iterator itstring_temp = itstring;
        for (int j = i; j < STR.size(); j++) {
            cout << "<";
            cout << *itstring << ",";
            cout << *itstring_temp;
            cout << "> , ";
            ++itstring_temp;
        }
        ++itstring;
    }
    cout << endl;
}
void SET::fldR() {  //域
    SET Temp_fldR;
    Temp_fldR = ranR() & domR();

    cout << "The fldR is :{";
    set<int>::iterator itint = Temp_fldR.I.begin();
    for (int i = 0; i < Temp_fldR.I.size(); i++) {
        cout << *itint << ",";
        ++itint;
    }
    set<char>::iterator itchar = Temp_fldR.CH.begin();
    for (int i = 0; i < Temp_fldR.CH.size(); i++) {
        cout << *itchar << ",";
        ++itchar;
    }
    cout << "}" << endl;
}
SET SET::domR() {  //定义域
    SET Temp;
    cout << "The domR is :{";
    for (int i = 0; i < OP.size(); i++) {
        if (OP[i].PI[0] != -1) Temp.I.insert(OP[i].PI[0]);

        if (OP[i].PCH[0] != '\0') Temp.CH.insert(OP[i].PI[0]);
    }
    set<int>::iterator itint = Temp.I.begin();
    for (int i = 0; i < Temp.I.size(); i++) {
        cout << *itint << ",";
        ++itint;
    }
    set<char>::iterator itchar = Temp.CH.begin();
    for (int i = 0; i < Temp.CH.size(); i++) {
        cout << *itchar << ",";
        ++itchar;
    }
    cout << "} " << endl;
    return Temp;
}
SET SET::ranR() {  //值域
    SET Temp;
    cout << "The ranR is :{";
    for (int i = 0; i < OP.size(); i++) {
        if (OP[i].PI[0] != -1) Temp.I.insert(OP[i].PI[1]);

        if (OP[i].PCH[0] != '\0') Temp.CH.insert(OP[i].PI[1]);
    }
    set<int>::iterator itint = Temp.I.begin();
    for (int i = 0; i < Temp.I.size(); i++) {
        cout << *itint << ",";
        ++itint;
    }
    set<char>::iterator itchar = Temp.CH.begin();
    for (int i = 0; i < Temp.CH.size(); i++) {
        cout << *itchar << ",";
        ++itchar;
    }
    cout << "} " << endl;
    return Temp;
}
void SET::inverse() {  //逆关系
    cout << "The inverse relationship are: ";
    vector<order_pair> OP_temp;
    order_pair op_temp;
    op_temp = {-1, -1, '\0', '\0', "", ""};
    for (int i = 0; i < OP.size(); i++) {
        for (int j = 0; j < 2; j++) {
            op_temp.PI[1 - j] = OP[i].PI[j];
            op_temp.PCH[1 - j] = OP[i].PCH[j];
        }
        op_temp.PSTR0 = OP[i].PSTR1;
        op_temp.PSTR1 = OP[i].PSTR0;
        OP_temp.push_back(op_temp);
    }
    for (int i = 0; i < OP.size(); i++) {
        cout << "<";
        for (int j = 0; j < 2; j++) {
            if (OP_temp[i].PI[j] != -1) {
                cout << OP_temp[i].PI[j];
            }
            if (OP_temp[i].PCH[j] != '\0') {
                cout << OP_temp[i].PCH[j];
            }
            if (OP_temp[i].PSTR0 != "" && j != 1) {
                cout << OP_temp[i].PSTR0;
            }
            if (OP_temp[i].PSTR1 != "" && j != 0) {
                cout << OP_temp[i].PSTR1;
            }
            if (j != 1) cout << ",";
        }
        cout << "> ";
    }
}
void SET::judgement(string str) {
    int len = str.length();
    string temp;
    //将输入行分类别存入各容器中
    for (int i = 0; i < len; i++) {
        //  判断是序偶 存入vector的结构体中
        if (str[i] == '<') {
            string temp_str;
            while (str[i] != '>') {
                temp_str += str[i++];
            }
            temp_str += str[i++];
            judgement_OP(temp_str);
        }
        //判断是数字 存入I中
        else if (str[i] >= '0' && str[i] <= '9' &&
                 (str[i + 1] == ' ' || str[i + 1] == '\0')) {
            push_I(str[i]);
            // cout << "Str " << i <<"为：" << (int)str[i] << endl;
        }
        //判断是字符串 存入STR中
        else if (str[i] != ' ' && str[i + 1] != ' ') {
            while (str[i] != ' ') {
                temp += str[i];
                i++;
            }
            push_STR(temp);
            temp = "";
        }
        // 判断是其他字符 存入CH中
        else if ((str[i] >= 'a' && str[i] <= 'z') ||
                 (str[i] >= 'A' && str[i] <= 'Z') && str[i] != ' ' &&
                     (str[i + 1] == ' ' || str[i + 1] == '\0'))
            push_CH(str[i]);
        // cout << "Error:" << str[i] << " Illegal character"<< endl;
    }
}
void SET::judgement_OP(string str_OP) {
    int len = str_OP.length();
    string temp;
    int cnt = 0;
    //将输入行分类别存入序偶容器中
    order_pair op_temp;
    op_temp = {-1, -1, '\0', '\0', "", ""};
    for (int i = 0; i < len; i++) {
        //判断是, 则序偶前半部分结束储存 开始后半部分序偶的储存
        if (str_OP[i] == ',' || str_OP[i] == '<') i++;
        if (cnt == 2) {
            break;
        }
        //判断是数字 存入OPI中
        if (str_OP[i] >= '0' && str_OP[i] <= '9' &&
            (str_OP[i + 1] == ',' || str_OP[i + 1] == '>')) {
            // cout << "cnt "<< "is: " << cnt << endl;
            op_temp.PI[cnt] = ((int)str_OP[i] - 48);
            // cout << "op_temp.PI[cnt]=" << op_temp.PI[cnt] << endl;
            // cout << "op[cnt_OP].PI[cnt]=" << OP[cnt_OP].PI[cnt] << endl;
            cnt++;
        }
        //判断是字符串 存入OPSTR中
        else if (str_OP[i + 1] != ',' && str_OP[i + 1] != '>') {
            while (str_OP[i] != ',' && str_OP[i] != '>') {
                temp += str_OP[i];
                i++;
            }
            if (cnt == 0)
                op_temp.PSTR0 = temp;
            else
                op_temp.PSTR1 = temp;
            cnt++;
            temp = "";
        }
        // 判断是其他字母字符 存入OPCH中
        else if ((str_OP[i] >= 'a' && str_OP[i] <= 'z') ||
                 (str_OP[i] >= 'A' && str_OP[i] <= 'Z') &&
                     (str_OP[i + 1] == ',' || str_OP[i + 1] == '>')) {
            op_temp.PCH[cnt] = str_OP[i];
            cnt++;
        }
        // cout << "Error:" << str_OP[i] << " Illegal character"<< endl;
    }
    cnt_OP++;
    OP.push_back(op_temp);
}
inline void SET::push(int IN) { I.insert(IN); };
inline void SET::push(char ch) { CH.insert(ch); };
inline void SET::push(SET Set) { SETS.insert(Set); };
inline void SET::push(string str) { STR.insert(str); };
inline void SET::push_CH(char CHAR) { CH.insert(CHAR); }
inline void SET::push_I(char IN) { I.insert((int)IN - 48); }
inline void SET::push_STR(string STRING) { STR.insert(STRING); }
inline size_t SET::size() const { return I.size() + CH.size() + STR.size(); }
inline void SET::judgement_domR(int x) {}
inline bool SET::operator<(const SET& S) const {
    return SETHash() < S.SETHash();
}
inline void SET::show(int x, int y) {  //输出所有暂存序偶
    if (OP[x].PI[y] != -1) {
        cout << OP[x].PI[y];
    }
    if (OP[x].PCH[y] != '\0') {
        cout << OP[x].PCH[y];
    }
    if (OP[x].PSTR0 != "" && y != 1) {
        cout << OP[x].PSTR0;
    }
    if (OP[x].PSTR1 != "" && y != 0) {
        cout << OP[x].PSTR1;
    }
}
void SET::display() {
    set<int>::iterator itint = I.begin();
    for (int i = 0; i < I.size(); i++) {
        cout << *itint << " " << endl;
        itint++;
    }
    set<string>::iterator itstr = STR.begin();
    for (int i = 0; i < STR.size(); i++) {
        cout << *itstr << " " << endl;
        itstr++;
    }
    set<char>::iterator itchar = CH.begin();
    for (int i = 0; i < CH.size(); i++) {
        cout << *itchar << " " << endl;
        itchar++;
    }
    for (int i = 0; i < OP.size(); i++) {
        cout << "<";
        for (int j = 0; j < 2; j++) {
            show(i, j);
            if (j != 1) cout << ",";
        }
        cout << "> ";
    }
}
void SET::display_Relationship_matrix() {  //关系矩阵输出
    set<int>::iterator itint = I.begin();
    int cnt = 0;
    for (int i = 0; i < I.size(); i++) {
        cout << "|";
        set<int>::iterator itint_j = I.begin();
        for (int j = 0; j < I.size(); j++) {
            if (OP[cnt].PI[0] == *itint && OP[cnt].PI[1] == *itint_j)
            {
                cout << "1 ";
                if (cnt < cnt_OP - 1)
                    cnt++;
            }
            else
                cout << "0 ";
            ++itint_j;
        }
        ++itint;
        cout << "|" << endl;
    }
}
SET SET::operator*(const SET& t) {  //交集
    SET Temp;
    for (int i : I)
        if (t.I.find(i) != t.I.end()) Temp.push(i);

    for (char ch : CH)
        if (t.CH.find(ch) != t.CH.end()) Temp.push(ch);

    for (string str : STR)
        if (t.STR.find(str) != t.STR.end()) Temp.push(str);

    return Temp;
}
SET SET::operator&(const SET& t) {  //并集
    SET Temp = t;
    Temp.I.insert(I.begin(), I.end());
    Temp.CH.insert(CH.begin(), CH.end());
    Temp.STR.insert(STR.begin(), STR.end());
    return Temp;
}
SET SET::operator-(const SET& t) {  //差集
    SET Temp;
    for (int i : I)
        if (t.I.find(i) == t.I.end()) Temp.push(i);

    for (char ch : CH)
        if (t.CH.find(ch) == t.CH.end()) Temp.push(ch);

    for (string str : STR)
        if (t.STR.find(str) == t.STR.end()) Temp.push(str);
    return Temp;
}
SET SET::Symmetrical_difference(const SET& S1, const SET& S2) {  //对称差
    SET Temp;
    for (int i : S1.I)
        if (S2.I.find(i) == S2.I.end()) Temp.push(i);

    for (char ch : S1.CH)
        if (S2.CH.find(ch) == S2.CH.end()) Temp.push(ch);

    for (string str : S1.STR)
        if (S2.STR.find(str) == S2.STR.end()) Temp.push(str);
    for (int i : S2.I)
        if (S1.I.find(i) == S1.I.end()) Temp.push(i);

    for (char ch : S2.CH)
        if (S1.CH.find(ch) == S1.CH.end()) Temp.push(ch);

    for (string str : S2.STR)
        if (S1.STR.find(str) == S1.STR.end()) Temp.push(str);
    return Temp;
}
void SET::power(int i, SET T, SET* Res) {  //幂集
    if (i == size()) {
        Res->push(T);
        return;
    } else {
        power(i + 1, T, Res);
        int ii = i;
        if (ii < I.size()) {
            set<int>::iterator isi = I.begin();
            for (int I = 0; I < ii; I++) isi++;
            T.push(*isi);
        } else {
            ii -= I.size();
            if (ii < CH.size()) {
                set<char>::iterator chsi = CH.begin();
                for (int I = 0; I < ii; I++) chsi++;
                T.push(*chsi);
            } else {
                ii -= CH.size();
                if (ii < STR.size()) {
                    set<string>::iterator strsi = STR.begin();
                    for (int I = 0; I < ii; I++) strsi++;
                    T.push(*strsi);
                }
            }
        }
        power(i + 1, T, Res);
    }
}
size_t SET::SETHash() const {
    size_t s = size() * 100000;
    set<int>::iterator isi = I.begin();
    set<char>::iterator chsi = CH.begin();
    set<string>::iterator strsi = STR.begin();
    for (int i = 1; i <= I.size(); i++) {
        s += *isi * i * 100;
        isi++;
    }
    for (int i = 1; i <= CH.size(); i++) {
        s += *chsi * i * 1000;
        chsi++;
    }
    for (int i = 1; i <= STR.size(); i++) {
        s += (strsi->length() + strsi->at(0)) * i * 10000;
        isi++;
    }
    return s;
}
ostream& operator<<(ostream& os, SET& t) {
    os << '{';
    for (int i : t.I) os << i << ',';

    for (char ch : t.CH) os << '\'' << ch << '\'' << ',';

    for (string str : t.STR) os << '"' << str << '"' << ',';

    cout << '}';
    return os;
}
inline SET SET::power() {
    SET RES;
    power(0, SET(), &RES);
    return RES;
}

int main() {
    SET SET1;
    //SET SET2;
    // in2 >> SET2.str_in;
    SET1.setup();
    SET1.display_Relationship_matrix();
    //SET2.setup();

    // if (SET1.judgement_binary_relation())
    //     cout << "SET1是二元关系" << endl;
    // else
    //     cout << "SET1不是二元关系" << endl;
    // SET1.Cartesian_product(SET2);    //笛卡尔积
    // SET1.Global_relationship();      //全域关系
    // SET1.Identity_relationship();    //恒等关系
    // SET1.LA();                       //小于或等于关系
    // SET1.fldR();                     //域
    // SET1.inverse();                  //逆关系

    return 0;
}
