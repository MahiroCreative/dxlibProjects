SamplerState smp : register(s0);
Texture2D<float4> tex : register(t0);

struct PS_INPUT
{
    float4 Diffuse : COLOR0; // �f�B�t���[�Y�J���[
    float4 Specular : COLOR1; // �X�y�L�����J���[
    float3 Normal : NORMAL;
    float3 Tangent : TANGENT;
    float3 Binormal : BINORMAL;
    float2 TexCoords0 : TEXCOORD0; // �e�N�X�`�����W
    float4 svPosition : SV_POSITION; // ���W( �v���W�F�N�V������� )
    float4 Position : POSITION0; // ���W( ���[���h��� )
    float4 P : POSITION1; // ���W( �v���W�F�N�V������� )
    float4 VPosition : POSITION2; // ���W( ���[���h��� * �r���[ )
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