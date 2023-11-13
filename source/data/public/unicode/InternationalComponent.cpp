#include "InternationalComponent.h"

InternationalComponent::InternationalComponent(uint8_t id)
{
    EngineLocale = id;
}

InternationalComponent::~InternationalComponent()
{

}

void InternationalComponent::SetEngineLocaleID(uint8_t id)
{
    EngineLocale = id;
}

uint8_t InternationalComponent::GetEngineLocaleID()
{
    return EngineLocale;
}

void InternationalComponent::SetBaseAppLocaleID(uint8_t id)
{
    BaseAppLocale = id;
}

uint8_t InternationalComponent::GetBaseAppLocaleID()
{
    return BaseAppLocale;
}

void InternationalComponent::SetAppLocaleID(uint8_t id)
{
    AppLocale = id;
}

uint8_t InternationalComponent::GetAppLocaleID()
{
    return AppLocale;
}

string InternationalComponent::toLocalStr(string str)
{

    return "";
}

string InternationalComponent::toEngineLocalStr(string str)
{
    return "";
}


