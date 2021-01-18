# Particle swarm optimization method (PSO) and random search (Monte Carlo)
### Presented implementations
This repository contains sequential and parallel implementation made with **OpenMP**. You can find our other implementations in the following repositories:
- **MPI:** [https://github.com/maciejpik/porr-pso-mpi](https://github.com/maciejpik/porr-pso-mpi "https://github.com/maciejpik/porr-pso-mpi")
- **CUDA:** [https://github.com/maciejpik/porr-pso-cuda](https://github.com/maciejpik/porr-pso-cuda "https://github.com/maciejpik/porr-pso-cuda")

## Exemplary tasks the software optimizes
### Task 1
<p align="center">
<img src = "https://latex.codecogs.com/gif.latex?\min_{x}&space;\left&space;(&space;f(x)=\frac{1}{40}\sum_{i=1}^{n}(x_i^2)&space;&plus;1&space;-&space;\prod_{i=1}^{n}cos(\frac{x_i}{i})&space;\right&space;),&space;-40\leq&space;x_i\leq&space;40,&space;i=1,\dots,n">
</p>

### Task 2
<p align="center">
<img src ="https://latex.codecogs.com/gif.latex?\min_{x}&space;\left&space;(&space;f_1(x)=\sum_{i=1}^{n-1}&space;\left&space;[&space;100(x_{i&plus;1}-x_i^2)^2&space;&plus;&space;(1-x_i)^2)&space;\right&space;]&space;\right&space;),&space;-40\leq&space;x_i\leq&space;40">
</p>

## 2d sections of our tasks with the heat map 
###  Task 1
<p align="center">
<img src = "https://github.com/egi-megi/porr-pso/blob/master/sprawozdanie/sprawozdanie_1/grafiki/Wykresy2d/Zad1_2d_heatmap.png">
</p>

## Task 2

<p align="center">
<img src = "https://github.com/egi-megi/porr-pso/blob/master/sprawozdanie/sprawozdanie_1/grafiki/Wykresy2d/Rosenbrock_2d_heatmap_close_min.png">
</p>

## Exemplary results
### Task 1 - PSO
<p align="center">
<img src = "https://github.com/egi-megi/rojCzastek_Szczepanski_Jurkiewicz_Pikulinski/blob/plottingTrajectories/PSO_zad1_ANIM.gif">
</p>

### Task 1 - Monte Carlo
<p align="center">
<img src = "https://github.com/egi-megi/rojCzastek_Szczepanski_Jurkiewicz_Pikulinski/blob/plottingTrajectories/MC_zad1_ANIM_faster.gif">
</p>

### Task 2 - PSO
<p align="center">
<img src = "https://github.com/egi-megi/rojCzastek_Szczepanski_Jurkiewicz_Pikulinski/blob/plottingTrajectories/PSO_zad2_ANIM.gif">
</p>

### Task 2 - Monte Carlo

<p align="center">
<img src = "https://github.com/egi-megi/rojCzastek_Szczepanski_Jurkiewicz_Pikulinski/blob/plottingTrajectories/MC_zad2_ANIM.gif">
</p>

### Task 2

### Generated with MPI Monte carlo version for Task 2 - Valley/Banana function

<p align="center">
<img src = "https://github.com/egi-megi/porr-pso/blob/plottingTrajectories/Wykresy%20PORR%20_%20GPU/MPI_MC_T2/MPI_MC_T2.gif">
</p>

<p align="center">
<img src = "https://github.com/egi-megi/porr-pso/blob/plottingTrajectories/Rosenbrock_function.svg">
</p>
            
## Trajectories

### Monte carlo Task 1
<p align="center">
<img src = "https://github.com/egi-megi/porr-pso/blob/master/sprawozdanie/sprawozdanie_1/grafiki/Wykresy2d/Zad1_MC_plot_5.png">
</p>


### PSO Task 1
<p align="center">
<img src = "https://github.com/egi-megi/porr-pso/blob/master/sprawozdanie/sprawozdanie_1/grafiki/Wykresy2d/zad1_pso_plot_5.png">
</p>

### Generated with MPI Monte carlo version for Task 1

<p align="center">
<img src = "https://github.com/egi-megi/porr-pso/blob/plottingTrajectories/Wykresy%20PORR%20_%20GPU/MPI_MC_T1/MPI_%20MC_T1_trajectory_id15.png">
</p>

### Generated with MPI PSO version for Task 1

<p align="center">
<img src = "https://github.com/egi-megi/porr-pso/blob/plottingTrajectories/Wykresy%20PORR%20_%20GPU/MPI_PSO_T1/MPI_PSO_T1_trajectory_id1.png">
</p>       
            
## Plots with isolines

### Task 1 - Isolines of cost function 
<p align="center">
<img src = "https://github.com/egi-megi/rojCzastek_Szczepanski_Jurkiewicz_Pikulinski/blob/plottingTrajectories/Stare%20Wykresy/PSO_izolinie_cbar_scatter.svg">
</p>

### Task 2 - Neighbourhood of global minimum of Rosenbrock's function
<p align="center">
<img src = "https://github.com/egi-megi/rojCzastek_Szczepanski_Jurkiewicz_Pikulinski/blob/plottingTrajectories/Przedstawienie%20funkcji%20kosztu/Rosenbrock_2d_izo_close_minimum.svg">
</p>
