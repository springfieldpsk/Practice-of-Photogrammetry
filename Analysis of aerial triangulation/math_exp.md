# 解析空中三角测量

## 一.连续法像对的相对定向

### 目标:

求解各模型点在各模型像空间辅助坐标系中的坐标 $（X_{i},Y_{i},Z_{i}）$

### 步骤:

#### 1.用连续法相对定向求解相对定向元素 $（b_{x}，b_{y}，b_{z}，φ，ω，κ）$
1. 计算初始值
   $$ b_{x}=给定值(200mm) $$
   $$ b_{y} = b_{x} \cdot tan_{\mu} \approx b_{x} \cdot \mu $$
   $$ b_{z} = b_{x} \cdot tan_{\nu} \approx b_{x} \cdot \nu$$
   $$ \mu = \nu = \varphi = \kappa = \omega =0 $$
2. 像空间坐标系转像空间辅助坐标系
    $$
    \begin{bmatrix}
        X_{1} \\ Y_{1} \\ Z_{1}
    \end{bmatrix}
    =
    R_{1}
    \begin{bmatrix}
        x_{1} \\ y_{1} \\ -f
    \end{bmatrix}
    $$
    $$
    \begin{bmatrix}
        X_{2} \\ Y_{2} \\ Z_{2}
    \end{bmatrix}
    =
    R_{2}
    \begin{bmatrix}
        x_{2} \\ y_{2} \\ -f
    \end{bmatrix}
    $$
    $$
    R_{1}=上个航带的R_{2}
    $$
    $$
    R_{2}=
    \begin{bmatrix}
      cos_{\varphi}cos_{\kappa}-sin_{\varphi}sin_{\omega}sin_{\kappa}  & -cos_{\varphi}sin_{\kappa}-sin_{\varphi}sin_{\omega}cos_{\kappa} & -sin_{\varphi}cos_{\omega} \\
      cos_{\omega}sin_{\kappa} & cos_{\omega}cos_{\kappa} & -sin_{\omega} \\
      sin_{\varphi}cos_{\kappa}+cos_{\varphi}sin_{\omega}sin_{\kappa}  & -sin_{\varphi}sin_{\kappa}+cos_{\varphi}sin_{\omega}cos_{\kappa} & cos_{\varphi}cos_{\omega} 
    \end{bmatrix}
    $$
3. 计算投影系数
   $$ N_{1}=\frac {b_{x}Z_{2}-b_{z}X_{2}}{X_{1}Z_{2}-X_{2}Z_{1}} $$
   $$ N_{2}=\frac {b_{x}Z_{1}-b_{z}X_{1}}{X_{1}Z_{2}-X_{2}Z_{1}} $$
4. 计算A矩阵
   $$ 
   \begin{cases}
    a=b_{x} \\ b=-\frac{Y_{2}}{Z_{2}}b_{x} \\ c=-\frac{X_{2}Y_{2}}{Z_{2}}N_{2} \\
    d=-(Z_{2}+\frac{Y_{2}^{2}}{Z_{2}})N_{2} \\ e=X_{2}N_{2} 
    \end{cases}
   $$
   $$
   A=
   \begin{bmatrix}
        a_{1} & b_{1} & c_{1} & d_{1} & e_{1} \\
        a_{2} & b_{2} & c_{2} & d_{2} & e_{2} \\
        \vdots & \vdots & \vdots & \vdots & \vdots \\
        a_{n} & b_{n} & c_{n} & d_{n} & e_{n} 
   \end{bmatrix}
   $$  
5. 计算L矩阵
   $$ l=Q$$
   $$ Q=N_{1}Y_{1}-N_{2}Y_{2}-b_{y} $$
   $$ L = \begin{bmatrix}
   l_{1} & l_{2} & \cdots & l_{n}
   \end{bmatrix} ^T
   $$
6. 计算法方程
   $$ X= (A^TA)^{-1}A^TL $$
7. 利用改正数计算结果，多次迭代,当改正数值小于某一限差$(0.3*10^{-4})$后得到结果
   
#### 2.用前方交会公式计算各模型点坐标。

通过像空间辅助坐标系坐标计算未改正模型点
   $$
   \begin{cases}
   X_{M}=N_{1}X_{1} \\
   Y_{M}=\frac{1}{2}[N_{1}Y_{1}+N_{2}Y_{2}+b_{y}] \\
   Z_{M}=N_{1}Z_{1}
   \end{cases}
   $$
   
## 二.航带网模型的建立

### 目标:

求出航带内各模型点在航带统一坐标系（第一个像片的像空间坐标系）中的坐标 $(X_{i}',Y_{i}',Z_{i}')$。

### 步骤：

#### 1.根据模型间的三个公共点求解个模型的缩放系数ki

   $$ k = \frac {N_{1A}Z_{2A}-b_{zA}}{N_{1B}Z_{1B}}$$
   $$ k_{平} = \frac {k_{1}k_{2}k_{3}}{3} $$

#### 2.通过各模型缩放系数ki将模型内各模型点转换到航带统一坐标系。

1. 通过缩放系数计算各模型摄站摄影测量坐标
   
   $S_{1} 点在摄影测量坐标系（A-X_{p}Y_{p}Z_{p})中坐标值为$
   $$
   \begin{cases}
   X_{ps_{1}}=0 \\
   Y_{ps_{1}}=0 \\
   Z_{ps_{1}}=mf(即航高)
   \end{cases}
   $$ 
   $$
   \begin{cases}
   X_{ps_{2}}= X_{ps_{1}} + mb_{X} \\
   Y_{ps_{2}}= Y_{ps_{1}} + mb_{Y} \\
   Z_{ps_{2}}= Z_{ps_{1}} + mb_{Z}
   \end{cases}
   $$
   $$ 
   \begin{cases}
   X_{ps_{i}}= X_{ps_{i-1}} + k_{i} \cdot mb_{X} \\
   Y_{ps_{i}}= Y_{ps_{i-1}} + k_{i} \cdot mb_{Y} \\
   Z_{ps_{i}}= Z_{ps_{i-1}} + k_{i} \cdot mb_{Z}
   \end{cases}
   $$
2. 计算最终的模型点坐标
   
   第一个模型
   $$
   \begin{cases}
   X_{pM}=m \cdot N_{1}X_{1} \\
   Y_{pM}=\frac{m}{2}(N_{1}Y_{1} + N_{2}Y_{2} + b_{y}) \\
   Z_{pM}=m \cdot N_{1}Z_{1}
   \end{cases}
   $$

   第一个模型后的模型
   $$
   \begin{cases}
   X_{pi}=X_{ps_{j-1}}+ k_{j} \cdot m \cdot N_{1 \cdot j}X_{1 \cdot j} \\
   Y_{pi}=\frac{1}{2}(Y_{ps_{j-1}}+ k_{j} \cdot m \cdot N_{1 \cdot j}Y_{1 \cdot j} + Y_{ps_{j}}+ k_{j} \cdot m \cdot N_{2 \cdot j}Y_{2 \cdot j}) \\
   Z_{pi}=Z_{ps_{j}}+ k_{j} \cdot m \cdot N_{1 \cdot j}Z_{1 \cdot j}
   \end{cases}
   $$
## 三.模型的绝对定向

### 目标：

求出航带内各模型点在大地坐标系中的坐标$(X_{ti},Y_{ti},Z_{ti})$。

### 步骤：

#### 1.根据两个已知控制点确定大地坐标系与地面摄测坐标系之间的转换参数$(a、b、\lambda)$。

1. 在航带网两端选择1和2两个控制点，该两点需要同时具有地面测量坐标与摄测坐标，同时所有地面控制点、加密点的地面测量坐标与摄测坐标都要换算为以1点为坐标原点的坐标，即:
   $$
    \begin{cases}
   X_{t1i}=X_{ti}-X_{t1} \\
   Y_{t1i}=Y_{ti}-Y_{t1} \\
   Z_{t1i}=Z_{ti}-Z_{t1} \\
   X_{P1i}=X_{ti}-X_{t1} \\
   Y_{P1i}=Y_{ti}-Y_{t1} \\
   Z_{P1i}=Z_{ti}-Z_{t1}
   \end{cases}
   $$
2. 按平面坐标变换的计算公式得
   $$
   \begin{bmatrix}
      X_{P1} \\
      Y_{P1}
   \end{bmatrix}
   =
   \begin{bmatrix}
      \lambda sin \theta & \lambda cos \theta \\
      \lambda cos \theta - \lambda sin \theta & \lambda sin \theta
   \end{bmatrix}
   \begin{bmatrix}
      X_{t1} \\ Y_{t1} 
   \end{bmatrix}
   =
    \begin{bmatrix}
      b & a \\
      a & -b
   \end{bmatrix}
   \begin{bmatrix}
      X_{t1} \\ Y_{t1} 
   \end{bmatrix}
   $$
   $\theta$ 为两平面坐标系轴系之间的夹角; $\lambda$为缩放系数,都为未知数
3. 由上式联立求解得
   $$ 
   \begin{cases}
      a = \frac{Y_{t1}X_{P1}+X_{t1}Y_{P1}}{X_{t1}^2+Y_{t1}^2} \\
      b = \frac{X_{t1}X_{P1}-Y_{t1}Y_{P1}}{X_{t1}^2+Y_{t1}^2} 
   \end{cases}
   $$
   $$
   \lambda = \sqrt{a^2+b^2}
   $$
#### 2.将所有控制点的大地坐标$(X_{t},Y_{t},Z_{t})$通过转换参数（a、b）转换为地面摄测坐标系$(X_{tp},Y_{tp},Z_{tp})$。
   $$
   \begin{bmatrix}
      X_{tP1} \\
      Y_{tP1}
   \end{bmatrix}
   =
    \begin{bmatrix}
      b & a \\
      a & -b
   \end{bmatrix}
   \begin{bmatrix}
      X_{t1} \\ Y_{t1} 
   \end{bmatrix}
   $$
   $$
   Z_{tP1i} = \lambda Z_{t1i}
   $$

#### 3.根据已知控制点的地面摄测坐标$(X_{tp},Y_{tp},Z_{tp})$求解绝对定向元素$(ΔX，ΔY，ΔZ，\varphi，\omega，\kappa , λ)$。
   初始值 $\lambda$=1 ,其余=0
1. 利用重心公式求解重心坐标
   $$
   X_{tpg}= \frac{\sum X_{tp}}{n},
   Y_{tpg}= \frac{\sum Y_{tp}}{n},
   Z_{tpg}= \frac{\sum Z_{tp}}{n}
   $$
2. 重心化摄测坐标
   $$
   \begin{cases}
      \bar{X_{pi}}= X_{pi} - X_{pg} \\
      \bar{Y_{pi}}= Y_{pi} - Y_{pg} \\
      \bar{Z_{pi}}= Z_{pi} - Z_{pg} 
   \end{cases}
   $$
3. 计算误差方程式常数项$l$
   $$
   \begin{bmatrix}
      l_{X} \\ l_{Y} \\ l_{Z}
   \end{bmatrix}
   =
   \begin{bmatrix}
      \bar{X_{tp}} \\ \bar{Y_{tp}} \\\bar{Z_{tp}}
   \end{bmatrix}
   -
   \lambda _{0}
   R_{0}
   \begin{bmatrix}
      \bar{X_{p}} \\ \bar{Y_{p}} \\\bar{Z_{p}}
   \end{bmatrix}
   $$
4. 计算误差方程式系数矩阵 A
   $$
   A = 
   \begin{bmatrix}
      1 & 0 & 0 & \bar{X_{pi}} & -\bar{Z_{pi}} & 0 & -\bar{Y_{pi}} \\
      0 & 1 & 0 & \bar{Y_{pi}} & 0 & -\bar{Z_{pi}} & \bar{X_{pi}} \\
      0 & 0 & 1 & \bar{Z_{pi}} & \bar{X_{pi}} & \bar{Y_{pi}} & 0
   \end{bmatrix}
   $$
5. 组成法方程式系数矩阵$A^TPA$ 和常数项矩阵 $A^T P L$
6. 求解法方程 $X=(A^TPA)^{-1}A^TPL$ , P 为权阵
7. 计算新值 
   $$
   X=
   \begin{bmatrix}
     d \Delta X &   d \Delta Y &  d \Delta Z &  d \Delta \lambda &  d \Delta \varPhi
     &  d \Delta \omega &  d \Delta \kappa
   \end{bmatrix}
   $$
8. 利用改正数计算结果，多次迭代,当改正数值小于某一限差$(1*10^{-6})$后得到结果
   
#### 4.根据绝对定向元素（ΔX，ΔY，ΔZ，Φ，Ω，Κ，λ）将各模型点在航带统一坐标系中的坐标（Xi‘,Yi‘,Zi‘）转换为地面摄测坐标系（Xtp,Ytp,Ztp）。

#### 5.将各模型点的地面摄测坐标（Xtp,Ytp,Ztp）通过转换参数（a、b）转换为所有控制点的大地坐标（Xt,Yt,Zt）。
