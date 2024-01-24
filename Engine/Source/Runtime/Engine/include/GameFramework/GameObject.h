#pragma once

namespace Nanometro
{
    class GameObject
    {
    public:
        GameObject();
        ~GameObject();

        virtual void PreInitialize();
        virtual void BeginPlay();
        virtual void Tick(float DeltaTime);

    };
}
