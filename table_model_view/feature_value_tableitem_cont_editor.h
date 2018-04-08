/* feature_value_tableitem_cont_editor.h */

#ifndef FEATURE_VALUE_TABLEITEM_CONT_EDITOR_H
#define FEATURE_VALUE_TABLEITEM_CONT_EDITOR_H

#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

#include "feature_value_tableitem_abstract_editor.h"
#include "nongui/feature_value.h"

class FeatureValueTableItemContEditor : public FeatureValueTableItemAbstractEditor
{
    Q_OBJECT

public:
    explicit FeatureValueTableItemContEditor(QWidget *parent = nullptr);

    QSize sizeHint() const override;
    void setFeatureValue(const FeatureValue &fv);
    FeatureValue featureValue();

    void setCurValue(ushort curVal);

// signals are protected in QT4, public in QT5
signals:
    void editingFinished();

protected:
        void paintEvent(QPaintEvent *event) override;
#ifdef ARE_THESE_NEEDED

    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
#endif

public slots:

private:
    // FeatureValue  _fv;   // should probably be a pointer

    QSlider*    _curSlider;
    QSpinBox*   _curSpinBox;
    QLabel*     _maxTitle;
    QLabel*     _maxValue;

};

#endif // FEATURE_VALUE_TABLEITEM_CONT_EDITOR_H