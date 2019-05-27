/**
 * @code
 * openD Example Application - Remote controlled power socket
 * @endcode
 *
 * @file       fp_hanfun_alarm.cpp
 * @copyright  Schuler Development, Oberdorf 90, 66687 Wadern, andreas@schulerdev.de
 * @author     Andreas Schuler
 * @brief      Example application for the usage of the openD framework
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose
 * between one of them if you use this work. For further details, please refer
 * to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 */

#include <stdint.h>

#include "application.h"
#include "opend_hanfun_api_fp.h"
#include "hf_transport.h"

extern "C" {
#include "opend_api.h"
}


void HF::Application::Save();
void HF::Application::Restore();

void devMgmtConfirmCallback(openD_hanfunApi_devMgmtCfm_t* hDevMgmtConfirm)
{
   FP* fp = FP::instance();

   if(!hDevMgmtConfirm || (hDevMgmtConfirm->status != OPEND_STATUS_OK))
   {
      return;
   }

   switch(hDevMgmtConfirm->service)
   {
      case OPEND_HANFUNAPI_DEVICE_MANAGEMENT_ENTRIES_REGISTRATION:
         printf("Currently registered HAN-FUN Devices: %u\n", hDevMgmtConfirm->param.entriesRegistration.size);

         for(int i = 0; i < hDevMgmtConfirm->param.entriesRegistration.size;i++)
         {
            hanfunApiDevMgmt_registrationElement_t RegEl = hDevMgmtConfirm->param.entriesRegistration.registrationElement[i];

            char c = (fp->link(RegEl.address)!= nullptr? '+': '-');
            printf("%c | %.5u | dect uid: %.2x%.2x%.2x%.2x%.2x\n",
                   c, RegEl.address, RegEl.uid[0], RegEl.uid[1], RegEl.uid[2], RegEl.uid[3], RegEl.uid[4]);
         }
         break;

      case OPEND_HANFUNAPI_DEVICE_MANAGEMENT_ENTRIES_LINK:
         for(int i = 0; i < (int)hDevMgmtConfirm->param.entriesRegistration.size; i++)
         {
            hanfunApiDevMgmt_registrationElement_t RegEl = hDevMgmtConfirm->param.entriesRegistration.registrationElement[i];

            printf("%.5u | dect uid: %.2x%.2x%.2x%.2x%.2x\n",
                   RegEl.address, RegEl.uid[0], RegEl.uid[1], RegEl.uid[2], RegEl.uid[3], RegEl.uid[4]);
         }
         break;

      case OPEND_HANFUNAPI_DEVICE_MANAGEMENT_CHANGE_CONCENTRATOR_DECT_MODE:
         printf("Successful change of Dect mode.\nResetting the Dect Module\n");
         break;
   }
}

void devMgmtIndicationCallback(openD_hanfunApi_devMgmtInd_t* hDevMgmtIndication)
{
   if(!hDevMgmtIndication)
   {
      return;
   }

   switch(hDevMgmtIndication->service)
   {
      case OPEND_HANFUNAPI_DEVICE_MANAGEMENT_REGISTER_DISABLE:
         printf("Registration mode disabled\n");
         break;

      case OPEND_HANFUNAPI_DEVICE_MANAGEMENT_REGISTER_DEVICE:
         printf("Registered device with ID: %u\n", hDevMgmtIndication->param.getAddress.address);
         break;

      case OPEND_HANFUNAPI_DEVICE_MANAGEMENT_GET_DEVICE_CORE_INFORMATION:
         openD_hanfunApi_devMgmtReq_t hMgmtRequest;
         hMgmtRequest.service = OPEND_HANFUNAPI_DEVICE_MANAGEMENT_GET_DEVICE_CORE_INFORMATION;
         openD_hanfunApi_fp_devMgmtRequest(&hMgmtRequest, hDevMgmtIndication->param.getAddress.address, 0);
         break;

      default:
         break;
   }

   return;
}

void profileIndCallback(openD_hanfunApi_profileInd_t* hProfileInd)
{
   if(!hProfileInd || (hProfileInd->status != OPEND_STATUS_OK))
   {
      return;
   }

   switch(hProfileInd->profile)
   {
      case OPEND_HANFUNAPI_SIMPLE_LIGHT:
         switch(hProfileInd->simpleLight.service)
         {
            case OPEND_HANFUN_IONOFF_SERVER_TOGGLE_ADDR:
               printf("Toggle indication from PP with address %u received.\n", hProfileInd->simpleLight.param.toggleAddr.addr.device);
               break;
            case OPEND_HANFUN_IONOFF_SERVER_ON_ADDR:
               printf("On indication from PP with address %u received.\n", hProfileInd->simpleLight.param.toggleAddr.addr.device);
               break;
            case OPEND_HANFUN_IONOFF_SERVER_OFF_ADDR:
               printf("Off indication from PP with address %u received.\n", hProfileInd->simpleLight.param.toggleAddr.addr.device);
               break;
         }
         break;
   }
}

void profileConfirmCallback(openD_hanfunApi_profileCfm_t* hProfileConfirm)
{
   if(!hProfileConfirm || (hProfileConfirm->status != OPEND_STATUS_OK))
   {
      return;
   }

   switch(hProfileConfirm->profile)
   {
      case OPEND_HANFUNAPI_SIMPLE_ONOFF_SWITCH:
         switch(hProfileConfirm->simpleOnOffSwitch.service)
         {
            case OPEND_HANFUN_IONOFF_CLIENT_TOGGLE:
               // CONFIRMATION IMPLEMENT HERE
               break;
         }
         break;
   }
}

void bindMgmtConfirmCallback(openD_hanfunApi_bindMgmtCfm_t* hBindMgmtConfirm)
{
   if(!hBindMgmtConfirm || (hBindMgmtConfirm->status != OPEND_STATUS_OK))
   {
      return;
   }

   switch(hBindMgmtConfirm->service)
   {
      case OPEND_HANFUNAPI_BIND_MANAGEMENT_ENTRIES:
         printf("HAN-FUN current Binds (%u)\n", hBindMgmtConfirm->param.entriesElement.entriesSize);

         printf("\t Source               | Destination          | Interface  \n");
         printf("\t----------------------|----------------------|--------------------\n");


         for(int i = 0; i < hBindMgmtConfirm->param.entriesElement.entriesSize; i++)
         {
            networkAddress_t src = hBindMgmtConfirm->param.entriesElement.src[i];
            networkAddress_t dst = hBindMgmtConfirm->param.entriesElement.dst[i];
            interfaceUid_t   itf = hBindMgmtConfirm->param.entriesElement.itf[i];

            printf("\t M: %.4x D: %.4x U:%.2x |" , src.mod, src.device, src.unit);
            printf("\t M: %.4x D: %.4x U:%.2x |" , dst.mod, dst.device, dst.unit);
            printf("Role: %.4x UID: %.4x\n", itf.role, itf.id);
         }
         break;

      case OPEND_HANFUNAPI_BIND_MANAGEMENT_ADD:
         switch(hBindMgmtConfirm->param.entriesElement.error)
         {
            case 0:
               printf("Bind created\n");
               break;

            case 1:
               printf("Bind already exist !\n");
               break;

            case 2:
            case 3:
            {
               printf("Bind not possible: ");
               if ((hBindMgmtConfirm->param.entriesElement.error & 0x01) != 0)
               {
                  printf("Second device does not exist !\n");
               }
               else
               {
                  printf("Fist device does not exist !\n");
               }
               break;
            }
            default:
               printf("No match for bind !\n");
               break;
            }
            break;

      case OPEND_HANFUNAPI_BIND_MANAGEMENT_REMOVE:
         if(hBindMgmtConfirm->param.entriesElement.error == 1)
         {
            printf("Bind: %u - %u removed !",
                   hBindMgmtConfirm->param.entriesElement.devicesToBind.address1,
                   hBindMgmtConfirm->param.entriesElement.devicesToBind.address2);
         }
         else
         {
            printf("Bind: does not exist !\n");
         }
         break;
   }
}

// Commands to control openD

void RequestDeviceList(void)
{
   openD_hanfunApi_devMgmtReq_t hMgmtRequest;
   hMgmtRequest.service = OPEND_HANFUNAPI_DEVICE_MANAGEMENT_ENTRIES_REGISTRATION;

   openD_hanfunApi_fp_devMgmtRequest(&hMgmtRequest);
}

openD_status_t RegistrationMode(bool enable, uint16_t address)
{
   openD_hanfunApi_devMgmtReq_t hMgmtRequest;

   if(enable)
   {
      // Enable registration
      hMgmtRequest.service = OPEND_HANFUNAPI_DEVICE_MANAGEMENT_REGISTER_ENABLE;
   }
   else
   {
      // Disable registration
      hMgmtRequest.service = OPEND_HANFUNAPI_DEVICE_MANAGEMENT_REGISTER_DISABLE;
   }

   return openD_hanfunApi_fp_devMgmtRequest(&hMgmtRequest, address);
}

openD_status_t Deregister(uint16_t address)
{
   openD_hanfunApi_devMgmtReq_t hMgmtRequest;
   hMgmtRequest.service = OPEND_HANFUNAPI_DEVICE_MANAGEMENT_DEREGISTER;

   return openD_hanfunApi_fp_devMgmtRequest(&hMgmtRequest, address);
}

openD_status_t SendSimpleSwitchOn(uint16_t address)
{
   openD_hanfunApi_profileReq_t hProfileRequest;
   hProfileRequest.profile = OPEND_HANFUNAPI_SIMPLE_ONOFF_SWITCH;
   hProfileRequest.simpleOnOffSwitch.service = OPEND_HANFUN_IONOFF_CLIENT_ON;

   return openD_hanfunApi_fp_profileRequest(&hProfileRequest, address, 1);
}

openD_status_t SendSimpleSwitchOff(uint16_t address)
{
   openD_hanfunApi_profileReq_t hProfileRequest;
   hProfileRequest.profile = OPEND_HANFUNAPI_SIMPLE_ONOFF_SWITCH;
   hProfileRequest.simpleOnOffSwitch.service = OPEND_HANFUN_IONOFF_CLIENT_OFF;

   return openD_hanfunApi_fp_profileRequest(&hProfileRequest, address, 1);
}

openD_status_t SendSimpleSwitchToggle(uint16_t address)
{
   openD_hanfunApi_profileReq_t hProfileRequest;
   hProfileRequest.profile = OPEND_HANFUNAPI_SIMPLE_ONOFF_SWITCH;
   hProfileRequest.simpleOnOffSwitch.service = OPEND_HANFUN_IONOFF_CLIENT_TOGGLE;

   return openD_hanfunApi_fp_profileRequest(&hProfileRequest, address, 1);
}

int main(int argc, char* argv[])
{
   // HAN-FUN Transport Layer over ULE Stack
   HF::ULE::Transport* transport = HF::ULE::Transport::instance();

   // Variable for the openD primitives
   openD_hanfunApiPrimitives openD_Api;

   // Set the confirmation and indication callbacks
   openD_Api.openD_hanfunApiProfileCfm = profileConfirmCallback;
   openD_Api.openD_hanfunApiProfileInd = profileIndCallback;
   openD_Api.openD_hanfunApi_mgmtCfm = devMgmtConfirmCallback;
   openD_Api.openD_hanfunApi_mgmtInd = devMgmtIndicationCallback;
   openD_Api.openD_hanfunApi_bindCfm = bindMgmtConfirmCallback;

   // Initialize the openD HANFUN API primitives
   if(openD_hanfunApi_init(&openD_Api) != OPEND_STATUS_OK)
   {
      printf("Initialization of primitives: FAILED\n");
   }

   initUleApp(argc, argv);
   openD_init(argv[1]);

   transport->initialize();
   openD_hanfunApi_fp_init(transport);

   // ****** Create your profiles hexe ******
   opend_hanfunApi_createProfile(OPEND_HANFUNAPI_SIMPLE_LIGHT, 1); // Create simple light profile
   opend_hanfunApi_createProfile(OPEND_HANFUNAPI_SIMPLE_ONOFF_SWITCH, 2); // Create simple switch profile
   // ****** End of creation of profiles ******

   // Restore saved registered devices
   HF::Application::Restore();

   // ****** Insert your application code here ******



   // ****** End of application code ******

   transport->destroy();
}