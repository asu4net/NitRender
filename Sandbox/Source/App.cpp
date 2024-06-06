#include "NitRender.h"

using namespace Nit;

int main(int argc, char* argv[])
{
    auto window = Window::Create();

	while (window->IsOpened())
	{
		window->Update();
	}
}