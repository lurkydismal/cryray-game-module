#ifndef vis_commonH
#define vis_commonH
#pragma once

#pragma pack(push,4)
struct vis_data
{
    Fsphere sphere; //
    Fbox box; //
    u32 marker; // for different sub-renders
    u32 accept_frame; // when it was requisted accepted for main render
    u32 hom_frame; // when to perform test - shedule
    u32 hom_tested; // when it was last time tested
    float fov; // render fov
    float vpnear; // render vp

    IC void clear()
    {
        sphere.P.set(0, 0, 0);
        sphere.R = 0;
        box.invalidate();
        marker = 0;
        accept_frame = 0;
        hom_frame = 0;
        hom_tested = 0;
        fov = 0.0f;
        vpnear = 0.0f;
    }
};
#pragma pack(pop)
#endif
