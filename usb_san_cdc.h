/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                            usb_san_cdc.h                        ////
//////////////http://br.groups.yahoo.com/group/GrupoSanUSB///////////////


//api for the user:
#define usb_cdc_kbhit() (usb_cdc_get_buffer_status.got)
#define usb_cdc_putready() (usb_cdc_put_buffer_nextin<USB_CDC_DATA_IN_SIZE)
#define usb_cdc_connected() (usb_cdc_got_set_line_coding)
void usb_cdc_putc_fast(char c);
char usb_cdc_getc(void);
void usb_cdc_putc(char c);

//input.c ported to use CDC:
float get_float_usb();
signed long get_long_usb();
signed int get_int_usb();
void get_string_usb(char* s, int max);
BYTE gethex_usb();
BYTE gethex1_usb();

//functions automatically called by USB handler code
void usb_isr_tkn_cdc(void);
void usb_cdc_init(void);
void usb_isr_tok_out_cdc_control_dne(void);
void usb_isr_tok_in_cdc_data_dne(void);
void usb_isr_tok_out_cdc_data_dne(void);

void usb_cdc_flush_out_buffer(void);

//Tells the CCS PIC USB firmware to include HID handling code.
#DEFINE USB_HID_DEVICE  FALSE
#DEFINE USB_CDC_DEVICE  TRUE

#define USB_CDC_COMM_IN_ENDPOINT       1
#define USB_CDC_COMM_IN_SIZE           8
#define USB_EP1_TX_ENABLE  USB_ENABLE_INTERRUPT
#define USB_EP1_TX_SIZE  USB_CDC_COMM_IN_SIZE

//pic to pc endpoint config
#define USB_CDC_DATA_IN_ENDPOINT       2
#define USB_CDC_DATA_IN_SIZE           64
#define USB_EP2_TX_ENABLE  USB_ENABLE_BULK
#define USB_EP2_TX_SIZE  USB_CDC_DATA_IN_SIZE

//pc to pic endpoint config
#define USB_CDC_DATA_OUT_ENDPOINT       2
#define USB_CDC_DATA_OUT_SIZE           64
#define USB_EP2_RX_ENABLE  USB_ENABLE_BULK
#define USB_EP2_RX_SIZE  USB_CDC_DATA_OUT_SIZE

/////////////////////////////////////////////////////////////////////////////
//
// Include the CCS USB Libraries.  See the comments at the top of these
// files for more information
//
/////////////////////////////////////////////////////////////////////////////
#ifndef __USB_PIC_PERIF__
#define __USB_PIC_PERIF__	1
#endif

#if __USB_PIC_PERIF__
 #if defined(__PCM__)
  #error CDC requires bulk mode!  PIC16C7x5 does not have bulk mode
 #else
  #include <pic18_usb.h>   //Microchip 18Fxx5x hardware layer for usb.c
 #endif
#else
 #include <usbn960x.c>   //National 960x hardware layer for usb.c
#endif
#include <usb_san_desc.h>	//USB Configuration and Device descriptors for this UBS device
#include <usb.c>        //handles usb setup tokens and get descriptor reports

struct {
        int32   dwDTERrate;   //data terminal rate, in bits per second
        int8    bCharFormat;  //num of stop bits (0=1, 1=1.5, 2=2)
        int8    bParityType;  //parity (0=none, 1=odd, 2=even, 3=mark, 4=space)
        int8    bDataBits;    //data bits (5,6,7,8 or 16)
} usb_cdc_line_coding;

//length of time, in ms, of break signal as we received in a SendBreak message.
//if ==0xFFFF, send break signal until we receive a 0x0000.
int16 usb_cdc_break;

int8 usb_cdc_encapsulated_cmd[8];

int8 usb_cdc_put_buffer[USB_CDC_DATA_IN_SIZE];
int1 usb_cdc_put_buffer_free;
#if USB_CDC_DATA_IN_SIZE>=0x100
 int16 usb_cdc_put_buffer_nextin=0;
// int16 usb_cdc_last_data_packet_size;
#else
 int8 usb_cdc_put_buffer_nextin=0;
// int8 usb_cdc_last_data_packet_size;
#endif

struct {
   int1 got;
  #if USB_CDC_DATA_OUT_SIZE>=0x100
   int16 len;
   int16 index;
  #else
   int8 len;
   int8 index;
  #endif
} usb_cdc_get_buffer_status;

int8 usb_cdc_get_buffer_status_buffer[USB_CDC_DATA_OUT_SIZE];
#if (defined(__PIC__))
 #if __PIC__
  //#locate usb_cdc_get_buffer_status_buffer=0x500+(2*USB_MAX_EP0_PACKET_LENGTH)+USB_CDC_COMM_IN_SIZE
  #if USB_MAX_EP0_PACKET_LENGTH==8
     #locate usb_cdc_get_buffer_status_buffer=0x500+24
  #elif USB_MAX_EP0_PACKET_LENGTH==64
     #locate usb_cdc_get_buffer_status_buffer=0x500+136
  #else
   #error CCS BUG WONT LET ME USE MATH IN LOCATE
  #endif
 #endif
#endif

int1 usb_cdc_got_set_line_coding;

struct  {
   int1 dte_present; //1=DTE present, 0=DTE not present
   int1 active;      //1=activate carrier, 0=deactivate carrier
   int reserved:6;
} usb_cdc_carrier;

enum {USB_CDC_OUT_NOTHING=0, USB_CDC_OUT_COMMAND=1, USB_CDC_OUT_LINECODING=2, USB_CDC_WAIT_0LEN=3} __usb_cdc_state=0;

#byte INTCON=0xFF2
#bit INT_GIE=INTCON.7

//handle OUT token done interrupt on endpoint 0 [read encapsulated cmd and line coding data]
void usb_isr_tok_out_cdc_control_dne(void) {
   debug_usb(debug_putc,"CDC %X ",__usb_cdc_state);

   switch (__usb_cdc_state) {
      //printf(putc_tbe,"@%X@\r\n", __usb_cdc_state);
      case USB_CDC_OUT_COMMAND:
         //usb_get_packet(0, usb_cdc_encapsulated_cmd, 8);
         memcpy(usb_cdc_encapsulated_cmd, usb_ep0_rx_buffer,8);
        #if USB_MAX_EP0_PACKET_LENGTH==8
         __usb_cdc_state=USB_CDC_WAIT_0LEN;
         usb_request_get_data();
        #else
         usb_put_0len_0();
         __usb_cdc_state=0;
        #endif
         break;

    #if USB_MAX_EP0_PACKET_LENGTH==8
      case USB_CDC_WAIT_0LEN:
         usb_put_0len_0();
         __usb_cdc_state=0;
         break;
    #endif

      case USB_CDC_OUT_LINECODING:
         //usb_get_packet(0, &usb_cdc_line_coding, 7);
         //printf(putc_tbe,"\r\n!GSLC FIN!\r\n");
         memcpy(&usb_cdc_line_coding, usb_ep0_rx_buffer,7);
         __usb_cdc_state=0;
         usb_put_0len_0();
         break;

      default:
         __usb_cdc_state=0;
         usb_init_ep0_setup();
         break;
   }
}

//handle IN token on 0 (setup packet)
void usb_isr_tkn_cdc(void) {
   //make sure the request goes to a CDC interface
   if ((usb_ep0_rx_buffer[4] == 1) || (usb_ep0_rx_buffer[4] == 0)) {
      //printf(putc_tbe,"!%X!\r\n", usb_ep0_rx_buffer[1]);
      switch(usb_ep0_rx_buffer[1]) {
         case 0x00:  //send_encapsulated_command
            __usb_cdc_state=USB_CDC_OUT_COMMAND;
            usb_request_get_data();
            break;

         case 0x01:  //get_encapsulated_command
            memcpy(usb_ep0_tx_buffer, usb_cdc_encapsulated_cmd, 8);
            usb_request_send_response(usb_ep0_rx_buffer[6]);  //send wLength bytes
            break;

         case 0x20:  //set_line_coding
            debug_usb(debug_putc,"!GSLC!");
            __usb_cdc_state=USB_CDC_OUT_LINECODING;
            usb_cdc_got_set_line_coding=TRUE;
            usb_request_get_data();
            break;

         case 0x21:  //get_line_coding
            memcpy(usb_ep0_tx_buffer, &usb_cdc_line_coding, sizeof(usb_cdc_line_coding));
            usb_request_send_response(sizeof(usb_cdc_line_coding)); //send wLength bytes
            break;

         case 0x22:  //set_control_line_state
            usb_cdc_carrier=usb_ep0_rx_buffer[2];
            usb_put_0len_0();
            break;

         case 0x23:  //send_break
            usb_cdc_break=make16(usb_ep0_rx_buffer[2],usb_ep0_rx_buffer[3]);
            usb_put_0len_0();
            break;

         default:
            usb_request_stall();
            break;
      }
   }
}

//handle OUT token done interrupt on endpoint 3 [buffer incoming received chars]
void usb_isr_tok_out_cdc_data_dne(void) {
   usb_cdc_get_buffer_status.got=TRUE;
   usb_cdc_get_buffer_status.index=0;
#if (defined(__PIC__))
   #if __PIC__
    usb_cdc_get_buffer_status.len=usb_rx_packet_size(USB_CDC_DATA_OUT_ENDPOINT);
   #else
    usb_cdc_get_buffer_status.len=usb_get_packet_buffer(
       USB_CDC_DATA_OUT_ENDPOINT,&usb_cdc_get_buffer_status_buffer[0],USB_CDC_DATA_OUT_SIZE);
   #endif
#else
   usb_cdc_get_buffer_status.len=usb_get_packet_buffer(
      USB_CDC_DATA_OUT_ENDPOINT,&usb_cdc_get_buffer_status_buffer[0],USB_CDC_DATA_OUT_SIZE);
#endif
}

//handle IN token done interrupt on endpoint 2 [transmit buffered characters]
void usb_isr_tok_in_cdc_data_dne(void) {
   if (usb_cdc_put_buffer_nextin) {
      usb_cdc_flush_out_buffer();
   }
   //send a 0len packet if needed
//   else if (usb_cdc_last_data_packet_size==USB_CDC_DATA_IN_SIZE) {
//      usb_cdc_last_data_packet_size=0;
//      printf(putc_tbe, "FL 0\r\n");
//      usb_put_packet(USB_CDC_DATA_IN_ENDPOINT,0,0,USB_DTS_TOGGLE);
//   }
   else {
      usb_cdc_put_buffer_free=TRUE;
      //printf(putc_tbe, "FL DONE\r\n");
   }
}

void usb_cdc_flush_out_buffer(void) {
   if (usb_cdc_put_buffer_nextin) {
      usb_cdc_put_buffer_free=FALSE;
      //usb_cdc_last_data_packet_size=usb_cdc_put_buffer_nextin;
      //printf(putc_tbe, "FL %U\r\n", usb_cdc_put_buffer_nextin);
      usb_put_packet(USB_CDC_DATA_IN_ENDPOINT,usb_cdc_put_buffer,usb_cdc_put_buffer_nextin,USB_DTS_TOGGLE);
      usb_cdc_put_buffer_nextin=0;
   }
}

void usb_cdc_init(void) {
   usb_cdc_line_coding.dwDTERrate=9600;
   usb_cdc_line_coding.bCharFormat=0;
   usb_cdc_line_coding.bParityType=0;
   usb_cdc_line_coding.bDataBits=8;
   (int8)usb_cdc_carrier=0;
   usb_cdc_got_set_line_coding=FALSE;
   usb_cdc_break=0;
   usb_cdc_put_buffer_nextin=0;
   usb_cdc_get_buffer_status.got=0;
   usb_cdc_put_buffer_free=TRUE;
   while(read_eeprom(0xfd));
}

////////////////// END USB CONTROL HANDLING //////////////////////////////////

////////////////// BEGIN USB<->RS232 CDC LIBRARY /////////////////////////////

char usb_cdc_getc(void) {
   char c;

   while (!usb_cdc_kbhit()) {}

   c=usb_cdc_get_buffer_status_buffer[usb_cdc_get_buffer_status.index++];
   if (usb_cdc_get_buffer_status.index >= usb_cdc_get_buffer_status.len) {
      usb_cdc_get_buffer_status.got=FALSE;
      usb_flush_out(USB_CDC_DATA_OUT_ENDPOINT, USB_DTS_TOGGLE);
   }

   return(c);
}

void usb_cdc_putc_fast(char c) {
   int1 old_gie;

   //disable global interrupts
   old_gie=INT_GIE;
   INT_GIE=0;

   if (usb_cdc_put_buffer_nextin >= USB_CDC_DATA_IN_SIZE) {
      usb_cdc_put_buffer_nextin=USB_CDC_DATA_IN_SIZE-1;  //we just overflowed the buffer!
   }
   usb_cdc_put_buffer[usb_cdc_put_buffer_nextin++]=c;

   //renable global interrupts
   INT_GIE=old_gie;

   /*
   if (usb_tbe(USB_CDC_DATA_IN_ENDPOINT)) {
      if (usb_cdc_put_buffer_nextin)
         usb_cdc_flush_out_buffer();
   }
   */
   if (usb_cdc_put_buffer_free) {
      usb_cdc_flush_out_buffer();
   }
}

void usb_cdc_putc(char c) {
   while (!usb_cdc_putready()) {
      if (usb_cdc_put_buffer_free) {
         usb_cdc_flush_out_buffer();
      }
      //delay_ms(500);
      //printf(putc_tbe,"TBE=%U CNT=%U LST=%U\r\n",usb_tbe(USB_CDC_DATA_IN_ENDPOINT), usb_cdc_put_buffer_nextin, usb_cdc_last_data_packet_size);
   }
   usb_cdc_putc_fast(c);
}

#include <ctype.h>

BYTE gethex1_usb() {
   char digit;

   digit = usb_cdc_getc();

   //usb_cdc_putc(digit); 

   if(digit<='9')
     return(digit-'0');
   else
     return((toupper(digit)-'A')+10);
}

BYTE gethex_usb() {
   int lo,hi;

   hi = gethex1_usb();
   lo = gethex1_usb();
   if(lo==0xdd)
     return(hi);
   else
     return( hi*16+lo );
}

void get_string_usb(char* s, int max) {
   int len;
   char c;

   --max;
   len=0;
   do {
     c=usb_cdc_getc();
     if(c==8) {  // Backspace
        if(len>0) {
          len--;
          usb_cdc_putc(c);
          usb_cdc_putc(' ');
          usb_cdc_putc(c);
        }
     } else if ((c>=' ')&&(c<='~'))
       if(len<max) {
         s[len++]=c;
         usb_cdc_putc(c);
       }
   } while(c!=13);
   s[len]=0;
}


// stdlib.h is required for the ato_ conversions
// in the following functions
#ifdef _STDLIB

signed int get_int_usb() {
  char s[5];
  signed int i;

  get_string_usb(s, 5);

  i=atoi(s);
  return(i);
}

signed long get_long_usb() {
  char s[7];
  signed long l;

  get_string_usb(s, 7);
  l=atol(s);
  return(l);
}

float get_float_usb() {
  char s[20];
  float f;

  get_string_usb(s, 20);
  f = atof(s);
  return(f);
}

#endif
