#ifndef FTEXT_H
#define FTEXT_H

#include <QString>
using namespace std;

class FText
{
public:
    FText() : Text(){}
    FText(const QString& str) : Text(str){}
    FText(const string& str) : Text(QString::fromStdString(str)) {}
    FText(const char* str) : Text(QString(str)) {}

    //Set
    const void append(const QString& str) { Text.append(str); }
    const void appendFromStdString(const string& str) { Text.append(QString::fromStdString(str)); }
    const void appendFromUtf8(const char* str) { Text.append(QString::fromUtf8(str)); }

    //Get
    const QString toCaseFolded() { return Text.toCaseFolded(); }
    const string toStdString() { return Text.toStdString(); }
    const char* c_str()
    {
        // Temp QByteArray
        QByteArray temp_qbytearray(Text.toUtf8());

        // Convert to const char*
        const char* const_char_ptr = temp_qbytearray.constData();

        // Returning pointer with data from QByteArray
        return const_char_ptr;
    }

    //Translation

private:
    QString Text;
};

#endif // FTEXT_H
