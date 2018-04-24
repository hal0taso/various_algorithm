
/*********************************************
 * 線形計画法（シンプレックス法）            *
 *********************************************/
#include <iostream>  // for cout
#include <stdio.h>   // for printf()
#include <vector>
#include <iomanip>

using namespace std;

/*
 * 計算クラス
 */
class LP{

  // 各種変数
  unsigned int rows, cols; // 係数行列のパラメタ
  unsigned int vars;         // 制約式の変数数
  vector<vector<double> > matrix; // 係数行列
  double min, p, d;

public:

  // rowConst: 制約の本数, varConst: 制約の変数数, ieqConst: 不等式標準形の制約式
  LP(unsigned int rowNum, unsigned int colNum, unsigned int varNum, vector<double> &objFunc, vector<vector<double> > &ieqConst);
  void Simplex();   // シンプレックス法
  void Disp(bool flag);

};

// rowConst: 制約の本数, varConst: 制約の変数数, ieqConst: 不等式標準形の制約式
LP::LP(unsigned int rowNum, unsigned int colNum, unsigned int varNum, vector<double> &objFunc, vector<vector<double> > &ieqConst){

  unsigned int i, j; // indexを保存する
  vars = varNum + rowNum; // 実際の変数の数 = 制約の本数 + 変数の数
  rows = rowNum + 1; // 係数行列の行数 = 制約の本数 + 1(目的関数)
  cols = vars + 1; // 係数行列の列数 = 制約の本数 + 変数の数 + 1

  matrix = vector<vector<double> >(rows, vector<double>(cols, 0.0));

  // 元の制約式の係数を代入
  for (i = 0; i < rowNum; ++i){
    for (j = 0; j < varNum; ++j){
      matrix[i][j] = ieqConst[i][j];
    }
  }

  // 定数項の値を代入
  for (i = 0; i < rowNum; ++i){
    matrix[i][cols - 1] = ieqConst[i][varNum];
  }

  // スラック変数の係数1.0として代入
  for (i = 0; i < rowNum; ++i){
    for (j = varNum; j < cols - 1; j ++){
      if (i == j - varNum){
        matrix[i][j] = 1.0;
      }
    }
  }

  // 目的関数の係数を入れる
  for (i = 0; i < cols; ++ i){
    if(i < varNum){
      matrix[rows - 1][i] = objFunc[i];
    }
  }

}

// flag: デフォルト: false, LPを解いた後: true
void LP::Disp(bool flag){
  unsigned int i, j;
  if (!flag){
    for (i = 0; i < rows; ++i){
      for (j = 0; j < cols; ++j){
        if (j != cols - 1){
          cout << setw(3) << right << matrix[i][j] << " ";
        } else {
          cout << setw(3) << right<< matrix[i][j] << "\n";
        }
      }
    }
  } else {
    // 最適解と最適値の出力
    for (j = 0; j < vars - rows + 1; ++j){
      for (i = 0; i < rows; ++i){
        if (matrix[i][j] == 1){
          cout << "x" << j << ": " << setw(3) << right << matrix[i][cols - 1] << "\n";
        }
      }
    }
    cout << "optimal solution: " << matrix[rows - 1][cols - 1] << "\n";
  }
}

/*
 * シンプレックス法
 */
void LP::Simplex(){

  unsigned int i, j, x, y; // indexを保存する
  while (1) {
    // 効率的に目的関数を最小化できる列を選択する.
    min = 0xfffffff;
    for (i = 0; i < cols - 1; ++i) {
      if (matrix[rows - 1][i] < min) {
        min = matrix[rows - 1][i];
        y = i;
      }
    }

    // 目的関数値がこれ以上小さくならない場合には繰り返しを終了する
    if (min >= 0) break;

    // 各制約式で変数x_yがどこまで増やせるかを調べる
    min = 0xfffffff;
    for (i = 0; i < rows - 1; ++i) {
      p = matrix[i][cols - 1] / matrix[i][y];
      if (matrix[i][y] > 0 && p < min) {
        min = p;
        x = i;
      }
    }

    // ピボット係数
    p = matrix[x][y];

    // ピボットが1になるように, ピボットのある行の全てをピボット係数 p で除算
    for (i = 0; i < cols; ++i){
      matrix[x][i] = matrix[x][i] / p;
    }
    // ピボット列の掃き出し
    for (i = 0; i < rows; ++i) {
      if (i != x) {
        d = matrix[i][y];
        for (j = 0; j < cols; ++j)
          matrix[i][j] = matrix[i][j] - d * matrix[x][j];
      }
    }
  }
}

/*
 * メイン処理
 */
int main(){

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
  objLP.Disp(false);

  // シンプレックス法
  objLP.Simplex();
  objLP.Disp(true);

  // 正常終了
  return 0;
}
