#ifndef UDISKDETECTWIDGET_H
#define UDISKDETECTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include "udisk.h"

class UDiskDetectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UDiskDetectWidget(QWidget *parent = nullptr);
    ~UDiskDetectWidget();

signals:

private slots:
    // U盘插入的槽函数
    void uDiskCome_slot(QString uDiskName);
    // U盘拔出的槽函数
    void uDiskRemove_slot();

private:
    // 显示U盘插拔信息的QLabel标签
    QLabel* m_pUSBInfoLabel = Q_NULLPTR;

    uDisk* m_uDisk = Q_NULLPTR;
};

#endif // UDISKDETECTWIDGET_H
