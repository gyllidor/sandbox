#ifndef STRINGLISTMODEL_H
#define STRINGLISTMODEL_H

#include <QAbstractListModel>

class StringListModel : public QAbstractListModel
{
public:
    StringListModel(const QStringList& strings, QObject* parent);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    bool insertRows(int row, int count, const QModelIndex &parent) override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;


private:
    QStringList m_strings;
};

#endif // STRINGLISTMODEL_H
