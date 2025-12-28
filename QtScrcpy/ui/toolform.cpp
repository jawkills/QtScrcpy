#include <QDebug>
#include <QHideEvent>
#include <QMouseEvent>
#include <QShowEvent>
#include <QClipboard>
#include <QApplication>
#include <QRandomGenerator>
#include <QSettings>
#include <QCoreApplication>

#include "iconhelper.h"
#include "toolform.h"
#include "ui_toolform.h"
#include "videoform.h"
#include "../groupcontroller/groupcontroller.h"

ToolForm::ToolForm(QWidget *adsorbWidget, AdsorbPositions adsorbPos) : MagneticWidget(adsorbWidget, adsorbPos), ui(new Ui::ToolForm)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    //setWindowFlags(windowFlags() & ~Qt::WindowMinMaxButtonsHint);

    updateGroupControl();

    initStyle();
    updateToolbarState();
}

ToolForm::~ToolForm()
{
    delete ui;
}

void ToolForm::setSerial(const QString &serial)
{
    m_serial = serial;
}

bool ToolForm::isHost()
{
    return m_isHost;
}

void ToolForm::initStyle()
{
    IconHelper::Instance()->SetIcon(ui->toggleExpandBtn, QChar(0xf078), 15); // chevron-down
    IconHelper::Instance()->SetIcon(ui->menuBtn, QChar(0xf096), 15);
    IconHelper::Instance()->SetIcon(ui->homeBtn, QChar(0xf1db), 15);
    //IconHelper::Instance()->SetIcon(ui->returnBtn, QChar(0xf104), 15);
    IconHelper::Instance()->SetIcon(ui->returnBtn, QChar(0xf053), 15);
    IconHelper::Instance()->SetIcon(ui->appSwitchBtn, QChar(0xf24d), 15);
    IconHelper::Instance()->SetIcon(ui->volumeUpBtn, QChar(0xf028), 15);
    IconHelper::Instance()->SetIcon(ui->volumeDownBtn, QChar(0xf027), 15);
    IconHelper::Instance()->SetIcon(ui->openScreenBtn, QChar(0xf06e), 15);
    IconHelper::Instance()->SetIcon(ui->closeScreenBtn, QChar(0xf070), 15);
    IconHelper::Instance()->SetIcon(ui->powerBtn, QChar(0xf011), 15);
    IconHelper::Instance()->SetIcon(ui->expandNotifyBtn, QChar(0xf103), 15);
    IconHelper::Instance()->SetIcon(ui->screenShotBtn, QChar(0xf0c4), 15);
    IconHelper::Instance()->SetIcon(ui->groupControlBtn, QChar(0xf0c0), 15);
    IconHelper::Instance()->SetIcon(ui->randomDataBtn, QChar(0xf2c2), 15); // address-card icon
    IconHelper::Instance()->SetIcon(ui->clipboardBtn, QChar(0xf0ea), 15); // clipboard icon
}

void ToolForm::updateGroupControl()
{
    if (m_isHost) {
        ui->groupControlBtn->setStyleSheet("color: red");
    } else {
        ui->groupControlBtn->setStyleSheet("color: green");
    }

    GroupController::instance().updateDeviceState(m_serial);
}

void ToolForm::updateToolbarState()
{
    // Update toggle button icon
    if (m_isExpanded) {
        IconHelper::Instance()->SetIcon(ui->toggleExpandBtn, QChar(0xf077), 15); // chevron-up
    } else {
        IconHelper::Instance()->SetIcon(ui->toggleExpandBtn, QChar(0xf078), 15); // chevron-down
    }

    // Tombol yang disembunyikan saat minimized
    ui->openScreenBtn->setVisible(m_isExpanded);
    ui->closeScreenBtn->setVisible(m_isExpanded);
    ui->volumeUpBtn->setVisible(m_isExpanded);
    ui->volumeDownBtn->setVisible(m_isExpanded);
    ui->appSwitchBtn->setVisible(m_isExpanded);
    ui->menuBtn->setVisible(m_isExpanded);
    ui->screenShotBtn->setVisible(m_isExpanded);

    // Resize window to fit content
    adjustSize();
}

void ToolForm::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
        m_dragPosition = event->globalPos() - frameGeometry().topLeft();
#else
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
#endif
        event->accept();
    }
}

void ToolForm::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
}

void ToolForm::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
        move(event->globalPos() - m_dragPosition);
#else
        move(event->globalPosition().toPoint() - m_dragPosition);
#endif
        event->accept();
    }
}

void ToolForm::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    qDebug() << "show event";
}

void ToolForm::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event)
    qDebug() << "hide event";
}

void ToolForm::on_returnBtn_clicked()
{
    auto device = qsc::IDeviceManage::getInstance().getDevice(m_serial);
    if (!device) {
        return;
    }
    device->postGoBack();
}

void ToolForm::on_homeBtn_clicked()
{
    auto device = qsc::IDeviceManage::getInstance().getDevice(m_serial);
    if (!device) {
        return;
    }
    device->postGoHome();
}

void ToolForm::on_menuBtn_clicked()
{
    auto device = qsc::IDeviceManage::getInstance().getDevice(m_serial);
    if (!device) {
        return;
    }
    device->postGoMenu();
}

void ToolForm::on_appSwitchBtn_clicked()
{
    auto device = qsc::IDeviceManage::getInstance().getDevice(m_serial);
    if (!device) {
        return;
    }
    device->postAppSwitch();
}

void ToolForm::on_powerBtn_clicked()
{
    auto device = qsc::IDeviceManage::getInstance().getDevice(m_serial);
    if (!device) {
        return;
    }
    device->postPower();
}

void ToolForm::on_screenShotBtn_clicked()
{
    auto device = qsc::IDeviceManage::getInstance().getDevice(m_serial);
    if (!device) {
        return;
    }
    device->screenshot();
}

void ToolForm::on_volumeUpBtn_clicked()
{
    auto device = qsc::IDeviceManage::getInstance().getDevice(m_serial);
    if (!device) {
        return;
    }
    device->postVolumeUp();
}

void ToolForm::on_volumeDownBtn_clicked()
{
    auto device = qsc::IDeviceManage::getInstance().getDevice(m_serial);
    if (!device) {
        return;
    }
    device->postVolumeDown();
}

void ToolForm::on_closeScreenBtn_clicked()
{
    auto device = qsc::IDeviceManage::getInstance().getDevice(m_serial);
    if (!device) {
        return;
    }
    device->setDisplayPower(false);
}

void ToolForm::on_expandNotifyBtn_clicked()
{
    auto device = qsc::IDeviceManage::getInstance().getDevice(m_serial);
    if (!device) {
        return;
    }
    device->expandNotificationPanel();
}

void ToolForm::on_groupControlBtn_clicked()
{
    m_isHost = !m_isHost;
    updateGroupControl();
}

void ToolForm::on_toggleExpandBtn_clicked()
{
    m_isExpanded = !m_isExpanded;
    updateToolbarState();
}

void ToolForm::on_openScreenBtn_clicked()
{
    auto device = qsc::IDeviceManage::getInstance().getDevice(m_serial);
    if (!device) {
        return;
    }
    device->setDisplayPower(true);
}

QString ToolForm::generateRandomIndonesianData()
{
    // Daftar nama depan Indonesia
    QStringList namaDepan = {
        "Adi", "Agus", "Ahmad", "Andi", "Bambang", "Budi", "Cahyo", "Dedi", "Dewi", "Eka",
        "Fajar", "Fitri", "Gunawan", "Hadi", "Indra", "Joko", "Kartika", "Lestari", "Maya", "Nia",
        "Putra", "Putri", "Rahmat", "Rina", "Sari", "Siti", "Sri", "Surya", "Tono", "Wati",
        "Yanto", "Yuni", "Zainal", "Ratna", "Nurul", "Dian", "Hendra", "Irwan", "Kusuma", "Lina"
    };

    // Daftar nama belakang Indonesia
    QStringList namaBelakang = {
        "Pratama", "Saputra", "Wijaya", "Kusuma", "Santoso", "Hidayat", "Permana", "Nugraha",
        "Setiawan", "Wibowo", "Susanto", "Hartono", "Suryadi", "Purnama", "Ramadhan", "Firmansyah",
        "Kurniawan", "Prasetyo", "Utomo", "Wahyudi", "Sugiarto", "Handoko", "Budiman", "Gunawan"
    };

    // Daftar jalan
    QStringList jalan = {
        "Jl. Sudirman", "Jl. Thamrin", "Jl. Gatot Subroto", "Jl. Merdeka", "Jl. Diponegoro",
        "Jl. Ahmad Yani", "Jl. Pahlawan", "Jl. Kartini", "Jl. Imam Bonjol", "Jl. Veteran",
        "Jl. Pemuda", "Jl. Asia Afrika", "Jl. Cendrawasih", "Jl. Mawar", "Jl. Melati",
        "Jl. Kenanga", "Jl. Anggrek", "Jl. Dahlia", "Jl. Flamboyan", "Jl. Bougenville"
    };

    // Daftar kota Indonesia
    QStringList kota = {
        "Jakarta", "Surabaya", "Bandung", "Medan", "Semarang", "Makassar", "Palembang",
        "Tangerang", "Depok", "Bekasi", "Bogor", "Malang", "Yogyakarta", "Solo", "Denpasar",
        "Balikpapan", "Banjarmasin", "Pontianak", "Manado", "Padang", "Pekanbaru", "Batam"
    };

    // Daftar provinsi
    QStringList provinsi = {
        "DKI Jakarta", "Jawa Barat", "Jawa Tengah", "Jawa Timur", "Banten", "DIY Yogyakarta",
        "Sumatera Utara", "Sumatera Barat", "Sumatera Selatan", "Kalimantan Timur", "Kalimantan Selatan",
        "Sulawesi Selatan", "Sulawesi Utara", "Bali", "Riau", "Kepulauan Riau"
    };

    QRandomGenerator *rng = QRandomGenerator::global();

    QString nama = namaDepan[rng->bounded(namaDepan.size())] + " " + namaBelakang[rng->bounded(namaBelakang.size())];
    QString alamat = jalan[rng->bounded(jalan.size())] + " No. " + QString::number(rng->bounded(1, 200));
    QString rt = QString::number(rng->bounded(1, 20));
    QString rw = QString::number(rng->bounded(1, 15));
    QString kotaTerpilih = kota[rng->bounded(kota.size())];
    QString provinsiTerpilih = provinsi[rng->bounded(provinsi.size())];
    QString kodePos = QString::number(rng->bounded(10000, 99999));

    QString result = nama + "\n" + alamat + ", RT " + rt + "/RW " + rw + "\n" + kotaTerpilih + ", " + provinsiTerpilih + " " + kodePos;

    return result;
}

void ToolForm::on_randomDataBtn_clicked()
{
    QString randomData = generateRandomIndonesianData();
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(randomData);
    qDebug() << "Random data copied to clipboard:\n" << randomData;
}

QString ToolForm::getDeviceClipboardNumber()
{
    QString configPath = QCoreApplication::applicationDirPath() + "/config/config.ini";
    QSettings settings(configPath, QSettings::IniFormat);
    settings.beginGroup("clipboard");
    QString number = settings.value(m_serial, "").toString();
    settings.endGroup();
    return number;
}

void ToolForm::on_clipboardBtn_clicked()
{
    QString number = getDeviceClipboardNumber();
    if (number.isEmpty()) {
        qDebug() << "No clipboard number configured for device:" << m_serial;
        return;
    }
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(number);
    qDebug() << "Device number copied to clipboard:" << number << "for device:" << m_serial;
}