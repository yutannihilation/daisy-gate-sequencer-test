#define LENGTH_ONESHOT 0.124f
#define LENGTH_LONG 1.0f

#define FLAM1 0.07f

struct SubStep {
  float start;  // when the gate starts **in phase**
  float length; // gate length **in seconds**
  float delay;  // gate delay **in seconds**
};

// TODO: indicate 1.0f as the end of the substeps
static SubStep endstep = SubStep{1.0f, 0.0f, 0.0f};

// clang-format off

//** blank ************************************************//

SubStep subptn_blank[] = {
    endstep,
};

//** long ************************************************//

SubStep subptn_long[] = {
    SubStep{0.0f, LENGTH_LONG, 0.0f},
    endstep,
};

SubStep subptn_long_2[] = {
    SubStep{0.0f, LENGTH_LONG, 0.2f},
    endstep,
};


//** evenly distributed patterns *******************************//

SubStep subptn_even_1beat[] = {
    SubStep{0.0f, LENGTH_ONESHOT, 0.0f},
    endstep,
};

SubStep subptn_even_2beats[] = {
    SubStep{0.0f,        LENGTH_ONESHOT, 0.0f},
    SubStep{1.0f / 2.0f, LENGTH_ONESHOT, 0.0f},
    endstep,
};

SubStep subptn_even_3beats[] = {
    SubStep{0.0f,        LENGTH_ONESHOT, 0.0f},
    SubStep{1.0f / 3.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{2.0f / 3.0f, LENGTH_ONESHOT, 0.0f},
    endstep,
};

SubStep subptn_even_4beats[] = {
    SubStep{0.0f,        LENGTH_ONESHOT, 0.0f},
    SubStep{1.0f / 4.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{2.0f / 4.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{3.0f / 4.0f, LENGTH_ONESHOT, 0.0f},
    endstep,
};

SubStep subptn_even_5beats[] = {
    SubStep{0.0f,        LENGTH_ONESHOT, 0.0f},
    SubStep{1.0f / 5.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{2.0f / 5.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{3.0f / 5.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{4.0f / 5.0f, LENGTH_ONESHOT, 0.0f},
    endstep,
};

SubStep subptn_even_6beats[] = {
    SubStep{0.0f,        LENGTH_ONESHOT, 0.0f},
    SubStep{1.0f / 6.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{2.0f / 6.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{3.0f / 6.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{4.0f / 6.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{5.0f / 6.0f, LENGTH_ONESHOT, 0.0f},
    endstep,
};

SubStep subptn_even_7beats[] = {
    SubStep{0.0f,        LENGTH_ONESHOT, 0.0f},
    SubStep{1.0f / 7.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{2.0f / 7.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{3.0f / 7.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{4.0f / 7.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{5.0f / 7.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{6.0f / 7.0f, LENGTH_ONESHOT, 0.0f},
    endstep,
};

SubStep subptn_even_8beats[] = {
    SubStep{0.0f,        LENGTH_ONESHOT, 0.0f},
    SubStep{1.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{2.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{3.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{4.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{5.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{6.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{7.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    endstep,
};

//** with rest *******************************//

SubStep subptn_rest_3beats_1[] = {
    SubStep{0.0f,        LENGTH_ONESHOT, 0.0f},
    SubStep{2.0f / 3.0f, LENGTH_ONESHOT, 0.0f},
    endstep,
};

SubStep subptn_rest_3beats_2[] = {
    SubStep{0.0f,        LENGTH_ONESHOT, 0.0f},
    SubStep{1.0f / 3.0f, LENGTH_ONESHOT, 0.0f},
    endstep,
};

SubStep subptn_rest_4beats_1[] = {
    SubStep{2.0f / 4.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{3.0f / 4.0f, LENGTH_ONESHOT, 0.0f},
    endstep,
};

SubStep subptn_rest_4beats_2[] = {
    SubStep{3.0f / 4.0f, LENGTH_ONESHOT, 0.0f},
    endstep,
};


SubStep subptn_rest_5beats_1[] = {
    SubStep{0.0f,        LENGTH_ONESHOT, 0.0f},
    SubStep{1.0f / 5.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{3.0f / 5.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{4.0f / 5.0f, LENGTH_ONESHOT, 0.0f},
    endstep,
};

SubStep subptn_rest_5beats_2[] = {
    SubStep{0.0f,        LENGTH_ONESHOT, 0.0f},
    SubStep{1.0f / 5.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{4.0f / 5.0f, LENGTH_ONESHOT, 0.0f},
    endstep,
};

SubStep subptn_rest_8beats_1[] = {
    SubStep{4.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{5.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{6.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{7.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    endstep,
};

SubStep subptn_rest_8beats_2[] = {
    SubStep{0.0f,        LENGTH_ONESHOT, 0.0f},
    SubStep{1.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{2.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{3.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    endstep,
};

SubStep subptn_rest_8beats_3[] = {
    SubStep{0.0f,        LENGTH_ONESHOT, 0.0f},
    SubStep{1.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{4.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{5.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{6.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{7.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    endstep,
};

SubStep subptn_rest_8beats_4[] = {
    SubStep{0.0f,        LENGTH_ONESHOT, 0.0f},
    SubStep{1.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{2.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{3.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{6.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{7.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    endstep,
};

SubStep subptn_rest_8beats_5[] = {
    SubStep{0.0f,        LENGTH_ONESHOT, 0.0f},
    SubStep{2.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{3.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{4.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{6.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{7.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    endstep,
};

SubStep subptn_rest_8beats_6[] = {
    SubStep{0.0f,        LENGTH_ONESHOT, 0.0f},
    SubStep{1.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{2.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{3.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{4.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{5.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{6.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    endstep,
};

SubStep subptn_rest_8beats_7[] = {
    SubStep{0.0f,        LENGTH_ONESHOT, 0.0f},
    SubStep{1.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{3.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{4.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{5.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{6.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{7.0f / 8.0f, LENGTH_ONESHOT, 0.0f},
    endstep,
};


//** with fram *******************************//

SubStep subptn_flam_1beats[] = {
    SubStep{0.0f,        LENGTH_ONESHOT, 0.0f},
    SubStep{0.0f,        LENGTH_ONESHOT, FLAM1},
    endstep,
};


SubStep subptn_flam_2beats_1[] = {
    SubStep{0.0f,        LENGTH_ONESHOT, 0.0f},
    SubStep{0.0f,        LENGTH_ONESHOT, FLAM1},
    SubStep{1.0f / 2.0f, LENGTH_ONESHOT, 0.0f},
    endstep,
};

SubStep subptn_flam_2beats_2[] = {
    SubStep{0.0f,        LENGTH_ONESHOT, 0.0f},
    SubStep{0.0f,        LENGTH_ONESHOT, FLAM1},
    SubStep{1.0f / 2.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{1.0f / 2.0f, LENGTH_ONESHOT, FLAM1},
    endstep,
};

SubStep subptn_flam_4beats_1[] = {
    SubStep{0.0f,        LENGTH_ONESHOT, 0.0f},
    SubStep{0.0f,        LENGTH_ONESHOT, FLAM1},
    SubStep{1.0f / 4.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{2.0f / 4.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{3.0f / 4.0f, LENGTH_ONESHOT, 0.0f},
    endstep,
};

SubStep subptn_flam_4beats_2[] = {
    SubStep{0.0f,        LENGTH_ONESHOT, 0.0f},
    SubStep{0.0f,        LENGTH_ONESHOT, FLAM1},
    SubStep{2.0f / 4.0f, LENGTH_ONESHOT, 0.0f},
    SubStep{3.0f / 4.0f, LENGTH_ONESHOT, 0.0f},
    endstep,
};

// clang-format on
