#include <string>
#include <vector>
#include <iostream>
#include "CustomHash.h"

using std::string;
using std::vector;
using namespace std;

bool is_prime(unsigned int n) {
    if (n == 2 || n == 3){
        return true;
    } else if (n == 1 || n % 2 == 0){
        return false;
    }

    for (int i = 3; i * i <= n; i += 2){
        if (n % i == 0){
            return false;
        }
    }
    return true;
}

unsigned int next_prime(unsigned int n) {
    if (n <= 0){
        n == 3;
    } else if (n % 2 == 0){
        n++;
    } else {
        n += 2;
    }
    
    while(!is_prime(n)){
        n += 2;
    }
    return n;
}

unsigned int prior_prime(unsigned int n) {
    if (n <= 0){
        n == 3;
    } else if (n % 2 == 0){
        n--;
    } else {
        n -= 2;
    }
    
    while(!is_prime(n)){
        n -= 2;
    }
    return n;
}


/*
##
## PRIVATE FUNCTIONS
##
*/

// HASHING
unsigned int CustomHash::str_to_int(const string & str){
    try{
        return stoi(str);
    } catch(const std::invalid_argument & error){
        
    }

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
    // Knuth, "Sorting and Searching", v. 3 of "The Art of Cominserter Programming")
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
unsigned int CustomHash::linear_probing_insert(const string & key){
    unsigned int index_current = hash(key);

    for(int i=0 ; i<this->TABLE_SIZE ; i++){
        if(this->HASH_TABLE[index_current].is_using == false){ // get index for new one
            return index_current;
        } else if(this->HASH_TABLE[index_current].key == key) { // get index for update
            return index_current;
        }

        this->CONFLICT_COUNT += 1;
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
        if(this->HASH_TABLE[index_current].deleted == false && this->HASH_TABLE[index_current].is_using == false){
            throw "값을 찾을 수 없습니다.";
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
        if(this->HASH_TABLE[index_current].deleted == false && this->HASH_TABLE[index_current].is_using == false){
            throw "값을 찾을 수 없습니다.";
        }

        index_current += 1;
        index_current %= this->TABLE_SIZE;
    }
    throw "값을 찾을 수 없습니다.";
    return 0;
};


// Collision:: Quadratic_probing
unsigned int CustomHash::quadratic_probing_insert(const string & key){
    unsigned int index_current = hash(key);
    unsigned int step = 0;

    while(1){ // 빈자리 rehashing
        
        if(this->HASH_TABLE[index_current].is_using == false){ // get index for new one
            return index_current;
        } else if(this->HASH_TABLE[index_current].key == key){ // get index for update
            return index_current;
        }

        this->CONFLICT_COUNT += 1;
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

    while(1){
        
        if(this->HASH_TABLE[index_current].is_using && this->HASH_TABLE[index_current].key == key){
            return index_current;
        }
        if(this->HASH_TABLE[index_current].deleted == false && this->HASH_TABLE[index_current].is_using == false){
            throw "값을 찾을 수 없습니다.";
        }
        
        step += 1;
        index_current += step^2;
        index_current %= this->TABLE_SIZE;
    }

    throw "값을 찾을 수 없습니다.";
    return 0;
};

unsigned int CustomHash::quadratic_probing_remove(const string & key){
    unsigned int index_current = hash(key);
    unsigned int step = 0;
    
    while(1){
        
        if(this->HASH_TABLE[index_current].key == key){
            return index_current;
        }
        if(this->HASH_TABLE[index_current].deleted == false && this->HASH_TABLE[index_current].is_using == false){
            throw "값을 찾을 수 없습니다.";
        }

        step += 1;
        index_current += step^2;
        index_current %= this->TABLE_SIZE;
    }
    throw "값을 찾을 수 없습니다.";
    return 0;
};

// Collision:: Double_hashing
unsigned int CustomHash::double_hashing_insert(const string & key){
    unsigned int index_current = hash(key);
    unsigned int prime = this->LAST_PRIME;
    unsigned int step = prime - (str_to_int(key) % prime);

    for(int i=0 ; i<this->TABLE_SIZE ; i++){

        if (this->HASH_TABLE[index_current].is_using == false){ // get index for new one
            return index_current;
        } else if (this->HASH_TABLE[index_current].key == key){ // get index for update
            return index_current;
        }

        this->CONFLICT_COUNT += 1;
        index_current += step;
        index_current %= this->TABLE_SIZE;
    }
    throw "테이블이 꽉 찼습니다.";
    return 0;
};

unsigned int CustomHash::double_hashing_get(const string & key){
    unsigned int index_current = hash(key);
    unsigned int prime = this->LAST_PRIME;
    unsigned int step = prime - (str_to_int(key) % prime);

    while(1){
        if(this->HASH_TABLE[index_current].is_using == true && this->HASH_TABLE[index_current].key == key){
            return index_current;
        }
        if(this->HASH_TABLE[index_current].deleted == false && this->HASH_TABLE[index_current].is_using == false){
            throw "값을 찾을 수 없습니다.";
        }

        index_current += step;
        index_current %= this->TABLE_SIZE;
    }

    throw "값을 찾을 수 없습니다.";
    return 0;
};

unsigned int CustomHash::double_hashing_remove(const string & key){
    unsigned int index_current = hash(key);
    unsigned int prime = this->LAST_PRIME;
    unsigned int step = prime - (str_to_int(key) % prime);
    
    while(1){
        if(this->HASH_TABLE[index_current].key == key){
            return index_current;
        }
        if(this->HASH_TABLE[index_current].deleted == false && this->HASH_TABLE[index_current].is_using == false){
            throw "값을 찾을 수 없습니다.";
        }

        index_current += step;
        index_current %= this->TABLE_SIZE;
    }
    throw "값을 찾을 수 없습니다.";
    return 0;
};

// Rehash
void CustomHash::rehash(bool print_option){
    this->LAST_PRIME = this->TABLE_SIZE;
    unsigned int VALUE_COUNT_OLD = this->VALUE_COUNT;
    bucket * HASH_TABLE_OLD = this->HASH_TABLE;
    
    this->TABLE_SIZE = prior_prime(2*this->TABLE_SIZE);
    this->VALUE_COUNT = 0;
    this->CONFLICT_COUNT = 0;
    this->HASH_TABLE = new bucket[TABLE_SIZE];
    
    if(print_option){
        cout << "REHASH:: from " << this->LAST_PRIME << " to " << this->TABLE_SIZE << endl;
    }
    
    for(signed int i=0 ; i<this->LAST_PRIME ; i++){
        if(HASH_TABLE_OLD[i].is_using){
            this->insert(HASH_TABLE_OLD[i].key, HASH_TABLE_OLD[i].value);
        }
    };
    
    if(VALUE_COUNT_OLD != this->VALUE_COUNT){
        this->TABLE_SIZE = this->LAST_PRIME;
        this->VALUE_COUNT = VALUE_COUNT_OLD;
        this->HASH_TABLE = HASH_TABLE_OLD;

        throw "FAIL!!::rehash";
    }

    delete[] HASH_TABLE_OLD;
};

void CustomHash::check_and_rehash(bool print_option){
    if (int(100*this->VALUE_COUNT/this->TABLE_SIZE) >= this->LIMIT_PERCENT){
        // this->rehash();
        
        try{
            this->REHASH_COUNT += 1;
            this->rehash(print_option);
        } catch (char const* error){
            cout << "ERROR::rehash:: " << error << endl;
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
    // this->TABLE_SIZE = 7;
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
            this->insertPointer = &CustomHash::quadratic_probing_insert;
            this->GetPointer = &CustomHash::quadratic_probing_get;
            this->RemovePointer = &CustomHash::quadratic_probing_remove;
            // cout << "QUADRATIC DONE" << endl;
            break;

        case 2: // DOUBLE HASHING
            this->insertPointer = &CustomHash::double_hashing_insert;
            this->GetPointer = &CustomHash::double_hashing_get;
            this->RemovePointer = &CustomHash::double_hashing_remove;
            // cout << "DOUBLE HASHING DONE" << endl;
            break;

        default: // LINEAR
            this->insertPointer = &CustomHash::linear_probing_insert;
            this->GetPointer = &CustomHash::linear_probing_get;
            this->RemovePointer = &CustomHash::linear_probing_remove;
            // cout << "LINEAR DONE" << endl;
            break;        
    }
        
};

CustomHash::~CustomHash(){
    delete[] this->HASH_TABLE;
}


// insert
CustomHash & CustomHash::insert(const string key, string value, bool rehash_print){
    try{
        unsigned int index = (this->*insertPointer)(key); // get index to insert data
        
        if(HASH_TABLE[index].key != key){
            this->VALUE_COUNT += 1;
        }
        
        HASH_TABLE[index].is_using = true;
        HASH_TABLE[index].key = key;
        HASH_TABLE[index].value = value;

        check_and_rehash(rehash_print);

    } catch(char const* error) {
        cout << "ERROR::insert:: " << error << endl;
        throw "ERROR";
    }
    
    return * this;
};

CustomHash & CustomHash::insert(const string key, int value, bool rehash_print){
    string value_string = to_string(value);
    return this->insert(key, value_string, rehash_print);
};

CustomHash & CustomHash::insert(const int key, int value, bool rehash_print){
    string key_string = to_string(key);
    string value_string = to_string(value);
    return this->insert(key_string, value_string, rehash_print);
};


CustomHash & CustomHash::insert(const int key, string value, bool rehash_print){
    string key_string = to_string(key);
    return this->insert(key_string, value, rehash_print);
};

// GET
string CustomHash::get(const string key){
    try{
        unsigned int index = (this->*GetPointer)(key); // get index to get data
        return this->HASH_TABLE[index].value;
    }
    catch(char const* error){
        cout << "ERROR::GET:: " << error << endl;
    }
    return "";
};

string CustomHash::get(const int key){
    string key_string = to_string(key);
    return this->get(key_string);
};

// REMOVE
CustomHash & CustomHash::remove(const string key){
    try{
        unsigned int index = (this->*GetPointer)(key); // get index to remove data

        this->HASH_TABLE[index].is_using = false; // this means remove
        this->VALUE_COUNT -= 1;
    }
    catch(char const* error){
        cout << "ERROR::REMOVE:: " << error << endl;
    }

    return * this;
};

CustomHash & CustomHash::remove(const string key, const string value){
    try{
        unsigned int index = (this->*RemovePointer)(key); // get index to remove data

        // check if values equal
        if(this->HASH_TABLE[index].value == value){
            this->HASH_TABLE[index].is_using = false;
            this->VALUE_COUNT -= 1;
        }
    }
    catch(char const* error){
        cout << "ERROR::REMOVE:: " << error << endl;
    }

    return * this;
};

CustomHash & CustomHash::remove(const int key){
    string key_string = to_string(key);
    return this->remove(key_string);
};

CustomHash & CustomHash::remove(const int key, const int value){
    string key_string = to_string(key);
    string value_string = to_string(value);
    return this->remove(key_string, value_string);
};

CustomHash & CustomHash::remove(const int key, const string value){
    string key_string = to_string(key);
    return this->remove(key_string, value);
};


// CLEAR
void CustomHash::clear(){
    delete[] this->HASH_TABLE;
    this->TABLE_SIZE = 7;
    this->LAST_PRIME = 5;
    this->VALUE_COUNT = 0;
    this->CONFLICT_COUNT = 0;
    this->REHASH_COUNT = 0;
    
    this->HASH_TABLE = new bucket[TABLE_SIZE];
};

// SHOW

unsigned int CustomHash::get_size(){
    return this->TABLE_SIZE;
};

unsigned int CustomHash::get_element_count(){
    return this->VALUE_COUNT;
};

unsigned int CustomHash::get_conflict_count(){
    return this->CONFLICT_COUNT;
}

unsigned int CustomHash::get_rehash_count(){
    return this->REHASH_COUNT;
}

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

bool CustomHash::contains_key(const string key){
    try{
        unsigned int index = (this->*GetPointer)(key); 
        return true;
    }
    catch(char const* error){
        return false;
    }
    return false;
}

bool CustomHash::contains_key(const int key){
    try{
        unsigned int index = (this->*GetPointer)(to_string(key));
        return true;
    }
    catch(char const* error){
        return false;
    }
    return false;
}

bool CustomHash::contains_value(const string value){
    for( unsigned int i=0 ; i<this->TABLE_SIZE ; i++){
        if(this->HASH_TABLE[i].value == value){
            return true;
        }
    };
    return false;
}

bool CustomHash::is_empty(){
    if(this->VALUE_COUNT > 0){
        return true;
    }
    return false;
}

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