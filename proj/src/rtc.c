#include <lcom/lcf.h>
#include "rtc.h"

bool RTCUpdating(){

  uint32_t value;

  sys_outb(RTC_ADDR_REG, RTC_REGA);
  sys_inb(RTC_DATA_REG, &value);

  if(value & UIP_FLAG)
    return true;
  else return false;
}


bool isBCD(){

  uint32_t value;

  sys_outb(RTC_ADDR_REG, RTC_REGB);
  sys_inb(RTC_DATA_REG, &value);

  if(value & DM_FLAG)
    return false;
  else return true;
}


uint32_t BCDtoBinary(uint32_t bcd) {
	uint32_t bi;

	bi = ((bcd & 0xF0) >> 4) * 10 + (bcd & 0x0F);

	return bi;
}


void get_date(uint32_t* day, uint32_t* month, uint32_t* year){

    sys_outb(RTC_ADDR_REG, RTC_DAYMONTH);
    sys_inb(RTC_DATA_REG, day);
    sys_outb(RTC_ADDR_REG, RTC_MONTH);
    sys_inb(RTC_DATA_REG, month);
    sys_outb(RTC_ADDR_REG, RTC_YEAR);
    sys_inb(RTC_DATA_REG, year);

    if(isBCD()){

        (*day) = BCDtoBinary(*day);
        (*month) = BCDtoBinary(*month);
        (*year) = BCDtoBinary(*year);
    }
}


void get_hour(uint32_t* minutes, uint32_t* hours){

    sys_outb(RTC_ADDR_REG, RTC_MINS);
    sys_inb(RTC_DATA_REG, minutes);
    sys_outb(RTC_ADDR_REG, RTC_HRS);
    sys_inb(RTC_DATA_REG, hours);

    if(isBCD()){

        (*minutes) = BCDtoBinary(*minutes);
        (*hours) = BCDtoBinary(*hours);
    }
}
