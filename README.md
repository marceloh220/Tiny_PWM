# Tiny_PWM
Dual channel PWM driver controller. For LEDs, motors and other strangers things.\
Based on Attiny25/45/85 microcontroller this device have two PWM channels controlled by independent potentiometer.

Fusebits:
  - Low:      0x62
  - High:     0xDC
  - Extended: 0xFF


Install avr-gcc:

 - windows:
    
       https://blog.zakkemble.net/avr-gcc-builds/
    
   Include the bin directory on system path
    
 -  Debian/Ubuntu:
    
        sudo apt install gcc-avr avr-libc binutils-avr
   
  - RedHat/Fedora:
    
        sudo dnf install avr-gcc avr-libc avr-binutils
    
  - Arch/Manjaro:
    
        sudo pacman -S avr-gcc avr-libc avr-binutils
    

Install avrdude:

  - Windows:

    Avrdude comes with avr-gcc
   
  - Debian/Ubuntu:
    
        sudo apt install avrdude
   
  - RedHat/Fedora:
    
        sudo dnf install avrdude
    
  - Arch/Manjaro:
    
        sudo pacman -S avrdude
    
    
Install Make:
    
   - Windows:
      
    Make comes with avr-gcc
    
   - Debian/Ubuntu
   
    sudo apt install make
   
   - RedHat/Fedora
   
    sudo dnf install make
   
   - Arch/Manjaro
   
    sudo pacman -S make
    
    
Using:

  For Windows rename Makefile.windows to Makefile\
  For Linux rename Makefile.linux to Makefile
  
   - Generate executable files
     
         make all
         
   - Clean build
        
         make clean
         
   - Verify size program
   
         make size
     
   - Configure fusebits
       
         make fuses
       
   - Upload to device

         make program
