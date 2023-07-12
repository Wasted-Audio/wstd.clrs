#include "DearImGui.hpp"


auto Blue     = ImColor::HSV(2.04f / 3.6f, 0.83f, 0.64f);
auto BlueBr   = ImColor::HSV(2.04f / 3.6f, 0.83f, 0.84f);
auto Green    = ImColor::HSV(1.6f  / 3.6f, 0.77f, 0.64f);
auto GreenBr  = ImColor::HSV(1.6f  / 3.6f, 0.77f, 0.74f);
auto GreenDr  = ImColor::HSV(1.6f  / 3.6f, 0.77f, 0.44f);
auto Red      = ImColor::HSV(0.03f / 3.6f, 0.76f, 0.74f);
auto RedBr    = ImColor::HSV(0.03f / 3.6f, 0.76f, 0.84f);
auto Yellow   = ImColor::HSV(0.47f / 3.6f, 0.75f, 0.64f);
auto YellowBr = ImColor::HSV(0.47f / 3.6f, 0.75f, 0.84f);
auto Grey     = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
auto GreyBr   = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
auto WhiteDr  = ImVec4(0.8f, 0.8f, 0.8f, 0.8f);

ImVec4 ColorBright(ImVec4 color, float bright)
{
    if (bright > -15.0f)
    {
        auto perc = bright / 100.0f;

        auto outcol = ImVec4(
            color.x + perc,
            color.y + perc,
            color.z + perc,
            color.w
        );
        return outcol;
    }
    else
    {
        auto outcol = ImVec4(
            0.3f,
            0.3f,
            0.3f,
            color.w
        );
        return outcol;
    }
}


ImVec4 ColorMid(ImVec4 high_col, ImVec4 mid_col, ImVec4 low_col, float bright, float freq)
{
    auto perc = bright / 100.0f;

    auto comp = (log(freq / 313.3f) / log(5705.6f / 313.3f)) * 2.0f - 1.0f;

    if (bright == -15.0f)
    {
        auto outcol = ImVec4(
            0.3f,
            0.3f,
            0.3f,
            mid_col.w
        );
        return outcol;
    }
    else
    {
        if (comp == 0.0f)
        {
            auto outcol = ImVec4(
                mid_col.x + perc,
                mid_col.y + perc,
                mid_col.z + perc,
                mid_col.w
            );
            return outcol;
        }
        else if (comp > 0.0f)
        {
            auto outcol = ImVec4(
                (mid_col.x + (high_col.x * comp) )/(1 + comp) + perc,
                (mid_col.y + (high_col.y * comp) )/(1 + comp) + perc,
                (mid_col.z + (high_col.z * comp) )/(1 + comp) + perc,
                (mid_col.w + (high_col.w * comp) )/(1 + comp)
            );
            return outcol;
        }
        else if (comp < 0.0f)
        {
            auto outcol = ImVec4(
                (mid_col.x + (low_col.x * fabs(comp)) )/(1 + fabs(comp)) + perc,
                (mid_col.y + (low_col.y * fabs(comp)) )/(1 + fabs(comp)) + perc,
                (mid_col.z + (low_col.z * fabs(comp)) )/(1 + fabs(comp)) + perc,
                (mid_col.w + (low_col.w * fabs(comp)) )/(1 + fabs(comp))
            );
            return outcol;
        }
        else
        {
            return ImVec4();
        }
    }
}


ImVec4 ColorMix(ImVec4 source_col, ImVec4 mix_col, float bright, float mix_val)
{
    auto perc = bright / 100.0f;
    auto val_perc = mix_val / 100.0f;
    auto val_perc_inv = 1.0f - val_perc;

    if (bright == -15.0f)
    {
        auto outcol = ImVec4(
            0.3f,
            0.3f,
            0.3f,
            mix_col.w
        );
        return outcol;
    }
    else
    {
        auto outcol = ImVec4(
            ((source_col.x * val_perc_inv) + ((mix_col.x + perc) * val_perc)),
            ((source_col.y * val_perc_inv) + ((mix_col.y + perc) * val_perc)),
            ((source_col.z * val_perc_inv) + ((mix_col.z + perc) * val_perc)),
            ((source_col.w * val_perc_inv) + (mix_col.w * val_perc))
            );
        return outcol;
    }
}