#include "GO_ScrambleRotation.h"
#include "GO_Player.h"
#include "GO_Scramble.h"

void GO_ScrambleRotation::Update(void){

	double x_distance = (double)mp_player->GetPos().x - (double)mp_vortex->GetScramblePos().x;
	double y_distance = (double)mp_player->GetPos().y - (double)mp_vortex->GetScramblePos().y;
	float angle = atan2(x_distance, y_distance);

	mp_vortex->SetScrambleAngle(angle);
}




