/* value_std_widget.cpp */

// Copyright (C) 2018 Sanford Rockowitz <rockowitz@minsoft.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "feature_value_widgets/value_std_widget.h"

#include <QtCore/QRect>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>

#include "ddcutil_c_api.h"

#include "base/debug_utils.h"
#include "base/ddcui_globals.h"


static bool dimensionReportShown = false;


ValueStdWidget::ValueStdWidget(QWidget *parent):
        ValueBaseWidget(parent)
{
    _cls = strdup(metaObject()->className());
    // PRINTFCM("Starting");

    QFont font;
    font.setPointSize(8);
    QWidget::setFont(font);

    QFont monoValueFont;
    monoValueFont.setFamily(QString::fromUtf8("Monospace"));

    QFont nonMonoValueFont;

    // printf("(%s::%s) Starting\n", _cls, __func__);  fflush(stdout);
    _valueField = new QLabel();
    _valueField->setAlignment(Qt::AlignLeft);
    // _valueField->setFrameStyle(QFrame::Sunken | QFrame::Panel);  // now set in ValueBaseWidget
    _valueField->setMinimumSize(400,10);
    _valueField->setFrameStyle( QFrame::Plain | QFrame::NoFrame);  // ValueStdWidget has the frame, not Label
    _valueField->setFont(font);
    _valueField->setIndent(5);

    // QSizePolicy* sizePolicy = new QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    QSizePolicy* sizePolicy = new QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    sizePolicy->setHorizontalStretch(1);
    // _cb->setHorizontalStretch(0);
    _valueField->setSizePolicy(*sizePolicy);
    delete sizePolicy;
    QHBoxLayout * layout = new QHBoxLayout();
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(_valueField);
    setLayout(layout);

    // int fieldFrameStyle;
    // fieldFrameStyle = QFrame::Sunken | QFrame::Panel;
    // fieldFrameStyle = QFrame::Plain | QFrame::Box;

    if (debugLayout) {
       this->setStyleSheet("background-color:magenta;");
       // _valueField->setStyleSheet("background-color:fuschia;");

       if (!dimensionReportShown) {
           PRINTFCM("_valueField dimensions\n");
           reportWidgetDimensions(_valueField, _cls, __func__);

           PRINTFCM("ValueStdWidget dimensions\n");
           reportWidgetDimensions(this, _cls, __func__);

           dimensionReportShown = true;
       }
    }
}


void ValueStdWidget::setValueField() {
    char * s_formatted = NULL;
    DDCA_Non_Table_Vcp_Value valrec;
    valrec.mh = _mh;
    valrec.ml = _ml;
    valrec.sh = _sh;
    valrec.sl = _sl;
    DDCA_Status rc = ddca_format_non_table_vcp_value_by_dref(
          _featureCode,
          _dref,
          &valrec,
          &s_formatted);
    if (rc != 0)
        s_formatted = (char*) "invalid formatted value";   // cast to avoid compiler warning

    _valueField->setText(QString::fromUtf8(s_formatted));
}


void ValueStdWidget::setFeatureValue(const FeatureValue &fv) {
    PRINTFCMF(debugValueWidgetSignals, "Starting. feature code: 0x%02x", fv.featureCode());
    ValueBaseWidget::setFeatureValue(fv);
    setValueField();
}


void ValueStdWidget::setCurrentValue(uint16_t newval) {
    ValueBaseWidget::setCurrentValue(newval);
    setValueField();
}


#ifdef DEBUG_PAINT
void ValueStdWidget::paintEvent(QPaintEvent *event) {
                // printf("(%s::%s) Starting\n", _cls, __func__);  fflush(stdout);
                const QRect rect = event->rect();
                // const QRegion = event->region();
                int x;
                int y;
                int width;
                int height;
                rect.getRect(&x, &y, &width, &height);
                printf("(ValueStdWidget::%s) event rectangle: x:%d, y:%d, width:%d, height:%d\n",
                       __func__, x, y, width, height);  fflush(stdout);
                this->ValueBaseWidget::paintEvent(event);
}
#endif

