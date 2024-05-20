#include <iostream>
//#include <RenderInterface.h>
#define ASIO_STANDALONE
#include <HTTP/Request.h>

using namespace Nanometro;
using asio::ip::tcp;

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

    Request req;
    req.SetHost("localhost", "3000");
    req.SetRequest(EHttpVerb::GET, "2.0");
    req.SyncConstructRequest();
    //req.OnRequestProgress = [](int BytesSent, int BytesReceived){ std::cout << BytesSent << "\n" << BytesReceived << "\n"; };
    int result = req.SyncProcessRequest();
    std::cout << result;

    return 0;
}
