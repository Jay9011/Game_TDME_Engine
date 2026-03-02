//////////////////////////////////////////////////////////////
// 기본 WVP 변환 + 텍스처 샘플링 셰이더
//
// VS: 로컬 좌표 -> 클립 좌표 (WVP 행렬 곱셈)
// PS: 텍스처 샘플링으로 최종 색상 결정
//
// 대응 정점 타입: VertexPT (Position + TexCoord)
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
// Constant Buffer
//////////////////////////////////////////////////////////////
cbuffer Transform : register(b0)	// Constant Buffer (b = buffer)
{
	matrix World;	// 추후 조명 계산에서 World 좌표가 필요하므로 분리 전달
	matrix View;
	matrix Projection;
};

//////////////////////////////////////////////////////////////
// Vertex Shader
//////////////////////////////////////////////////////////////
struct VS_INPUT
{
	float3 Position : POSITION;
	float2 TexCoord : TEXCOORD;	
};

struct VS_OUTPUT
{
	float4 Position : SV_POSITION;	// SV_POSITION = System Value Position
	float2 TexCoord : TEXCOORD0;
};

VS_OUTPUT VS_MAIN(VS_INPUT input)
{
	VS_OUTPUT output;

	float4 worldPos = mul(float4(input.Position, 1.0f), World);	// Row-Vector 이므로 (Vector * Matrix)
	float4 viewPos  = mul(worldPos, View);
	output.Position = mul(viewPos, Projection);

	output.TexCoord = input.TexCoord;

	return output;
}

//////////////////////////////////////////////////////////////
// Pixel Shader
//////////////////////////////////////////////////////////////
Texture2D DiffuseMap : register(t0);
SamplerState Sampler0 : register(s0);

float4 PS_MAIN(VS_OUTPUT input) :SV_Target
{
	return DiffuseMap.Sample(Sampler0, input.TexCoord);
}