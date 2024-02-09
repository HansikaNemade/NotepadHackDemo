/**
* @file:   notepad.cpp
* @brief:  Notepad Controller - some controls of notepad applications can be controlled from this application
* @author: Hansika Nemade(hansikanemade@gmail.com)
* @date:   03/02/2024 (Saturday)
*/

// Headers
#include<windows.h>
#include<stdlib.h>

#include"notepad.h"


// Macros
#define    GET_NOTEPAD_HWND       101
#define    CHANGE_ICON            102
#define    CHANGE_TITLE           103
#define    REMOVE_MENU            104
#define    MOVE_UP                105
#define    MOVE_LEFT              106
#define    MOVE_RIGHT             107
#define    MOVE_DOWN              108
#define    INC_HORIZONTAL         109
#define    DEC_HORIZONTAL         110
#define    INC_VERTICAL           112
#define    DEC_VERTICAL           113
#define    SET_INITIAL            114
#define    TEXT_FONT              115
#define    SET_WINDOW             116
#define    CLOSE_NOTEPAD          117
#define    INFORMATION            118



// Global variable declaration
HWND hHackWindow = NULL;
HWND hChildNotepad = NULL;
HICON hIcon = NULL;
HICON hNotepadIcon;
HMENU hMenu;

RECT rcNotepad;
RECT rcNotepadClient;
RECT rcInitialNotepad;
RECT rcInitialClient;

TCHAR szNotepadWindowName[255] = TEXT("Untitled - Notepad");
TCHAR szChildNotepadName[255] = TEXT("Untitled");


// Function Declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK EnumWindowProc(HWND, LPARAM);
BOOL CALLBACK EnumChildProc(HWND, LPARAM);
BOOL CALLBACK EnumChildWindowProc(HWND, LPARAM);
int strtoint(char*, int);



// Entry point function

/*
*  FUNCTION NAME : WinMain()
*                      It is the Main entry point function.
* 
*  PARAMETERS :  
*                1) HINSTANCE : parameter is a handle to current instance of the application
*                2) HINSTANCE : identify the previous instance of the application (it is not used in modern windows applications)(NULL)
*                3) LPSTR :     command line parameter . it is a null terminated string
*                4) int :       parameter specifies how the application window initially shown
* 
*  RETURNS :
*                int : 
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
    // local variable declaration
    WNDCLASSEX  wndclass;
    HWND hwnd;
    HMENU hmenu;
    MSG msg;
    TCHAR szAppName[] = TEXT("HANSIKA");

    hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
    // rc.exe notepad.rc

    //WNDCLASSEX initialization   structure used to define the characteristics if window
    wndclass.cbSize = sizeof(WNDCLASSEX);
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.lpfnWndProc = WndProc;
    wndclass.hInstance = hInstance;
    wndclass.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
    wndclass.hIcon = LoadIcon(hInstance , MAKEINTRESOURCE(MYICON));
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = szAppName;
    wndclass.lpszMenuName = NULL;
    wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

    // register WNDCLASSEX
    RegisterClassEx(&wndclass);

    // creating Main Window
    hwnd = CreateWindow( szAppName,
                          TEXT("Notepad Controller"),
                          WS_OVERLAPPEDWINDOW ,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          600,
                          700,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    
    //  Show Window
    ShowWindow(hwnd, iCmdShow);

    //Update Window
    UpdateWindow(hwnd);

    // Message Loop
    while(GetMessage(&msg , NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return((int) msg.wParam);
}


/*
*  FUNCTION NAME : WndProc()
*                      this is a callback function which is called by OS whenever a msg need to proceed for an particular window.
*                      it handles messages sent to a window.
* 
*  PARAMETERS :  
*                1) HWND : it takes the Handle of the Window
*                2) UINT : it is the message from Message loop. value determine which type of msg is being processed
*                3) WPARAM : contains additional message specific data / information 
*                4) LPARAM : contains additional long message data / information
* 
*  RETURNS :
*                LRESULT : 
*/
LRESULT CALLBACK WndProc(HWND hwnd , UINT iMsg, WPARAM wParam , LPARAM lParam)
{
    // local variable 
    int cxChar, cyChar;

    int btn_width = 180;
    int btn_height = 25;
    int btn_gap = 15;
    int btn_xMid = 0;
    int btn_xpos = 0;

    static RECT rc;

    static HWND hbtn_Hack;
    static HWND hbtn_ChangeIcon;
    static HWND hbtn_ChangeTitle;
    static HWND hbtn_RemoveMenu;
    static HWND hbtn_Left;
    static HWND hbth_Right;
    static HWND hbtn_Up;
    static HWND hbtn_Down;
    static HWND hbtn_IncHorizontal;
    static HWND hbtn_DecHorizontal;
    static HWND hbtn_IncVertical;
    static HWND hbtn_DecVertical;
    static HWND hbtn_SetToInitial;
    static HWND hbtn_TextFont;
    static HWND hbtn_SetWindow;
    static HWND hbtn_CloseNotepad;
    static HWND hbtn_Info;

    //   GetDialogBaseUnits() function returns the  average width and height of the characters in the system  
    // 21*cxChar

    switch(iMsg)
    {
        // this msg is send when window is being created
        // it will be called only first time
        case WM_CREATE:
            cxChar = LOWORD(GetDialogBaseUnits());
            cyChar = HIWORD(GetDialogBaseUnits());

            GetClientRect(hwnd, &rc);
            btn_xMid = (rc.right - btn_width) / 2;
            btn_xpos = rc.right / 3;

            // x = col* (buttonsize - gapsize);
            // y = row* (buttonsize - gapsize);

            // First row  of buttons
            // mid    - Hack Notepad
            hbtn_Hack = CreateWindow(TEXT("button"), TEXT("Hack Notepad"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, btn_xMid, cyChar, btn_width, btn_height, hwnd, (HMENU)GET_NOTEPAD_HWND, NULL, NULL);


            // second row of buttons
            // first    - Change Icon
            hbtn_ChangeIcon = CreateWindow(TEXT("button"), TEXT("Change Icon"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, cxChar + btn_xpos * 0 , cyChar * 4, btn_width, btn_height, hwnd, (HMENU)CHANGE_ICON, NULL, NULL);

            // mid      - Change Title
            hbtn_ChangeTitle = CreateWindow(TEXT("button"), TEXT("Change Title"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, cxChar + (btn_xpos * 1), cyChar * 4, btn_width, btn_height, hwnd, (HMENU)CHANGE_TITLE, NULL, NULL);

            // Last     - Remove Menu
            hbtn_RemoveMenu = CreateWindow(TEXT("button"), TEXT("Remove Menu"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, cxChar + (btn_xpos * 2), cyChar * 4, btn_width, btn_height, hwnd, (HMENU) REMOVE_MENU, NULL, NULL);

 
            // third row of buttons
            // mid       - Move Up
            hbtn_Up = CreateWindow(TEXT("button"), TEXT("Move UP"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, btn_xMid,  cyChar * 8, btn_width, btn_height, hwnd, (HMENU)MOVE_UP, NULL, NULL);

            // fourth row of buttons
            // first     - Move left
            hbtn_Left = CreateWindow(TEXT("button"), TEXT("Move LEFT"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, cxChar + btn_xpos * 0, cyChar * 10, btn_width, btn_height, hwnd, (HMENU)MOVE_LEFT, NULL, NULL);

            //  second    - Move right
            hbth_Right = CreateWindow(TEXT("button"), TEXT("Move RIGHT"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, cxChar + btn_xpos * 2, cyChar * 10, btn_width, btn_height, hwnd, (HMENU)MOVE_RIGHT, NULL, NULL);

            // fifth row
            // mid        - move down
            hbtn_Down = CreateWindow(TEXT("button"), TEXT("Move DOWN"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, cxChar + btn_xpos * 1, cyChar * 12, btn_width, btn_height, hwnd, (HMENU)MOVE_DOWN, NULL, NULL);

            
            // sixth row
            //  first      - Inc horizontal
            hbtn_IncHorizontal = CreateWindow(TEXT("button"), TEXT("Increase Horizontal"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, btn_xMid / 2, cyChar * 16, btn_width, btn_height, hwnd, (HMENU)INC_HORIZONTAL, NULL, NULL);

            // second      - dec horizontal
            hbtn_DecHorizontal = CreateWindow(TEXT("button"), TEXT("Decrease Horizontal"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, btn_xMid / 2 + btn_width + btn_gap , cyChar * 16, btn_width, btn_height, hwnd, (HMENU)DEC_HORIZONTAL, NULL, NULL);

            // seventh row
            //  first      - inc vertical
            hbtn_IncVertical = CreateWindow(TEXT("button"), TEXT("Increase Vertical"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, btn_xMid / 2, cyChar * 19, btn_width, btn_height, hwnd, (HMENU)INC_VERTICAL, NULL, NULL);
 
            // second       - dec vertical
            hbtn_DecVertical = CreateWindow(TEXT("button"), TEXT("Decrease Vertical"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, btn_xMid / 2 + btn_width + btn_gap, cyChar * 19, btn_width, btn_height, hwnd, (HMENU)DEC_VERTICAL, NULL, NULL);
            
            // eighth row
            // first       - set window to initial
            //hbtn_SetToInitial = CreateWindow(TEXT("button"), TEXT("Set to Initial"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, cxChar + btn_xpos * 0, cyChar * 23, btn_width, btn_height, hwnd, (HMENU)SET_INITIAL, NULL, NULL);

            // second      - set Text with font change
            //hbtn_TextFont = CreateWindow(TEXT("button"), TEXT("Add Text with Font change"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, cxChar + (btn_xpos * 1), cyChar * 23, btn_width, btn_height, hwnd, (HMENU)TEXT_FONT, NULL, NULL);

            // third       - setwindow
            hbtn_SetWindow = CreateWindow(TEXT("button"), TEXT("Setwindow(10, 10, 700, 400)"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, cxChar + (btn_xpos * 1), cyChar * 23, btn_width, btn_height, hwnd, (HMENU)SET_WINDOW, NULL, NULL);

            // ninth row
            //  mid         - close Notepad
            hbtn_Info = CreateWindow(TEXT("button"), TEXT("Information"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, btn_xMid, cyChar * 27, btn_width, btn_height, hwnd, (HMENU)INFORMATION, NULL, NULL);

            // tenth row
            //  mid          - information
            hbtn_CloseNotepad = CreateWindow(TEXT("button"), TEXT("Close Notepad"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, btn_xMid, cyChar * 31, btn_width, btn_height, hwnd, (HMENU)CLOSE_NOTEPAD, NULL, NULL);

            break;


        // msg to destroy the parent window
        case WM_DESTROY:
           //PostQuitMessage(0);
           PostMessage(hwnd , WM_QUIT, 0, 0L);
           break;


        // Handling the messages
        case WM_COMMAND:

           switch(LOWORD(wParam))
           {
                // BUTTON - Hack Notepad
                case GET_NOTEPAD_HWND:
                    //if(hHackWindow == NULL)
                    EnumWindows(EnumWindowProc, lParam);
                    

                    GetWindowRect(hHackWindow, &rcNotepad);
                    GetClientRect(hHackWindow, &rcNotepadClient);

                    rcInitialNotepad.left = rcNotepad.left;
                    rcInitialNotepad.top = rcNotepad.top;
                    rcInitialNotepad.right = rcNotepad.right;
                    rcInitialNotepad.bottom = rcNotepad.bottom;

                    rcInitialClient.left = rcNotepadClient.left;
                    rcInitialClient.top = rcNotepadClient.top;
                    rcInitialClient.right = rcNotepadClient.right;
                    rcInitialClient.bottom = rcNotepad.bottom;
        
                    hMenu = GetMenu(hHackWindow);
                    
                    //EnumChildWindows(hHackWindow, EnumChildWindowProc, lParam);
                    MessageBox(hwnd, TEXT("Notepad Hacked"), TEXT("Message"), MB_OK);
                    break;

                //  BUTTON Change Icon
                case CHANGE_ICON:
                    //SendMessage(hHackWindow, WM_SETICON, ICON_BIG ,(LPARAM) hIcon);
                    //hIcon = (HICON) LoadImage(NULL, TEXT("MyIcon.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
                    SendMessage(hHackWindow, WM_SETICON, ICON_BIG, (LPARAM) hIcon);
                    SendMessage(hHackWindow, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
                    SendMessage(hHackWindow, WM_SETICON, ICON_SMALL2, (LPARAM)hIcon);
                    //MessageBox(hwnd, TEXT("after pressing Change Icon"), TEXT("message"), MB_OK);
                    break;

                // BUTTON Change Title
                case CHANGE_TITLE:
                    //MessageBox(hwnd, TEXT("after change title"), TEXT("message"), MB_OK);
                    SetWindowText(hChildNotepad, TEXT("MY WINDOW"));
                    SetWindowText(hHackWindow, TEXT("HANSIKA NEMADE"));
                    break;
                
                // BUTTON Remove Menu
                case REMOVE_MENU:
                    SetMenu(hHackWindow, NULL);
                    break;

                // BUTTON  Move Up
                case MOVE_UP:
                    rcNotepad.top = rcNotepad.top - 50;
                    MoveWindow(hHackWindow, rcNotepad.left, rcNotepad.top, rcNotepad.right, rcNotepad.bottom, SWP_NOZORDER);
                    //SetWindowPos(hHackWindow, NULL, rcNotepad.left, rcNotepad.top, rcNotepad.right, rcNotepad.bottom- 50,SWP_NOZORDER);
                    break;

                // BUTTON Move Down
                case MOVE_DOWN:
                    rcNotepad.top = rcNotepad.top + 50;
                    MoveWindow(hHackWindow, rcNotepad.left, rcNotepad.top, rcNotepad.right, rcNotepad.bottom, SWP_NOZORDER);
                    break;

                // BUTTON Move Left
                case MOVE_LEFT:
                    rcNotepad.left = rcNotepad.left - 50;
                    MoveWindow(hHackWindow, rcNotepad.left, rcNotepad.top, rcNotepad.right, rcNotepad.bottom, SWP_NOZORDER);
                    break;

                // BUTTON Move Right
                case MOVE_RIGHT:
                    rcNotepad.left = rcNotepad.left + 50;
                    MoveWindow(hHackWindow, rcNotepad.left, rcNotepad.top, rcNotepad.right, rcNotepad.bottom, SWP_NOZORDER);
                    break;

                // BUTTON increase Horizontal
                case INC_HORIZONTAL:
                    rcNotepadClient.right = rcNotepadClient.right + 50;
                    MoveWindow(hHackWindow, rcNotepad.left, rcNotepad.top, rcNotepadClient.right, rcNotepad.bottom, SWP_NOZORDER);
                    break;
                
                // BUTTON Decrease Horizontal
                case DEC_HORIZONTAL:
                    rcNotepadClient.right = rcNotepadClient.right - 50;
                    MoveWindow(hHackWindow, rcNotepad.left, rcNotepad.top, rcNotepadClient.right, rcNotepad.bottom, SWP_NOZORDER);
                    break;

                // BUTTON Increase Vertical
                case INC_VERTICAL:
                    rcNotepadClient.bottom = rcNotepadClient.bottom + 50;
                    MoveWindow(hHackWindow, rcNotepad.left, rcNotepad.top, rcNotepad.right, rcNotepadClient.bottom, SWP_NOZORDER);
                    break;

                // BUTTON Decrease Vertical
                case DEC_VERTICAL: 
                    rcNotepadClient.bottom = rcNotepadClient.bottom - 50;
                    MoveWindow(hHackWindow, rcNotepad.left, rcNotepad.top, rcNotepad.right, rcNotepadClient.bottom, SWP_NOZORDER);
                    break;

                //BUTTON  Set to initial
                case SET_INITIAL:
                    if(hHackWindow == NULL)
                        break;

                    rcNotepad.left = rcInitialNotepad.left;
                    rcNotepad.top = rcInitialNotepad.top;
                    rcNotepadClient.right = rcInitialClient.right;
                    rcNotepadClient.bottom = rcInitialClient.bottom;

                    SetWindowText(hHackWindow, szNotepadWindowName);
                    SetMenu(hHackWindow, hMenu);
                    DrawMenuBar(hHackWindow);
                    SendMessage(hHackWindow, WM_SETICON, ICON_BIG, (LPARAM)hNotepadIcon);
                    EnumChildWindows(hHackWindow, EnumChildProc, 0);
                    SetWindowPos(hHackWindow, NULL, rcNotepad.left, rcNotepad.top, rcNotepadClient.right, rcNotepadClient.bottom,SWP_NOZORDER);
                    break;
                
                //BUTTON Add text with font
                case TEXT_FONT:
                    if(hHackWindow == NULL);
                       break;

                    EnumChildWindows(hHackWindow, EnumChildProc, 1);
                    break;

                //BUTTON  Set Window
                case SET_WINDOW:
                    rcNotepad.left = 10;
                    rcNotepad.top = 10;
                    rcNotepad.right = 700;
                    rcNotepad.bottom = 400;
                    SetWindowPos(hHackWindow, NULL, rcNotepad.left, rcNotepad.top, rcNotepad.right, rcNotepad.bottom,SWP_NOZORDER);
                    break;

                // BUTTON Close Notepad
                case CLOSE_NOTEPAD:
                    PostMessage(hHackWindow, WM_DESTROY, 0, 0);
                    hHackWindow = NULL;
                    break;

                // BUTTON Information
                case INFORMATION:
                    MessageBox(hwnd, 
                               TEXT("This Application is Created By Hansika Nemade\n Directed by - Dr. Vijay Gokhale Sir and Mayur Tadekar Sir\nLanguage : C++  \nTechnology : Win32 SDK"), 
                               TEXT("Project Name : Notepad Controller (Notepad Hack Demo)"), 
                               MB_OK | MB_ICONINFORMATION);
                    break;

                default:
                    break;
           }
           break;

        default:
           break;
             
    }

    return(DefWindowProc(hwnd , iMsg, wParam, lParam));
}

/*
*  FUNCTION NAME : EnumWindowProc()
*                       it is a callback function which enumerates all top level windows.
*                       also get the window names of all top level window with the handle and comparing the names with which
*                       we want. store the handle of that window.
* 
*  PARAMETERS :  
*                1) HWND :  handle of the enumrating window
*                2) LPARAM : contains additional Information
* 
*  RETURNS :
*                BOOL : TRUE - if handle found, FALSE - if handle not found
*/
BOOL CALLBACK EnumWindowProc(HWND hwnd, LPARAM lParam)
{
    // local vairable
    TCHAR WindowName[256] ;

    // getting window text
    GetWindowText(hwnd, WindowName, 256);

    // comparing the text of the handle which we want
    if( lstrcmp(WindowName, szNotepadWindowName) == 0)
    {
        hHackWindow = hwnd;
        //return(TRUE);
    }

    return(TRUE);
}

/*BOOL CALLBACK EnumChildWindowProc(HWND hwnd, LPARAM lParam)
{
    TCHAR TabName[256] ;

    GetWindowText(hwnd, TabName, 256);

    if(lstrcmp(TabName, szChildNotepadName) == 0)
    {
        hChildNotepad = hwnd;
    }

    return(TRUE);
}*/

/*
*  FUNCTION NAME : EnumChildProc()
*                       it is a callback which is used to create specific font and print with new font text
* 
*  PARAMETERS :  
*                1) HWND :  handle of the  window
*                2) LPARAM : contains additional Information - string should add to window or not;
* 
*  RETURNS :
*                BOOL : True
*/
BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam)
{
    TCHAR strChild[256];
    HFONT hFont;

    // creating font
    hFont = CreateFont(36,                     // Height
                       0,                      // Width
                       0,                      // Escapement
                       500,                    // Orientation
                       FW_NORMAL,              // Weight
                       FALSE,                  // Italic
                       FALSE,                  // Underline
                       FALSE,                  // Strikeout
                       DEFAULT_CHARSET,        // Charset
                       OUT_DEFAULT_PRECIS,     // Output precision
                       CLIP_DEFAULT_PRECIS,    // Clipping precision
                       DEFAULT_QUALITY,        // Quality
                       DEFAULT_PITCH | FF_DONTCARE, // Pitch and family
                       TEXT("Cambria")                // Font name
    );

    // sending message to change with created font
    SendMessage(hwnd, WM_SETFONT, (WPARAM)hFont, TRUE);

    if(lParam)
    {
        // adding string to str
        wsprintf(strChild, TEXT("This is the Default Font"));
    }
    
    // sending message to set the text 
    SendMessage(hHackWindow, WM_SETTEXT, 0, (LPARAM) strChild);

    return(TRUE);
}

