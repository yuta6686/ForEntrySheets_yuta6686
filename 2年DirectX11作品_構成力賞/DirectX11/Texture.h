/*==============================================================================

   テクスチャの読み込み [texture.h]
														 Author :Yanagisawa Yuta
														 Date   :
--------------------------------------------------------------------------------*/
#pragma once


#include "renderer.h"

int LoadTexture(char* fileName);
void UninitTexture(void);

ID3D11ShaderResourceView** GetTexture(int index);
