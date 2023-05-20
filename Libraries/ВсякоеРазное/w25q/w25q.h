
#ifndef _W25Q_H
#define _W25Q_H

// ���� SPI (��� ������������� �������� �� ������)
#define W25Q_SPI                &hspi1

// ��������
#define W25Q_SPI_NOP            0xFF

// ���� �� ������� ��������� CS
#define W25Q_PORT     GPIOA

// ��� �� ������� ��������� CS
#define W25Q_PIN      GPIO_PIN_4

// ����� CS � 0
#define W25Q_CS_LO() HAL_GPIO_WritePin(W25Q_PORT, W25Q_PIN, GPIO_PIN_RESET);
// ����� CS � 1
#define W25Q_CS_HI() HAL_GPIO_WritePin(W25Q_PORT, W25Q_PIN, GPIO_PIN_SET);


// ����� ������ ����������
#define W25Q_MAMORY_8           0x4014 // 1��
#define W25Q_MAMORY_16          0x4015 // 2��
#define W25Q_MAMORY_32          0x4016 // 4��

// ����� �������������
#define W25Q_WINBOND            0xEF // Winbond

// ������ ��������
#define W25Q_PAGE_LEN           256

// ������ ������� � ��
#define W25Q_SECTOR_4           0x04

// ������ ����� � ��
#define W25Q_BLOCK_64           0x40

// ���������� �������
#define W25Q_PAGE_8             0x0FFF
#define W25Q_PAGE_16            0x1FFF
#define W25Q_PAGE_32            0x3FFF


// �������
#define W25Q_WRITE_ENABLE       0X06
#define W25Q_WRRITE_DISABLE     0X04
#define W25Q_RD_STATUS_1        0x05       
#define W25Q_RD_STATUS_2        0x35
#define W25Q_WR_STATUS          0x01
#define W25Q_PAGE_PROGRAM       0x02
#define W25Q_Q_PAGE_PROGRAM     0x32
#define W25Q_BLOCK_ERASE_64     0xD8
#define W25Q_BLOCK_ERASE_32     0x52
#define W25Q_SECTOR_ERASE_4     0x20
#define W25Q_CHIP_ERASE         0xC7
#define W25Q_ERASE_SUSPEND      0X75
#define W25Q_ERASE_RESUME       0x7A
#define W25Q_POWER_DOWN         0xB9
#define W25Q_HI_PF_MODE         0xA3
#define W25Q_MODE_BIT_RESET     0xFF
#define W25Q_RS_PWR_DOUN        0xAB
#define W25Q_MNF_DEVICE_ID      0x90
#define W25Q_RD_UNIQUE_ID       0x4B
#define W25Q_JEDEC_ID           0x9F
#define W25Q_READ_PAGE          0x0B

// ������ ���������� ��������
void w25qReadStatus(uint8_t *answer, uint8_t regnum);

// �������� ������ ���� ���������
void w25qWaitForReady(void);

// ��������� �������� ���
void w25qSetBlockProtect(uint8_t protect);

// ������ ���������. 
// � �������� ��������� ��������� ������ �� 3 ������
// ����� ������ ������� � ������� �����:
//      answer[0] = ������ �������������
//      answer[1] = ������� ���� ������ ������
//      answer[2] = ������� ���� ������ ������
// ������: 0xEF, 0x40, 0x16 = W25Q32
void w25qReadManuf(uint8_t *answer);

// ������ ��������
// � �������� ��������� ��������� ������ �� 
// 256 ����� � ����� �������� ��� ������
// ����� ������ ������� � ������� ����� ������ ����������� ��������
void w25qReadPage(uint8_t *page, uint16_t pagenum);

// ������ ��������
// � �������� ��������� ��������� ������ � ������� �� 
// 256 ����� � ����� �������� ��� ������
void w25qWritePage(uint8_t *page, uint16_t pagenum);

// ������� ������� 4��
void w25qEraseSector(uint16_t sector);

// ������� ��� ������
void w25qEraseChip(void);

#endif /* _W25Q_H */