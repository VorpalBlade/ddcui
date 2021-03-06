/* monitor.h */

/* <copyright>
 * Copyright (C) 2018 Sanford Rockowitz <rockowitz@minsoft.com>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 * </endcopyright>
 */

#ifndef MONITOR_H
#define MONITOR_H

#include <QtCore/QObject>
#include <QtCore/QHash>

#include <ddcutil_c_api.h>

#include "config.h"
#include "base/feature_selector.h"

class QListView;
class QListWidget;
class QPlainTextEdit;
class QTableView;
class QTableWidget;
class QWidget;
// class QHash;  // incomplete type, need full #include <QtCore/QHash>

class FeatureBaseModel;
class FeatureItemModel;
class FeatureListWidget;
class FeaturesScrollAreaView;
class FeaturesScrollAreaView;
class FeatureTableModel;
class VcpRequest;
class VcpRequestQueue;


// Represents a single display

class Monitor : public QObject
{
    Q_OBJECT

public:
    Monitor(DDCA_Display_Info * display_info, int monitorNumber);
    ~Monitor();

    DDCA_Feature_List getFeatureList(DDCA_Feature_Subset_Id);
    bool supportsDdc();
    void dbgrpt();

    const int            _monitorNumber = -1;    // 1 based
    DDCA_Display_Info *  _displayInfo;
    FeatureBaseModel *   _baseModel;
    VcpRequestQueue*     _requestQueue;

    QWidget *           _page_moninfo;
    int                 _pageno_moninfo;
    QPlainTextEdit *    _moninfoPlainText;

    QWidget *           _page_capabilities;
    int                 _pageno_capabilities;
    QPlainTextEdit *    _capabilitiesPlainText;

    FeatureSelector     _curFeatureSelector;

    // FEATURES_VIEW_SCROLLAREAVIEW
    // When using FeaturesScrollAreaView, do not allocate a permanent
    // QScrollArea and contents.  These must be created dynamically
    // each time features are loaded.
    FeaturesScrollAreaView * _featuresScrollAreaView = NULL;

public slots:
        void putVcpRequest(VcpRequest * rqst);

private:
    const char *  _cls;    // className
    QHash<DDCA_Feature_Subset_Id, DDCA_Feature_List> _features;

    // try removing from ifdef
public:
    FeatureItemModel *   _listModel;   // for central widget alternative
    FeatureTableModel *  _tableModel;
    void setFeatureItemModel(FeatureItemModel * listModel);      // ALT
    void setFeatureTableModel(FeatureTableModel * tableModel);

#ifdef ALT_FEATURES
// *** Begin Functions and Variables for Alternative Central Widgets ***

public:
    // For selecting among alternative features views
    enum FeaturesView {
       FEATURES_VIEW_SCROLLAREA_VIEW,
       FEATURES_VIEW_SCROLLAREA_MOCK,
       FEATURES_VIEW_TABLEVIEW,
       FEATURES_VIEW_TABLEWIDGET,
       FEATURES_VIEW_LISTVIEW,
       FEATURES_VIEW_LISTWIDGET,
       FEATURES_VIEW_UNSET
    };



    FeaturesView         _curFeaturesView = FEATURES_VIEW_UNSET;



#ifdef UNUSED
    QWidget *           page_vcp;
    QListWidget *       vcpListWidget;
    int                 _pageno_vcp;
#endif

    // FEATURES_VIEW_LISTWIDGET, initListWidget()
    QWidget *           _page_listWidget   = NULL;
    FeatureListWidget * _featureListWidget = NULL;
    int                 _pageno_listWidget = -1;

#ifdef UNUSED
    QWidget *page_list_widget;
    // QListWidget *feature_listWidget;
    FeatureListWidget * feature_listWidget;
    int _pageno_list_widget;
#endif

    // FEATURES_VIEW_LISTVIEW
    QWidget *           page_list_view    = NULL;
    QListView *         vcp_listView      = NULL;
    int                 _pageno_list_view = -1;

    // FEATURES_VIEW_TABLEWIDGET
    // init function defined, but no action
    QWidget *           page_table_item     = NULL;
    QTableWidget *      tableWidget         = NULL;
    int                 _pageno_table_item  = -1;

    // FEATURES_VIEW_TABLEVIEW
    QWidget *           _page_table_view   = NULL;
    QTableView *        _vcp_tableView     = NULL;
    int                 _pageno_table_view = -1;

    // QScrollArea *                 _page_features_scrollarea;
    // FeaturesScrollAreaContents *  _featuresScrollAreaContents;
    // int                           _pageno_features_scrollarea;

    // *** End Alternative Central Widgets ***
#endif

};

#endif // MONITOR_H
