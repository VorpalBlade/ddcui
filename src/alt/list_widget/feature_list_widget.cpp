/* feature_list_widget.cpp */

/* <copyright>
 * Copyright (C) 2018 Sanford Rockowitz <rockowitz@minsoft.com>
 *
 * Licensed under the GNU General Public License Version 2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * </endcopyright>
 */

#include "alt/list_widget/feature_list_widget.h"

#include <assert.h>
#include <iostream>
#include "nongui/feature_base_model.h"
#include "nongui/feature_value.h"

#include "alt/list_widget/feature_widget_extended.h"

using namespace std;

static bool debugMain    = false;

FeatureListWidget::FeatureListWidget(QWidget * parent):
    QListWidget(parent)
{
    _cls       = metaObject()->className();
    _baseModel = NULL;            // avoid Coverity warning
}


void FeatureListWidget::setModel(FeatureBaseModel * baseModel) {
    if (debugMain)
        printf("(FeatureListWidget::%s)\n", __func__); fflush(stdout);

    _baseModel = baseModel;
}


int FeatureListWidget::findFeatureItem(uint8_t feature_code) {
    int result = -1;

    for (int ndx = 0; ndx < count(); ndx++) {
        FeatureWidgetExtended * curItem = (FeatureWidgetExtended*) item(ndx);  // ???
        if (curItem->_feature_code == feature_code) {
            result = ndx;
            break;
        }
    }

    return result;
}


FeatureWidgetExtended * FeatureListWidget::getFeatureItem(uint8_t feature_code) {
    FeatureWidgetExtended * result = NULL;

    for (int ndx = 0; ndx < count(); ndx++) {
        FeatureWidgetExtended * curItem = (FeatureWidgetExtended *) item(ndx);
        if (curItem->_feature_code == feature_code) {
            result = curItem;
            break;
        }
    }

    return result;
}


void FeatureListWidget::addFeature(FeatureValue * fv) {
    if (debugMain)
        printf("(%s::%s)\n", _cls, __func__); fflush(stdout);

    FeatureWidgetExtended * itemWidget = new FeatureWidgetExtended();
    itemWidget->setFeatureValue(*fv);
    // printf("(%s::%s) Calling addItem()...\n", _cls, __func__); fflush(stdout);
    addItem(itemWidget);
    // printf("(%s::%s) After addItem()\n", _cls, __func__); fflush(stdout);
}


void FeatureListWidget::updateFeature(FeatureValue * fv) {
    FeatureWidgetExtended * itemWidget = getFeatureItem(fv->featureCode());
    assert(itemWidget);

    uint16_t newval = (fv->val().sh << 8) | fv->val().sl;
    itemWidget->setCurrentValue(newval);
    // signal paint event?
}


// void modelMccsVersionSet(DDCA_MCCS_Version_Spec    vspec);
// DDCA_MCCS_Version_Spec mccsVersionSpec();

void  FeatureListWidget::startInitialLoad(void) {
    if (debugMain)
        printf("FeatureListWidget::%s)\n", __func__); fflush(stdout);

    // setUpdatesEnabled(true); // no effect
    // show();                  // no effect

}

void   FeatureListWidget::endInitialLoad(void) {
    if (debugMain) {
        printf("(FeatureListWidget::%s)\n", __func__); fflush(stdout);
        // printf("   count: %d\n", count()); fflush(stdout);
        dbgrpt();
    }

    setUpdatesEnabled(true);
    show();
    update();
#ifdef NO
    for (int ndx = 0; ndx < count(); ndx++) {
        FeatureWidgetExtended * curItem = (FeatureWidgetExtended*) item(ndx);  // ???
        curItem->show();
    }
#endif

}

// slot
void  FeatureListWidget::featureAdded(FeatureValue fv) {
   if (debugSignals) {
        printf("FeatureListWidget::%s) feature_code=0x%02x\n", __func__, fv.featureCode()); fflush(stdout);
        // a QListWidget is not a QWidget - but is is a QObject
        QString objname = QListWidget::objectName();
        std::cout << "        objectname: " << objname.toStdString() << std::endl;
        // printf("(FeatureListWidget::%s) _baseModel=%p\n", __func__, _baseModel);
    }

    FeatureValue * fv2 = _baseModel->modelVcpValueFind(fv.featureCode());
    assert(fv2);
    addFeature(&fv);

}

void   FeatureListWidget::featureUpdated(char feature_code) {
    if (debugSignals)
        printf("FeatureListWidget::%s) feature_code=0x%02x\n", __func__, feature_code); fflush(stdout);

    FeatureValue * fv = _baseModel->modelVcpValueFind(feature_code);
    assert(fv);
    updateFeature(fv);
}

void   FeatureListWidget::featureUpdated3(
          const char *  caller,
          uint8_t feature_code,
          uint8_t sh,
          uint8_t sl)
{
    if (debugSignals)
        printf("FeatureListWidget::%s) feature_code=0x%02x\n", __func__, feature_code); fflush(stdout);

    FeatureValue * fv = _baseModel->modelVcpValueFind(feature_code);
    assert(fv);
    updateFeature(fv);
}



#ifdef OLD
void    FeatureListWidget::featureChangedObserver(uint8_t feature_code) {
     printf("FeatureListWidget::%s) feature_code=0x%02x\n", __func__, feature_code); fflush(stdout);
     FeatureValue * fv = _baseModel->modelVcpValueFind(feature_code);
     assert(fv);
     addFeature(fv);

}
#endif

// #ifdef NO_FEATURE_CHANGED
void    FeatureListWidget::featureChanged(char * caller, char feature_code, char sh, char sl)  {
     if (debugSignals)
         printf("FeatureListWidget::%s) feature_code=0x%02x\n", __func__, feature_code); fflush(stdout);
     FeatureValue * fv = _baseModel->modelVcpValueFind(feature_code);
     assert(fv);
     addFeature(fv);

}
// #endif

void FeatureListWidget::paintEvent(QPaintEvent *event) {
     if (debugMain)
         printf("(%s::%s)\n", _cls, __func__); fflush(stdout);
     // QListWidget::paintEvent(event);
     if (debugSignals)
         printf("(%s::%s) Calling update() for %d FeatureWidget instances\n", _cls, __func__, count()); fflush(stdout);

     for (int ndx = 0; ndx < count(); ndx++) {
         FeatureWidgetExtended * curItem = (FeatureWidgetExtended*) item(ndx);  // ???
         // printf("(%s::%s) Calling update() for FeatureWidget %d\n", _cls, __func__, ndx); fflush(stdout);
         curItem->setUpdatesEnabled(true);  // no effect
         // curItem->setVisible(true);   // fills screen with empty window for each feature
         // fills scroll area, but items are empty
         curItem->update();    // not the culprit
         // curItem->repaint();    // syncronously for developemnt
     }
}


void  FeatureListWidget::dbgrpt() const {
    std::string on1 = objectName().toStdString();
    const char * objname = on1.c_str();
    printf("FeatureListWidget: %-20s contains %d ListWidgets\n", objname, count());
    for (int ndx = 0; ndx < count(); ndx++) {
        FeatureWidgetExtended * curItem = (FeatureWidgetExtended*) item(ndx);
        curItem->dbgrpt();
    }
    fflush(stdout);
}
