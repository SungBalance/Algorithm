#include <iostream>
#include "CustomHash.h"

using namespace std;

int main()
{
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
        cout << "\x1B[2J\x1B[H";
        hashtable->print_list();
        cout << "-----------------------------------" << endl;
        cout << "작업을 선택하세요." << endl;
        cout << "|  0: PUT  |  1: GET  |  2: REMOVE  |  3:LIST  |  4:CLEAR  |  5:TEST  |" << endl;
        
        cin >> selectWork;
        
        string key_input = "";
        string value_input = "";

        switch(selectWork){
            case 0:
                cout << "-----------------------------------" << endl;
                //cout << "== 0: PUT ==" << endl;
                key_input = "";
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
                key_input = "";
                cout << "== test completed ==" << endl;
                break;

            default:
                cout << ":::ERROR::: -> WRONG JOB." << endl;
                break;
        };
        selectWork = -1;
    };

    return 0;
}