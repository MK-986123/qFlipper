#ifndef FLIPPER_ZEROREMOTE_H
#define FLIPPER_ZEROREMOTE_H

#include <QObject>
#include <QByteArray>

class QSerialPort;

namespace Flipper {

class ZeroRemote : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QByteArray screenData READ screenData NOTIFY screenDataChanged)
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(int screenWidth READ screenWidth CONSTANT)
    Q_PROPERTY(int screenHeight READ screenHeight CONSTANT)

public:
    ZeroRemote(QSerialPort *port, QObject *parent = nullptr);
    ~ZeroRemote();

    const QByteArray &screenData() const;

    bool isEnabled() const;
    void setEnabled(bool enabled);

    static int screenWidth();
    static int screenHeight();

signals:
    void screenDataChanged();
    void enabledChanged();

private slots:
    void onPortReadyRead();
    void onPortErrorOccured();

private:
    bool openPort();
    void closePort();

    QSerialPort *m_port;
    QByteArray m_dataBuffer;
    QByteArray m_screenData;

    bool m_isEnabled;
    bool m_isHeaderFound;
};

} // namespace Flipper

#endif // FLIPPER_ZEROREMOTE_H
