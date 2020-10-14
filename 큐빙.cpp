#include <iostream>
#include <algorithm>
using namespace std;

const int WW = 0;
const int YY = 1;
const int RR = 2;
const int OO = 3;
const int GG = 4;
const int BB = 5;

char COLOR[] = "wyrogb";
char cube[6][9];
char backup[6][9];

void init() {
  for (int f = 0; f < 6; ++f)
    for (int i = 0; i < 9; ++i)
      cube[f][i] = COLOR[f];
}

void cw(int face) {
  cube[face][0] = backup[face][6];
  cube[face][1] = backup[face][3];
  cube[face][2] = backup[face][0];
  cube[face][3] = backup[face][7];
  cube[face][4] = backup[face][4];
  cube[face][5] = backup[face][1];
  cube[face][6] = backup[face][8];
  cube[face][7] = backup[face][5];
  cube[face][8] = backup[face][2];
}

void rotate(char face) {
  for (int f = 0; f < 6; f++)
    for (int i = 0; i < 9; ++i)
      backup[f][i] = cube[f][i];

  if (face == 'F') {
    cube[WW][6] = backup[GG][6];
    cube[WW][7] = backup[GG][7];
    cube[WW][8] = backup[GG][8];
    cube[BB][6] = backup[WW][6];
    cube[BB][7] = backup[WW][7];
    cube[BB][8] = backup[WW][8];
    cube[YY][2] = backup[BB][6];
    cube[YY][1] = backup[BB][7];
    cube[YY][0] = backup[BB][8];
    cube[GG][6] = backup[YY][2];
    cube[GG][7] = backup[YY][1];
    cube[GG][8] = backup[YY][0];
    cw(RR);
  } else if (face == 'B') {
    cube[YY][6] = backup[GG][2];
    cube[YY][7] = backup[GG][1];
    cube[YY][8] = backup[GG][0];
    cube[BB][2] = backup[YY][6];
    cube[BB][1] = backup[YY][7];
    cube[BB][0] = backup[YY][8];
    cube[WW][2] = backup[BB][2];
    cube[WW][1] = backup[BB][1];
    cube[WW][0] = backup[BB][0];
    cube[GG][2] = backup[WW][2];
    cube[GG][1] = backup[WW][1];
    cube[GG][0] = backup[WW][0];
    cw(OO);
  } else if (face == 'U') {
    cube[OO][6] = backup[GG][8];
    cube[OO][7] = backup[GG][5];
    cube[OO][8] = backup[GG][2];
    cube[BB][0] = backup[OO][6];
    cube[BB][3] = backup[OO][7];
    cube[BB][6] = backup[OO][8];
    cube[RR][2] = backup[BB][0];
    cube[RR][1] = backup[BB][3];
    cube[RR][0] = backup[BB][6];
    cube[GG][8] = backup[RR][2];
    cube[GG][5] = backup[RR][1];
    cube[GG][2] = backup[RR][0];
    cw(WW);
  } else if (face == 'D') {
    cube[RR][6] = backup[GG][0];
    cube[RR][7] = backup[GG][3];
    cube[RR][8] = backup[GG][6];
    cube[BB][8] = backup[RR][6];
    cube[BB][5] = backup[RR][7];
    cube[BB][2] = backup[RR][8];
    cube[OO][2] = backup[BB][8];
    cube[OO][1] = backup[BB][5];
    cube[OO][0] = backup[BB][2];
    cube[GG][0] = backup[OO][2];
    cube[GG][3] = backup[OO][1];
    cube[GG][6] = backup[OO][0];
    cw(YY);
  } else if (face == 'R') {
    cube[OO][8] = backup[WW][8];
    cube[OO][5] = backup[WW][5];
    cube[OO][2] = backup[WW][2];
    cube[YY][8] = backup[OO][8];
    cube[YY][5] = backup[OO][5];
    cube[YY][2] = backup[OO][2];
    cube[RR][8] = backup[YY][8];
    cube[RR][5] = backup[YY][5];
    cube[RR][2] = backup[YY][2];
    cube[WW][8] = backup[RR][8];
    cube[WW][5] = backup[RR][5];
    cube[WW][2] = backup[RR][2];
    cw(BB);
  } else if (face == 'L') {
    cube[OO][0] = backup[YY][0];
    cube[OO][3] = backup[YY][3];
    cube[OO][6] = backup[YY][6];
    cube[WW][0] = backup[OO][0];
    cube[WW][3] = backup[OO][3];
    cube[WW][6] = backup[OO][6];
    cube[RR][0] = backup[WW][0];
    cube[RR][3] = backup[WW][3];
    cube[RR][6] = backup[WW][6];
    cube[YY][0] = backup[RR][0];
    cube[YY][3] = backup[RR][3];
    cube[YY][6] = backup[RR][6];
    cw(GG);
  }
}

int main() {
  int tc;
  cin >> tc;
  while (tc--) {
    int n;
    cin >> n;
    init();
    char buf[10];
    for (int i = 0; i < n; ++i) {
      cin >> buf;
      int k = 1;
      if (buf[1] == '-')
        k = 3;
      for (int j = 0; j < k; ++j)
        rotate(buf[0]);
    }
    for (int i = 0; i < 9; ++i) {
      if (i != 0 && i % 3 == 0)
        cout << endl;
      cout << cube[WW][i];
    }
    cout << endl;
  }

  return 0;
}
