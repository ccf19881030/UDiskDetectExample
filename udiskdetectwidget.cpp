#include "udiskdetectwidget.h"
#include <QApplication>

UDiskDetectWidget::UDiskDetectWidget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle(tr("USB Plug Demo"));

    //setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);//无边框
    this->setStyleSheet(QString("background-color: rgb(0, 255, 0);"));

    // 设置Label的大小和位置
    m_pUSBInfoLabel = new QLabel(this);
    m_pUSBInfoLabel->setGeometry(200, 300, 200, 200);

    m_uDisk = new uDisk(this);
    // 安装事件过滤器
    qApp->installNativeEventFilter(m_uDisk);
//    connect(m_uDisk, &uDisk::sigUDiskCome, [this](QString uDiskName) {
//        QString strMessage = QString("USB Disk Come! The Disk is: %1").arg(uDiskName);
//        this->m_pUSBInfoLabel->setText(strMessage);
//    });
//    connect(m_uDisk, &uDisk::sigUDiskRemove, [this](){
//        this->m_pUSBInfoLabel->setText(tr("USB Disk Remove"));
//    });
    // 关联U盘插拔的信号和槽函数
    connect(m_uDisk, &uDisk::sigUDiskCome, this, &UDiskDetectWidget::uDiskCome_slot);
    connect(m_uDisk, &uDisk::sigUDiskRemove, this, &UDiskDetectWidget::uDiskRemove_slot);
}

UDiskDetectWidget::~UDiskDetectWidget()
{
    if (m_uDisk)
    {
        delete m_uDisk;
        m_uDisk = Q_NULLPTR;
    }
}

void UDiskDetectWidget::uDiskCome_slot(QString uDiskName)
{
    QString strMsg = QString("USB Disk Come! The Disk is: %1").arg(uDiskName);
    m_pUSBInfoLabel->setText(strMsg);
}

void UDiskDetectWidget::uDiskRemove_slot()
{
    m_pUSBInfoLabel->setText(tr("USB Disk Remove"));
}
