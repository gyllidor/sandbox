#include "mainwindow.h"

#include "stringsmodel.h"

#include <iostream>

#include <QApplication>
#include <QSplitter>
#include <QFileSystemModel>
#include <QTreeView>
#include <QListView>
#include <QDebug>
#include <QTimer>

#include <chrono>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

//    MainWindow w;
//    w.show();

    QSplitter splitter;
    QListView* p_list_view = new QListView(&splitter);

    auto strings = QDir(QDir::currentPath()).entryList(QDir::Filter::Files);
    StringsModel model(strings);
    p_list_view->setModel(&model);

    p_list_view->connect(p_list_view, &QListView::clicked, [&model](const QModelIndex& index)
    {
        model.insertRows(index.row(), 1, index);
        model.setData(model.index(index.row()), "woohoo", Qt::EditRole);
    });

    splitter.show();

    return app.exec();
}
