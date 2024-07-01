#include <iostream>
//#include <RenderInterface.h>
#include <HTTP/HttpClient.h>

using namespace Nanometro;

int main(int argc, char* argv[])
{
    /*
    Nanometro::RenderInterface RHI(OPENGL_INIT_460);
    size_t size = sizeof(RHI);
    int code = RHI.exec();
    std::cout << size << "\n";
    if (!code)
        std::cout << RHI.GetErrorLog() << "\n";
    */

    //WebsocketClient client;
    //client.Connect("localhost", "3000");
    HttpClient client;
    client.setHost("localhost", "3000");
    client.processRequest();
    
    
    
    std::string input;
    std::cout << "Digite algo: ";
    while (std::getline(std::cin, input)) {
        if (input == "quit")
        {
            break;
        }
    }
    
    return 0;
}
