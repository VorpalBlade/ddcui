// ddc_error.cpp

// Copyright (C) 2018 Sanford Rockowitz <rockowitz@minsoft.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ddcutil_c_api.h"
#include "ddcutil_status_codes.h"

#include "ddc_error.h"

// *** DdcError ***

DdcError::DdcError()
   : _featureCode(0)
   , _ddcErrno(0)
{}


DdcError::DdcError(
      uint8_t       featureCode,
      const char *  ddcFunction,
      DDCA_Status   ddcErrno)
    : _featureCode(featureCode)
    , _ddcErrno(   ddcErrno)
    , _ddcFunction(QString(ddcFunction))
{
    // printf("(DdcError::DdcError) Executing\n"); fflush(stdout);
}


DdcError::DdcError(const DdcError& erec)
    : QObject()
    , _featureCode(erec._featureCode)
    , _ddcErrno(   erec._ddcErrno)
    , _ddcFunction(erec._ddcFunction)
{}


DdcError::~DdcError() {
   // TODO Auto-generated destructor stub
}


QString DdcError::repr() {
   // printf("(DdcError::repr) Executing\n"); fflush(stdout);
   char * s = ddca_rc_name(_ddcErrno);
   QString msg = QString("[feature=0x%1, function=%2, ddcrc=%3 - %4]")
                    .arg(_featureCode, 2, 16)
                    .arg(_ddcFunction)
                    .arg(_ddcErrno)
                    .arg(s);
   return msg;
}


char *  DdcError::srepr() {
   return strdup(repr().toLatin1().data());
}


QString DdcError::expl() {
   // printf("(DdcError::expl) Executing\n"); fflush(stdout);
   return repr();
}


char *  DdcError::sexpl() {
   return strdup(expl().toLatin1().data());
}


// *** DdcVerifyError ***

DdcVerifyError::DdcVerifyError(
      uint8_t      featureCode,
      const char * ddcFunction,
      uint8_t      expectedValue,
      uint8_t      observedValue)
    : DdcError(featureCode, ddcFunction, DDCRC_VERIFY)
    , _expectedValue(expectedValue)
    , _observedValue(observedValue)
{
   // printf("(DdcVerifyError::DdcVerifyError) Executing\n"); fflush(stdout);
}


DdcVerifyError::DdcVerifyError(const DdcVerifyError& erec)
    : DdcError(erec)
    , _expectedValue(erec._expectedValue)
    , _observedValue(erec._observedValue)
{}


DdcVerifyError::DdcVerifyError(void)
    : DdcError()
    , _expectedValue(0)
    , _observedValue(0)
{
   // printf("(DdcVerifyError::DdcVerifyError(void)\n"); fflush(stdout);
}


DdcVerifyError::~DdcVerifyError() {
   // TODO
}


QString DdcVerifyError::repr() {
   // printf("(DdcVerifyError::repr)\n"); fflush(stdout);
   char * s = ddca_rc_name(_ddcErrno);
   QString msg = QString("[feature=0x%1, function=%2, ddcrc=%3 - %4, expected: 0x%5, observed: 0x%6]")
                    .arg(_featureCode, 2, 16)
                    .arg(_ddcFunction)
                    .arg(_ddcErrno)
                    .arg(s)
                    .arg(_expectedValue, 2, 16)
                    .arg(_observedValue, 2, 16)
                    ;
   return msg;
}


QString DdcVerifyError::expl() {
   // printf("(DdcVerifyError::expl) Starting.\n"); fflush(stdout);
   QString msg = QString("Verification failed after value change for feature 0x%1.\n"
                         "Expected value: %2 (0x%3), Reported value: %4 (0x%05)")
                               .arg(_featureCode, 2, 16)
                               .arg(_expectedValue)
                               .arg(_expectedValue, 2, 16)
                               .arg(_observedValue)
                               .arg(_observedValue, 2, 16)
                               ;
   // printf("(DdcVerifyError::expl) msg: %s\n", strdup(msg.toLatin1().data()) );
   // std::cout << "(DdcVerifyError::expl) Returning: " << msg << std::endl;
   return msg;
}

