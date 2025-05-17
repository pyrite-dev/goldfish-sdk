#include "sdk.h"

#include <GL/glu.h>

#include <stdlib.h>
#include <time.h>

double deg = 0;

GLuint cube;

void sdk_opengl_render(void) {
	double sz = 0.5;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120, (double)opengl_area.w / opengl_area.h, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	if(scene == SDK_UI_INIT) {
		int   i;
		int   s	  = 0;
		float p[] = {1, 1, 1, 1};
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

		gluLookAt(0, 1, 1, 0, 0, 0, 0, 1, 0);
		glLightfv(GL_LIGHT0, GL_POSITION, p);

		glPushMatrix();
		glRotatef(deg, 0.5, 0.75, 1);
		for(i = 0; i < 3; i++) {
			int j;
			for(j = 0; j < 2; j++) {
				glColor3f(1, 1, 1);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, cube);
				glBegin(GL_QUADS);
				glNormal3f(0, 1, 0);

				glTexCoord2f(1.0 / 6 * (s - 1), 0);
				glVertex3f(-sz, sz, sz);

				glTexCoord2f(1.0 / 6 * s, 0);
				glVertex3f(sz, sz, sz);

				glTexCoord2f(1.0 / 6 * s, 1);
				glVertex3f(sz, sz, -sz);

				glTexCoord2f(1.0 / 6 * (s - 1), 1);
				glVertex3f(-sz, sz, -sz);
				glEnd();
				glDisable(GL_TEXTURE_2D);
				glRotatef(180, 1, 0, 0);
				s++;
			}
			if(i == 0) glRotatef(90, 0, 0, 1);
			if(i == 1) glRotatef(90, 1, 0, 0);
		}
		glPopMatrix();
		deg += 180.0 / 60;
		glDisable(GL_LIGHTING);
	}
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
}
