#include "GO_SS_Fan.h"

void GO_SS_Fan::Initialize(void)
{
	m_FanATex = LoadTexture("data/TEXTURE/”[“¤.png");
	m_FanBTex = LoadTexture("data/TEXTURE/bullet00.png");
	m_WindTex = LoadTexture("data/TEXTURE/fan_wind.png");

	once = true;

	for (int i = 0; i < FANS_MAX; i++)
	{
		m_FanInfo[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		m_FanInfo[i].size = D3DXVECTOR2(0.0f, 0.0f);
		m_FanInfo[i].use = false;
		m_FanInfo[i].isLeft = false;
		m_FanInfo[i].isWork = false;
		m_FanInfo[i].isLink = false;
	}
}

void GO_SS_Fan::Finalize(void)
{

}

void GO_SS_Fan::Update(void)
{
	for (int i = 0; i < FANS_MAX; i++)
	{
		if (FCCollision(m_FanInfo[i].pos, m_FanInfo[i].size, m_pCircle->pos, m_pCircle->size.x / 3))
		{
			m_FanInfo[i].isWork = true;
		}
		else
		{
			m_FanInfo[i].isWork = false;
		}
	}
	
	//DebugOut();
}

void GO_SS_Fan::Draw(void)
{
	for (int i = 0; i < FANS_MAX; i++)
	{
		if (m_FanInfo[i].use)
		{
			//‹z‚¢ž‚ÝŒû•`‰æ
			DrawSpriteLeftTop(m_FanATex, m_FanInfo[i].pos.x, m_FanInfo[i].pos.y,
				m_FanInfo[i].size.x, m_FanInfo[i].size.y, 0.0f, 0.0f, 1.0f, 1.0f);

			//“f‚«o‚µŒûã•`‰æ
			if (!m_FanInfo[i].isLeft)
			{
				DrawSpriteLeftTop(m_FanBTex, m_FanInfo[i].fanB_Pos.x, m_FanInfo[i].fanB_Pos.y,
					m_FanInfo[i].size.x, m_FanInfo[i].size.y, 0.0f, 0.0f, 1.0f, 1.0f);
			}
			//¶
			else
			{
				DrawSpriteColorRotate(m_FanBTex, m_FanInfo[i].fanB_Pos.x + WALL_WIDTH * 0.5f, m_FanInfo[i].fanB_Pos.y + WALL_HEIGHT * 0.5f,
					m_FanInfo[i].size.x, m_FanInfo[i].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LEFT_QUANTITY);
			}
		

			if (m_FanInfo[i].isWork)
			{
				static int cnt = 0;
				static float u, v;

				cnt++;

				u = cnt % WIND_WIDTH_SPLIT * WIND_ADD_U;
				v = cnt / WIND_HEIGHT_SPLIT * WIND_ADD_V;

				//•—•`‰æ
				SetBlendState(BLEND_MODE_ADD);

				if (!m_FanInfo[i].isLeft)
				{
					DrawSpriteLeftTop(m_WindTex, m_FanInfo[i].fanB_Pos.x, m_FanInfo[i].fanB_Pos.y - WALL_HEIGHT,
						m_FanInfo[i].size.x, m_FanInfo[i].size.y, u, v, WIND_ADD_U, WIND_ADD_V);
				}
				else
				{
					DrawSpriteColorRotate(m_WindTex, m_FanInfo[i].fanB_Pos.x - WALL_WIDTH * 0.5f, m_FanInfo[i].fanB_Pos.y + WALL_HEIGHT * 0.5f,
						m_FanInfo[i].size.x, m_FanInfo[i].size.y, u, v, WIND_ADD_U, WIND_ADD_V,
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LEFT_QUANTITY);
				}

				if (cnt > WIND_TEX_MAX)
				{
					cnt = 0;
				}

				SetBlendState(BLEND_MODE_ALPHABLEND);
			}
		}
	}
}

void GO_SS_Fan::LinkFanB(D3DXVECTOR2 pos, bool isLeft)
{
	for (int i = 0; i < FANS_MAX; i++)
	{
		if (!m_FanInfo[i].isLink)
		{
			m_FanInfo[i].fanB_Pos = pos;
			m_FanInfo[i].isLeft = isLeft;
			m_FanInfo[i].isLink = true;
			break;
		}
	}
}

void GO_SS_Fan::SetFan(D3DXVECTOR2 pos)
{
	for (int i = 0; i < FANS_MAX; i++)
	{
		if (m_FanInfo[i].use)
			continue;

		m_FanInfo[i].pos = pos;
		m_FanInfo[i].size = D3DXVECTOR2(WALL_WIDTH, WALL_HEIGHT);
		m_FanInfo[i].use = true;
		break;
	}
}

void GO_SS_Fan::AddX(FLOAT x)
{
	for (int i = 0; i < FANS_MAX; i++)
	{
		if (!m_FanInfo[i].use)continue;
		m_FanInfo[i].pos.x += x;
		m_FanInfo[i].fanB_Pos.x += x;
	}
}

bool GO_SS_Fan::FCCollision(D3DXVECTOR2 pos1,D3DXVECTOR2 size1,D3DXVECTOR2 pos2,float size2)
{
	if (pos2.x > pos1.x - size1.x - size2 && pos2.x < pos1.x + size1.x + size2)
	{
		if (pos2.y > pos1.y - size1.y - size2 && pos2.y < pos1.y + size1.y + size2)
		{
			
			return true;
		}
	}
	return false;
}

void GO_SS_Fan::DebugOut(void)
{
#ifdef _DEBUG	// ƒfƒoƒbƒO”Å‚ÌŽž‚¾‚¯Angle‚ð•\Ž¦‚·‚é
	wsprintf(GetDebugStr(), WINDOW_CAPTION);
	wsprintf(&GetDebugStr()[strlen(GetDebugStr())], " isWork:%d",
		m_FanInfo[0].isWork);

	SetWindowText(GethWnd()[0], GetDebugStr());
#endif
}

void PlayerMoveForFan::ChangeWindSpeed()
{
	if (once) {
		if (windSpeed >= 10.0f) {
			once = false;
			windSpeed = WIND_DEFAULT_SPEED;
		}
		else {
			windSpeed += WIND_ACCELERATION;
		}
	}
	
}
