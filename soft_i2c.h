/*
 * File Name: soft_i2c.c
 * Author: Siddharth Chandrasekaran
 * Website	: http://embedjournnal.com/
 * Created on July 27, 2012, 12:12 PM
*/
//#include "../mcc_generated_files/mcc.h"


void Soft_I2C_Init();
void Soft_I2C_Start();
void Soft_I2C_Stop();
void Soft_I2C_Write(unsigned char dato_);
unsigned char Soft_I2C_Read(unsigned char ack); 

void i2cNack(void);
void i2cAck(void);
void Soft_I2C_Stop(void);
void i2cHighSda(void);
void i2cLowSda(void);
void i2cHighScl(void);
void i2cLowScl(void);

void Soft_I2C_Init()
{
Soft_I2C_Scl_Direction=0;//reloj salida
Soft_I2C_Sda_Direction=0;// SDA entrada
Soft_I2C_Scl=1; //reloj en alto
Soft_I2C_Sda=1; //sda en alto
__delay_us(5);
}

void Soft_I2C_Start()
{
 __delay_us(10);   
Soft_I2C_Scl=1;
__delay_us(5);
Soft_I2C_Sda=0; //baja el sda mientra reloj es alto
__delay_us(2);
Soft_I2C_Scl=0;
}

void Soft_I2C_Stop()
{
    Soft_I2C_Sda=0;
Soft_I2C_Scl=1; //sube sda sda mientra reloj es alto
__delay_us(5);
Soft_I2C_Sda=1;
__delay_us(20);   
    
}

void Soft_I2C_Write(unsigned char dato_)

{
 unsigned char cont_s= 0;

 for(cont_s = 0;cont_s < 8; cont_s++)
  {
    if((dato_ & 0x80) != 0) Soft_I2C_Sda=1;  //sino termina rotacion coloca un uno sino un cero
    else    Soft_I2C_Sda = 0;
    dato_ <<= 1;  //rota
    //genera un pulso del reloj
   Soft_I2C_Scl = 1;
    __delay_us(3);
    Soft_I2C_Scl=0;
    __delay_us(3);
  }
 Soft_I2C_Scl = 0;
 Soft_I2C_Sda_Direction=1; //se configura como entrada
 
 //Da pulso para que el esclavo envio el ACK o reconocimiento  
 Soft_I2C_Scl = 1;
    __delay_us(3);
    Soft_I2C_Scl=0;
    __delay_us(5);
 
    Soft_I2C_Sda_Direction=0; //se configura como salida
    Soft_I2C_Sda = 0;// deja SDA  en cero
    __delay_us(5);
 Soft_I2C_Sda = 1;// deja SDA en 1
    
 
           
}

unsigned char Soft_I2C_Read(unsigned char ack)
{
 unsigned char cont_s= 0;
  unsigned char dato_ = 0;
  
 ack =ack ^1; //invierte el recnocimeinto
  
  Soft_I2C_Sda_Direction=1;//sda como entrada
  
  for(cont_s= 0; cont_s < 8; cont_s++)
  {
      dato_ <<= 1;
      Soft_I2C_Scl = 1;
     __delay_us(3);   //retardo de lectura

      if(Soft_I2C_Sda != 0)
      {
        dato_ |= 1;
      }
      Soft_I2C_Scl = 0;
      __delay_us(3);
  }
  
    Soft_I2C_Scl = 1;
    __delay_us(3);
    Soft_I2C_Sda_Direction=0;//sda como salida
  //manda el reconocimiento
  Soft_I2C_Sda = 1;//saca reconocimiento
  Soft_I2C_Scl=0;
__delay_us(3);
  Soft_I2C_Sda = 1;// deja SDA en 1
    
  
 
    
  return (dato_);

}






//void Soft_I2C_Init();
//void Soft_I2C_Start();
//void Soft_I2C_Stop();
//void Soft_I2C_Write(unsigned char dato_);
//unsigned char Soft_I2C_Read(void); 
//
//void i2cs_nack(void);
//void i2cs_Ack(void);
//void Soft_I2C_Stop(void);
//void i2cHighSda(void);
//void i2cLowSda(void);
//void i2cHighScl(void);
//void i2cLowScl(void);
//
//
//void Soft_I2C_Init()
//{
//Soft_I2C_Scl_Direction=0;//reloj salida
//Soft_I2C_Sda_Direction=0;// SDA entrada
//Soft_I2C_Scl=1; //reloj en alto
//Soft_I2C_Sda=1; //sda en alto
//__delay_us(5);
//}
//
//void Soft_I2C_Start()
//{
// __delay_us(10);   
//Soft_I2C_Scl=1;
//__delay_us(5);
//Soft_I2C_Sda=0; //baja el sda mientra reloj es alto
//__delay_us(2);
//Soft_I2C_Scl=0;
//}
//
//void Soft_I2C_Stop()
//{
//    Soft_I2C_Sda=0;
//Soft_I2C_Scl=1; //sube sda sda mientra reloj es alto
//__delay_us(5);
//Soft_I2C_Sda=1;
//__delay_us(20);   
//    
//}
//
//void Soft_I2C_Write(unsigned char dato_)
//
//{
// unsigned char cont_s= 0;
//
// for(cont_s = 0;cont_s < 8; cont_s++)
//  {
//    if((dato_ & 0x80) != 0) Soft_I2C_Sda=1;  //sino termina rotacion coloca un uno sino un cero
//    else    Soft_I2C_Sda = 0;
//    dato_ <<= 1;  //rota
//    //genera un pulso del reloj
//   Soft_I2C_Scl = 1;
//    __delay_us(3);
//    Soft_I2C_Scl=0;
//    __delay_us(3);
//  }
// Soft_I2C_Scl = 0;
// Soft_I2C_Sda_Direction=1; //se configura como entrada
// 
// //Da pulso para que el esclavo envio el ACK o reconocimiento  
// Soft_I2C_Scl = 1;
//    __delay_us(3);
//    Soft_I2C_Scl=0;
//    __delay_us(5);
// 
//    Soft_I2C_Sda_Direction=0; //se configura como salida
//    Soft_I2C_Sda = 0;// deja SDA  en cero
//    __delay_us(5);
// Soft_I2C_Sda = 1;// deja SDA en 1
//    
// 
//           
//}
//
//unsigned char Soft_I2C_Read(void)
//{
//    unsigned char _data;
//    unsigned char _bits;
// 
//    for (_bits = 8; _bits > 0; _bits--)
//    {
//        __delay_us(5);
//        _data = _data << 1;
//        Soft_I2C_Scl_Direction = 1;
//        __delay_us(2);
//        if (Soft_I2C_Sda == 1) _data |= 1;
//        __delay_us(2);
//        Soft_I2C_Scl = 0;
//        Soft_I2C_Scl_Direction = 0;
//    }
//    return _data;
//}
//
//void i2cs_nack(void)
//{
//    __delay_us(5);
//    Soft_I2C_Sda_Direction = 1;
//    __delay_us(1);
//    Soft_I2C_Scl_Direction = 1;
//    __delay_us(4);
//    Soft_I2C_Scl = 0;
//    Soft_I2C_Scl_Direction = 0;
//    __delay_us(5);
//    Soft_I2C_Sda = 0;
//    Soft_I2C_Sda_Direction = 0;
//}
// 
//void i2cs_ack(void)
//{
//    __delay_us(5);
//    Soft_I2C_Sda = 0;
//    Soft_I2C_Sda_Direction = 0;
//    __delay_us(1);
//       Soft_I2C_Scl_Direction = 1;
//    __delay_us(4);
//    Soft_I2C_Scl = 0;
//    Soft_I2C_Scl_Direction = 0;
//    __delay_us(5);
//    Soft_I2C_Sda = 0;
//    Soft_I2C_Sda_Direction = 0;
//}









