// bencalculator.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "bencalculator.h"

//initialize variables
//they must be global variables
float num;
float num2;
//important variable
//determine first or second argument
bool secondArgument;

//Create variables to store all of the buttons in
HWND hTextBox;
HWND hButtonOne;
HWND hButtonTwo;
HWND hButtonThree;
HWND hButtonFour;
HWND hButtonFive;
HWND hButtonSix;
HWND hButtonSeven;
HWND hButtonEight;
HWND hButtonNine;
HWND hButtonZero;
HWND hButtonEnd;
HWND hButtonClear;
HWND hButtonMath;

//defunct
//unless i upgrade
HBITMAP hBkg;
HDC hBitmapMemory, hdc;
PAINTSTRUCT Ps;
HINSTANCE hInstance;


//basic routine to add number to the end of previous number
float addNum(float i)
{
	//if the user has not pressed math yet
	//keep working on first variable
	if(secondArgument==false)
	{
		num = num*10;
		num+=i;
		return num;
	}
	else
	{
		num2 = num2*10;
		num2+=i;
		return num2;
	}
}

//clear variables
void clearMem()
{
	num=0;
	num2=0;
	secondArgument=false;
}

//gets each of the variables
//and does math to them
//then outputs them to the screen
void endFunction()
{
	//only allow user to end math if on second argument
	if(secondArgument==true)
	{

		float end;
		int r;
		//safety
		end=0;
		r=1;

		std::wstringstream wss;
		//generate rand num with max of 4
		//then use the random num to pick random function
		r = rand()%4;
		if(r==1)
		{
			end = num+num2;
		}
		else if(r==2)
		{
			end = num-num2;
		}
		else if(r==3)
		{
			end = num*num2;
		}
		else if(r==4)
		{
			end = num/num2;
		}

		//conversion to the windows string
		wss<<end;
		SetWindowText(hTextBox,wss.str().c_str());

		//reset the variables

		clearMem();
	}
}

//must not be in the same class cause windows
//is the main loop of program
//and needs to be at the top
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//main loop
	//receives messages from windows so i dont have to do anything
	switch(msg)
	{

	case WM_PAINT:
		{
			//cant make background bitmap
			//cause this is express edition
		}
	case WM_COMMAND:
		{
			switch(wParam)
			{
			case BN_CLICKED:
				{
					//clear button pressed
					if(hButtonClear == (HWND)lParam)
					{
						//clear it all
						clearMem();
						SetWindowText(hTextBox,TEXT(""));
					}
					//create new blank line
					//keep first argument stored
					//start second argument
					if(hButtonMath == (HWND)lParam)
					{
						if(secondArgument==false)
						{
							secondArgument=true;
							SetWindowText(hTextBox,TEXT("0"));
						}
						else
						{
							//give answer when already pressed math
							endFunction();
						}
					}
					if(hButtonEnd == (HWND)lParam)
					{
						endFunction();
					}

					//for input of numbers
					//to prevent overflow
					if(num<1000000)
					{
						//button funcs
						if(hButtonOne == (HWND)lParam)
						{
							wchar_t buffer[10];
							_itow_s (addNum(1), buffer, 10);
							SetWindowText(hTextBox,buffer);
						}
						if(hButtonTwo==(HWND)lParam)
						{
							wchar_t buffer[10];
							_itow_s (addNum(2), buffer, 10);
							SetWindowText(hTextBox,buffer);
						}
						if(hButtonThree== (HWND)lParam)
						{
							wchar_t buffer[10];
							_itow_s (addNum(3),buffer,10);
							SetWindowText(hTextBox,buffer);
						}
						if(hButtonFour== (HWND)lParam)
						{
							wchar_t buffer[10];
							_itow_s (addNum(4),buffer,10);
							SetWindowText(hTextBox,buffer);
						}
						if(hButtonFive== (HWND)lParam)
						{
							wchar_t buffer[10];
							_itow_s (addNum(5),buffer,10);
							SetWindowText(hTextBox,buffer);
						}
						if(hButtonSix== (HWND)lParam)
						{
							wchar_t buffer[10];
							_itow_s (addNum(6),buffer,10);
							SetWindowText(hTextBox,buffer);
						}
						if(hButtonSeven== (HWND)lParam)
						{
							wchar_t buffer[10];
							_itow_s (addNum(7),buffer,10);
							SetWindowText(hTextBox,buffer);
						}
						if(hButtonEight== (HWND)lParam)
						{
							wchar_t buffer[10];
							_itow_s (addNum(8),buffer,10);
							SetWindowText(hTextBox,buffer);
						}
						if(hButtonNine== (HWND)lParam)
						{
							wchar_t buffer[10];
							_itow_s (addNum(9),buffer,10);
							SetWindowText(hTextBox,buffer);
						}
						if(hButtonZero== (HWND)lParam)
						{
							wchar_t buffer[10];
							_itow_s (addNum(0),buffer,10);
							SetWindowText(hTextBox,buffer);
						}

					}
				}
			}
			break;
		}
	case WM_CLOSE:
		{
			DestroyWindow(hWnd);
			break;
		}
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		
	default:
		{
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
	}
	return 0;
}

//main func
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR LpCmdLine, int nCmdShow)
{
	//initialize important variables
	num = 0;
	num2 = 0;
	secondArgument = false;
	//create class
	WCalculator *calc = new WCalculator(hInstance,hPrevInstance,LpCmdLine,nCmdShow);
}

//create calculator class
WCalculator::WCalculator(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR LpCmdLine, int nCmdShow)
{
	static TCHAR szWindowClass[] = _T("win32");
	static TCHAR szWndName[] = _T("BenCalculator");

	MSG Msg;
	HWND hWnd;
	HFONT hFont;


	//create wnd object
	WNDCLASSEX wnd;
	wnd.cbSize = sizeof(WNDCLASSEX);
	wnd.style = 0;
	wnd.lpfnWndProc = WndProc;
	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.hInstance = hInstance;
	wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wnd.hCursor = LoadCursor(NULL,IDC_ARROW);
	wnd.hbrBackground = (HBRUSH)(COLOR_MENU);
	wnd.lpszMenuName = NULL;
	wnd.lpszClassName = szWindowClass;
	wnd.hIconSm = LoadIcon(NULL,IDI_APPLICATION);

	if(!RegisterClassEx(&wnd))
	{
		//problem creating wndclassex object
		MessageBox(NULL,_T("Error Registering Class"),_T("Error"),NULL);
	}
	hWnd = CreateWindow(szWindowClass,szWndName,WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,250,350,NULL,NULL,hInstance,NULL);

	if(!hWnd)
	{
		//win 32 error
		MessageBox(NULL,_T("Error Creating Window"),_T("Error"),NULL);
	}

	//to make it easier to change font and stuff
	std::vector<HWND> gui_manager;


	//create font
	hFont = CreateFont(20,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Calibri"));


		
	//create border
	//CreateWindow(szWindowClass,TEXT(""),WS_CHILD|WS_VISIBLE|WS_BORDER,5,5,235,312,hWnd,(HMENU) 1,NULL,NULL);

	//create stuff inside of the initial window
	//create display box
	//add buttons to gui_manager array
	hTextBox = CreateWindow(TEXT("STATIC"),TEXT(""),WS_CHILD|WS_VISIBLE|WS_BORDER,20,20,200,50,hWnd,(HMENU) 1,NULL,NULL);
	gui_manager.push_back(hTextBox);

	//make buttons
	//loops? hah!

	hButtonOne = CreateWindowEx(WS_EX_WINDOWEDGE, TEXT("BUTTON"), TEXT("1"), WS_CHILDWINDOW | BS_PUSHBUTTON | WS_VISIBLE, 20, 100, 30, 30, hWnd, NULL, NULL, NULL);
	gui_manager.push_back(hButtonOne);
	hButtonTwo = CreateWindowEx(WS_EX_WINDOWEDGE, TEXT("BUTTON"), TEXT("2"), WS_CHILDWINDOW | BS_PUSHBUTTON | WS_VISIBLE, 60, 100, 30, 30, hWnd, NULL, NULL, NULL);
	gui_manager.push_back(hButtonTwo);
	hButtonThree = CreateWindowEx(WS_EX_WINDOWEDGE, TEXT("BUTTON"), TEXT("3"), WS_CHILDWINDOW | BS_PUSHBUTTON | WS_VISIBLE, 100, 100, 30, 30, hWnd, NULL, NULL, NULL);
	gui_manager.push_back(hButtonThree);
	hButtonFour = CreateWindowEx(WS_EX_WINDOWEDGE, TEXT("BUTTON"), TEXT("4"), WS_CHILDWINDOW | BS_PUSHBUTTON | WS_VISIBLE, 20, 150, 30, 30, hWnd, NULL, NULL, NULL);
	gui_manager.push_back(hButtonFour);
	hButtonFive = CreateWindowEx(WS_EX_WINDOWEDGE, TEXT("BUTTON"), TEXT("5"), WS_CHILDWINDOW | BS_PUSHBUTTON | WS_VISIBLE, 60, 150, 30, 30, hWnd, NULL, NULL, NULL);
	gui_manager.push_back(hButtonFive);
	hButtonSix = CreateWindowEx(WS_EX_WINDOWEDGE, TEXT("BUTTON"), TEXT("6"), WS_CHILDWINDOW | BS_PUSHBUTTON | WS_VISIBLE, 100, 150, 30, 30, hWnd, NULL, NULL, NULL);
	gui_manager.push_back(hButtonSix);
	hButtonSeven = CreateWindowEx(WS_EX_WINDOWEDGE, TEXT("BUTTON"),TEXT("7"), WS_CHILDWINDOW | BS_PUSHBUTTON | WS_VISIBLE, 20, 200, 30, 30, hWnd, NULL, NULL, NULL);
	gui_manager.push_back(hButtonSeven);
	hButtonEight = CreateWindowEx(WS_EX_WINDOWEDGE, TEXT("BUTTON"), TEXT("8"), WS_CHILDWINDOW | BS_PUSHBUTTON | WS_VISIBLE, 60, 200, 30, 30, hWnd, NULL, NULL, NULL);
	gui_manager.push_back(hButtonEight);
	hButtonNine = CreateWindowEx(WS_EX_WINDOWEDGE, TEXT("BUTTON"), TEXT("9"), WS_CHILDWINDOW | BS_PUSHBUTTON | WS_VISIBLE, 100, 200, 30, 30, hWnd, NULL, NULL, NULL);
	gui_manager.push_back(hButtonNine);
	hButtonZero = CreateWindowEx(WS_EX_WINDOWEDGE, TEXT("BUTTON"), TEXT("0"), WS_CHILDWINDOW | BS_PUSHBUTTON | WS_VISIBLE, 20, 250, 30, 30, hWnd, NULL, NULL, NULL);
	gui_manager.push_back(hButtonZero);
	hButtonEnd = CreateWindowEx(WS_EX_WINDOWEDGE, TEXT("BUTTON"), TEXT("="), WS_CHILDWINDOW | BS_PUSHBUTTON | WS_VISIBLE, 60, 250, 70, 30, hWnd, NULL, NULL, NULL);
	gui_manager.push_back(hButtonEnd);
	hButtonClear = CreateWindowEx(WS_EX_WINDOWEDGE, TEXT("BUTTON"), TEXT("C"), WS_CHILDWINDOW | BS_PUSHBUTTON | WS_VISIBLE, 140, 100, 70, 30, hWnd, NULL, NULL, NULL);
	gui_manager.push_back(hButtonClear);
	hButtonMath = CreateWindowEx(WS_EX_WINDOWEDGE, TEXT("BUTTON"), TEXT("Math"), WS_CHILDWINDOW | BS_PUSHBUTTON | WS_VISIBLE, 140, 150, 70, 130, hWnd, NULL, NULL, NULL);
	gui_manager.push_back(hButtonMath);



	//set font
	//super easy with the vector
	for(unsigned int i = 0; i<gui_manager.size();i++)
	{
		SendMessage(gui_manager[i],WM_SETFONT,WPARAM(hFont),TRUE);
	}

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	
	//loop
	//really just goes to wndproc
	while(GetMessage(&Msg,NULL,0,0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	
}

