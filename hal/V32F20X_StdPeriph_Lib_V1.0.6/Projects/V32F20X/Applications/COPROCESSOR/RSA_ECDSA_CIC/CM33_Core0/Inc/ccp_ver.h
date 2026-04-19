/**
  ******************************************************************************
  * @file    ccp_ver.h
  * @details CryptCoProcessor Verify Headfile 
  ******************************************************************************
  */
#ifndef __CCP_VER_H
#define __CCP_VER_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"
#include <stdio.h>
#include "lib_ccp.h"

int CCP_Ver(void);
void CASPER_Deinit(CASPER_Type *base);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CCP_VER_H */

/*********************************** END OF FILE ******************************/
