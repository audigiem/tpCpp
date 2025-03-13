#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np


SIGMA = 1
EPSILON = 1

def potentiel_LennardJones(distance):
    var = (SIGMA / distance)**6
    return 4*EPSILON*var * (var - 1)

def plot_potentiels():
    distances = np.linspace(1, 10, 10000)
    potentiels = [potentiel_LennardJones(i) for i in distances]

    plt.figure()
    plt.plot(distances, potentiels)
    plt.grid()
    plt.title('Potentiel de Lennard-Jones pour un système à 2 particules en fonction de leurs distance')
    plt.show()

plot_potentiels()