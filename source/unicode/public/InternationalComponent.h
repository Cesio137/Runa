#ifndef INTERNATIONALCOMPONENT_H
#define INTERNATIONALCOMPONENT_H

#include <QObject>
#include <boost/locale.hpp>
#include <Config.h>
#include <iostream>

using namespace boost::locale;
using namespace std;

class InternationalComponent : public QObject
{
    Q_OBJECT
public:
    explicit InternationalComponent(QObject *parent = nullptr);
    ~InternationalComponent();

private:
    generator gen;

public:
    
};


#endif // INTERNATIONALCOMPONENT
