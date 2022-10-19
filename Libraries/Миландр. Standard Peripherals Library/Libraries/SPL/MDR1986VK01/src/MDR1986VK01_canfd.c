/**
  ******************************************************************************
  * @file    MDR1986VK01_canfd.c
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    06/04/2022
  * @brief   CAN-FD Implementation file
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
  * FILE MDR1986VK01_canfd.c
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR1986VK01_canfd.h"
#include <stdlib.h>
#include <string.h>

/** @addtogroup __MDR1986VK01_StdPeriph_Driver MDR1986VK01 Standard Peripherial Driver
  * @{
  */

/** @addtogroup CANFD CANFD
  * @{
  */

/** @defgroup CANFD_Exported_Types CANFD Exported Types
  * @{
  */


#define ClearBit(reg, bit)       reg &= (~(1<<(bit)))
#define SetBit(reg,   bit)       reg |= (1<<(bit))

/* CTRL Reg bits */
#define CRC_MODE     7
#define RST_MAC      6
#define UPTIME       5
#define SOVLFRM      4
#define ENACK        3
#define ENTX         2
#define FDMODE       1
#define CANEN        0

/* CFG0 Reg bits */
#define TSI          10
#define STM          9
#define TSR          6
#define TECE         5
#define RECE         4
#define EOVLC        3
#define EPSC         2
#define BOSC         1
#define LMSGLC       0

/* CFG1 Reg bits */
#define PROPSEG      26
#define SEG2_N       21
#define SEG1_N       16
#define RJW_N        14
#define SEG2_D       8
#define RJW_D        6
#define SEG1_D       0

/* CFG2 Reg bits */
#define TecLvl       8
#define RecLvl       0

/* CFG3 Reg bits */
#define RXQD         24
#define TXQD         16
#define RXQMMSIZE    8
#define TXQMMSIZE    0


//---------------------------------------------------------------
// This is how message stored in memory
// Named constants defines address shift
//---------------------------------------------------------------
/** @note Don't change this defines! */

#define MsgHeaderSize        0x14 /*!< Message Header size in bytes */
#define MaxPayloadSize       0x40 /*!< Message Payload max size in bytes */

#define timeLO_shift         0x00 /*!< Message Timestamp (LO) shift */
#define timeHI_shift         0x04 /*!< Message Timestamp (HI) shift */
#define status_control_shift 0x08 /*!< Status&Control field shift */
#define id_shift             0x0C /*!< Message ID shift */
#define payload_shift        0x10 /*!< Message Data shift */

/* Control bit in Status&Control field */
#define ssf_shift            7
#define ode_shift            8
#define stmf_shift           9
#define trc_shift            16

#define CANFD_FUNCODE        0x9
#define GPIO_FAST_DRV        0x3

/** @} */ /* End of group CANFD_Exported_Types */

/** @defgroup CANFD_Private_Function_Prototypes CANFD Private Function Prototypes
 * 	@{
 */

/**
  * @brief  Internal function prototypes
  */

/** @note Only for internal purpose! */

static uint32_t GetMsgBAddr     (uint32_t QueueBAddr, uint16_t QueueElement, uint8_t MsgMaxSize);
static uint32_t EndianConversion(uint32_t data_i);
static uint16_t GetMsgNum       (uint16_t QueuePart, uint16_t QueueElement);
static uint16_t GetQueuePart    (uint16_t SlotNum);
static uint16_t AlignSlotNum    (uint16_t SlotNum);
static CanFdStatus_t CheckArgs  (uint16_t QNum, uint16_t SlotNum);

/** @} */ /* End of group CANFD_Private_Function_Prototypes */

/* Receive Queue */
CanFdMsg_t RxQ0[64];

/* Transmit Queue */
CanFdMsg_t TxQ[4][96];


/** @defgroup CANFD_Exported_Functions CANFD Exported Functions
  * @{
  */

/**
  * @brief  Create config structure with default parameters.
  * @param  CanfdInitCfg_t poiter
  * @retval None
  */
void CanFdCreateDefaultCfg(CanfdInitCfg_t *InitCfg)
{
    /* Timing Control */
    InitCfg->ClkDiv_D = 0;
    InitCfg->ClkDiv_N = 0;

    InitCfg->PropSeg  = 1;

    InitCfg->Seg1_n   = 13;
    InitCfg->Seg2_n   = 14;

    InitCfg->Seg1_d   = 1;
    InitCfg->Seg2_d   = 1;

    InitCfg->Rjw_n    = 3;
    InitCfg->Rjw_d    = 2;

    /* Operation mode */
    InitCfg->EnTx     = 1;
    InitCfg->FdEn     = 1;
    InitCfg->CrcMode  = 0; // ISO
    InitCfg->SelfMode = 0;
    InitCfg->Tsi      = 1;

    /* Queue Control */
    InitCfg->TxQSize  = 15;
    InitCfg->RxQSize  = 15;
    InitCfg->TxMSize  = 64;
    InitCfg->RxMSize  = 64;

    /* Error Control */
    InitCfg->TxErrMaxLvl = 10;
    InitCfg->RxErrMaxLvl = 10;
    InitCfg->TxErrEn     = 1;
    InitCfg->RxErrEn     = 1;
    InitCfg->EovlcEn     = 0;
    InitCfg->EpscEn      = 0;
    InitCfg->BoscEn      = 0;
    InitCfg->LostMsgEn   = 1;

//    InitCfg->RxPIN       = 2;
//    InitCfg->TxPIN       = 3;
}

/**
  * @brief  Enable clock, apply config to module and allocate
  *         memory for queues
  * @param  CanfdInitCfg_t poiter
  * @retval None
  */
void CanFdInit(CanfdInitCfg_t *InitCfg)
{

//    uint8_t RxPIN_SFUNC_EL;
//    uint8_t TxPIN_SFUNC_EL;
//    uint8_t RxPIN_SFUNC_SHT;
//    uint8_t TxPIN_SFUNC_SHT;
//    uint8_t RxPIN_SPWR_EL;
//    uint8_t TxPIN_SPWR_EL;
//    uint8_t RxPIN_SPWR_SHT;
//    uint8_t TxPIN_SPWR_SHT;

    // Enable perih clock
//    MDR_CLK->KEY       = 0x8555AAA1;
//    SetBit(MDR_CLK->CANFD_CLK, 16);
//    SetBit(MDR_CLK->PER0_CLK, 13);
//    SetBit(MDR_CLK->PER0_CLK, 14);
//    MDR_CLK->KEY       = 0x00000000;

    /* Set timing parameters */
    MDR_CANFDx->CFG1     = (InitCfg->PropSeg << PROPSEG)|
                           (InitCfg->Rjw_n   << RJW_N  )|
                           (InitCfg->Seg1_n  << SEG1_N )|
                           (InitCfg->Seg2_n  << SEG2_N )|
                           (InitCfg->Rjw_d   << RJW_D  )|
                           (InitCfg->Seg1_d  << SEG1_D )|
                           (InitCfg->Seg2_d  << SEG2_D );

    /* Operation mode */
    MDR_CANFDx->CONTROL  = (InitCfg->CrcMode  << CRC_MODE)|
                           (InitCfg->SelfMode << ENACK   )|
                           (InitCfg->EnTx     << ENTX    )|
                           (InitCfg->FdEn     << FDMODE  );

    MDR_CANFDx->CFG0     = (InitCfg->Tsi       << TSI   )|
                           (InitCfg->SelfMode  << STM   )|
                           (InitCfg->TxErrEn   << TECE  )|
                           (InitCfg->RxErrEn   << RECE  )|
                           (InitCfg->EovlcEn   << EOVLC )|
                           (InitCfg->EpscEn    << EPSC  )|
                           (InitCfg->BoscEn    << BOSC  )|
                           (InitCfg->LostMsgEn << LMSGLC);

    /* Set clock prescalers */
    MDR_CANFDx->PRSC     = InitCfg->ClkDiv_N;
    MDR_CANFDx->FPRSC    = InitCfg->ClkDiv_D;

    MDR_CANFDx->CFG2     = (InitCfg->TxErrMaxLvl << TecLvl)|
                           (InitCfg->RxErrMaxLvl << RecLvl);

    /* Set queue size */
    MDR_CANFDx->CFG3     = (InitCfg->RxQSize << RXQD);
    MDR_CANFDx->CFG3    |= (InitCfg->RxMSize << RXQMMSIZE);
    MDR_CANFDx->CFG3    |= (InitCfg->TxQSize << TXQD);
    MDR_CANFDx->CFG3    |= (InitCfg->TxMSize << TXQMMSIZE);

    /* Memory allocation */
    MDR_CANFDx->RXBADDR    = (uint32_t) &RxQ0;
    MDR_CANFDx->TXBADDR[0] = (uint32_t) &TxQ[0];
    MDR_CANFDx->TXBADDR[1] = (uint32_t) &TxQ[1];
    MDR_CANFDx->TXBADDR[2] = (uint32_t) &TxQ[2];
    MDR_CANFDx->TXBADDR[3] = (uint32_t) &TxQ[3];

    // Set filtration options
    // regmodel.RXFCFG.write(status, tcfg.filt_en);
    // foreach(tcfg.filt_en[i]) begin
    //     if (tcfg.filt_en[i]) begin
    //         regmodel.RXF[i].write(   status, tcfg.filt[i]);
    //         regmodel.RXFMSK[i].write(status, tcfg.mask[i]);
    //     end

//    RxPIN_SFUNC_EL                           = InitCfg->RxPIN >> 3;
//    TxPIN_SFUNC_EL                           = InitCfg->TxPIN >> 3;
//    RxPIN_SFUNC_SHT                          = 4*(InitCfg->RxPIN % 8);
//    TxPIN_SFUNC_SHT                          = 4*(InitCfg->TxPIN % 8);

//    RxPIN_SPWR_EL                            = InitCfg->RxPIN >> 4;
//    TxPIN_SPWR_EL                            = InitCfg->TxPIN >> 4;
//    RxPIN_SPWR_SHT                           = 2*(InitCfg->RxPIN % 16);
//    TxPIN_SPWR_SHT                           = 2*(InitCfg->TxPIN % 16);

//    //Connect to pins
//    MDR_CANFD_RxPORT->KEY                    = 0x8555AAA1;
//    SetBit(MDR_CANFD_RxPORT->SANALOG, InitCfg->RxPIN);
//    MDR_CANFD_RxPORT->SPWR[RxPIN_SPWR_EL]   |= (GPIO_FAST_DRV << RxPIN_SPWR_SHT);
//    MDR_CANFD_RxPORT->SFUNC[RxPIN_SFUNC_EL] |= (CANFD_FUNCODE << RxPIN_SFUNC_SHT);
//    MDR_CANFD_RxPORT->KEY                    = 0x00000000;
//    //
//    MDR_CANFD_TxPORT->KEY                    = 0x8555AAA1;
//    SetBit(MDR_CANFD_TxPORT->SANALOG, InitCfg->TxPIN);
//    MDR_CANFD_TxPORT->SPWR[TxPIN_SPWR_EL]   |= (GPIO_FAST_DRV << TxPIN_SPWR_SHT);
//    MDR_CANFD_TxPORT->SFUNC[TxPIN_SFUNC_EL] |= (CANFD_FUNCODE << TxPIN_SFUNC_SHT);
//    MDR_CANFD_TxPORT->KEY                    = 0x00000000;
    //
    CanFdEnable();
}

/**
  * @brief  Disable clock and free memory
  * @param  CanfdInitCfg_t poiter
  * @retval None
  */
void CanFdDeInit(CanfdInitCfg_t *InitCfg)
{
    CanFdDisable();

    // Disable perih clock
//    MDR_CLK->KEY       = 0x8555AAA1;
//    ClearBit(MDR_CLK->CANFD_CLK,16);
//    ClearBit(MDR_CLK->PER0_CLK, 13);
//    ClearBit(MDR_CLK->PER0_CLK, 14);
//    MDR_CLK->KEY       = 0x00000000;
}

/**
  * @brief  Enable module
  * @param  None
  * @retval None
  */
void CanFdEnable(void)
{
    SetBit(MDR_CANFDx->CONTROL, CANEN);
}

/**
  * @brief  Disable module
  * @param  None
  * @retval None
  */
void CanFdDisable(void)
{
    ClearBit(MDR_CANFDx->CONTROL, CANEN);
}

/**
  * @brief  Software reset just for MAC level.
  *         All settings will be saved.
  * @param  None
  * @retval None
  */
void CanFdMacRst(void)
{
    SetBit(MDR_CANFDx->CONTROL, RST_MAC);
}

/**
  * @brief  Wake up from reset state for MAC level.
  * @param  None
  * @retval None
  */
void CanFdMacDeRst(void)
{
    ClearBit(MDR_CANFDx->CONTROL, RST_MAC);
}

/**
  * @brief  Update timer register.
  * @param  None
  * @retval None
  */
void CanFdUptime(void)
{
    SetBit(MDR_CANFDx->CONTROL, UPTIME);
}

/**
  * @brief  Get message from *MsgPtr address and add in the Tx queue.
  * @param  CanFdUserMsg_t: Message pointer
  * @param  QNum:           Queue number
  * @param  SlotNum:        Slot number inside queue
  * @retval CanFdStatus_t:  Operation status - if non zero there was a problem
  */
CanFdStatus_t CanFdSendMessage(const CanFdUserMsg_t *UserMsgPtr, uint16_t QNum, uint16_t SlotNum)
{
    uint32_t                 Data;
    uint8_t                  NumWords;
    uint8_t                  i;

    uint32_t                *WordPtr;
    CanFdMsg_t              *QMsgPtr;
    CanFdStatus_t            Status;

    /* Check input args */
    Status = CheckArgs(QNum, SlotNum);
    if( Status != OK) {
        return Status;
    }

    QMsgPtr = &TxQ[QNum][SlotNum];

    /* Frame Start Time */
    CanFdUptime();
    QMsgPtr->TimeLo = MDR_CANFDx->CURTIMELo;
    QMsgPtr->TimeHi = MDR_CANFDx->CURTIMEHi;

    /* Control information */
    Data            = 0x00000000;
    Data           |= (UserMsgPtr->Oce << 29);  // Outdated check
    Data           |= (UserMsgPtr->Ssf << 28);  // SingleShotFlag
    Data           |= (0xE             << 24);  // TRC code - New message
    Data           |= (UserMsgPtr->Brs << 15);
    Data           |= (UserMsgPtr->Rtr << 14);
    Data           |= (0               << 13);  // R1
    Data           |= (0               << 12);  // R0
    Data           |= (UserMsgPtr->Dlc << 8);
    QMsgPtr->Ctrl   = Data;

    /* Frame ID */
    Data            = 0x00000000;
    Data           |= (UserMsgPtr->BaseId << 21);
    Data           |= (UserMsgPtr->Srr    << 20);
    Data           |= (UserMsgPtr->Ide    << 19);
    Data           |= (UserMsgPtr->ExtId  << 0 );
    QMsgPtr->ID     = EndianConversion(Data);

    /* Payload */
    if( UserMsgPtr->PType == 0) {
        WordPtr = UserMsgPtr->WordPtr;
    } else {
        WordPtr = (uint32_t*) UserMsgPtr->BytePtr;       
    }

    NumWords = Dlc2Words(UserMsgPtr->Dlc);
    if( NumWords != 0 ) {
        for(i = 0; i < NumWords; i++ ) {
            /* Copy word */
            QMsgPtr->Payload[i] = *(WordPtr + i);
        }
    } 
    Status = AddMsg(QNum, SlotNum);
    return(Status);
}

/**
  * @brief  Check message in desired slot and if it exist return address in *MsgPtr.
  * @param  CanFdUserMsg_t: Message pointer
  * @param  QNum:           Queue number
  * @param  SlotNum:        Slot number inside queue
  * @retval CanFdStatus_t:  Operation status - if non zero there was a problem
  */
CanFdStatus_t CanFdReadMessage(CanFdUserMsg_t *UserMsgPtr, uint16_t QNum, uint16_t SlotNum)
{
    uint32_t                 Data;
    uint8_t                  NumWords;
    uint8_t                  i;

    CanFdMsg_t              *QMsgPtr;
    CanFdStatus_t            Status;

    /* Check input args */
    Status = CheckArgs(QNum, SlotNum);
    if( Status != OK) {
        return Status;
    }

    QMsgPtr = &RxQ0[SlotNum];

    /* Check message existense */
    if((QMsgPtr->Ctrl == 0) & (QMsgPtr->TimeLo == 0) & (QMsgPtr->ID == 0)) {
        return MSG_NOT_FOUND;
    }

    UserMsgPtr->Ssf     = 0;
    UserMsgPtr->Brs     = 0;
    UserMsgPtr->Rtr     = 0;
    UserMsgPtr->Dlc     = 0;
    UserMsgPtr->Oce     = 0;
    UserMsgPtr->BaseId  = 0;
    UserMsgPtr->Srr     = 0;
    UserMsgPtr->Ide     = 0;
    UserMsgPtr->ExtId   = 0;

    /* Control information */
    Data                = QMsgPtr->Ctrl;
    UserMsgPtr->Ssf     = (unsigned) ( (Data >> 28) & 0x00000001 );
    UserMsgPtr->Brs     = (unsigned) ( (Data >> 15) & 0x00000001 );
    UserMsgPtr->Rtr     = (unsigned) ( (Data >> 14) & 0x00000001 );
    UserMsgPtr->Dlc     = (unsigned) ( (Data >>  8) & 0x0000000F );
    UserMsgPtr->Oce     = (unsigned)                             0; // makes no sense

    /* Frame ID */
    Data                = EndianConversion(QMsgPtr->ID);
    UserMsgPtr->BaseId  = (uint16_t) ( (Data >> 21) & 0x000007FF );
    UserMsgPtr->Srr     = (unsigned) ( (Data >> 20) & 0x00000001 );
    UserMsgPtr->Ide     = (unsigned) ( (Data >> 19) & 0x00000001 );
    UserMsgPtr->ExtId   = (uint32_t) ( (Data >>  0) & 0x0003FFFF );

    /* Payload */
    NumWords            = Dlc2Words(UserMsgPtr->Dlc);

    if( NumWords != 0 ) {
        UserMsgPtr->WordPtr = (uint32_t*) malloc(NumWords*sizeof(uint32_t));   
        if( UserMsgPtr->WordPtr == NULL ) {
            return ALLOC_ERR;
        } 

        UserMsgPtr->BytePtr = (uint8_t *) UserMsgPtr->WordPtr;
        for(i = 0; i < NumWords; i++ ) {
            /* Copy word */
            *(UserMsgPtr->WordPtr + i) = *(QMsgPtr->Payload + i);
        }
    }
    return OK;
}

/**
  * @brief  Converts DLC into bytes
  * @param  uint8_t Dlc
  * @retval uint8_t Bytes Number
  */
uint8_t Dlc2Bytes(uint8_t Dlc)
{
    uint8_t FdBit;

    FdBit = MDR_CANFDx->CONTROL & 0x00000002; // clear all bits except CANFD_EN

    if(FdBit == 0) {
        if(Dlc <= 8) {
            return(Dlc);
        } else {
            return(8);
        }
    }

    if(Dlc <= 8) {
        return(Dlc);
    } else {
        // Otherwise we have CAN FD frame with more than 8 bytes
        switch (Dlc) {
            case 9 : return(12); 
            case 10: return(16); 
            case 11: return(20); 
            case 12: return(24); 
            case 13: return(32); 
            case 14: return(48); 
            default: return(64); 
        }
    }
}

/**
  * @brief  Converts DLC into words
  * @param  uint8_t Frame Dlc
  * @retval uint8_t Words Number
  */
uint8_t Dlc2Words(uint8_t Dlc)
{
    uint8_t BytesNum;

    if(Dlc == 0) {
        return(0);
    }

    BytesNum = Dlc2Bytes(Dlc);
    if(BytesNum <= 4) {
        return(1);
    }

    if(BytesNum <= 8) {
        return(2);
    }

    return(BytesNum >> 2);
}

/**
  * @brief  Add message in queue.
  * @param  QNum:           Queue number
  * @param  SlotNum:        Slot number inside queue
  * @retval CanFdStatus_t:  Operation status
  */
CanFdStatus_t AddMsg(uint16_t QNum, uint16_t SlotNum)
{
    uint16_t      QueuePart;
    uint16_t      AlignedSlotNum;
    CanFdStatus_t Status;

    Status = CheckMsg(QNum, SlotNum);
    if( Status == OK) {
        QueuePart      = GetQueuePart(SlotNum);
        AlignedSlotNum = AlignSlotNum(SlotNum);
        MDR_CANFDx->TXQCTRL[QNum].CTRL[QueuePart] |= (1 << AlignedSlotNum);
    }
    return Status;
}

/**
  * @brief  Check message in queue.
  * @param  QNum:           Queue number
  * @param  SlotNum:        Slot number inside queue
  * @retval CanFdStatus_t:  Operation status
  */
CanFdStatus_t CheckMsg(uint16_t QNum, uint16_t SlotNum)
{
    uint16_t      QueuePart;
    uint16_t      AlignedSlotNum;
    uint32_t      tmp;
    CanFdStatus_t Status;
    
    Status = CheckArgs(QNum, SlotNum);
    if(Status != OK) {
        return Status;
    }

    QueuePart      = GetQueuePart(SlotNum);
    AlignedSlotNum = AlignSlotNum(SlotNum);
    tmp            = MDR_CANFDx->TXQCTRL[QNum].CTRL[QueuePart];

    if( (tmp & (1 << AlignedSlotNum)) == 0 ) {
        return OK;
    } else {
        return MSG_EXIST;
    }
}

/**
  * @brief  Check message from queue.
  * @param  QNum:           Queue number
  * @param  SlotNum:        Slot number inside queue
  * @retval CanFdStatus_t:  Operation status
  */
CanFdStatus_t ClearMsg(uint16_t QNum, uint16_t SlotNum)
{
    uint16_t      QueuePart;
    uint16_t      AlignedSlotNum;
    uint32_t      tmp;
    CanFdStatus_t Status;
    
    Status = CheckArgs(QNum, SlotNum);
    if(Status != OK) {
        return Status;
    }

    QueuePart      = GetQueuePart(SlotNum);
    AlignedSlotNum = AlignSlotNum(SlotNum);
    tmp            = MDR_CANFDx->TXRCTRL[QNum].CTRL[QueuePart];

    if( (tmp & (1 << AlignedSlotNum)) == 0 ) {
        MDR_CANFDx->TXRCTRL[QNum].CTRL[QueuePart] |= (1 << AlignedSlotNum);
    }
    return OK;
}

/** @} */ /* End of group CANFD_Exported_Functions */


/** @defgroup CANFD_Private_Functions CANFD Private Functions
 * 	@{
 */

/**
  * @brief  Internal functions
  */

/** @note Not for user purposes! */

/**
  * @brief     Base function for data convertion.
  * @warning   Not for user purpose! Use LittleEndian_to_BigEndian and BigEndian_to_LittleEndian instead.
  * @param     uint32_t
  * @retval    uint32_t
  */
static uint32_t EndianConversion(uint32_t data_i)
{
    // data_o = {data_i[7:0], data_i[15:8], data_i[23:16], data_i[31:24]};
    uint32_t byte[4] = {0,0,0,0};
    byte[0] = (data_i & (0xFFu << (0*8)));
    byte[1] = (data_i & (0xFFu << (1*8)));
    byte[2] = (data_i & (0xFFu << (2*8)));
    byte[3] = (data_i & (0xFFu << (3*8)));
    return((byte[0]<< 3*8) | (byte[1] << 1*8) | (byte[2] >> 1*8) | (byte[3] >> 3*8));
}

/**
  * @brief     Calculate message base address.
  * @retval    uint32_t
  */
static uint32_t GetMsgBAddr(uint32_t QueueBAddr, uint16_t MsgNum, uint8_t MsgMaxSize)
{
    uint32_t MsgBAddr;
    uint8_t  MsgMaxSize_b;  // padded payload size
                            // each message must be alligned by 32-bits word

    switch (MsgMaxSize % 4) {
        case 0: MsgMaxSize_b = MsgMaxSize + 0; break;
        case 1: MsgMaxSize_b = MsgMaxSize + 3; break;
        case 2: MsgMaxSize_b = MsgMaxSize + 2; break;
        case 3: MsgMaxSize_b = MsgMaxSize + 1; break;
    }

    MsgMaxSize_b = MsgMaxSize_b/(4)*(4);
    MsgBAddr     = QueueBAddr + MsgNum*(MsgHeaderSize + MsgMaxSize_b);
    return(MsgBAddr);
}

/**
  * @brief     Calculate queue element number.
  * @retval    uint16_t
  */
static uint16_t GetMsgNum(uint16_t queue_part, uint16_t queue_element)
{
    uint16_t message_number;
    message_number = queue_element + 32*queue_part;
    return(message_number);
}

/**
  * @brief     Convert Slot Number in Queue Part number
  * @param     uint16_t Slot Number
  * @retval    uint16_t Queue Part
  */
static uint16_t GetQueuePart(uint16_t SlotNum)
{
    if(                   (SlotNum <= 31)) { // (SlotNum >= 0)  &
        return(0);
    } else {
    if( (SlotNum >= 32) & (SlotNum <= 63)) {
        return(1);
    } else {
        return(2);
    }
    }
}

/**
  * @param     uint16_t Slot Number
  * @retval    uint16_t Aligned by 32 Slot Number
  */
static uint16_t AlignSlotNum(uint16_t SlotNum)
{
    if(SlotNum < 32) {
        return (SlotNum);
    } else {
        if(SlotNum < 64) {
            return (SlotNum - 32);
        } else {
            return (SlotNum - 64);
        }
    }
}

/**
  * @param     uint16_t Slot Number
  * @param     uint16_t Queue Number
  * @retval    CanFdStatus_t Status
  */
static CanFdStatus_t CheckArgs(uint16_t QNum, uint16_t SlotNum)
{
    if(QNum > 3) {
        return WRONG_ARG;
    }

    if(SlotNum > 96) {
        return WRONG_ARG;
    }

    return OK;
}

/** @} */ /* End of group CANFD_Private_Functions */

/** @} */ /* End of group CANFD */

/** @} */ /* End of group __MDR1986VK01_StdPeriph_Driver */


/******************* (C) COPYRIGHT 2022 Milandr *********
*
* END OF FILE MDR1986VK01_canfd.h */


