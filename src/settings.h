#ifndef SETTINGS_H
#define SETTINGS_H

struct s_video
{
    int width, height;
    float fov;
    float aspect;
    int aa_samples;
};

struct s_settings
{
    struct s_video video;
};

#endif // SETTINGS_H
