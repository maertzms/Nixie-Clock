# Nixie Tube
Cathode poisoning routines should have a 300:1 ratio of on-time (any digit) to recovery time (each individual digit). 
An example would be if the clock is running for 10 minutes (600 seconds) each digit should get a recovery cycle of 2 seconds. 
    600/300 = 2


# DS1302 COMMS
  ## PHY Standards
  CE needs to be driven high for all data transfers
  Data inputs are valid during RE of CLK
  Data outputs are valid during FE of CLK
  SCLK must be 0 during CE rising edge
  
  ## General
  Data transfers are LSB first
  Data comes out on the first falling edge after command. Since Data in is done on RE, (to be confirmed) data will come out on that FE, 
  so pin direction should be made an input while the CLK is still high.
  
  ## 
  
