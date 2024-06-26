#pragma once

#include "AbstractResource.h"
#include "Param.h"
#include <QtCore/qjsonarray.h>
#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/qlogging.h>
#include <QtCore/qobject.h>
#include <QtCore/qobjectdefs.h>
#include <QtCore/qtmetamacros.h>
#include <QtNetwork/qrestreply.h>
#include <QtQml/qqmllist.h>
#include <qqmlintegration.h>
#include <utility>

class ResourceWithParams : public AbstractResource, public QQmlParserStatus {
    Q_OBJECT
    Q_PROPERTY(QJsonObject data READ data NOTIFY dataChanged)
    Q_PROPERTY(QList<QJsonObject> forecast READ forecast NOTIFY forecastChanged)
    Q_PROPERTY(QQmlListProperty<Param> params READ params)
    Q_PROPERTY(QString path MEMBER m_path REQUIRED)
    Q_CLASSINFO("DefaultProperty", "params")
    Q_INTERFACES(QQmlParserStatus)
    QML_ELEMENT

  public:
    explicit ResourceWithParams(QObject *parent = nullptr)
        : AbstractResource(parent) {}
    ~ResourceWithParams() override = default;
    QJsonObject data() const { return m_data; }
    QList<QJsonObject> forecast() const { return m_forecast; }
    QQmlListProperty<Param> params() { return {this, &m_params}; }
    void classBegin() override {}
    void componentComplete() override {
        for (const auto param : std::as_const(m_params)) {
            QObject::connect(param, SIGNAL(valueChanged()), this,
                             SLOT(onParamChanged()));
        }
    }
    Q_INVOKABLE void refreshData() {
        // TODO: Make the query
        QUrlQuery query{{"key", QString{"b36de820f0ff4e5b84d165913242206"}}};
        for (const auto param : std::as_const(m_params)) {
            query.addQueryItem(param->name(), param->value());
        }
        m_manager->get(m_api->createRequest(m_path, query), this,
                       [this](QRestReply &reply) {
                           if (const auto json = reply.readJson()) {
                               refreshRequestCompleted(*json);
                           } else {
                               // I don't how to manage the error for the
                               // moment
                           }
                       });
    }

  signals:
    void dataChanged();
    void forecastChanged();

  public slots:
    void onParamChanged() { refreshData(); }

  private:
    void refreshRequestCompleted(const QJsonDocument &json) {
        m_data = json.object();

        m_forecast.clear();
        QJsonArray json_forecastday = json["forecast"]["forecastday"].toArray();
        for (const auto &entry : json_forecastday) {
            m_forecast.append(entry.toObject());
        }

        emit dataChanged();
        emit forecastChanged();
    }
    QJsonObject m_data;
    QList<QJsonObject> m_forecast;
    QList<Param *> m_params;
    QString m_path;
};
