/* value_reset_widget.h - Widget containing Reset button */

// Copyright (C) 2018 Sanford Rockowitz <rockowitz@minsoft.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef VALUE_RESET_WIDGET_H
#define VALUE_RESET_WIDGET_H

#include <QtWidgets/QPushButton>

#include "value_base_widget.h"

class QPushButton;

class ValueResetWidget : public ValueBaseWidget
{
    Q_OBJECT

public:
    ValueResetWidget(QWidget *parent = nullptr);

private slots:
    void on_resetButton_pressed();

private:
    QPushButton * _resetButton;
};

#endif // VALUE_RESET_WIDGET_H
