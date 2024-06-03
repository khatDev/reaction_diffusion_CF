/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	grid(gfx.ScreenWidth, gfx.ScreenHeight, cellSize)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	float dt = fTimer.Mark();

	if (wnd.kbd.KeyIsPressed('R') && debounce >= debounceTime) //Resets the grid
	{
		debounce = 0;
		grid.Reset();
	}
	if (wnd.kbd.KeyIsPressed(VK_SPACE) && debounce >= debounceTime) //Resets the grid
	{
		debounce = 0;
		pause = !pause;
	}
	if (wnd.kbd.KeyIsPressed('1') && debounce >= debounceTime) //Increases brush size
	{
		debounce = 0;
		radius++;
	}	
	if (wnd.kbd.KeyIsPressed('2') && debounce >= debounceTime) //Decreases brush size
	{
		debounce = 0;
		radius--;
		if (radius <= 0)
		{
			radius = 1;
		}
	}
	if (wnd.mouse.LeftIsPressed()) //Left click paints using black, aka Adds
	{
		grid.Paint(wnd.mouse.GetPosX(), wnd.mouse.GetPosY(), radius);
	}
	if (wnd.mouse.RightIsPressed()) //Right click paints using white, aka Subtracts
	{
		grid.Paint(wnd.mouse.GetPosX(), wnd.mouse.GetPosY(), radius, false);
	}

	if (!pause)
	{
		//for (int i = 0; i < 3; i++)
		//{
		//	
		//}
		grid.Update();
	}

	debounce += dt;
}

void Game::ComposeFrame()
{
	grid.Draw(gfx);
}
