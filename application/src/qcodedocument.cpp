/****************************************************************************
**
** Copyright (C) 2014 Dinu SV.
** (contact: mail@dinusv.com)
** This file is part of Live CV application.
**
** GNU General Public License Usage
** 
** This file may be used under the terms of the GNU General Public License 
** version 3.0 as published by the Free Software Foundation and appearing 
** in the file LICENSE.GPL included in the packaging of this file.  Please 
** review the following information to ensure the GNU General Public License 
** version 3.0 requirements will be met: http://www.gnu.org/copyleft/gpl.html.
**
****************************************************************************/

#include "qcodedocument.h"
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>

#include <QDebug>
#include <QQmlEngine>

QCodeDocument::QCodeDocument(QQuickItem *parent)
    : QQuickItem(parent)
{
}

QString QCodeDocument::openFile(const QUrl &file){
    QString fileName = file.toLocalFile();
    if ( fileName != "" ){
        QFile file(fileName);
        if ( !file.open(QIODevice::ReadOnly ) ){
            return QString("Could not open file : ") + fileName;
        }
        QTextStream in(&file);
        setFile(fileName);
        setPath(QFileInfo(file).path());
        QString content = in.readAll();
        file.close();
        return content;
    }
    return "";
}

void QCodeDocument::saveFile(const QUrl& file, const QString &content){
    QString fileName = file.toLocalFile();
    if ( fileName != "" ){
        QFile file(fileName);
        if ( !file.open(QIODevice::WriteOnly ) ){
            qDebug() << "Can't open file for writing";
            return;
        } else {
            QTextStream stream(&file);
            stream << content;
            stream.flush();
            file.close();
            setPath(QFileInfo(file).path());
            setFile(fileName);
        }
    }
}

void QCodeDocument::saveFile(const QString& content){
    if ( m_openedFile != "" )
        saveFile(QUrl::fromLocalFile(m_openedFile), content);
}