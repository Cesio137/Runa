#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include "glad/glad.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QObject *parent = nullptr);

signals:

};

#endif // ENGINE_H
