
#include "reg51.h"
#include "stdio.h"

sbit   RST   = P3^0;
sbit   CD    = P3^1;  // RS
sbit   RW    = P3^4;
sbit   E     = P3^3;

sbit  BUSY   = P1^7;

#define uchar  unsigned char 
#define uint   unsigned int

code uchar pho1[]={"????????????!!"};

code uchar table_8[]=
  {0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff};

 void Delay(uint t)
 {
  while(t!=0) t--;
 }

 
void CHECK_BUSY(void)
 {uchar dat;
    do
    {
	  P1=0XFF;
	  CD=0;
	  RW=1;
	  E=1;
      dat=P1;
      E=0;
    } while(dat&0x80);
 }

 void WCOM(uchar cmd)
 { CHECK_BUSY();
    
   CD=0;

   RW=0;
   E=1;
   Delay(1);
   P1=cmd;
   Delay(1);
   E=0;
 
	 
 }



  void WDATA(uchar dat)
 { 
   CHECK_BUSY(); 
   CD=1;

   RW=0;
   E=1; 
   Delay(1);
   P1=dat;
   Delay(1);
   E=0;
 }


 void  INI()
 {  RST=0;
    Delay(100);
	RST=1;
	Delay(8000);
	WCOM(0x30);    //funtion set 8 bit
	Delay(10);
    WCOM(0x30);    //   
    Delay(10);
	WCOM(0x0c);    // display on
    Delay(10);
	WCOM(0x01);    // clear display
    Delay(10);
	WCOM(0x06);    //ENTRY MODE SET
    Delay(100);

  }

void clear_D(void)
    {	WCOM(0x30);    //funtion set 8 bit
        WCOM(0x01);    // clear display
    }



void clear_G(void)  //write at graphic mode
  {  uchar x,y;
       WCOM(0x34);    //   extened   grahpic on
	   
       for(y=0;y<32;y++)
         {
		  WCOM(0x80+y);
          WCOM(0x80);
          for(x=0;x<15;x++)
             {WDATA(0x00);
              WDATA(0x00);
			 }

	     }
      WCOM(0x36);
	  WCOM(0x30);
  }


 
void clear(void)
  {clear_G();
   clear_D();
  }

 




  void full_dotmatrix_AS_GRAPHIC(uchar dat1,dat2)  //write at graphic mode
  {  uchar x,y;
       WCOM(0x34);    //   extened   grahpic on
	  
       for(y=0;y<17;y++)
         {
		  WCOM(0x80+y);
          WCOM(0x80);
          y++;
          for(x=0;x<13;x++)
             {WDATA(dat1);
              WDATA(dat1);

             }
          WCOM(0x80+y);
          WCOM(0x80);
          for(x=0;x<13;x++)
             {WDATA(dat2);
              WDATA(dat2);
             }

	     }
        WCOM(0x36);
        WCOM(0X30);
  }
    








  void FRAME(void)
   {uchar x,y;
    WCOM(0X34);
    WCOM(0X80);
    WCOM(0X80);
    for(x=0;x<13;x++)
			{WDATA(0xff);
             WDATA(0xff);
             }    
    for(y=1;y<15;y++)
        { WCOM(0X80+y);    //x
          WCOM(0X80);    //y

          WDATA(0x80);
          WDATA(0x00);


          WCOM(0X80+y);    //x
          WCOM(0X80+12);    //y
		  WDATA(0x00);
          WDATA(0x01);
         }
    WCOM(0X80+15);
    WCOM(0X80);
    for(x=0;x<13;x++)
			{WDATA(0xff);
             WDATA(0xff);
             }
    WCOM(0X36);
	WCOM(0X30);
   }

 void WRITE_CGRAM(void)
   { uchar i;
     WCOM(0X34);
     WCOM(0X02);
     WCOM(0x30);
     WCOM(0x40);// set CGRAM ADDRESS
     for(i=0;i<16;i++)   // 0000H ???
       { WDATA(0XFF);
         WDATA(0XFF);
       } 
        
       
	//     WCOM(0x40+16);                    // 0002H ??2 +Dn
         WDATA(0X00);  //Pn
         WDATA(0X00);  //Pn
         WDATA(0XFF);  //A
         WDATA(0XFF);  //A
         WDATA(0X00);  //F
         WDATA(0X00);  //F 
         WDATA(0XFF);  //B
         WDATA(0XFF);  //B
         WDATA(0XFF);  //G
         WDATA(0XFF);  //G
         WDATA(0XFF);  //E
         WDATA(0XFF);  //E
         WDATA(0X00);  //C
         WDATA(0X00);  //C
         WDATA(0XFF);  //D
         WDATA(0XFF);  //D
         WDATA(0XFF);  //Dn
         WDATA(0XFF);  //Dn
         WDATA(0XFF);  //A
         WDATA(0XFF);  //A
         WDATA(0X00);  //F
         WDATA(0X00);  //F 
         WDATA(0XFF);  //B
         WDATA(0XFF);  //B
         WDATA(0XFF);  //G
         WDATA(0XFF);  //G
         WDATA(0XFF);  //E
         WDATA(0XFF);  //E
         WDATA(0X00);  //C
         WDATA(0X00);  //C
         WDATA(0XFF);  //D
         WDATA(0XFF);  //D


   //      WCOM(0x40+16*2);              //004  ?? 5+Pn
	
        WDATA(0Xff);  //Pn
         WDATA(0Xff);  //Pn
         WDATA(0XFF);  //A
         WDATA(0XFF);  //A
         WDATA(0Xff);  //F
         WDATA(0Xff);  //F 
         WDATA(0X00);  //B
         WDATA(0X00);  //B
         WDATA(0XFF);  //G
         WDATA(0XFF);  //G
         WDATA(0X00);  //E
         WDATA(0X00);  //E
         WDATA(0Xff);  //C
         WDATA(0Xff);  //C
         WDATA(0XFF);  //D
         WDATA(0XFF);  //D
         WDATA(0X00);  //Dn
         WDATA(0X00);  //Dn
         WDATA(0XFF);  //A
         WDATA(0XFF);  //A
         WDATA(0Xff);  //F
         WDATA(0Xff);  //F 
         WDATA(0X00);  //B
         WDATA(0X00);  //B
         WDATA(0XFF);  //G
         WDATA(0XFF);  //G
         WDATA(0X00);  //E
         WDATA(0X00);  //E
         WDATA(0Xff);  //C
         WDATA(0Xff);  //C
         WDATA(0XFF);  //D
         WDATA(0XFF);  //D

    //     WCOM(0x40+16*3);                             //006 ??8 

        WDATA(0X00);  //Pn
         WDATA(0X00);  //Pn
         WDATA(0XFF);  //A
         WDATA(0XFF);  //A
         WDATA(0Xff);  //F
         WDATA(0Xff);  //F 
         WDATA(0Xff);  //B
         WDATA(0Xff);  //B
         WDATA(0XFF);  //G
         WDATA(0XFF);  //G
         WDATA(0Xff);  //E
         WDATA(0Xff);  //E
         WDATA(0Xff);  //C
         WDATA(0Xff);  //C
         WDATA(0XFF);  //D
         WDATA(0XFF);  //D
         WDATA(0X00);  //Dn
         WDATA(0X00);  //Dn
         WDATA(0XFF);  //A
         WDATA(0XFF);  //A
         WDATA(0Xff);  //F
         WDATA(0Xff);  //F 
         WDATA(0Xff);  //B
         WDATA(0Xff);  //B
         WDATA(0XFF);  //G
         WDATA(0XFF);  //G
         WDATA(0Xff);  //E
         WDATA(0Xff);  //E
         WDATA(0Xff);  //C
         WDATA(0Xff);  //C
         WDATA(0XFF);  //D
         WDATA(0XFF);  //D      



   }
  

  void write_dotmatirx_AS_DDRAM(uchar pho[],n)
   { uchar i;
      WCOM(0x30);
      WCOM(0x80);
	  for(i=0;i<(n*2);i++)
	   { WDATA(pho[i]);
		i++;
		WDATA(pho[i]);
	   }
   }

   void write_segment_as_DDRAM(uchar  CGRAM_CODE_H,CGRAM_CODE_L)
   {  WCOM(0X30);
      Delay(1);
      WCOM(0X90+13);
	  WDATA(CGRAM_CODE_H);
	  WDATA(CGRAM_CODE_L);

	  WDATA(CGRAM_CODE_H);
	  WDATA(CGRAM_CODE_L);

   }
   

  void main(void)
  {  INI();
     
     while(1)
	   {WRITE_CGRAM();
	    clear();
	    
	    full_dotmatrix_AS_GRAPHIC(0xff,0xff);
	    write_segment_as_DDRAM(0X00,0X00);  //quan xian
	    Delay(50000);
		Delay(50000);
		Delay(50000);
		clear();

	
		FRAME();
      	write_segment_as_DDRAM(0X00,0X02);  //2
	    Delay(50000);
		Delay(50000);
		Delay(50000);

		clear();
		
		full_dotmatrix_AS_GRAPHIC(0xff,0x00);
	    write_segment_as_DDRAM(0X00,0X04);  //5
		Delay(50000);
		Delay(50000);
		Delay(50000);
		Delay(50000);

		clear();
		full_dotmatrix_AS_GRAPHIC(0xaa,0xaa);
	    write_segment_as_DDRAM(0X00,0X06);  //8
		Delay(50000);
		Delay(50000);
		Delay(50000);
		Delay(50000);

	    clear();
		full_dotmatrix_AS_GRAPHIC(0xaa,0x55);
		Delay(50000);
		Delay(50000);
		Delay(50000);
		Delay(50000);

		clear();
        write_dotmatirx_AS_DDRAM(pho1,13);
		Delay(50000);
		Delay(50000);
		Delay(50000);
		Delay(50000);

	   }
  }
