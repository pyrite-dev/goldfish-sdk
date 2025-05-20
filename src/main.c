#include "sdk.h"

int	  scene;
ui_area_t opengl_area;

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
#else
int main(int argc, char** argv) {
#endif
	sdk_ui_init();
	sdk_ui_loop();
}
