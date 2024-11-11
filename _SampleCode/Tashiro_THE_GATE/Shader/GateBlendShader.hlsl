Texture2D base : register(t0);
Texture2D from : register(t1);
Texture2D pre : register(t2);   // 使わないかも
Texture2D gatePos : register(t3);
Texture2D baseDepth : register(t4);
Texture2D fromDepth : register(t5);
SamplerState smp : register(s0);

struct PS_INPUT
{
    float4 pos : SV_POSITION;
    float4 dif : COLOR0;
    float2 uv : TEXCOORD0;
};

float4 main(PS_INPUT input) : SV_TARGET
{
    float bDep = base.Sample(smp, input.uv).r;
    float fDep = from.Sample(smp, input.uv).r;
    
    // ゲートが描かれている場合
    if (fDep > 0)
    {
        // プレイヤーからの描画がない || ゲートの深度値がプレイヤーの深度値より小さい場合
        if (bDep == 0 || fDep < bDep)
        {
            return from.Sample(smp, input.uv);
        }

    }
    
    // 通常のまま描画
    return base.Sample(smp, input.uv);
}