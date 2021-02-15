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
    string key = NULL;
    string value = NULL;
};

class CustomHash{

    private:
        // Knuth, "Sorting and Searching", v. 3 of "The Art of Computer Programming").
        const float CONST_MULTIPLICATION_METHOD{0.6180339887}; // (sqrt(5)-1)/2
        const int limit_percent{75};

        unsigned int TABLE_SIZE{8};
        bucket HASH_TABLE[TABLE_SIZE]; // array<bucket, 256> HASH_TABLE{};

        vector<unsigned int> INDEX_LIST;

        // FUNCTION POINTERS
        unsigned int (CustomHash::*HasingPointer)(const unsigned int & key_int, const unsigned int & size);
        unsigned int (CustomHash::*PutPointer)(const string & key);
        unsigned int (CustomHash::*GetPointer)(const string & key);
        unsigned int (CustomHash::*RemovePointer)(const string & key);

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
        void rehash();
        void extend();
        void check_and_extend();

    public:
        // CONSTRUCTOR
        CustomHash(const int Hashing = 0, const int Collision = 0);

        // PUT
        CustomHash & put(const string & key, string & value);

        // GET
        string get(const string & key);

        // REMOVE
        CustomHash & remove(const string & key);
        CustomHash & remove(const string & key, const string & value);

        void clear();

        vector<string> & get_keys();
        vector<string> & get_values();

        void print_list();


};