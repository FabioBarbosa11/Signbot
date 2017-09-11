#ifndef _GESTURE_INFO_
#define _GESTURE_INFO_

#define MAX_JOINTS 46

/*******************************************************************************
 *                                database
 * ****************************************************************************/

//vector com as coordenadas default(braços em baixo)
float default_pose[1][MAX_JOINTS] = {
                                   1.57, 1.5, 0, 0, 0,
                                   0, 0, 0,
                                   0, 0, 0,
                                   0, 0, 0,
                                   0, 0, 0,
                                   0, 0, 0,
                                   0, 0, 0,

                                   1.57, -1.5, 0, 0, 0,
                                   0, 0, 0,
                                   0, 0, 0,
                                   0, 0, 0,
                                   0, 0, 0,
                                   0, 0, 0,
                                   0, 0, 0};

float letter_b[1][MAX_JOINTS] = {
                              0.52, 1.19, -0.09, -0.16, 1.57,
                              0.27, 0, 0.3,
                              0, 0, 0,
                              1.57, 1.57, 1.57,
                              1.57, 1.57, 1.57,
                              1.57, 1.57, 1.57,
                              1.57, 1.57, 1.57,

                              1.57, -1.5, 0, 0, 0,
                              0, 0, 0,
                              0, 0, 0,
                              0, 0, 0,
                              0, 0, 0,
                              0, 0, 0,
                              0, 0, 0
                            };

float bom_dia[4][MAX_JOINTS] =
{
  {
    0.52, 1.19, -0.09, -0.16, 1.57,
    0.27, 0, 0.3,
    0, 0, 0,
    1.57, 1.57, 1.57,
    1.57, 1.57, 1.57,
    1.57, 1.57, 1.57,
    1.57, 1.57, 1.57,

    1.57, -1.5, 0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0
  },
  {
    0.52, 1.19, -0.09, -0.16, 1.57,
    0.27, 0, 0.3,
    0, 0, 0,
    1.57, 1.57, 1.57,
    1.57, 1.57, 1.57,
    1.57, 1.57, 1.57,
    1.57, 1.57, 1.57,

    1.57, -1.5, 0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0
  },
  {
    0.52, 1.19, -0.09, -0.16, 1.57,
    0.27, 0, 0.3,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,

    1.57, -1.5, 0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0
  },
  {
   0.59, 1.41, -0.23, -1.34, 1.57,
    0, -0.22, 0.35,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,

    1.57, -1.5, 0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0
  }
};

float ajudar[2][MAX_JOINTS] =
{
  {
    0.49, 1.03, 0.23, -0.45, 1.57,
    0, -0.43, -0.79,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,

    0.08, -0.93, -0.49, -0.17, -1.57,
    0, 0.52, 0.79,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0
  },
  {
    0, 1.41, 0.61, -0.51, 0.7,
    0, -0.37, -0.4,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,

    0, -1.49, -0.69, -0.8, -0.81,
    0, 0.09, 0.48,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0
  }
};

/**********************************************************************************
 * *******************************************************************************/


#endif
