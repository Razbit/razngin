#ifndef SETTINGS_H
#define SETTINGS_H

/**
 * @file
 * @brief Settings of the game.
 */

/**
 * @brief A struct for storing video settings
 */
struct s_video
{
    /** Width of the scene */
    int width;
    /** Height of the scene */
    int height;
    /** Field of View */
    float fov;
    /** Aspect ratio */
    float aspect;
    /** Anti-aliasing samples */
    int aa_samples;
};

/**
 * @brief A struct for storing game settings
 */
struct s_settings
{
    /** Video settings @sa s_video */
    struct s_video video;
};

#endif // SETTINGS_H
