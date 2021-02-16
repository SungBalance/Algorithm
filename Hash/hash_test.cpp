#include <iostream>
#include "CustomHash.h"

using namespace std;

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

    CustomHash *hashtable = new CustomHash(0, 0);

    cout << "-----------------------------------" << endl;
    cout << "HASH TABLE is created." << endl;
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
        cout << "|  0: PUT  |  1: GET  |  2: REMOVE  |  3:LIST  |  4:CLEAR  |  5:TEST  |" << endl;
        
        
        cin >> selectWork;
        
        string key_input = "";
        string value_input = "";

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
                
                cout << "TEST할 put 수를 입력하세요(단위:1000): ";

                cin >> test_count;

                start = clock();
                
                for( unsigned int i=0 ; i < test_count*1000 ; i++){
                    hashtable->put(i, i, true);
                };

                end = clock();
                
                cout << test_count*1000 << " puts with " << ((float) end - start)/CLOCKS_PER_SEC << "s" << endl;

                cout << "== test completed ==" << endl;
                break;

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

        start = clock();
                
        for( unsigned int j=0 ; j < test_count ; j++){
            hashtable->put(j, j);
        };

        end = clock();
        cout << "for " << test_count << " puts / time: " << ((float) end - start)/CLOCKS_PER_SEC << "s" << endl;
        
        delete hashtable;
    }
}

int main(){

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