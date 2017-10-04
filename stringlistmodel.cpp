#include "stringlistmodel.h"

StringListModel::StringListModel(const QStringList &strings, QObject *parent)
    : QAbstractListModel(parent)
    , m_strings(strings)
{

}

int StringListModel::rowCount(const QModelIndex &) const
{
    return m_strings.size();
}

QVariant StringListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    if (index.row() >= m_strings.size())
        return QVariant();

    return m_strings.at(index.row());
}

QVariant StringListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QString("row %1").arg(section);

    return QString("col %1").arg(section);
}

Qt::ItemFlags StringListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool StringListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    if (role != Qt::EditRole)
        return false;

    m_strings.replace(index.row(), value.toString());
    emit dataChanged(index, index, QVector<int>{Qt::EditRole});
    return true;
}

bool StringListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);

    beginInsertRows(QModelIndex(), row, row + count -1);

    for (int i = 0; i < count; ++i)
        m_strings.insert(row, "");

    endInsertRows();
    return true;
}

bool StringListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);

    beginRemoveRows(QModelIndex(), row, row + count - 1);

    for (int i = 0; i < count; ++i)
        m_strings.removeAt(row);

    endRemoveRows();
    return true;
}

