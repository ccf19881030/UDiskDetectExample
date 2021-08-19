#ifndef UDISK_H
#define UDISK_H

#include <QWidget>
#include <Windows.h>
#include <QAbstractNativeEventFilter>
#include <Dbt.h>

// Qt的QAbstractNativeEventFilter类，虚函数nativeEventFilter。这个类的主要作用是捕获全局windows消息。
class uDisk : public QWidget, public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    uDisk(QWidget *parent = nullptr);
    ~uDisk();

protected:
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) override;

signals:
    // U盘插入信号
    void sigUDiskCome(QString uDiskName);
    // U盘拔出信号
    void sigUDiskRemove();
private:
    char FirstDriveFromUDisk(ULONG unitmask);
};
#endif // UDISK_H
