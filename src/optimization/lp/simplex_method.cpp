
/*********************************************
 * 線形計画法（シンプレックス法）            *
 *********************************************/
#include <iostream>  // for cout
#include <stdio.h>   // for printf()
#include <vector>

using namespace std;

/*
 * 計算クラス
 */
class LP
{
  // 各種変数
  unsigned int rows, cols; // 係数行列のパラメタ
  unsigned int vars;         // 制約式の変数数
  vector<vector<double> > matrix; // 係数行列
  double min, p, d;
  unsigned int i, j, k, x, y; // indexを保存する
  int flag;

public:
  // rowConst: 制約の本数, varConst: 制約の変数数, ieqConst: 不等式標準形の制約式
  LP(unsigned int rowNum, unsigned int colNum, unsigned int varNum, vector<double> &objFunc, vector<vector<double> > &ieqConst);
  void Simplex();   // シンプレックス法
};

// rowConst: 制約の本数, varConst: 制約の変数数, ieqConst: 不等式標準形の制約式
LP::LP(unsigned int rowNum, unsigned int colNum, unsigned int varNum, vector<double> &objFunc, vector<vector<double> > &ieqConst)
{
  vars = varNum + rowNum;  // 実際の変数の数 = 制約の本数 + 変数の数
  rows = rowNum + 1;       // 係数行列の行数 = 制約の本数 + 1(目的関数)
  cols = vars + 1;           // 係数行列の列数 = 制約の本数 + 変数の数 + 1

  // 元の制約式の係数を代入
  for (i = 0; i < rowNum; ++i){
    for (j = 0; j < colNum; ++j){
      matrix[i][j] = ieqConst[i][j];
    }
  }

  // スラック変数の係数1.0として代入
  for (i = 0; i < rowNum; ++i){
    for (j = varNum; j < cols - 1; j ++){
        matrix[i][j] = 1.0;
    }
  }

  // 目的関数の係数を入れる
  for (i = 0; i < cols; ++ i){
    if(i < varNum){
      matrix[rows - 1][i] = objFunc[i];
    } else {
      matrix[rows - 1][i] = 0.0;
    }
  }

  // 定数項の値を代入
  for (i = 0; i < rows; i ++){
    if (i < rowNum){
      matrix[i][colNum - 1] = ieqConst[i][varNum];
    } else {
      matrix[i][colNum - 1] = 0.0;
    }
  }

}

/*
 * シンプレックス法
 */
void LP::Simplex()
{

  while (1) {
    // 列選択
    min = 0xffff;
    for (k = 0; k < cols - 1; k++) {
      if (matrix[rows - 1][k] < min) {
        min = matrix[rows - 1][k];
        y = k;
      }
    }
    if (min >= 0) break;

    // 行選択
    min = 0xffff;
    for (k = 0; k < rows - 1; k++) {
      p = matrix[k][cols - 1] / matrix[k][y];
      if (matrix[k][y] > 0 && p < min) {
        min = p;
        x = k;
      }
    }

    // ピボット係数
    p = matrix[x][y];

    // ピボット係数を p で除算
    for (k = 0; k < cols; k++)
      matrix[x][k] = matrix[x][k] / p;

    // ピボット列の掃き出し
    for (k = 0; k < rows; k++) {
      if (k != x) {
        d = matrix[k][y];
        for (j = 0; j < cols; j++)
          matrix[k][j] = matrix[k][j] - d * matrix[x][j];
      }
    }
  }

  // 結果出力
  for (k = 0; k < vars; k++) {
    flag = -1;
    for (j = 0; j < rows; j++) {
      // ==== 2016-11-14 UPDATE ===>
      // if (a[j][k] == 1) flag = j;
      if (matrix[j][k] == 1) {
        flag = j;
      } else if (flag != -1 && matrix[j][k] != 0) {
        flag = -1;
        break;
      }
      // <=== 2016-11-14 UPDATE ====
    }
    if (flag != -1)
      printf("x%d = %8.4f\n", k, matrix[flag][cols - 1]);
    else
      printf("x%d = %8.4f\n", k, 0.0);
  }
  printf("z  = %8.4f\n", matrix[rows - 1][cols - 1]);
}

/*
 * メイン処理
 */
int main()
{
  try
    {
      unsigned int rowNum, colNum, varNum, i, j;
      vector<vector<double>> ieqConst;
      vector<double> objFunc;
      double c;

      /* Get a parameter of problem*/
      cin >> rowNum >> colNum >> varNum;

      /* Get coefficients of objective function */
      objFunc = vector<double>(varNum, 0);
      for(i = 0; i < varNum; ++i){
        cin >> c;
        objFunc[i] = c;
        cout << c;
      }
      cout << "\n";

      /* Get coefficients of construction inequality*/
      ieqConst = vector<vector<double> >(rowNum, vector<double>(colNum, 0));
      for(i = 0; i < rowNum; ++i){
        for (j = 0; j < colNum; ++j){
          cin >> c;
          ieqConst[i][j] = c;
          cout << c << " ";
        }
        cout << "\n";
      }


      // 計算クラスインスタンス化
      LP objLP(rowNum, rowNum, varNum, objFunc, ieqConst);

      // シンプレックス法
      objLP.Simplex();
    }
  catch (...) {
    cout << "例外発生！" << endl;
    return -1;
  }

  // 正常終了
  return 0;
}
