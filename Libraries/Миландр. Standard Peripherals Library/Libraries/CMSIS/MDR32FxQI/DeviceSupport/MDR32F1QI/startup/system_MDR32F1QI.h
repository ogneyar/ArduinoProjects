/**
  * FILE system_MDR32F1QI.h
  */

/** @addtogroup __CMSIS CMSIS
  * @{
  */

/** @defgroup MDR32F1QI
 *  @{
 */

/** @defgroup MDR32F1QI_System MDR32F1QI System
  * @{
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYSTEM_MDR32F1QI_H
#define __SYSTEM_MDR32F1QI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h> /* standard types definitions */

/** @addtogroup __MDR32F1QI_System_Exported_Variables MDR32F1QI System Exported Variables
  * @{
  */

extern uint32_t SystemCoreClock;    /*!< System Clock Frequency (Core Clock) default value */

/** @} */ /* End of group __MDR32F1QI_System_Exported_Variables */

/** @addtogroup __MDR32F1QI_System_Exported_Functions MDR32F1QI System Exported Functions
  * @{
  */

extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);

/** @} */ /* End of group __MDR32F1QI_System_Exported_Functions */

#ifdef __cplusplus
}
#endif

#endif /* #define __SYSTEM_MDR32F1QI_H */

/** @} */ /* End of group MDR32F1QI_System */

/** @} */ /* End of goup MDR32F1QI */

/** @} */ /* End of group __CMSIS */

/*
*
* END OF FILE system_MDR32F1QI.h */

