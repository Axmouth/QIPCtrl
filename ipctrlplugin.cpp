#include "ipctrl.h"
#include "ipctrlplugin.h"

#include <QtPlugin>

IPCtrlPlugin::IPCtrlPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void IPCtrlPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool IPCtrlPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *IPCtrlPlugin::createWidget(QWidget *parent)
{
    return new IPCtrl(parent);
}

QString IPCtrlPlugin::name() const
{
    return QLatin1String("IPCtrl");
}

QString IPCtrlPlugin::group() const
{
    return QLatin1String("");
}

QIcon IPCtrlPlugin::icon() const
{
    return QIcon();
}

QString IPCtrlPlugin::toolTip() const
{
    return QLatin1String("");
}

QString IPCtrlPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool IPCtrlPlugin::isContainer() const
{
    return false;
}

QString IPCtrlPlugin::domXml() const
{
    return QLatin1String("<widget class=\"IPCtrl\" name=\"iPCtrl\">\n</widget>\n");
}

QString IPCtrlPlugin::includeFile() const
{
    return QLatin1String("ipctrl.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(ipctrlplugin, IPCtrlPlugin)
#endif // QT_VERSION < 0x050000
