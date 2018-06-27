#include <iostream>
#include "include.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
//������ �� â
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;
SDL_Texture *texture;
TTF_Font * Font_Size[100];
TTF_Font * Font_Size2[100];
int TTF_DrawText(SDL_Renderer *Renderer, TTF_Font* Font, char* sentence, int x, int y, SDL_Color Color) {
	cout << "����";
	SDL_Surface * Surface = TTF_RenderText_Blended(Font, sentence, Color);// ��Ʈ�� ����,���ڿ�, ������ ������ �����ڵ�� �����Ѵ��� ���ǽ��� �����Ѵ�
	SDL_Texture* Texture = SDL_CreateTextureFromSurface(Renderer, Surface);// ���ǽ��κ��� �ؽ��ĸ� �����Ѵ�
	SDL_FreeSurface(Surface);//���ǽ� �޸𸮸� ���� ���ش�.
	SDL_Rect Src;
	Src.x = 0;
	Src.y = 0;
	SDL_QueryTexture(Texture, NULL, NULL, &Src.w, &Src.h);
	SDL_Rect Dst;
	Dst.x = x;
	Dst.y = y;
	Dst.w = Src.w;
	Dst.h = Src.h;
	SDL_RenderCopy(Renderer, Texture, &Src, &Dst); //�״�� �������� �����Ѵ�
	SDL_DestroyTexture(Texture);
	return Src.w;// ����� ���ڿ��� �ʺ� ��ȯ
}
int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Rect texture_rect;
	texture_rect.x = 0;  //the x coordinate
	texture_rect.y = 0; // the y coordinate
	texture_rect.w = 800; //the width of the texture
	texture_rect.h = 600; //the height of the texture
	TTF_Init();
	TTF_Font* font = TTF_OpenFont(".\\font\\NanumGothic.ttf", 35);
	SDL_Color color = { 0,0,0,0 };
	window = SDL_CreateWindow("1", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	texture = IMG_LoadTexture(renderer, ".\\white.png");
	SDL_RenderCopy(renderer, texture, NULL, &texture_rect);
	TTF_DrawText(renderer, font, "capture", 400,300, color);
	VideoCapture capture(0);
	if (!capture.isOpened())
	{
		cout << "ī�޶� ������� ����" << endl;
		exit(1);
	}
	double fps = 29.97;
	int delay = cvRound(1000.0 / fps);
	Size size(640, 360);
	int fourcc = VideoWriter::fourcc('D', 'X', '5', '0');
	capture.set(CAP_PROP_FRAME_WIDTH, size.width);
	capture.set(CAP_PROP_FRAME_HEIGHT, size.height);

	bool quit = false;
	while (!quit)
	{
		Mat frame;
		capture >> frame;
		if (SDL_WaitEventTimeout(&event, 1))
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					int x, y;
					x = event.button.x;
					y = event.button.y;
					SDL_RenderPresent(renderer);
					imwrite("caputred.jpg", frame);

				}
			}


		SDL_RenderPresent(renderer);

	}
	return 0;
}
