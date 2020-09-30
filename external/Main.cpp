#include <Windows.h>
#include<TlHelp32.h>
#include <iostream>
#include <tchar.h>
#include <vector>
#include <WinUser.h>
using namespace std;

void read(HANDLE handle, LPVOID mem, int read) {
    ReadProcessMemory(handle, (PBYTE*)mem, &read, sizeof(int), 0);
    cout << "Current value: " << read << endl;
}
void write(HANDLE phandle, DWORD pID, LPVOID mem, int newvalue) {
    WriteProcessMemory(phandle, (LPVOID)mem, &newvalue, sizeof(newvalue), 0);
}
int main()
{

    int newvalue = 68;
    int readTest = 0; 
    //change memory address value here (hard code bc yea)
    PVOID mem = (PVOID)0x009EFADC;
    

    SetConsoleTitle(_T("bEEP bop"));

    //app window name, change here 
    HWND hwnd_AC = FindWindow(NULL, _T("Tacobell"));
    if (hwnd_AC == NULL)
    {
        cout << "Couldn't find window" << endl;
        Sleep(1000);
        exit(0);
    }
    
    cout << "Window Found." << endl;
    DWORD pID = NULL; 
    GetWindowThreadProcessId(hwnd_AC, &pID);
    if (pID == NULL) {
        cout << "Cannot Obtain Process" << endl; 
        Sleep(1000);
        exit(0);
    }
    cout << "Process ID: " << pID << endl;
    HANDLE phandle = NULL;
    phandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
    cout << "Accessing Memory at 0x" << mem << endl << endl; 
    while(1){
        char rw;
        cout << "write or read [r/w]" << endl;
        cin >> rw; 
        cin.ignore(1000, 10);

        if (tolower(rw) == 'r') {
            read(phandle, mem, readTest);

        }
        else if (tolower(rw) == 'w') {
            
            cout << "enter new value: "; 
            cin >> newvalue; 
            cin.ignore(1000, 10);

            write(phandle, pID, mem, newvalue);

        }
        else if (tolower(rw) == 'c') {

            system("cls");

        }
        else {
            cout << "Enter a valid option" << endl;
        }
        cout << endl << endl; 
        

    }
}
