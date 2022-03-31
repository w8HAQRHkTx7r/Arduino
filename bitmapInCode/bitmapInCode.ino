// This program takes a bitmap several bitmap arrays, each in a
// different color, and combines them onto an LED matrix

#define FASTLED_INTERNAL
#include <FastLED.h>

// LED Matrix parameters
#define MATRIX_HEIGHT 16
#define MATRIX_WIDTH  16
#define NUM_LEDS      MATRIX_HEIGHT * MATRIX_WIDTH

#define DATA_PIN     3
#define CLOCK_PIN   13
#define PAUSE       10
#define BRIGHTNESS  10
#define VOLTS        5
#define MAX_mAMPS  500

CRGB leds[NUM_LEDS];

CRGB testColor = CRGB::Black;  // Used for printing

CRGB pumpkin[] = {
  CRGB(255, 91, 0),
  CRGB::Green,
  CRGB::White,
  CRGB::Yellow,
};
CRGB batman[] = {
  CRGB(0, 91, 255),
  CRGB::Yellow,
};
CRGB egg[] {
  CRGB::White,
  CRGB(0, 79, 97),
  CRGB(255, 91,  0),
  CRGB(222, 57, 105),
  CRGB(209, 0, 0),
  CRGB(0, 96, 47),
  CRGB(0, 103, 0),
};

CRGB donald[] = {
  CRGB(111, 25, 122),  // purple background
  CRGB(51, 62, 122),   // blue at
  CRGB::White,         // white face
  CRGB(186, 191, 250), // lavender eyeball
  CRGB(239, 149, 65),  // orange bill
  CRGB(229, 108, 105), // salmon mouth
};

CRGB rabbit[] {
  CRGB::White,
  CRGB(103,115,141), //gray
  CRGB(255,160,160),  //pink
  CRGB(225,164,73),
};

CRGB Error[] = {
  CRGB(255, 91, 0),
  CRGB::Green,
  CRGB::White,
  CRGB::Yellow,
};

CRGB eyeColor = pumpkin[2];

void drawImage(char pattern, CRGB palette[]) {
  //leds[21]=g;leds[22]=g;
  //leds[41]=g;leds[40]=g;
  //leds[54]=g;leds[55]=g;leds[56]=g;
  //leds[75]=g;leds[74]=g;leds[73]=g;leds[72]=g;leds[71]=g;leds[70]=g;leds[69]=g;
  //leds[83]=o;leds[84]=o;leds[85]=o;leds[86]=g;leds[87]=o;leds[88]=o;leds[89]=g;leds[90]=o;leds[91]=o;
  //leds[109]=o;leds[108]=o;leds[107]=o;leds[106]=o;leds[105]=o;leds[104]=o;leds[103]=o;leds[102]=o;leds[101]=o;leds[100]=o;leds[99]=o;
  //leds[113]=o;leds[114]=o;leds[115]=o;leds[116]=w;leds[118]=o;leds[119]=o;leds[120]=o;leds[121]=w;leds[123]=o;leds[124]=o;leds[125]=o;
  //leds[142]=o;leds[141]=o;leds[140]=o;leds[137]=o;leds[136]=o;leds[135]=o;leds[132]=o;leds[131]=o;leds[130]=o;
  //leds[145]=o;leds[146]=o;leds[147]=o;leds[148]=o;leds[149]=o;leds[150]=o;leds[152]=o;leds[153]=o;leds[154]=o;leds[155]=o;leds[156]=o;leds[157]=o;
  //leds[174]=o;leds[173]=o;leds[172]=o;leds[171]=o;leds[170]=o;leds[166]=o;leds[165]=o;leds[164]=o;leds[163]=o;leds[162]=o;
  //leds[177]=o;leds[178]=o;leds[179]=o;leds[181]=o;leds[182]=o;leds[183]=o;leds[184]=o;leds[185]=o;leds[187]=o;leds[188]=o;leds[189]=o;
  //leds[205]=o;leds[204]=o;leds[203]=o;leds[201]=y;leds[199]=y;leds[197]=o;leds[196]=o;leds[195]=o;
  //leds[211]=o;leds[212]=o;leds[213]=o;leds[214]=o;leds[215]=o;leds[216]=o;leds[217]=o;leds[218]=o;leds[219]=o;
  //leds[235]=o;leds[234]=o;leds[233]=o;leds[232]=o;leds[231]=o;leds[230]=o;leds[229]=o;
  switch (pattern) {
    case 'p': // pumpkin
      leds[21] = palette[1]; leds[22] = palette[1];
      leds[41] = palette[1]; leds[40] = palette[1];
      leds[54] = palette[1]; leds[55] = palette[1]; leds[56] = palette[1];
      leds[75] = palette[1]; leds[74] = palette[1]; leds[73] = palette[1]; leds[72] = palette[1]; leds[71] = palette[1]; leds[70] = palette[1]; leds[69] = palette[1];
      leds[83] = palette[0]; leds[84] = palette[0]; leds[85] = palette[0]; leds[86] = palette[1]; leds[87] = palette[0]; leds[88] = palette[0]; leds[89] = palette[1]; leds[90] = palette[0]; leds[91] = palette[0];
      leds[109] = palette[0]; leds[108] = palette[0]; leds[107] = palette[0]; leds[106] = palette[0]; leds[105] = palette[0]; leds[104] = palette[0]; leds[103] = palette[0]; leds[102] = palette[0]; leds[101] = palette[0]; leds[100] = palette[0]; leds[99] = palette[0];
      leds[113] = palette[0]; leds[114] = palette[0]; leds[115] = palette[0]; leds[116] = palette[2]; leds[118] = palette[0]; leds[119] = palette[0]; leds[120] = palette[0]; leds[121] = palette[2]; leds[123] = palette[0]; leds[124] = palette[0]; leds[125] = palette[0];
      leds[142] = palette[0]; leds[141] = palette[0]; leds[140] = palette[0]; leds[137] = palette[0]; leds[136] = palette[0]; leds[135] = palette[0]; leds[132] = palette[0]; leds[131] = palette[0]; leds[130] = palette[0];
      leds[145] = palette[0]; leds[146] = palette[0]; leds[147] = palette[0]; leds[148] = palette[0]; leds[149] = palette[0]; leds[150] = palette[0]; leds[152] = palette[0]; leds[153] = palette[0]; leds[154] = palette[0]; leds[155] = palette[0]; leds[156] = palette[0]; leds[157] = palette[0];
      leds[174] = palette[0]; leds[173] = palette[0]; leds[172] = palette[0]; leds[171] = palette[0]; leds[170] = palette[0]; leds[166] = palette[0]; leds[165] = palette[0]; leds[164] = palette[0]; leds[163] = palette[0]; leds[162] = palette[0];
      leds[177] = palette[0]; leds[178] = palette[0]; leds[179] = palette[0]; leds[181] = palette[0]; leds[182] = palette[0]; leds[183] = palette[0]; leds[184] = palette[0]; leds[185] = palette[0]; leds[187] = palette[0]; leds[188] = palette[0]; leds[189] = palette[0];
      leds[205] = palette[0]; leds[204] = palette[0]; leds[203] = palette[0]; leds[201] = palette[3]; leds[199] = palette[3]; leds[197] = palette[0]; leds[196] = palette[0]; leds[195] = palette[0];
      leds[211] = palette[0]; leds[212] = palette[0]; leds[213] = palette[0]; leds[214] = palette[0]; leds[215] = palette[0]; leds[216] = palette[0]; leds[217] = palette[0]; leds[218] = palette[0]; leds[219] = palette[0];
      leds[235] = palette[0]; leds[234] = palette[0]; leds[233] = palette[0]; leds[232] = palette[0]; leds[231] = palette[0]; leds[230] = palette[0]; leds[229] = palette[0];
      break;
    case 'b': // batman
      leds[15] = palette[0]; leds[14] = palette[0]; leds[13] = palette[0]; leds[12] = palette[0]; leds[11] = palette[0]; leds[10] = palette[0]; leds[9] = palette[0]; leds[8] = palette[0]; leds[7] = palette[0]; leds[6] = palette[0]; leds[5] = palette[0]; leds[4] = palette[0]; leds[3] = palette[0]; leds[2] = palette[0]; leds[1] = palette[0]; leds[0] = palette[0];
      leds[16] = palette[0]; leds[17] = palette[0]; leds[18] = palette[0]; leds[19] = palette[0]; leds[20] = palette[0]; leds[21] = palette[0]; leds[22] = palette[0]; leds[23] = palette[0]; leds[24] = palette[0]; leds[25] = palette[0]; leds[26] = palette[0]; leds[27] = palette[0]; leds[28] = palette[0]; leds[29] = palette[0]; leds[30] = palette[0]; leds[31] = palette[0];
      leds[47] = palette[0]; leds[46] = palette[0]; leds[45] = palette[0]; leds[44] = palette[0]; leds[43] = palette[0]; leds[42] = palette[1]; leds[41] = palette[1]; leds[40] = palette[1]; leds[39] = palette[1]; leds[38] = palette[1]; leds[37] = palette[1]; leds[36] = palette[1]; leds[35] = palette[0]; leds[34] = palette[0]; leds[33] = palette[0]; leds[32] = palette[0];
      leds[48] = palette[0]; leds[49] = palette[0]; leds[50] = palette[0]; leds[51] = palette[0]; leds[52] = palette[1]; leds[53] = palette[1]; leds[54] = palette[1]; leds[55] = palette[1]; leds[56] = palette[1]; leds[57] = palette[1]; leds[58] = palette[1]; leds[59] = palette[1]; leds[60] = palette[1]; leds[61] = palette[0]; leds[62] = palette[0]; leds[63] = palette[0];
      leds[79] = palette[0]; leds[78] = palette[0]; leds[77] = palette[0]; leds[76] = palette[1]; leds[75] = palette[1]; leds[74] = palette[1]; leds[73] = palette[1]; leds[72] = palette[1]; leds[71] = palette[1]; leds[70] = palette[1]; leds[69] = palette[1]; leds[68] = palette[1]; leds[67] = palette[1]; leds[66] = palette[1]; leds[65] = palette[0]; leds[64] = palette[0];
      leds[80] = palette[0]; leds[81] = palette[0]; leds[82] = palette[0]; leds[83] = palette[1]; leds[84] = palette[1]; leds[85] = palette[1]; leds[86] = palette[1]; leds[87] = palette[1]; leds[88] = palette[1]; leds[89] = palette[1]; leds[90] = palette[1]; leds[91] = palette[1]; leds[92] = palette[1]; leds[93] = palette[1]; leds[94] = palette[0]; leds[95] = palette[0];
      leds[111] = palette[0]; leds[110] = palette[0]; leds[109] = palette[0]; leds[108] = palette[1]; leds[107] = palette[1]; leds[106] = palette[1]; leds[105] = palette[1]; leds[104] = palette[1]; leds[103] = palette[1]; leds[102] = palette[1]; leds[101] = palette[1]; leds[100] = palette[1]; leds[99] = palette[1]; leds[98] = palette[1]; leds[97] = palette[0]; leds[96] = palette[0];
      leds[115] = palette[1]; leds[116] = palette[1]; leds[118] = palette[1]; leds[120] = palette[1]; leds[121] = palette[1]; leds[125] = palette[1]; leds[126] = palette[0]; leds[127] = palette[0];
      leds[143] = palette[0]; leds[140] = palette[1]; leds[139] = palette[1]; leds[135] = palette[1]; leds[134] = palette[1]; leds[131] = palette[1]; leds[130] = palette[1]; leds[129] = palette[0]; leds[128] = palette[0];
      leds[144] = palette[0]; leds[145] = palette[0]; leds[155] = palette[1]; leds[156] = palette[1]; leds[157] = palette[1]; leds[158] = palette[0]; leds[159] = palette[0];
      leds[175] = palette[0]; leds[174] = palette[0]; leds[165] = palette[1]; leds[164] = palette[1]; leds[163] = palette[1]; leds[162] = palette[1]; leds[161] = palette[0]; leds[160] = palette[0];
      leds[176] = palette[0]; leds[177] = palette[0]; leds[178] = palette[0]; leds[186] = palette[1]; leds[187] = palette[1]; leds[188] = palette[1]; leds[189] = palette[0]; leds[190] = palette[0]; leds[191] = palette[0];
      leds[207] = palette[0]; leds[206] = palette[0]; leds[205] = palette[0]; leds[204] = palette[0]; leds[203] = palette[0]; leds[199] = palette[1]; leds[198] = palette[1]; leds[197] = palette[1]; leds[196] = palette[1]; leds[195] = palette[0]; leds[194] = palette[0]; leds[193] = palette[0]; leds[192] = palette[0];
      leds[208] = palette[0]; leds[209] = palette[0]; leds[210] = palette[0]; leds[211] = palette[0]; leds[212] = palette[0]; leds[213] = palette[0]; leds[215] = palette[0]; leds[216] = palette[0]; leds[217] = palette[0]; leds[218] = palette[0]; leds[219] = palette[0]; leds[220] = palette[0]; leds[221] = palette[0]; leds[222] = palette[0]; leds[223] = palette[0];
      leds[239] = palette[0]; leds[238] = palette[0]; leds[237] = palette[0]; leds[236] = palette[0]; leds[235] = palette[0]; leds[234] = palette[0]; leds[233] = palette[0]; leds[232] = palette[0]; leds[231] = palette[0]; leds[230] = palette[0]; leds[229] = palette[0]; leds[228] = palette[0]; leds[227] = palette[0]; leds[226] = palette[0]; leds[225] = palette[0]; leds[224] = palette[0];
      leds[240] = palette[0]; leds[241] = palette[0]; leds[242] = palette[0]; leds[243] = palette[0]; leds[244] = palette[0]; leds[245] = palette[0]; leds[246] = palette[0]; leds[247] = palette[0]; leds[248] = palette[0]; leds[249] = palette[0]; leds[250] = palette[0]; leds[251] = palette[0]; leds[252] = palette[0]; leds[253] = palette[0]; leds[254] = palette[0]; leds[255] = palette[0];
      break;
    case 'e': // egg
      leds[15] = palette[1]; leds[14] = palette[1]; leds[13] = palette[1]; leds[12] = palette[1]; leds[11] = palette[1]; leds[10] = palette[1]; leds[5] = palette[1]; leds[4] = palette[1]; leds[3] = palette[1]; leds[2] = palette[1]; leds[1] = palette[1]; leds[0] = palette[1];
      leds[16] = palette[1]; leds[17] = palette[1]; leds[18] = palette[1]; leds[19] = palette[1]; leds[20] = palette[1]; leds[22] = palette[0]; leds[23] = palette[0]; leds[24] = palette[0]; leds[25] = palette[0]; leds[27] = palette[1]; leds[28] = palette[1]; leds[29] = palette[1]; leds[30] = palette[1]; leds[31] = palette[1];
      leds[47] = palette[1]; leds[46] = palette[1]; leds[45] = palette[1]; leds[44] = palette[1]; leds[42] = palette[2]; leds[41] = palette[0]; leds[40] = palette[0]; leds[39] = palette[0]; leds[38] = palette[3]; leds[37] = palette[3]; leds[35] = palette[1]; leds[34] = palette[1]; leds[33] = palette[1]; leds[32] = palette[1];
      leds[48] = palette[1]; leds[49] = palette[1]; leds[50] = palette[1]; leds[52] = palette[2]; leds[53] = palette[2]; leds[54] = palette[2]; leds[55] = palette[0]; leds[56] = palette[0]; leds[57] = palette[3]; leds[58] = palette[3]; leds[59] = palette[3]; leds[61] = palette[1]; leds[62] = palette[1]; leds[63] = palette[1];
      leds[79] = palette[1]; leds[78] = palette[1]; leds[77] = palette[1]; leds[75] = palette[2]; leds[74] = palette[2]; leds[73] = palette[2]; leds[72] = palette[0]; leds[71] = palette[0]; leds[70] = palette[3]; leds[69] = palette[3]; leds[68] = palette[3]; leds[66] = palette[1]; leds[65] = palette[1]; leds[64] = palette[1];
      leds[80] = palette[1]; leds[81] = palette[1]; leds[83] = palette[2]; leds[84] = palette[2]; leds[85] = palette[2]; leds[86] = palette[2]; leds[87] = palette[0]; leds[88] = palette[0]; leds[89] = palette[0]; leds[90] = palette[3]; leds[91] = palette[3]; leds[92] = palette[3]; leds[94] = palette[1]; leds[95] = palette[1];
      leds[111] = palette[1]; leds[110] = palette[1]; leds[108] = palette[2]; leds[107] = palette[2]; leds[106] = palette[2]; leds[105] = palette[0]; leds[104] = palette[0]; leds[103] = palette[0]; leds[102] = palette[0]; leds[101] = palette[0]; leds[100] = palette[0]; leds[99] = palette[0]; leds[97] = palette[1]; leds[96] = palette[1];
      leds[112] = palette[1]; leds[114] = palette[0]; leds[115] = palette[0]; leds[116] = palette[0]; leds[117] = palette[0]; leds[118] = palette[0]; leds[119] = palette[5]; leds[120] = palette[5]; leds[121] = palette[5]; leds[122] = palette[0]; leds[123] = palette[0]; leds[124] = palette[0]; leds[125] = palette[0]; leds[127] = palette[1];
      leds[143] = palette[1]; leds[141] = palette[0]; leds[140] = palette[0]; leds[139] = palette[0]; leds[138] = palette[0]; leds[137] = palette[5]; leds[136] = palette[5]; leds[135] = palette[5]; leds[134] = palette[5]; leds[133] = palette[5]; leds[132] = palette[0]; leds[131] = palette[0]; leds[130] = palette[0]; leds[128] = palette[1];
      leds[144] = palette[1]; leds[146] = palette[6]; leds[147] = palette[6]; leds[148] = palette[0]; leds[149] = palette[0]; leds[150] = palette[5]; leds[151] = palette[5]; leds[152] = palette[5]; leds[153] = palette[5]; leds[154] = palette[5]; leds[155] = palette[0]; leds[156] = palette[0]; leds[157] = palette[0]; leds[159] = palette[1];
      leds[175] = palette[1]; leds[173] = palette[6]; leds[172] = palette[6]; leds[171] = palette[6]; leds[170] = palette[0]; leds[169] = palette[5]; leds[168] = palette[5]; leds[167] = palette[5]; leds[166] = palette[5]; leds[165] = palette[5]; leds[164] = palette[0]; leds[163] = palette[4]; leds[162] = palette[4]; leds[160] = palette[1];
      leds[176] = palette[1]; leds[177] = palette[1]; leds[179] = palette[6]; leds[180] = palette[6]; leds[181] = palette[0]; leds[182] = palette[0]; leds[183] = palette[5]; leds[184] = palette[5]; leds[185] = palette[5]; leds[186] = palette[0]; leds[187] = palette[4]; leds[188] = palette[4]; leds[190] = palette[1]; leds[191] = palette[1];
      leds[207] = palette[1]; leds[206] = palette[1]; leds[204] = palette[6]; leds[203] = palette[6]; leds[202] = palette[0]; leds[201] = palette[0]; leds[200] = palette[0]; leds[199] = palette[0]; leds[198] = palette[0]; leds[197] = palette[0]; leds[196] = palette[4]; leds[195] = palette[4]; leds[193] = palette[1]; leds[192] = palette[1];
      leds[208] = palette[1]; leds[209] = palette[1]; leds[210] = palette[1]; leds[212] = palette[0]; leds[213] = palette[0]; leds[214] = palette[0]; leds[215] = palette[0]; leds[216] = palette[0]; leds[217] = palette[0]; leds[218] = palette[0]; leds[219] = palette[4]; leds[221] = palette[1]; leds[222] = palette[1]; leds[223] = palette[1];
      leds[239] = palette[1]; leds[238] = palette[1]; leds[237] = palette[1]; leds[236] = palette[1]; leds[233] = palette[0]; leds[232] = palette[0]; leds[231] = palette[0]; leds[230] = palette[0]; leds[227] = palette[1]; leds[226] = palette[1]; leds[225] = palette[1]; leds[224] = palette[1];
      leds[240] = palette[1]; leds[241] = palette[1]; leds[242] = palette[1]; leds[243] = palette[1]; leds[244] = palette[1]; leds[245] = palette[1]; leds[250] = palette[1]; leds[251] = palette[1]; leds[252] = palette[1]; leds[253] = palette[1]; leds[254] = palette[1]; leds[255] = palette[1];
      break;
    case 'r': // rabbit
leds[15]=palette[0];leds[14]=palette[0];leds[13]=palette[0];leds[12]=palette[0];leds[11]=palette[0];leds[10]=palette[0];leds[9]=palette[0];leds[8]=palette[0];leds[7]=palette[0];leds[6]=palette[0];leds[5]=palette[0];leds[4]=palette[0];leds[3]=palette[0];leds[2]=palette[0];leds[1]=palette[0];leds[0]=palette[0];
leds[16]=palette[0];leds[17]=palette[0];leds[18]=palette[0];leds[21]=palette[0];leds[22]=palette[0];leds[23]=palette[0];leds[24]=palette[0];leds[25]=palette[0];leds[26]=palette[0];leds[27]=palette[0];leds[28]=palette[0];leds[31]=palette[0];
leds[47]=palette[0];leds[46]=palette[0];leds[44]=palette[3];leds[43]=palette[3];leds[41]=palette[0];leds[40]=palette[0];leds[39]=palette[0];leds[38]=palette[0];leds[37]=palette[0];leds[36]=palette[0];leds[34]=palette[3];leds[33]=palette[3];
leds[48]=palette[0];leds[50]=palette[3];leds[51]=palette[2];leds[52]=palette[3];leds[54]=palette[0];leds[55]=palette[0];leds[56]=palette[0];leds[57]=palette[0];leds[58]=palette[0];leds[60]=palette[3];leds[61]=palette[2];leds[62]=palette[3];
leds[79]=palette[0];leds[77]=palette[3];leds[76]=palette[2];leds[75]=palette[2];leds[74]=palette[3];leds[72]=palette[0];leds[71]=palette[0];leds[70]=palette[0];leds[68]=palette[3];leds[67]=palette[2];leds[66]=palette[2];leds[65]=palette[3];
leds[80]=palette[0];leds[81]=palette[0];leds[83]=palette[3];leds[84]=palette[2];leds[85]=palette[2];leds[87]=palette[0];leds[88]=palette[0];leds[89]=palette[0];leds[91]=palette[3];leds[92]=palette[2];leds[93]=palette[3];leds[95]=palette[0];
leds[111]=palette[0];leds[110]=palette[0];leds[109]=palette[0];leds[107]=palette[3];leds[106]=palette[2];leds[105]=palette[3];leds[101]=palette[3];leds[100]=palette[2];leds[99]=palette[3];leds[97]=palette[0];leds[96]=palette[0];
leds[112]=palette[0];leds[113]=palette[0];leds[114]=palette[0];leds[115]=palette[0];leds[117]=palette[3];leds[118]=palette[3];leds[119]=palette[3];leds[120]=palette[3];leds[121]=palette[3];leds[122]=palette[3];leds[123]=palette[3];leds[125]=palette[0];leds[126]=palette[0];leds[127]=palette[0];
leds[143]=palette[0];leds[142]=palette[0];leds[141]=palette[0];leds[139]=palette[3];leds[138]=palette[3];leds[137]=palette[3];leds[136]=palette[3];leds[135]=palette[3];leds[134]=palette[3];leds[133]=palette[3];leds[132]=palette[3];leds[130]=palette[0];leds[129]=palette[0];leds[128]=palette[0];
leds[144]=palette[0];leds[145]=palette[0];leds[147]=palette[3];leds[148]=palette[3];leds[150]=palette[3];leds[151]=palette[3];leds[152]=palette[3];leds[153]=palette[3];leds[155]=palette[3];leds[156]=palette[3];leds[158]=palette[0];leds[159]=palette[0];
leds[175]=palette[0];leds[174]=palette[0];leds[172]=palette[3];leds[171]=palette[3];leds[169]=palette[3];leds[168]=palette[3];leds[167]=palette[3];leds[166]=palette[3];leds[164]=palette[3];leds[163]=palette[3];leds[161]=palette[0];leds[160]=palette[0];
leds[176]=palette[0];leds[177]=palette[0];leds[179]=palette[3];leds[180]=palette[2];leds[181]=palette[2];leds[182]=palette[3];leds[183]=palette[3];leds[184]=palette[3];leds[185]=palette[3];leds[186]=palette[2];leds[187]=palette[2];leds[188]=palette[3];leds[190]=palette[0];leds[191]=palette[0];
leds[207]=palette[0];leds[203]=palette[3];leds[202]=palette[3];leds[201]=palette[3];leds[198]=palette[3];leds[197]=palette[3];leds[196]=palette[3];leds[192]=palette[0];
leds[209]=palette[3];leds[210]=palette[3];leds[212]=palette[3];leds[213]=palette[3];leds[214]=palette[3];leds[215]=palette[3];leds[216]=palette[3];leds[217]=palette[3];leds[218]=palette[3];leds[219]=palette[3];leds[221]=palette[3];leds[222]=palette[3];
leds[238]=palette[3];leds[237]=palette[3];leds[226]=palette[3];leds[225]=palette[3];
leds[244]=palette[3];leds[245]=palette[3];leds[246]=palette[3];leds[247]=palette[3];leds[248]=palette[3];leds[249]=palette[3];leds[250]=palette[3];leds[251]=palette[3];
      break;
    default: // 404 file not found
      leds[19] = CRGB::Red; leds[22] = CRGB::Red; leds[23] = CRGB::Red; leds[24] = CRGB::Red; leds[30] = CRGB::Red;
      leds[45] = CRGB::Red; leds[44] = CRGB::Red; leds[42] = CRGB::Red; leds[38] = CRGB::Red; leds[34] = CRGB::Red; leds[33] = CRGB::Red;
      leds[49] = CRGB::Red; leds[51] = CRGB::Red; leds[53] = CRGB::Red; leds[54] = CRGB::Red; leds[57] = CRGB::Red; leds[60] = CRGB::Red; leds[62] = CRGB::Red;
      leds[79] = CRGB::Red; leds[76] = CRGB::Red; leds[74] = CRGB::Red; leds[72] = CRGB::Red; leds[70] = CRGB::Red; leds[68] = CRGB::Red; leds[65] = CRGB::Red;
      leds[80] = CRGB::Red; leds[81] = CRGB::Red; leds[82] = CRGB::Red; leds[83] = CRGB::Red; leds[85] = CRGB::Red; leds[88] = CRGB::Red; leds[89] = CRGB::Red; leds[91] = CRGB::Red; leds[92] = CRGB::Red; leds[93] = CRGB::Red; leds[94] = CRGB::Red;
      leds[108] = CRGB::Red; leds[106] = CRGB::Red; leds[102] = CRGB::Red; leds[97] = CRGB::Red;
      leds[115] = CRGB::Red; leds[118] = CRGB::Red; leds[119] = CRGB::Red; leds[120] = CRGB::Red; leds[126] = CRGB::Red;

      leds[148] = CRGB::Red; leds[154] = CRGB::Red;
      leds[172] = CRGB::Red; leds[169] = CRGB::Red; leds[167] = CRGB::Red; leds[164] = CRGB::Red;
      leds[179] = CRGB::Red; leds[187] = CRGB::Red;
      leds[204] = CRGB::Red; leds[201] = CRGB::Red; leds[200] = CRGB::Red; leds[199] = CRGB::Red; leds[196] = CRGB::Red;
      leds[211] = CRGB::Red; leds[213] = CRGB::Red; leds[217] = CRGB::Red; leds[219] = CRGB::Red;
      leds[236] = CRGB::Red; leds[228] = CRGB::Red;
      leds[244] = CRGB::Red; leds[250] = CRGB::Red;
  }

}

void printLEDMatrix() {
  int x = MATRIX_WIDTH - 1; // index of leftmost pixel in the 0th row
  int y = ((MATRIX_WIDTH - 1) * MATRIX_WIDTH) - 1; // index of pixel to the left of the rightmost
  for (int start = x; start <= y; start += MATRIX_WIDTH * 2) {
    for (int p = start; p >= start - (MATRIX_WIDTH - 1); p--) {
      if (leds[p] != testColor) {
        Serial.print("@");
      } else {
        Serial.print(".");
      }
      Serial.print(" ");
    }
    Serial.println(" ");
    for (int p = start + 1; p <= start + 1 + (MATRIX_WIDTH - 1); p++) {
      if (leds[p] != testColor) {
        Serial.print("@");
      } else {
        Serial.print(".");
      }
      Serial.print(" ");
    }
    Serial.println(" ");
  }
  delay(50);
}

// Convert from (0,0) in upper left to matrix index
// Used when turning on an individual (random) pixel
int mapScreenToMatrix(int row, int col) {
  // Switch from increasing left to right into
  // increasing right to left for even numbered rows
  // Then compute a linear pixel offset
  //  int newCol = (row % 2 == 0) ? newCol = (MATRIX_WIDTH - 1) - col : newCol = col; This was flipping the bitmap around the vertical axis
  int newCol = (row % 2 == 0) ? newCol = col : newCol = (MATRIX_WIDTH - 1) - col;
  return row * MATRIX_WIDTH + newCol;
}
void moveEyes() {
  // Black left eye
  leds[mapScreenToMatrix(7, 5)] = CRGB::Black;
  leds[mapScreenToMatrix(7, 6)] = CRGB::Black;
  leds[mapScreenToMatrix(8, 5)] = CRGB::Black;
  leds[mapScreenToMatrix(8, 6)] = CRGB::Black;
  // Black right eye
  leds[mapScreenToMatrix(7, 10)] = CRGB::Black;
  leds[mapScreenToMatrix(7, 11)] = CRGB::Black;
  leds[mapScreenToMatrix(8, 10)] = CRGB::Black;
  leds[mapScreenToMatrix(8, 11)] = CRGB::Black;
  // Random eye direction
  int randrow = random(7, 9);
  int randcol = random(5, 7);
  leds[mapScreenToMatrix(randrow, randcol)] = eyeColor;
  leds[mapScreenToMatrix(randrow, randcol + 5)] = eyeColor;
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_mAMPS);
  set_max_power_indicator_LED(LED_BUILTIN);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  drawImage('p', pumpkin);
  FastLED.show();
}

void loop() {
  FastLED.clear();
  drawImage('p', pumpkin);
  moveEyes();
  FastLED.show();
  delay(random(200, 600));
  delay(2000);

  FastLED.clear();
  drawImage('b', batman);
  FastLED.show();
  delay(2000);

  FastLED.clear();
  drawImage('x', batman);
  FastLED.show();
  delay(2000);

  FastLED.clear();
  drawImage('e', egg);
  FastLED.show();
  delay(2000);

  FastLED.clear();
  drawImage('r', rabbit);
  FastLED.show();
  delay(2000);
}
