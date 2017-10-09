#include "stringsmodel.h"

StringsModel::StringsModel(const QStringList &i_strings)
    : m_strings(i_strings)
{

}

int StringsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_strings.size();
}

QVariant StringsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    return m_strings.at(index.row());
}

bool StringsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    if (role != Qt::EditRole)
        return false;

    m_strings.replace(index.row(), value.toString());
    emit dataChanged(index, index, QVector<int>{Qt::EditRole});
    return true;
}

Qt::ItemFlags StringsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return QAbstractItemModel::flags(index);

    return QAbstractItemModel::flags(index) | Qt::ItemFlag::ItemIsEditable;
}

bool StringsModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);

    m_strings.insert(row, "");

    endInsertRows();

    return true;
}
