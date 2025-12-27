#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <SDL2/SDL.h>

/*The .ppm files need to have the following header format:
P3/P6
# Comment line (ignored)
width height
maxValue (ignored and assumed 255)
The pixel data follows the header...
  - For P3: ASCII values for R G B for each pixel
  - For P6: Binary values for R G B for each pixel
*/

int main(){
	const int MAX_VECTOR_SIZE = 1000;

	FILE* in=stdin;

	char* pformat=calloc(MAX_VECTOR_SIZE,sizeof(char));
	//Read first line (format - P3/P6)
	fgets(pformat,1000,in);
	
	char* pcomment=calloc(MAX_VECTOR_SIZE,sizeof(char));
	//Read second line (comment - ignore)
	fgets(pcomment,1000,in);
	free(pcomment);
	
	char* pdimensions=calloc(MAX_VECTOR_SIZE,sizeof(char));
	//Read dimensions
	fgets(pdimensions,1000,in);

	int width=-1;
	int height=-1;
	sscanf(pdimensions,"%d %d\n",&width,&height);
	free(pdimensions);

	char* pmax=calloc(MAX_VECTOR_SIZE,sizeof(char));
	//Read fourth line (maxValue) - ignore it
	fgets(pmax,MAX_VECTOR_SIZE,in);
	free(pmax);
	
	printf("Width: %d , Height: %d\n",width,height);

	SDL_Window* pwindow=SDL_CreateWindow("Image Viewer",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,0);
	
	SDL_Surface* psurface=SDL_GetWindowSurface(pwindow);
	
	SDL_Rect pixel=(SDL_Rect){0,0,1,1};
	Uint32 color=0;

	void removeStringSpaces(char* dest, const char* src) {
		int j = 0;
		for (int i = 0; src[i] != '\0'; i++) {
			if (!isspace((unsigned char)src[i]))
				dest[j++] = src[i];
		}
		dest[j] = '\0';
	}

	char* cleanedFormat = calloc(MAX_VECTOR_SIZE, sizeof(char));
	removeStringSpaces(cleanedFormat, pformat);
	free(pformat);

	if (strcmp(cleanedFormat,"P6") == 0) {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {

				Uint8 r, g, b;
				r = (char)getchar();
				g = (char)getchar();
				b = (char)getchar();
				color = SDL_MapRGB(psurface->format, r, g, b);
				pixel.x = x;
				pixel.y = y;
				SDL_FillRect(psurface, &pixel, color);
			}
		}
	}
	else if (strcmp(cleanedFormat, "P3") == 0) {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				int r, g, b;
				fscanf(in, "%d %d %d", &r, &g, &b);
				color = SDL_MapRGB(psurface->format, r, g, b);
				pixel.x = x;
				pixel.y = y;
				SDL_FillRect(psurface, &pixel, color);
			}
		}
	}
	else {
		printf("Unsupported format: %s\n", cleanedFormat);
		return -1;
	}
	
	SDL_UpdateWindowSurface(pwindow);
	int app_running=1;
	while(app_running){
	  SDL_Event event;
	  while(SDL_PollEvent(&event)){
	  	if(event.type==SDL_QUIT){
			app_running=0;
		}
	  }
	  SDL_Delay(100);
	}
	
}

