#ifndef _RTC_H_
#define _RTC_H_

/** @defgroup rtc rtc
 * @{
 * Functions for manipulating the rtc
 */


#define BIT(n)        (0x01<<(n))

#define RTC_SECS      0x00
#define RTC_MINS      0x02
#define RTC_HRS       0x04
#define RTC_DAYMONTH  0x07
#define RTC_MONTH     0x08
#define RTC_YEAR      0x09

#define RTC_REGA      0x0A
#define RTC_REGB      0x0B
#define RTC_REGC      0x0C
#define RTC_REGD      0x0D

#define UIP_FLAG      BIT(7)
#define DM_FLAG				BIT(2)

#define RTC_ADDR_REG	0x70
#define RTC_DATA_REG	0x71



/**
 * @brief Checks if the RTC is updating 
 * 
 * @return True if it is, false if it is not
 */
bool RTCUpdating();


/**
 * @brief Checks if the RTC has its values in BCD or in binary
 * 
 * @return True if it is in BCD, false if it is in binary
 */
bool isBCD();


/**
 * @brief Receives a value in BCD format, and retrieves it in the binary format
 * 
 * @param bcd Value in BCD format
 * 
 * @return Value in binary format
 */
uint32_t BCDtoBinary(uint32_t bcd);


/**
 * @brief Extracts the day of the month, the month and the year from the RTC
 * 
 * @param day Pointer to store the day
 * @param month Pointer to store the month
 * @param year Pointer to store the year
 */
void get_date(uint32_t* day, uint32_t* month, uint32_t* year);


/**
 * @brief Extracts the current number of hours and minutes from the RTC
 * 
 * @param minutes Pointer to store the minutes
 * @param hours Pointer to store the hours
 */
void get_hour(uint32_t* minutes, uint32_t* hours);


/** @} end of rtc */


#endif
