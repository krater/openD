#ifdef __cplusplus
extern "C"
{
#endif
/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_hanfun_pSiren.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN pSiren.
 *
 * @addtogroup OPEND_HANFUN_PROFILE
 * @{
 *
 * @defgroup   OPEND_HANFUN_PSIREN openD HAN-FUN pSiren
 *             This module specifies the HAN-FUN siren profile.
 * @{
 */

#ifndef __OPEND_HANFUN_PSIREN_H__
#define __OPEND_HANFUN_PSIREN_H__

#include "../interfaces/opend_hanfun_iOnOff.h"

/**
 * openD Hanfun pSiren profile request structure.
 */
typedef openD_hanfun_iOnOffServerReq_t openD_hanfun_pSirenReq_t;

/**
 * openD Hanfun pSiren profile confirm structure.
 */
typedef openD_hanfun_iOnOffServerCfm_t openD_hanfun_pSirenCfm_t;

/**
 * openD Hanfun pSiren profile indication structure.
 */
typedef openD_hanfun_iOnOffServerInd_t openD_hanfun_pSirenInd_t;


/*! @} defgroup OPEND_HANFUN_PSIREN */

/*! @} addtogroup OPEND_HANFUN_PROFILE */

#endif /* __OPEND_HANFUN_PSIREN_H__ */
#ifdef __cplusplus
}
#endif
