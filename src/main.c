#include "sdk.h"

int	  scene;
ui_area_t opengl_area;

int main(int argc, char** argv) {
	sdk_ui_init();
	sdk_ui_loop();
}
