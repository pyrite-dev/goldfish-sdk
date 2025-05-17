#ifndef __SDK_H__
#define __SDK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <GL/gl.h>

enum SDK_UI_SCENE {
	SDK_UI_INIT = 0,
	SDK_UI_PROJECT
};

typedef struct ui_area_ {
	int x;
	int y;
	int w;
	int h;
} ui_area_t;

/* decl in main.c */
extern int	 scene;
extern ui_area_t opengl_area;

/* decl in opengl.c */
extern GLuint cube;
extern GLuint logo;

void sdk_opengl_render(void);

void sdk_ui_init(void);
void sdk_ui_loop(void);

#ifdef __cplusplus
}
#endif

#endif
