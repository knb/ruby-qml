#include "componentextension.h"
#include "qmlexception.h"
#include <QQmlComponent>
#include <QQmlEngine>
#include <QDebug>

namespace RubyQml {

ComponentExtension::ComponentExtension(QQmlComponent *component) :
    mComponent(component)
{
}

void ComponentExtension::loadString(const QString &data, const QString &path)
{
    mComponent->setData(data.toUtf8(), QUrl::fromLocalFile(path));
    throwIfError();
}

void ComponentExtension::loadFile(const QString &filePath)
{
    mComponent->loadUrl(QUrl::fromLocalFile(filePath));
    throwIfError();
}

QObject *ComponentExtension::create(QQmlContext *context)
{
    auto created = mComponent->create(context);
    throwIfError();
    QQmlEngine::setObjectOwnership(created, QQmlEngine::JavaScriptOwnership);
    return created;
}

void ComponentExtension::throwIfError()
{
    if (mComponent->status() == QQmlComponent::Error) {
        throw QmlException(mComponent->errorString());
    }
}

} // namespace RubyQml
