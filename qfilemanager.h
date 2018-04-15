#ifndef QFILEMANAGER_H
#define QFILEMANAGER_H

#include <vector>
#include <iostream>
#include <QString>
#include <QObject>

#include <QDial>
#include <QDir>
#include <QDebug>
#include <QFileInfo>

class QFileManager
{
public:
    QFileManager();
    virtual ~QFileManager();

public:
    void ReverseDir(QString strPath);

private:
    std::vector<QString> m_arrFilePath;
};

#if 0
void ReverseDir(QString strPath)
{
    QDir dir(strPath);
    foreach(QFileInfo mfi ,dir.entryInfoList())
    {
      if(mfi.isFile())
      {
          qDebug()<< "File :" << mfi.fileName();
          //m_arrFilePath.push_back(mfi.fileName());
      }
      else
      {
          if(mfi.fileName()=="." || mfi.fileName() == "..")
              continue;
          qDebug() << "Entry Dir" << mfi.absoluteFilePath();
          ReverseDir(mfi.absoluteFilePath());
      }
    }
}
#endif
#endif // QFILEMANAGER_H
