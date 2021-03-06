// value_stacked_widget.h

// Copyright (C) 2018 Sanford Rockowitz <rockowitz@minsoft.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef VALUE_STACKED_WIDGET_H
#define VALUE_STACKED_WIDGET_H

#include <QtWidgets/QStackedWidget>

// #include "nongui/simple_feature_value.h"
// #include "nongui/simple_feature_value_subject.h"

// #include "value_abstract_widget.h"
#include "value_base_widget.h"
#include "value_std_widget.h"
#include "value_cont_widget.h"
#include "value_nc_widget.h"
#include "value_reset_widget.h"
#include "value_2button_widget.h"

class QWidget;
class QPaintEvent;

class ValueStackedWidget :  public QStackedWidget
{
   Q_OBJECT

public:
    explicit ValueStackedWidget(QWidget *parent = nullptr);

    void     setFeatureValue(const FeatureValue &fv);
    void     setCurrentValue(uint16_t newval);
    uint16_t getCurrentValue();
    bool     isSimpleNc();
    void     setNcValuesSource(NcValuesSource newsrc);

    // QSize sizeHint() const override;
    // void paintEvent(QPaintEvent *event) override;

signals:
    void stackedFeatureValueChanged(uint8_t feature_code, uint8_t sh, uint8_t sl);

private:
    const char *        _cls;
    uint8_t             _featureCode;
    int                 _pageno_selected;
    ValueBaseWidget*    _cur_stacked_widget;

    int                 _pageno_std;
    int                 _pageno_cont;
    int                 _pageno_nc;
    int                 _pageno_reset;
    int                 _pageno_2button;

    ValueStdWidget*     _stdWidget;
    ValueContWidget*    _contWidget;
    ValueNcWidget*      _ncWidget;
    ValueResetWidget*   _resetWidget;
    Value2ButtonWidget* _2ButtonWidget;

private slots:
    void onContainedWidgetChanged(uint8_t feature_code, uint8_t sh, uint8_t sl);

};

#endif // VALUE_STACKED_WIDGET_H


