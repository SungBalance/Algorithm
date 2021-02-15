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

// HASHING:: Methods
unsigned int CustomHash::division_method(const unsigned int & key_int, const unsigned int & size){
    return key_int % size;
};

unsigned int CustomHash::multiplication_method(const unsigned int & key_int, const unsigned int & size){
    // Knuth, "Sorting and Searching", v. 3 of "The Art of Computer Programming")
    return int( size * ( (key_int * this->CONST_MULTIPLICATION_METHOD) % 1 ) );
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
    unsigned int index = hash(key);
    unsigned int index_end = index;
    
    do {
        // get index for new one
        if(this->HASH_TABLE[index].is_using == false)
            return index;
        
        // get index for update
        if(this->HASH_TABLE[index].is_using == true && this->HASH_TABLE[index].key == key)
            return index;

        index = index + 1;
    
        index %= this->TABLE_SIZE; // warp around the TABLE
    } while(index != index_end);
    
};

unsigned int CustomHash::linear_probing_get(const string & key){
    unsigned int index = hash(key);
    unsigned int index_end = index;

    do {
        if(this->HASH_TABLE[index].is_using == true && this->HASH_TABLE[index].key == key){
            return index;
        }
        
        index = index + 1;
    
        index %= this->TABLE_SIZE; // warp around the TABLE
    } while(index != index_end);

};

unsigned int CustomHash::linear_probing_remove(const string & key){
    unsigned int hash_value = hash(key);

    unsigned int index = hash(key);
    unsigned int index_end = index;

    do {
        if(this->HASH_TABLE[index].key == key){
            return index;
        }
        
        index = index + 1;

        index %= this->TABLE_SIZE; // warp around the TABLE
    } while(index != index_end);
};


// Collision:: Quadratic_probing
unsigned int CustomHash::quadratic_probing_put(const string & key){
    unsigned int index_current = hash(key);
    unsigned int step = 0;

    while(step < this->TABLE_SIZE){

        index_current += step^2;
        index_current %= this->TABLE_SIZE;
        
        // get index for new one
        if(this->HASH_TABLE[index_current].is_using == false)
            return index_current;
        
        // get index for update
        if(this->HASH_TABLE[index_current].is_using == true && this->HASH_TABLE[index_current].key == key)
            return index_current;

        step += 1;
    }
};

unsigned int CustomHash::quadratic_probing_get(const string & key){
    unsigned int index_current = hash(key);
    unsigned int step = 0;

    while(step < this->TABLE_SIZE){

        index_current += step^2;
        index_current %= this->TABLE_SIZE;
        
        if(this->HASH_TABLE[index_current].is_using == true && this->HASH_TABLE[index_current].key == key){
            return index_current;
        }
        
        step += 1;
    }
};

unsigned int CustomHash::quadratic_probing_remove(const string & key){
    unsigned int index_current = hash(key);
    unsigned int step = 0;
    
    while(step < this->TABLE_SIZE){
        index_current += step^2;
        index_current %= this->TABLE_SIZE;
        
        if(this->HASH_TABLE[index_current].key == key){
            return index_current;
        }

        step += 1;
    }
};

// Collision:: Double_hashing
unsigned int CustomHash::double_hashing_put(const string & key){
    unsigned int index_current = hash(key);
    unsigned int step = hash(key, this->TABLE_SIZE+1);

    while(step < this->TABLE_SIZE){

        index_current += step;
        index_current %= this->TABLE_SIZE;
        
        // get index for new one
        if(this->HASH_TABLE[index_current].is_using == false)
            return index_current;
        
        // get index for update
        if(this->HASH_TABLE[index_current].is_using == true && this->HASH_TABLE[index_current].key == key){
            return index_current;
        }
    }
};

unsigned int CustomHash::double_hashing_get(const string & key){
    unsigned int index_current = hash(key);
    unsigned int step = hash(key, this->TABLE_SIZE+1);

    while(step < this->TABLE_SIZE){

        index_current += step^2;
        index_current %= this->TABLE_SIZE;
        
        if(this->HASH_TABLE[index_current].is_using == true && this->HASH_TABLE[index_current].key == key){
            return index_current;
        }
    }
};

unsigned int CustomHash::double_hashing_remove(const string & key){
    unsigned int index_current = hash(key);
    unsigned int step = hash(key, this->TABLE_SIZE+1);
    
    while(step < this->TABLE_SIZE){
        index_current += step^2;
        index_current %= this->TABLE_SIZE;
        
        if(this->HASH_TABLE[index_current].key == key){
            return index_current;
        }
    }
};

// Extends
void CustomHash::rehash(){
    
};

void CustomHash::extend(){

};

void CustomHash::check_and_extend(){
    if (condition){
        this->extend();
    }
};


/*
##
## PUBLIC FUNCTIONS
##
*/


// Constructors
CustomHash::CustomHash( const int Hashing = 0, const int Collision = 0 ){

    switch(Hashing){
        case 1: // for multiplication method, we take power of 2 as table size
            break;
        
        case 2:
            break;

        default: // for division method, we take prime number as table size
            this->HasingPointer = division_method;
            break;
    }

    switch(Collision){

        case 1: // QUADRATIC
            this->PutPointer = quadratic_probing_put;
            this->GetPointer = quadratic_probing_get;
            this->RemovePointer = quadratic_probing_remove;
            break;

        case 2: // DOUBLE HASHING
            this->PutPointer = double_hashing_put;
            this->GetPointer = double_hashing_get;
            this->RemovePointer = double_hashing_remove;
            break;

        default: // LINEAR
            this->PutPointer = linear_probing_put;
            this->GetPointer = linear_probing_get;
            this->RemovePointer = linear_probing_remove;
            break;        
    }
        
};


// PUT
CustomHash & CustomHash::put(const string & key, string & value){
    unsigned int index = (this->*PutPointer)(key); // get index to put data
    
    HASH_TABLE[index].is_using = true;
    HASH_TABLE[index].key = key;
    HASH_TABLE[index].value = value;

    check_and_extend();

    return * this;
};

// GET
string CustomHash::get(const string & key){
    unsigned int index = (this->*GetPointer)(key); // get index to get data
    
    return this->HASH_TABLE[index].value;
};

// REMOVE
CustomHash & CustomHash::remove(const string & key){
    unsigned int index = (this->*RemovePointer)(key); // get index to remove data

    this->HASH_TABLE[index].is_using = false; // this means remove

    return * this;
};

CustomHash & CustomHash::remove(const string & key, const string & value){
    unsigned int index = (this->*RemovePointer)(key); // get index to remove data

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