

//*****************************************************************************
// 定数バッファ
//*****************************************************************************

// マトリクスバッファ
cbuffer WorldBuffer : register( b0 )
{
	matrix World;
}

cbuffer ViewBuffer : register( b1 )
{
	matrix View;
}

cbuffer ProjectionBuffer : register( b2 )
{
	matrix Projection;
}

// マテリアルバッファ
struct MATERIAL
{
	float4		Ambient;
	float4		Diffuse;
	float4		Specular;
	float4		Emission;
	float		Shininess;
	int			noTexSampling;
	float		Dummy[2];//16byte境界用
};

cbuffer MaterialBuffer : register( b3 )
{
	MATERIAL	Material;
}

// ライト用バッファ
struct LIGHT
{
	float4		Direction[10];
	float4		Position[10];
	float4		Diffuse[10];
	float4		Ambient[10];
	float4		Attenuation[10];
	int4		Flags[10];
	int			Enable;
	int			Dummy[3];//16byte境界用
};

cbuffer LightBuffer : register( b4 )
{
	LIGHT		Light;
}


//=============================================================================
// 頂点シェーダ
//=============================================================================
void VertexShaderPolygon( in  float4 inPosition		: POSITION0,
						  in  float4 inNormal		: NORMAL0,
						  in  float4 inDiffuse		: COLOR0,
						  in  float2 inTexCoord		: TEXCOORD0,

						  out float4 outPosition	: SV_POSITION,
						  out float4 outNormal		: NORMAL0,
						  out float2 outTexCoord	: TEXCOORD0,
						  out float4 outDiffuse		: COLOR0 )
{
	matrix wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);

	outPosition = mul(inPosition, wvp);
	outNormal = inNormal;
	outTexCoord = inTexCoord;

	if (Light.Enable == 0) 
	{
		outDiffuse = inDiffuse * Material.Diffuse;
	}
	else
	{
		float4 color = float4(0.0f, 0.0f, 0.0f, 0.0f);
		float4 outColor = float4(0.0f, 0.0f, 0.0f, 0.0f);

		for (int i = 0; i < 10; i++)
		{
			if (Light.Flags[i].y == 1)
			{
				if (Light.Flags[i].x == 1)
				{
					float4 worldNormal, normal;
					normal = float4(inNormal.xyz, 0.0);
					worldNormal = mul(normal, World);
					worldNormal = normalize(worldNormal);

					float light = 0.5 - 0.25 * dot(Light.Direction[i].xyz, worldNormal.xyz);

					color = inDiffuse * Material.Diffuse * light * Light.Diffuse[i];
					color += inDiffuse * Material.Ambient * Light.Ambient[i];
				}
				else if (Light.Flags[i].x == 2)
				{
					float4 worldNormal, normal;
					normal = float4(inNormal.xyz, 0.0);
					worldNormal = mul(normal, World);
					worldNormal = normalize(worldNormal);

					float3 posWorld = mul(inPosition, World);
					float3 lightDir;
					lightDir = normalize(posWorld - Light.Position[i]);
					float light = -1.0 * dot(lightDir.xyz, worldNormal.xyz);

					color = inDiffuse * Material.Diffuse * light * Light.Diffuse[i];
					color += inDiffuse * Material.Ambient * Light.Ambient[i];
					float distance = length(posWorld - Light.Position[i]);

					float att = saturate((Light.Attenuation[i].x - distance) / Light.Attenuation[i].x);
					color *= att;
				}
				else
				{
					color = float4(0.0f, 0.0f, 0.0f, 0.0f);
				}

				outColor += color;
			}
		}

		outColor += Material.Emission;

		outDiffuse = saturate(outColor);
		outDiffuse.a = inDiffuse.a * Material.Diffuse.a;
	}
}



//*****************************************************************************
// グローバル変数
//*****************************************************************************
Texture2D		g_Texture : register( t0 );
SamplerState	g_SamplerState : register( s0 );


//=============================================================================
// ピクセルシェーダ
//=============================================================================
void PixelShaderPolygon( in  float4 inPosition		: SV_POSITION,
						 in  float4 inNormal		: NORMAL0,
						 in  float2 inTexCoord		: TEXCOORD0,
						 in  float4 inDiffuse		: COLOR0,

						 out float4 outDiffuse		: SV_Target )
{
	float4 color;

	if (Material.noTexSampling == 0)
	{
		color = g_Texture.Sample(g_SamplerState, inTexCoord);

		color *= inDiffuse;
	}
	else
	{
		color = inDiffuse;
	}

	outDiffuse = color;

}
