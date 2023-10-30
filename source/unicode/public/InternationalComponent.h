#ifndef INTERNATIONALCOMPONENT_H
#define INTERNATIONALCOMPONENT_H

#include <QObject>
#include <unicode/unistr.h>
#include <unicode/translit.h>
#include <Config.h>
#include <iostream>

using namespace icu_73;
using namespace std;

class InternationalComponent : public QObject
{
    Q_OBJECT
public:
    explicit InternationalComponent(QObject *parent = nullptr);
    ~InternationalComponent();

private:
    // Cria uma função para traduzir uma string de um idioma para outro
inline string translate(const std::string& input, const std::string& from, const std::string& to) 
{
  // Converte a string de entrada para um objeto UnicodeString do ICU
  UnicodeString uinput = UnicodeString::fromUTF8(input);

  // Cria um objeto Transliterator do ICU com os idiomas de origem e destino
  UErrorCode status = U_ZERO_ERROR;
  std::string id = from + "-" + to;
  Transliterator* transliterator = Transliterator::createInstance(id.c_str(), UTRANS_FORWARD, status);

  // Verifica se o transliterador foi criado com sucesso
  if (U_FAILURE(status)) {
    // Retorna uma string vazia em caso de erro
    return "";
  }

  // Aplica o transliterador na string de entrada
  transliterator->transliterate(uinput);

  // Converte o objeto UnicodeString do ICU para uma string padrão
  std::string output;
  uinput.toUTF8String(output);

  // Libera a memória do transliterador
  delete transliterator;

  // Retorna a string traduzida
  return output;
}

public:
    
};


#endif // INTERNATIONALCOMPONENT
