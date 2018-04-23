
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
  int rowNum, colNum; // 係数行列のパラメタ
  int varNum;         // 制約式の変数数
  vector<vector<double> > matConst; // 係数行列
  double min, p, d;
  int i, j, k, x, y; // indexを保存する
  int flag;

public:
  // rowConst: 制約の本数, varConst: 制約の変数数, ieqConst: 不等式標準形の制約式
  LP(int rowConst, int varConst, vector<vector<double> > ieqConst)
  {
    varNum = varConst + rowConst;     // 実際の変数の数 = 制約の本数 + 変数の数
    rowNum = rowConst + 1;            // 係数行列の行数 = 制約の本数 + 1(目的関数)
    colNum = varConst + rowConst + 1; // 係数行列の列数 = 制約の本数 + 変数の数 + 1

    // 元の制約式の係数を代入
    for (i = 0; i < varConst; ++i){
      for (j = 0; j < colNum; ++j){
        matConst[i][j] = ieqConst[i][j];
      }
    }
    // スラック変数の係数1.0として代入
    for (i = 0; i < rowNum; i ++){
      if (i < rowNum - 1){
        for (j = varConst; j < colNum - 1; j ++){
          matConst[i][j] = 1.0;
        }
      } else {
        matConst[i][j] = 0.0;
      }
    }
    // 定数項の値を代入
    for (i = 0; i < rowNum; i ++){
      if (i < rowNum - 1){
        matConst[i][colNum - 1] = ieqConst[i][varConst];
      } else {
        matConst[i][colNum - 1] = 0.0;
      }
    }
  }

  void Calc();   // 線形計画法
};

/*
 * 線形計画法
 */
void LP::Calc()
{

  while (1) {
    // 列選択
    min = 0xffff;
    for (k = 0; k < colNum - 1; k++) {
      if (matConst[rowNum - 1][k] < min) {
        min = matConst[rowNum - 1][k];
        y = k;
      }
    }
    if (min >= 0) break;

    // 行選択
    min = 0xffff;
    for (k = 0; k < rowNum - 1; k++) {
      p = matConst[k][colNum - 1] / matConst[k][y];
      if (matConst[k][y] > 0 && p < min) {
        min = p;
        x = k;
      }
    }

    // ピボット係数
    p = matConst[x][y];

    // ピボット係数を p で除算
    for (k = 0; k < colNum; k++)
      matConst[x][k] = matConst[x][k] / p;

    // ピボット列の掃き出し
    for (k = 0; k < rowNum; k++) {
      if (k != x) {
        d = matConst[k][y];
        for (j = 0; j < colNum; j++)
          matConst[k][j] = matConst[k][j] - d * matConst[x][j];
      }
    }
  }

  // 結果出力
  for (k = 0; k < varNum; k++) {
    flag = -1;
    for (j = 0; j < rowNum; j++) {
      // ==== 2016-11-14 UPDATE ===>
      // if (a[j][k] == 1) flag = j;
      if (matConst[j][k] == 1) {
        flag = j;
      } else if (flag != -1 && matConst[j][k] != 0) {
        flag = -1;
        break;
      }
      // <=== 2016-11-14 UPDATE ====
    }
    if (flag != -1)
      printf("x%d = %8.4f\n", k, matConst[flag][colNum - 1]);
    else
      printf("x%d = %8.4f\n", k, 0.0);
  }
  printf("z  = %8.4f\n", matConst[rowNum - 1][colNum - 1]);
}

/*
 * メイン処理
 */
int main()
{
  try
    {
      int N, M;
      vector<vector<double> > ieqConst;
      cin >> N >> M;
      cout << N << " " << M << "\n";
      ieqConst = vector<vector<double> >(N, vector<double>(M, 0));

      for(int i = 0; i < N; ++i){
        cout << "[" << i << "]";
        for (int j = 0; j < M; ++j){
          cin >> ieqConst[i][j];
          cout << ieqConst[i][j] << " ";
        }
      }

      cout << "hello";

      for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
          cout << ieqConst[i][j]<< " ";
        }
      }

      // 計算クラスインスタンス化
      LP objLP(N, M, ieqConst);
      // 線形計画法
      objLP.Calc();
    }
  catch (...) {
    cout << "例外発生！" << endl;
    return -1;
  }

  // 正常終了
  return 0;
}
