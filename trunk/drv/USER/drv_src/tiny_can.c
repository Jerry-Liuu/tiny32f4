
#include <stdlib.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "tiny_can.h"
#include "bsp_sys.h"

#define SPRINTF(a) log_e a

#define TINY_LOG    		    1
#define	CAN_MODE_LOOP_BACK		0
#define	CAN_SEND_DATA			1
#define CAN_GET_BOARD_INFO		1
#define CAN_READ_DATA			1
#define CAN_CALLBACK_READ_DATA	1
#define	CAN_INIT_EX				1
#define CAN_GET_STATUS			1

#define CAN_DATA_SEND_FRAME_COUNT 10

CAN_BaudRate  CAN_BaudRateInitTab[]= {     
{1000,1,2,4,6},      // 1M (1000K)
{900,1,16,6,2},      // 900K
{800,1,5,7,4},       // 800K
{666,1,12,8,3},      // 666K
{600,1,5,4,7},       // 600K
{500,1,7,6,6},       // 500K
{400,1,7,7,7},       // 400K
{300,1,8,5,10},      // 300K
{250,1,8,5,12},      // 250K
{225,1,13,3,11},     // 225K
{200,1,5,8,15},      // 200K
{160,1,9,1,24},      // 160K
{150,1,6,3,28},      // 150K
{144,1,7,2,29},      // 144K
{125,1,4,3,42},      // 125K
{120,1,3,3,50},      // 120K
{100,1,6,5,35},      // 100K
{90,1,4,7,39},       // 90K
{80,1,16,4,25},      // 80K
{75,1,8,1,56},       // 75K
{60,1,5,1,100},      // 60K
{50,1,6,1,105},      // 50K
{40,1,7,2,105},      // 40K
{30,1,11,2,100},     // 30K
{20,1,9,2,175},      // 20K
};

int SetBaudRate(int baudrate, CAN_INIT_CONFIG_EX *config_ex)
{
	int i, ret=0; 
	for(i=0; i<sizeof(CAN_BaudRateInitTab); i++)
	{
		if(CAN_BaudRateInitTab[i].BAUD_RATE == baudrate)
		{
			config_ex->CAN_SJW = CAN_BaudRateInitTab[i].SJW;
			config_ex->CAN_BS1 = CAN_BaudRateInitTab[i].BS1;
			config_ex->CAN_BS2 = CAN_BaudRateInitTab[i].BS2;
			config_ex->CAN_BRP = CAN_BaudRateInitTab[i].PreScale;
		    SPRINTF(("Set Baud Rate = %d Khz\n", baudrate));
			ret = 1; 
			break;
		}
	}
	return ret; 
}

#if CAN_CALLBACK_READ_DATA
void  GetDataCallback(uint32_t CANIndex,uint32_t Len)
{
	int ReadDataNum;
	static int data_num = 0;
	data_num++;
	SPRINTF(("data_num = %d\n\n", data_num));
	int DataNum = tinyGetReceiveNumCAN(CANIndex);
	CAN_OBJ	*pCAN_ReceiveData = (CAN_OBJ *)malloc(DataNum*sizeof(CAN_OBJ));
    if((DataNum > 0)&&(pCAN_ReceiveData != 0)){
        ReadDataNum = tinyReceiveCAN(CANIndex, pCAN_ReceiveData, DataNum,0);
        for (int i = 0; i < ReadDataNum; i++)
        {
			SPRINTF(("\n"));
		    SPRINTF(("CAN_CALLBACK_READ_DATA\n"));
            SPRINTF(("--CAN_ReceiveData.RemoteFlag = %d\n",pCAN_ReceiveData[i].RemoteFlag));
            SPRINTF(("--CAN_ReceiveData.ExternFlag = %d\n",pCAN_ReceiveData[i].ExternFlag));
            SPRINTF(("--CAN_ReceiveData.ID = 0x%X\n",pCAN_ReceiveData[i].ID));
            SPRINTF(("--CAN_ReceiveData.DataLen = %d\n",pCAN_ReceiveData[i].DataLen));
            SPRINTF(("--CAN_ReceiveData.Data:"));
            for(int j=0;j<pCAN_ReceiveData[i].DataLen;j++){
                SPRINTF(("%02X ",pCAN_ReceiveData[i].Data[j]));
            }
            SPRINTF(("\n"));
            SPRINTF(("--CAN_ReceiveData.TimeStamp = %d\n\n",pCAN_ReceiveData[i].TimeStamp));
        }
    }
	free(pCAN_ReceiveData);
}
#endif

int tiny_CAN_TEST(void)
{
    int Status, i;  
	int canIndex = 0; 
#if CAN_INIT_EX
	CAN_INIT_CONFIG_EX	CAN_InitEx;
    CAN_InitEx.CAN_ABOM = 0;
#if CAN_MODE_LOOP_BACK
    CAN_InitEx.CAN_Mode = 1;
#else
    CAN_InitEx.CAN_Mode = 0;
#endif
	SetBaudRate(1000, &CAN_InitEx); 
    CAN_InitEx.CAN_NART = 1;
    CAN_InitEx.CAN_RFLM = 0;
    CAN_InitEx.CAN_TXFP = 1;
	CAN_InitEx.CAN_RELAY = 0;
    
    Status = tinyInitExCAN(canIndex,&CAN_InitEx);
#if TINY_LOG
    SPRINTF(("\n****************************\n"));
    SPRINTF(("CANConfig.CAN_ABOM %d:\n", CAN_InitEx.CAN_ABOM));
    SPRINTF(("CANConfig.CAN_BRP: %d \n",CAN_InitEx.CAN_BRP));
    SPRINTF(("CANConfig.CAN_BS1:%d\n",CAN_InitEx.CAN_BS1));
    SPRINTF(("CANConfig.CAN_BS2: %d\n ",CAN_InitEx.CAN_BS2));
    SPRINTF(("CANConfig.CAN_Mode: %d\n",CAN_InitEx.CAN_Mode));
    SPRINTF(("CANConfig.CAN_NART: %d\n ",CAN_InitEx.CAN_NART));
    SPRINTF(("CANConfig.CAN_RELAY: %d\n ",CAN_InitEx.CAN_RELAY));
    SPRINTF(("CANConfig.CAN_RFLM: %d\n ",CAN_InitEx.CAN_RFLM));
    SPRINTF(("CANConfig.CAN_SJW: %d\n ",CAN_InitEx.CAN_SJW));
    SPRINTF(("CANConfig.CAN_TXFP: %d\n ",CAN_InitEx.CAN_TXFP));
#endif
	if(Status==0){
        SPRINTF(("Init device failed!\n"));
        return 0;
    }else{
        SPRINTF(("Init device success!\n"));
    }
    
	CAN_FILTER_CONFIG CAN_FilterConfig;
    
    CAN_FilterConfig.FilterIndex = 0;
    CAN_FilterConfig.Enable = 1;		
    CAN_FilterConfig.ExtFrame = 0;
    CAN_FilterConfig.FilterMode = 0;
    CAN_FilterConfig.ID_IDE = 0;
    CAN_FilterConfig.ID_RTR = 0;
    CAN_FilterConfig.ID_Std_Ext = 0;
    CAN_FilterConfig.MASK_IDE = 0;
    CAN_FilterConfig.MASK_RTR = 0;
    CAN_FilterConfig.MASK_Std_Ext = 0;
    
    Status = tinySetFilterCAN(canIndex,&CAN_FilterConfig);
	for(i=1; i<=13; i++)
	{
        CAN_FilterConfig.FilterIndex = i;
        Status = tinySetFilterCAN(canIndex,&CAN_FilterConfig);
	}
    if(Status==0){
        SPRINTF(("Set filter failed!\n"));
        return 0;
    }else{
        SPRINTF(("Set filter success!\n"));
    }
#else
	CAN_INIT_CONFIG	CAN_Init;
    //Config device
	CAN_Init.AccCode = 0x00000000;
	CAN_Init.AccMask = 0xFFFFFFFF;
	CAN_Init.Filter = 1;
	CAN_Init.Mode = 0;
	CAN_Init.Timing0 = 0x00;
	CAN_Init.Timing1 = 0x14;
    Status = tinyInitCAN(0,&CAN_Init);
    if(Status==STATUS_ERR){
        SPRINTF(("Init device failed!\n"));
        return 0;
    }else{
        SPRINTF(("Init device success!\n"));
    }
#endif
    
#if CAN_CALLBACK_READ_DATA
	tinyRegisterReceiveCallbackCAN(GetDataCallback);
#endif
    Status = tinyStartCAN(canIndex);
    if(Status==0){
        SPRINTF(("Start CAN failed!\n"));
        return 0;
    }else{
        SPRINTF(("Start CAN success!\n"));
    }
#if CAN_SEND_DATA
	CAN_OBJ	CAN_SendData[CAN_DATA_SEND_FRAME_COUNT];
	for(int j=0;j<CAN_DATA_SEND_FRAME_COUNT;j++){
		CAN_SendData[j].DataLen = 8;
		for(int i=0;i<CAN_SendData[j].DataLen;i++){
			CAN_SendData[j].Data[i] = i+j*10;
		}
		CAN_SendData[j].ExternFlag = 0;
		CAN_SendData[j].RemoteFlag = 0;
		CAN_SendData[j].ID = 0x155+j;
#if CAN_MODE_LOOP_BACK
		CAN_SendData[j].SendType = 2;
#else
		CAN_SendData[j].SendType = 0;
#endif
    }
    Status = tinyTransmitCAN(canIndex,CAN_SendData,CAN_DATA_SEND_FRAME_COUNT);
    if(Status==0){
        SPRINTF(("Send CAN data failed!\n"));
        tinyResetCAN(0);
    }else{
        SPRINTF(("Send CAN data success!\n"));
    }
#endif//CAN_SEND_DATA

#ifndef OS_LINUX
    Sleep(10);
#else
	sleep(0.01);
#endif
#if CAN_GET_STATUS
    CAN_STATUS CAN_Status;
    Status = tinyReadStatusCAN(canIndex, &CAN_Status);
    if (Status == 0)
    {
        SPRINTF(("Get CAN status failed!\n"));
        return 1;
    }else{
        SPRINTF(("Buffer Size : %d\n",CAN_Status.BufferSize));
        SPRINTF(("ESR : 0x%08X\n" ,CAN_Status.regESR));
        SPRINTF(("------Error warning flag : %d\n" ,((CAN_Status.regESR>>0)&0x01)));
        SPRINTF(("------Error passive flag : %d\n" , ((CAN_Status.regESR >> 1) & 0x01)));
        SPRINTF(("------Bus-off flag : %d\n" , ((CAN_Status.regESR >> 2) & 0x01)));
        SPRINTF(("------Last error code(%d) : ",(CAN_Status.regESR>>4)&0x07));
        switch ((CAN_Status.regESR>>4)&0x07)
        {
            case 0:
                SPRINTF(("No Error\n"));
                break;
            case 1:
                SPRINTF(("Stuff Error\n"));
                break;
            case 2:
                SPRINTF(("Form Error\n"));
                break;
            case 3:
                SPRINTF(("Acknowledgment Error\n"));
                break;
            case 4:
                SPRINTF(("Bit recessive Error\n"));
                break;
            case 5:
                SPRINTF(("Bit dominant Error\n"));
                break;
            case 6:
                SPRINTF(("CRC Error\n"));
                break;
            case 7:
                SPRINTF(("Set by software\n"));
                break;
            default:
                break;
        }
        SPRINTF(("------Transmit error counter : %d\n" , ((CAN_Status.regESR >> 16) & 0xFF)));
        SPRINTF(("------Receive error counter : %d\n" , ((CAN_Status.regESR >> 24) & 0xFF)));
        SPRINTF(("TSR : 0x%08X\n" , CAN_Status.regTSR));

    }
#endif
            
#if CAN_READ_DATA
	while(1){
#if !CAN_CALLBACK_READ_DATA
		int ReadDataNum;
		int DataNum = VCI_GetReceiveNum(VCI_USBCAN2, 0, 0);
		VCI_CAN_OBJ	*pCAN_ReceiveData = (VCI_CAN_OBJ *)malloc(DataNum*sizeof(VCI_CAN_OBJ));
		if((DataNum > 0)&&(pCAN_ReceiveData != NULL)){
			ReadDataNum = VCI_Receive(VCI_USBCAN2, 0, 0, pCAN_ReceiveData, DataNum);
			for (int i = 0; i < ReadDataNum; i++)
			{
				SPRINTF(("\n");
				SPRINTF(("CAN_READ_DATA£º\n"));
				SPRINTF(("--CAN_ReceiveData.RemoteFlag = %d\n",pCAN_ReceiveData[i].RemoteFlag));
				SPRINTF(("--CAN_ReceiveData.ExternFlag = %d\n",pCAN_ReceiveData[i].ExternFlag));
				SPRINTF(("--CAN_ReceiveData.ID = 0x%X\n",pCAN_ReceiveData[i].ID));
				SPRINTF(("--CAN_ReceiveData.DataLen = %d\n",pCAN_ReceiveData[i].DataLen));
				SPRINTF(("--CAN_ReceiveData.Data:"));
				for(int j=0;j<pCAN_ReceiveData[i].DataLen;j++){
					SPRINTF(("%02X ",pCAN_ReceiveData[i].Data[j]));
				}
				SPRINTF(("\n"));
				SPRINTF(("--CAN_ReceiveData.TimeStamp = %d\n\n",pCAN_ReceiveData[i].TimeStamp));
			}
		}
		free(pCAN_ReceiveData);
#endif 
	}
#endif
    while(getchar()!='\n');
#if CAN_CALLBACK_READ_DATA
	tinyLogoutReceiveCallbackCAN();
	SPRINTF(("VCI_LogoutReceiveCallback\n"));
#endif
	Sleep(10);
	//Stop receive can data
	Status = tinyResetCAN(0);
	SPRINTF(("VCI_ResetCAN %d\n",Status));
    return 0;
}
