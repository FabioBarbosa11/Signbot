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

float bom_dia[3][MAX_JOINTS] =
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

float eu[1][MAX_JOINTS] = {
                              0.10, 0.99, 0.66, -0.34, 1.57,
                              0.45, -0.13, 0.79,
                              1.57, 0, 0,
                              1.05, 0.00, 0.00,
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

float posso[2][MAX_JOINTS] =
{
  {
    0.0, 1.12, -0.06, -0.30, 1.57,
    0.66, -0.05, -0.44,
    0, 1.25, 1.57,
    0.67, 1.20, 1.17,
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
    0, 1.10, 0.19, -0.22, 1.52,
    1.26, 0.60, -0.26,
    0, 0, 0,
    0, 0, 0,
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
  }
};
/**********************************************************************************
 * *******************************************************************************/


#endif
