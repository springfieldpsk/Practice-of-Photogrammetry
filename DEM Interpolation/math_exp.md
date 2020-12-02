# 数字高程模型（DEM）内插

## 内容
利用移动二次曲面拟合法，由格网点P$（X_p,Y_p）$周围的10个已知点内插出待求格网点P的高程

## 操作步骤

### 1.读入已知点的坐标，建立以待定点为原点的局部坐标系

### 2.建立误差方程式：
    
$$
    v_{i} =  \bar{X_i}^2 A + \bar{X_i} \bar{Y_i} B + \bar{Y_i}^2 C + \bar{X_i}D + \bar{Y_i} E + F
    
$$

### 3.组成法方程，解算六个系数

$$
    x = (M^TPM)^{-1}M^TPZ
$$

$$
    M =\begin{bmatrix}
        \bar{X_i}^2 & \bar{X_i} \bar{Y_i} &  \bar{Y_i}^2 & \bar{X_i} & \bar{Y_i} &1
    \end{bmatrix}
$$

$$
    Z = \begin{bmatrix}
        Z_i \\
        \cdots
    \end{bmatrix}
$$

$$
    P = \begin{bmatrix}
        \frac{1}{\bar{X_1}^2 + \bar{Y_1}^2} & 0 & \cdots \\
        0 & \frac{1}{\bar{X_2}^2 + \bar{Y_2}^2} & \cdots \\
        \cdots & \cdots & \cdots
    \end{bmatrix}
$$
### 4.计算结果