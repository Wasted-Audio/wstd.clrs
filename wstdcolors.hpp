#include "DearImGui.hpp"


auto WstdTitleBgActive = ImColor::HSV(3.31f / 3.6f, 0.64f, 0.40f);
auto WstdWindowBg = ImColor::HSV(3.31f / 3.6f, 0.64f, 0.10f);

auto Blue     = ImColor::HSV(2.04f / 3.6f, 0.83f, 0.64f);
auto BlueBr   = ImColor::HSV(2.04f / 3.6f, 0.83f, 0.84f);
auto BlueDr   = ImColor::HSV(2.04f / 3.6f, 0.83f, 0.44f);
auto Green    = ImColor::HSV(1.6f  / 3.6f, 0.77f, 0.64f);
auto GreenBr  = ImColor::HSV(1.6f  / 3.6f, 0.77f, 0.74f);
auto GreenDr  = ImColor::HSV(1.6f  / 3.6f, 0.77f, 0.44f);
auto Red      = ImColor::HSV(0.03f / 3.6f, 0.76f, 0.74f);
auto RedBr    = ImColor::HSV(0.03f / 3.6f, 0.76f, 0.84f);
auto RedDr    = ImColor::HSV(0.03f / 3.6f, 0.76f, 0.54f);
auto Yellow   = ImColor::HSV(0.47f / 3.6f, 0.75f, 0.64f);
auto YellowBr = ImColor::HSV(0.47f / 3.6f, 0.75f, 0.84f);
auto YellowDr = ImColor::HSV(0.47f / 3.6f, 0.75f, 0.44f);
auto Grey     = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
auto GreyBr   = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
auto WhiteDr  = ImVec4(0.8f, 0.8f, 0.8f, 0.6f);
auto TextClr  = ImVec4(0.85f, 0.85f, 0.85f, 0.85f);

ImVec4 ColorBright(ImVec4 color, float bright, bool grey = true)
{
    if (bright > -15.0f || not grey)
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
    auto mix_col = ImVec4();
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
            mix_col = high_col;
        else if (comp < 0.0f)
            mix_col  = low_col;

        auto outcol = ImVec4(
            (mid_col.x + (mix_col.x * fabs(comp)) )/(1 + fabs(comp)) + perc,
            (mid_col.y + (mix_col.y * fabs(comp)) )/(1 + fabs(comp)) + perc,
            (mid_col.z + (mix_col.z * fabs(comp)) )/(1 + fabs(comp)) + perc,
            (mid_col.w + (mix_col.w * fabs(comp)) )/(1 + fabs(comp))
        );
        return outcol;
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

void CenterTextX(const char *text, float objectWidth)
{
    ImVec2 textSize = ImGui::CalcTextSize(text);
    auto margin = ((objectWidth) - (textSize.x))/ 2.0f;
    ImGui::Dummy(ImVec2(margin, 0.0f)); ImGui::SameLine();
    ImGui::Text(text); ImGui::SameLine();
    ImGui::Dummy(ImVec2(margin, 0.0f));
}