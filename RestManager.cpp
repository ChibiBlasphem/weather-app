#include "RestManager.h"
#include "AbstractResource.h"
#include <QtNetwork/qnetworkrequestfactory.h>
#include <QtNetwork/qrestaccessmanager.h>
#include <QtQml/qqmllist.h>
#include <memory>
#include <utility>

RestManager::RestManager(QObject *parent) : QObject(parent) {
    m_networkAccessManager.setAutoDeleteReplies(true);
    m_manager = std::make_shared<QRestAccessManager>(&m_networkAccessManager);
    m_api = std::make_shared<QNetworkRequestFactory>();
}

QQmlListProperty<AbstractResource> RestManager::resources() {
    return {this, &m_resources};
}

void RestManager::classBegin() {}

void RestManager::componentComplete() {
    m_api->setBaseUrl(m_url);
    for (const auto resource : std::as_const(m_resources)) {
        resource->setManager(m_manager);
        resource->setApi(m_api);
    }
}
