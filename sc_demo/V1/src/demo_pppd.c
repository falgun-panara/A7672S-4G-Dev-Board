/**
  ******************************************************************************
  * @file    demo_loc.c
  * @author  SIMCom OpenSDK Team
  * @brief   Source file of location feature from LBS.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 SIMCom Wireless.
  * All rights reserved.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "simcom_os.h"
#include "simcom_pppd.h"
#include "simcom_common.h"
#include "simcom_debug.h"

#include "simcom_uart.h"
#include "uart_api.h"


extern sMsgQRef SC_PppResp_msgq;
extern sMsgQRef SC_PppSend_msgq;
sTaskRef sc_PppsendTask;
static uint8_t sc_PppsendStack[SC_DEFAULT_THREAD_STACKSIZE];

extern void PrintfOptionMenu(char *options_list[], int array_size);
extern void PrintfResp(char *format);
void ppp_sendtask(void *arg)
{

    SIM_MSG_T uartMsg = {0,0,0,NULL};
    while(1)
    {
        if(sAPI_MsgQRecv(SC_PppSend_msgq,&uartMsg,SC_SUSPEND) != SC_SUCCESS)
            continue;
        if(strstr(uartMsg.arg3,"NO CARRIER"))
            PrintfResp("\r\nNO CARRIER\r\n");
        else if(uartMsg.arg3)
        {
            sAPI_UartWrite(SC_UART, uartMsg.arg3, uartMsg.arg2);
            if(uartMsg.arg3)
                sAPI_Free(uartMsg.arg3);
        }
    }
}
void PppdDemo(void)
{

    UINT32 opt = 0;
    SC_STATUS status;

    char *note =
        "\r\nPlease select an option to test from the items listed below.\r\n";
    char *options_list[] =
    {
        "1. Dial start",
        "2. Get dial status",
        "3. Get dial statics",
        "4. Dial stop",
        "99. back",
    };
    while (1)
    {
        PrintfResp(note);
        PrintfOptionMenu(options_list, sizeof(options_list) / sizeof(options_list[0]));
        opt = UartReadValue();
        if (SC_PppResp_msgq == NULL)
        {
            status = sAPI_MsgQCreate(&SC_PppResp_msgq, "SC_PppResp_msgq", (sizeof(SIM_MSG_T)), 4, SC_FIFO);
            if (SC_SUCCESS != status)
            {
                sAPI_Debug("osaStatus = [%d],create recvmsg error!", status);
            }
        }
        if (SC_PppSend_msgq == NULL)
        {
            status = sAPI_MsgQCreate(&SC_PppSend_msgq, "SC_PppSend_msgq", (sizeof(SIM_MSG_T)), 4, SC_FIFO);
            if (SC_SUCCESS != status)
            {
                sAPI_Debug("osaStatus = [%d],create sendmsg error!", status);
            }
        }
        if (sc_PppsendTask == NULL)
        {
            status = sAPI_TaskCreate(&sc_PppsendTask,sc_PppsendStack,SC_DEFAULT_THREAD_STACKSIZE,SC_DEFAULT_TASK_PRIORITY,"sc_PppTask",ppp_sendtask,(void *)0);
        }


        switch (opt)
        {
             
            case SC_DIAL_START:
            {
                char *resp = NULL;
                char path[200] = {0};
                DialResultE dialstate = DIAL_RESULT_SUCCESS;
                resp = "\r\nATD*99#\r\n";
                sAPI_UartWrite(SC_UART, (UINT8 *)resp, strlen(resp));
                dialstate = sAPI_DialStart(SC_PppResp_msgq,SC_PppSend_msgq,DIAL_TYPE_PPP);
                if(dialstate == 0)
                    PrintfResp("\r\nDIAL is OK\r\n");
                else 
                {
                    if(dialstate == DIAL_RESULT_PAPFAIL || dialstate == DIAL_RESULT_CHAPFAIL)
                        snprintf(path, sizeof(path), "\r\nDIAL is FAIL, reason: %d,need set usbername and password,then redial.\r\n",dialstate);
                    else if(dialstate == DIAL_RESULT_IPCPFAIL)
                        snprintf(path, sizeof(path), "\r\nDIAL is FAIL, reason: %d,need set apn and active,then redial.\r\n",dialstate);
                    else if(dialstate == DIAL_RESULT_DIALING)
                        snprintf(path, sizeof(path), "\r\nDIAL is in progress. Please wait until the dial is complete. reason: %d.\r\n",dialstate);
                    else
                        snprintf(path, sizeof(path), "\r\nDIAL is FAIL, reason: %d, Please redial again\r\n",dialstate);
                    PrintfResp(path);
                }
                    
                break;
            }
            case SC_DIAL_STATUS:
            {
                DialStateE status;
                status = sAPI_GetDialStatus();
                if(status == DIAL_STATE_CONNECTED)
                    PrintfResp("\r\nDIAL current status is CONNECTED\r\n");
                else if(status == DIAL_STATE_NONE)
                    PrintfResp("\r\nDIAL current status is DISCONNECTED\r\n");
                else
                    PrintfResp("\r\nDIAL current status is CONNECTING\r\n");

                break;
            }
            case SC_DIAL_STATICS:
            {
                unsigned long long  downcnt = 0;
                unsigned long long  upcnt = 0;
                char path[200] = {0};
                sAPI_GetDialCount(&downcnt, &upcnt);
                snprintf(path, sizeof(path), "\r\nDIAL current downcnt:%lld,upcnt:%lld\r\n",downcnt,upcnt);
                PrintfResp(path);
                break;
            }
            case SC_DIAL_STOP:
            {
                sAPI_DialStop();
                break;
            }

            case SC_PPPD_DEMO_MAX:
            {
                return;
            }

            default :
                break;
        }
    }
}

