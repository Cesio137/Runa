#ifndef QCORE_H
#define QCORE_H

#include <QObject>
#include <ProjectManager/qprojectmanager.h>

class QCore : public QObject
{
    Q_OBJECT
public:
    explicit QCore(QObject *parent = nullptr);

private: 
    QProjectManager* ProjectManager;
    
};

#endif // QCORE_H
