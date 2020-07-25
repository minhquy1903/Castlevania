#pragma once

#include "GameObject.h"

/*
	Object that triggers scene switching
*/
class CPortal : public CGameObject
{
public:
	int scene_id;	// target scene to switch to 
	int width;
	int height;
	int xNextPortal;
	int yNextPortal;
	int xCam;
public:
	CPortal(float x, float y, float width, float height, int scene_id, int xNextPortal, int yNextPortal, int xCam);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	int GetSceneID() { return scene_id; }
	int GetXNextPortal() { return xNextPortal; }
	int GetYNextPortal() { return yNextPortal; }
};