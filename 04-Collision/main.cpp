/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	SAMPLE 04 - COLLISION

	This sample illustrates how to:

		1/ Implement SweptAABB algorithm between moving objects
		2/ Implement a simple (yet effective) collision frame work

	Key functions: 
		CGame::SweptAABB
		CGameObject::SweptAABBEx
		CGameObject::CalcPotentialCollisions
		CGameObject::FilterCollision

		CGameObject::GetBoundingBox
		
================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Whip.h"
#include "Simon.h"
#include "Ground.h"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define MAX_FRAME_RATE 120

#define ID_TEX_SIMON 0
#define ID_TEX_ENEMY 10
#define ID_TEX_GROUND 20
#define ID_TEX_WHIP  30
CGame *game;

CSimon *simon;
Whip * whip;
vector<LPGAMEOBJECT> objects;

class CSampleKeyHander: public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler; 

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_SPACE:
		simon->Jump(); 
		break;
	case DIK_A: // reset
		simon->Hit();
		break;
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHander::KeyState(BYTE *states)
{
	if(simon->isHitting && (!simon->animations[SIMON_STAND_HIT]->RenderOver(400) || !simon->animations[SIMON_SIT_HIT]->RenderOver(400)))
		return;
	if (simon->isHitting && (simon->animations[SIMON_STAND_HIT]->RenderOver(400) || simon->animations[SIMON_SIT_HIT]->RenderOver(400)))
		simon->isHitting = false;
	
	if (game->IsKeyDown(DIK_DOWN))
	{
		simon->SetState(SIMON_SIT);
		if (game->IsKeyDown(DIK_RIGHT))
			simon->SetNx(1);
		else if (game->IsKeyDown(DIK_LEFT))
			simon->SetNx(-1);
	}
	else if (game->IsKeyDown(DIK_RIGHT))
	{
		simon->WalkRight();
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		simon->WalkLeft();
	}
	
	else
	{
		if(simon->isGrounded && !simon->isHitting)
			simon->SetState(SIMON_IDLE);
	}
		
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources 
	In this example: load textures, sprites, animations and mario object

	TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/
void LoadResources()
{
	CTextures * textures = CTextures::GetInstance();

	textures->Add(ID_TEX_SIMON, L"textures\\simon.png",D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_GROUND, L"textures\\ground.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_WHIP, L"textures\\whip.png", D3DCOLOR_XRGB(255, 0, 255));


	//textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));


	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	
	LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_TEX_SIMON);

	LPDIRECT3DTEXTURE9 texTexWhip = textures->Get(ID_TEX_WHIP);
	// big
	



	LPDIRECT3DTEXTURE9 texGround = textures->Get(ID_TEX_GROUND);

	sprites->Add(GROUND_ID, 0, 0, 64, 32, texGround);


	
	

	LPANIMATION ani;
	//WHIP
	sprites->Add(100, 0, 0, 240, 66, texTexWhip);
	sprites->Add(101, 240, 0, 480, 66, texTexWhip);
	sprites->Add(102, 480, 0, 720, 66, texTexWhip);

	ani = new CAnimation(100);
	ani->Add(100);
	ani->Add(101);
	ani->Add(102);
	
	animations->Add(200, ani);
	whip = new Whip();
	whip->AddAnimation(200);
	//whip


	ani = new CAnimation(100);		// ground
	ani->Add(GROUND_ID);
	animations->Add(GROUND_ANI, ani);
#pragma region Simon
	//sprite
	sprites->Add(SIMON_SPRITE_IDLE, 0, 0, 60, 64, texSimon);

	sprites->Add(SIMON_SPRITE_WALK1, 60, 0, 120, 64, texSimon);//walk
	sprites->Add(SIMON_SPRITE_WALK2, 120, 0, 180, 64, texSimon);
	sprites->Add(SIMON_SPRITE_WALK3, 180, 0, 240, 64, texSimon);
	
	sprites->Add(SIMON_SPRITE_JUMP, 240,	0,	300,	64, texSimon);//jump

	sprites->Add(SIMON_SPRITE_SIT, 300,	198,	360,	262, texSimon);//sit

	sprites->Add(SIMON_SPRITE_STAND_HIT1, 300, 0, 360, 64, texSimon);//hit stand
	sprites->Add(SIMON_SPRITE_STAND_HIT2, 360, 0, 420, 64, texSimon);
	sprites->Add(SIMON_SPRITE_STAND_HIT3, 420, 0, 480, 64, texSimon);

	sprites->Add(SIMON_SPRITE_SIT_HIT1, 420	,66	,480, 130, texSimon);// hit sit
	sprites->Add(SIMON_SPRITE_SIT_HIT2, 0, 132, 60, 196, texSimon);
	sprites->Add(SIMON_SPRITE_SIT_HIT3, 60,	132, 120, 196, texSimon);
	//sprite
	//ANI
	ani = new CAnimation(80);//IDLE
	ani->Add(SIMON_SPRITE_IDLE);
	animations->Add(SIMON_IDLE, ani);

	ani = new CAnimation(80);//WALK
	ani->Add(SIMON_SPRITE_IDLE);
	ani->Add(SIMON_SPRITE_WALK1);
	ani->Add(SIMON_SPRITE_WALK2);
	ani->Add(SIMON_SPRITE_WALK3);
	animations->Add(SIMON_WALKING, ani);

	ani = new CAnimation(80);//JUMP
	ani->Add(SIMON_SPRITE_JUMP);
	animations->Add(SIMON_JUMP, ani);

	ani = new CAnimation(80);//SIT
	ani->Add(SIMON_SPRITE_SIT);
	animations->Add(SIMON_SIT, ani);

	ani = new CAnimation(100);//stand hit
	ani->Add(SIMON_SPRITE_STAND_HIT1);
	ani->Add(SIMON_SPRITE_STAND_HIT2);	
	ani->Add(SIMON_SPRITE_STAND_HIT3);
	animations->Add(SIMON_STAND_HIT, ani);

	ani = new CAnimation(100);//SIT hit
	ani->Add(SIMON_SPRITE_SIT_HIT1);
	ani->Add(SIMON_SPRITE_SIT_HIT2);
	ani->Add(SIMON_SPRITE_SIT_HIT3);
	animations->Add(SIMON_SIT_HIT, ani);

	simon = new CSimon();
	simon->AddAnimation(SIMON_IDLE);		
	simon->AddAnimation(SIMON_WALKING);		
	simon->AddAnimation(SIMON_JUMP);		
	simon->AddAnimation(SIMON_SIT);
	simon->AddAnimation(SIMON_STAND_HIT);
	simon->AddAnimation(SIMON_SIT_HIT);


	simon->SetPosition(50.0f, 0);
	objects.push_back(simon);
#pragma endregion


	for (int i = 0; i < 30; i++)
	{
		CGround *ground = new CGround();
		ground->AddAnimation(GROUND_ANI);
		ground->SetPosition(0 + i*16.0f, 180);
		objects.push_back(ground);
	}

}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt,&coObjects);
	}


	// Update camera to follow mario
	float cx, cy;
	simon->GetPosition(cx, cy);

	cx -= SCREEN_WIDTH / 2;
	cy -= SCREEN_HEIGHT / 2;

	CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);
}

/*
	Render a frame 
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render();
		
		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();
			
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT*2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}