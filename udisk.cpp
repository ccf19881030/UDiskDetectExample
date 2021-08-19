#include "udisk.h"
#include <QApplication>
#include <QDebug>

uDisk::uDisk(QWidget *parent)
    : QWidget(parent)
{
}

uDisk::~uDisk()
{
}

// 在QWidget中重新实现它的nativeEvent函数来接收处理WM_DEVICECHANGE消息
bool uDisk::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
    MSG* msg = reinterpret_cast<MSG*>(message);
    int msgType = msg->message;
    if (msgType == WM_DEVICECHANGE)
    {
        PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)msg->lParam;
        switch (msg->wParam)
        {
        case DBT_DEVICEARRIVAL:
            if (lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME)
            {
                PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
                if (lpdbv->dbcv_flags == 0)
                {
                    QString strUSBDisk = QString(this->FirstDriveFromUDisk(lpdbv->dbcv_unitmask));
                    emit sigUDiskCome(strUSBDisk);
                }
            }
            break;
        case DBT_DEVICEREMOVECOMPLETE:
            if (lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME)
            {
                PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
                if (lpdbv->dbcv_flags == 0)
                {
                    emit sigUDiskRemove();
                }
            }
             break;
        case DBT_DEVNODES_CHANGED:
            break;
        default:
            break;
        }
    }
    return QWidget::nativeEvent(eventType, message, result);
}

char uDisk::FirstDriveFromUDisk(ULONG unitmask)
{
    char i;
    for (i = 0; i < 26; i++)
    {
        if (unitmask & 0x01)
        {
            break;
        }
        unitmask = unitmask >> 1;
    }
    return (i + 'A');
}

