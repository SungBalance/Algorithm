#include <string>
#include <vector>

struct bucket{
    std::string key;
    std::string value;
}

class CustomHash{

    private:
        int hash_method{0};
        int MAX_TABLE{0};
        std::vector<int> KEY_TABLE{};
        std::vector<std::string> VALUE_TABLE{};

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
        int hash(const std::string * key);

        // PUT
        CustomHash & put(const std::string * key, std::string value);

        // GET
        std::string get(const std::string * key) const;

        // EDIT
        CustomHash & update();

        // remove
        CustomHash & remove(const std::string * key);
        CustomHash & remove(const std::string * key, const std::string * value);

        void clear();


        int size();
        
        void keys();
        void values();


};