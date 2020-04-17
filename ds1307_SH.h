
#include "../Librerias/soft_i2c.h"
//#include "../mcc_generated_files/mcc.h"



const unsigned char d_segundo=0;
const unsigned  char d_minuto=1;
const unsigned char  d_hora=2;
const unsigned char d_dia=3;
const unsigned char d_fecha=4;
const unsigned char d_mes=5;
const unsigned char d_anho=6;
const unsigned char d_control=7;
const unsigned char dir_ds1307=0b11010000;

typedef struct ds1307_estruct {
  char   _segundo,_minuto,_hora;
  char   _dia,_fecha,_mes,_anho;   //fecha es el dia de mes   dia esel dia d ela semana
  char _control;
}reloj;

 extern reloj  ds1307;   //crea una  estructura con el formato del reloj  llamada ds1307

//I2C SOFTWARE
void reloj_init_s();
void guarda_segundo_s();
void guarda_minuto_s();
void guarda_hora_s();
void guarda_dia_s();
void guarda_fecha_s();
void guarda_mes_s();
void guarda_anho_s();

void guarda_control_s();
void guardatodo_s();
unsigned char lee_segundo_s();
unsigned char lee_minuto_s();
unsigned char lee_dia_s();
unsigned char lee_hora_s();
unsigned char lee_fecha_S();
unsigned char lee_mes_S();
unsigned char lee_anho_s();
void leertodo_s();
void carga_inicial(unsigned char _seg,unsigned char _min,unsigned char _hor,unsigned char _dia,unsigned char _fecha,unsigned char _mes,unsigned char _anho);


 void UNO (unsigned int  *port, char bit1)
{
    *port |= (1 << bit1);
}
void CERO (unsigned char *port, char bit1)
{

    *port &= ~ (1 << bit1);
}

unsigned char  Bcd2Dec (unsigned char bcdByte)
{
  return (((bcdByte & 0xF0) >> 4) * 10) + (bcdByte & 0x0F);
}

unsigned char Dec2Bcd (unsigned char decimalByte)
{
  return (((decimalByte / 10) << 4) | (decimalByte % 10));
}
unsigned char Dec2Bcd1(unsigned char a) //Convert BCD to Binary so we can do some basic calculations
{
   unsigned char r,t;
   t = a & 0x0F;
   r = t;
   a = 0xF0 & a;
   t = a >> 4;
   t = 0x0F & t;
   r = t*10 + r;
   return r;
}

  void reloj_init_s()
  {
      Soft_I2C_Init();
  
  }
void carga_inicial(unsigned char _seg,unsigned char _min,unsigned char _hor,unsigned char _dia,unsigned char _fecha,unsigned char _mes, unsigned char _anho)
{
 ds1307._segundo=_seg;
 ds1307._minuto=_min;
 ds1307._hora=_hor;
 ds1307._fecha=_fecha;
 ds1307._dia=_dia;
 ds1307._mes=_mes;
 ds1307._anho=_anho;
}


void guarda_control_s()
{
unsigned char tempi;

  Soft_I2C_Start();
  Soft_I2C_Write(dir_ds1307  & 0b11111110);
  Soft_I2C_Write(d_control);
  Soft_I2C_Write(0b00010000);
  Soft_I2C_Stop();

}

unsigned char lee_segundo_s()
{
unsigned char leido;

 Soft_I2C_Start();
 Soft_I2C_Write(dir_ds1307  & 0b11111110);
 Soft_I2C_Write(d_segundo);

 Soft_I2C_Start();

 Soft_I2C_Write(dir_ds1307  | 0b00000001);

 leido= (Bcd2Dec(Soft_I2C_Read(0))) & 0b01111111;

 Soft_I2C_Stop();

return (leido);

}

unsigned char lee_minuto_s()
{
unsigned char leido;
 Soft_I2C_Start();
 Soft_I2C_Write(dir_ds1307  & 0b11111110);
 Soft_I2C_Write(d_minuto);
 Soft_I2C_Start();
 Soft_I2C_Write(dir_ds1307  | 0b00000001);
 leido= Bcd2Dec(Soft_I2C_Read(0)) & 0b01111111;
 Soft_I2C_Stop();
return (leido);

}

unsigned char lee_dia_s()
{
unsigned char leido;

 Soft_I2C_Start();
 Soft_I2C_Write(dir_ds1307  & 0b11111110);
 Soft_I2C_Write(d_dia);

 Soft_I2C_Start();

 Soft_I2C_Write(dir_ds1307  | 0b00000001);

 leido= (Bcd2Dec(Soft_I2C_Read(0))) & 0b000001111;

 Soft_I2C_Stop();

return (leido);

}

unsigned char lee_hora_s()
{
unsigned char leido;

 Soft_I2C_Start();
 Soft_I2C_Write(dir_ds1307  & 0b11111110);
 Soft_I2C_Write(d_hora);

 Soft_I2C_Start();

 Soft_I2C_Write(dir_ds1307  | 0b00000001);

 leido= (Bcd2Dec(Soft_I2C_Read(0))) & 0b001111111;
 

 Soft_I2C_Stop();

return (leido);

}
unsigned char lee_fecha_s()
{
unsigned char leido;

 Soft_I2C_Start();
 Soft_I2C_Write(dir_ds1307  & 0b11111110);
 Soft_I2C_Write(d_fecha);
 Soft_I2C_Start();

 Soft_I2C_Write(dir_ds1307  | 0b00000001);

 leido= (Bcd2Dec(Soft_I2C_Read(0))) & 0b00111111;
 Soft_I2C_Stop();

return (leido);

}
unsigned char lee_mes_s()
{
unsigned char leido;

 Soft_I2C_Start();
 Soft_I2C_Write(dir_ds1307  & 0b11111110);
 Soft_I2C_Write(d_mes);
 Soft_I2C_Start();
 Soft_I2C_Write(dir_ds1307  | 0b00000001);
 leido= (Bcd2Dec(Soft_I2C_Read(0))) & 0b000111111;

 Soft_I2C_Stop();

return (leido);

}
unsigned char lee_anho_s()
{
unsigned char leido;

 Soft_I2C_Start();
 Soft_I2C_Write(dir_ds1307  & 0b11111110);
 Soft_I2C_Write(d_anho);
 Soft_I2C_Start();
 Soft_I2C_Write(dir_ds1307  | 0b00000001);
 leido= (Bcd2Dec(Soft_I2C_Read(0))) & 0b111111111;

 Soft_I2C_Stop();

return (leido);

}


void guarda_segundo_s()
{
unsigned char tempi;

tempi=Dec2Bcd(ds1307._segundo);
CERO(&tempi,7);
  Soft_I2C_Start();
  Soft_I2C_Write(dir_ds1307  & 0b11111110);
  Soft_I2C_Write(d_segundo);
  Soft_I2C_Write(tempi);
  Soft_I2C_Stop();

}

void guarda_minuto_s()
{
unsigned char tempi;

tempi=Dec2Bcd(ds1307._minuto);
CERO(&tempi,7);

  Soft_I2C_Start();
  Soft_I2C_Write(dir_ds1307  & 0b11111110);
  Soft_I2C_Write(d_minuto);
  Soft_I2C_Write(tempi);
  Soft_I2C_Stop();

}

void guarda_hora_s()
{
unsigned char tempi;

tempi=Dec2Bcd(ds1307._hora);
CERO(&tempi,7);
CERO(&tempi,6);  //para 24 horas

  Soft_I2C_Start();
  Soft_I2C_Write(dir_ds1307  & 0b11111110);
  Soft_I2C_Write(d_hora);
  Soft_I2C_Write(tempi);
  Soft_I2C_Stop();

}
void guarda_dia_s()
{
unsigned char tempi;

tempi=Dec2Bcd(ds1307._dia);
CERO(&tempi,7);
CERO(&tempi,6);
CERO(&tempi,5);
CERO(&tempi,4);
CERO(&tempi,3);

  Soft_I2C_Start();
  Soft_I2C_Write(dir_ds1307  & 0b11111110);
  Soft_I2C_Write(d_dia);
  Soft_I2C_Write(tempi);
  Soft_I2C_Stop();

}

void guarda_fecha_s()
{
unsigned char tempi;

tempi=Dec2Bcd(ds1307._fecha);
CERO(&tempi,7);
CERO(&tempi,6);

  Soft_I2C_Start();
  Soft_I2C_Write(dir_ds1307  & 0b11111110);
  Soft_I2C_Write(d_fecha);
  Soft_I2C_Write(tempi);
  Soft_I2C_Stop();

}
void guarda_mes_s()
{
unsigned char tempi;

tempi=Dec2Bcd(ds1307._mes);
CERO(&tempi,7);

  Soft_I2C_Start();
  Soft_I2C_Write(dir_ds1307  & 0b11111110);
  Soft_I2C_Write(d_mes);
  Soft_I2C_Write(tempi);
  Soft_I2C_Stop();

}
void guarda_anho_s()
{
unsigned int  tempi;

tempi=Dec2Bcd(ds1307._anho);

  Soft_I2C_Start();
  Soft_I2C_Write(dir_ds1307  & 0b11111110);
  Soft_I2C_Write(d_anho);
  Soft_I2C_Write(tempi);
  Soft_I2C_Stop();

}

void guardatodo_s()
{
guarda_control_s();
guarda_segundo_s();
guarda_minuto_s();
guarda_hora_s();
guarda_dia_s();
guarda_mes_s();
guarda_fecha_s();
guarda_anho_s();
 }

void leertodo_s()
{
ds1307._segundo=lee_segundo_s();
ds1307._minuto=lee_minuto_s();
ds1307._dia=lee_dia_s();
ds1307._fecha=lee_fecha_s();
ds1307._hora=lee_hora_s();
ds1307._mes=lee_mes_s();
ds1307._anho=lee_anho_s();
}





//const unsigned char d_segundo=0;
//const unsigned char d_minuto=1;
//const unsigned char  d_hora=2;
//const unsigned char d_dia=3;
//const unsigned char d_fecha=4;
//const unsigned char d_mes=5;
//const unsigned char d_anho=6;
//const unsigned char d_control=7;
//const unsigned char dir_ds1307=0b11010000;
//
//typedef struct ds1307_estruct 
//{
//    char   _segundo,_minuto,_hora;
//    char   _dia,_fecha,_mes,_anho;   //fecha es el dia de mes   dia esel dia d ela semana
//    char _control;
//}reloj;
//
// extern reloj  ds1307;   //crea una  estructura con el formato del reloj  llamada ds1307
//
////I2C SOFTWARE
//void reloj_init_s();
//void guarda_segundo_s();
//void guarda_minuto_s();
//void guarda_hora_s();
//void guarda_dia_s();
//void guarda_fecha_s();
//void guarda_mes_s();
//void guarda_anho_s();
//
//void guarda_control_s();
//void guardatodo_s();
//unsigned char lee_segundo_s();
//unsigned char lee_minuto_s();
//unsigned char lee_dia_s();
//unsigned char lee_hora_s();
//unsigned char lee_fecha_S();
//unsigned char lee_mes_S();
//unsigned char lee_anho_s();
//void leertodo_s();
//void carga_inicial(unsigned char _seg,unsigned char _min,unsigned char _hor,unsigned char _dia,unsigned char _fecha,unsigned char _mes,unsigned char _anho);
//
//
// void UNO (unsigned int  *port, char bit1)
//{
//    *port |= (1 << bit1);
//}
//void CERO (unsigned char *port, char bit1)
//{
//
//    *port &= ~ (1 << bit1);
//}
//
//unsigned char  Bcd2Dec (unsigned char bcdByte)
//{
//  return (((bcdByte & 0xF0) >> 4) * 10) + (bcdByte & 0x0F);
//}
//
//unsigned char Dec2Bcd (unsigned char decimalByte)
//{
//  return (((decimalByte / 10) << 4) | (decimalByte % 10));
//}
//
//unsigned char Dec2Bcd1(unsigned char a) //Convert BCD to Binary so we can do some basic calculations
//{
//   unsigned char r,t;
//   t = a & 0x0F;
//   r = t;
//   a = 0xF0 & a;
//   t = a >> 4;
//   t = 0x0F & t;
//   r = t*10 + r;
//   return r;
//}
//
//  
//void carga_inicial(unsigned char _seg,unsigned char _min,unsigned char _hor,unsigned char _dia,unsigned char _fecha,unsigned char _mes, unsigned char _anho)
//{
// ds1307._segundo=_seg;
// ds1307._minuto=_min;
// ds1307._hora=_hor;
// ds1307._fecha=_fecha;
// ds1307._dia=_dia;
// ds1307._mes=_mes;
// ds1307._anho=_anho;
//}
//
//
//void guarda_control_s()
//{
//unsigned char tempi;
//
//  Soft_I2C_Start();
//  Soft_I2C_Write(dir_ds1307  & 0b11111110);
//  Soft_I2C_Write(d_control);
//  Soft_I2C_Write(0b00010000);
//  Soft_I2C_Stop();
//
//}
//
//unsigned char lee_segundo_s()
//{
//unsigned char leido;
//
// Soft_I2C_Start();
// Soft_I2C_Write(dir_ds1307  & 0b11111110);
// Soft_I2C_Write(d_segundo);
//
// Soft_I2C_Start();
//
// Soft_I2C_Write(dir_ds1307  | 0b00000001);
//
// leido= (Bcd2Dec(Soft_I2C_Read())) & 0b01111111;
//
// Soft_I2C_Stop();
//
//return (leido);
//
//}
//
//unsigned char lee_minuto_s()
//{
//unsigned char leido;
// Soft_I2C_Start();
// Soft_I2C_Write(dir_ds1307  & 0b11111110);
// Soft_I2C_Write(d_minuto);
// Soft_I2C_Start();
// Soft_I2C_Write(dir_ds1307  | 0b00000001);
// leido= Bcd2Dec(Soft_I2C_Read()) & 0b01111111;
// Soft_I2C_Stop();
//return (leido);
//
//}
//
//unsigned char lee_dia_s()
//{
//unsigned char leido;
//
// Soft_I2C_Start();
// Soft_I2C_Write(dir_ds1307  & 0b11111110);
// Soft_I2C_Write(d_dia);
//
// Soft_I2C_Start();
//
// Soft_I2C_Write(dir_ds1307  | 0b00000001);
//
// leido= (Bcd2Dec(Soft_I2C_Read())) & 0b000001111;
//
// Soft_I2C_Stop();
//
//return (leido);
//
//}
//
//unsigned char lee_hora_s()
//{
//unsigned char leido;
//
// Soft_I2C_Start();
// Soft_I2C_Write(dir_ds1307 & 0b11111110);
// Soft_I2C_Write(d_hora);
//
// Soft_I2C_Start();
//
// Soft_I2C_Write(dir_ds1307 | 0b00000001);
//
// leido= (Bcd2Dec(Soft_I2C_Read())) & 0b001111111;
// 
//
// Soft_I2C_Stop();
//
//return (leido);
//
//}
//unsigned char lee_fecha_s()
//{
//unsigned char leido;
//
// Soft_I2C_Start();
// Soft_I2C_Write(dir_ds1307  & 0b11111110);
// Soft_I2C_Write(d_fecha);
// Soft_I2C_Start();
//
// Soft_I2C_Write(dir_ds1307  | 0b00000001);
//
// leido= (Bcd2Dec(Soft_I2C_Read())) & 0b00111111;
// Soft_I2C_Stop();
//
//return (leido);
//
//}
//unsigned char lee_mes_s()
//{
//unsigned char leido;
//
// Soft_I2C_Start();
// Soft_I2C_Write(dir_ds1307  & 0b11111110);
// Soft_I2C_Write(d_mes);
// Soft_I2C_Start();
// Soft_I2C_Write(dir_ds1307  | 0b00000001);
// leido= (Bcd2Dec(Soft_I2C_Read())) & 0b000111111;
//
// Soft_I2C_Stop();
//
//return (leido);
//
//}
//unsigned char lee_anho_s()
//{
//unsigned char leido;
//
// Soft_I2C_Start();
// Soft_I2C_Write(dir_ds1307  & 0b11111110);
// Soft_I2C_Write(d_anho);
// Soft_I2C_Start();
// Soft_I2C_Write(dir_ds1307  | 0b00000001);
// leido= (Bcd2Dec(Soft_I2C_Read())) & 0b111111111;
//
// Soft_I2C_Stop();
//
//return (leido);
//
//}
//
//
//void guarda_segundo_s()
//{
//unsigned char tempi;
//
//tempi=Dec2Bcd(ds1307._segundo);
//CERO(&tempi,7);
//  Soft_I2C_Start();
//  Soft_I2C_Write(dir_ds1307  & 0b11111110);
//  Soft_I2C_Write(d_segundo);
//  Soft_I2C_Write(tempi);
//  Soft_I2C_Stop();
//
//}
//
//void guarda_minuto_s()
//{
//unsigned char tempi;
//
//tempi=Dec2Bcd(ds1307._minuto);
//CERO(&tempi,7);
//
//  Soft_I2C_Start();
//  Soft_I2C_Write(dir_ds1307  & 0b11111110);
//  Soft_I2C_Write(d_minuto);
//  Soft_I2C_Write(tempi);
//  Soft_I2C_Stop();
//
//}
//
//void guarda_hora_s()
//{
//unsigned char tempi;
//
//tempi=Dec2Bcd(ds1307._hora);
//CERO(&tempi,7);
//CERO(&tempi,6);  //para 24 horas
//
//  Soft_I2C_Start();
//  Soft_I2C_Write(dir_ds1307  & 0b11111110);
//  Soft_I2C_Write(d_hora);
//  Soft_I2C_Write(tempi);
//  Soft_I2C_Stop();
//
//}
//void guarda_dia_s()
//{
//unsigned char tempi;
//
//tempi=Dec2Bcd(ds1307._dia);
//CERO(&tempi,7);
//CERO(&tempi,6);
//CERO(&tempi,5);
//CERO(&tempi,4);
//CERO(&tempi,3);
//
//  Soft_I2C_Start();
//  Soft_I2C_Write(dir_ds1307  & 0b11111110);
//  Soft_I2C_Write(d_dia);
//  Soft_I2C_Write(tempi);
//  Soft_I2C_Stop();
//
//}
//
//void guarda_fecha_s()
//{
//unsigned char tempi;
//
//tempi=Dec2Bcd(ds1307._fecha);
//CERO(&tempi,7);
//CERO(&tempi,6);
//
//  Soft_I2C_Start();
//  Soft_I2C_Write(dir_ds1307  & 0b11111110);
//  Soft_I2C_Write(d_fecha);
//  Soft_I2C_Write(tempi);
//  Soft_I2C_Stop();
//
//}
//void guarda_mes_s()
//{
//unsigned char tempi;
//
//tempi=Dec2Bcd(ds1307._mes);
//CERO(&tempi,7);
//
//  Soft_I2C_Start();
//  Soft_I2C_Write(dir_ds1307  & 0b11111110);
//  Soft_I2C_Write(d_mes);
//  Soft_I2C_Write(tempi);
//  Soft_I2C_Stop();
//
//}
//void guarda_anho_s()
//{
//unsigned int  tempi;
//
//tempi=Dec2Bcd(ds1307._anho);
//
//  Soft_I2C_Start();
//  Soft_I2C_Write(dir_ds1307  & 0b11111110);
//  Soft_I2C_Write(d_anho);
//  Soft_I2C_Write(tempi);
//  Soft_I2C_Stop();
//
//}
//
//void guardatodo_s()
//{
//guarda_control_s();
//guarda_segundo_s();
//guarda_minuto_s();
//guarda_hora_s();
//guarda_dia_s();
//guarda_mes_s();
//guarda_fecha_s();
//guarda_anho_s();
// }
//
//void leertodo_s()
//{
//ds1307._segundo=lee_segundo_s();
//ds1307._minuto=lee_minuto_s();
//ds1307._dia=lee_dia_s();
//ds1307._fecha=lee_fecha_s();
//ds1307._hora=lee_hora_s();
//ds1307._mes=lee_mes_s();
//ds1307._anho=lee_anho_s();
//}
//
//
//
//void reloj_init_s()
//  {
//      Soft_I2C_Init();
//  
//  }