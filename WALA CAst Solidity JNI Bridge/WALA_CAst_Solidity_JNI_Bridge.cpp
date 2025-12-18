//
//  WALA_CAst_Solidity_JNI_Bridge.cpp
//  WALA CAst Solidity JNI Bridge
//
//  Created by Julian Dolby on 12/18/25.
//

#include <iostream>
#include "WALA_CAst_Solidity_JNI_Bridge.hpp"
#include "WALA_CAst_Solidity_JNI_BridgePriv.hpp"

void WALA_CAst_Solidity_JNI_Bridge::HelloWorld(const char * s)
{
    WALA_CAst_Solidity_JNI_BridgePriv *theObj = new WALA_CAst_Solidity_JNI_BridgePriv;
    theObj->HelloWorldPriv(s);
    delete theObj;
};

void WALA_CAst_Solidity_JNI_BridgePriv::HelloWorldPriv(const char * s) 
{
    std::cout << s << std::endl;
};

