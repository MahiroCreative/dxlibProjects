Texture2D base : register(t0);
Texture2D from : register(t1);
Texture2D pre : register(t2);   // �g��Ȃ�����
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
    
    // �Q�[�g���`����Ă���ꍇ
    if (fDep > 0)
    {
        // �v���C���[����̕`�悪�Ȃ� || �Q�[�g�̐[�x�l���v���C���[�̐[�x�l��菬�����ꍇ
        if (bDep == 0 || fDep < bDep)
        {
            return from.Sample(smp, input.uv);
        }

    }
    
    // �ʏ�̂܂ܕ`��
    return base.Sample(smp, input.uv);
}