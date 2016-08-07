//Portas
#BYTE TRISA=0xF92
#BYTE TRISB=0xF93
#BYTE TRISC=0xF94
#BYTE TRISD=0xF95
#BYTE TRISE=0xF96
#BYTE PORTA=0xF80
#BYTE PORTB=0xF81
#BYTE PORTC=0xF82
#BYTE PORTD=0xF83
#BYTE PORTE=0xF84
#BIT TRIS_A6=TRISA.6
#BIT TRIS_A5=TRISA.5
#BIT TRIS_A4=TRISA.4
#BIT TRIS_A3=TRISA.3
#BIT TRIS_A2=TRISA.2
#BIT TRIS_A1=TRISA.1
#BIT TRIS_A0=TRISA.0
#BIT RA6=PORTA.6
#BIT RA5=PORTA.5
#BIT RA4=PORTA.4
#BIT RA3=PORTA.3
#BIT RA2=PORTA.2
#BIT RA1=PORTA.1
#BIT RA0=PORTA.0
#BIT TRIS_B7=TRISB.7
#BIT TRIS_B6=TRISB.6
#BIT TRIS_B5=TRISB.5
#BIT TRIS_B4=TRISB.4
#BIT TRIS_B3=TRISB.3
#BIT TRIS_B2=TRISB.2
#BIT TRIS_B1=TRISB.1
#BIT TRIS_B0=TRISB.0
#BIT RB7=PORTB.7
#BIT RB6=PORTB.6
#BIT RB5=PORTB.5
#BIT RB4=PORTB.4
#BIT RB3=PORTB.3
#BIT RB2=PORTB.2
#BIT RB1=PORTB.1
#BIT RB0=PORTB.0
#BIT TRIS_C7=TRISC.7
#BIT TRIS_C6=TRISC.6
#BIT TRIS_C5=TRISC.5
#BIT TRIS_C4=TRISC.4
#BIT TRIS_C3=TRISC.3
#BIT TRIS_C2=TRISC.2
#BIT TRIS_C1=TRISC.1
#BIT TRIS_C0=TRISC.0
#BIT RC7=PORTC.7
#BIT RC6=PORTC.6
#BIT RC5=PORTC.5
#BIT RC4=PORTC.4
#BIT RC3=PORTC.3
#BIT RC2=PORTC.2
#BIT RC1=PORTC.1
#BIT RC0=PORTC.0
#BIT TRIS_D7=TRISD.7
#BIT TRIS_D6=TRISD.6
#BIT TRIS_D5=TRISD.5
#BIT TRIS_D4=TRISD.4
#BIT TRIS_D3=TRISD.3
#BIT TRIS_D2=TRISD.2
#BIT TRIS_D1=TRISD.1
#BIT TRIS_D0=TRISD.0
#BIT RD7=PORTD.7
#BIT RD6=PORTD.6
#BIT RD5=PORTD.5
#BIT RD4=PORTD.4
#BIT RD3=PORTD.3
#BIT RD2=PORTD.2
#BIT RD1=PORTD.1
#BIT RD0=PORTD.0
#BIT TRIS_E2=TRISE.2
#BIT TRIS_E1=TRISE.1
#BIT TRIS_E0=TRISE.0
#BIT RE3=PORTE.3
#BIT RE2=PORTE.2
#BIT RE1=PORTE.1
#BIT RE0=PORTE.0
//Interrup��es gerais
#BYTE INTCON=0xFF2
#BIT GIE=INTCON.7
#BIT PEIE=INTCON.6
#BIT RBIE=INTCON.3
//Timer0
#BYTE T0CON=0xFD5
#BYTE TMR0L=0xFD6
#BYTE TMR0H=0xFD7
#BYTE INTCON2=0xFF1
#BIT TMR0IF=INTCON.2
#BIT TMR0IE=INTCON.5
#BIT TMR0IP=INTCON2.2
#BIT TMR0ON=T0CON.7
#BIT T08BIT=T0CON.6
#BIT T0CS=T0CON.5
#BIT T0SE=T0CON.4
#BIT PSA=T0CON.3
#BIT T0PS2=T0CON.2
#BIT T0PS1=T0CON.1
#BIT T0PS0=T0CON.0
//Timer1
#BYTE T1CON=0xFCD
#BYTE TMR1L=0xFCE
#BYTE TMR1H=0xFCF
#BYTE PIR1=0xF9E
#BYTE PIE1=0xF9D
#BYTE IPR1=0xF9F
#BIT TMR1IF=PIR1.0
#BIT TMR1IE=PIE1.0
#BIT TMR1IP=IPR1.0
#BIT TM1RD16=T1CON.7
#BIT T1RUN=T1CON.6
#BIT T1CKPS1S=T1CON.5
#BIT T1CKPS0=T1CON.4
#BIT T1OSCEN=T1CON.3
#BIT T1SYNC=T1CON.2
#BIT TMR1CS=T1CON.1
#BIT TMR1ON=T1CON.0
//Timer2
#BYTE T2CON=0xFCA
#BYTE TMR2=0xFCC
#BYTE PR2=0xFCB
#BIT TMR2IF=PIR1.1
#BIT TMR2IE=PIE1.1
#BIT TMR2IP=IPR1.1
#BIT T2OUTPS3=T2CON.6
#BIT T2OUTPS2=T2CON.5
#BIT T2OUTPS1=T2CON.4
#BIT T2OUTPS0=T2CON.3
#BIT TMR2ON=T2CON.2
#BIT T2CKPS1=T2CON.1
#BIT T2CKPS0=T2CON.0
//Timer 3
#BYTE T3CON=0xFB1
#BYTE TMR3L=0xFB2
#BYTE TMR3H=0xFB3
#BYTE PIR2=0xFA1
#BYTE PIE2=0xFA0
#BYTE IPR2=0xFA2
#BIT TMR3IF=PIR2.1
#BIT TMR3IE=PIE2.1
#BIT TMR3IP=IPR2.1
#BIT TM3RD16=T3CON.7
#BIT T3CCP2=T3CON.6
#BIT T3CKPS1=T3CON.5
#BIT T3CKPS0=T3CON.4
#BIT T3CCP1=T3CON.3
#BIT T3SYNC=T3CON.2
#BIT TMR3CS=T3CON.1
#BIT TMR3ON=T3CON.0
//ADC
#BYTE ADCON0=0xFC2
#BYTE ADCON1=0xFC1
#BYTE ADCON2=0xFC0
#BYTE ADRESH=0xFC4
#BYTE ADRESL=0xFC3
#BIT ADIF=PIR1.6
#BIT ADIE=PIE1.6
#BIT ADIP=IPR1.6
#BIT CHS3=ADCON0.5
#BIT CHS2=ADCON0.4
#BIT CHS1=ADCON0.3
#BIT CHS0=ADCON0.2
#BIT GODONE=ADCON0.1
#BIT ADON=ADCON0.0
#BIT VCFG0ME=ADCON1.5
#BIT VCFG0MA=ADCON1.4
#BIT PCFG3=ADCON1.3
#BIT PCFG2=ADCON1.2
#BIT PCFG1=ADCON1.1
#BIT PCFG0=ADCON1.0
#BIT ADFM=ADCON2.7
#BIT ACQT2=ADCON2.5
#BIT ACQT1=ADCON2.4
#BIT ACQT0=ADCON2.3
#BIT ADCS2=ADCON2.2
#BIT ADCS1=ADCON2.1
#BIT ADCS0=ADCON2.0
//USART
#BYTE TXSTA=0xFAC
#BYTE RCSTA=0xFAB
#BYTE BAUDCON=0xFB8
#BYTE SPBRGH=0xFB0
#BYTE SPBRG=0xFAF
#BYTE TXREG=0xFAD
#BYTE RCREG=0xFAE
#BIT RCIE=PIE1.5
#BIT TXIF=PIR1.4
#BIT TXIE=PIE1.4
#BIT TXIP=IPR1.4
//
#BIT TXIP=IPR1.1
#BIT CSRC=TXSTA.7
#BIT TX9=TXSTA.6
#BIT TXEN=TXSTA.5
#BIT SYNC=TXSTA.4
#BIT SENDB=TXSTA.3
#BIT BRGH=TXSTA.2
#BIT TRMT=TXSTA.1
#BIT TX9D=TXSTA.0
#BIT SPEN=RCSTA.7
#BIT RX9=RCSTA.6
#BIT SREN=RCSTA.5
#BIT CREN=RCSTA.4
#BIT ADDEN=RCSTA.3
#BIT FERR=RCSTA.2
#BIT OERR=RCSTA.1
#BIT RX9D=RCSTA.0
#BIT ABDOVF=BAUDCON.7
#BIT RCIDL=BAUDCON.6
#BIT RXDTP=BAUDCON.5
#BIT TXCKP=BAUDCON.4
#BIT BRG16=BAUDCON.3
#BIT WUE=BAUDCON.1
#BIT ABDEN=BAUDCON.0