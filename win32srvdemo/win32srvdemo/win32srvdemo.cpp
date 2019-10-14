/*******************************************************************************
 ����֧�֣�zyy6569@163.com
 ��    ����15927557560
 QQȺ    ��376440003
 ���˳н�Labview��MFC����λ����Ŀ Ƕ��ʽ�����Ŀ VLC��Ŀ 
 1588Э����Ŀ Marvell6095F/broadcom53262 Switch��Ŀ ��ӭ����������ѯ��
 CAN/485/��̫��ת���豸�����ڷ����� ����http://xstrive.taobao.com
 ��˾��ַ��www.xstrive.com
 Ѹ˼ά�Ƽ���Ȩ����
*******************************************************************************/


#include "stdafx.h"
#include "Windows.h"

#define SERVICE_NAME "srv_demo"

SERVICE_STATUS ServiceStatus;
SERVICE_STATUS_HANDLE hServiceStatusHandle;
void WINAPI service_main(int argc, char** argv); 
void WINAPI ServiceHandler(DWORD fdwControl);

TCHAR szSvcName[80];
SC_HANDLE schSCManager;
SC_HANDLE schService;
int uaquit;
FILE* log;

DWORD WINAPI srv_core_thread(LPVOID para)
{   
int i = 0;
for(;;)
{
	if(uaquit)
	{
		break; 
	}
	fprintf(log,"srv_core_thread run time count:%d\n",i++);
	Sleep(5000); 
}    
   return NULL; 
}   


void WINAPI ServiceHandler(DWORD fdwControl)
{
switch(fdwControl) 
{
	case SERVICE_CONTROL_STOP:
	case SERVICE_CONTROL_SHUTDOWN:
	ServiceStatus.dwWin32ExitCode = 0; 
	ServiceStatus.dwCurrentState  = SERVICE_STOPPED; 
	ServiceStatus.dwCheckPoint    = 0; 
	ServiceStatus.dwWaitHint      = 0;
	uaquit= 1;
	//add you quit code here
	if(log != NULL)
	fclose(log);
	break; 
	default:
		return;	
	};
	if (!SetServiceStatus(hServiceStatusHandle,  &ServiceStatus)) 
	{ 
		DWORD nError = GetLastError();
	} 
}

  
void WINAPI service_main(int argc, char** argv) 
{       
    ServiceStatus.dwServiceType        = SERVICE_WIN32; 
    ServiceStatus.dwCurrentState       = SERVICE_START_PENDING; 
    ServiceStatus.dwControlsAccepted   = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN | SERVICE_ACCEPT_PAUSE_CONTINUE; 
    ServiceStatus.dwWin32ExitCode      = 0; 
    ServiceStatus.dwServiceSpecificExitCode = 0; 
    ServiceStatus.dwCheckPoint         = 0; 
    ServiceStatus.dwWaitHint           = 0;  
    hServiceStatusHandle = RegisterServiceCtrlHandler(_T(SERVICE_NAME), ServiceHandler); 
    if (hServiceStatusHandle==0) 
    {
		DWORD nError = GetLastError();
    }  
	//add your init code here
	log = fopen("d:\\test.txt","w");
	//add your service thread here
	HANDLE task_handle = CreateThread(NULL,NULL,srv_core_thread,NULL,NULL,NULL);
	if(task_handle == NULL)
	{
		fprintf(log,"create srv_core_thread failed\n");
	}
	
    // Initialization complete - report running status 
    ServiceStatus.dwCurrentState       = SERVICE_RUNNING; 
    ServiceStatus.dwCheckPoint         = 0; 
    ServiceStatus.dwWaitHint           = 9000;  
    if(!SetServiceStatus(hServiceStatusHandle, &ServiceStatus)) 
    { 
		DWORD nError = GetLastError();
    } 
 
} 
//do not change main function
int main (int argc, const char *argv[])
{
    SERVICE_TABLE_ENTRY ServiceTable[2];
    
    ServiceTable[0].lpServiceName = _T(SERVICE_NAME);
    ServiceTable[0].lpServiceProc = (LPSERVICE_MAIN_FUNCTION)service_main;
    
    ServiceTable[1].lpServiceName = NULL;
    ServiceTable[1].lpServiceProc = NULL;
    // ��������Ŀ��Ʒ��ɻ��߳�
    StartServiceCtrlDispatcher(ServiceTable); 
    return 0;
}

