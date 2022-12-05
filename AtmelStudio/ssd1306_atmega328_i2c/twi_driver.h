#ifndef TWI_DRIVER_H_
#define TWI_DRIVER_H_
// 2000 / 12 / 05: Original source is AVR155 by Asmund Saetre
// 2010 / 01 / 07: This code was modified heavily by Crystalfontz. -BAC
 
/////////////////////////////////////////////////////////////////////////////
char twi_init(void);
void Wait_TWI_int(void);
unsigned char   Send_start(void);
void Send_stop(void);
unsigned char Send_byte(unsigned char data);
unsigned char Send_adr(unsigned char adr);
unsigned char Get_byte_and_ACK(void);
unsigned char Get_byte_and_NACK(void);

/////////////////////////////////////////////////////////////////////////////
#define W               0                   //Data transfer direction WRITE
#define R               1                   //Data transfer direction READ
#define SUCCESS         0xFF
#define OWN_ADR         0x78                  //Own slave address

/////////////////////////////////////////////////////////////////////////////
// TWI Stautus register definitions
/////////////////////////////////////////////////////////////////////////////
//General Master staus codes                                            
#define START       0x08                    //START has been transmitted    
#define REP_START   0x10                    //Repeated START has been 
                                            //transmitted       
//Master Transmitter staus codes                                            
#define MTX_ADR_ACK     0x18                //SLA+W has been tramsmitted
                                            //and ACK received  
#define MTX_ADR_NACK    0x20                //SLA+W has been tramsmitted
                                            //and NACK received     
#define MTX_DATA_ACK    0x28                //Data byte has been tramsmitted
                                            //and ACK received          
#define MTX_DATA_NACK   0x30                //Data byte has been tramsmitted
                                            //and NACK received         
#define MTX_ARB_LOST    0x38                //Arbitration lost in SLA+W or 
                                            //data bytes    
//Master Receiver staus codes   
#define MRX_ARB_LOST    0x38                //Arbitration lost in SLA+R or 
                                            //NACK bit
#define MRX_ADR_ACK     0x40                //SLA+R has been tramsmitted
                                            //and ACK received  
#define MRX_ADR_NACK    0x48                //SLA+R has been tramsmitted
                                            //and NACK received     
#define MRX_DATA_ACK    0x50                //Data byte has been received
                                            //and ACK tramsmitted
#define MRX_DATA_NACK   0x58                //Data byte has been received
                                            //and NACK tramsmitted
/////////////////////////////////////////////////////////////////////////////
#endif
