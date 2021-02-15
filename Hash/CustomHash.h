#include <string>
#include <array>
using std::string;
using std::array;

// https://gist.github.com/jorendorff/b6afda0f5ae670b8ebb3

// for c++11, we can give init value to non-static member variables.
struct bucket{
    bool is_using = false;
    string key = "";
    string value = "";
}

class CustomHash{

    private:
        int hash_method{0};
        int MAX_TABLE{0};
        const unsigned int TABLE_SIZE{256};
        bucket HASH_TABLE[TABLE_SIZE]; // array<bucket, 256> HASH_TABLE{};

        // HASHING
        unsigned int str_to_int(const string & str);

        unsigned int division_method();
        unsigned int multiplication_method();
        unsigned int universal_hasing();


        // Collision
        void linear_probing(int _age, char* _name , double _height);
        void quadratic_probing();
        void double_hashing();

        // Extends
        void rehash();
        void extend();
        void check_and_extend();

    public:
        // CONSTRUCTOR
        CustomHash();

        // HASHING
        int hash(const string & key);

        // PUT
        CustomHash & put(const string & key, string & value);

        // GET
        string get(const string & key) const;

        // EDIT
        CustomHash & update();

        // remove
        CustomHash & remove(const string * key);
        CustomHash & remove(const string * key, const string * value);

        void clear();


        int size();
        
        void keys();
        void values();


};