#include <iostream>
#include <cstdlib>
#include <vector>
#include "CustomHash.h"

using namespace std;

string get_random_string(){
    
    string str = "";
    /*
    int len = 1; //rand() % 5;
    for (size_t i = 0; i < len; ++i) {
         int randomChar = rand()%(26+26+10);
         if (randomChar < 26)
             str.append('a' + randomChar);
         else if (randomChar < 26+26)
             str.append('A' + (randomChar - 26));
         else
             str.append('0' + (randomChar - 26 - 26));
     }
     */
     return str;
}


void multi_inserts(CustomHash * hashtable, unsigned int test_count, vector<unsigned int> & key_list){
    clock_t start, end;
    unsigned int key;
    
    start = clock();
    for( unsigned int i=0 ; i < test_count ; i++){
        try{
            key = rand();
            key_list.push_back(key);
            hashtable->insert(key, rand());
        } catch(char const* error) {
            cout << error << endl;
            break;
        }
    };
    end = clock();
    cout << "inserts:: for " << test_count << " inserts / node: " << hashtable->get_element_count() << " / time: " << ((float) end - start)/CLOCKS_PER_SEC << "s / conflict: " << hashtable->get_conflict_count()  << " / rehash:" << hashtable->get_rehash_count() << " / size:" << hashtable->get_size() << endl;
}

void multi_searches(CustomHash * hashtable, vector<unsigned int> & key_list){
    clock_t start, end;
    unsigned int key;
    
    start = clock();
    for( unsigned int i=0 ; i < key_list.size() ; i++){
        try{
            hashtable->get(key_list[i]);
        } catch(char const* error) {
            cout << error << endl;
            break;
        }
    };
    end = clock();
    cout << "searches:: for " << key_list.size() << " keys / time: " << ((float) end - start)/CLOCKS_PER_SEC << endl;
}

void multi_removes(CustomHash * hashtable, vector<unsigned int> & key_list){
    clock_t start, end;
    unsigned int key;
    
    start = clock();
    for( unsigned int i=0 ; i < key_list.size() ; i++){
        try{
            hashtable->remove(key_list[i]);
        } catch(char const* error) {
            cout << error << endl;
            break;
        }
    };
    end = clock();
    cout << "removes:: for " << key_list.size() << " keys / time: " << ((float) end - start)/CLOCKS_PER_SEC << endl;
}

void auto_test(){

    vector<unsigned int> key_list;
    int test_count;

    cout << "TEST할 insert 수를 입력하세요: ";
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
        
        multi_inserts(hashtable, test_count, key_list);

        switch(i){
            case 1: // QUADRATIC
                multi_searches(hashtable, key_list);
                break;

            case 2: // DOUBLE HASHING
                multi_searches(hashtable, key_list);
                break;

            default: // LINEAR
                multi_searches(hashtable, key_list);
                break;        
        }
        
        delete hashtable;
        key_list.clear();
    }

}


void test_one_hash(){
    cout << "-----------------------------------" << endl;
    
    
    int selectHash = 0;
    /*
    while(selectHash != 0 && selectHash != 1){
        cout << "HASH 종류를 선택하세요." << endl;
        cout << "0: DIVISION(default)  |  1: MULTIPLICATION" << endl;
        cin >> selectHash;
    }
    */
    
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
        cout << "\n\n\n\n";
        
        cout << "size: " << hashtable->get_size() << endl;
        cout << "element: " << hashtable->get_element_count() << endl;
        if(hashtable->get_element_count() < 10){
            hashtable->print_list_all();
        }
        


        cout << "-----------------------------------" << endl;
        cout << "작업을 선택하세요." << endl;
        cout << "|  0: insert  |  1: GET  |  2: REMOVE  |  3:LIST  |  4:CLEAR  |  5:TEST  |  6:MULTI_insert  |  7: INFO  |" << endl;
        
        
        cin >> selectWork;
        
        string key_input = "";
        string value_input = "";
        string stop = "";
        vector<unsigned int> key_list;

        unsigned int test_count;
        clock_t start, end;

        switch(selectWork){
            case 0:
                cout << "-----------------------------------" << endl;
                //cout << "== 0: insert ==" << endl;
                value_input = "";

                cout << "KEY를 입력하세요: ";
                cin >> key_input;
                cout << "VALUE를 입력하세요: ";
                cin >> value_input;

                hashtable->insert(key_input, value_input);
                cout << "== insert completed ==" << endl;
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
                
                cout << "TEST할 insert 수를 입력하세요: ";

                cin >> test_count;

                multi_inserts(hashtable, test_count, key_list);
                /*
                start = clock();
                
                for( unsigned int i=0 ; i < test_count ; i++){
                    hashtable->insert(rand(), rand(), true);
                };

                end = clock();
                
                cout << "for " << test_count << " inserts / time: " << ((float) end - start)/CLOCKS_PER_SEC << "s / conflict: " << hashtable->get_conflict_count()  << " / rehash:" << hashtable->get_rehash_count() << " / size:" << hashtable->get_size() << endl;
                */
                cout << "== test completed ==" << endl;
                break;

            case 6:
                cout << "press 0 to stop" << endl;
                stop = "";
                while(1){
                    
                    try{
                        hashtable->insert(rand(), rand());
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
                cout << "conflict: " << hashtable->get_conflict_count() << endl;
                cout << "rehash: " << hashtable->get_rehash_count() << endl;
                break;

            default:
                cout << ":::ERROR::: -> WRONG JOB." << endl;
                key_input = "";
                break;
        };
    };
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