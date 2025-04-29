## 本地运行截图

![图](https://asd-1357033528.cos.ap-shanghai.myqcloud.com/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202025-04-28%20210417.png)

![+](https://asd-1357033528.cos.ap-shanghai.myqcloud.com/img/1.png)

![-](https://asd-1357033528.cos.ap-shanghai.myqcloud.com/img/2.png)

![*](https://asd-1357033528.cos.ap-shanghai.myqcloud.com/img/3.png)

![.](https://asd-1357033528.cos.ap-shanghai.myqcloud.com/img/4.png)

![t](https://asd-1357033528.cos.ap-shanghai.myqcloud.com/img/5.png)

![d](https://asd-1357033528.cos.ap-shanghai.myqcloud.com/img/6.png)

![r](https://asd-1357033528.cos.ap-shanghai.myqcloud.com/img/8.png)

![j](https://asd-1357033528.cos.ap-shanghai.myqcloud.com/img/9.png)

![i](https://asd-1357033528.cos.ap-shanghai.myqcloud.com/img/7.png)



## 实现思路

这里主要讲讲det_matrix、inv_matrix和rank_matrix函数的实现思路

-   **det_matrix**

    主要运用了递归的思想。其中，当行列数不等或为1、2时，能即刻得出结果，其中行列数均为2时，也作为递归调用的终止条件。当

行列数为一般情况时，根据|A|=∑j=1n(−1)i+jaij|Aij|公式写出递归函数，其中构造了temp_matrix这样一个矩阵表示Aij项。

-   **inv_matrix**

    总体上依据A^−1=1/|A|*(*A∗)这样一个矩阵求逆公式，实现细节上，开始对一些特殊情况（非方阵、行列式为0）进行了处理，之后的一般情况中，行列式的求解可以直接调用相应的函数，对于伴随阵的求解则参考了上面函数求Aij项的思路。

    ps.在该实现方式中，需特别注意额外讨论矩阵的行列数为1的情况。

-   **rank_matrix**

    总体上依照高斯消元法的思想，实现细节上，参考thinking.md中的思路：

    1.  首先，函数初始化秩为矩阵行数和列数中较小的那个值：

    rank=min(m,n)

    2.  接下来，函数将矩阵转化为上三角形式。这个过程通过高斯消元法实现，具体步骤如下：

    a. 对于每一列 i，从第 i 行开始，检查当前主对角线上的元素 aii 是否为零。如果 aii≠0 ，则表示可以进行高斯消元操作，否则需要在下方寻找一个非零元素，并将其与当前行交换。

    b. 对于当前主对角线上的元素 aii，将其下方的所有元素通过行运算消除为零，使得当前列下方的元素全部为零。

    c. 如果主对角线上的元素 aii 为零，则需要在下方寻找一个非零元素 aji 并将其与当前行交换，以确保在进行下一轮高斯消元时可以继续消去元素。

    d. 如果在下方找不到非零元素，说明当前列已经全为零，需要将秩减一，并将当前列的元素全部设为最后一列对应位置的元素。

    3.  最后，函数返回计算得到的秩值。

    其中，行运算的具体方式为

    Rj=Rj−ajiaii×Ri
    
    但结果不对啊