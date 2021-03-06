/* feature_table_model.cpp */

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

#include "alt/table_model_view/feature_table_model.h"

#include <assert.h>
#include <iostream>

#include <QtCore/QVector>
#include <QtWidgets/QWidget>

#include "ddcutil_c_api.h"

#include "base/ddcui_globals.h"
#include "nongui/feature_value.h"



// #include <QAbstractItemModel>

using namespace std;

FeatureTableModel::FeatureTableModel(FeatureBaseModel * baseModel, QObject *parent)
    : QAbstractTableModel(parent)
{
        _cls = metaObject()->className();
    _baseModel = baseModel;
}

QVariant FeatureTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // cout << "(FeatureTableModel::headerData) section=" << section <<
    //        ", orientation=" << orientation << ",  role=" << role << endl;

    // FIXME: Implement me!
    // section is column number, Qt::Orientation always 1 (horizontal?)
    // roles 0, 1, 9, 8
    // 0 DisplayRole - QString                             seen
    // 1 DecorationRole - icon (QColor, QIcon, QPixmap)    seen
    // 8 BackgroundRole - QBrush                           seen
    // 9 ForegroundRole - QBrush                           seen
    // 13 SizeHintRole  - QSize
    //  6 FontRole       - QFont                           seen
    //  7 TextAlignmentRole  Qt::Alignment                 seen


    QVariant result = QVariant();

    if (orientation == Qt::Horizontal) {
        if (role == Qt::DisplayRole) {
            switch(section) {
            case 0:
                result = QVariant("Vcp\nCode");
                break;
            case 1:
                result = QVariant("Feature Name");
                break;
            case 2:
                result = QVariant("Type");
                break;
            case 3:
                result = QVariant("RW");
                break;
            case 4:
                result = QVariant("Value");
                break;
            default:
                break;
            }
        }
    }

    return result;
}

bool FeatureTableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role)) {
        // FIXME: Implement me!
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}


int FeatureTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
    int result = 0;
    result = _baseModel->modelVcpValueCount();
    return result;
}

int FeatureTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
    return 5;
}

// Called by view to get data for a cell
QVariant FeatureTableModel::data(const QModelIndex &index, int role) const
{
    // printf("(FeatureTableModel::data) Starting. role=%d\n", role);
    if (!index.isValid()) {
        printf("FeatureTableModel::data) invalid index\n");  fflush(stdout);
        return QVariant();
    }

    // FIXME: Implement me!
    // return QVariant();
    int rowNdx = index.row();
    FeatureValue * fv = _baseModel->modelVcpValueAt(rowNdx);
    // printf("Retrieved feature value. fv->_feature_code=0x%02x\n", fv->_feature_code);

    // bool editable = (this->flags(index) & Qt::ItemIsEditable);   // unused
    // cout << "(FeatureTableModel::data) Index: " << index.row() << "," << index.column() << ", role:" << role
    // ..      << " editable: " << editable << ", feature_code: " << fv->_feature_code << endl;
    if (index.column() == 4) {
        // printf("(FeatureTableModel::data) Index: %d,%d, role: %d, editable: %d, feature_code: 0x%02x\n",
        //    index.row(), index.column(), role, editable, fv->_feature_code);
        // fflush(stdout);
    }

    // roles seen: 0, 1, 6,7,8,9,10,257
    QVariant result = QVariant();

    DDCA_Feature_Flags flags = fv->flags();

    switch(role) {
    case Qt::DisplayRole:          //   0
    case Qt::EditRole:             //   2
    case FeatureValueRole:         // 257
    {
        switch(index.column()) {
        case 0:                  // feature code
        {
            // result = QVariant(fv->feature_code);    // how to force display as hex?,  or convert to string here?
            char buffer[8];
            snprintf(buffer, 8, "x%02x", fv->featureCode());
            QString qs = QString(buffer);
            result = QVariant(buffer);
            break;
        }
        case 1:                 // feature name
        {
            // char * feature_name = ddca_feature_name_by_vspec(fv->_feature_code, fv->_vspec, &fv->_mmid);
            char * feature_name = fv->finfo().feature_name;
            result = QVariant(QString(feature_name));
            break;
        }
        case 2:                 // mccs type
        {
            if (fv->flags() & DDCA_CONT)
                result = QString("C");
            else if (flags & DDCA_NC)
                result = QString("NC");
            else {
                assert ( flags & DDCA_TABLE) ;
                result = QString("T");
            }
            break;
        }
        case 3:               // RW,RO,WO
        {
            if (flags & DDCA_RW)
                result = QString("RW");
            else if (flags & DDCA_RO)
                result = QString("RO");
            else {
                assert (flags & DDCA_WO) ;
                result = QString("WO");
            }
            break;
        }
        case 4:              // value
        {
            if (role == FeatureValueRole) {
                // printf("(FeatureTableModel::data) col 4, Setting QVariant from feature value\n"); fflush(stdout);
                // fv->report();
                result = QVariant::fromValue(*fv);
            }
            else {
                // printf("(FeatureTableModel::data) col 4, Setting QVariant as String\n"); fflush(stdout);
                // this will vary with display vs edit role
                if (flags & DDCA_WO) {
                    result = QVariant(QString(""));
                }
                else {
                    char * formatted_value = NULL;
                    DDCA_Non_Table_Vcp_Value value = fv->val(); // needed because can't take address of temporary in function call
                    DDCA_Status rc = ddca_format_non_table_vcp_value_by_dref(
                                         fv->featureCode(),
                                         fv->dref(),
                                         &value,
                                         &formatted_value);
                    if (rc == 0)
                       result = QVariant(QString(formatted_value));
                    else
                       result = QVariant(QString("invalid formatted value, rc=" + QString::number(rc)));
                }
            }
            break;
        }
        default:
            break;
        }
    }
    case(Qt::FontRole):     // 6
        // todo custom QVaraiant
        break;
    case (Qt::TextAlignmentRole):  // 7
        break;
    case (Qt::BackgroundRole):    // 8
       //  QBrush brush();
       // brush.setColor(Qt::yellow);

       //  printf("(%s)   BackgroundRole.  row,col=%d,%d\n", __func__, index.row(), index.column()); fflush(stdout);
       //  result = QVariant(QBrush(Qt::yellow));
        break;
    case (Qt::ForegroundRole):    // 9
        break;

    default:
        break;
    }

    // FIXME: Implement me!
    // return QVariant();
    return result;
}


// called by view to set data for a cell
bool FeatureTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    printf("(FeatureTableModel::setData) row=%d, role=%d\n", index.row(), role);
    if (value.canConvert<FeatureValue>()) {
       FeatureValue fv = value.value<FeatureValue>();
       fv.dbgrpt();
       bool writeOnly = false;    // *** TEMP, assume verification ***
       VcpSetRequest * rqst = new VcpSetRequest(fv.featureCode(), fv.val().sl, writeOnly);
       emit _baseModel->signalVcpRequest(rqst);
    }

    if (data(index, role) != value) {

        // FIXME: Implement me!
        //             top-left,bottom-rt, vector of roles that have been modified
        // TEMP, commented out due to compilation error
        // emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}


Qt::ItemFlags FeatureTableModel::flags(const QModelIndex &index) const
{
    // printf("(FeatureTableModel::flags) (%d,%d) \n", index.row(), index.column());
    if (!index.isValid())
        return Qt::NoItemFlags;

    Qt::ItemFlags result = Qt::NoItemFlags;
    if ( index.column() == 4) {
        // TODO: check feature flags to see if editable
        FeatureValue * fv = _baseModel->modelVcpValueAt(index.row() );
        if (fv->flags() & DDCA_WRITABLE) {
            // printf("   returning editable\n");
            result = Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
        }
    }
    else {
        // printf("   returning NOT editable\n");
    }
    return result;
}

#ifdef ALT
QT::ItemFlags FeatureTableModel::flags (const QModelIndex &index) const
{
    printf("(FeatureTableModel::flags)\n");
    if ( index.column() == 4 )
        return AbstractItemModel::flags(index) | Qt::ItemIsEditable;
    else
        return AbstractItemModel::flags(index);
}
#endif



#ifdef UNNEEDED
bool FeatureTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
}

bool FeatureTableModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    beginInsertColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endInsertColumns();
}

bool FeatureTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
}

bool FeatureTableModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    beginRemoveColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endRemoveColumns();
}
#endif


void  FeatureTableModel::startInitialLoad(void) {
    // TODO replace with signal
    beginResetModel();
}

void  FeatureTableModel::endInitialLoad(void) {
    // TODO: replace with signal
    endResetModel();
}

