#include <string>
#include "CustomHash.h"
using std::string;


// PRIVATE FUNCTIONS

unsigned int CustomHash::str_to_int(const string& str){
    unsigned int result = 0;
    for (size_t i = 0; i < str.length(); i++)
        result += str[i];
    return int(result);
};



// PUBLIC FUNCTIONS

CustomHash::CustomHash(){
};



int CustomHash::hash(const string * key){
    return (int)&key % this->MAX_TABLE;
};


// PUT
CustomHash & CustomHash::put(const string * key, string value){
    int hash_value = this->hash(key);

    return *this;
};

// GET
string get(const string * key) {
    value = ;
    return value;
};




/*
// member init
CustomHash::CustomHash(int numerator, int denominator=1): m_value1(value1), m_value2(value2), m_value3(value3){
    hash_method = 0;
};
*/

void CustomHash::linear_probing(int _age, char* _name , double _height){
    this.age = _age;
    name = _name;
    height = _height;

};

void CustomHash::double_hashing(){
    cout << "나이 : " << age << endl;
    cout << "이름 : " << name << endl;
    cout << "키 : " << height << "  이었으면 좋겠다. ㅎ "<<endl << endl;

};

void check_and_extend();



/*

public:
    Employee(int id, const string &name) : m_ID(id), m_Name(name) {
        cout << "Employee " << m_Name << " created.\n" << endl;
        } // 중복 코드를 최소화하기 위해 생성자 위임을 사용
        
    Employee(const string& name) : Employee(0, name) {

    }

*/