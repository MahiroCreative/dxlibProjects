Texture2D original : register(t0);
Texture2D gateA : register(t1);
Texture2D gateB : register(t2);
Texture2D gatePos : register(t3);
Texture2D originalDepth : register(t4);
Texture2D gatePosDepth : register(t5);
SamplerState smp : register(s0);

struct PS_INPUT
{
    float4 pos : SV_POSITION;
    float4 dif : COLOR0;
    float2 uv : TEXCOORD0;
};

float4 main(PS_INPUT input) : SV_TARGET
{
    float oDep = originalDepth.Sample(smp, input.uv).r;
    float gDep = gatePosDepth.Sample(smp, input.uv).r;
    
    const float minimum = 0.005f;
    
    // ゲートが描かれている場合
    if (gDep > 0)
    {
        // プレイヤーからの描画がない || ゲートの深度値がプレイヤーの深度値より小さい場合
        if (oDep == 0 || gDep < oDep)
        {
            // ゲートからのカメラを描画
            float4 col = gatePos.Sample(smp, input.uv);
            // 赤いゲート(ゲートA)からのカメラを描画
            if (col.r > 0.5)
            {
                return gateA.Sample(smp, input.uv);
            }
            // 青いゲート(ゲートB)からのカメラを描画
            else if (col.b > 0.5)
            {
                return gateB.Sample(smp, input.uv);
            }
                
        }

    }
    
    // 通常のまま描画
    return original.Sample(smp, input.uv);
}