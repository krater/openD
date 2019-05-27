#!/bin/bash
clear
echo "Please select your target hardware"
echo ""
echo "1) DSPG FP, Raspberry Pi"
echo "2) DSPG PP, Nucleo"
echo "3) Dialog FP, Raspberry Pi"
echo "4) Dialog PP, Nucleo"
echo ""

while [ 1 ]
do
  read -rsn1 input

  case $input in
  1)
    CMAKE_TOOLCHAIN_FILE=cmake/toolchains/arm-linux-gnueabihf.cmake
    BOARD=DspgDectRpi
    MANU=DSPG
    DEV=FP
    break
    ;;
  2)
    CMAKE_TOOLCHAIN_FILE=cmake/toolchains/toolchain-cortex-M4.cmake
    BOARD=DspgDectNucleo
    MANU=DSPG
    DEV=PP
    break
    ;;
  3)
    CMAKE_TOOLCHAIN_FILE=cmake/toolchains/arm-linux-gnueabihf.cmake
    BOARD=DialogMmiRpi
    MANU=Dialog
    DEV=FP
    break
    ;;
  4)
    CMAKE_TOOLCHAIN_FILE=cmake/toolchains/toolchain-cortex-M4.cmake
    BOARD=DialogMmiNucleo
    MANU=Dialog
    DEV=PP
    break
    ;;
  *)
    ;;
  esac
done

if [ ${DEV} == "FP" ]
then

  echo ""
  echo "Please select your example application"
  echo ""
  echo "1) FP_HANFUN_SERVER"
  echo "2) FP_HANFUN_CLIENT"
  echo "3) FP_LEGACY_SERVER"
  echo "4) FP_LEGACY_CLIENT"
  echo "5) FP_HANFUN_ALARM"
  echo "6) FP_HANFUN_POWERSWITCH"
  echo ""

  while [ 1 ]
  do
    read -rsn1 input

    case $input in
    1)
      APPLICATION=HANFUN_SERVER
      break
      ;;
    2)
      APPLICATION=HANFUN_CLIENT
      break
      ;;
    3)
      APPLICATION=LEGACY_SERVER
      break
      ;;
    4)
      APPLICATION=LEGACY_CLIENT
      break
      ;;
    5)
      APPLICATION=HANFUN_ALARM
      break
      ;;
    6)
      APPLICATION=HANFUN_SOCKET
      break
      ;;
    *)
      ;;
    esac

  done
fi

if [ ${DEV} == "PP" ]
then

  echo ""
  echo "Please select your example application"
  echo ""
  echo "1) PP_HANFUN_SIMPLELIGHT"
  echo "2) PP_HANFUN_SIMPLESWITCH"
  echo "3) PP_LEGACY_INTERCOM"
  echo "4) PP_LEGACY_BASICCALL"
  echo ""

  while [ 1 ]
  do
    read -rsn1 input

    case $input in
    1)
      APPLICATION=HANFUN_SIMPLELIGHT
      break
      ;;
    2)
      APPLICATION=HANFUN_SIMPLESWITCH
      break
      ;;
    3)
      APPLICATION=LEGACY_INTERCOM
      break
      ;;
    4)
      APPLICATION=LEGACY_BASICCALL
      break
      ;;

    *)
      ;;
    esac

  done
fi


mkdir build
rm -rf build/${MANU}_${DEV}_${APPLICATION}
mkdir build/${MANU}_${DEV}_${APPLICATION}
cd build/${MANU}_${DEV}_${APPLICATION}
cmake -DCMAKE_BUILD_TYPE=Release -DTOOLCHAIN_PREFIX=/usr -DCMAKE_TOOLCHAIN_FILE=$CMAKE_TOOLCHAIN_FILE -DBOARD=$BOARD -DAPPLICATION=${DEV}_${APPLICATION} ../..
cd ../..

echo ""
echo "You will find your configured project in build/${MANU}_${DEV}_${APPLICATION}"
echo "switch to this directory and call"
echo "make"
echo "to bulid it"
echo ""
echo "Have Fun!"


