/*
 *  Copyright (c) 2016, The OpenThread Authors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

#include <assert.h>
#include <string.h>
#include <openthread-core-config.h>
#include <openthread/config.h>

#include <openthread/cli.h>
#include <openthread/diag.h>
#include <openthread/tasklet.h>
#include <openthread/platform/logging.h>
#include <openthread/platform/uart.h>
#include <openthread/instance.h>
#include <openthread/thread.h>
#include <openthread/thread_ftd.h>
#include <openthread/ip6.h>
#include <openthread/udp.h>
#include <openthread/message.h>

#include "openthread-system.h"
#include "utils/code_utils.h"

#define UDP_PORT 5569
static const char UDP_MULTICAST[] = "ff03::1";

void handleNetifStateChanged(uint32_t aFlags, void *aContext); // Board function to control RGB Thread state LED
void handleUdpReceive(void *aContext, otMessage *aMessage, const otMessageInfo *aMessageInfo); // Board function to handling UDP receive
static void initUdp(otInstance *aInstance);
static void sendUdp(otInstance *aInstance, otIp6Address destIp, char *messageString);

static otUdpSocket sUdpSocket;
otInstance *instance;

void sendLEDnum(int argc, char *argv[]); // UART test function: returns LED number as set by GPIO

int getLEDnum(void); // Board function to determine which LED number this board is set to
// void connectCheck(int argc, char *argv[]); // Server startup command for server to check what LEDs are connected
void ledOn(int argc, char *argv[]); // Server command to turn an LED on
void ledOff(int argc, char *argv[]); // Server command to turn an LED off
// void sendAck(void); // Board function to send acknowledgement back to message sender once LED request has been handled
// void recvAck(void); // Board funtion to receive acknowledgement and relay to server

#if OPENTHREAD_EXAMPLES_POSIX
#include <setjmp.h>
#include <unistd.h>

jmp_buf gResetJump;

void __gcov_flush();
#endif

#if OPENTHREAD_CONFIG_MULTIPLE_INSTANCE_ENABLE
void *otPlatCAlloc(size_t aNum, size_t aSize)
{
    return calloc(aNum, aSize);
}

void otPlatFree(void *aPtr)
{
    free(aPtr);
}
#endif

void otTaskletsSignalPending(otInstance *aInstance)
{
    OT_UNUSED_VARIABLE(aInstance);
}

int main(int argc, char *argv[])
{


#if OPENTHREAD_EXAMPLES_POSIX
    if (setjmp(gResetJump))
    {
        alarm(0);
#if OPENTHREAD_ENABLE_COVERAGE
        __gcov_flush();
#endif
        execvp(argv[0], argv);
    }
#endif

#if OPENTHREAD_CONFIG_MULTIPLE_INSTANCE_ENABLE
    size_t   otInstanceBufferLength = 0;
    uint8_t *otInstanceBuffer       = NULL;
#endif

pseudo_reset:

    otSysInit(argc, argv);

#if OPENTHREAD_CONFIG_MULTIPLE_INSTANCE_ENABLE
    // Call to query the buffer size
    (void)otInstanceInit(NULL, &otInstanceBufferLength);

    // Call to allocate the buffer
    otInstanceBuffer = (uint8_t *)malloc(otInstanceBufferLength);
    assert(otInstanceBuffer);

    // Initialize OpenThread with the buffer
    instance = otInstanceInit(otInstanceBuffer, &otInstanceBufferLength);
#else
    instance = otInstanceInitSingle();
#endif
    assert(instance);

    otSysLEDInit();
    otSysPinsInit();
    initUdp(instance);

    otLinkSetPanId(instance,0xa420);
    otIp6SetEnabled(instance,true);
    otThreadSetEnabled(instance,true);

    otCliUartInit(instance);
    const struct otCliCommand testcommands[] = {
      {"getLED",&sendLEDnum},
      {"ledOn",&ledOn},
      {"ledOff",&ledOff},
    };
    otCliSetUserCommands(testcommands,3);

    otSetStateChangedCallback(instance, handleNetifStateChanged, instance);

    while (!otSysPseudoResetWasRequested())
    {
        otTaskletsProcess(instance);
        otSysProcessDrivers(instance);
    }

    otInstanceFinalize(instance);
#if OPENTHREAD_CONFIG_MULTIPLE_INSTANCE_ENABLE
    free(otInstanceBuffer);
#endif

    goto pseudo_reset;

    return 0;
}

void handleNetifStateChanged(uint32_t aFlags, void *aContext){
  if ((aFlags & OT_CHANGED_THREAD_ROLE) != 0){
    otDeviceRole changedRole = otThreadGetDeviceRole(aContext);

    switch(changedRole){
      case OT_DEVICE_ROLE_LEADER:
        otSysLEDSet(0,false);
        otSysLEDSet(1,true);
        otSysLEDSet(2,true);
        break;
      case OT_DEVICE_ROLE_ROUTER:
        otSysLEDSet(0,false);
        otSysLEDSet(1,true);
        otSysLEDSet(2,false);
        break;
      case OT_DEVICE_ROLE_CHILD:
        otSysLEDSet(0,false);
        otSysLEDSet(1,false);
        otSysLEDSet(2,true);
        break;
      case OT_DEVICE_ROLE_DETACHED:
        otSysLEDSet(0,true);
        otSysLEDSet(1,false);
        otSysLEDSet(2,false);
        break;
      case OT_DEVICE_ROLE_DISABLED:
        otSysLEDSet(0,false);
        otSysLEDSet(1,false);
        otSysLEDSet(2,false);
        break;
    }
  }
}

void handleUdpReceive(void *aContext, otMessage *aMessage, const otMessageInfo *aMessageInfo){
  OT_UNUSED_VARIABLE(aContext);
  OT_UNUSED_VARIABLE(aMessageInfo); //temp
  char recvBuffer[20];
  // otIp6Address sender = aMessageInfo->mPeerAddr;
  otMessageRead(aMessage,otMessageGetOffset(aMessage),recvBuffer,sizeof(recvBuffer));
  otCliOutputFormat("Received: %s \n\r", recvBuffer);

  if(strncmp(recvBuffer,"connectcheck",12) == 0){

  }
  else if(strncmp(recvBuffer,"ledon",5) == 0){
    otSysLEDSet(3,true);
  }
  else if(strncmp(recvBuffer,"ledoff",6) == 0){
    otSysLEDSet(3,false);
  }
  else if(strncmp(recvBuffer,"ack",3) == 0){

  }
}

void initUdp(otInstance *aInstance){
  otSockAddr listenSockAddr;

  memset(&sUdpSocket, 0, sizeof(sUdpSocket));
  memset(&listenSockAddr, 0, sizeof(listenSockAddr));

  listenSockAddr.mPort = UDP_PORT;

  otUdpOpen(aInstance, &sUdpSocket, handleUdpReceive, aInstance);
  otUdpBind(&sUdpSocket, &listenSockAddr);
}

void sendUdp(otInstance *aInstance, otIp6Address destIp, char *messageString){
  otError error = OT_ERROR_NONE;
  otMessage *message = NULL;
  otMessageInfo messageInfo;

  memset(&messageInfo, 0, sizeof(messageInfo));

  messageInfo.mPeerAddr = destIp;
  messageInfo.mPeerPort = UDP_PORT;

  message = otUdpNewMessage(aInstance, NULL);
  otEXPECT_ACTION(message != NULL, error = OT_ERROR_NO_BUFS);

  error = otMessageAppend(message, messageString, strlen(messageString));
  otEXPECT(error == OT_ERROR_NONE);

  error = otUdpSend(&sUdpSocket, message, &messageInfo);

exit:
  if(error != OT_ERROR_NONE && message != NULL){
    otMessageFree(message);
  }
  otCliOutputFormat("Sent something \n\r");
}

void sendLEDnum(int argc, char *argv[]){
  OT_UNUSED_VARIABLE(argc);
  OT_UNUSED_VARIABLE(argv);
  otCliOutputFormat(
    "LED NUM: %d \n\r", getLEDnum()
  );
}

int getLEDnum(void){
  int num = 0;
  for(int i=1;i<=4;i++){
    if(otSysPinsRead(i)==0){
      num = i;
      break;
    }
  }
  return num;
}

// void connectCheck(int argc, char *argv[]){
//
// }

void ledOn(int argc, char *argv[]){
  OT_UNUSED_VARIABLE(argc);
  OT_UNUSED_VARIABLE(argv);
  otIp6Address destAddr;
  otIp6AddressFromString(UDP_MULTICAST, &destAddr);
  sendUdp(instance, destAddr, "ledon");
}

void ledOff(int argc, char *argv[]){
  OT_UNUSED_VARIABLE(argc);
  OT_UNUSED_VARIABLE(argv);
  otIp6Address destAddr;
  otIp6AddressFromString(UDP_MULTICAST, &destAddr);
  sendUdp(instance, destAddr, "ledoff");
}

// void sendAck(void){
//
// }
//
// void recvAck(void){
//
// }

/*
 * Provide, if required an "otPlatLog()" function
 */
#if OPENTHREAD_CONFIG_LOG_OUTPUT == OPENTHREAD_CONFIG_LOG_OUTPUT_APP
void otPlatLog(otLogLevel aLogLevel, otLogRegion aLogRegion, const char *aFormat, ...)
{
    OT_UNUSED_VARIABLE(aLogLevel);
    OT_UNUSED_VARIABLE(aLogRegion);
    OT_UNUSED_VARIABLE(aFormat);

    va_list ap;
    va_start(ap, aFormat);
    otCliPlatLogv(aLogLevel, aLogRegion, aFormat, ap);
    va_end(ap);
}
#endif
