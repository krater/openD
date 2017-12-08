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
 * @file       opend_audio_api.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD audio API.
 *
 * @defgroup   OPEND_AUDIO_API openD Audio API
 *             This module specifies the audio API of openD connect.
 * \{
 */

#ifndef __OPEND_AUDIO_API_H__
#define __OPEND_AUDIO_API_H__

#include <stdbool.h>
#include "opend_dataTypes.h"

/**
 * openD AudioApi services.
 */
typedef enum openD_audioApi {
  /**
   * Mute.
   */
  AUDIOAPI_MUTE,
  /**
   * Volume.
   */
  AUDIOAPI_VOLUME,
} openD_audioApiServices_t;

/**
 * openD AudioApi request mute structure.
 */
typedef struct audioApiReq_mute {
  /**
   * Portable part MAC Identity (PMID).
   */
  pmid_t pmid;
  /**
    * Mute enable.
    */
  bool enable;
} audioApiReq_mute_t;

/**
 * openD AudioApi request volume structure.
 */
typedef struct audioApiReq_volume {
  /**
   * Portable part MAC Identity (PMID).
   */
  pmid_t pmid;
  /**
    * Volume level.
    */
  uint8_t level;
} audioApiReq_volume_t;

/**
 * openD AudioApi request structure.
 */
typedef struct openD_audioApiReq {
  /**
   * AudioApi request type.
   */
  openD_audioApiServices_t type;

  /**
   * openD AudioApi request parameters.
   */
  union {
    /**
     * AudioApi parameters for a mute request.
     */
    audioApiReq_mute_t mute;
    /**
     * AudioApi parameters for a volume request.
     */
    audioApiReq_volume_t volume;
  } param;
} openD_audioApiReq_t;

/**
 * openD AudioApi confirm structure.
 */
typedef struct openD_audioApiConfirm {
  /**
   * AudioApi service type.
   */
  openD_audioApiServices_t type;
  /**
   * AudioApi service status.
   */
  openD_status_t status;
} openD_audioApiConfirm_t;

/**
 * openD AudioApi indication structure.
 */
typedef struct openD_audioApiIndication {
  /**
   * AudioApi service type.
   */
  openD_audioApiServices_t type;
} openD_audioApiIndication_t;

/**
 * openD AudioApi primitives structure.
 */
typedef struct openD_audioApiPrimitives {
  /**
   * @brief   AudioApi confirm primitive.
   *
   * @param   aConfirm Pointer to the AudioApi confirm structure (@ref openD_audioApiConfirm_t).
   */
  void ( *openD_audioApiConfirm )( openD_audioApiConfirm_t *aConfirm );
  /**
   * @brief   AudioApi indication primitive.
   *
   * @param   aIndication Pointer to the AudioApi indication structure (@ref openD_audioApiIndication_t).
   */
  void ( *openD_audioApiIndication )( openD_audioApiIndication_t *aIndication );
} openD_audioApiPrimitives_t;

/**
 * @brief   openD audio API initialization.
 *
 * @details DETAILED DESCRIPTION HERE.
 *
 * @param   aPrimitives Pointer of the audio API primitives structure (@ref openD_audioApiPrimitives_t).
 *
 * @retval  openD_status_t Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_audioApi_init( openD_audioApiPrimitives_t *aPrimitives );

/**
 * @brief   openD audio API request.
 *
 * @details DETAILED DESCRIPTION HERE.
 *
 * @param   aRequest Pointer of the audio API request structure (@ref openD_audioApiReq_t).
 *
 * @retval  openD_status_t Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_audioApi_request( openD_audioApiReq_t *aRequest );


/*! @} defgroup OPEND_AUDIO_API */

#endif /* __OPEND_AUDIO_API_H__ */
#ifdef __cplusplus
}
#endif
