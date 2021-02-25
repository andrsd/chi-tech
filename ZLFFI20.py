import numpy as np
import matplotlib.pyplot as plt

data0=np.zeros([100,5])
data0[0,0] = -1
data0[0,1] = 0
data0[0,2] = 0.025
data0[0,3] = 0
data0[0,4] = 1.1962e-05
data0[1,0] = -0.979798
data0[1,1] = 0
data0[1,2] = 0.025
data0[1,3] = 0.020202
data0[1,4] = 8.03019e-06
data0[2,0] = -0.959596
data0[2,1] = 0
data0[2,2] = 0.025
data0[2,3] = 0.040404
data0[2,4] = 8.03019e-06
data0[3,0] = -0.939394
data0[3,1] = 0
data0[3,2] = 0.025
data0[3,3] = 0.0606061
data0[3,4] = 4.575e-06
data0[4,0] = -0.919192
data0[4,1] = 0
data0[4,2] = 0.025
data0[4,3] = 0.0808081
data0[4,4] = 2.04921e-06
data0[5,0] = -0.89899
data0[5,1] = 0
data0[5,2] = 0.025
data0[5,3] = 0.10101
data0[5,4] = 2.04921e-06
data0[6,0] = -0.878788
data0[6,1] = 0
data0[6,2] = 0.025
data0[6,3] = 0.121212
data0[6,4] = 4.96778e-07
data0[7,0] = -0.858586
data0[7,1] = 0
data0[7,2] = 0.025
data0[7,3] = 0.141414
data0[7,4] = 0
data0[8,0] = -0.838384
data0[8,1] = 0
data0[8,2] = 0.025
data0[8,3] = 0.161616
data0[8,4] = 0
data0[9,0] = -0.818182
data0[9,1] = 0
data0[9,2] = 0.025
data0[9,3] = 0.181818
data0[9,4] = 0
data0[10,0] = -0.79798
data0[10,1] = 0
data0[10,2] = 0.025
data0[10,3] = 0.20202
data0[10,4] = 0
data0[11,0] = -0.777778
data0[11,1] = 0
data0[11,2] = 0.025
data0[11,3] = 0.222222
data0[11,4] = 0
data0[12,0] = -0.757576
data0[12,1] = 0
data0[12,2] = 0.025
data0[12,3] = 0.242424
data0[12,4] = 0
data0[13,0] = -0.737374
data0[13,1] = 0
data0[13,2] = 0.025
data0[13,3] = 0.262626
data0[13,4] = 0
data0[14,0] = -0.717172
data0[14,1] = 0
data0[14,2] = 0.025
data0[14,3] = 0.282828
data0[14,4] = 0
data0[15,0] = -0.69697
data0[15,1] = 0
data0[15,2] = 0.025
data0[15,3] = 0.30303
data0[15,4] = 0
data0[16,0] = -0.676768
data0[16,1] = 0
data0[16,2] = 0.025
data0[16,3] = 0.323232
data0[16,4] = 0
data0[17,0] = -0.656566
data0[17,1] = 0
data0[17,2] = 0.025
data0[17,3] = 0.343434
data0[17,4] = 0
data0[18,0] = -0.636364
data0[18,1] = 0
data0[18,2] = 0.025
data0[18,3] = 0.363636
data0[18,4] = 0
data0[19,0] = -0.616162
data0[19,1] = 0
data0[19,2] = 0.025
data0[19,3] = 0.383838
data0[19,4] = 0
data0[20,0] = -0.59596
data0[20,1] = 0
data0[20,2] = 0.025
data0[20,3] = 0.40404
data0[20,4] = 0
data0[21,0] = -0.575758
data0[21,1] = 0
data0[21,2] = 0.025
data0[21,3] = 0.424242
data0[21,4] = 0
data0[22,0] = -0.555556
data0[22,1] = 0
data0[22,2] = 0.025
data0[22,3] = 0.444444
data0[22,4] = 0
data0[23,0] = -0.535354
data0[23,1] = 0
data0[23,2] = 0.025
data0[23,3] = 0.464646
data0[23,4] = 0
data0[24,0] = -0.515152
data0[24,1] = 0
data0[24,2] = 0.025
data0[24,3] = 0.484848
data0[24,4] = 0
data0[25,0] = -0.494949
data0[25,1] = 0
data0[25,2] = 0.025
data0[25,3] = 0.505051
data0[25,4] = 0
data0[26,0] = -0.474747
data0[26,1] = 0
data0[26,2] = 0.025
data0[26,3] = 0.525253
data0[26,4] = 0
data0[27,0] = -0.454545
data0[27,1] = 0
data0[27,2] = 0.025
data0[27,3] = 0.545455
data0[27,4] = 0
data0[28,0] = -0.434343
data0[28,1] = 0
data0[28,2] = 0.025
data0[28,3] = 0.565657
data0[28,4] = 0
data0[29,0] = -0.414141
data0[29,1] = 0
data0[29,2] = 0.025
data0[29,3] = 0.585859
data0[29,4] = 0
data0[30,0] = -0.393939
data0[30,1] = 0
data0[30,2] = 0.025
data0[30,3] = 0.606061
data0[30,4] = 0
data0[31,0] = -0.373737
data0[31,1] = 0
data0[31,2] = 0.025
data0[31,3] = 0.626263
data0[31,4] = 0
data0[32,0] = -0.353535
data0[32,1] = 0
data0[32,2] = 0.025
data0[32,3] = 0.646465
data0[32,4] = 0
data0[33,0] = -0.333333
data0[33,1] = 0
data0[33,2] = 0.025
data0[33,3] = 0.666667
data0[33,4] = 0
data0[34,0] = -0.313131
data0[34,1] = 0
data0[34,2] = 0.025
data0[34,3] = 0.686869
data0[34,4] = 0
data0[35,0] = -0.292929
data0[35,1] = 0
data0[35,2] = 0.025
data0[35,3] = 0.707071
data0[35,4] = 0
data0[36,0] = -0.272727
data0[36,1] = 0
data0[36,2] = 0.025
data0[36,3] = 0.727273
data0[36,4] = 0
data0[37,0] = -0.252525
data0[37,1] = 0
data0[37,2] = 0.025
data0[37,3] = 0.747475
data0[37,4] = 0
data0[38,0] = -0.232323
data0[38,1] = 0
data0[38,2] = 0.025
data0[38,3] = 0.767677
data0[38,4] = 0
data0[39,0] = -0.212121
data0[39,1] = 0
data0[39,2] = 0.025
data0[39,3] = 0.787879
data0[39,4] = 0
data0[40,0] = -0.191919
data0[40,1] = 0
data0[40,2] = 0.025
data0[40,3] = 0.808081
data0[40,4] = 0
data0[41,0] = -0.171717
data0[41,1] = 0
data0[41,2] = 0.025
data0[41,3] = 0.828283
data0[41,4] = 0
data0[42,0] = -0.151515
data0[42,1] = 0
data0[42,2] = 0.025
data0[42,3] = 0.848485
data0[42,4] = 0
data0[43,0] = -0.131313
data0[43,1] = 0
data0[43,2] = 0.025
data0[43,3] = 0.868687
data0[43,4] = 0
data0[44,0] = -0.111111
data0[44,1] = 0
data0[44,2] = 0.025
data0[44,3] = 0.888889
data0[44,4] = 0
data0[45,0] = -0.0909091
data0[45,1] = 0
data0[45,2] = 0.025
data0[45,3] = 0.909091
data0[45,4] = 0
data0[46,0] = -0.0707071
data0[46,1] = 0
data0[46,2] = 0.025
data0[46,3] = 0.929293
data0[46,4] = 0
data0[47,0] = -0.0505051
data0[47,1] = 0
data0[47,2] = 0.025
data0[47,3] = 0.949495
data0[47,4] = 0
data0[48,0] = -0.030303
data0[48,1] = 0
data0[48,2] = 0.025
data0[48,3] = 0.969697
data0[48,4] = 0
data0[49,0] = -0.010101
data0[49,1] = 0
data0[49,2] = 0.025
data0[49,3] = 0.989899
data0[49,4] = 0
data0[50,0] = 0.010101
data0[50,1] = 0
data0[50,2] = 0.025
data0[50,3] = 1.0101
data0[50,4] = 0
data0[51,0] = 0.030303
data0[51,1] = 0
data0[51,2] = 0.025
data0[51,3] = 1.0303
data0[51,4] = 0
data0[52,0] = 0.0505051
data0[52,1] = 0
data0[52,2] = 0.025
data0[52,3] = 1.05051
data0[52,4] = 0
data0[53,0] = 0.0707071
data0[53,1] = 0
data0[53,2] = 0.025
data0[53,3] = 1.07071
data0[53,4] = 0
data0[54,0] = 0.0909091
data0[54,1] = 0
data0[54,2] = 0.025
data0[54,3] = 1.09091
data0[54,4] = 0
data0[55,0] = 0.111111
data0[55,1] = 0
data0[55,2] = 0.025
data0[55,3] = 1.11111
data0[55,4] = 0
data0[56,0] = 0.131313
data0[56,1] = 0
data0[56,2] = 0.025
data0[56,3] = 1.13131
data0[56,4] = 0
data0[57,0] = 0.151515
data0[57,1] = 0
data0[57,2] = 0.025
data0[57,3] = 1.15152
data0[57,4] = 0
data0[58,0] = 0.171717
data0[58,1] = 0
data0[58,2] = 0.025
data0[58,3] = 1.17172
data0[58,4] = 0
data0[59,0] = 0.191919
data0[59,1] = 0
data0[59,2] = 0.025
data0[59,3] = 1.19192
data0[59,4] = 0
data0[60,0] = 0.212121
data0[60,1] = 0
data0[60,2] = 0.025
data0[60,3] = 1.21212
data0[60,4] = 0
data0[61,0] = 0.232323
data0[61,1] = 0
data0[61,2] = 0.025
data0[61,3] = 1.23232
data0[61,4] = 0
data0[62,0] = 0.252525
data0[62,1] = 0
data0[62,2] = 0.025
data0[62,3] = 1.25253
data0[62,4] = 0
data0[63,0] = 0.272727
data0[63,1] = 0
data0[63,2] = 0.025
data0[63,3] = 1.27273
data0[63,4] = 0
data0[64,0] = 0.292929
data0[64,1] = 0
data0[64,2] = 0.025
data0[64,3] = 1.29293
data0[64,4] = 0
data0[65,0] = 0.313131
data0[65,1] = 0
data0[65,2] = 0.025
data0[65,3] = 1.31313
data0[65,4] = 0
data0[66,0] = 0.333333
data0[66,1] = 0
data0[66,2] = 0.025
data0[66,3] = 1.33333
data0[66,4] = 0
data0[67,0] = 0.353535
data0[67,1] = 0
data0[67,2] = 0.025
data0[67,3] = 1.35354
data0[67,4] = 0
data0[68,0] = 0.373737
data0[68,1] = 0
data0[68,2] = 0.025
data0[68,3] = 1.37374
data0[68,4] = 0
data0[69,0] = 0.393939
data0[69,1] = 0
data0[69,2] = 0.025
data0[69,3] = 1.39394
data0[69,4] = 0
data0[70,0] = 0.414141
data0[70,1] = 0
data0[70,2] = 0.025
data0[70,3] = 1.41414
data0[70,4] = 0
data0[71,0] = 0.434343
data0[71,1] = 0
data0[71,2] = 0.025
data0[71,3] = 1.43434
data0[71,4] = 0
data0[72,0] = 0.454545
data0[72,1] = 0
data0[72,2] = 0.025
data0[72,3] = 1.45455
data0[72,4] = 0
data0[73,0] = 0.474747
data0[73,1] = 0
data0[73,2] = 0.025
data0[73,3] = 1.47475
data0[73,4] = 0
data0[74,0] = 0.494949
data0[74,1] = 0
data0[74,2] = 0.025
data0[74,3] = 1.49495
data0[74,4] = 0
data0[75,0] = 0.515152
data0[75,1] = 0
data0[75,2] = 0.025
data0[75,3] = 1.51515
data0[75,4] = 0
data0[76,0] = 0.535354
data0[76,1] = 0
data0[76,2] = 0.025
data0[76,3] = 1.53535
data0[76,4] = 0
data0[77,0] = 0.555556
data0[77,1] = 0
data0[77,2] = 0.025
data0[77,3] = 1.55556
data0[77,4] = 0
data0[78,0] = 0.575758
data0[78,1] = 0
data0[78,2] = 0.025
data0[78,3] = 1.57576
data0[78,4] = 0
data0[79,0] = 0.59596
data0[79,1] = 0
data0[79,2] = 0.025
data0[79,3] = 1.59596
data0[79,4] = 0
data0[80,0] = 0.616162
data0[80,1] = 0
data0[80,2] = 0.025
data0[80,3] = 1.61616
data0[80,4] = 0
data0[81,0] = 0.636364
data0[81,1] = 0
data0[81,2] = 0.025
data0[81,3] = 1.63636
data0[81,4] = 0
data0[82,0] = 0.656566
data0[82,1] = 0
data0[82,2] = 0.025
data0[82,3] = 1.65657
data0[82,4] = 0
data0[83,0] = 0.676768
data0[83,1] = 0
data0[83,2] = 0.025
data0[83,3] = 1.67677
data0[83,4] = 0
data0[84,0] = 0.69697
data0[84,1] = 0
data0[84,2] = 0.025
data0[84,3] = 1.69697
data0[84,4] = 0
data0[85,0] = 0.717172
data0[85,1] = 0
data0[85,2] = 0.025
data0[85,3] = 1.71717
data0[85,4] = 0
data0[86,0] = 0.737374
data0[86,1] = 0
data0[86,2] = 0.025
data0[86,3] = 1.73737
data0[86,4] = 0
data0[87,0] = 0.757576
data0[87,1] = 0
data0[87,2] = 0.025
data0[87,3] = 1.75758
data0[87,4] = 0
data0[88,0] = 0.777778
data0[88,1] = 0
data0[88,2] = 0.025
data0[88,3] = 1.77778
data0[88,4] = 0
data0[89,0] = 0.79798
data0[89,1] = 0
data0[89,2] = 0.025
data0[89,3] = 1.79798
data0[89,4] = 0
data0[90,0] = 0.818182
data0[90,1] = 0
data0[90,2] = 0.025
data0[90,3] = 1.81818
data0[90,4] = 0
data0[91,0] = 0.838384
data0[91,1] = 0
data0[91,2] = 0.025
data0[91,3] = 1.83838
data0[91,4] = 0
data0[92,0] = 0.858586
data0[92,1] = 0
data0[92,2] = 0.025
data0[92,3] = 1.85859
data0[92,4] = 0
data0[93,0] = 0.878788
data0[93,1] = 0
data0[93,2] = 0.025
data0[93,3] = 1.87879
data0[93,4] = 0
data0[94,0] = 0.89899
data0[94,1] = 0
data0[94,2] = 0.025
data0[94,3] = 1.89899
data0[94,4] = 0
data0[95,0] = 0.919192
data0[95,1] = 0
data0[95,2] = 0.025
data0[95,3] = 1.91919
data0[95,4] = 0
data0[96,0] = 0.939394
data0[96,1] = 0
data0[96,2] = 0.025
data0[96,3] = 1.93939
data0[96,4] = 0
data0[97,0] = 0.959596
data0[97,1] = 0
data0[97,2] = 0.025
data0[97,3] = 1.9596
data0[97,4] = 0
data0[98,0] = 0.979798
data0[98,1] = 0
data0[98,2] = 0.025
data0[98,3] = 1.9798
data0[98,4] = 0
data0[99,0] = 1
data0[99,1] = 0
data0[99,2] = 0.025
data0[99,3] = 2
data0[99,4] = 0
done=True


plt.figure(1)
plt.plot(data0[:,3],data0[:,4],label="phi")
plt.legend()
plt.grid(which='major')
plt.show()
