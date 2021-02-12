#include <string>
#include <vector>
using std::string;

struct bucket{
    bool is_using;
    string key;
    string value;
}

class CustomHash{

    private:
        int hash_method{0};
        int MAX_TABLE{0};
        std::vector<int> KEY_TABLE{};
        std::vector<string> VALUE_TABLE{};

        // HASHING
        int division_method();
        int multiplication_method();
        int universal_hasing();


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
        int hash(const string * key);

        // PUT
        CustomHash & put(const string * key, string value);

        // GET
        string get(const string * key) const;

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