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
 * @file       opend_sub_types.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD subscription types.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   OPEND_SUB_TYPES openD Subscription types
 *             This file defines the subscription types of openD connect.
 * \{
 */

#ifndef __OPEND_SUB_TYPES_H__
#define __OPEND_SUB_TYPES_H__

#include <stdbool.h>
#include "opend_dataTypes.h"

/**
 * openD SubApi services.
 */
typedef enum openD_subApi_service {
  /**
   * Subscribe enable.
   */
  OPEND_SUBAPI_SUBSCRIBE_ENABLE,
  /**
   * Subscribe disable.
   */
  OPEND_SUBAPI_SUBSCRIBE_DISABLE,
  /**
   * Subscribe.
   */
  OPEND_SUBAPI_SUBSCRIBE,
  /**
   * Subscribe delete.
   */
  OPEND_SUBAPI_SUBSCRIPTION_DELETE,
  /**
   * Get registration state.
   */
  OPEND_SUBAPI_GET_REGISTRATION_STATE,
  /**
   * Set access code.
   */
  OPEND_SUBAPI_SET_AC,
} openD_subApi_service_t;

/**
 * openD SubApi request subscribeEnable structure.
 */
typedef struct subApiReq_subscribeEnable {
  /**
    * Subscribe enable.
    */
  bool enable;
} subApiReq_subscribeEnable_t;

/**
 * openD SubApi request subscribe structure.
 */
typedef struct subApiReq_subscribe {
  /**
   * Radio Fixed Part Identity (RFPI).
   */
  rfpi_t rfpi;
  /**
   * Access code (AC).
   */
  ac_t ac;
} subApiReq_subscribe_t;

/**
 * openD SubApi request subscriptionDelete structure.
 */
typedef struct subApiReq_subscriptionDelete {
  /**
   * Portable part MAC Identity (PMID).
   */
  pmid_t pmid;
} subApiReq_subscriptionDelete_t;

/**
 * openD SubApi request setAc structure.
 */
typedef struct subApiReq_setAc {
  /**
   * Access code (AC).
   */
  ac_t ac;
} subApiReq_setAc_t;

/**
 * openD SubApi indication subscribeEnable structure.
 */
typedef struct subApiInd_subscribeEnable {
  /**
    * Subscribe enable.
    */
  bool enable;
} subApiInd_subscribeEnable_t;

/**
 * openD SubApi indication subscribe structure.
 */
typedef struct subApiInd_subscribe {
  /**
   * Portable part MAC Identity (PMID).
   */
  pmid_t pmid;
  /**
   * International Portable User Identity (IPUI).
   */
  ipui_t ipui;
} subApiInd_subscribe_t;

/**
 * openD SubApi indication subscriptionDelete structure.
 */
typedef struct subApiInd_subscriptionDelete {
  /**
   * Portable part MAC Identity (PMID).
   */
  pmid_t pmid;
} subApiInd_subscriptionDelete_t;

/**
 * openD SubApi request structure.
 */
typedef struct openD_subApiReq {
  /**
   * SubApi request service.
   */
  openD_subApi_service_t service;

  /**
   * openD SubApi request parameters.
   */
  union {
    /**
     * SubApi parameters for a subscribeEnable request.
     */
    subApiReq_subscribeEnable_t subscribeEnable;
    /**
     * SubApi parameters for a subscribe request.
     */
    subApiReq_subscribe_t subscribe;
    /**
     * SubApi parameters for a subscriptionDelete request.
     */
    subApiReq_subscriptionDelete_t subscriptionDelete;
    /**
     * SubApi parameters for a setAc request.
     */
    subApiReq_setAc_t setAc;
  } param;
} openD_subApiReq_t;

/**
 * openD SubApi confirm get registration state structure.
 */
typedef struct subApiReq_getRegState {
  /**
   * Indicates if the device is registered or not.
   */
  bool isRegistered;
  /**
   * Portable part MAC Identity (PMID).
   */
  pmid_t pmid;
} subApiReq_getRegState_t;

/**
 * openD SubApi confirm get registration state structure.
 */
typedef struct subApiReq_getHandsetId_t {
  /**
   * Indicates the handset ID.
   */
  uint8_t id;
} subApiReq_getHandsetId_t;

/**
 * openD SubApi confirm structure.
 */
typedef struct openD_subApiCfm {
  /**
   * SubApi confirm service.
   */
  openD_subApi_service_t service;
  /**
   * SubApi service status.
   */
  openD_status_t status;

  /**
   * openD SubApi confirm parameters.
   */
  union {
    /**
     * SubApi parameters for an OPEND_SUBAPI_GET_REGISTRATION_STATE request.
     */
    subApiReq_getRegState_t registrationState;
    /**
     * SubApi parameters for an OPEND_SUBAPI_SUBSCRIBE request.
     */
    subApiReq_getHandsetId_t handsetId;
  } param;
} openD_subApiCfm_t;

/**
 * openD SubApi indication structure.
 */
typedef struct openD_subApiInd {
  /**
   * SubApi indication service.
   */
  openD_subApi_service_t service;

  /**
   * openD SubApi indication parameters.
   */
  union {
    /**
     * SubApi parameters for a subscribeEnable indication.
     */
    subApiInd_subscribeEnable_t subscribeEnable;
    /**
     * SubApi parameter for a subscribe indication.
     */
    subApiInd_subscribe_t subscribe;
    /**
     * SubApi parameter for a subscriptionDelete indication.
     */
    subApiInd_subscriptionDelete_t subscriptionDelete;
    /**
     * SubApi parameters for an OPEND_SUBAPI_GET_REGISTRATION_STATE request.
     */
    subApiReq_getRegState_t registrationState;
  } param;
} openD_subApiInd_t;

/*! @} defgroup OPEND_SUB_TYPES */

#endif /* __OPEND_SUB_TYPES_H__ */
#ifdef __cplusplus
}
#endif
