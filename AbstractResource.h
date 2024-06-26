#pragma once

#include <QtCore/qobject.h>
#include <QtNetwork/qnetworkrequestfactory.h>
#include <QtNetwork/qrestaccessmanager.h>
#include <QtQml/qqml.h>
#include <memory>

class AbstractResource : public QObject {
    Q_OBJECT
    QML_ANONYMOUS

  public:
    explicit AbstractResource(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~AbstractResource() override = default;
    void setManager(std::shared_ptr<QRestAccessManager> manager) {
        m_manager = manager;
    }
    void setApi(std::shared_ptr<QNetworkRequestFactory> api) { m_api = api; }

  protected:
    std::shared_ptr<QRestAccessManager> m_manager;
    std::shared_ptr<QNetworkRequestFactory> m_api;
};
