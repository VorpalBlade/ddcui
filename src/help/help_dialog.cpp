// help_dialog.cpp

// Copyright (C) 2018 Sanford Rockowitz <rockowitz@minsoft.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

#include "help_dialog.h"


void HelpDialog2::commonInit() {
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_GroupLeader);

    Qt::WindowFlags flags = windowFlags();
    flags &= ~Qt::WindowContextHelpButtonHint;
    setWindowFlags(flags);

    _textBrowser = new QTextBrowser;
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(_textBrowser);
    setLayout(mainLayout);
    setMinimumSize(800,600);
}


HelpDialog2::HelpDialog2(QWidget* parent)
    : QDialog(parent)
{
    commonInit();
}


HelpDialog2::HelpDialog2(QString title, QString& htmlText, QWidget* parent)
    : QDialog(parent)
{
    commonInit();
    setWindowTitle(title);
    _textBrowser->setText(htmlText);
    show();   // not showing - why?
}


HelpDialog2::~HelpDialog2() {
   // TODO Auto-generated destructor stub
}


void HelpDialog2::setText(QString& htmlText) {
   _textBrowser->setText(htmlText);
}
