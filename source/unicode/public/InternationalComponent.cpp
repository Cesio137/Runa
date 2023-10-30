#include "InternationalComponent.h"

InternationalComponent::InternationalComponent(QObject* parent)
    : QObject{parent}
{
#ifdef ENGINE_BUILD_DEBUG
    
#endif
    // Define as strings de entrada e os idiomas de origem e destino
  std::string input = "Olá, mundo!";
  std::string from = "pt";
  std::string to = "en";

  // Chama a função de tradução e imprime o resultado
  std::string output = translate(input, from, to);
  std::cout << output << std::endl;

  // Saída esperada: Hello, world!
}

InternationalComponent::~InternationalComponent()
{
}
