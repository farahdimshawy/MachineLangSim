#include <iostream>
#include <iomanip>
#include "Machine.h"
int main() {
    Machine machine;
    while(1){
        vector<string> menu{
                "Load a new program from a file",
                "Display register content",
                "Display memory content",
                "Display screen content"
        };
        cout << "====================================\n";
        for (int i{1}; i <= menu.size(); i++)
        {
            cout << i << "-" << menu[i - 1] << endl;
        }
        cout << "0-Exit\n";
        cout << "====================================\n";
        cout << "Response: ";
        int choice;
        cin >> choice;
        if (choice < 0 || choice > menu.size()) continue;
        switch(choice)
        {
            case 0:
            {
                return 0;
            }
            case 1:
            {
                machine.reset();
                string file_name;
                cout << "Filename: ";
                cin >> file_name;
                machine.read(file_name);
                machine.execute();
                break;
            }
            case 2:
            {
                machine.displayRegister();
                break;
            }
            case 3:
            {
                machine.displayMemory();
                break;
            }
            case 4:
            {
                machine.screen_content();
                break;
            }
        }
    }
}

