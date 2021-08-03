/*

testbed.cpp

Blake Troutman 2018

Driver for testing controller architecture.

*/


#include <iostream>


#include "WindowsController.h"
#include "dik.h"

#include <setupapi.h>
DEFINE_GUID(GUID_DEVINTERFACE_SCPVBUS, 0xf679f562, 0x3164, 0x42ce, 0xa4, 0xdb, 0xe7, 0xdd, 0xbe, 0x72, 0x39, 0x9);


//key press tests
void testKeyPress() {
	
	std::cout << "Starting testKeyPress." << std::endl;
	
	Controller * ctrl = new WindowsController();
	Sleep(2000);
	ctrl->pressKey(DIK_H);
	ctrl->pressKey(DIK_E);
	ctrl->pressKey(DIK_L);
	ctrl->pressKey(DIK_L);
	ctrl->pressKey(DIK_O);
	ctrl->pressKey(DIK_SPACE);
	ctrl->pressKey(DIK_T);
	ctrl->pressKey(DIK_H);
	ctrl->pressKey(DIK_E);
	ctrl->pressKey(DIK_R);
	ctrl->pressKey(DIK_E);
	Sleep(2000);
	ctrl->releaseKey(DIK_H);
	ctrl->releaseKey(DIK_E);
	ctrl->releaseKey(DIK_L);
	ctrl->releaseKey(DIK_L);
	ctrl->releaseKey(DIK_O);
	ctrl->releaseKey(DIK_SPACE);
	ctrl->releaseKey(DIK_T);
	ctrl->releaseKey(DIK_H);
	ctrl->releaseKey(DIK_E);
	ctrl->releaseKey(DIK_R);
	ctrl->releaseKey(DIK_E);
	delete ctrl;
	
	std::cout << "testKeyPress complete." << std::endl;
	
}

//test mouse functionality
void testMouseMove() {
	
	std::cout << "Starting testMouseMove." << std::endl;
	
	Controller * ctrl = new WindowsController();
	Sleep(2000);
	ctrl->moveMouse(400, 100);
	Sleep(2000);
	ctrl->moveMouseTo(5000, 5000);
	delete ctrl;
	
	std::cout << "testMouseMove complete." << std::endl;
	
}

//test mouse clicking
void testMouseClick() {

	std::cout << "Starting testMouseClick." << std::endl;
	
	Controller * ctrl = new WindowsController();
	
	int numClicks = 10;
	Sleep(2000);
	
	for(int i = 0; i < numClicks; i++) {
		ctrl->clickMouse();
		Sleep(10);
		ctrl->releaseMouse();
		Sleep(20);
	}
		
	delete ctrl;
	
	std::cout << "testMouseClick complete." << std::endl;
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// library code

int GetVXbusPath(LPCTSTR path, UINT size)
{
	SP_DEVICE_INTERFACE_DATA deviceInterfaceData = {};
	deviceInterfaceData.cbSize = sizeof(deviceInterfaceData);
	// GUID deviceClassGuid = { 0xF679F562, 0x3164, 0x42CE,{ 0xA4, 0xDB, 0xE7 ,0xDD ,0xBE ,0x72 ,0x39 ,0x09 } };
	GUID deviceClassGuid = GUID_DEVINTERFACE_SCPVBUS;
	DWORD memberIndex = 0;
	DWORD requiredSize = 0;

	WINSETUPAPI HDEVINFO deviceInfoSet = SetupDiGetClassDevs(&deviceClassGuid, nullptr, nullptr, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

	if (SetupDiEnumDeviceInterfaces(deviceInfoSet, nullptr, &deviceClassGuid, memberIndex, &deviceInterfaceData))
	{
		// get required target buffer size
		SetupDiGetDeviceInterfaceDetail(deviceInfoSet, &deviceInterfaceData, nullptr, 0, &requiredSize, nullptr);

		// allocate target buffer
		auto detailDataBuffer = static_cast<PSP_DEVICE_INTERFACE_DETAIL_DATA>(malloc(requiredSize));
		if (detailDataBuffer == NULL)
			return -1;
		detailDataBuffer->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

		// get detail buffer
		if (!SetupDiGetDeviceInterfaceDetail(deviceInfoSet, &deviceInterfaceData, detailDataBuffer, requiredSize, &requiredSize, nullptr))
		{
			SetupDiDestroyDeviceInfoList(deviceInfoSet);
			free(detailDataBuffer);
			return -1;
		}

		// Copy	the path to output buffer
		memcpy((void *)path, detailDataBuffer->DevicePath, requiredSize*sizeof(WCHAR));

		// Cleanup
		SetupDiDestroyDeviceInfoList(deviceInfoSet);
		free(detailDataBuffer);
	}
	else
		return -1;

	return requiredSize;
}

HANDLE GetVXbusHandle(void)
{
	TCHAR path[MAX_PATH];

	int n = GetVXbusPath(path, MAX_PATH);

	if (n<1)
		return INVALID_HANDLE_VALUE;

	// bus found, open it and obtain handle
	g_hBus = CreateFile(path,
								 GENERIC_READ | GENERIC_WRITE,
								 FILE_SHARE_READ | FILE_SHARE_WRITE,
								 nullptr,
								 OPEN_EXISTING,
								 FILE_ATTRIBUTE_NORMAL,
								 nullptr);
	return g_hBus;
}

// test custom input types
void testControllerInput() {
	std::cout << "Starting testControllerInput." << std::endl;
	
	Sleep(5000);
	
	DeviceIoControl(g_hBus, IOCTL_BUSENUM_REPORT_HARDWARE, buffer, _countof(buffer), output, FEEDBACK_BUFFER_LENGTH, &trasfered, nullptr);

	std::cout << "testControllerInput complete." << std::endl;
}

int main(int argc, char ** argv) {
	
	std::cout << "Starting main scope." << std::endl;
	//testKeyPress();
	//testMouseMove();
	//testMouseClick();
	testControllerInput();
	std::cout << "Ending main scope." << std::endl;
	return 0;
	
}
