#pragma once

#include "AbstractResource.h"
#include <QtCore/qlist.h>
#include <QtCore/qobject.h>
#include <QtCore/qtmetamacros.h>
#include <QtNetwork>
#include <QtQml/qqml.h>
#include <QtQml/qqmllist.h>
#include <QtQml/qqmlparserstatus.h>

class RestManager : public QObject, public QQmlParserStatus {
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<AbstractResource> resources READ resources)
    Q_PROPERTY(QUrl url MEMBER m_url)
    Q_CLASSINFO("DefaultProperty", "resources")
    Q_INTERFACES(QQmlParserStatus)
    QML_ELEMENT

  public:
    explicit RestManager(QObject *parent = nullptr);
    ~RestManager() override = default;

    void classBegin() override;
    void componentComplete() override;

    QQmlListProperty<AbstractResource> resources();

  private:
    QList<AbstractResource *> m_resources;
    QNetworkAccessManager m_networkAccessManager;
    std::shared_ptr<QRestAccessManager> m_manager;
    std::shared_ptr<QNetworkRequestFactory> m_api;
    QUrl m_url;
};
