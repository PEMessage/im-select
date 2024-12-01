#include "stdafx.h"
#include "parg.h"

#include <cstdlib>
#include <cstring>
#include <Windows.h>
#include <immdev.h>
/* #define DEBUG */

using namespace std;

int getInputMethod() {
	HWND hwnd = GetForegroundWindow(); //dll
	if (hwnd) {
		DWORD threadID = GetWindowThreadProcessId(hwnd, NULL); //dll
		HKL currentLayout = GetKeyboardLayout(threadID); //dll
		unsigned int x = (unsigned int)currentLayout & 0x0000FFFF;
		return ((int)x);
	}
	return 0;
}
void switchInputMethod(int locale) {
    if (locale < 0) {
        return;
    }
	HWND hwnd = GetForegroundWindow(); //dll
	LPARAM currentLayout = ((LPARAM)locale);
	PostMessage(hwnd, WM_INPUTLANGCHANGEREQUEST, 0, currentLayout); //dll
}

// API: https://learn.microsoft.com/en-us/previous-versions/aa913780(v=msdn.10)
// For  Microsoft Old Chinese IME(Win10 and Previous) :
//       0: English
//       1: Chinese
// For  Microsoft New Chinese IME(Win11) :
//       0: English / Half Shape
//       1: Chinese / Half Shape
//       1024: English / Full Shape (Bit10 and Bit1 used)
//       1025: Chinese / Full Shape
LRESULT getInputMode(){
    HWND foregroundWindow  = GetForegroundWindow(); 
    HWND foregroundIME = ImmGetDefaultIMEWnd(foregroundWindow);
    if(foregroundIME){
        LRESULT result = SendMessage(foregroundIME, WM_IME_CONTROL, 0x001, 0);
        return result;
    } else {
        return 0;
    }
}

void switchInputMode(LRESULT mode){
    if ( mode < 0 ) {
        return;
    }
    HWND foregroundWindow  = GetForegroundWindow(); 
    HWND foregroundIME = ImmGetDefaultIMEWnd(foregroundWindow);
    LPARAM currentMode = (LPARAM)mode;
    SendMessage(foregroundIME, WM_IME_CONTROL, IMC_SETCONVERSIONMODE, currentMode);
}


int main(int argc, char** argv)
{
    // init parg
    struct parg_state ps;
    int c;
    parg_init(&ps);
    // h: help page
    // d: delay INT ms
    const char optstring[] = "hd:" ;
    int optend = parg_reorder(argc, argv, optstring, NULL);

    /* printf("%d\n", optend) ; */


    int delay = 30 ; // ms 
    while ((c = parg_getopt(&ps, optend, argv, optstring)) != -1) {
        switch (c) {
            case 'h':
                printf( \
                        "USAGE:                                              \n" \
                        "       im-select-imm [-h] [-d DELAY] [METHOD] [MODE]\n" \
                        "VERSION:                                            \n" \
                        "       1.0.2                                        \n" \
                        );
                return 0;
            case 'd':
                delay = atoi(ps.optarg); 
                #ifdef DEBUG 
                printf("DELAY: %d\n", delay);
                #endif
                break;
            case 1:
                // for remaining option
                break;
        }
    }

    // process position args

    int remian_argc = argc - ps.optind ;
    char **remain_argv = argv + ps.optind ;

    #ifdef DEBUG
    printf("OPTIND: %d\n", ps.optind);
    printf("REMIAN_ARGC: %d\n", remian_argc);
    for(int i = 1; i < argc; i++) {
        printf("ARGV[%d]: %s\n", i, argv[i]);
    }
    for(int i = 0; i < remian_argc; i++) {
        printf("REMAIN_ARGV[%d]: %s\n", i, remain_argv[i]);
    }
    #endif

    // get mode
    if ( remian_argc == 0 ) {
        int imID = getInputMethod();
        int imMode = getInputMode();
        printf("%d-%d\n", imID, imMode);
        return 0;
    } 

    // not getmode, so is set mode
    LRESULT mode = -1;
    int method = -1;
    if(  remian_argc == 1 ) {
        char *dash_p = strchr(remain_argv[0],'-');
        if(dash_p){
            char locale_str[16];
            memccpy(locale_str,remain_argv[0],'-',sizeof locale_str);

            method = atoi(locale_str);
            mode = atoi(dash_p + 1);
        } else {
            method = atoi(remain_argv[0]);
        }
    } 

    if ( remian_argc == 2 ) {
		// im-select-imm [Method] [Mode]
        method = atoi(remain_argv[0]);
        mode = atoi(remain_argv[1]);
    }
    #ifdef DEBUG
    printf("SET METHOD: %d\n", method);
    printf("SET MODE: %d\n", mode);
    #endif 

    switchInputMethod(method);
    Sleep(delay);
    switchInputMode(mode);

	return 0;
}

