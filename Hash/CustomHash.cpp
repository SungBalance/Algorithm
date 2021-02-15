#include <string>
#include "CustomHash.h"
using std::string;

/*
##
## PRIVATE FUNCTIONS
##
*/


// HASHING
unsigned int CustomHash::str_to_int(const string & str){
    unsigned int result = 0;
    for (size_t i = 0; i < str.length(); i++)
        result += str[i];
    return int(result);
};

unsigned int CustomHash::division_method(const string & str){

    return 0;
};

unsigned int CustomHash::multiplication_method(const string & str){

    return 0;
};

unsigned int CustomHash::universal_hasing(const string & str){

    return 0;
};

int CustomHash::hash(const string & key){
    unsigned int hash_value = this->str_to_int(key) % this->TABLE_SIZE;
    return hash_value;
};



// Collision:: Linear_probing
unsigned int CustomHash::linear_probing_put(const string & key){

    unsigned int index = this->hash(key);

    while(this->HASH_TABLE[index].value != NULL){

        // get index for new one
        if(this->HASH_TABLE[index].is_using==false)
            return index;
        
        // get index for update
        if(this->HASH_TABLE[index].key == key && this->HASH_TABLE[index].is_using==true)
            return index;

        index = index+1;
    
        index %= this->TABLE_SIZE; // warp around the TABLE
    }

    return NULL;
};

unsigned int CustomHash::linear_probing_get(const string & key){

    unsigned int index = this->hash(key);

    while(this->HASH_TABLE[index].value != NULL){
        if(this->HASH_TABLE[index].is_using==true == this->HASH_TABLE[index].key == key)
            return index;

        index = index+1;
    
        index %= this->TABLE_SIZE; // warp around the TABLE
    }

};

unsigned int CustomHash::linear_probing_remove(const string & key){

    unsigned int index = this->hash(key);

    while(this->HASH_TABLE[index].key != key){
        if(this->HASH_TABLE[index].key == key){
            return index;
        }

        index = index+1;
    
        index %= this->TABLE_SIZE; // warp around the TABLE
    }
};


// Collision:: Quadratic_probing
unsigned int CustomHash::quadratic_probing_put(const string & key){

};

unsigned int CustomHash::quadratic_probing_get(const string & key){

};

unsigned int CustomHash::quadratic_probing_remove(const string & key){

};

// Collision:: Double_hashing
unsigned int CustomHash::double_hashing_put(const string & key){

};

unsigned int CustomHash::double_hashing_get(const string & key){

};
unsigned int CustomHash::double_hashing_remove(const string & key){

};

// Extends
void CustomHash::rehash(){
    
};

void CustomHash::extend(){

};

void CustomHash::check_and_extend(){
    
};


/*
##
## PUBLIC FUNCTIONS
##
*/


// Constructors
CustomHash::CustomHash(){
    //
};


// PUT
CustomHash & CustomHash::put(const string & key, string & value){
    unsigned int index = this->linear_probing_put(key); // get index to put data
    
    HASH_TABLE[index].is_using = true;
    HASH_TABLE[index].key = key;
    HASH_TABLE[index].value = value;

    return * this;
};

// GET
string CustomHash::get(const string & key){
    unsigned int index = this->linear_probing_put(key); // get index to get data
    
    return this->HASH_TABLE[index].value;
};

// REMOVE
CustomHash & CustomHash::remove(const string & key){
    unsigned int index = this->linear_probing_remove(key); // get index to remove data

    this->HASH_TABLE[index].is_using = false; // this means remove

    return * this;
};

CustomHash & CustomHash::remove(const string & key, const string & value){
    unsigned int index = this->linear_probing_remove(key); // get index to remove data

    // check if values equal
    if(this->HASH_TABLE[index].value == value){
        this->HASH_TABLE[index].is_using = false; // this means remove
    }

    return * this;
};

// CLEAR
void CustomHash::clear(){

};




/*
// member init
CustomHash::CustomHash(int numerator, int denominator=1): m_value1(value1), m_value2(value2), m_value3(value3){
    hash_method = 0;
};
*/


/*
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



public:
    Employee(int id, const string &name) : m_ID(id), m_Name(name){
        cout << "Employee " << m_Name << " created.\n" << endl;
        } // 중복 코드를 최소화하기 위해 생성자 위임을 사용
        
    Employee(const string& name) : Employee(0, name){

    }

*/