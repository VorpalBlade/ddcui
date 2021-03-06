// ddcui_globals.h

// Copyright (C) 2018 Sanford Rockowitz <rockowitz@minsoft.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef DDCUI_GLOBALS_H
#define DDCUI_GLOBALS_H

#include "config.h"

#include <QtCore/QtCore>
#include <QtWidgets/QListWidgetItem>

const QString ddcui_version = "0.0.1";

const int FeatureValueRole  = Qt::UserRole+1;  // DisplayRole, EditorRole, .. etc

const int FeatureWidgetType = QListWidgetItem::UserType+1;

extern const bool debugSignals            ;
extern const bool debugValueWidgetSignals ;
extern const bool debugFeatureLists       ;
extern const bool debugFeatureSelection   ;
extern const bool debugNcValues;
extern const bool debugLayout             ;

#define PRINTFCM(__FMT__, ...) \
   do { \
     printf("(%s::%s) " __FMT__ "\n", _cls, __func__, ##__VA_ARGS__); \
     fflush(stdout); \
   } while(0)

#define PRINTFCMF(__FLAG__, __FMT__, ...) \
   if (__FLAG__) { \
      printf("(%s::%s) " __FMT__ "\n", _cls, __func__, ##__VA_ARGS__); \
      fflush(stdout); \
   }

#define PRINTFTCM(__FMT__, ...) \
   do { \
     printf("(%p %s::%s) " __FMT__ "\n",  QThread::currentThreadId(), _cls, __func__, ##__VA_ARGS__); \
     fflush(stdout); \
   } while(0)

#define PRINTFTCMF(__FLAG__, __FMT__, ...) \
   if (__FLAG__) { \
      printf("(%p %s::%s) " __FMT__ "\n",  QThread::currentThreadId(), _cls, __func__, ##__VA_ARGS__); \
      fflush(stdout); \
   }


inline const char * sbool(bool val) { return (val) ? "true" : "false"; }

#define SBOOL(__v) ( (__v) ? "true" : "false")

// #define APPLY_CANCEL
// #define ALT_MOCK_FEATURES

#ifdef APPLY_CANCEL
const bool useApplyCancel    = true;
#endif
#ifdef ALT_FEATURES
const bool enableAltFeatures = true;
#endif


inline const char * qs2s(QString qstr) {return qstr.toLatin1().data(); }

#define QS2S(_qstr) ( _qstr.toLatin1().data() )

#endif // DDCUI_GLOBALS_H
