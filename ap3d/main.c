#include <windows.h>  

#include <lua.h> 
#include <lualib.h>  
#include <lauxlib.h>  



void run_lua(HWND hwnd)
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	//����Ҫ���������ļ���ע��ÿˢ��һ�ζ�Ҫ������
	if(luaL_loadfile(L,"main.lua") || lua_pcall(L,0,0,0))
	{
		MessageBox(NULL,TEXT("luaL_loadfile main.lua  error."),TEXT("warning"),MB_OK); 		
	}
	
	lua_getglobal(L,"on_paint");//�����õĺ���	
	lua_pushnumber(L,1);
	
	HDC hdc = GetDC(hwnd);
	lua_pushlightuserdata(L,hdc);
	
	
	//1��������0������ֵ
	if(lua_pcall(L,2,1,0) !=0)
	{
		MessageBox(NULL,TEXT("run onpaint function error."),TEXT("warning"),MB_OK); 		
	}
	if(!lua_isnumber(L,-1)){
		MessageBox(NULL,TEXT("return error."),TEXT("warning"),MB_OK); 
	}
	int num = lua_tonumber(L,-1);
	char str[25];
    itoa(num, str, 10);
	//MessageBox(NULL,TEXT(str),TEXT("result"),MB_OK); 
	lua_pop(L,1);
	
	//������
	lua_close(L);	
}


void on_paint(HWND hwnd)
{
	RECT rect;
	HDC hdc;
	GetClientRect(hwnd,&rect);
	ValidateRect(hwnd,&rect); //ǿ�ư���Ч���������Ϊ��Ч
	hdc = GetDC(hwnd);
	DrawText(hdc,TEXT("Hello world��"),-1,&rect,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
	
	//��Ӧlua�е�on_paint����
	run_lua(hwnd);	
	
	MoveToEx(hdc,0,0,NULL);
	LineTo(hdc,500,500);
	
	ReleaseDC(hwnd,hdc);		
}
/*
void run_lua(HWND hwnd)
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	if(luaL_loadfile(L,"main.lua") || lua_pcall(L,0,0,0))
	{
		MessageBox(NULL,TEXT("luaL_loadfile error."),TEXT("warning"),MB_OK); 
	}
	
	lua_getglobal(L,"width");
	int w;
	w = lua_tointeger(L,-1);

}
*/
void write_dxf()
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	if(luaL_loadfile(L,"write_dxf.lua") || lua_pcall(L,0,0,0))
	{
		MessageBox(NULL,TEXT("luaL_loadfile error."),TEXT("warning"),MB_OK); 
	}
	
}	
LRESULT CALLBACK WinProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)  
{  
    switch(message)  
    {  
    case WM_CREATE:
		//run_lua(hwnd);
		//write_dxf();
		return 0;
    case WM_PAINT:  
		on_paint(hwnd);
		return 0;
    case WM_LBUTTONDOWN:  
		InvalidateRect(hwnd,NULL,TRUE);
		return 0;
    case WM_MOUSEMOVE:  
		if(wParam&MK_LBUTTON)
		{
			
		}
		return 0;
    case WM_CLOSE:  
        DestroyWindow(hwnd);  
        PostQuitMessage(0);  
        break;  
    default:  
        return DefWindowProc(hwnd,message,wParam,lParam);  
    }  
	
	
	
    return 0;  
}  
//���������  
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR szCmdLine,int iCmdShow)  
{  
    TCHAR szname[]=TEXT("classname");  
    HWND hwnd;  
    MSG msg;  
    ZeroMemory(&msg,sizeof(msg));  
    WNDCLASS wndclass;  
    wndclass.style=CS_HREDRAW | CS_VREDRAW;  
    wndclass.lpfnWndProc=WinProc;  
    wndclass.cbClsExtra=0;  
    wndclass.cbWndExtra=0;  
    wndclass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);  
    wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);  
    wndclass.hIcon=LoadIcon(NULL,IDI_APPLICATION);  
    wndclass.hInstance=hInstance;  
    wndclass.lpszClassName=szname;  
    wndclass.lpszMenuName=NULL;  
    RegisterClass(&wndclass);//ע�ᴰ����  
    hwnd=CreateWindow(szname,TEXT("����"),WS_OVERLAPPEDWINDOW ,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);  
    if(hwnd)  
        ShowWindow(hwnd,SW_SHOW);  
    else  
    {  
        MessageBox(NULL,TEXT("��������ʧ�ܣ�"),TEXT("��ʾ"),MB_OK);  
        UnregisterClass(szname,hInstance);  
        return 1;  
    }  
    UpdateWindow(hwnd);  
      
    while(GetMessage(&msg,hwnd,0,0)>0)  
    {  
        TranslateMessage(&msg);  
        DispatchMessage(&msg);  
    }  
    UnregisterClass(szname,hInstance);  
    return msg.wParam;  
}  
