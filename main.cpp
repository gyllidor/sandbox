#include "mainwindow.h"

#include "stringlistmodel.h"

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

    QSplitter* splitter = new QSplitter;

    auto tree = new QTreeView(splitter);

    QFileSystemModel *model = new QFileSystemModel;
    QModelIndex parentIndex = model->setRootPath(QDir::currentPath());

    tree->setModel(model);
    tree->setRootIndex(model->index(QDir::currentPath()));

    QListView* list = new QListView(splitter);

    QStringList strings;
    strings << "1" << "2" << "3";

    StringListModel* strmodel = new StringListModel(strings, nullptr);
    list->setModel(strmodel);


    splitter->show();

    std::chrono::seconds secs(3);
    QTimer::singleShot(std::chrono::milliseconds(secs).count(), [model, &parentIndex](){
        int numRows = model->rowCount(parentIndex);
        qDebug() << numRows;
        for (int row = 0; row < numRows; ++row) {
            QModelIndex index = model->index(row, 0, parentIndex);
            QString text = model->data(index, Qt::DisplayRole).toString();
            // Display the text in a widget.
            qDebug() << text;
        }
    });


    QTimer::singleShot(std::chrono::milliseconds(secs).count(), [&]()
    {
        strmodel->insertRows(0, 1, QModelIndex());
        auto index = strmodel->index(0);
        strmodel->setData(index, QString("boom"), Qt::EditRole);
    });

    return app.exec();
}
