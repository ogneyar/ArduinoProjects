/**
  ******************************************************************************
  * @file    MDR1986VK01_can.h
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    06/04/2022
  * @brief   CAN-FD Header file.
  ******************************************************************************
  * <br><br>
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
  * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2022 Milandr</center></h2>
  ******************************************************************************
  * FILE MDR1986VK01_can.h
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MDR1986VK01_CANFD_LIBRARY_H
#define __MDR1986VK01_CANFD_LIBRARY_H

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "MDR1986VK01_config.h"

/** @addtogroup __MDR1986VK01_StdPeriph_Driver MDR1986VK01 Standard Peripherial Driver
  * @{
  */

/** @addtogroup CANFD CANFD
  * @{
  */

/** @defgroup CANFD_Exported_Types CANFD Exported Types
  * @{
  */

// Active module name
#define MDR_CANFDx MDR_CANFD0

// Active Pins
#define MDR_CANFD_RxPORT MDR_PORTA
#define MDR_CANFD_TxPORT MDR_PORTB

// If your memory has word structure
// Comment out this line
#define ByteMem

typedef struct {
    uint32_t   TimeLo;
    uint32_t   TimeHi;
    uint32_t   Ctrl;
    uint32_t   ID;
    uint32_t   Payload[16];
} CanFdMsg_t;

typedef struct {
    // Timing Control
    uint16_t ClkDiv_N;
    uint16_t ClkDiv_D;

    uint8_t  PropSeg;
    uint8_t  Seg1_n;
    uint8_t  Seg2_n;
    uint8_t  Rjw_n;
    uint8_t  Seg1_d;
    uint8_t  Seg2_d;
    uint8_t  Rjw_d;

    // Queue Control
    uint8_t  TxQSize;
    uint8_t  RxQSize;
    uint8_t  TxMSize;
    uint8_t  RxMSize;

    // Error Control
    uint8_t  TxErrMaxLvl;
    uint8_t  RxErrMaxLvl;
    unsigned TxErrEn          :1;
    unsigned RxErrEn          :1;
    unsigned EovlcEn          :1;
    unsigned EpscEn           :1;
    unsigned BoscEn           :1;
    unsigned LostMsgEn        :1;

    // Operation mode
    unsigned EnTx             :1;
    unsigned FdEn             :1;
    unsigned CrcMode          :1;
    unsigned SelfMode         :1;
    unsigned Tsi              :4;

    // Tx/Rx Connections
    uint8_t  TxPIN;
    uint8_t  RxPIN;
} CanfdInitCfg_t;

typedef struct {
    uint32_t ExtId;
    uint16_t BaseId;
    unsigned Srr          : 1; //
    unsigned Ide          : 1; //
    unsigned Rtr          : 1; // Remote transmission request frame
    unsigned Brs          : 1; // Flexible data-rate format with bitrate switch
    unsigned Dlc          : 4; // Data length code
    unsigned Oce          : 1; // Outdated check Enable
    unsigned Ssf          : 1; // Single Shot Frame
    unsigned PType        : 1; // 0 for Word data, 1 for byte data
    uint32_t *WordPtr;     // Word Data Pointer
    uint8_t  *BytePtr;     // Byte Data Pointer
} CanFdUserMsg_t;

typedef enum {
    // TRC codes
    OK            = 0,
    MSG_TOO_OLD   = 1,
    MSG_TX_ERROR  = 2,
    MSG_ARB_LOST  = 3,
    MSG_TOO_BIG   = 4,
    MSG_EXIST     = 5,
    MSG_NEW       = 7,
    // Other states
    WRONG_ARG     = 6,
    MSG_NOT_FOUND = 8,
    ALLOC_ERR     = 10
} CanFdStatus_t;

/** @} */ /* End of group CANFD_Exported_Types */

// Receive Queue
extern CanFdMsg_t RxQ0[64];

// Transmit Queue
extern CanFdMsg_t TxQ[4][96];


//-----------------------------------------------------------------------------
// IRQ table
//-----------------------------------------------------------------------------

/** @defgroup CANFD_IRQ_Table CANFD IRQ Table
  * @{
  */

#define RXQF         28
#define TXQ0F        27
#define TXQ1F        26
#define TXQ2F        25
#define TXQ3F        24
#define TXQ0E        23
#define TXQ1E        22
#define TXQ2E        21
#define TXQ3E        20
#define EAS          19
#define EPS          18
#define BOS          17
#define RXACT        16
#define TXACT        15
#define DLCERR       14
#define RXML         13
#define RXQOVL       12
#define TECOVL       11
#define RECOVL       10
#define RXFRMCMPLT   9
#define TXFRMCMPLT   8
#define ABRLOST      7
#define TXERR        6
#define RXERR        5
#define BITERR       4
#define BITSTAFFERR  3
#define ACKERR       2
#define CRCERR       1
#define FRMERR       0

/** @} */ /* End of group CANFD_IRQ_Table */

//-----------------------------------------------------------------------------
// Functions Prototypes
//-----------------------------------------------------------------------------

/** @defgroup CANFD_Exported_Functions CAN Exported Functions
  * @{
  */

void CanFdCreateDefaultCfg(CanfdInitCfg_t *InitCfg);

void CanFdInit(CanfdInitCfg_t *InitCfg);
void CanFdDeInit(CanfdInitCfg_t *InitCfg);

void CanFdEnable(void);
void CanFdDisable(void);

void CanFdMacRst(void);
void CanFdMacDeRst(void);

void CanFdUptime(void);

CanFdStatus_t CanFdSendMessage(const CanFdUserMsg_t *UserMsgPtr, uint16_t QNum, uint16_t SlotNum);
CanFdStatus_t CanFdReadMessage(CanFdUserMsg_t *UserMsgPtr, uint16_t QNum, uint16_t SlotNum);

uint8_t Dlc2Bytes(uint8_t Dlc);
uint8_t Dlc2Words(uint8_t Dlc);

CanFdStatus_t AddMsg(uint16_t QNum, uint16_t SlotNum);
CanFdStatus_t ClearMsg(uint16_t QNum, uint16_t SlotNum);
CanFdStatus_t CheckMsg(uint16_t QNum, uint16_t SlotNum);

/** @} */ /* End of group CANFD_Exported_Functions */

/** @} */ /* End of group CANFD */

/** @} */ /* End of group MDR1986VK01_StdPeriph_Driver */

#endif // __MDR1986VK01_CANFD_LIBRARY_H

/******************* (C) COPYRIGHT 2022 Milandr *********
*
* END OF FILE MDR1986VK01_can.h */


