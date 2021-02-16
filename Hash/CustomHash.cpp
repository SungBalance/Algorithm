#include <string>
#include <vector>
#include <iostream>
#include "CustomHash.h"

using std::string;
using std::vector;
using namespace std;

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

// HASHING:: Methods
unsigned int CustomHash::division_method(const unsigned int & key_int, const unsigned int & size){
    return key_int % size;
};

unsigned int CustomHash::multiplication_method(const unsigned int & key_int, const unsigned int & size){
    // Knuth, "Sorting and Searching", v. 3 of "The Art of Computer Programming")
    return 0; // int( size * ( (key_int * this->CONST_MULTIPLICATION_METHOD) % 1 ) );
};

unsigned int CustomHash::universal_hasing(const unsigned int & key_int, const unsigned int & size){
    //
    return 0;
};

unsigned int CustomHash::hash(const string & key, const unsigned int size){
    unsigned int hash_size{0};

    if(size == 0){
        hash_size = this->TABLE_SIZE;
    } else {
        hash_size = size;
    }

    unsigned int hash_value = (this->*HasingPointer)(str_to_int(key), hash_size);
    return hash_value;
};



// Collision:: Linear_probing
unsigned int CustomHash::linear_probing_put(const string & key){
    unsigned int index_current = hash(key);

    for(int i=0 ; i<this->TABLE_SIZE ; i++){
        if(this->HASH_TABLE[index_current].is_using == false){ // get index for new one
            return index_current;
        } else if(this->HASH_TABLE[index_current].key == key) { // get index for update
            return index_current;
        }

        index_current += 1;
        index_current %= this->TABLE_SIZE;
    };
    throw "테이블이 꽉 찼습니다.";
    return 0;
};

unsigned int CustomHash::linear_probing_get(const string & key){
    unsigned int index_current = hash(key);

    for(int i=0 ; i<this->TABLE_SIZE ; i++){   

        if(this->HASH_TABLE[index_current].is_using == true && this->HASH_TABLE[index_current].key == key){
            return index_current;
        }

        index_current += 1;
        index_current %= this->TABLE_SIZE;
    }
    throw "키 값을 찾을 수 없습니다.";
    return 0;
};

unsigned int CustomHash::linear_probing_remove(const string & key){
    unsigned int index_current = hash(key);

    for(int i=0 ; i<this->TABLE_SIZE ; i++){

        if(this->HASH_TABLE[index_current].key == key){
            return index_current;
        }

        index_current += 1;
        index_current %= this->TABLE_SIZE;
    }
    throw "값을 찾을 수 없습니다.";
    return 0;
};


// Collision:: Quadratic_probing
unsigned int CustomHash::quadratic_probing_put(const string & key){
    unsigned int index_current = hash(key);
    unsigned int step = 0;

    for(int i=0 ; i<this->TABLE_SIZE ; i++){

        if (this->HASH_TABLE[index_current].is_using == false){ // get index for new one
            return index_current;
        } else if (this->HASH_TABLE[index_current].key == key){ // get index for update
            return index_current;
        }

        step += 1;
        index_current += step^2;
        index_current %= this->TABLE_SIZE;
    }
    throw "테이블이 꽉 찼습니다.";
    return 0;
};

unsigned int CustomHash::quadratic_probing_get(const string & key){
    unsigned int index_current = hash(key);
    unsigned int step = 0;

    for(int i=0 ; i<this->TABLE_SIZE ; i++){
        
        if(this->HASH_TABLE[index_current].is_using == true && this->HASH_TABLE[index_current].key == key){
            return index_current;
        }
        
        step += 1;
        index_current += step^2;
        index_current %= this->TABLE_SIZE;
    }

    throw "키 값을 찾을 수 없습니다.";
    return 0;
};

unsigned int CustomHash::quadratic_probing_remove(const string & key){
    unsigned int index_current = hash(key);
    unsigned int step = 0;
    
    for(int i=0 ; i<this->TABLE_SIZE ; i++){
        
        if(this->HASH_TABLE[index_current].key == key){
            return index_current;
        }

        step += 1;
        index_current += step^2;
        index_current %= this->TABLE_SIZE;
    }
    throw "값을 찾을 수 없습니다.";
    return 0;
};

// Collision:: Double_hashing
unsigned int CustomHash::double_hashing_put(const string & key){
    unsigned int index_current = hash(key);
    unsigned int step = hash(key, this->TABLE_SIZE-1);

    for(int i=0 ; i<this->TABLE_SIZE ; i++){

        if (this->HASH_TABLE[index_current].is_using == false){ // get index for new one
            return index_current;
        } else if (this->HASH_TABLE[index_current].key == key){ // get index for update
            return index_current;
        }

        index_current += step^2;
        index_current %= this->TABLE_SIZE;
    }
    throw "테이블이 꽉 찼습니다.";
    return 0;
};

unsigned int CustomHash::double_hashing_get(const string & key){
    unsigned int index_current = hash(key);
    unsigned int step = hash(key, this->TABLE_SIZE-1);

    for(int i=0 ; i<this->TABLE_SIZE ; i++){
        if(this->HASH_TABLE[index_current].is_using == true && this->HASH_TABLE[index_current].key == key){
            return index_current;
        }

        index_current += step^2;
        index_current %= this->TABLE_SIZE;
    }
    throw "키 값을 찾을 수 없습니다.";
    return 0;
};

unsigned int CustomHash::double_hashing_remove(const string & key){
    unsigned int index_current = hash(key);
    unsigned int step = hash(key, this->TABLE_SIZE-1);
    
    for(int i=0 ; i<this->TABLE_SIZE ; i++){        
        if(this->HASH_TABLE[index_current].key == key){
            return index_current;
        }

        index_current += step^2;
        index_current %= this->TABLE_SIZE;
    }
    throw "값을 찾을 수 없습니다.";
    return 0;
};

// Extends
void CustomHash::extend(bool print_option){
    unsigned int TABLE_SIZE_OLD = this->TABLE_SIZE;
    unsigned int VALUE_COUNT_OLD = this->VALUE_COUNT;
    bucket * HASH_TABLE_OLD = this->HASH_TABLE;

    this->TABLE_SIZE *= 2;
    this->VALUE_COUNT = 0;
    this->HASH_TABLE = new bucket[TABLE_SIZE];
    
    if(print_option){
        cout << "REHASH:: from " << TABLE_SIZE_OLD << " to " << this->TABLE_SIZE << endl;
    }
    
    for(signed int i=0 ; i<TABLE_SIZE_OLD ; i++){
        if(HASH_TABLE_OLD[i].is_using){
            this->put(HASH_TABLE_OLD[i].key, HASH_TABLE_OLD[i].value);
        }
    };

    if(VALUE_COUNT_OLD != this->VALUE_COUNT){
        this->TABLE_SIZE = TABLE_SIZE_OLD;
        this->VALUE_COUNT = VALUE_COUNT_OLD;
        this->HASH_TABLE = HASH_TABLE_OLD;

        throw "FAIL!!::EXTEND";
    }

    delete[] HASH_TABLE_OLD;
};

void CustomHash::check_and_extend(bool print_option){
    if (int(100*this->VALUE_COUNT/this->TABLE_SIZE) >= this->LIMIT_PERCENT){
        // this->extend();
        
        try{
            this->extend(print_option);
        } catch (string expn){
            cout << "ERROR::EXTEND:: " << expn << endl;
        }
    }
};


/*
##
## PUBLIC FUNCTIONS
##
*/


// Constructors
CustomHash::CustomHash( const int Hashing, const int Collision){
    // initialize table
    this->HASH_TABLE = new bucket[this->TABLE_SIZE];

    switch(Hashing){
        case 1: // for multiplication method, we take power of 2 as table size
            break;
        
        case 2:
            break;

        default: // for division method, we take prime number as table size
            this->HasingPointer = &CustomHash::division_method;
            break;
    }

    switch(Collision){

        case 1: // QUADRATIC
            this->PutPointer = &CustomHash::quadratic_probing_put;
            this->GetPointer = &CustomHash::quadratic_probing_get;
            this->RemovePointer = &CustomHash::quadratic_probing_remove;
            break;

        case 2: // DOUBLE HASHING
            this->PutPointer = &CustomHash::double_hashing_put;
            this->GetPointer = &CustomHash::double_hashing_get;
            this->RemovePointer = &CustomHash::double_hashing_remove;
            break;

        default: // LINEAR
            this->PutPointer = &CustomHash::linear_probing_put;
            this->GetPointer = &CustomHash::linear_probing_get;
            this->RemovePointer = &CustomHash::linear_probing_remove;
            break;        
    }
        
};

CustomHash::~CustomHash(){
    delete[] this->HASH_TABLE;
}


// PUT
CustomHash & CustomHash::put(const string key, string value, bool extend_print){
    try{
        unsigned int index = (this->*PutPointer)(key); // get index to put data
        
        if(HASH_TABLE[index].key != key){
            this->VALUE_COUNT += 1;
        }    
        
        HASH_TABLE[index].is_using = true;
        HASH_TABLE[index].key = key;
        HASH_TABLE[index].value = value;

        

    } catch(string expn) {
        cout << "ERROR::put:: " << expn << endl;
    }
    
    check_and_extend(extend_print);
    return * this;
};

CustomHash & CustomHash::put(const int key, int value, bool extend_print){
    string key_string = to_string(key);
    string value_string = to_string(value);
    this->put(key_string, value_string, extend_print);
};


CustomHash & CustomHash::put(const int key, string value, bool extend_print){
    string key_string = to_string(key);
    this->put(key_string, value, extend_print);
};

// GET
string CustomHash::get(const string key){
    try{
        unsigned int index = (this->*GetPointer)(key); // get index to get data
        return this->HASH_TABLE[index].value;
    }
    catch(string expn){
        cout << "ERROR::GET:: " << expn << endl;
    }
};

string CustomHash::get(const int key){
    string key_string = to_string(key);
    this->get(key_string);
};

// REMOVE
CustomHash & CustomHash::remove(const string key){
    unsigned int index = (this->*RemovePointer)(key); // get index to remove data

    this->HASH_TABLE[index].is_using = false; // this means remove
    this->VALUE_COUNT -= 1;

    return * this;
};

CustomHash & CustomHash::remove(const string key, const string value){
    unsigned int index = (this->*RemovePointer)(key); // get index to remove data

    // check if values equal
    if(this->HASH_TABLE[index].value == value){
        this->HASH_TABLE[index].is_using = false;
        this->VALUE_COUNT -= 1;
    }
};

CustomHash & CustomHash::remove(const int key){
    string key_string = to_string(key);
    this->remove(key_string);
};

CustomHash & CustomHash::remove(const int key, const int value){
    string key_string = to_string(key);
    string value_string = to_string(value);
    this->remove(key_string, value_string);
};

CustomHash & CustomHash::remove(const int key, const string value){
    string key_string = to_string(key);
    this->remove(key_string, value);
};


// CLEAR
void CustomHash::clear(){
    delete[] this->HASH_TABLE;
    this->VALUE_COUNT = 0;
    this->TABLE_SIZE = 8;
    this->HASH_TABLE = new bucket[TABLE_SIZE];
};

// SHOW

unsigned int CustomHash::get_size(){
    return this->TABLE_SIZE;
};

unsigned int CustomHash::get_element_count(){
    return this->VALUE_COUNT;
};


vector<string> CustomHash::get_keys(){
    vector<string> key_list;

    for( unsigned int i=0 ; i<this->TABLE_SIZE ; i++){
        if(this->HASH_TABLE[i].is_using == true){
            key_list.push_back(this->HASH_TABLE[i].key);
        }
    };

    return key_list;
};

vector<string> CustomHash::get_values(){
    vector<string> value_list;

    for( unsigned int i=0 ; i<this->TABLE_SIZE ; i++){
        if(this->HASH_TABLE[i].is_using == true){
            value_list.push_back(this->HASH_TABLE[i].value);
        }
    };

    return value_list;
};

void CustomHash::print_list(){
    vector<bucket> value_list;

    for( unsigned int i=0 ; i<this->TABLE_SIZE ; i++){
        if(this->HASH_TABLE[i].is_using == true){
            cout << this->HASH_TABLE[i].key << ":" << this->HASH_TABLE[i].value << endl;
        }
    };   
};

void CustomHash::print_list_all(){
    vector<bucket> value_list;

    for( unsigned int i=0 ; i<this->TABLE_SIZE ; i++){
        cout << this->HASH_TABLE[i].is_using << ":" << this->HASH_TABLE[i].key << ":" << this->HASH_TABLE[i].value << endl;
    };   
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