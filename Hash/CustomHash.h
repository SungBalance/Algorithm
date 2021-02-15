#include <string>
#include <array>
using std::string;
using std::array;

// https://gist.github.com/jorendorff/b6afda0f5ae670b8ebb3

// for c++11, we can give init value to non-static member variables.

struct bucket{
    bool is_using = false;
    string key = NULL;
    string value = NULL;
};

class CustomHash{

    private:
        int hash_method{0};
        int MAX_TABLE{0};
        const unsigned int TABLE_SIZE{256};
        bucket HASH_TABLE[TABLE_SIZE]; // array<bucket, 256> HASH_TABLE{};

        // HASHING
        unsigned int str_to_int(const string & str);
        unsigned int division_method(const string & str);
        unsigned int multiplication_method(const string & str);
        unsigned int universal_hasing(const string & str);
        int hash(const string & key);


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
        CustomHash();

        

        // PUT
        CustomHash & put(const string & key, string & value);

        // GET
        string get(const string & key);

        // EDIT
        CustomHash & update();

        // REMOVE
        CustomHash & remove(const string & key);
        CustomHash & remove(const string & key, const string & value);

        void clear();


};