#include <iostream>
#include <cstdlib>
#include "CustomHash.h"

using namespace std;

string get_random_string(){
    string str;
    int len = 1; //rand() % 5;
    for (size_t i = 0; i < len; ++i) {
         int randomChar = rand()%(26+26+10);
         if (randomChar < 26)
             str[i] = 'a' + randomChar;
         else if (randomChar < 26+26)
             str[i] = 'A' + randomChar - 26;
         else
             str[i] = '0' + randomChar - 26 - 26;
     }
     return str;
}

void multi_puts(CustomHash * hashtable, unsigned int test_count){
    clock_t start, end;

    start = clock();
    for( unsigned int i=0 ; i < test_count ; i++){
        try{
            hashtable->put(get_random_string(), rand());
        } catch(char const* error) {
            cout << error << endl;
            break;
        }
    };
    end = clock();
    
    cout << "for " << test_count << " puts / time: " << ((float) end - start)/CLOCKS_PER_SEC << "s / conflict: " << hashtable->get_conflict_count()  << " / rehash:" << hashtable->get_rehash_count() << " / size:" << hashtable->get_size() << endl;
}

void test_one_hash(){
    cout << "-----------------------------------" << endl;
    
    int selectHash = -1;
    while(selectHash != 0 && selectHash != 1){
        cout << "HASH 종류를 선택하세요." << endl;
        cout << "0: DIVISION(default)  |  1: MULTIPLICATION" << endl;
        cin >> selectHash;
    }
    
    int selectProbe = -1;
    while(selectProbe != 0 && selectProbe != 1 && selectProbe != 2){
        cout << "\n" << endl;
        cout << "탐사 방법을 선택하세요." << endl;
        cout << "0: LINEAR  |  1: QUADRATIC  |  2: DOUBLE HASHING" << endl;
        cin >> selectProbe;
    }

    CustomHash *hashtable = new CustomHash(0, selectProbe);

    cout << "-----------------------------------" << endl;
    cout << "HASH TABLE is created." << endl;
    cout << "HASH: " << selectHash << "Probe: " << selectProbe << endl;
    cout << "-----------------------------------" << endl;
    cout << "" << endl;
    cout << "" << endl;

    int selectWork = -1;
    

    while(1){
        selectWork = -1;
        cout << "\n\n\n\n\n\n\n\n";
        
        cout << "size: " << hashtable->get_size() << endl;
        cout << "element: " << hashtable->get_element_count() << endl;
        //hashtable->print_list_all();


        cout << "-----------------------------------" << endl;
        cout << "작업을 선택하세요." << endl;
        cout << "|  0: PUT  |  1: GET  |  2: REMOVE  |  3:LIST  |  4:CLEAR  |  5:TEST  |  6:MULTI_PUT  |  7: INFO  |" << endl;
        
        
        cin >> selectWork;
        
        string key_input = "";
        string value_input = "";
        string stop = "";

        unsigned int test_count;
        clock_t start, end;

        switch(selectWork){
            case 0:
                cout << "-----------------------------------" << endl;
                //cout << "== 0: PUT ==" << endl;
                value_input = "";

                cout << "KEY를 입력하세요: ";
                cin >> key_input;
                cout << "VALUE를 입력하세요: ";
                cin >> value_input;

                hashtable->put(key_input, value_input);
                cout << "== put completed ==" << endl;
                break;

            case 1:
                cout << "-----------------------------------" << endl;
                //cout << "== 1: GET ==" << endl;
                key_input = "";

                cout << "KEY를 입력하세요: ";
                cin >> key_input;
                cout << "" << endl;
                cout << "   " << key_input << " :: " << hashtable->get(key_input) << endl;
                break;

            case 2:
                cout << "-----------------------------------" << endl;
                //cout << "== 2: REMOVE ==" << endl;
                key_input = "";

                cout << "KEY를 입력하세요: ";
                cin >> key_input;
                hashtable->remove(key_input);
                cout << "== remove completed ==" << endl;
                break;

            case 3:
                cout << "-----------------------------------" << endl;
                //cout << "== 3: LIST ==" << endl;
                key_input = "";
                cout << "" << endl;
                hashtable->print_list();
                cout << "" << endl;
                cout << "== list completed ==" << endl;
                break;

            case 4:
                cout << "-----------------------------------" << endl;
                cout << "== 4: CLEAR ==" << endl;
                hashtable->clear();
                cout << "== clear completed ==" << endl;
                break;
            
            case 5:
                cout << "-----------------------------------" << endl;
                cout << "== 5: TEST ==" << endl;
                
                cout << "TEST할 put 수를 입력하세요: ";

                cin >> test_count;

                multi_puts(hashtable, test_count);
                /*
                start = clock();
                
                for( unsigned int i=0 ; i < test_count ; i++){
                    hashtable->put(rand(), rand(), true);
                };

                end = clock();
                
                cout << "for " << test_count << " puts / time: " << ((float) end - start)/CLOCKS_PER_SEC << "s / conflict: " << hashtable->get_conflict_count()  << " / rehash:" << hashtable->get_rehash_count() << " / size:" << hashtable->get_size() << endl;
                */
                cout << "== test completed ==" << endl;
                break;

            case 6:
                cout << "press 0 to stop" << endl;
                
                while(1){
                    try{
                        hashtable->put(rand(), rand());
                    } catch(char const* error) {
                        cout << error << endl;
                        break;
                    }
                    
                    cout << "size: " << hashtable->get_size() << endl;
                    cout << "element: " << hashtable->get_element_count() << endl;

                    stop = cin.get();
                    if(stop=="0"){
                        break;
                    }
                }
                break;

            case 7:
                cout << "size: " << hashtable->get_size() << endl;
                cout << "element: " << hashtable->get_element_count() << endl;
                cout << "conflict: " << hashtable->get_conflict() << endl;
                cout << "rehash: " << hashtable->get_rehash_count() << endl;

            default:
                cout << ":::ERROR::: -> WRONG JOB." << endl;
                key_input = "";
                break;
        };
    };
}

void auto_test(){

    int test_count;
    clock_t start, end;

    cout << "TEST할 put 수를 입력하세요: ";
    cin >> test_count;

    for(int i=0 ; i<=2 ; i++){
        CustomHash *hashtable = new CustomHash(0, i);
        cout << "" << endl;
        cout << "" << endl;
        switch(i){
            case 1: // QUADRATIC
                cout << "QUADRATIC PROBING" << endl;
                break;

            case 2: // DOUBLE HASHING
                cout << "DOUBLE HASHING" << endl;
                break;

            default: // LINEAR
                cout << "LINEAR PROBING" << endl;
                break;        
        }
        multi_puts(hashtable, test_count);

        delete hashtable;
    }
}

int main(){

    srand(static_cast<unsigned int>(time(0)));
    int selectWork = -1;

    while(selectWork != 0 && selectWork != 1){
        cout << "\n" << endl;
        cout << "작업을 선택하세요." << endl;
        cout << "0: CREATE HASH  |  1: AUTO TEST" << endl;
        cin >> selectWork;

        switch(selectWork){
            case 0:
                test_one_hash();
                break;
            case 1:
                auto_test();
                break;

            default:
                break;
        }
    }

    return 0;
};