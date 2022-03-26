0000	0
0001	1
0011	3
0111	7
1111	15
1000	8
1001	9
1011	11
1110	14
1100	12

double dirInside = -1;

#define BORDER_WHITE_LINE 400
#define BORDER_BLACK_LINE 780
#define BORDER_IS_IN_AIR 17
#define MULTI_AVG_LINE 0.2
#define QTY_LINE 20
const int P_LINE[] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9,
					 A10, A11, A16, A17, A20, A21, A22, A23, A24, A25};//上から見て前から時計回り
int valueLine[QTY_LINE];

int countIIA = 0;
#define MAX_CIIA 5
#define MULTI_AVG_DI 0.5
boolean isLineBlack[QTY_LINE];
boolean isLineWhite[QTY_LINE];
double prvDirInside = -1;

void setupLine() {

}

void calLine() {
	prvDirInside = dirInside;

	int qtyILB = 0;
	int qtyILW = 0;
	for(int numLine = 0; numLine < QTY_LINE; numLine ++) {
		//ライン読み取り
		valueLine[numLine] = analogRead(P_LINE[numLine]);
		isLineBlack[numLine] = valueLine[numLine] >= BORDER_BLACK_LINE;
		isLineWhite[numLine] = valueLine[numLine] <= BORDER_WHITE_LINE;
		if(isLineBlack[numLine]) {
			qtyILB ++;
		}
		if(isLineWhite[numLine]) {
			qtyILW ++;
		}
	}

	if(qtyILB >= BORDER_IS_IN_AIR) {
		//持ち上げられている
		countIIA ++;
		if(countIIA >= MAX_CIIA) {
			countIIA = MAX_CIIA;
			isOutsideLine = false;
			isHalfOut = false;
			dirInside = -1;
		}
	}else if(qtyILW <= 2) {
		//ライン上でない
		countIIA = 0;
		isOutsideLine = isHalfOut;
		dirInside = isOutsideLine ? prvDirInside : -1;
	}else {
		//ライン上
		countIIA = 0;
		isOutsideLine = false;
		//白の番号を調べる
		int posILW[qtyILW];
		int numILW = 0;
		for(int numLine = 0; numLine < QTY_LINE; numLine ++) {
			if(isLineWhite[numLine]) {
				posILW[numILW] = numLine;
				numILW ++;
			}
		}
		//白の間隔を調べる
		int intvLine[qtyILW];
		for(int numLine = 0; numLine < qtyILW - 1; numLine ++) {
			intvLine[numLine] = posILW[numLine + 1] - posILW[numLine];
		}
		intvLine[qtyILW - 1] = posILW[0] - posILW[qtyILW - 1] + QTY_LINE;
		//ラインの方向を調べる
		int maxIntvL = 0;
		int posMaxIntvL = 0;
		for(numILW = 0; numILW < qtyILW; numILW ++) {
			if(maxIntvL < intvLine[numILW]) {
				maxIntvL = intvLine[numILW];
				posMaxIntvL = numILW;
			}
		}
		double numDirInside = posILW[posMaxIntvL] + maxIntvL * 0.5;
		dirInside = simplifyDeg(numDirInside / QTY_LINE * 360);
		//前回と比較
		if(prvDirInside >= 0) {
			//半分以上外か
			isHalfOut = false;
			if(insideAngle(dirInside, prvDirInside + 110, prvDirInside + 250)) {
				dirInside = simplifyDeg(dirInside + 180);
				isHalfOut = true;
			}
			//平均値計算
			if(abs(dirInside - prvDirInside) <= 180) {
				dirInside = prvDirInside * MULTI_AVG_DI + dirInside * (1 - MULTI_AVG_DI);
			}else {
				dirInside = prvDirInside * MULTI_AVG_DI + dirInside * (1 - MULTI_AVG_DI)
								+ 360 * (dirInside >= prvDirInside ? MULTI_AVG_DI : 1 - MULTI_AVG_DI);
			}
			dirInside = simplifyDeg(dirInside);
		}
	}
}