#include "engine.h"

engine::engine(QObject *parent)
    : QObject{parent}
{
    /*
    QCoreApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Lumen_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    */

    if (!glfwInit())
    {
        CoreShouldClose = true;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(800, 600, "Lumen", NULL, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        CoreShouldClose = true;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, 800, 600);
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    while (!glfwWindowShouldClose(window))
    {
        glfwWaitEvents();
        CoreShouldClose = glfwWindowShouldClose(window);
        //QThread::msleep(33);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
