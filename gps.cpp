#include "mbed.h"
 
Serial pc(USBTX, USBRX);
Serial gps(PTD3,PTD2,9600);


int main()
{
    pc.baud(9600);
    gps.baud(9600);
    char buffer[128];       //   NMEA data, Example:  $GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47  
    char * split;
    char part1[12] = "";    //   GGA          Global Positioning System Fix Data
    char part2[12] = "";    //   123519       Fix taken at 12:35:19 UTC
    char part3[12] = "";    //   4807.038     Latitude 48 deg 07.038' 
    char part4[12] = "";    //   N            Direction - North
    char part5[12] = "";    //   01131.000    Longitude 11 deg 31.000' 
    char part6[12] = "";    //   E            Direction - East
    char part7[12] = "";    //   1            Fix quality: 0 = invalid
                            //                             1 = GPS fix (SPS)
                            //                             2 = DGPS fix
                            //                             3 = PPS fix
                            //                             4 = Real Time Kinematic
                            //                             5 = Float RTK
                            //                             6 = estimated (dead reckoning) (2.3 feature)
                            //                             7 = Manual input mode
                            //                             8 = Simulation mode
    char part8[12] = "";    //   08           Number of satellites being tracked
    char part9[12] = "";    //   0.9          Horizontal dilution of position
    char part10[12] = "";   //   545.4        Altitude, Meters
    char part11[12] = "";   //   M            above mean sea level
    char part12[12] = "";   //   46.9         Height of geoid (mean sea level) above WGS84 ellipsoid
    char part13[12] = "";   //   M            above mean sea level  
    char part14[12] = "";   //  (empty field) time in seconds since last DGPS update
    char part15[12] = "";   //  *47           the checksum data, always begins with *
    
    //int count=0;
    
    while(true) {
       
      
        if(gps.readable()) {
             gps.gets(buffer, 70);  
                 
             if(buffer[0] == '$' && buffer[5] == 'A' && buffer[43] == '1')              
               {
                   
                   split = strtok(buffer, ",");
                   while(split != NULL)   {
                        strcpy(part1,split);
                           
                        split = strtok(NULL,",");
                        
                        strcpy(part2,split);
                        
                        split = strtok(NULL,",");
                        
                        strcpy(part3,split);
                        pc.printf(" Latitude: '%s'\r\n",part3);
                        split = strtok(NULL,",");
                        
                        strcpy(part4,split);
                       
                        split = strtok(NULL,",");
                        
                        strcpy(part5,split);
                        pc.printf(" Longitude: '%s'\r\n",part5);
                        split = strtok(NULL,",");
                        
                        strcpy(part6,split);
                           
                        split = strtok(NULL,",");
                        
                        strcpy(part7,split);
                           
                        split = strtok(NULL,",");
                        
                        strcpy(part8,split);
                       
                        split = strtok(NULL,",");
                        
                        strcpy(part9,split);
                        
                        split = strtok(NULL,",");
                        
                        strcpy(part10,split);
                        
                        split = strtok(NULL,",");
                        
                        strcpy(part11,split);
                      
                        split = strtok(NULL,",");
                        
                        strcpy(part12,split);
                       
                        split = strtok(NULL,",");
                        
                        strcpy(part13,split);
                       
                        split = strtok(NULL,",");
                        
                        strcpy(part14,split);
                        
                        split = strtok(NULL,",");
                        
                        strcpy(part15,split);
                       
                        split = strtok(NULL,",");
                        
                        
                     }
                     break;
                 }
             
             }
        }
        
    }   


