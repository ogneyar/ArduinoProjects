#include <avr/io.h>
#include "TWI_driver.h"                                                         

/////////////////////////////////////////////////////////////////////////////
//  Function : char Init_TWI(void)
//  Setup the TWI module
//  Baudrate    : 100kHz @ 4MHz system clock
//  Own address : OWN_ADR (Defined in TWI_driver.h)
/////////////////////////////////////////////////////////////////////////////
char twi_init(void)
  {
  TWAR = OWN_ADR;                       //Set own slave address
  TWBR = 12;                         //Set cycle time to 400 KHz
                                        // 12 -> 400 KHz measured
                                        // 72 -> 100 KHz measured
  TWCR = (1<<TWEN);                     //Enable TWI-interface
  return 1;
  }    
/////////////////////////////////////////////////////////////////////////////
//  Function : void Wait_TWI_int(void)
//  Loop until TWI interrupt flag is set
/////////////////////////////////////////////////////////////////////////////
void Wait_TWI_int(void)
  {
  while (!(TWCR & (1<<TWINT))); 
  }    
/////////////////////////////////////////////////////////////////////////////
//  Function :unsigned char Send_start(void)
//  Send a START condition to the bus and wait for the TWINT get set set to 
//  see the result. If it failed return the TWSR value, if succes return 
//  SUCCESS.
/////////////////////////////////////////////////////////////////////////////
unsigned char Send_start(void)
  {
  TWCR = ((1<<TWINT)+(1<<TWSTA)+(1<<TWEN));//Send START
    
  Wait_TWI_int();                          //Wait for TWI interrupt flag set

  if((TWSR != START)&&(TWSR != REP_START)) //If status other than START 
    return TWSR;                           //transmitted(0x08) or Repeated
  return SUCCESS;                          //START transmitted(0x10) 
                                           //-> error  and return TWSR.
                                           //If success return   SUCCESS
  }                         
/////////////////////////////////////////////////////////////////////////////
//  Function :
//  Send a STOP condition to the bus
/////////////////////////////////////////////////////////////////////////////
void Send_stop(void)
  {
  TWCR = ((1<<TWEN)+(1<<TWINT)+(1<<TWSTO)); //Send STOP condition
  }        
/////////////////////////////////////////////////////////////////////////////
//  Function : unsigned char Send_byte(unsigned char data)
//  Send one byte to the bus.
/////////////////////////////////////////////////////////////////////////////
unsigned char Send_byte(unsigned char data)
  {
  Wait_TWI_int();                           //Wait for TWI interrupt flag set

  TWDR = data;
  TWCR = ((1<<TWINT)+(1<<TWEN));            //Clear int flag to send byte 

  Wait_TWI_int();                           //Wait for TWI interrupt flag set

  if(TWSR != MTX_DATA_ACK)                  //If NACK received return TWSR
    return TWSR;
  return SUCCESS;                           //Else return SUCCESS
  } 
/////////////////////////////////////////////////////////////////////////////
//  Function : unsigned char Send_adr(unsigned char adr)                            
//  Send a SLA+W/R to the bus
/////////////////////////////////////////////////////////////////////////////
unsigned char Send_adr(unsigned char adr)
  {
  Wait_TWI_int();                           //Wait for TWI interrupt flag set

  TWDR = adr;
  TWCR = ((1<<TWINT)+(1<<TWEN));            //Clear int flag to send byte 

  Wait_TWI_int();                           //Wait for TWI interrupt flag set

  if((TWSR != MTX_ADR_ACK)&&(TWSR != MRX_ADR_ACK)) //If NACK received return
        return TWSR;                               //TWSR
    return SUCCESS;                                //Else return SUCCESS
  } 
/////////////////////////////////////////////////////////////////////////////
unsigned char Get_byte_and_ACK(void)
  {
  Wait_TWI_int();                           //Wait for TWI interrupt flag set

  //Clear int flag and enable acknowledge to receive data.
  TWCR = ((1<<TWINT)+(1<<TWEA)+(1<<TWEN));

  Wait_TWI_int();                           //Wait for TWI interrupt flag set

  return(TWDR);                             //Save received byte
  }
/////////////////////////////////////////////////////////////////////////////
unsigned char Get_byte_and_NACK(void)
  { 
  Wait_TWI_int();                           //Wait for TWI interrupt flag set

  //Clear int flag to and do not enable acknowledge to tell the slave 
  //to stop transmitting
  TWCR = ((1<<TWINT)+(1<<TWEN));            

  Wait_TWI_int();                           //Wait for TWI interrupt flag set

  return(TWDR);                             //Save received byte
  }
/////////////////////////////////////////////////////////////////////////////
