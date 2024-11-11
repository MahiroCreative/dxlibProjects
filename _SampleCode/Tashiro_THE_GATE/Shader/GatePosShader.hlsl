SamplerState smp : register(s0);
Texture2D<float4> tex : register(t0);

struct PS_INPUT
{
    float4 Diffuse : COLOR0; // ディフューズカラー
    float4 Specular : COLOR1; // スペキュラカラー
    float3 Normal : NORMAL;
    float3 Tangent : TANGENT;
    float3 Binormal : BINORMAL;
    float2 TexCoords0 : TEXCOORD0; // テクスチャ座標
    float4 svPosition : SV_POSITION; // 座標( プロジェクション空間 )
    float4 Position : POSITION0; // 座標( ワールド空間 )
    float4 P : POSITION1; // 座標( プロジェクション空間 )
    float4 VPosition : POSITION2; // 座標( ワールド空間 * ビュー )
};

float4 main(PS_INPUT input) : SV_TARGET
{
    float2 location;
    location.x = input.P.x / input.P.w;
    location.y = input.P.y / input.P.w;
    
    location.y *= -1;
    
    location.x = (location.x + 1) * 0.5;
    location.y = (location.y + 1) * 0.5;
    
    return tex.Sample(smp, location);

}