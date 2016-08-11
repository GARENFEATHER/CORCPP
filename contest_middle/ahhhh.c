#include <cstdio>
#include <cstdlib>
#include <ctime>
#define MAX 1000 //最多可能皇后数
#define swap(a,b) {int t = a; a = b; b = t;}
//row[i]表示当前摆放方式下第i行的皇后数，col[i]表示当前摆放方式下第i列的皇后数
int row[MAX];
int col[MAX];

int N; //放置N个皇后在N*N棋盘上

//从左上到右下的对角线上row-col值是相同的，但是这个值有可能是负值，最小为-(N-1)，
//所以可以做个偏移，统一加上N-1，这样这个值就在[0,2*N-2]范围内，将这个值作为该对角线的编号
//pdiag[i]表示当前摆放方式下编号为i的对角线上的皇后数
int pdiag[2 * MAX];//principal diagonal,主对角线，左上到右下（表示和主对角线平行的2N-1条对角线）

//从右上到左下的对角线row+col的值相同，取值范围为[0, 2 * MAX - 2]，作为对角线编号
//cdiag[i]表示编号为i的对角线上的皇后数
int cdiag[2 * MAX];//counter diagonal,副对角线

//R[]用来存储皇后放置位置，R[row] = col表示(row,col)处,即“第row行第col列”有个皇后
int R[MAX];

//给定二维矩阵的一个点坐标，返回其对应的左上到右下的对角线编号
int getP(int row, int col) {
    return row - col + N - 1;
}

//给定二维矩阵的一个点坐标，返回其对应的右上到左下的对角线编号
int getC(int row, int col) {
    return row + col;
}

//返回begin, begin + 1, ... , end - 1 这end - begin个数中的随机的一个
int my_rand(int begin, int end) {//左闭右开[begin, end)
    return rand() % (end - begin) + begin;
}

//原地shuffle算法，算法导论中的randomize in place算法
void randomize(int a[], int begin, int end)// 左闭右开
{
    for(int i = begin; i <= end - 2; i++){
        int x = my_rand(i, end);
        swap(a[i], a[x]);
    }
}

//初始化皇后的摆放，同时初始化row,col,pdiag,cdiag数组
void init()
{
    for(int i = 0; i < N; i++){//N queens
        R[i] = i;
    }
    randomize(R, 0, N);//初始化N个皇后对应的R数组为0~N-1的一个排列，即没有任意皇后同列，也没有任何皇后同行
    for(int i = 0; i < N; i++){
        row[i] = 1;//每行恰好一个皇后
        col[i] = 0;
    }
    for(int i = 0; i < 2 * N - 1; i++){//N queens
        pdiag[i] = 0;
        cdiag[i] = 0;
    }
    for(int i = 0; i < N; i++){//N queens
        col[R[i]]++;
        pdiag[getP(i, R[i])]++;
        cdiag[getC(i, R[i])]++;
    }
}

bool adjust_row(int row);
void print_result();
bool qualify();

int main(int argc, const char *argv[])
{
    srand((unsigned)time(NULL));
    scanf("%d", &N);
    init();
    if (qualify()) {//运气很好，初始化后就满足终止条件
        print_result();
        return 0;
    }
    bool can_terminate = false;
    while (!can_terminate) {
        for (int i = 0; i < N; i++) {
            if(adjust_row(i)) {
                can_terminate = true;
                break;
            }
        }
    }
    print_result();
    return 0;
}
//用最小冲突算法调整第row行的皇后的位置（初始化时每行都有一个皇后，调整后仍然在第row行）
//调整过后check一下看看是否已经没有冲突，如果没有冲突（达到终止状态），返回true
bool adjust_row(int row) {
    int cur_col = R[row];
    int optimal_col = cur_col;//最佳列号，设置为当前列，然后更新
    int    min_conflict = col[optimal_col] + pdiag[getP(row, optimal_col)] - 1
        + cdiag[getC(row, optimal_col)] - 1;//对角线冲突数为当前对角线皇后数减一
    for (int i = 0; i < N; i++) {//逐个检查第row行的每个位置
        if (i == cur_col) {
            continue;
        }
        int conflict = col[i] + pdiag[getP(row, i)] + cdiag[getC(row, i)];
        if (conflict < min_conflict) {
            min_conflict = conflict;
            optimal_col = i;
        }
    }
    if (optimal_col != cur_col) {//要更新col,pdiag,cdiag
        col[cur_col]--;
        pdiag[getP(row, cur_col)]--;
        cdiag[getC(row, cur_col)]--;

        col[optimal_col]++;
        pdiag[getP(row, optimal_col)]++;
        cdiag[getC(row, optimal_col)]++;
        R[row] = optimal_col;
        if (col[cur_col] == 1 && col[optimal_col] == 1 
                && pdiag[getP(row, optimal_col)] == 1 && cdiag[getC(row, optimal_col)] == 1) {
            return qualify();//qualify相对更耗时，所以只在满足上面基本条件后才检查
        }
    }
    //当前点就是最佳点，一切都保持不变
    return false;//如果都没变的话，肯定不满足终止条件，否则上一次就应该返回true并终止了
    //return qualify();
}
bool qualify() {
    for(int i = 0; i < N; i++){//N queens
        if(col[R[i]] != 1 ||
                pdiag[getP(i, R[i])] != 1 ||
                cdiag[getC(i, R[i])] != 1) {
            return false;
        }
    }
    return true;
}
void print_result()
{
    printf("the result is like this:\n");
    for(int i = 0; i < N; i++){
        printf("%d,", R[i]);
    }
    printf("\n");
    for (int j = 0; j < N; j++) {
        for (int k = 0; k < N; k++) {
            if (R[j] == k)
                printf("*");
            else
                printf("-");
        }
        printf("\n");
    }
}