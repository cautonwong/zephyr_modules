/**
*******************************************************************************
  * @file    lib_version.h
  * @author  Application Team
  * @version V2.5.0
  * @date    2022-10-18
  * @brief   Version library.
*******************************************************************************/

#ifndef __LIB_VERSION_H
#define __LIB_VERSION_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"
   
#define DRIVER_VERSION(major,minor) (((major) << 8) | (minor))

/* Exported Functions ------------------------------------------------------- */
   
/**
  * @brief  Gets Target driver's current version.
  * @param  None
  * @retval Version value
  */
uint16_t Target_GetDriveVersion(void);

#ifdef __cplusplus
}
#endif

#endif /* __LIB_VERSION_H */

/*********************************** END OF FILE ******************************/
