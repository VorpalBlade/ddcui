//feature_widget_header.cpp

// Copyright (C) 2018 Sanford Rockowitz <rockowitz@minsoft.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include <QtWidgets/QFrame>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSizePolicy>
#include <QtWidgets/QHBoxLayout>

#include "base/debug_utils.h"

#include "feature_widget_header.h"


static bool dimensionsReported = false;

static void stdLabelSetup(QLabel * l) {
   // l->setFrameStyle(QFrame::NoFrame | QFrame::Plain);
   l->setFrameStyle(QFrame::Box | QFrame::Plain);
   // setMargin()
   // setindent()
   //set

   QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
   l->setSizePolicy(sizePolicy);
   // l->setHorizontalPolicy(QSizePolicy::Fixed);
   // l->setVerticalPolicy(QSizePolicy::Fixed);

   QFont font;
   font.setPointSize(8);
   font.setWeight(QFont::Bold);
   l->setFont(font);
   l->setContentsMargins(0,0,0,0);
   l->setMargin(0);
   l->setIndent(0);

}



FeatureWidgetHeader::FeatureWidgetHeader(QWidget * parent)
: QFrame(parent)
{
   _cls = metaObject()->className();

   QLabel * _codeLabel  = new QLabel("Code");
   QLabel * _nameLabel  = new QLabel("Name");
   QLabel * _rwLabel    = new QLabel("RW");
   QLabel * _typeLabel  = new QLabel("Type");
   QLabel * _valueLabel = new QLabel("Value");

   stdLabelSetup(_codeLabel);
   stdLabelSetup(_nameLabel);
   stdLabelSetup(_rwLabel);
   stdLabelSetup(_typeLabel);
   stdLabelSetup(_valueLabel);

   _codeLabel->setMinimumWidth(30);
   _nameLabel->setFixedWidth(200-2);
   _rwLabel->setFixedWidth(25-1);
   _typeLabel->setFixedWidth(25+1+4);
   _valueLabel->setMinimumWidth(200-4+2);

   QSizePolicy adjSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
   _valueLabel->setSizePolicy(adjSizePolicy);


   QHBoxLayout * layout = new QHBoxLayout();
   layout->addWidget(_codeLabel);
   layout->addWidget(_nameLabel);
   layout->addWidget(_rwLabel);
   layout->addWidget(_typeLabel);
   layout->addWidget(_valueLabel);

   layout->setSpacing(0);

   setLayout(layout);

   setFrameStyle(QFrame::NoFrame | QFrame::Plain);
   setContentsMargins(1,1,1,1);  // 0,0,0,0 doesn't move "Code" left



   setLineWidth(1);

   if (debugLayout) {
      setStyleSheet("background-color:beige;");

      if (!dimensionsReported) {
         reportLabelDimensions(_codeLabel, _cls, __func__, "_codeLabel dimensions");
         reportLabelDimensions(_nameLabel, _cls, __func__, "_nameLabel dimensions");
         reportLabelDimensions(_rwLabel, _cls, __func__, "_rwLabel dimensions");
         reportLabelDimensions(_typeLabel, _cls, __func__, "_typeLabel dimensions");
         reportLabelDimensions(_valueLabel, _cls, __func__, "_valueLabel dimensions");

         reportFrameDimensions(this, _cls, __func__, "FeatureWidgetHeader dimensions");

         dimensionsReported = true;
      }
   }
}

FeatureWidgetHeader::~FeatureWidgetHeader() {
   // TODO Auto-generated destructor stub
}

