#include "MyForm.h"
#include "PauseMenu.h"

using namespace FruitNinja;

[STAThreadAttribute]
int main(array <String^>^ args) {
	Drawing::Size resolution = SystemInformation::PrimaryMonitorSize;
	int screenSizeX = resolution.Width;
	int screenSizeY = resolution.Height;
	PauseMenu^ startMenu = gcnew PauseMenu("Фрукт0вый ниндзя", "Новая игра");
	startMenu->Location = Point(screenSizeX / 2 - 91, screenSizeY / 2 - 115);
	if (startMenu->ShowDialog() != Windows::Forms::DialogResult::Abort)
		Application::Run(gcnew MyForm(screenSizeX, screenSizeY));
	return 0;
}