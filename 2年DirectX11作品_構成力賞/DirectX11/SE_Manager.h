/*==============================================================================

   SoundEffectä«óù [SE_Manager.h]
														 Author :Yanagisawa Yuta
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "sound.h"

enum SE_INDEX {
	SE_NONE = -1,
	SE_BON		= 0,
	SE_GETEXP	= 1,
	SE_KIRAKIRA	= 2,
	SE_MAJIKARU	= 3,
	SE_POTSUN	= 4,
	SE_FIRE		= 5,
	SE_EXPLOSION= 6,
	SE_TAIKO	= 7,
	SE_PAGE		= 8,
	//SE_BLAST	= 10,
	SE_MAX,
};

class SE_Manager
{
private:
	char m_SEName[SE_MAX][64] = {
		"data/SE/DL_SE/01_bo-n.wav",
		"data/SE/DL_SE/02_getexp.wav",
		"data/SE/DL_SE/03_kirakira.wav",
		"data/SE/DL_SE/04_majikaru.wav",
		"data/SE/DL_SE/05_potsun.wav",
		"data/SE/DL_SE/06_fire.wav",
		"data/SE/DL_SE/07_explosion.wav",
		"data/SE/DL_SE/08_taiko.wav",
		"data/SE/DL_SE/09_page.wav",
		//"data/SE/DL_SE/10_blast.wav",
	};
public:

	void LoadSE(void) {
		for (int i = 0; i < SE_MAX; i++) {
			m_SE[i] = LoadSound(m_SEName[i]);
		}
	}

	int GetSE(int index) { return m_SE[index]; }

	void PlaySE(int index, float volume) { 
		SetVolume(index, volume); 
		PlaySound(index, 0);
	}

	

private:
	int m_SE[SE_MAX];
};

