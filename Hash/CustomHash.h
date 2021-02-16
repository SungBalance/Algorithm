#include <string>
#include <array>
#include <vector>
#include <functional>

using std::string;
using std::array;
using std::function;
using std::vector;

// https://gist.github.com/jorendorff/b6afda0f5ae670b8ebb3

// for c++11, we can give init value to non-static member variables.

struct bucket{
    bool is_using = false;
    bool deleted = false;
    string key = "";
    string value = "";
};

class CustomHash{

    private:
        // Knuth, "Sorting and Searching", v. 3 of "The Art of Computer Programming").
        const float CONST_MULTIPLICATION_METHOD{0.6180339887}; // (sqrt(5)-1)/2
        const int LIMIT_PERCENT{75};
        
        bucket * HASH_TABLE;
        unsigned int TABLE_SIZE{7};
        unsigned int LAST_PRIME{5};
        unsigned int VALUE_COUNT{0};
        unsigned int CONFLICT_COUNT{0};
        unsigned int REHASH_COUNT{0};
        // bucket HASH_TABLE[TABLE_SIZE]; // array<bucket, 256> HASH_TABLE{};

        vector<unsigned int> INDEX_LIST;

        // FUNCTION POINTERS
        unsigned int (CustomHash::*HasingPointer)(const unsigned int &, const unsigned int &);
        unsigned int (CustomHash::*PutPointer)(const string &);
        unsigned int (CustomHash::*GetPointer)(const string &);
        unsigned int (CustomHash::*RemovePointer)(const string &);

        // HASHING
        unsigned int str_to_int(const string & str);
        unsigned int division_method(const unsigned int & key_int, const unsigned int & size);
        unsigned int multiplication_method(const unsigned int & key_int, const unsigned int & size);
        unsigned int universal_hasing(const unsigned int & key_int, const unsigned int & size);
        unsigned int hash(const string & key, const unsigned int size = 0);


        // get index to work per Collision methods
        unsigned int linear_probing_put(const string & key);
        unsigned int linear_probing_get(const string & key);
        unsigned int linear_probing_remove(const string & key);

        unsigned int quadratic_probing_put(const string & key);
        unsigned int quadratic_probing_get(const string & key);
        unsigned int quadratic_probing_remove(const string & key);

        unsigned int double_hashing_put(const string & key);
        unsigned int double_hashing_get(const string & key);
        unsigned int double_hashing_remove(const string & key);

        // Extends
        void extend(bool print_option = false);
        void check_and_extend(bool print_option = false);

    public:
        // CONSTRUCTOR
        CustomHash(const int Hashing = 0, const int Collision = 0);
        ~CustomHash();

        // PUT
        CustomHash & put(const string key, const string value, bool extend_print = false);
        CustomHash & put(const string key, const int value, bool extend_print = false);
        CustomHash & put(const int key, const int value, bool extend_print = false);
        CustomHash & put(const int key, const string value, bool extend_print = false);

        // GET
        string get(const string key);
        string get(const int key);

        // REMOVE
        CustomHash & remove(const string key);
        CustomHash & remove(const string key, const string value);
        CustomHash & remove(const int key);
        CustomHash & remove(const int key, const int value);
        CustomHash & remove(const int key, const string value);

        void clear();

        unsigned int get_size();
        unsigned int get_element_count();
        unsigned int get_conflict_count();
        unsigned int get_rehash_count();

        vector<string> get_keys();
        vector<string> get_values();
        
        bool contains_key(const string key);
        bool contains_key(const int key);
        bool contains_value(const string value);

        void print_list();
        void print_list_all();


};