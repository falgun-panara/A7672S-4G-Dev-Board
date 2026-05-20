/**
  ******************************************************************************
  * @file    simcom_bt.h
  * @author  SIMCom OpenSDK Team
  * @brief   Header file of BT.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 SIMCom Wireless.
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef __SIMCOM_BT_STACK_H__
#define __SIMCOM_BT_STACK_H__

#include "simcom_os.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define SC_BT_NAME_MAX                       248
#define SC_BT_PHONE_NUMBER_MAX               25
#define SC_BT_DEVICE_RECORD_MAX              10
#define SC_BT_OBEX_FILE_NAME                 256
#define SC_BT_OBEX_FILE_TYPE_SIZE            32
#define SC_BT_OBEX_FRAME_SIZE                (8087 - SC_BT_OBEX_FILE_TYPE_SIZE - SC_BT_OBEX_FILE_NAME - 5)

//adv type
#define SC_BLE_ADV_TYPE_IND                  0x00
#define SC_BLE_ADV_TYPE_DIRECT_IND           0x01
#define SC_BLE_ADV_TYPE_SCAN_IND             0x02
#define SC_BLE_ADV_TYPE_NONCONN_IND          0x03
#define SC_BLE_ADV_TYPE_DIRECT_IND_LOW_DUTY  0x04

//address type
#define SC_BLE_ADDRESS_TYPE_PUBLIC           0x00
#define SC_BLE_ADDRESS_TYPE_RANDOM           0x01

//scan type
#define SC_BLE_PASSIVE_SCAN                           0x00
#define SC_BLE_ACTIVE_SCAN                            0x01

//gap type
#define SC_BLE_GAP_TYPE_FLAGS                         0x01
#define SC_BLE_GAP_TYPE_INCOMPLETE_SERVICE_16BIT_LIST 0x02
#define SC_BLE_GAP_TYPE_COMPLETE_SERVICE_LIST         0x03
#define SC_BLE_GAP_TYPE_SHORT_NAME                    0x08
#define SC_BLE_GAP_TYPE_COMPLETE_NAME                 0x09
#define SC_BLE_GAP_TYPE_TX_POWER                      0x0A
#define SC_BLE_GAP_TYPE_SERVICE_DATA                  0x16
#define SC_BLE_GAP_TYPE_APPEARANCE                    0x19
#define SC_BLE_GAP_TYPE_SPECIFIC_DATA                 0xFF

#define SC_BLE_ATT_CHARC_PROP_READ          0x02
#define SC_BLE_ATT_CHARC_PROP_WWP           0x04
#define SC_BLE_ATT_CHARC_PROP_WRITE         0x08
#define SC_BLE_ATT_CHARC_PROP_NOTIFY        0x10
#define SC_BLE_ATT_CHARC_PROP_INDICATE      0x20


typedef void (*sc_pair_result_callback)(unsigned char result, unsigned char reason);

typedef unsigned short (*sc_att_read_callback)(unsigned short con_handle, unsigned short attribute_handle,
        unsigned short offset, unsigned char *buffer, unsigned short buffer_size);

typedef int (*sc_att_write_callback)(unsigned short con_handle, unsigned short attribute_handle,
                                     unsigned short transaction_mode, unsigned short offset, unsigned char *buffer,
                                     unsigned short buffer_size);
#ifdef CUS_DRIVER_BT
typedef enum
{
    SC_BT_UART1 = 1,
    //SC_BT_UART2 = 0,
    //SC_BT_UART3 = 3,
    SC_BT_UART4 = 4,
} SC_BLE_UART_ID;

typedef enum
{
    BT_UART_BAUDRATE_115200 = 115200,
    BT_UART_BAUDRATE_921600 = 921600,
    BT_UART_BAUDRATE_3000000 = 3000000,
} SC_BLE_UART_BAUDRATE;

typedef struct
{
    SC_BLE_UART_ID id;
    SC_BLE_UART_BAUDRATE baudrate;
} SC_BLE_UART_CFG_T;

typedef struct
{
    unsigned int        host_wakeup_bt;/* config host_wakeup_bt pin */
    unsigned int        bt_wakeup_host;/* config bt_wakeup_host pin */
    unsigned int        bt_rst;/* config bt_reset pin */
    unsigned int        bt_pwdn;/* config bt_ldo_en pin */
    SC_BLE_UART_CFG_T   uart_id;
    SC_BLE_UART_CFG_T   uart_baudrate;
} SC_BLE_DEV_CFG_T;
#endif

typedef enum
{
    SC_BT_BR = 0,
    SC_BT_BR_LE,
    SC_BT_LE,
    SC_BT_MAX,
} SC_BT_MODE_T;

typedef enum
{
    SC_BT_IO_DISPLAYONLY = 0,
    SC_BT_IO_DISPLAYTESNO,
    SC_BT_IO_KEYBOARDONLY,
    SC_BT_IO_NOINPUTNOOUTPUT,
} SC_BT_IOCAP_T;

typedef enum
{
    SC_BT_PAIR_MODE_JUST_WORK_MODE,
    SC_BT_PAIR_MODE_NUMERIC_COMPARISON_MODE,
    SC_BT_PAIR_MODE_PASSKEY_ENTRY_MODE,
    SC_BT_PAIR_MODE_PIN_CODE,
} SC_BT_PAIR_MODE_T;

typedef enum
{
    SC_BT_EVENT_TYPE_COMMON,
    SC_BT_EVENT_TYPE_ACL,
    SC_BT_EVENT_TYPE_SCO,
    SC_BT_EVENT_TYPE_A2DP,
    SC_BT_EVENT_TYPE_AVRCP,
    SC_BT_EVENT_TYPE_HFP,
    SC_BT_EVENT_TYPE_OBEX,
    SC_BT_EVENT_TYPE_SPP,
    SC_BT_EVENT_TYPE_LE,
    SC_BT_EVENT_TYPE_A2DP_SINK,
    SC_BT_EVENT_TYPE_HFP_HF,
    SC_BT_EVENT_TYPE_HID,
    SC_BT_EVENT_TYPE_PBAP,
    SC_BT_EVENT_TYPE_MAP,
    SC_BT_EVENT_TYPE_FTP,
} SC_EVENT_TYPE_T;

typedef enum
{
    SC_COMMON_INQUIRY_RESULT,
    SC_COMMON_INQUIRY_COMPLETE,
    SC_COMMON_PAIRING_REQUEST,
    SC_COMMON_PAIRED,
    SC_COMMON_PIN_REQUEST,
    SC_COMMON_USER_PASSKEY_NOTIFICATION,
    SC_COMMON_USER_PASSKEY_REQUEST,
    SC_COMMON_POWERUP_COMPLETE,
    SC_COMMON_POWERUP_FAILED,
    SC_COMMON_SHUTDOWN_COMPLETE,
    SC_COMMON_BTFIRMWARE_ASSERT,
    SC_COMMON_HCI_COMPLETE_EVENT,
    SC_COMMON_NULL, // message was eaten by upper layer
    SC_COMMON_NAME,
    SC_COMMON_RSSI,
    SC_COMMON_TEMPERATURE_CHECK,
    SC_COMMON_PCM_MODE,
    SC_COMMON_BTRX_RESULT,
} SC_COMMON_EVENT_TYPE_T; // common define

typedef enum
{
    SC_ACL_CONNECTED,
    SC_ACL_DISCONNECTED,
    SC_ACL_CONNECT_FAILED,
} SC_ACL_EVENT_TYPE_T; // ACL define

typedef enum
{
    SC_A2DP_CONNECTED,
    SC_A2DP_MEIDA_CONNECTED,
    SC_A2DP_DISCONNECTED,
    SC_A2DP_START,
    SC_A2DP_MEDIA_SEND_COMPLETE,
    SC_REMOTE_SBC_CAPABILITIES,
    SC_A2DP_START_PRIVATE,
    SC_A2DP_MEDIA_MTU,
    SC_A2DP_SUSPEND,
    SC_A2DP_REJECTED,
} SC_A2DP_EVENT_TYPE_T; // a2dp define

typedef enum
{
    SC_A2DP_SINK_CONNECTED,
    SC_A2DP_SINK_MEIDA_CONNECTED,
    SC_A2DP_SINK_DISCONNECTED,
    SC_A2DP_SINK_REMOTE_SBC_CAPABILITIES,
    SC_A2DP_SINK_MEDIA_PAYLOAD,
    SC_A2DP_SINK_PLAY_STARTED,
    SC_A2DP_SINK_PLAY_SUSPENDED,
    SC_A2DP_SINK_PLAY_STOPPED,
} SC_A2DP_SINK_EVENT_TYPE_T; // a2dp sink define

typedef enum
{
    SC_AVRCP_CONNECTED,
    SC_AVRCP_DISCONNECTED,
    SC_AVRCP_KEY_PRESSED,
    SC_AVRCP_KEY_RELEASED,
} SC_AVRCP_EVENT_TYPE_T; // avrcp define

typedef enum
{
    SC_HFP_CONNECTION_REQUEST, // HF initate a connection to AG
    SC_HFP_CONNECTED, // connection complete, HF or AG initate this connection
    SC_HFP_DISCONNECTED,
    SC_HFP_ATA,
    SC_HFP_ATCHUP,
    SC_HFP_DIAL,
    SC_HFP_ATCHLD,
    SC_HFP_VOICE_RECOGNITION,
    SC_HFP_SPEAKER_VOLUME,
    SC_HFP_MICROPHONE_GAIN,
    SC_HFP_SDP_FAILED, // remote device not support HFP
    SC_HFP_CLCC,
    SC_HFP_RESPONSE_AND_HOLD,
} SC_HFP_EVENT_TYPE_T; // hfp ag define

typedef enum
{
    SC_BTBS_CALL_STATE_IDLE,
    SC_BTBS_CALL_STATE_DIALING,
    SC_BTBS_CALL_STATE_INCONING,
    SC_BTBS_CALL_STATE_ALERTING,
    SC_BTBS_CALL_STATE_WAITING,
    SC_BTBS_CALL_STATE_HELD, //5
    SC_BTBS_CALL_STATE_OUTGOING_CALL_ESTABLISHED,
    SC_BTBS_CALL_STATE_AG_ANSWER_INCOMING_CALL,
    SC_BTBS_CALL_STATE_AG_JOIN_HELD_CALL,
    SC_BTBS_CALL_STATE_OUTGOING_CALL_REJECTED,
    SC_BTBS_CALL_STATE_TERMINATE_CALL, //10
    SC_BTBS_CALL_STATE_DROP,
} SC_BTBS_CALL_STATE_T;

typedef enum
{
    SC_HFP_HF_CONNECTED, // connection complete, HF or AG initate this connection
    SC_HFP_HF_DISCONNECTED,
    SC_HFP_HF_SPEAKER_VOLUME,
    SC_HFP_HF_MICROPHONE_GAIN,
    SC_HFP_HF_RING,
    SC_HFP_HF_AG_INDICATOR_STATUS_CHANGED,
    SC_HFP_HF_NETWORK_OPERATOR_CHANGED,
    SC_HFP_HF_CLIP,
    SC_HFP_HF_CLCC,
} SC_HFP_HF_EVENT_TYPE_T; // hfp hf define

typedef enum
{
    SC_SPP_CONNECT_IND,
    SC_SPP_CONNECT_CNF,
    SC_SPP_DISCONNECT_IND,
    SC_SPP_DISCONNECT_CNF,
    SC_SPP_DATA_IND,
    SC_SPP_DATA_CNF,
    SC_SPP_FLOW_IND,
} SC_SPP_EVENT_TYPE_T; // SPP define

typedef enum
{
    SC_FTP_CLIENT_CONNECTED = 0,
    SC_FTP_CLIENT_DISCONNECTED,
    SC_FTP_CLIENT_PUT_CONTINUE = 3,
    SC_FTP_CLIENT_PKT_DATA,
    SC_FTP_CLIENT_OPERATION_COMPLETED,
} SC_BT_FTP_EVENT_T; //ftp

typedef enum
{
    SC_BLE_SCAN_EVENT,
    SC_BLE_GATT_CONNECTED,
    SC_BLE_GATT_DISCONNECTED,
    SC_BLE_MTU_EXCHANGED, // this indication means MTU be changed (no matter master or slave)
    SC_BLE_CLIENT_HANDLE_NOTIFY,
    SC_BLE_CLIENT_HANDLE_INDIATION,
    SC_BLE_WHITE_LIST_SIZE,
    SC_BLE_SMP_PASSKEY,
    SC_BLE_ADV_PHY_TXPOWER,
    SC_BLE_SLAVE_LE_BOND_COMPLETE, //slave role, bond

    // add for btstack
    SC_BLE_ATT_EVENT_CAN_SEND_NOW,
    SC_BLE_ATT_EVENT_CAN_WRITE_NOW,
    SC_BLE_IDENTITY_INFO,
    SC_BLE_DB_CONTROL_GET_INFO,
    SC_BLE_ATT_EVENT_READ_DATA_RESULT,
    SC_BLE_ATT_EVENT_READ_OVER_RESULT,
    SC_BLE_GATT_SCAN_RESULT,
    SC_BLE_GATT_SCAN_DUMP_SERVICE,
    SC_BLE_GATT_SCAN_DUMP_CHARACTERISTIC,
    SC_BLE_GATT_SCAN_DUMP_DESCRIPTOR,
    SC_BLE_CONNECTION_UPDATE_COMPLETE,
    SC_BLE_ATT_INDICATION_COMPLETE,
    SC_BLE_ENCRYPTION_CHANGE,
} SC_BLE_EVENT_TYPE_T; // le define

typedef enum
{
    SC_BLE_ADV_LEGACY_MODE = 0,
    SC_BLE_EXTENDED_ADV_LEGACY_MODE,
    SC_BLE_EXTENDED_ADV_AUX_MODE,
} SC_BLE_AVD_EVENT_TYPE_T; // le adv mode

#if 0
typedef enum
{
    PAL_BLE_ERR_OK = 0,
    PAL_BLE_ERR_INVALID_HANDLE,
    PAL_BLE_ERR_READ_NOT_PERMITTED,
    PAL_BLE_ERR_WRITE_NOT_PERMITTED,
    PAL_BLE_ERR_INVALID_PDU,
    PAL_BLE_ERR_INSUFFICIENT_AUTHEN,
    PAL_BLE_ERR_REQUEST_NOT_SUPPORT,
    PAL_BLE_ERR_INVALID_OFFSET,
    PAL_BLE_ERR_INSUFFICIENT_AUTHOR,
    PAL_BLE_ERR_PREPARE_QUEUE_FULL,
    PAL_BLE_ERR_ATTRIBUTE_NOT_FOUND,
    PAL_BLE_ERR_ATTRIBUTE_NOT_LONG,
    PAL_BLE_ERR_INSUFFICIENT_ENCRY_KEY,
    PAL_BLE_ERR_INVALID_ATTRIBUTE_VALUE,
    PAL_BLE_ERR_UNLIKELY_ERROR,
    PAL_BLE_ERR_INSUFFICIENT_ENCRY,
    PAL_BLE_ERR_UNSUPPORTED_GTOUP_TYPE,
    PAL_BLE_ERR_INSUFFICIENT_RESOURCES,
} PAL_BLE_ATT_ERROR_RESPONSE_T;

typedef enum
{
    PAL_BLE_RETURNCODE_OK,
    PAL_BLE_RETURNCODE_NOT_KNOW_ERROR,
    PAL_BLE_RETURNCODE_ALERT,
    PAL_BLE_RETURNCODE_PARAM_ERROR,
    PAL_BLE_RETURNCODE_OPEN_FAIL,
    PAL_BLE_RETURNCODE_MSGQ_ERROR,
} PAL_BLE_RETURNCODE_T;
#endif

typedef enum
{
    SC_BLE_ADV_DATA_TYPE_FLAG = 0x01,
    SC_BLE_ADV_DATA_TYPE_COMPLETE_SERVICE_LIST = 0x03,
    SC_BLE_ADV_DATA_TYPE_SHORT_NAME = 0x08,
    SC_BLE_ADV_DATA_TYPE_COMPLETE_NAME = 0x09,
    SC_BLE_ADV_DATA_TYPE_APPEARANCE = 0x19,
    SC_BLE_ADV_DATA_TYPE_SPECIFIC_DATA = 0xff,
} SC_BLE_ADV_DATATYPE_T;


typedef struct
{
    unsigned short int event_type;
    unsigned short int event_id;
    int payload_length;
    void *payload;
} SC_BT_TASK_EVENT_T;

typedef struct
{
    unsigned char bytes[6];
} SC_BT_ADDR_T;

typedef struct sc_bt_device_record
{
    char name[SC_BT_NAME_MAX];
    unsigned int cod;
    unsigned char addr[6];
    unsigned char linkkey[16];
    int linkkey_type;
    int hfp_volume;
    int a2dp_volume;
    struct sc_bt_device_record *next;
} SC_BT_DEVICE_RECORD_T;

/* command and event related define */
typedef struct
{
    int command_id;
    void (*execute_cb)(void *arg);
    int payload_length;
    void *payload;
} SC_BT_TASK_COMMAND_T;

/* ------------------------------- classic command struct define start ---------------------------*/
typedef struct
{
    unsigned char inquiry_length;
    unsigned char num_responses;
} SC_BT_TASK_INQUIRY_T;

typedef struct
{
    unsigned char addr[6];
    int accept;
} SC_BT_TASK_BONDING_ACCEPT_T;

typedef struct
{
    SC_BT_ADDR_T addr;
    char pin[64];
} SC_BT_TASK_PIN_REPLY_T;

typedef struct
{
    SC_BT_ADDR_T addr;
} SC_BT_TASK_PIN_NEGATIVE_REPLY_T;

typedef struct
{
    SC_BT_ADDR_T addr;
    unsigned int numeric_value; /*valid values are decimal 000000 to 999999*/
} SC_BT_TASK_USER_PASSKEY_REQUEST_REPLY_T;

typedef struct
{
    SC_BT_ADDR_T addr;
} SC_BT_TASK_USER_PASSKEY_REQUEST_NEGATIVE_REPLY_T;

typedef struct
{
    SC_BT_ADDR_T addr;
    unsigned char notification_type;
} SC_BT_TASK_SEND_KEYPRESS_NOTIFICATION_T;

typedef struct
{
    unsigned int length;
    unsigned char *data;
    unsigned int timestamp;
    unsigned int seq_num;
    unsigned char payload_type;
    unsigned char frames;
} SC_BT_TASK_A2DP_MEDIA_DATA_T;

typedef struct
{
    unsigned char addr[6];
    int call_status;
} SC_BT_TASK_HFP_CONNECT_T;

typedef struct
{
    int ciev_index;
    int value;
    int delay;
} SC_BT_TASK_HFP_CALL_STATUS_T;

typedef struct
{
    char number[SC_BT_PHONE_NUMBER_MAX];
    unsigned char type;
} SC_BT_TASK_HFP_UPDATE_PHONE_NUMBER_T;

typedef struct
{
    unsigned short int size;
    unsigned char *data;
} SC_BT_TASK_SCO_DATA_SEND_T;

typedef struct
{
    unsigned char addr[6];
    unsigned char remote_role;
} SC_BT_TASK_HID_CONNECT_T;

typedef struct
{
    unsigned char with_attachment;
    unsigned char handle_len;
    char *handle;
} SC_BT_TASK_MAP_GET_MASSAGE_T;

typedef struct
{
    unsigned char box_type;
    unsigned char msg_type;
    char *dst_num;
    unsigned short int buf_length;
    char *msg_content_buf;
} SC_BT_TASK_MAP_PUSH_MESSAGE_T;

typedef struct
{
    unsigned short int length;
    unsigned char *data;
    unsigned short int spp_port;
} SC_BT_TASK_SPP_SNED_DATA_T;

//for btstack
typedef struct
{
    int call_status;
    int call_dir;
    int call_id;
} SC_BT_TASK_HFP_BS_CALL_STATUS_UPDATE_T;

typedef struct
{
    unsigned short int tid;
    unsigned short int name_len;
    /*
     * backward set name: ..
     * root set name: /
     */
    unsigned short int *name;
} SC_BT_FTP_NAME_T;

typedef struct
{
    unsigned int total; //total file size
    unsigned char *data;
    unsigned int payload_size; //data size
    char type[SC_BT_OBEX_FILE_TYPE_SIZE];
    char name[SC_BT_OBEX_FILE_NAME]; // name: unicode type, should be uint16
    unsigned int name_size;
    int final; //final file packet
    int tid;
} SC_BT_TASK_OBEX_FILE_SEND_T;

/* ------------------------------- classic command struct define end ---------------------------*/

/* ------------------------------- le command struct define start ------------ -----------------*/
typedef unsigned short (*sc_att_read_callback)(unsigned short con_handle, unsigned short attribute_handle,
        unsigned short offset, unsigned char *buffer, unsigned short buffer_size);

typedef int (*sc_att_write_callback)(unsigned short con_handle, unsigned short attribute_handle,
                                     unsigned short transaction_mode, unsigned short offset, unsigned char *buffer,
                                     unsigned short buffer_size);

typedef struct
{
    SC_BT_ADDR_T addr;
    unsigned char type;
} SC_BLE_TASK_WHITE_LIST_T;

typedef struct
{
    /*
        Minimum advertising interval for undirected and low duty cycle directed advertising.
        N: Value Range 0x000020 to 0xFFFFFF
        Time Range: 20 ms to 10,485.759375s(N * 0.625 ms)
    */
    unsigned short int interval_min;
    /*
        Maximum advertising interval for undirected and low duty cycle directed advertising.
        N: Value Range 0x000020 to 0xFFFFFF
        Time Range: 20 ms to 10,485.759375s(N * 0.625 ms)
    */
    unsigned short int interval_max;
    unsigned char advertising_type; // SC_BLE_ADV_TYPE_XXX
    /*
        0x00 Public Device Address
        0x01 Random Device Address
        0x02 Controller generates the Resolvable Private Address based on the local
             IRK from the resolving list. If the resolving list contains no matching
             entry, use the public address.
        0x03 Controller generates the Resolvable Private Address based on the local
             IRK from the resolving list. If the resolving list contains no matching
             entry, use the random address from sAPI_BleSetRandomAddress().
    */
    unsigned char own_address_type;
    /*
        0x00 Public Device Address or Public Identity Address
        0x01 Random Device Address or Random (static) Identity Address
    */
    unsigned char peer_address_type;
    SC_BT_ADDR_T peer_address;
    /*
        0x00: process scan and connection request from all devices
        0x01: process connection request from all devices and scan request only from White List
        0x02: process scan request from all devices and conneciton request only from White List
        0x03: process scan and connection reques only from in the White List
    */
    unsigned char filter;
} SC_BLE_TASK_ADV_PARAMETERS_T;

typedef struct
{
    /*
        SC_BLE_ADV_LEGACY_MODE: legacy adv
        SC_BLE_EXTENDED_ADV_LEGACY_MODE: externed adv for legacy
        SC_BLE_EXTENDED_ADV_AUX_MODE:only config adv ind, no scan response
    */
    unsigned char adv_mode;
    /*
        bit0 Connectable advertising
        bit1 Scannable advertising
        bit2 Directed advertising
        bit3 High Duty Cycle Directed Connectable advertising (≤ 3.75 ms Advertising Interval)
        bit4 Use legacy advertising PDUs
        bit5 Omit advertiser's address from all PDUs ("anonymous advertising")
        bit6 Include TxPower in the extended header of the advertising PDU
    */
    unsigned short int properties;
    /*
        Minimum advertising interval for undirected and low duty cycle directed advertising.
        N: Value Range 0x000020 to 0xFFFFFF
        Time Range: 20 ms to 10,485.759375s(N * 0.625 ms)
    */
    unsigned short int interval_min;
    /*
        Maximum advertising interval for undirected and low duty cycle directed advertising.
        N: Value Range 0x000020 to 0xFFFFFF
        Time Range: 20 ms to 10,485.759375s(N * 0.625 ms)
    */
    unsigned short int interval_max;
    /*
        bit0 Channel 37 shall be used
        bit1 Channel 38 shall be used
        bit2 Channel 39 shall be used
    */
    unsigned char channel;
    /*
        0x00 Public Device Address
        0x01 Random Device Address
        0x02 Controller generates the Resolvable Private Address based on the local
             IRK from the resolving list. If the resolving list contains no matching
             entry, use the public address.
        0x03 Controller generates the Resolvable Private Address based on the local
             IRK from the resolving list. If the resolving list contains no matching
             entry, use the random address from sAPI_BleSetRandomAddress().
    */
    unsigned char own_address_type;
    /*
        0x00 Public Device Address or Public Identity Address
        0x01 Random Device Address or Random (static) Identity Address
    */
    unsigned char peer_address_type;
    SC_BT_ADDR_T peer_address;
    /*
        0x00 Process scan and connection requests from all devices (i.e., the White List is not in use)
        0x01 Process connection requests from all devices and only scan requests from devices that are in the White List
        0x02 Process scan requests from all devices and only connection requests from devices that are in the White List.
        0x03 Process scan and connection requests only from devices in the White List.
    */
    unsigned char filter_policy;
    unsigned char tx_power;// -127 ~ +20 dBm
    /*
        0x01 Primary advertisement PHY is LE 1M
        0x03 Primary advertisement PHY is LE Coded
    */
    unsigned char primary_phy;
    /*
        0x01 Secondary advertisement PHY is LE 1M
        0x02 Secondary advertisement PHY is LE 2M
        0x03 Secondary advertisement PHY is LE Coded
    */
    unsigned char secondary_phy;
    /*
        0x00 – 0x0F Value of the Advertising SID subfield in the ADI field of the PDU
    */
    unsigned char sid;
    /*
        0x00 Scan request notifications disabled
        0x01 Scan request notifications enabled
    */
    unsigned char scan_request_notification;
    SC_BT_ADDR_T adv_random_addr;
} SC_BLE_TASK_EXT_ADV_PARAMETERS_T;

typedef struct
{
    unsigned char enable;
    unsigned char number;
    unsigned char *handle;
    unsigned short *duration;
    unsigned char *max_event;
} SC_BLE_TASK_EXT_ADV_ENABLE_T;

typedef struct
{
    unsigned char handle;
    SC_BT_ADDR_T addr;
} SC_BLE_TASK_SET_ADV_RANDOM_ADDR_T;

typedef struct
{
    SC_BT_ADDR_T addr;
} SC_BLE_TASK_SET_RANDOM_ADDR_T;

typedef struct
{
    unsigned char data[31];
    unsigned char length;
} SC_BLE_TASK_ADV_DATA_T;

typedef struct
{
    unsigned char data[251];
    unsigned char length;
    unsigned char handle;
    unsigned char operation;
    unsigned char fragment;
} SC_BLE_TASK_EXT_ADV_DATA_T;

typedef struct
{
    unsigned char type;
    unsigned short int interval;
    unsigned short int window;
    unsigned char own_address_type;
} SC_BLE_TASK_SCAN_T;

typedef struct
{
    unsigned short acl;
    unsigned short att;
    unsigned char *data;
    int size;
} SC_BLE_TASK_NOTIFY_INDICATE_T;

typedef struct
{
    SC_BT_ADDR_T addr;
    int type;
} SC_BLE_TASK_CONNECT_T;

typedef struct
{
    unsigned char set_enable; // 0: disable 1: enable
    unsigned int passkey;
    void *callback;
} SC_BLE_TASK_PASSKEY_T;

typedef struct
{
    unsigned short connection_handle;
} SC_BLE_TASK_SECURITY_REQUEST_T;

typedef struct
{
    unsigned char *profile_data;
    unsigned short profile_data_len;
    sc_att_read_callback read_callback;
    sc_att_write_callback write_callback;
} SC_BLE_TASK_REGISTER_ATT_SERVER_T;

typedef struct
{
    unsigned int param1;
    unsigned int param2;
    unsigned int param3;
    unsigned char *data;
    unsigned short size;
} SC_BLE_CUSTOM_COMMAND_T;

typedef struct
{
    unsigned short conn_handle;
    unsigned short att_handle;
    unsigned char *data;
    unsigned short length;
} SC_BLE_TASK_CUSTOM_WRITE_COMMAND_T;

typedef struct
{
    unsigned short conn_handle;
    unsigned short att_handle;
    unsigned char *data;
    unsigned short length;
} SC_BLE_TASK_CUSTOM_WRITE_REQUEST_T;

typedef struct
{
    unsigned short conn_handle;
    unsigned short att_handle;
} SC_BLE_TASK_CUSTOM_READ_REQUEST_T;

typedef struct
{
    unsigned short conn_handle;
    unsigned short mtu;
} SC_BLE_TASK_CUSTOM_MTU_REQUEST_T;

typedef struct
{
    unsigned short conn_handle;
    unsigned short conn_interval;
    unsigned short slave_latency;
    unsigned short supervision_timeout;
} SC_BLE_TASK_CONNECTION_PARAMETER_UPDATE_REQUEST_T;

typedef struct
{
    unsigned short conn_handle;
} SC_BLE_TASK_CUSTOM_GATT_SCAN_T;

/* ------------------------------- le command struct define end -------------- -----------------*/

/* ------------------------------- classic event struct define start ---------------------------*/

typedef struct
{
    char name[SC_BT_NAME_MAX];
    int length;
    unsigned int cod;
    unsigned char addr[6];
    char rssi;
} SC_BT_EVENT_INQUIRY_T;

typedef struct
{
    unsigned char name[SC_BT_NAME_MAX];
    SC_BT_ADDR_T addr;
    unsigned int numeric_value;
    unsigned int cod;
    unsigned char io_capability;
} SC_BT_EVENT_PAIRING_REQUEST_T;

typedef struct
{
    unsigned char name[SC_BT_NAME_MAX];
    unsigned char addr[6];
    unsigned linkey[16];
    int linkkey_type;
    unsigned int cod;
} SC_BT_EVENT_PAIRED_T;

typedef struct
{
    SC_BT_ADDR_T addr;
    unsigned char name[SC_BT_NAME_MAX];
    unsigned int cod;
} SC_BT_EVENT_PIN_REQUEST_T;

typedef struct
{
    SC_BT_ADDR_T addr;
    unsigned int passkey;
} SC_BT_EVENT_USER_PASSKEY_NOTIFICATION_T;

typedef struct
{
    SC_BT_ADDR_T addr;
} SC_BT_EVENT_USER_PASSKEY_REQUEST_T;

typedef struct
{
    SC_BT_ADDR_T addr;
    unsigned char name[SC_BT_NAME_MAX];
    int name_length;
} SC_BT_EVENT_NAME_INDICATION_T;

typedef struct
{
    unsigned char addr[6];
    unsigned short int handle;
} SC_BT_EVENT_ACL_CONNECT_T;

typedef struct
{
    unsigned short int reason;
    unsigned short int handle;
} SC_BT_EVENT_ACL_DISCONNECT_T;

typedef struct
{
    unsigned char addr[6];
    unsigned int handle;
    unsigned int role;
} SC_BT_EVENT_SCO_T;

//a2dp source
typedef struct
{
    int cid;
    unsigned char addr[6];
} SC_BT_EVENT_A2DP_CONNECT_T;

typedef struct
{
    int cid;
} SC_BT_EVENT_A2DP_DISCONNECT_T;

typedef struct
{
    int cid;
    unsigned int mtu;
} SC_BT_EVENT_A2DP_MEDIA_MTU_T;

typedef struct
{
    unsigned int remote_device_samples_support;
    unsigned int config_samples;
    unsigned int config_sbc_bitpool;
    unsigned int config_channel_mode;
    unsigned int config_allocation;
    unsigned int config_subbands;
    unsigned int config_blocks;
} SC_BT_EVENT_SBC_CAPABILITIES_T;

//a2dp sink struct
typedef struct
{
    int cid;
    unsigned char addr[6];
} SC_BT_EVENT_A2DP_SINK_CONNECT_T;

typedef struct
{
    int cid;
} SC_BT_EVENT_A2DP_SINK_DISCONNECT_T;

typedef struct
{
    unsigned char payload_type;
    unsigned char number_of_frames;
    unsigned short int sequence_number;
    unsigned short int length;
    void *data;
} SC_BT_EVENT_A2DP_SINK_MEDIA_PAYLOAD_T;

typedef struct
{
    int reconfigure;
    int num_channels;
    int sampling_frequency;
    int block_length;
    int subbands;
    int bitpool_value;
    int channel_mode;
    int allocation_method;
} SC_BT_EVENT_A2DP_SINK_SBC_CAPABILITIES_T;

//avrcp
typedef struct
{
    unsigned char addr[6];
} SC_BT_EVENT_AVRCP_CONNECT_T;

typedef struct
{
    unsigned char addr[6];
} SC_BT_EVENT_HFP_CONNECT_T;

typedef struct
{
    int type; // 0: number; 1: redial; 2: memory
    unsigned char number[SC_BT_PHONE_NUMBER_MAX];
    int length;
} SC_BT_EVENT_HFP_DIAL_T;

//hfp hf
typedef struct
{
    unsigned char addr[6];
} SC_BT_EVENT_HFP_HF_CONNECT_T;

typedef struct
{
    int type; // 0: number; 1: redial; 2: memory
    unsigned char number[SC_BT_PHONE_NUMBER_MAX];
    int length;
} SC_BT_EVENT_HFP_HF_DIAL_T;

typedef struct
{
    unsigned char index;
    unsigned char status;
    unsigned char min_range;
    unsigned char max_range;
    char name[20];
} SC_BT_EVENT_HFP_HF_AG_IND_STATUS_T;

typedef struct
{
    unsigned char mode;
    unsigned char format;
    char name[17];
} SC_BT_EVENT_HFP_HF_NETWORK_STATUS_T;

typedef struct
{
    unsigned char type;
    char number[25];
} SC_BT_EVENT_HFP_HF_CLIP_T;

typedef struct
{
    unsigned char idx;
    unsigned char dir;
    unsigned char status;
    unsigned char mode;
    unsigned char mpty;
    unsigned char number[SC_BT_PHONE_NUMBER_MAX];
    unsigned char type;
} SC_BT_EVENT_HFP_HF_CLCC_T;

typedef struct
{
    unsigned short int size;
    unsigned char *sco_data;
} SC_BT_EVENT_HFP_SCO_DATA_T;

//hid
typedef struct
{
    unsigned char addr[6];
    unsigned int result;
} SC_BT_EVENT_HID_CONNECTED_T;

typedef struct
{
    unsigned char addr[6];
    unsigned char port;
    unsigned char result;
    unsigned short int max_frame_size;
    unsigned short int data_len;
    unsigned char *data;
} SC_BT_EVENT_SPP_EVENT_T;

typedef struct
{
    unsigned short int cid;
    unsigned char status;
    int max_packet_length;//the data size sended to server must be less than or equal to SC_BT_OBEX_FRAME_SIZE
} SC_BT_EVENT_FTP_CLIENT_CONNECT_T;


typedef struct
{
    unsigned short int cid;
    unsigned char status;
} SC_BT_EVENT_FTP_CLIENT_STATUS_T;

typedef struct
{
    unsigned short int cid;
    unsigned short int size;
    unsigned char *data;
} SC_BT_EVENT_FTP_CLIENT_PKT_DATA_T;

typedef void (*sc_bt_stack_shutdown_clearup_cb)(void);

typedef struct
{
    sc_bt_stack_shutdown_clearup_cb clearup;
} SC_BT_EVENT_SHUTDOWN_COMPLETE_T;
/* ------------------------------- classic event struct define end ---------------------------*/

/* ------------------------------- le event struct define start ---------------------------*/
typedef struct
{
    unsigned char event_type;
    unsigned char address_type;
    SC_BT_ADDR_T address;
    unsigned char length;
    unsigned char data[31];
    char rssi;
} SC_BLE_EVENT_SCAN_EVENT_T;

typedef void (*sc_le_scan_event_handle)(SC_BLE_EVENT_SCAN_EVENT_T *event);

typedef void (*sc_le_user_event_handle)(SC_BT_TASK_EVENT_T *msg);

typedef struct
{
    SC_BT_ADDR_T addr;
    unsigned char addr_type;
    int acl_handle;
    int role;
    unsigned char peer_irk[16];
} SC_BLE_EVENT_ATT_CONNECTED_T;

typedef struct
{
    unsigned char address_type;
    SC_BT_ADDR_T address;
} SC_BLE_EVENT_BOND_COMPLETE_T;

typedef struct
{
    unsigned char status;
    unsigned short connection_handle;
    unsigned char encryption_enabled;
} SC_BLE_EVENT_ENCRYPTION_CHANGE_T;

typedef struct
{
    unsigned char request;
    unsigned short att_handle;
    unsigned char code;
} SC_BLE_EVENT_ERROR_RSP_T;

typedef struct
{
    int mut;
    int acl_handle;
} SC_BLE_EVENT_MTU_EXCHANGE_EVENT_T;

typedef struct
{
    SC_BT_ADDR_T addr;
    unsigned int passkey_value;
} SC_BLE_EVENT_SMP_PASSKEY_T;

typedef struct
{
    unsigned char success_flag;
    unsigned char index;
    unsigned short connection_handle;
    SC_BT_ADDR_T address;
    unsigned char address_type;
    SC_BT_ADDR_T identity_address;
    unsigned char identity_address_type;
} SC_BLE_EVENT_IDENTITY_INFO_EVENT_T;

typedef struct
{
    unsigned char valid_count;
    unsigned char max_count;
    unsigned char index;
    SC_BT_ADDR_T identity_address;
    unsigned char identity_address_type;
    unsigned int seq;
} SC_BLE_EVENT_GET_PAIR_INFO_T;

typedef struct
{
    unsigned short connection_handle;
    unsigned short value_handle;
    unsigned char value[255];
    unsigned short value_length;
} SC_BLE_EVENT_CLIENT_HANDLE_NOTIFY_T;

typedef struct
{
    unsigned short connection_handle;
    unsigned short value_handle;
    unsigned char value[255];
    unsigned short value_length;
} SC_BLE_EVENT_CLIENT_HANDLE_INDICATION_T;

typedef struct
{
    unsigned short connection_handle;
    unsigned char write_type;
} SC_BLE_EVENT_ATT_CAN_WRITE_NOW_T;

typedef struct
{
    unsigned short connection_handle;
    unsigned short value_handle;
    unsigned short value_offset;
    unsigned short value_len;
    unsigned char value[255];
} SC_BLE_EVENT_ATT_READ_DATA_RESULT_T;

typedef struct
{
    unsigned short connection_handle;
    unsigned char att_status;
} SC_BLE_EVENT_ATT_READ_OVER_RESULT_T;

typedef struct
{
    unsigned short connection_handle;
    unsigned char status;
} SC_BLE_EVENT_GATT_SCAN_RESULT_T;

typedef struct
{
    unsigned short start_group_handle;
    unsigned short end_group_handle;
    unsigned short uuid16;
    unsigned char  uuid128[16];
} SC_GATT_CLIENT_SERVICE_T;

typedef struct
{
    unsigned short start_handle;
    unsigned short value_handle;
    unsigned short end_handle;
    unsigned short properties;
    unsigned short uuid16;
    unsigned char  uuid128[16];
} SC_GATT_CLIENT_CHARACTERISTIC_T;

typedef struct
{
    unsigned short handle;
    unsigned short uuid16;
    unsigned char  uuid128[16];
} SC_GATT_CLIENT_CHARACTERISTIC_DESCRIPTOR_T;

typedef struct
{
    unsigned short connection_handle;
    SC_GATT_CLIENT_SERVICE_T service;
} SC_BLE_EVENT_GATT_SCAN_DUMP_SERVICE_T;

typedef struct
{
    unsigned short connection_handle;
    SC_GATT_CLIENT_CHARACTERISTIC_T characteristic;
} SC_BLE_EVENT_GATT_SCAN_DUMP_CHARACTERISTIC_T;

typedef struct
{
    unsigned short connection_handle;
    SC_GATT_CLIENT_CHARACTERISTIC_DESCRIPTOR_T descriptor;
} SC_BLE_EVENT_GATT_SCAN_DUMP_DESCRIPTOR_T;

typedef struct
{
    unsigned char status;
    unsigned short conn_handle;
    unsigned short conn_interval;
    unsigned short slave_latency;
    unsigned short supervision_timeout;
} SC_BLE_EVENT_CONNECTION_PARAMETER_UPDATE_T;

/* ------------------------------- le event struct define end ---------------------------*/
/*
 *           sAPI_BtOpenStaus
 *
 * function: get bt openning status
 *
 * parameter:
 *      none
 *
 * return:
 *      0: closed
 *      1: opened
 */
int sAPI_BtOpenStaus(void);

/*
 *           sAPI_BtRegisterEventHandle
 *
 * function: register bt event handle callback function, should be invoked before executing sAPI_BtOpen()
 *
 * parameter:
 *      function_cb: bt event handle callback function
 *
 * return:
 *      0: success
 *      other: fail
 */

int sAPI_BtRegisterEventHandle(void (*function_cb)(void *msg));
/*
 *           sAPI_BtUnregisterEventHandle
 *
 * function: unregister bt event handle callback function, should be invoked after executing sAPI_BtClose()
 *
 * parameter: none
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BtUnregisterEventHandle(void);

/*
 *          sAPI_BtCreateAddress
 *
 * function: create mac address
 *
 * parameter:
 *      address: used to store mac address
 *
 * return: none
 */
void sAPI_BtCreateAddress(SC_BT_ADDR_T *address);

/*
 *           sAPI_BtSetAddress
 *
 * function: set bt device address, should be set before sAPI_BtOpen()
 *
 * parameter:
 *      addr: bt device address
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BtSetAddress(SC_BT_ADDR_T addr);

/*
 *       sAPI_BtGetAddress
 *
 * function: get bt device address
 *
 * parameter:
 *      addr: bt device address
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BtGetAddress(SC_BT_ADDR_T      *addr);

/*
 *           sAPI_BtSetName
 *
 * function: set bt name, should be set before sAPI_BtOpen()
 *
 * parameter:
 *      name: bt name
 *      length: the length of bt name , max buffer length is SC_BT_NAME_MAX.
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BtSetName(char *name, unsigned char length);

/*
 *           sAPI_BtGetName
 *
 * function: get bt name
 *
 * parameter:
 *      name: bt name
 *      length: the length of bt name
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BtGetName(char *name, unsigned char *length);

/*
 *           sAPI_BtSetIoCap
 *
 * function: set bt I/O capability, should be set before sAPI_BtOpen()
 *
 * parameter:
 *      ioCap: I/O capability(refer to SC_BT_IOCAP_T)
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BtSetIoCap(SC_BT_IOCAP_T ioCap);

/*
 *           sAPI_BtGetIoCap
 *
 * function: get bt I/O capability
 *
 * parameter:
 *      ioCap: I/O capability
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BtGetIoCap(SC_BT_IOCAP_T *ioCap);

/*
 *           sAPI_BtOpen
 *
 * function: open bt device, however whether bt device open success or not need to be known from function_cb registered with sAPI_BTRegisterEventHandle()
 *
 * parameter:
 *           mode: bluetooth mode
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BtOpen(SC_BT_MODE_T mode);

/*
 *           sAPI_BtClose
 *
 * function: close bt device
 *
 * parameter: none
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BtClose(void);

/*
 *           sAPI_BtScanStart
 *
 * function: scan for nearby bt device, scan result are returned by function_cb registered with sAPI_BtRegisterEventHandle()
 *
 * parameter:
 *      scan_duration: the duration of scan(range:1~48, unit:1.28s)
 *      scan_response_num: the number of response(0:unlimited,1 - 255)
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BtScanStart(unsigned char scan_duration, unsigned char scan_response_num);

/*
 *           sAPI_BtScanStop
 *
 * function: stop to scan nearby bt device
 *
 * parameter: none
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BtScanStop(void);

/*
 *          sAPI_BtPairingMode
 *
 * function: set pairing mode
 *
 * parameter:
 *      pair_mode: 0 is pin code
 *                 1 is ssp
 *
 * return:
 *      0: success
 *      other: fail
 *
 */
int sAPI_BtPairingMode(int pair_mode);

/*
 *           sAPI_BtPairRequest
 *
 * function: request to pair with specified device
 *
 * parameter:
 *      addr: peer bt device address
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BtPairRequest(SC_BT_ADDR_T addr);

/*
 *           sAPI_BtPairAccept
 *
 * function: pair accept
 *
 * parameter:
 *      mode: pairing mode(refer to SC_BT_PAIR_MODE_T)
 *      addr: peer bt device address
 *      verification_code: verification code(aim at PASSKEY_ENTRY_MODE)
 *      pin: pin code
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BtPairAccept(SC_BT_PAIR_MODE_T mode, SC_BT_ADDR_T addr, unsigned int verification_code, char *pin);

/*
 *           sAPI_BtPairRefuse
 *
 * function: refuse to pair with remote device
 *
 * parameter:
 *      mode: pairing mode(refer to SC_BT_PAIR_MODE_T)
 *      addr: peer bt device address
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BtPairRefuse(SC_BT_PAIR_MODE_T mode, SC_BT_ADDR_T addr);

/*
 *           sAPI_BtUnpair
 *
 * function: unpair to paired device. This API should be executed at disconnect status.
 *
 * parameter:
 *      addr: peer bt device address
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BtUnpair(SC_BT_ADDR_T addr);

/*
 *           sAPI_BtPairedQueryByIndex
 *
 * function: get paired information by index
 *
 * parameter:
 *      index: paired information index(the max index is 9)
 *      record: device paired information
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BtPairedQueryByIndex(unsigned char index, SC_BT_DEVICE_RECORD_T *record);

/*
 *           sAPI_BtPairedQueryByIndex
 *
 * function: get paired information by address
 *
 * parameter:
 *      addr: device address
 *      record: device paired information
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BtPairedQueryByAddr(SC_BT_ADDR_T addr, SC_BT_DEVICE_RECORD_T *record);

/*
 *           sAPI_BtSppConnect
 *
 * function: initiate an spp connection
 *
 * parameter:
 *      addr: peer bt device address
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BtSppConnect(SC_BT_ADDR_T addr);

/*
 *           sAPI_BtSppDisconnect
 *
 * function: disconnect spp connection
 *
 * parameter:
 *      spp_port: the port of spp connection, which can be obtained by function_cb registered with sAPI_BtRegisterEventHandle()
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BtSppDisconnect(unsigned short spp_port);

/*
 *           sAPI_BtSppSend
 *
 * function: send data by spp
 *
 * parameter:
 *      data: data to be sent
 *      length: the length of data to be sent(the max is 200 bytes)
 *      spp_port: the port of spp connection, which can be obtained by function_cb registered with sAPI_BtRegisterEventHandle()
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BtSppSend(unsigned char *data, unsigned short length, unsigned short spp_port);

/*
 *           sAPI_BtReadRssi
 *
 * function: read RSSI
 *
 * parameter:
 *      conn_handle: connnection handle
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BtReadRssi(unsigned short int conn_handle);

/*
 *           sAPI_BleSetRandomAddress()
 *
 * function: set le random address.It should be set after openning bluetooth and before advertising.
 *
 * parameter:
 *      *addr: random address
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BleSetRandomAddress(SC_BT_ADDR_T *addr);

/*
 *           sAPI_BleRegisterAttServer
 *
 * function: register gatt server, should be invoked before sAPI_BleEnableAdv().
 *
 * parameter:
 *      profile_data: defines basic elements such as services and characteristics,used in a profile.
 *      profile_data_len: size of basic elements.
 *      read_callback: get data for remote device
 *      write_callback: write data to remote device
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BleRegisterAttServer(unsigned char *profile_data,
                              unsigned short profile_data_len,
                              sc_att_read_callback read_callback,
                              sc_att_write_callback write_callback);

/*
 *           sAPI_BleCreateAdvData
 *
 * function: output ble advertising packets that satisfy bluetooth protocol according to input data.
 *
 * parameter:
 *      dataType: advertise data type(reference to SC_BLE_ADV_DATATYPE_T enum and other type of bluetooth protocol)
 *      advData: store ble advertise packets that satisfy bluetooth protocol(size should doesn't exceed 31bytes)
 *      advDataSize: size of advData remaining space
 *      data: advertise data
 *      length: advertise data length
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BleCreateAdvData(int dataType, unsigned char *advData, int advDataSize, unsigned char *data, int length);

/*
 *           sAPI_BleSetAdvData
 *
 * function: set advertise data, should be set before sAPI_BleEnableAdv()
 *
 * parameter:
 *      advData: advertise data(size should doesn't exceed 31bytes)
 *      length: advertise data length
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BleSetAdvData(unsigned char *advData, int length);

/*
 *           sAPI_BleSetScanResponseData
 *
 * function: set scan response data, should be set before sAPI_BleEnableAdv()
 *
 * parameter:
 *      data: scan response data(size should doesn't exceed 31bytes)
 *      length: scan response data length
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BleSetScanResponseData(unsigned char *data, unsigned char length);

/*
 *           sAPI_BleSetAdvParam
 *
 * function: set advertise parameter, should be set before sAPI_BleEnableAdv().
 *
 * parameter:
 *      param: advertise parameter
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BleSetAdvParam(SC_BLE_TASK_ADV_PARAMETERS_T *param);

/*
 *           sAPI_BleEnableAdv
 *
 * function: enable ble advertising
 *
 * parameter: none
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BleEnableAdv(void);

/*
 *           sAPI_BleDisableAdv
 *
 * function: disable ble advertising
 *
 * parameter: none
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BleDisableAdv(void);

/*
 *           sAPI_BleSetExtAdvData
 *
 * function: set extended advertising data
 *
 * parameter:
 *      advData: adv data(size should doesn't exceed 255bytes)
 *      length: adv data length
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BleSetExtAdvData(unsigned char *advData, int length);

/*
 *           sAPI_BleSetExtScanResponseData
 *
 * function: set extended scan_response data
 *
 * parameter:
 *      data: scan_response data(size should doesn't exceed 255bytes)
 *      length: scan_response data length
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BleSetExtScanResponseData(unsigned char *data, unsigned char length);

/*
 *           sAPI_BleSetExtAdvParam
 *
 * function: set extended advertising parameters
 *
 * parameter:
 *      param: struct for advertising parameters
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BleSetExtAdvParam(SC_BLE_TASK_EXT_ADV_PARAMETERS_T *param);

/*
 *           sAPI_BleEnableExtAdv
 *
 * function: enable extended advertising
 *
 * parameter:
 *      none
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BleEnableExtAdv(void);

/*
 *           sAPI_BleDisableExtAdv
 *
 * function: disable extended advertising
 *
 * parameter:
 *      none
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BleDisableExtAdv(void);

/*
 *           sAPI_BleScan
 *
 * function: scan for nearby ble device that are advertising, scan result are returned by handle registered with sAPI_BtRegisterEventHandle()
 *
 * parameter:
 *      type: scan type(SC_BLE_ACTIVE_SCAN or SC_BLE_PASSIVE_SCAN)
 *      interval: scan interval(range:0x0004-0x4000, unit:0.625msec)
 *      window: scan window(range:0x0004-0x4000, unit:0.625msec)
 *      own_address_type: own address type(SC_BLE_ADDRESS_TYPE_PUBLIC or SC_BLE_ADDRESS_TYPE_RANDOM)
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BleScan(unsigned char type, unsigned short int interval, unsigned short int window,
                 unsigned char own_address_type);

/*
 *           sAPI_BleScanStop
 *
 * function: stop to scan
 *
 * parameter: none
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BleScanStop(void);

/*
 *           sAPI_BleConnect
 *
 * function: initiate connection to target ble device
 *
 * parameter:
 *      addr: target ble device mac address
 *      type: target ble device mac address type
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BleConnect(SC_BT_ADDR_T *addr, int type);

/*
 *           sAPI_BleDisconnect
 *
 * function: initiate disconnection to current connected ble device
 *
 * parameter:
 *      conn_handle : connection handle
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BleDisconnect(unsigned short conn_handle);

/*
 *           sAPI_BleIndicate
 *
 * function: send indication to gap central
 *
 * parameter:
 *      conn_handle: connection handle of remote device.
 *      att_handle: handle of basic element (obtain from characteristic after connection is established)
 *      data: data for notifying to remote device
 *      size: data length
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BleIndicate(unsigned short conn_handle, unsigned short att_handle, unsigned char *data, int size);

/*
 *           sAPI_BleNotify
 *
 * function: send notification to gap central
 *
 * parameter:
 *      conn_handle: connection handle of remote device.
 *      att_handle: attribute handle(obtain from characteristic after connection is established)
 *      data: data to be sent to gap central
 *      size: data length
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BleNotify(unsigned short conn_handle, unsigned short att_handle, unsigned char *data, int size);

/*
 *           sAPI_BleMtuRequest
 *
 * function: initiate an MTU request to gap peripheral
 *
 * parameter:
 *      conn_handle: connection handle of remote device.
 *      mtu_size: local supported ATT_MTU size(current fixed as 185bytes)
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BleMtuRequest(unsigned short conn_handle, unsigned short mtu_size);

/*
*          sAPI_BleGattScanStart
*
* function: request to get basic elements of remote device
*
* parameter:
*      conn_handle: connection handle of remote device.
*
* return:
*      0: success
*      other: fail
*
*/
int sAPI_BleGattScanStart(unsigned short conn_handle);

/*
*          sAPI_BleReadRequest
*
* function: request to read data from remote device
*
* parameter:
*      conn_handle: connection handle of remote device.
*      att_handle: basic element handle of remote device
*
* return:
*      0: success
*      other: fail
*
*/
int sAPI_BleReadRequest(unsigned short conn_handle, unsigned short att_handle);

/*
*          sAPI_BleWriteRequest
*
* function: request to write data to remote device
*
* parameter:
*      conn_handle: connection handle of remote device.
*      att_handle: basic element handle of remote device
*      data: data for writing to remote device
*      size: data length
*
* return:
*      0: success
*      other: fail
*
*/
int sAPI_BleWriteRequest(unsigned short conn_handle, unsigned short att_handle, unsigned char *data,
                         unsigned short size);

/*
*          sAPI_BleWriteCommand
*
* function: write data to remote device by wirte-command
*
* parameter:
*      conn_handle: connection handle of remote device.
*      att_handle: basic element handle of remote device
*      data: data for writing to remote device
*      size: data length
*
* return:
*      0: success
*      other: fail
*
*/
int sAPI_BleWriteCommand(unsigned short conn_handle, unsigned short att_handle, unsigned char *data,
                         unsigned short size);

/*
 *          sAPI_BleSmpIniate
 *
 * function: pair to device
 *
 * parameter:
 *      conn_handle: connection handle of remote device.
 *
 * return:
 *      0: success to send pair command
 *      other: fail
 */
int sAPI_BlePairRequest(unsigned short conn_handle);

/*
 *          sAPI_BleSetPairEnable
 *
 * function: Enable or disable to accept remote pairing request before starting request.
 *
 * parameter:
 *      enable: 0/1,default is 1.
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BleSetPairEnable(unsigned char enable);

/*
 *          sAPI_BleGetPairInfo
 *
 * function: get single pair info by index
 *
 * parameter:
 *      index: record index
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BleGetPairInfo(int index);

/*
 *          sAPI_BleDeleteSinglePairInfo
 *
 * function: delete single pair info by index
 *
 * parameter:
 *      index: record index
 *
 * return:
 *      NONE
 */
void sAPI_BleRemovePairInfo(int index);

/*
 *          sAPI_BleSetWhiteList
 *
 * function: add device to white list
 *
 * parameter:
 *      addr :device addr
 *      type : addr type
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BleSetWhiteList(SC_BT_ADDR_T addr, unsigned char type);

/*
 *          sAPI_BleClearWhiteList
 *
 * function: clean white list
 *
 * parameter:
 *      none
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BleClearWhiteList(void);
#ifdef CUS_DRIVER_BT
/*
 *sAPI_BleDevConfigInit
 *
 * function: Set up custom Bluetooth driver configuration.
 *
 * parameter:
 *      SC_BLE_DEV_CFG_T *handle
 *
 * return:
 *      0: success
 *      other: fail
 */
int sAPI_BleDevConfigInit(SC_BLE_DEV_CFG_T *handle);
#endif

#ifdef __cplusplus
}
#endif

#endif


