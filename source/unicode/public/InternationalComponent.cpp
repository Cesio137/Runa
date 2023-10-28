#include "InternationalComponent.h"

#include <QCoreApplication>

InternationalComponent::InternationalComponent(QObject* parent)
    : QObject{parent}
{
#ifdef ENGINE_BUILD_DEBUG
    
#endif
    // Especificar o caminho e o domínio dos arquivos de dicionário
    gen.add_messages_path(DICTIONARY_PATH);
    gen.add_messages_domain("hello");

    // Gerar uma localização em português
    std::locale loc_pt = gen("pt_BR.UTF-8");

    // Atribuir as localizações aos fluxos de saída
    std::wcout.imbue(loc_pt);

    // Usar a função translate para traduzir os textos
    std::wcout << boost::locale::translate(L"Hello World") << std::endl;
}

InternationalComponent::~InternationalComponent()
{
}
