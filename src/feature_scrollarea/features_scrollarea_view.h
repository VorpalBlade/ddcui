/* features_scrollarea_view.h */

// Copyright (C) 2018 Sanford Rockowitz <rockowitz@minsoft.com>
// SPDX-License-Identifier: GPL-2.0-or-later

// Manages the scroll area that provides a view onto the current feature settings
// of a monitor

#ifndef FEATURES_SCROLLAREA_VIEW_H
#define FEATURES_SCROLLAREA_VIEW_H

#include <QtCore/QObject>

#include "nongui/ddc_error.h"
#include "nongui/feature_base_model.h"

#include "feature_scrollarea/feature_widget.h"

class QStackedWidget;
class Monitor;
class FeaturesScrollAreaContents;
class MsgBoxQueue;


class FeaturesScrollAreaView : public QObject
{
    Q_OBJECT

public:
    FeaturesScrollAreaView(
            Monitor *          monitor,    // needed?  complicates dependency order?
            FeatureBaseModel * model,
            QStackedWidget *   centralStackedWidget,
            MsgBoxQueue *      msgboxQueue,
            QObject *          parent = nullptr);

    void freeContents(void);    // private?

private:
    const char *       _cls;
    Monitor *          _monitor;
    FeatureBaseModel * _baseModel;
    QStackedWidget *   _centralStackedWidget;
    MsgBoxQueue *      _msgboxQueue;

    NcValuesSource     _curNcValuesSource;  // how to properly initialize?
    FeaturesScrollAreaContents * _scrollAreaContents = NULL;

    // quick and dirty for now, eventually replace by hash
    FeatureWidget * _widgets[256] = {0};

    // QSemaphore  errorMsgSemaphore;

signals:
    void signalVcpRequest(VcpRequest * rqst);  // used to call into monitor

public slots:
    // void startInitialLoad(void);
    void onEndInitialLoad(void);
    void onUIValueChanged(uint8_t feature_code, bool writeOnly, uint8_t sh, uint8_t sl);
    void onModelValueChanged(const char * caller, uint8_t featureCode, uint8_t sh, uint8_t sl);
    void onNcValuesSourceChanged(NcValuesSource newsrc);
    void onModelDdcError(DdcError* perec);
};
#endif // FEATURES_SCROLLAREA_VIEW_H
