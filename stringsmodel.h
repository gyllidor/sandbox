#ifndef STRINGSMODEL_H
#define STRINGSMODEL_H

#include <QVariant>
#include <QAbstractListModel>

class StringsModel : public QAbstractListModel
{
public:
    StringsModel(const QStringList& i_strings);

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool insertRows(int row, int count, const QModelIndex &parent) override;


private:
    QStringList m_strings;
};

#endif // STRINGSMODEL_H
