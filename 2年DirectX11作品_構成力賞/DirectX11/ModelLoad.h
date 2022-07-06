#pragma once
#include "main.h"
#include "GameObject.h"

enum MODEL_INDEX {
	MODEL_NONE = -1,
	MODEL_RANGE,
	MODEL_MAX,
};

class ModelLoad {
public:
	ModelLoad() {
		for (int i = 0; i < MODEL_MAX; i++) {
			LoadModel(m_TexName[i], &m_Models[i]);
		}
	}

	~ModelLoad() {
		for (int i = 0; i < MODEL_MAX; i++) {
			UnloadModel(&m_Models[i]);
		}
	}

	DX11_MODEL* GetModel(int index) { return &m_Models[index]; }

	DX11_MODEL m_Models[MODEL_MAX];
	char m_TexName[MODEL_MAX][64] = {
		"data/MODEL/range.obj",
	};
};