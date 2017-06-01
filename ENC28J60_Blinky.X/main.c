

#include <xc.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "hardware.h"
#include "rtcc.h"
#include "syslog.h"
//#include "tcpip_config.h"
#include "network.h"
#include "ipv4.h"
//#include "udpv4.h"
#include "ethernet_driver.h"
#include "tcpv4.h"
#include "ip_database.h"
//#include "ntp.h"


void TCP_Blinky(void);


void interrupt high_priority isr(){
    rtcc_handler();   
}

//Implement a server over TCP
void TCP_Blinky(void)
{
    // create the socket for the TCP Server
    static tcpTCB_t port7TCB;

    // create the TX and RX Server's buffers
    static uint8_t rxdataPort7[20];
    static uint8_t txdataPort7[20];
    static uint8_t hit_counter;
    uint8_t len;

    uint16_t rxLen, txLen;
    socketState_t socket_state;

    socket_state = TCP_SocketPoll(&port7TCB);

    switch(socket_state)
    {
        case NOT_A_SOCKET:
            // Inserting and initializing the socket
            TCP_SocketInit(&port7TCB);
            hit_counter = 0;
            break;
        case SOCKET_CLOSED:
            //configure the local port
            TCP_Bind(&port7TCB, 7);
            // add receive buffer
            TCP_InsertRxBuffer(&port7TCB, rxdataPort7, sizeof(rxdataPort7));
            // start the server
            TCP_Listen(&port7TCB);
            break;
        case SOCKET_CONNECTED:
            // check if the buffer was sent, if yes we can send another buffer
            if(TCP_SendDone(&port7TCB))
            {
                // check to see  if there are any received data
                rxLen = TCP_GetRxLength(&port7TCB);
                if(rxLen > 0)
                {
                    hit_counter++;
                    rxLen = TCP_GetReceivedData(&port7TCB);

                    if(rxdataPort7[0]== '0'){
                        LED_LAT = 0;
                        len = sprintf(txdataPort7,"counter %i. led off\n",hit_counter);
                    }
                    else if(rxdataPort7[0]== '1'){
                        LED_LAT = 1;
                        len = sprintf(txdataPort7,"counter %i. led on\n",hit_counter);
                    }
                    else
                        len = sprintf(txdataPort7,"counter %i. enter 1 or 0\n",hit_counter);
                    // reuse the RX buffer
                    TCP_InsertRxBuffer(&port7TCB, rxdataPort7, sizeof(rxdataPort7));
                    //send a message back to client
                    TCP_Send(&port7TCB, txdataPort7, strlen(txdataPort7));
                }
            }
            break;
        default:
            // we should not end up here
            break;
    }
}

void main(void) {
    time_t t;
    //time_t time_check;
    unsigned long ip, old_ip;
    char str[32];
    bool no_ip_display = true;
    
    
    //initialize hardware
    init_device();
    SYSLOG_Init();    
    //init network stack
    SYSLOG_Write("Waiting for Link");
    Network_Init();
    SYSLOG_Write("Link started");  
    
    //enable interrupts
    IPEN = 1;
    GIEH = 1;    
    
    //SYSLOG_Write("Waiting for Link");
    //Network_WaitForLink(); //done in Network_Init()
    //SYSLOG_Write("Link started");  
         
    while(1){     
        time_t now_p;
        time(&now_p);
        Network_Manage();
        time(&t);
        
        ip = ipdb_getAddress();// IPV4_GetMyIP();
        // make sure we update the IP if we get another one from the DHCP server
        
        if((no_ip_display) || (old_ip != ip))
        {
            old_ip = ip;
            memset(str,0,sizeof(str));
            sprintf(str,"%d.%d.%d.%d",((char*)&ip)[3],((char*)&ip)[2],((char*)&ip)[1],((char*)&ip)[0]);

            SYSLOG_Write(str);
            no_ip_display = false;

        }
     
        TCP_Blinky();
    }
    return;
}
