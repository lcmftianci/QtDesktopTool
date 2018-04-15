#include "qfilemanager.h"
#include <QDial>
#include <QDir>
#include <QDebug>
#include <QFileInfo>

void QFileManager::ReverseDir(QString strPath)
{
    QDir dir(strPath);
    foreach(QFileInfo mfi ,dir.entryInfoList())
    {
      if(mfi.isFile())
      {
          qDebug()<< "File :" << strPath + "/" + mfi.fileName();
          m_arrFilePath.push_back(strPath + "/" + mfi.fileName());
      }else
      {
          if(mfi.fileName()=="." || mfi.fileName() == "..")continue;
          qDebug() << "Entry Dir" << mfi.absoluteFilePath();
          this->ReverseDir(mfi.absoluteFilePath());
      }
    }
}

QFileManager::QFileManager()
{

}

QFileManager::~QFileManager()
{

}
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
      }else
      {
          if(mfi.fileName()=="." || mfi.fileName() == "..")continue;
          qDebug() << "Entry Dir" << mfi.absoluteFilePath();
          ReverseDir(mfi.absoluteFilePath());
      }
    }
}
#endif
