#pragma once

#include <QtCore/qobject.h>
#include <QtCore/qtmetamacros.h>
#include <qqmlintegration.h>

class Param : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString name MEMBER m_name REQUIRED)
    Q_PROPERTY(
        QString value READ value WRITE setValue NOTIFY valueChanged REQUIRED)
    QML_ELEMENT

  public:
    explicit Param(QObject *parent = nullptr) : QObject(parent) {}
    ~Param() override = default;
    QString name() const { return m_name; }
    QString value() const { return m_value; }
    void setValue(QString value) {
        m_value = value;
        emit valueChanged();
    }

  signals:
    void valueChanged();

  private:
    QString m_name;
    QString m_value;
};
